#pragma once

#include <nlohmann/json.hpp>

#include "wms.h"

void load_bbox(const struct bbox* outer_bbox);

nlohmann::json get_chunk_json(const struct bbox* bbox);
