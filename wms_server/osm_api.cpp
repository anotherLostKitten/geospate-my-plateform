#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <cpr/cpr.h>

#include "osm_api.h"

#define OSM_API_URL "https://api.openstreetmap.org/api/0.6/map"
#define TMP_OSM_FILE "tmp.osm"

using namespace std;

void fetch_bounding_box(const struct getmap_query* query) {
    string bbox = std::format("{},{},{},{}", query->minx, query->miny, query->maxx, query->maxy);
    cpr::Response r = cpr::Get(cpr::Url{OSM_API_URL}, cpr::Parameters{{"bbox", bbox}});

    cout << r.status_code << "\t" << r.header["content-type"] << "\n" << r.text << endl;

    // TODO thread safety))
    if (r.status_code == 200) {
        ofstream outfile;
        outfile.open(TMP_OSM_FILE, ios::trunc);
        outfile << r.text;
        outfile.close();
    }
}
