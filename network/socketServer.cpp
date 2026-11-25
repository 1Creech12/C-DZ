#include <iostream>
#include <cstring>
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

static const int PORT = 20000;
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

static string ipOf(const sockaddr_in& a) {
    char ip[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &a.sin_addr, ip, sizeof(ip)) == NULL)
        return string("?");
    return string(ip);
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

    cout << "Асинхронный сервер запущен. Слушаю 0.0.0.0:" << PORT
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
                    cout << "Подключился клиент: " << ipOf(clientAddr) << endl;
                }
                continue;
            }

            char buf[256];
            ssize_t r = recv(fd, buf, sizeof(buf) - 1, 0);

            if (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
                continue;

            if (r > 0) {
                buf[r] = '\0';
                cout << "Получено сообщение: " << buf << endl;

                const char* reply = "Hello from server!";
                send(fd, reply, strlen(reply), 0);
            } else if (r == 0) {
                cout << "Клиент закрыл соединение" << endl;
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
