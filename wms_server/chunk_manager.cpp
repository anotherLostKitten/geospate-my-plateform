#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "wms.h"
#include "osm_api.h"
#include "constants.h"

using json = nlohmann::json;
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
        vector<string> fs = check_bbox_local_file(&bboxes[i]);
        if (fs.empty()) {
            cout << "bbox not found for " << get_bbox_filename(&bboxes[i]) << endl;
            GDALDatasetH dat = fetch_map_for_bounding_box(&bboxes[i]);
            if (dat)
                GDALClose(dat);
        }
    }
}

json get_chunk_json(const struct bbox* bbox) {
    vector<string> fns = check_bbox_local_file(bbox);
    if (fns.empty())
        return NULL;

    json data = json::array();
    for (const string fn : fns) {
        std::ifstream f(fn);
        data.emplace_back(json::parse(f));
    }
    return data;
}
