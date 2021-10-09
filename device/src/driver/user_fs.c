/*
* user_fs.c
*
*  Created on: 2020.4.3
*      Author: lc
*/
#include "fibo_opencpu.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "types.h"
#include "utils.h"
#include "user_fs.h"

#define MAX_CAT_SIZE   1024

int fs_ls(const unsigned char *cmdString, unsigned short length)
{
    char dir[64] = {0};
    char cmd[64] = {0};
    const unsigned char *directory = (const unsigned char *)string_bypass((const char *)cmdString, "ls");
    directory = string_trimLeft((const unsigned char *)directory);
    string_trimRight((unsigned char*)directory);
    
    strcpy(dir, "/");

    if(0 < strlen((const char *)directory))
    {
        strcat(dir, (const char *)directory);
    }
    snprintf(cmd, 64, "at+fslstfile=\"%s\"\r", dir);
    fibo_at_send((UINT8 *)cmd, strlen(cmd));
    return 0;
}

int fs_rm(const unsigned char *cmdString, unsigned short length)
{
    const char *filename = string_bypass((const char *)cmdString, CMD_STRING_RM);
    
    if(!filename)
    {
        LOG_DEBUG("parameter not correct.\r\n");
        return -1;
    }
    filename = (const char *)string_trimLeft((const unsigned char *)filename);
    string_trimRight((unsigned char*)filename);
    if (strlen((const char *)filename) == 0)
    {
        LOG_DEBUG("parameter not correct.");
        return 0;
    }
    fibo_file_delete((const INT8 *)filename);
    LOG_DEBUG("delete file %s Success", filename);
    return 0;
}

int fs_cat(const unsigned char *cmdString, unsigned short length)
{
    int fd = -1;
    int ret = -1;
    int filesize = -1;
    char buf[MAX_CAT_SIZE] = {0};
    const char* filename = string_bypass((const char *)cmdString, CMD_STRING_CAT);

    if(!filename)
    {
        LOG_DEBUG("parameter not correct.\r\n");
        return -1;
    }
    filename = (const char *)string_trimLeft((const unsigned char *)filename);
    string_trimRight((unsigned char*)filename);

    if(strlen((const char *)filename) == 0)
    {
        LOG_DEBUG("parameter not correct.\r\n");
        return 0;
    }
    
    ret = fibo_file_getSize((const INT8 *)filename);
    if(ret == -1)
    {
        LOG_DEBUG("get file %s size failed.\r\n", filename);
        return -1;
    }   

    fd = fibo_file_open((const INT8 *)filename, FS_O_RDONLY);
    if(fd == -1)
    {
        LOG_DEBUG("open file %s filed.\r\n", filename);
        return -1;
    }

    while(filesize > MAX_CAT_SIZE)
    {
        ret = fibo_file_read(fd, (UINT8 *)buf, MAX_CAT_SIZE);
        if (ret == -1)
        {
            LOG_DEBUG("read file %s failed.\r\n", filename);
            fibo_file_close(fd);
            return -1;
        }
        LOG_DEBUG("%s", buf);
        memset(buf, 0, MAX_CAT_SIZE);
        filesize = filesize - MAX_CAT_SIZE;
    }

    ret = fibo_file_read(fd, (UINT8 *)buf, filesize);
    if (ret == -1)
    {
        LOG_DEBUG("read file %s failed.\r\n", filename);
        fibo_file_close(fd);
        return -1;
    }
    LOG_DEBUG("%s\r\n", buf);
    
    fibo_file_close(fd);
    return 0;
}

int fs_saveFileData(const char *fileName, void *data, int length)
{
    int fd = -1;
    int ret = -1;    

    if(!fileName)
    {
        return -1;
    }
    fileName = (const char *)string_trimLeft((const unsigned char *)fileName);
    string_trimRight((unsigned char *)fileName);

    if(strlen((const char *)fileName) == 0)
    {
        return -1;
    }

    if(!data || length == 0)
    {
        return -1;
    }
    
    fd = fibo_file_open(fileName, FS_O_WRONLY | FS_O_CREAT | FS_O_TRUNC);
    if(fd == -1)
    {
        LOG_ERROR("open file %s filed.", fileName);
        return -1;
    }

    ret = fibo_file_write(fd, data, length);
    if (ret == -1)
    {
        LOG_ERROR("write file %s failed.", fileName);
        fibo_file_close(fd);
        return -1;
    }
    LOG_DEBUG("write file %s success.len: %d", fileName, length);
    
    fibo_file_close(fd);
    return 0;
}

int fs_getFileSize(const char *fileName)
{
    if(!fileName)
    {
        return -1;
    }
    fileName = (const char *)string_trimLeft((const unsigned char *)fileName);
    string_trimRight((unsigned char *)fileName);
    
    int ret = fibo_file_getSize(fileName);
    if(ret == -1)
    {
        LOG_ERROR("get file %s size failed.", fileName);
        return -1;
    }   
    return ret;
}

int fs_getFileData(const char *fileName, void *data, int length)
{
    int ret = 0;
    
    if(!fileName)
    {
        return -1;
    }
    fileName = (const char *)string_trimLeft((const unsigned char *)fileName);
    string_trimRight((unsigned char *)fileName);
    
    if(strlen((const char *)fileName) == 0)
    {
        return -1;
    }

    int filesize = fibo_file_getSize(fileName);
    if(filesize == -1)
    {
        LOG_ERROR("get file %s size failed.", fileName);
        return -1;
    }   

    if(filesize > length || !data)
    {
        LOG_ERROR("file %s is too large filesize = %d inputlen=%d", fileName, filesize, length);
        return -1;
    }

    int fd = fibo_file_open(fileName, FS_O_RDONLY);
    if(fd == -1)
    {
        LOG_ERROR("open file %s filed.", fileName);
        return -1;
    }

    int leftLen = filesize;
    int readLen = 0;
    while(leftLen > MAX_CAT_SIZE)
    {
        ret = fibo_file_read(fd, data + readLen, MAX_CAT_SIZE);
        if (ret == -1)
        {
            LOG_ERROR("read file %s failed.", fileName);
            fibo_file_close(fd);
            return -1;
        }
        leftLen -= ret;
        readLen += ret;
    }

    ret = fibo_file_read(fd, data + readLen, leftLen);
    if (ret == -1)
    {
        LOG_ERROR("read file %s failed.", fileName);
        fibo_file_close(fd);
        return -1;
    }
    
    fibo_file_close(fd);
    return 0;
}

int fs_deleteFile(const char *fileName)
{
    if(!fileName)
    {
        return -1;
    }
    fileName = (const char *)string_trimLeft((const unsigned char *)fileName);
    string_trimRight((unsigned char *)fileName);
    
    int ret = fibo_file_getSize(fileName);
    if(ret == -1)
    {
        LOG_ERROR("get file %s size failed.", fileName);
        return -1;
    }   
    ret = fibo_file_delete(fileName);
    return ret;
}

uint8_t fs_isFileExists(const char *fileName)
{
    if(!fileName)
    {
        return -1;
    }
    fileName = (const char *)string_trimLeft((const unsigned char *)fileName);
    string_trimRight((unsigned char *)fileName);
    
    return fibo_file_exist(fileName) == 1 ? L_TRUE : L_FALSE;
}

