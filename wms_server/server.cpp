#include <iostream>
#include <string>
#include <thread>

#include "sockpp/tcp_acceptor.h"

using namespace std;

void handler(sockpp::tcp_socket sock) {
    char buf[512];
    sockpp::result<size_t> res;

    while (1) {
        res = sock.read(buf, sizeof(buf));
        if (!res || res.value() <= 0)
            break;
        cout << "recieved: " << buf << endl;
        sock.write_n(buf, res.value());
    }
}

int main() {
    in_port_t port = sockpp::TEST_PORT;
    sockpp::initialize();

    error_code ec;
    sockpp::tcp_acceptor acc{port, 4, ec};

    if (ec)
        exit(1);

    cout << "waiting for connection on " << port << endl;

    while (1) {
        sockpp::inet_address peer;

        sockpp::result res = acc.accept(&peer);

        if (res) {
            cout << "connection with " << peer << endl;
            sockpp::tcp_socket sock = res.release();

            thread thr(handler, std::move(sock));
            thr.detach();
        } else
            cout << "error " << res.error_message();
    }
}
