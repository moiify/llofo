/*
 * http.h
 *
 *  Created on: 2017/03/24
 *      Author: lc
 */
#ifndef __USER_HTTP_H__
#define __USER_HTTP_H__

#include "types.h"
#include "fibo_opencpu.h"

typedef void (*http_callback_proc)(int result, uint8_t *data, int data_len);

int http_get(uint8_t *url, http_callback_proc cb);
int http_post(uint8_t *url, uint8_t *postData, uint16_t postDatalen, http_callback_proc cb);
uint8_t *http_get_data(void);
int http_get_datalen(void);
L_BOOL http_isProcing(void);

#define MAX_HTTPCMD_LEN (256)
#define MAX_HTTPURL_LEN (256)
#define MAX_HTTPGET_HEAD_LEN (512)
#define MAX_HTTP_FILENAME_LEN (36)

#endif/*__USER_HTTP_H__*/

