/*
 * socket.h
 *
 *  Created on: 2020.04.07
 *      Author: lc
 */
#ifndef __USER_SOCKET_H__
#define __USER_SOCKET_H__

#include "fibo_opencpu.h"

typedef enum
{
    SOCKET_WAIT_REGISTER=0,
    SOCKET_WAIT_PDPACTIVE,
    SOCKET_WAIT_IPADDR,
    SOCKET_WAIT_SOCKET,
    SOCKET_WAIT_SUBSCRIBE1,
    SOCKET_WAIT_SUBSCRIBE2,
    SOCKET_WAIT_LOGIN,
    SOCKET_RUNING,
    SOCKET_MAX
}SocketState_enum;

typedef enum
{
    SOCKET_TYPE_TCP=0,
    SOCKET_TYPE_UDP,
    SOCKET_TYPE_MAX
}SocketType_enum;

enum
{
    REG_STATE_NOT_REGISTERED=0,
    REG_STATE_REGISTERED,
    REG_STATE_SEARCHING,
    REG_STATE_REG_DENIED,
    REG_STATE_UNKNOWN,
    REG_STATE_REGISTERED_ROAMING
};

typedef int SOCKET_ACTION(void);
typedef int SOCKET_RECV_ACTION(const void *m, int msgLen);
typedef int SOCKET_MQTTRECV_ACTION(uint8_t *topic, uint8_t qos, void *payload, uint16_t payloadLen);

typedef struct
{
    int16_t port;
    uint8_t domain[64];
    uint8_t ip_addr[4];
    
    uint8_t *pIsLogined;
    SOCKET_ACTION *pLoginAction;
    SOCKET_ACTION *pRuningAction;
    SOCKET_RECV_ACTION *pRecvAction;
}Socket_st;

typedef struct
{
    int16_t port;
    uint8_t domain[64];

    int8_t  user[64];
    int8_t  passwd[64];
    int8_t  client[64];    
    uint8_t topic[2][64];
    
    SOCKET_ACTION *pMqttRuningAction;
    SOCKET_MQTTRECV_ACTION *pMqttRecvAction;
}Mqtt_st;

bool socket_isRegNet(void);

bool socket_isLogined(void);

bool socket_isPDPActived(void);

void socket_sig_callback(GAPP_SIGNAL_ID_T sig, va_list arg);

int socket_close(void);

void socket_initial(void);

int socket_sendData(void *data, int32_t len);

int32_t socket_sendDataDirectly(void *data, int32_t len);
int32_t socket_sendDatawithUDP(void *data, int32_t len);

int socket_run(void);

void socket_ConnectThread(void *argument);

int32_t socket_select(void);

#endif /* __USER_SOCKET_H__ */
