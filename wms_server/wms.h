#pragma once

#include <stdint.h>
#include <string>

struct getmap_query {
    float minx;
    float miny;
    float maxx;
    float maxy;
};

void print_getmap_query(const struct getmap_query* query);

std::string get_bbox_filename(const struct getmap_query* query);
