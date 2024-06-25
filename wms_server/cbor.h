#pragma once

#include <stdint.h>

#include "wms.h"

size_t decode_getmap_query(const uint8_t* buf, size_t size, struct getmap_query* query);

size_t encode_getmap_query(uint8_t* buf, size_t size, const struct getmap_query* query);
