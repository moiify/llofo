/*
 * msg.h
 *
 *  Created on: 2015��7��8��
 *      Author: jk
 */

#ifndef USER_ELECTROMBILE_MSG_H_
#define USER_ELECTROMBILE_MSG_H_


#include <stdio.h>
#include "fibo_opencpu.h"
#include "protocol.h"

#define _htonl(l) ((((l >> 24) & 0x000000ff)) | \
                  (((l >>  8) & 0x0000ff00)) | \
                  (((l) & 0x0000ff00) <<  8) | \
                  (((l) & 0x000000ff) << 24))
#define _ntohl(l) _htonl(l)

#define _htons(s) ((((s) >> 8) & 0xff) | \
                  (((s) << 8) & 0xff00))
#define _ntohs(s) _htons(s)

#define Malloc myTestMalloc
int32_t Free(void *buffer);


void* alloc_msg(char cmd, size_t length) __attribute__((malloc));
void* alloc_device_msg(const MSG_HEADER* pMsg, size_t length);

void free_msg(void* msg);
void * myTestMalloc(unsigned int size);

#endif /* USER_ELECTROMBILE_MSG_H_ */

