
#ifndef _GETKEY_CLASS_18_19_IR_BLU_H_
#define _GETKEY_CLASS_18_19_IR_BLU_H_




extern void _IR_BLU_DECRYPT_Proess(unsigned char *DATA,unsigned char *DATE_TIME,unsigned char *OUT);
extern void _IR_BLU_CRYPT_Proess(unsigned char *DATA,unsigned char *DATE_TIME,unsigned char *OUT);

//���뷵��λ�� OUT   xx xx   xx xx    xx xx 
///   OUT[0] OUT[1] ����һ�������  �� ʮ�����Ƹ�ʽ 
///   OUT[2] OUT[3] �ǵ�ǰ�����    �� ʮ�����Ƹ�ʽ 
///   OUT[4] OUT[5] ����һ�������  �� ʮ�����Ƹ�ʽ 

//���ݲ��� Addr ��ַ MAC �����ֽ� 
//         DATE_TIME ��ǰʱ�� ������ʱ���� ע��   ���� ��λ  17/12/12  12:12:12   17��12��12�� 12��12��12��
//         OUT ���������

extern void _KEY_CRYPT_Proess(unsigned char *Addr,unsigned char *DATE_TIME,unsigned char *OUT);


//  DATA ��һ���� ��̨���ݽ����� ���� 4�ֽ�   DATA1 �Ǵ洢�����ڲ������� 16�ֽ� 6�ֽ� MAC
//���� �� ��ʾ�Ϸ�����  ������һ ��ʾ�� ���Ϸ����� 
extern unsigned char _RegistCode_CMP_Proess(unsigned char *DATA,unsigned char *DATA1,unsigned char *MAC);  //



extern void Get_keyA(unsigned char *UID, unsigned char SecNR, unsigned char Key_mode,unsigned char *key);
extern void Get_key_ALLAB(unsigned char *UID, unsigned char Key_mode,unsigned char *Out);
extern void Get_key_AnySector_ALLAB(unsigned char *UID,unsigned char *Sector, unsigned char *Key_mode1,unsigned char *Out);


//�㷨ѡ����  DECRYPT
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
extern void DECRYPT_Class20(unsigned char *DATA,unsigned char *UID,unsigned char *OUT); //19�ź���




#endif //#ifndef _GETKEY_CLASS_18_19_IR_BLU_H_


