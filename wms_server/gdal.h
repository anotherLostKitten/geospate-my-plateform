#include <gdal.h>

GDALDatasetH load_osm_to_gdal(std::string osm_file_loc);

int write_gdal_to_geojson(GDALDatasetH dat, std::string out_file_loc);
