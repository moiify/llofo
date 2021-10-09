/*
 * tlv.h
 *
 *  Created on: 2019/4/16
 *      Author: lc
 */
#ifndef __TLV_H__
#define __TLV_H__
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct
{
    unsigned char  signature;  //0xAA
    unsigned short payloadLen;
    unsigned char  payload[];  //TLV data
}__attribute__((__packed__))TLV_DATA_HEADER;
typedef struct
{
    unsigned char type;        //type
    unsigned char len;         //value len
    unsigned char value[];     //value
}__attribute__((__packed__))TLV_DATA;
#pragma pack(pop)

/*
* func: create a tlv header, call tlv_deleteHeader when use finished.
* return:
*    NULL when failed
*    OTHERS when success.
*/
TLV_DATA_HEADER *tlv_createHeader(void);

/*
* func: add a buffer to tlv struct data
*/
bool tlv_addData(TLV_DATA_HEADER **ppTlvData, unsigned char type, void *data, unsigned char len);

/*
* func: release a tlv header
*/
void tlv_deleteHeader(TLV_DATA_HEADER *pTlvData);

/*
* func: check the tlv header is pass
*/
bool tlv_isHeaderCheckPass(const TLV_DATA_HEADER *pTlvData);

#endif //__TLV_H__

