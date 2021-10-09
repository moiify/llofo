/*
 * adler32.h
 *
 *  Created on: 2016年2月18日
 *      Author: jk
 */

#ifndef USER_INC_ADLER32_H_
#define USER_INC_ADLER32_H_
#include <stdint.h>
/*
 * refer to https://en.wikipedia.org/wiki/Adler-32
 *
 * An Adler-32 checksum is obtained by calculating two 16-bit checksums A and B and concatenating their bits into a 32-bit integer. A is the sum of all bytes in the stream plus one, and B is the sum of the individual values of A from each step.
 *
 * At the beginning of an Adler-32 run, A is initialized to 1, B to 0. The sums are done modulo 65521 (the largest prime number smaller than 216). The bytes are stored in network order (big endian), B occupying the two most significant bytes.
 *
 * The function may be expressed as

        A = 1 + D1 + D2 + ... + Dn (mod 65521)
        B = (1 + D1) + (1 + D1 + D2) + ... + (1 + D1 + D2 + ... + Dn) (mod 65521)
          = n×D1 + (n−1)×D2 + (n−2)×D3 + ... + Dn + n (mod 65521)

         Adler-32(D) = B × 65536 + A
 */

uint32_t adler32(unsigned char *data, size_t len);
uint32_t adler32_con(uint32_t adler32, unsigned char *data, size_t len);


#endif /* USER_INC_ADLER32_H_ */
