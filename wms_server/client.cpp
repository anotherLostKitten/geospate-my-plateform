#include <iostream>
#include <string>

#include "sockpp/tcp_connector.h"
#include "cbor.h"

#define CLIENT_TIMEOUT 10s

using namespace std;

int main() {
    string host = "localhost";
    in_port_t port = sockpp::TEST_PORT;

    sockpp::initialize();
    sockpp::tcp_connector conn;

    sockpp::result res = conn.connect(host, port, CLIENT_TIMEOUT);

    if (!res)
        exit(1);

    if (!conn.read_timeout(CLIENT_TIMEOUT))
        exit(1);

    struct bbox query = {.minx = 11.54, .miny = 48.14, .maxx = 11.543, .maxy = 48.145};
    char buf[512];

    while (1) {
        sockpp::result<size_t> res;
#ifdef TEST_GET_BBOX_CIN
        cin >> query.minx >> query.miny >> query.maxx >> query.maxy;
#endif
        size_t len = encode_getmap_query((uint8_t*)buf, sizeof(buf), &query);

        if (conn.write_n(buf, len) != len)
            exit(1);

        res = conn.read(buf, sizeof(buf));
        if (!res || res.value() <= 0)
            exit(1);

        cout << "recieved: " << buf << endl;

        return 0;
    }

    return 0;
}
