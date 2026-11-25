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
static const int TIMEOUT_SEC = 5;

static void setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags >= 0)
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static bool waitFor(int kq, int fd, int16_t filter, int seconds) {
    struct kevent ev;
    EV_SET(&ev, fd, filter, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if (kevent(kq, &ev, 1, NULL, 0, NULL) < 0) { perror("kevent"); return false; }

    struct timespec ts;
    ts.tv_sec  = seconds;
    ts.tv_nsec = 0;

    struct kevent out[1];
    int n = kevent(kq, NULL, 0, out, 1, &ts);

    EV_SET(&ev, fd, filter, EV_DELETE, 0, 0, NULL);
    kevent(kq, &ev, 1, NULL, 0, NULL);

    return n > 0;
}

static bool sendAll(int kq, int fd, const char* data, size_t len) {
    while (len > 0) {
        ssize_t s = send(fd, data, len, 0);

        if (s > 0) {
            data += s;
            len  -= s;
            continue;
        }
        if (s < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            if (!waitFor(kq, fd, EVFILT_WRITE, TIMEOUT_SEC)) return false;
            continue;
        }
        perror("send");
        return false;
    }
    return true;
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) { perror("socket"); return 1; }
    setNonBlocking(sock);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    int kq = kqueue();
    if (kq < 0) { perror("kqueue"); return 1; }

    if (::connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        if (errno != EINPROGRESS) { perror("connect"); return 1; }

        if (!waitFor(kq, sock, EVFILT_WRITE, TIMEOUT_SEC)) {
            cerr << "connect: сервер не ответил за " << TIMEOUT_SEC << " с" << endl;
            return 1;
        }

        int err = 0;
        socklen_t errLen = sizeof(err);
        getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &errLen);
        if (err != 0) {
            errno = err;
            perror("connect");
            return 1;
        }
    }

    cout << "Соединение с сервером установлено (асинхронно)" << endl;

    const char* msg = "Hello world!";
    if (!sendAll(kq, sock, msg, strlen(msg))) { close(sock); return 1; }
    cout << "Отправлено: " << msg << endl;

    string reply;
    char buf[256];

    while (true) {
        ssize_t r = recv(sock, buf, sizeof(buf), 0);

        if (r > 0) {
            reply.append(buf, r);
            continue;
        }
        if (r == 0) break;

        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            if (!waitFor(kq, sock, EVFILT_READ, TIMEOUT_SEC)) {
                cerr << "recv: ответ не пришёл за " << TIMEOUT_SEC << " с" << endl;
                break;
            }
            continue;
        }

        perror("recv");
        break;
    }

    close(kq);
    close(sock);

    cout << "Ответ от сервера: " << reply << endl;
    return 0;
}
