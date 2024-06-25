#include <stdint.h>

struct getmap_query {
    float minx;
    float miny;
    float maxx;
    float maxy;
};

void print_getmap_query(const struct getmap_query* query);
