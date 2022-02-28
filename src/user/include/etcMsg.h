/*
 * etcMsg_etc.h
 *
 *  Created on: 2018/06/03
 *      Author: lc
 */
#ifndef __USER_ETCMSG_H__
#define __USER_ETCMSG_H__
#include "async.h"

#pragma pack(push, 1)

#pragma pack(pop)

/*
 * ETC OTA global parameters   Only Extern Use in ETC_XiaoAn.c
 */
extern u8 *g_etcFirmwareData;
extern u8 *g_etcFirmwareDataP;
extern u16 g_etcPackID;
extern u16 g_etcSendCompleteFlag;
extern u16 g_etcResendLenBak;
extern u32 g_etcFirmwareDataBytes;
extern u16 g_etcSendDataLenPerTime; 
extern u16 g_etcRetransferCnt; 
extern u16 g_etcReupgradeCnt;
extern u16 g_etcResendCommpleteDataCnt;

/*
 * BMS OTA global parameters   Only Extern Use in ETC_XiaoAn.c
 */
extern u8 *g_bmsFirmwareData;
extern u8 *g_bmsFirmwareDataP;
extern u16 g_bmsPackID;
extern u16 g_bmsSendCompleteFlag;
extern u16 g_bmsResendLenBak;
extern u32 g_bmsFirmwareDataBytes;
extern u16 g_bmsSendDataLenPerTime;
extern u16 g_bmsRetransferCnt;
extern u16 g_bmsReupgradeCnt;
extern u16 g_bmsResendCompleteDataCnt;

//控制器通信框架相关
ASYNC_PROC_MAP *etcMsg_getAsyncProcs(void);
int etcMsg_getAsyncProcsSize(void);
void etcMsg_etcInitial(void);
void etcMsg_setAsyncHandler(u8 address, u8 cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction, u8 isWaitRsp);
void etcMsg_setETCHandler(uint8_t address, uint8_t cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction);
void etcMsg_setETCHandlerOnce(uint8_t address, uint8_t cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction);
void etcMsg_setETCHandlerErrState(uint8_t address, uint8_t cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction);
int  etcMsg_MsgProc(uint8_t* data, uint16_t dataLen);

//控制器通信功能相关
void etcMsg_getETCInfo(void);
void etcMsg_setETCLight(u8 state);
void etcMsg_setETCAccOn(void);
void etcMsg_setETCDefend(u8 isDefend);

void etcMsg_SendEtcStartPAC(void);
int  etcMsg_SendEtcOTARealData(void);
int  etcMsg_SendEtcOTAComplete(void);
void etcMsg_ETCOTA_Failed(void);

void etcMsg_SendBmsStartPAC(void);
int  etcMsg_SendBmsRealData(void);
int  etcMsg_SendBmsOTAComplete(void);
void etcMsg_BMSOTA_Failed(void);
float etcMsg_hall2Speed(u32 pulse);

#endif/*__USER_ETCMSG_H__*/

