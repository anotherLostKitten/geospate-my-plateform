#include <iostream>
#include <tinycbor/cbor.h>

#include "cbor.h"

#define CHECK_ERR(...) do {                     \
        if ((__VA_ARGS__) != CborNoError) {     \
            return 0;                           \
        }                                       \
    } while(0)                                  \

size_t decode_getmap_query(const uint8_t* buf, size_t size, struct getmap_query* query) {
    CborParser par;
    CborValue val, outVal;
    cbor_parser_init(buf, size, 0, &par, &outVal);
    CHECK_ERR(cbor_value_enter_container(&outVal, &val));
    CHECK_ERR(cbor_value_get_float(&val, &query->minx));
    CHECK_ERR(cbor_value_advance(&val));
    CHECK_ERR(cbor_value_get_float(&val, &query->miny));
    CHECK_ERR(cbor_value_advance(&val));
    CHECK_ERR(cbor_value_get_float(&val, &query->maxx));
    CHECK_ERR(cbor_value_advance(&val));
    CHECK_ERR(cbor_value_get_float(&val, &query->maxy));

    return size;
}

size_t encode_getmap_query(uint8_t* buf, size_t size, const struct getmap_query* query) {
    CborEncoder enc, arrEnc;
    cbor_encoder_init(&enc, buf, size, 0);
    CHECK_ERR(cbor_encoder_create_array(&enc, &arrEnc, 4));
    CHECK_ERR(cbor_encode_float(&arrEnc, query->minx));
    CHECK_ERR(cbor_encode_float(&arrEnc, query->miny));
    CHECK_ERR(cbor_encode_float(&arrEnc, query->maxx));
    CHECK_ERR(cbor_encode_float(&arrEnc, query->maxy));
    CHECK_ERR(cbor_encoder_close_container(&enc, &arrEnc));

    return cbor_encoder_get_buffer_size(&enc, buf);
}
