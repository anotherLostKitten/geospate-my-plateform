#include <iostream>
#include <string>
#include <format>
#include <cpr/cpr.h>

#include "osm_api.h"

#define OSM_API_URL "https://api.openstreetmap.org/api/0.6/map"

using namespace std;

void fetch_bounding_box(const struct getmap_query* query) {
    string bbox = std::format("{},{},{},{}", query->minx, query->miny, query->maxx, query->maxy);
    cpr::Response r = cpr::Get(cpr::Url{OSM_API_URL}, cpr::Parameters{{"bbox", bbox}});

    cout << r.status_code << "\t" << r.header["content-type"] << "\n" << r.text << endl;
}
