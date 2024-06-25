#include <iostream>

#include "wms.h"

using namespace std;

void print_getmap_query(const struct getmap_query* query) {
    cout << "getmap\n\tminx: " << query->minx
         << "\n\tminy: " << query->miny
         << "\n\tmaxx: " << query->maxx
         << "\n\tmaxy: " << query->maxy << endl;
}
