
#ifndef _GETKEY_CLASS_18_19_IR_BLU_H_
#define _GETKEY_CLASS_18_19_IR_BLU_H_




extern void _IR_BLU_DECRYPT_Proess(unsigned char *DATA,unsigned char *DATE_TIME,unsigned char *OUT);
extern void _IR_BLU_CRYPT_Proess(unsigned char *DATA,unsigned char *DATE_TIME,unsigned char *OUT);

//密码返回位置 OUT   xx xx   xx xx    xx xx 
///   OUT[0] OUT[1] 是上一个五分钟  是 十六进制格式 
///   OUT[2] OUT[3] 是当前五分钟    是 十六进制格式 
///   OUT[4] OUT[5] 是下一个五分钟  是 十六进制格式 

//传递参数 Addr 地址 MAC 六个字节 
//         DATE_TIME 当前时间 年月日时分秒 注意   年是 两位  17/12/12  12:12:12   17年12月12日 12点12分12秒
//         OUT 是密码输出

extern void _KEY_CRYPT_Proess(unsigned char *Addr,unsigned char *DATE_TIME,unsigned char *OUT);


//  DATA 第一个是 后台传递进来的 密文 4字节   DATA1 是存储在锁内部的数据 16字节 6字节 MAC
//返回 零 表示合法数据  返回是一 表示的 不合法数据 
extern unsigned char _RegistCode_CMP_Proess(unsigned char *DATA,unsigned char *DATA1,unsigned char *MAC);  //



extern void Get_keyA(unsigned char *UID, unsigned char SecNR, unsigned char Key_mode,unsigned char *key);
extern void Get_key_ALLAB(unsigned char *UID, unsigned char Key_mode,unsigned char *Out);
extern void Get_key_AnySector_ALLAB(unsigned char *UID,unsigned char *Sector, unsigned char *Key_mode1,unsigned char *Out);


//算法选择函数  DECRYPT
extern void DECRYPT_Class1(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class2(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class3(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class4(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class5(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class6(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class7(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class8(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class9(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class10(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class11(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class12(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class13(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class14(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class15(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class16(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class17(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class18(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class19(unsigned char *DATA,unsigned char *UID,unsigned char *OUT);
extern void DECRYPT_Class20(unsigned char *DATA,unsigned char *UID,unsigned char *OUT); //19号函数




#endif //#ifndef _GETKEY_CLASS_18_19_IR_BLU_H_


