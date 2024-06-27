#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <cpr/cpr.h>

#include "osm_api.h"
#include "gdal.h"

#define OSM_API_URL "https://api.openstreetmap.org/api/0.6/map"
#define TMP_OSM_FILE "tmp.osm"
#define OVERPASS_API_URL "https://overpass-api.de/api/interpreter"

using namespace std;

mutex osm_tmp_file_mutex;

GDALDatasetH fetch_map_for_bounding_box(const struct bbox* query) {
    string bbox = std::format("{},{},{},{}", query->minx, query->miny, query->maxx, query->maxy);
    cpr::Response r = cpr::Get(cpr::Url{OSM_API_URL}, cpr::Parameters{{"bbox", bbox}});

    cout << r.status_code << "\t" << r.header["content-type"] // << "\n" << r.text
         << endl;

    if (r.status_code == 200) {
        lock_guard<mutex> guard(osm_tmp_file_mutex);
        ofstream outfile; // TODO ? it would be nicer if we could use virtual memeory here instead of creating a temp file but that would require more effort
        outfile.open(TMP_OSM_FILE, ios::trunc);
        outfile << r.text;
        outfile.close();

        GDALDatasetH dat = load_osm_to_gdal(TMP_OSM_FILE);
        if (!dat) return NULL;

        if (write_gdal_to_geojson(dat, get_bbox_filename(query))) {
            GDALClose(dat);
            return NULL;
        }
        return dat;
    }
    return NULL;
}

void fetch_bounding_box_for_city(string city_name, struct bbox* query) {
    return; // TODO ?
}
