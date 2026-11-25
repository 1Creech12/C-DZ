#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/event.h>
#include <sys/time.h>

using namespace std;

static const int PORT = 20001;

static void setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags >= 0)
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static bool watch(int kq, int fd, int16_t filter, uint16_t flags) {
    struct kevent ev;
    EV_SET(&ev, fd, filter, flags, 0, 0, NULL);
    return kevent(kq, &ev, 1, NULL, 0, NULL) == 0;
}

static string nowHM() {
    time_t t = time(NULL);
    tm* lt = localtime(&t);
    char s[8];
    strftime(s, sizeof(s), "%H:%M", lt);
    return string(s);
}

static string peerIP(int fd) {
    sockaddr_in a;
    socklen_t len = sizeof(a);
    if (getpeername(fd, (sockaddr*)&a, &len) < 0) return string("?");
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &a.sin_addr, ip, sizeof(ip));
    return string(ip);
}

static string currentDate() {
    time_t t = time(NULL);
    tm* lt = localtime(&t);
    char s[16];
    strftime(s, sizeof(s), "%d.%m.%Y", lt);
    return string(s);
}

static string currentTime() {
    time_t t = time(NULL);
    tm* lt = localtime(&t);
    char s[16];
    strftime(s, sizeof(s), "%H:%M:%S", lt);
    return string(s);
}

static void trim(string& s) {
    while (!s.empty() && (s[s.size() - 1] == '\n' || s[s.size() - 1] == '\r' ||
                          s[s.size() - 1] == ' '  || s[s.size() - 1] == '\t'))
        s.erase(s.size() - 1);
    size_t i = 0;
    while (i < s.size() && (s[i] == ' ' || s[i] == '\t')) i++;
    if (i > 0) s.erase(0, i);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket < 0) { perror("socket"); return 1; }

    int one = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);

    if (::bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    if (::listen(serverSocket, 16) < 0) { perror("listen"); return 1; }

    setNonBlocking(serverSocket);

    int kq = kqueue();
    if (kq < 0) { perror("kqueue"); return 1; }

    if (!watch(kq, serverSocket, EVFILT_READ, EV_ADD | EV_ENABLE)) {
        perror("kevent");
        return 1;
    }

    cout << "Асинхронный сервер времени и даты запущен. Слушаю 0.0.0.0:" << PORT
         << " (Ctrl+C — выход)" << endl;

    struct kevent events[64];

    while (true) {
        int n = kevent(kq, NULL, 0, events, 64, NULL);

        if (n < 0) {
            if (errno == EINTR) continue;
            perror("kevent");
            break;
        }

        for (int i = 0; i < n; i++) {
            int fd = (int)events[i].ident;

            if (fd == serverSocket) {
                while (true) {
                    sockaddr_in clientAddr;
                    socklen_t clientLen = sizeof(clientAddr);
                    int client = ::accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);
                    if (client < 0) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                        perror("accept");
                        break;
                    }
                    setNonBlocking(client);
                    watch(kq, client, EVFILT_READ, EV_ADD | EV_ENABLE);
                }
                continue;
            }

            string ip = peerIP(fd);

            char buf[256];
            ssize_t r = recv(fd, buf, sizeof(buf) - 1, 0);

            if (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
                continue;

            if (r > 0) {
                buf[r] = '\0';

                string request(buf);
                trim(request);
                cout << "В " << nowHM() << " от " << ip
                     << " получена строка: " << request << endl;

                string reply;
                if (request == "time" || request == "1")
                    reply = currentTime();
                else if (request == "date" || request == "2")
                    reply = currentDate();
                else
                    reply = "Ошибка: неизвестный запрос, ожидается time или date";

                send(fd, reply.c_str(), reply.size(), 0);
                cout << "В " << nowHM() << " клиенту " << ip
                     << " отправлена строка: " << reply << endl;
            } else if (r == 0) {
                cout << "Клиент " << ip << " закрыл соединение" << endl;
            } else {
                perror("recv");
            }

            watch(kq, fd, EVFILT_READ, EV_DELETE);
            close(fd);
        }
    }

    close(kq);
    close(serverSocket);
    return 0;
}
