#include <iostream>
#include <string>

#include "sockpp/tcp_connector.h"

#define TIMEOUT 10s

using namespace std;

int main() {
    string host = "localhost";
    in_port_t port = sockpp::TEST_PORT;

    sockpp::initialize();
    sockpp::tcp_connector conn;

    sockpp::result res = conn.connect(host, port, TIMEOUT);

    if (!res)
        exit(1);

    if (!conn.read_timeout(TIMEOUT))
        exit(1);

    string msg = "test";
    char buf[512];

    while (1) {
        sockpp::result<size_t> res;

        if (conn.write(msg) != msg.length())
            exit(1);

        res = conn.read(buf, sizeof(buf));
        if (!res || res.value() <= 0)
            exit(1);

        cout << "recieved: " << buf << endl;
    }

    return 0;
}
