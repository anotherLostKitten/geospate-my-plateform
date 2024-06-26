#include <string>
#include <iostream>

#include <gdal.h>
#include <gdal_utils.h>

#include "osm_api.h"

using namespace std;

void load_osm_to_geojson(string osm_file_loc, string out_file_loc) {
    int err;
    GDALAllRegister();

    GDALDriverH driver = GDALGetDriverByName("OSM");
    cout << GDALGetDescription(driver) << endl;

    GDALDatasetH dat = GDALOpenEx(osm_file_loc.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (dat == NULL) {
        cerr << "could not open tmp osm file " << osm_file_loc << endl;
        return;
    }
    GDALDatasetH dat2 = GDALVectorTranslate(out_file_loc.c_str(), NULL, 1, &dat, NULL, &err);

    if (err != 0) {
        cerr << "could not write geojson file with error " << err << endl;
    }
}
