#ifndef HASH_FUNC_H
#define HASH_FUNC_H

#include <stdint.h>

#define MURMURHASH

#ifdef MURMURHASH

const uint32_t MAGIC_NUM_1 = 0xcc9e2d51;
const uint32_t MAGIC_NUM_2 = 0x1b873593;
const uint32_t MAGIC_NUM_3 = 0xe6546b64;
const uint32_t MAGIC_NUM_4 = 0x85ebca6b;
const uint32_t MAGIC_NUM_5 = 0xc2b2ae35;
const int      MAGIC_NUM_6 = 5;

const int MAGIC_NUM_FOR_ROL_1 = 15;
const int MAGIC_NUM_FOR_ROL_2 = 13;

const int MAGIC_NUM_FOR_BIT_SHIFT_1 = 16;
const int MAGIC_NUM_FOR_BIT_SHIFT_2 = 13;

#endif

/**
    Murmur_3 function that generates hash.
    @param [in] key_void pointer to element that has to be hashed.
    @param [in] len size of element in bytes.
    @param [in] seed seed to hashing.
    @return hash of the element.
*/
uint32_t MurmurHash3_32 (const void *key_void, const uint32_t len, const uint32_t seed);

/**
    Function that does ROL to number.
    @param [in] number number that has to be rolled.
    @param [in] num_to_rol amount of ROL.
    @return ROLled number.
*/
uint32_t MyROL (const uint32_t number, const int num_to_rol);

#endif
