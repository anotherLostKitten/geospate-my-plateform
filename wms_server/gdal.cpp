#include <string>
#include <iostream>
#include <format>

#include <gdal.h>
#include <gdal_utils.h>

#include "osm_api.h"
#include "constants.h"

using namespace std;

GDALDatasetH load_osm_to_gdal(string osm_file_loc) {
    int err;

    // GDALDriverH driver = GDALGetDriverByName("OSM");
    // cout << GDALGetDescription(driver) << endl;

    GDALDatasetH dat = GDALOpenEx(osm_file_loc.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);

    if (dat == NULL)
        cerr << "could not open tmp osm file " << osm_file_loc << endl;
    return dat;

    // GDALDatasetH dat2 = GDALVectorTranslate(out_file_loc.c_str(), NULL, 1, &dat, NULL, &err);
    // if (err != 0) {
    //     cerr << "could not write geojson file with error " << err << endl;
    // }
}

int write_osm_to_geojson(string osm_file_name, string out_file_loc) {
    GDALDatasetH dat = load_osm_to_gdal(osm_file_name);
    if (!dat)
        return -1;

    size_t layers = GDALDatasetGetLayerCount(dat);

    for (int i = 0; i < layers; i++) {
        OGRLayerH layer = GDALDatasetGetLayer(dat, i);
        const char* opts_txt[2] = {OGR_L_GetName(layer), NULL};
        GDALVectorTranslateOptions* opts =
            GDALVectorTranslateOptionsNew((char**)opts_txt, NULL);
        string out_file = format(GEOJSON_PATH "{}_{}.geojson", OGR_L_GetName(layer), out_file_loc);
        int err = 0;
        GDALDatasetH out_dat = GDALVectorTranslate(out_file.c_str(), NULL, 1, &dat, opts, &err);
        GDALVectorTranslateOptionsFree(opts);
        if (err) return err;
        if (out_dat) GDALClose(out_dat);

        GDALClose(dat);
        if (i < layers - 1) {
            dat = load_osm_to_gdal(osm_file_name);
            if (!dat)
                return -1;
        }
    }
    return 0;
}
