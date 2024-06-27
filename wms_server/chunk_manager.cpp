#include <iostream>
#include <string>
#include <filesystem>

#include "wms.h"
#include "osm_api.h"
#include "constants.h"

using namespace std;

int check_bbox_local_file(const struct bbox* bbox, unique_ptr<string>* file_names) {
    int n = 0;
    for (const filesystem::directory_entry entry
             : filesystem::directory_iterator(GEOJSON_PATH)) {
        cout << entry << endl;
    }
    return n;
}

void load_bbox(const struct bbox* outer_bbox) {
    unique_ptr<struct bbox[]> bboxes;
    size_t nbb = create_normalized_bbox(outer_bbox, &bboxes);
    for (int i = 0; i < nbb; i++) {

    }
}
