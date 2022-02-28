/*
 * client.h
 *
 *  Created on: 2015/7/9
 *      Author: jk
 */

#ifndef USER_ELECTROMBILE_CLIENT_H_
#define USER_ELECTROMBILE_CLIENT_H_

typedef int (*MSG_PROC)(const void* msg);
typedef struct
{
    char cmd;
    MSG_PROC pfn;
}MC_MSG_PROC;


/*
 * function: TCP数据处理
 */
int client_proc(const void* m, int msgLen);

/*
 * function: UDP数据处理
 */
int client_udp_proc(const void *m, int msgLen);

/*
 * function: 初始化TCP接收数据处理
 *  params:
 *      responseArray: 接受处理数组
 *      responseArraySize: 接受处理数组元素个数
 */
void client_initail(void *responseArray, int responseArraySize);

/*
 * function: 初始化TCP接收数据处理 其他协议
 *  params:
 *      procHandler: 其他协议处理函数
 */
typedef int (*CLIENT_PROC)(const void *m, int msgLen);
void client_initailEXT(CLIENT_PROC procHandler);


/*
 * function: 初始化UDP接收数据处理
 *  params:
 *      responseArray: 接受处理数组
 *      responseArraySize: 接受处理数组元素个数
 */
void client_initailUDP(void *responseArray, int responseArraySize);


#endif /* USER_ELECTROMBILE_CLIENT_H_ */
