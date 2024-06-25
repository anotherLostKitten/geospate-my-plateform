#include <iostream>
#include <string>

#include "sockpp/tcp_connector.h"
#include "cbor.h"

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

    struct getmap_query query = {.minx = 1, .miny = 2, .maxx = 3, .maxy = 4};
    char buf[512];

    while (1) {
        sockpp::result<size_t> res;

        size_t len = encode_getmap_query((uint8_t*)buf, sizeof(buf), &query);

        if (conn.write_n(buf, len) != len)
            exit(1);

        res = conn.read(buf, sizeof(buf));
        if (!res || res.value() <= 0)
            exit(1);

        cout << "recieved: " << buf << endl;
    }

    return 0;
}
