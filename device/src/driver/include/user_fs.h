/*
 * user_fs.h
 *
 *  Created on: 2020.4.3
 *      Author: lc
 */

#ifndef __USER_INC_FS_H__
#define __USER_INC_FS_H__

#define MAX_FILENAME_LEN 64

#define CMD_STRING_LS       "ls"
#define CMD_STRING_RM       "rm"
#define CMD_STRING_CAT      "cat"

#define FILE_FENCE_CONF   "fence.conf"
#define FILE_SERVER_CONF  "server.conf"
#define FILE_SETTING_CONF "setting.conf"
#define FILE_DEFAULT_CONF "default.conf"
#define FILE_STATUS_CONF  "status.conf"

#define FILE_AUDIO_DIR    "/FFS/"

#define UPGRADE_ETC_FILE_NAME          "ETC_OTA.bin"
#define UPGRADE_BMS_FILE_NAME          "BMS_OTA.bin"


int fs_ls(const unsigned char* cmdString, unsigned short length);
int fs_rm(const unsigned char* cmdString, unsigned short length);
int fs_cat(const unsigned char* cmdString, unsigned short length);

int fs_deleteFile(const char *fileName);
int fs_getFileSize(const char *fileName);
uint8_t fs_isFileExists(const char *fileName);
int fs_getFileData(const char *fileName, void *data, int length);
int fs_saveFileData(const char *fileName, void *data, int length);

#endif /* __USER_INC_FS_H__ */

