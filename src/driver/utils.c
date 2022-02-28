/*
 * utils.c
 *
 *  Created on: 2016年2月25日
 *      Author: jk
 */
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "md5/md5.h"

#include "log.h"
#include "msg.h"
#include "types.h"
#include "utils.h"

int *__errno(void)
{
    return 0;
}

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
const unsigned char* string_trimLeft(const unsigned char* string)
{
    const unsigned char* p = string;

    while(*p == ' ' || *p == '\r' || *p == '\n' || *p == '\t') p++;

    return p;
}

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
void string_trimRight(unsigned char* string)
{
    unsigned char *p = string + strlen((const char *)string) - 1;

    while(*p == ' ' || *p == '\r' || *p == '\n' || *p == '\t')
    {
        *p = 0;
        p--;
    }

    return;
}

/*
 * locates the first occurrence of string s2 in the string
 * and return the next pointer by s2 in s1
 * if not found, the return null
 */
char *string_bypass(const char *s1, const char *s2)
{
    char *p = strstr(s1, s2);
    if(p)
    {
        p += strlen(s2);
    }

    return p;
}

char *string_bypassByNum(const char *s1, const char *s2, unsigned char num)
{
    unsigned char i = 0;
    char *p = (char *)s1;
    for(i = 0; i < num; i++)
    {
        p = string_bypass((const char *)p, s2);
        if(!p)
        {
            return p;
        }
    }

    return p;
}

void string_toUpper(char *buffer, unsigned char len)
{
    unsigned char i = 0;
    for(; i < len; i++)
    {
        buffer[i] = toupper(buffer[i]);
    }
}

void string_toLower(char *buffer, unsigned char len)
{
    unsigned char i = 0;
    for(; i < len; i++)
    {
        buffer[i] = tolower(buffer[i]);
    }
}

char *string_revert(char *str, unsigned char len)
{
    int i=0;
    int n = len;
    char c;
    for(i=0;i<=n/2;i++)
    {
        c=str[i];
        str[i]= str[n-1-i];
        str[n-1-i]=c;
    }
    return str;
    
}

void ascii2unicode(const unsigned char *asciiIn, unsigned short *unicodeOut)
{
    int i = 0;
    unsigned char *outp = (unsigned char *)unicodeOut;
    const unsigned char *inp = asciiIn;

    while(inp[i])
    {
        outp[i * 2] = inp[i];
        outp[i * 2 + 1] = 0x00;
        i++;
    }
}

void unicode2ascii(const unsigned short *unicodeIn, unsigned char *asciiOut)
{
    int i = 0;

    while( unicodeIn[i] )
    {
        asciiOut[i] = unicodeIn[i] & 0xFF;
        i++;
    }

    asciiOut[i] = 0;
}

/************************************************************************
*   功能：将一个十六进制字节串转换成 ASCII 码表示的十六进制的字符串
*   输入参数：pHex    -- 十六进制数字节串首地址
*            pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            nLen    -- 要转换的十六进制数的长度（字节数）
*   输出参数：None
*   注：  转换后的结果全部是大写 ASCII 表示的十六进制数
*   例：{ 0x23, 0x3A, 0x46, 0x4C, 0x52 } => “233A464C52”
************************************************************************/
void Hex2String(unsigned char *pHex, unsigned char *pString, int hexLen)
{
    int i = 0, j = 0;
    unsigned char Nibble[2];

    for (i = 0; i < hexLen; i++)
    {
        Nibble[0] = (pHex[i] & 0xF0) >> 4;
        Nibble[1] = pHex[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] < 10)
            {
                Nibble[j] += 0x30;
            }
            else
            {
                if (Nibble[j] < 16)
                    Nibble[j] = Nibble[j] - 10 + 'A';
            }
            *pString++ = Nibble[j];
        }
    }
}

