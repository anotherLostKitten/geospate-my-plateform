#pragma once

#include <stdint.h>
#include <string>

struct bbox {
    float minx;
    float miny;
    float maxx;
    float maxy;
};

void print_bbox(const struct bbox* query);

std::string get_bbox_filename(const struct bbox* query);
