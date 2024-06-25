#include <iostream>
#include <string>

#include "sockpp/tcp_acceptor.h"

using namespace std;

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
        } else
            cout << "error " << res.error_message();
    }
}