/****************************************************************************
*   功能：将一个 ASCII 码表示的十六进制字符串转换成十六进制的字节串
*   输入参数：pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            pHex   -- 十六进制数字节串首地址
*            nLen   -- 要转换的 ASCII 码表示的十六进制字符串的长度（字节数）
*   输出参数：None
*   注：  要求输入的 ASCII 码表示的十六进制数的字符个数必须为偶数，除了是1 - 9 和 A(a) - F(f) 以外没有别的字符
*   例： “233A464C52” => { 0x23, 0x3A, 0x46, 0x4C, 0x52 }
****************************************************************************/
void StringToHex(unsigned char *pString, unsigned char *pHex, int stringLen)
{
    int nHexLen = 0;
    int i = 0, j = 0;
    
    if (stringLen % 2)
    {
        return;
    }

    nHexLen = stringLen / 2;
    for (i = 0; i < nHexLen; i++)
    {
        unsigned char Nibble[2];
        Nibble[0] = *pString++;
        Nibble[1] = *pString++;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
                Nibble[j] = Nibble[j] - 'A' + 10;
            else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
                Nibble[j] = Nibble[j] - 'a' + 10;
            else if (Nibble[j] >= '0' && Nibble[j] <= '9')
                Nibble[j] = Nibble[j] - '0';
            else
                return;
        }
        pHex[i] = Nibble[0] << 4;   // Set the high nibble
        pHex[i] |= Nibble[1];   //Set the low nibble
    }
}

int _atoi(const char *string)
{
    int number = 0;
    sscanf(string, "%d%*s", &number);
    return number;
}

const char *_itoa(int number)
{
    static char numString[16] = {0};
    memset(numString, 0, 16);
    snprintf(numString, 15, "%d", number);
    return (const char *)numString;
}

unsigned int htonf(float f)
{
    unsigned int * p_tmpu32 = (unsigned int *)&f;
    return _htonl(*p_tmpu32);
}

float ntohf(unsigned int p)
{
    unsigned int tmpu32 = _ntohl(p);
    float *p_tmpfloat = (float *)&tmpu32;
    return (*p_tmpfloat);
}

/*
 * get the distance between two GPS point
 */
long double getdistance(float lat1, float lng1, float lat2, float lng2)
{
    long double radLat1 = DEG2RAD(lat1);
    long double radLat2 = DEG2RAD(lat2);
    long double a = radLat1 - radLat2;
    long double b = DEG2RAD(lng1) - DEG2RAD(lng2);
    long double s = 0.0;

    s = 2 * asin(sqrt(sin(a/2)*sin(a/2)+cos(radLat1)*cos(radLat2)*sin(b/2)*sin(b/2)));
    s = s * EARTH_RADIUS;

    return s;
}

//输出的是内存大端数据
unsigned int getInetAddr(const unsigned char *sIp)
{
    int i;
    unsigned int lIp = 0;
    for(i = 0; i < 4; i++)
    {
        lIp |= (sIp[i] << (i * 8));
    }
    return lIp;
}

// 字符串对比，大小写不敏感
int string_casecmp(const char *s1,const char *s2)
{
	if (!s1) return (s1==s2)?0:1;if (!s2) return 1;
	for(; tolower(*s1) == tolower(*s2); ++s1, ++s2)	if(*s1 == 0)	return 0;
	return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

void SigAddFloat(char *buff, char *key, double value) 
{
    char tmp[30] = {0};
    sprintf(tmp,"%f",value);
    if(strlen(buff) != 0)
    {
        strcat(buff,"&");
    }
    strcat(buff,key); strcat(buff,"=");strcat(buff,tmp);
}


void SigAddNum(char *buff, char *key, unsigned long long value) 
{
    char tmp[30] = {0};
    sprintf(tmp,"%lld",value);
    if(strlen(buff) != 0)
    {
        strcat(buff,"&");
    }
    strcat(buff,key); strcat(buff,"=");strcat(buff,tmp);
}

void SigAddString(char *buff, char *key, char *value) 
{ 
    if(strlen(value) == 0) return ;
    if(strlen(buff) != 0)
    {
        strcat(buff,"&");
    }
    strcat(buff,key); 
    strcat(buff,"="); 
    strcat(buff,value);
}

unsigned short SigAddEnd(char *buff, char *appSecret) 
{
    strcat(buff, "&appSecret=");
    strcat(buff, appSecret);
    return (strlen(buff)+1);
}

void SigGetSign(char *str, char *out, unsigned long long datalen)
{
    unsigned char decrypt[16];
    MD5_CTX md5;

    MD5Init(&md5); 
    MD5Update(&md5, (unsigned char *)str, datalen);
    MD5Final(&md5, decrypt);        
    
    Hex2String(decrypt, (unsigned char *)out, 16);
    out[32]='\0';  // add str end to md5 string
}


bool getHostfromUrl(const unsigned char *url, unsigned char *host, unsigned char *uri)
{
    if(!url || !host)
    {
        return false;
    }
    unsigned char *p = (unsigned char *)string_bypass((const char *)url, "://");//preamble
    if(!p)
    {
        return false;
    }
    unsigned char *q = (unsigned char *)strchr((const char *)p, '/');//uri
    if(!q)
    {
        sprintf((char *)host, "%s", p);
        sprintf((char *)uri, "%s", "/");
    }
    else
    {
        memcpy(host, p, q - p);
        sprintf((char *)uri, "%s", q);
    }
    return true;
}

/************************************************************************
*   功能：将一个十六进制字节串转换成 ASCII 码表示的十六进制的字符串
*   输入参数：pHex    -- 十六进制数字节串首地址
*            pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            nLen    -- 要转换的十六进制数的长度（字节数）
*   输出参数：None
*   注：  转换后的结果全部是大写 ASCII 表示的十六进制数
*   例：{ 0x23, 0x3A, 0x46, 0x4C, 0x52 } => “233A464C52”
************************************************************************/
void HexToAscii(unsigned char * pHex, unsigned char * pAscii, int nLen)
{
    int i = 0, j = 0;
    unsigned char Nibble[2];

    for (i = 0; i < nLen; i++)
    {
        Nibble[0] = (pHex[i] & 0xF0) >> 4;
        Nibble[1] = pHex[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] < 10)
            {
                Nibble[j] += 0x30;
            }
            else
            {
                if (Nibble[j] < 16)
                    Nibble[j] = Nibble[j] - 10 + 'A';
            }
            *pAscii++ = Nibble[j];
        }
    }
}

