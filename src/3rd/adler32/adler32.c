/*
 * adler32.c
 *
 *  Created on: 2016年2月18日
 *      Author: jk
 *
 *  Here we have two options for the checksum algorithm:
 *      https://en.wikipedia.org/wiki/Adler-32
 *      https://en.wikipedia.org/wiki/Fletcher%27s_checksum
 *
 *  currently we use the first one
 */

#include <stdlib.h>
#include <stdint.h>

const int MOD_ADLER = 65521;

const uint32_t ADLER_DEFAULT_A = 1;
const uint32_t ADLER_DEFAULT_B = 0;

//const uint32_t ADLER_DEFAULT = ADLER_DEFAULT_B << 16 | ADLER_DEFAULT_A;

/*
 * data is the location of the data in physical memory
 * len is the length of the data in bytes
 */
uint32_t adler32(unsigned char *data, size_t len)
{
    uint32_t a = ADLER_DEFAULT_A;
    uint32_t b = ADLER_DEFAULT_B;
    size_t index;

    /* Process each byte of the data in order */
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}

uint32_t adler32_con(uint32_t adler32, unsigned char *data, size_t len)
{
    uint32_t a = adler32 & 0xffff;
    uint32_t b = (adler32 & 0xffff0000) >> 16;

    size_t index;

    /* Process each byte of the data in order */
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}
