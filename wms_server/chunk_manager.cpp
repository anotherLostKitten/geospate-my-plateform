#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

#include "wms.h"
#include "osm_api.h"
#include "constants.h"

using namespace std;

vector<string> check_bbox_local_file(const struct bbox* bbox) {
    vector<string> fs;
    string fn = get_bbox_filename(bbox);
    for (const filesystem::directory_entry entry
             : filesystem::directory_iterator(GEOJSON_PATH))
        if (entry.is_regular_file() && fn.find(entry.path().stem()) != string::npos)
            fs.push_back(entry.path().filename());

    return fs;
}

void load_bbox(const struct bbox* outer_bbox) {
    unique_ptr<struct bbox[]> bboxes;
    size_t nbb = create_normalized_bbox(outer_bbox, &bboxes);
    for (int i = 0; i < nbb; i++) {

    }
}
