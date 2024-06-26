#pragma once

#include <stdint.h>
#include <string>
#include <memory>

struct bbox {
    float minx;
    float miny;
    float maxx;
    float maxy;
};

void print_bbox(const struct bbox* query);

std::string get_bbox_filename(const struct bbox* query);

size_t create_normalized_bbox(const struct bbox* outer, std::unique_ptr<struct bbox[]>* arr);