/* 在输出中加入空格 如：{ 0x23, 0x3A, 0x46, 0x4C, 0x52 } => “23 3A 46 4C 52” */
void HexToAscii_AddSpace(unsigned char * pHex, unsigned char * pAscii, int nLen)
{
    int i = 0, j = 0;
    unsigned char Nibble[2];

    for (i = 0; i < nLen; i++)
    {
        Nibble[0] = (pHex[i] & 0xF0) >> 4;
        Nibble[1] = pHex[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] < 10)
            {
                Nibble[j] += 0x30;
            }
            else
            {
                if (Nibble[j] < 16)
                    Nibble[j] = Nibble[j] - 10 + 'A';
            }
            *pAscii++ = Nibble[j];
        }
		*pAscii++ = 32;
    }
}

/****************************************************************************
*   功能：将一个 ASCII 码表示的十六进制字符串转换成十六进制的字节串
*   输入参数：pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            pHex   -- 十六进制数字节串首地址
*            nLen   -- 要转换的 ASCII 码表示的十六进制字符串的长度（字节数）
*   输出参数：None
*   注：  要求输入的 ASCII 码表示的十六进制数的字符个数必须为偶数，除了是1 - 9 和 A(a) - F(f) 以外没有别的字符
*   例： “233A464C52” => { 0x23, 0x3A, 0x46, 0x4C, 0x52 }
****************************************************************************/
void AsciiToHex(unsigned char * pAscii, unsigned char * pHex, int nLen)
{
    int nHexLen = 0;
    int i = 0, j = 0;
    
    if (nLen % 2)
    {
        return;
    }

    nHexLen = nLen / 2;
    for (i = 0; i < nHexLen; i++)
    {
        unsigned char Nibble[2];
        Nibble[0] = *pAscii++;
        Nibble[1] = *pAscii++;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
                Nibble[j] = Nibble[j] - 'A' + 10;
            else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
                Nibble[j] = Nibble[j] - 'a' + 10;
            else if (Nibble[j] >= '0' && Nibble[j] <= '9')
                Nibble[j] = Nibble[j] - '0';
            else
                return;
        }
        pHex[i] = Nibble[0] << 4;   // Set the high nibble
        pHex[i] |= Nibble[1];   //Set the low nibble
    }
}

int check_ip(u32 ip0, u32 ip1, u32 ip2, u32 ip3)
{
    if((ip0 < 1) || (ip0 > 223) || (ip0 == 127))
    {
        return -1;
    }
    if((ip1 < 0) || (ip1 > 255))
    {
        return -1;
    }
    if((ip2 < 0) || (ip2 > 255))
    {
        return -1;
    }
    if((ip3 < 0) || (ip3 > 255))
    {
        return -1;
    }
    return 0;
}

int check_port(u32 port)
{
    if((port < 1) || (port > 65535))
    {
        return -1;
    }
    return 0;
}
