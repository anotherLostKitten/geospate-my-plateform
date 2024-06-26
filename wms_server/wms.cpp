#include <iostream>
#include <format>

#include "wms.h"

using namespace std;

void print_bbox(const struct bbox* query) {
    cout << "getmap\n\tminx: " << query->minx
         << "\n\tminy: " << query->miny
         << "\n\tmaxx: " << query->maxx
         << "\n\tmaxy: " << query->maxy << endl;
}

string get_bbox_filename(const struct bbox* query) {
    return format("map_bbox_{}_{}_{}_{}.geojson", query->minx, query->miny, query->maxx, query->maxy);
}
