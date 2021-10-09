/**
 * Copyright (c) 2018 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stdio.h>
#include <stdint.h>

#include "rtc.h"
#include "uuid4.h"

static uint64_t seed[2];

static uint64_t xorshift128plus(uint64_t *s)
{
    /* http://xorshift.di.unimi.it/xorshift128plus.c */
    uint64_t s1 = s[0];
    const uint64_t s0 = s[1];
    s[0] = s0;
    s1 ^= s1 << 23;
    s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
    return s[1] + s0;
}

int uuid4_init(void)
{
    int i = 0;
    uint64_t temp = 0;
    uint8_t imei[32] = {0};  
    uint64_t timestamp = (uint64_t)rtc_getTimestamp();
    
    if(timestamp < 1546272000) //2019-01-01 00:00:00
    {
        return UUID4_EFAILURE;
    }
    
    //eat_get_imei(imei, 31);
    
    for(i = 3; i < 11; i++){
        temp = imei[i];
        seed[0] |= temp << (64 - ((i - 2) * 8 ));
    }
    
    for(i = 11; i < 15; i++){
        temp = imei[i];
        seed[1] |= temp << (64 - ((i - 10) * 8 ));
    }
    
    seed[1] |= timestamp;

    return UUID4_ESUCCESS;
}

int  uuid4_generate(char *dst)
{
    static const char *template = "xxxxxxxxxxxx4xxxyxxxxxxxxxxxxxxx";
    static const char *chars = "0123456789abcdef";
    union { unsigned char b[16]; uint64_t word[2]; } s;
    const char *p;
    int i, n;
    if(seed[0] == 0 && seed[1] == 0){
        return UUID4_EFAILURE;
    }
    /* get random */
    s.word[0] = xorshift128plus(seed);
    s.word[1] = xorshift128plus(seed);
    /* build string */
    p = template;
    i = 0;
    while (*p) {
        n = s.b[i >> 1];
        n = (i & 1) ? (n >> 4) : (n & 0xf);
        switch (*p) {
        case 'x'  : *dst = chars[n];              i++;  break;
        case 'y'  : *dst = chars[(n & 0x3) + 8];  i++;  break;
        default   : *dst = *p;
        }
        dst++, p++;
    }
    *dst = '\0';
    return UUID4_ESUCCESS;
}

