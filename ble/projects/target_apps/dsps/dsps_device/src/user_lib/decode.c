/*******************************************************************************
 *	文件名称：decode.c
 *
 *	功能描述：解密处理文件
 *
 *	编写日期：18.01.29
 *
 *	修改日期：
 *
 *	备	  注：
 *******************************************************************************/
#include "decode.h"
 
#include "time.h"																//ARMCC编译器自带头文件

#include "GetKey_Class18_19_IR_BLU.h"

		uint8_t             			Device_Customer_ID[2];  				//设备客户编号：生产时，通过串口命令写入设备
		
		uint8_t             			Device_Serial[16];  					//设备序列号：生产时，通过串口命令写入设备
		
		uint8_t             			Device_Mac[6];  						//设备蓝牙MAC
		
		uint8_t							_IR_BUL_CMD_Sec[4] = {0, 0, 0, 0};  	//上次开锁时间因子
		
//------------------------------------------------------------------------------
// 解密处理函数
//------------------------------------------------------------------------------
uint8_t	decode_process(uint8_t* p_data, uint8_t length)							//解密处理函数
{
    unsigned int BLUTime, BLUTimeBAK;
    unsigned char Out__[16];
	unsigned char Status = 1;
	
    _IR_BLU_DECRYPT_Proess(&p_data[p_data[3] - 12], &p_data[0], Out__);			//16字节密文+帧数据=>16字节译文

    BLUTime = Out__[8];
    BLUTime = BLUTime * 256 + Out__[9];
    BLUTime = BLUTime * 256 + Out__[10];
    BLUTime = BLUTime * 256 + Out__[11];										//(Out__[8]<<24)+(Out__[9]<<16)+(Out__[10]<<8)+(Out__[11])
	
    BLUTimeBAK = _IR_BUL_CMD_Sec[0];
    BLUTimeBAK = BLUTimeBAK * 256 + _IR_BUL_CMD_Sec[1];
    BLUTimeBAK = BLUTimeBAK * 256 + _IR_BUL_CMD_Sec[2];
    BLUTimeBAK = BLUTimeBAK * 256 + _IR_BUL_CMD_Sec[3];
	
	Status = _RegistCode_CMP_Proess(&Out__[3], Device_Serial, Device_Mac);		//Out__[3]~Out__[6]->密文种子
	
	if((Status==0)&&(memcmp(&Out__, &Device_Mac[3], 3)==0))						//Out__[0]~Out__[2]->蓝牙MAC后3字节
    {
        if(BLUTime > BLUTimeBAK)
        {
            _IR_BUL_CMD_Sec[0] = Out__[8];
            _IR_BUL_CMD_Sec[1] = Out__[9];
            _IR_BUL_CMD_Sec[2] = Out__[10];
            _IR_BUL_CMD_Sec[3] = Out__[11];
			
            return 1;															//密文有效
        }
        else
        {
            return 2;															//密文无效：时间不对
        }
    }
    else
    {
		return 0;																//密文不合法
    }
}
