#pragma once

#include "wms.h"

void fetch_map_for_bounding_box(const struct bbox* query);

void fetch_bounding_box_for_city(std::string city_name, struct bbox* query);
