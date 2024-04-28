#include <stdint.h>
#include <string.h>

#include "hash_func.h"

uint32_t MurmurHash3_32 (const void *key_void, const uint32_t len, const uint32_t seed) {

    const uint8_t *key = (const uint8_t *) key_void;
    uint32_t hash_ = seed;

    uint32_t FourBytesBlock = 0;

    for (uint32_t i = len / 4; i > 0; i--) {

        memcpy (&FourBytesBlock, key, sizeof (uint32_t));

        key += sizeof (uint32_t);

        FourBytesBlock *= MAGIC_NUM_1;
        FourBytesBlock = MyROL (FourBytesBlock, MAGIC_NUM_FOR_ROL_1);
        FourBytesBlock *= MAGIC_NUM_2;

        hash_ ^= FourBytesBlock;
        hash_ = MyROL (hash_, MAGIC_NUM_FOR_ROL_2);
        hash_ = hash_ * MAGIC_NUM_6 + MAGIC_NUM_3;
    }

    FourBytesBlock = 0;

    for (uint32_t i = len % 4; i > 0; i--) {

        memcpy (&FourBytesBlock, (key + i - 1), 1);

        FourBytesBlock <<= 8;
    }

    FourBytesBlock *= MAGIC_NUM_1;
    FourBytesBlock = MyROL (FourBytesBlock, MAGIC_NUM_FOR_ROL_1);
    FourBytesBlock *= MAGIC_NUM_2;

    hash_ ^= FourBytesBlock;

    hash_ ^= len;

    hash_ ^= (hash_ >> MAGIC_NUM_FOR_BIT_SHIFT_1);
    hash_ *= MAGIC_NUM_4;
    hash_ ^= (hash_ >> MAGIC_NUM_FOR_BIT_SHIFT_2);
    hash_ *= MAGIC_NUM_5;
    hash_ ^= (hash_ >> MAGIC_NUM_FOR_BIT_SHIFT_1);

    return hash_;
}

uint32_t MyROL (const uint32_t number, const int num_to_rol) {

    return ((number << num_to_rol) | (number >> ((sizeof (uint32_t)) * 8 - num_to_rol)));
}
