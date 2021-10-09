/*
 * utils.h
 *
 *  Created on: 2020.4.3
 *      Author: lc
 */

#ifndef __USER_UTILS_H__
#define __USER_UTILS_H__

#include <stdbool.h>
#include "types.h"

#define KMPH2MPS(x) (((float)(x))/3.6f)
#define MPS2KMPH(x) (((float)(x))*3.6f)

#define PI 3.141592653
#define EARTH_RADIUS 6378137 //radius of our earth unit :  m
#define DEG2RAD(d) (d * PI / 180.f)//degree to radian

//#ifndef MAX
//#define MAX(a,b) ((a)>(b) ? (a):(b))
//#endif

#ifndef MIN
#define MIN(a,b) ((a)>(b) ? (b):(a))
#endif

/*
 * function: 去掉字符串开头的空白符
 * params:
 *  string: 需要去掉字符串开头的空白符的字符串地址
 * return:
 *  去掉字符串开头的空白符后的字符串地址
 *
 * note:
 *  这个函数没做保护
 */
const unsigned char *string_trimLeft(const unsigned char *string);

/*
 * function: 去掉字符串末尾的空白符
 * params:
 *  string: 需要去掉字符串末尾的空白符的字符串地址
 * return:
 *  no return
 *
 * note:
 *  这个函数没做保护
 */
void string_trimRight(unsigned char *string);

/*
 * function: 查找并跳过子串
 * params:
 *  str1: 主串
 *  str2: 子串
 * return:
 *  跳过子串后的地址, 如果没有子串, 返回NULL
 */
char *string_bypass(const char *str1, const char *str2);

/*
 * function: 连续查找并跳过子串
 * params:
 *  str1: 主串
 *  str2: 子串
 * return:
 *  连续跳过子串厚的地址, 如果没有子串, 返回NULL
 */
char *string_bypassByNum(const char *s1, const char *s2, unsigned char num);


void string_toUpper(char *buffer, unsigned char len);

void string_toLower(char *buffer, unsigned char len);


int _atoi(const char *string);
const char *_itoa(int number);


unsigned int htonf(float f);

float ntohf(unsigned int p);


void ascii2unicode(const unsigned char *asciiIn, unsigned short *unicodeOut);

void unicode2ascii(const unsigned short *unicodeIn, unsigned char *asciiOut);

/************************************************************************
*   功能：将一个十六进制字节串转换成 ASCII 码表示的十六进制的字符串
*   输入参数：pHex    -- 十六进制数字节串首地址
*            pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            nLen    -- 要转换的十六进制数的长度（字节数）
*   输出参数：None
*   注：  转换后的结果全部是大写 ASCII 表示的十六进制数
*   例：{ 0x23, 0x3A, 0x46, 0x4C, 0x52 } => “233A464C52”
************************************************************************/
void Hex2String(unsigned char *pHex, unsigned char *pString, int hexLen);


/****************************************************************************
*   功能：将一个 ASCII 码表示的十六进制字符串转换成十六进制的字节串
*   输入参数：pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            pHex   -- 十六进制数字节串首地址
*            nLen   -- 要转换的 ASCII 码表示的十六进制字符串的长度（字节数）
*   输出参数：None
*   注：  要求输入的 ASCII 码表示的十六进制数的字符个数必须为偶数，除了是1 - 9 和 A(a) - F(f) 以外没有别的字符
*   例： “233A464C52” => { 0x23, 0x3A, 0x46, 0x4C, 0x52 }
****************************************************************************/
void StringToHex(unsigned char *pString, unsigned char *pHex, int stringLen);

long double getdistance(float lat1, float lng1, float lat2, float lng2);

unsigned int getInetAddr(const unsigned char *sIp);

bool getHostfromUrl(const unsigned char *url, unsigned char *host, unsigned char *uri);

int *__errno(void);

void HexToAscii(unsigned char * pHex, unsigned char * pAscii, int nLen);
void HexToAscii_AddSpace(unsigned char * pHex, unsigned char * pAscii, int nLen);

void AsciiToHex(unsigned char * pAscii, unsigned char * pHex, int nLen);

int check_ip(u32 ip0, u32 ip1, u32 ip2, u32 ip3);
int check_port(u32 port);

#endif /* __USER_UTILS_H__ */
