/**
 * Copyright (C) 1996 Bob Jenkins (bob_jenkins@burtleburtle.net)
 */
/**
 * jhash.h: Jenkins hash support.
 *
 * http://burtleburtle.net/bob/hash/
 *
 * These are the credits from Bob's sources:
 *
 * lookup2.c, by Bob Jenkins, December 1996, Public Domain.
 * hash(), hash2(), hash3, and mix() are externally useful functions.
 * Routines to test the hash are included if SELF_TEST is defined.
 * You can use this free for any purpose.  It has no warranty.
 *
 * Copyright (C) 2003 David S. Miller (davem@redhat.com)
 *
 * I've modified Bob's hash to be useful in the Linux kernel, and
 * any bugs present are surely my fault.  -DaveM
 */

#ifndef _JHASH_H_
#define _JHASH_H_

#include "cds_def.h"

/* NOTE: Arguments are modified. */
#define __jhash_mix(a, b, c) do {   \
    a -= b; a -= c; a ^= (c>>13);   \
    b -= c; b -= a; b ^= (a<<8);    \
    c -= a; c -= b; c ^= (b>>13);   \
    a -= b; a -= c; a ^= (c>>12);   \
    b -= c; b -= a; b ^= (a<<16);   \
    c -= a; c -= b; c ^= (b>>5);    \
    a -= b; a -= c; a ^= (c>>3);    \
    b -= c; b -= a; b ^= (a<<10);   \
    c -= a; c -= b; c ^= (b>>15);   \
} while (0)

/* The golden ration: an arbitrary value */
#define JHASH_GOLDEN_RATIO  0x9e3779b9

/**
 * The most generic version, hashes an arbitrary sequence
 * of bytes.  No alignment or length assumptions are made about
 * the input key.
 */
static inline uint32_t jhash (const void *key, uint32_t length,  uint32_t initval) {
    uint32_t        a, 
                    b, 
                    c, 
                    len;
    const uint8_t   *k;

    k   = (const uint8_t *)key;
    a   = JHASH_GOLDEN_RATIO;
    b   = JHASH_GOLDEN_RATIO;
    c   = initval;
    len = length;

    while (len >= 12) {
        a += (k[0] + ((uint32_t)k[1] << 8) + ((uint32_t)k[2] << 16) + ((uint32_t)k[3] << 24));
        b += (k[4] + ((uint32_t)k[5] << 8) + ((uint32_t)k[6] << 16) + ((uint32_t)k[7] << 24));
        c += (k[8] + ((uint32_t)k[9] << 8) + ((uint32_t)k[10] << 16) + ((uint32_t)k[11] << 24));

        __jhash_mix(a, b, c);

        k += 12;
        len -= 12;
    }

    c += length;
    switch (len) {
    case 11: c += ((uint32_t)k[10] << 24);
        __attribute__((fallthrough));
    case 10: c += ((uint32_t)k[9] << 16);
        __attribute__((fallthrough));
    case 9 : c += ((uint32_t)k[8] << 8);
        __attribute__((fallthrough));
    case 8 : b += ((uint32_t)k[7] << 24);
        __attribute__((fallthrough));
    case 7 : b += ((uint32_t)k[6] << 16);
        __attribute__((fallthrough));
    case 6 : b += ((uint32_t)k[5] << 8);
        __attribute__((fallthrough));
    case 5 : b += k[4];
        __attribute__((fallthrough));
    case 4 : a += ((uint32_t)k[3] << 24);
        __attribute__((fallthrough));
    case 3 : a += ((uint32_t)k[2] << 16);
        __attribute__((fallthrough));
    case 2 : a += ((uint32_t)k[1] << 8);
        __attribute__((fallthrough));
    case 1 : a += k[0];
        __attribute__((fallthrough));
    };

    __jhash_mix(a,b,c);

    return c;
} /* jhash */

/**
 * A special optimized version that handles 1 or more of u32s.
 * The length parameter here is the number of u32s in the key.
 */
static inline uint32_t jhash2 (uint32_t *k, uint32_t length, uint32_t initval) {
    uint32_t    a, 
                b, 
                c, 
                len;

    a   = JHASH_GOLDEN_RATIO;
    b   = JHASH_GOLDEN_RATIO;
    c   = initval;
    len = length;

    while (len >= 3) {
        a += k[0];
        b += k[1];
        c += k[2];
        __jhash_mix(a, b, c);
        k   += 3;
        len -= 3;
    }

    c += length * 4;

    switch (len) {
    case 2 : b += k[1];
    case 1 : a += k[0];
    };

    __jhash_mix(a,b,c);

    return c;
} /* jhash2 */

/**
 * A special ultra-optimized versions that knows they are hashing exactly
 * 3, 2 or 1 word(s).
 *
 * NOTE: In partilar the "c += length; __jhash_mix(a,b,c);" normally
 *       done at the end is not done here.
 */
static inline uint32_t jhash_3words (uint32_t a, uint32_t b, uint32_t c, uint32_t initval) {
    a += JHASH_GOLDEN_RATIO;
    b += JHASH_GOLDEN_RATIO;
    c += initval;

    __jhash_mix(a, b, c);

    return c;
} /* jhash_3words */

static inline uint32_t jhash_2words (uint32_t a, uint32_t b, uint32_t initval) {
    return jhash_3words(a, b, 0, initval);
} /* jhash_2words */

static inline uint32_t jhash_1word (uint32_t a, uint32_t initval) {
    return jhash_3words(a, 0, 0, initval);
} /* jhash_1word */

#endif /* _JHASH_H_ */
