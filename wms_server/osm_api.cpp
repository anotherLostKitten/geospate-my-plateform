#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <cpr/cpr.h>

#include "osm_api.h"
#include "gdal.h"

#define OSM_API_URL "https://api.openstreetmap.org/api/0.6/map"
#define TMP_OSM_FILE "tmp.osm"

using namespace std;

mutex osm_tmp_file_mutex;

void fetch_map_for_bounding_box(const struct bbox* query) {
    string bbox = std::format("{},{},{},{}", query->minx, query->miny, query->maxx, query->maxy);
    cpr::Response r = cpr::Get(cpr::Url{OSM_API_URL}, cpr::Parameters{{"bbox", bbox}});

    cout << r.status_code << "\t" << r.header["content-type"] // << "\n" << r.text
         << endl;

    if (r.status_code == 200) {
        lock_guard<mutex> guard(osm_tmp_file_mutex);
        ofstream outfile;
        outfile.open(TMP_OSM_FILE, ios::trunc);
        outfile << r.text;
        outfile.close();

        load_osm_to_geojson(TMP_OSM_FILE, get_bbox_filename(query));
    }
}
