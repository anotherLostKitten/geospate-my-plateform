#include <gdal.h>

GDALDatasetH load_osm_to_gdal(std::string osm_file_loc);

int write_osm_to_geojson(std::string osm_file_loc, std::string out_file_loc);
