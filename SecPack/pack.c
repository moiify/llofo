/*
firmware_L610
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGNATURE_LEN         10
#define MAX_PLATFORM_LEN      16
#define MAX_APP_VERSION_LEN   16
#define MAX_CORE_VERSION_LEN  64
#define MAX_FILE_NAME_LEN     128
#define GET_APPVERSION_OFFSET 17

static const unsigned short crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

unsigned short crc16_ccitt(const char *buf, int len)
{
	register int counter;
	register unsigned short crc = 0;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[( (crc>>8) ^ (*(buf++)) )&0x00FF];
	return crc;
}

char* memstr(char* full_data, int full_data_len, char* str)
{
    int str_len = strlen(str);
    int i;
    char* cur = full_data;

    if (full_data == NULL || full_data_len <= 0 || str == NULL)
    {
        return NULL;
    }
    if (*str == '\0')
    {
        return NULL;
    }

    int last_cur = full_data_len - str_len + 1;

    for (i = 0; i < last_cur; i++)
    {
        if (*cur == *str)
        {
            if (memcmp(cur, str, str_len) == 0)
            {
                return cur;
            }
        }
        cur++;
    }
    return NULL;
}

void main(int argc,char** argv)
{
  char signature[SIGNATURE_LEN] = "xiaoantech";
  char PlatForm[MAX_PLATFORM_LEN] =              {0};
  char appversion[MAX_APP_VERSION_LEN] =         {0};
  char coreversion[MAX_CORE_VERSION_LEN] =       {0};
  char filename[MAX_FILE_NAME_LEN] =             {0};
  char binname[MAX_FILE_NAME_LEN] =              {0};
  char packname[MAX_FILE_NAME_LEN] =             {0};

  int i;
  int crc=0;
  int packfilesize = 0;
  int filesize = 0;
  int offset_len = 0;
  int appversion_len=0;
  char *pack_file = NULL;
  char *temp_appversion = NULL;
  char *temp = NULL;
  FILE *fp = NULL;

  strcpy(filename,argv[1]);
  strcpy(PlatForm,argv[2]);
  strcpy(coreversion,argv[3]);

  if(NULL == (fp = fopen(filename,"rb+")))
  {
      printf("%s open error \n",filename);
      return;
  }
  fseek(fp, 0,SEEK_END);//移到末尾读取文件长度
  filesize=ftell(fp);
  fseek(fp, 0,SEEK_SET);//
  temp=(char *)malloc(filesize * sizeof(char));
  memset(temp, 0, filesize * sizeof(char));
  fread(temp,1,filesize,fp);//拷贝所有固件包中的原始数据
  fclose(fp);

  temp_appversion = memstr(temp, filesize, "firmware version");
  if(NULL == temp_appversion)
  {
    printf("can not get version\n");
    free(temp);
    return;
  }
  temp_appversion -= GET_APPVERSION_OFFSET + MAX_APP_VERSION_LEN;
  for(i=0; i<(MAX_APP_VERSION_LEN + GET_APPVERSION_OFFSET); i++)
  {
    if(('0' <= (char)temp_appversion[i]) && ('9' >= (char)temp_appversion[i]))
    {
      appversion_len++;
    }
    else if('.' == (char)temp_appversion[i] && appversion_len)
    {
      appversion_len++;
    }
    else if(0 == appversion_len)
    {
      offset_len++;
    }
    else if(appversion_len && '\0' == (char)temp_appversion[i])
    {
      break;
    }
  }
  memcpy(appversion, temp_appversion + offset_len, appversion_len);

  crc = crc16_ccitt((const char *)temp, filesize);
  sprintf(binname, "./hex/app_%s_%d.bin", appversion, crc);
  if(NULL == (fp = fopen(binname,"wb"))) //新建.bin
  {
      printf("%s open error \n", binname);
      free(temp);
      return;
  }
  fwrite(temp, filesize, 1, fp);
  fclose(fp);
  printf("FILE %s saved ok.\n", binname);

  //打包数据并计算crc
  packfilesize = sizeof(signature) + sizeof(PlatForm) + sizeof(appversion) + sizeof(coreversion) + filesize;
  pack_file = (char *)malloc(packfilesize * sizeof(char));
  memset(pack_file, 0, packfilesize);
  memcpy(pack_file, signature, sizeof(signature));
  memcpy(pack_file + sizeof(signature), PlatForm, sizeof(PlatForm));
  memcpy(pack_file + sizeof(signature) + sizeof(PlatForm), appversion, sizeof(appversion));
  memcpy(pack_file + sizeof(signature) + sizeof(PlatForm) + sizeof(appversion), coreversion, sizeof(coreversion));
  memcpy(pack_file + sizeof(signature) + sizeof(PlatForm) + sizeof(appversion) + sizeof(coreversion), temp, filesize);
  crc = crc16_ccitt((const char *)pack_file, packfilesize);
  sprintf(packname, "./hex/app_%s_%d.pack", appversion, crc);

  if(NULL == (fp = fopen(packname,"wb"))) //新建.pack
  {
      printf("%s open error \n", packname);
      free(temp);
      return;
  }
  fwrite(pack_file, packfilesize, 1, fp);
  fclose(fp);
  free(temp);
  printf("FILE %s saved ok.\n", packname);
}
