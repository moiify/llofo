#include "ke_mem.h"
#include "ke_task.h"
#include "app_task.h"

#include "setting.h"
#include "ble_proc.h"
#include "ble_adv_proc.h"

void ble_adv_set_name(const uint8_t *name,uint8_t len)
{
    setting.adv.nameLen = MIN(len, MAX_BLE_ADV_NAME_LEN);
    memcpy(setting.adv.name, name, setting.adv.nameLen);  
}

void ble_adv_set_manufData(const uint8_t *manufData,uint8_t len)
{
    setting.adv.meanufDataLen = MIN(len, MAX_BLE_ADV_MEANUFDATA_LEN);
    memcpy(setting.adv.meanufData, manufData, setting.adv.meanufDataLen);  
}

/*
*配置广播数据
*param: pAdvData 广播数据配置
*return：自定义广播数据总长度
*/
uint8_t ble_adv_load_advData(uint8_t *pAdvData)
{
    uint8_t *p = pAdvData;
    uint8_t nameLen = MIN(setting.adv.nameLen, MAX_BLE_ADV_NAME_LEN);
    uint8_t specDataLen = MIN(setting.adv.meanufDataLen, MAX_BLE_MANUFACTURE_DATA_LEN);

    // meanufacture data 
    *p++ = specDataLen + 1;
    *p++ = BLE_TYPE_MANUFACTURE;    
    memcpy(p, &setting.adv.meanufData, specDataLen);
    p += specDataLen;

    // name
    *p++ = nameLen + 1;
    *p++ = BLE_TYPE_NAME;
    memcpy(p, setting.adv.name, nameLen);
    p += nameLen;
    
    return (p - pAdvData);
}

/*
*配置广播数据
*param: scanRspData 扫描响应数据配置
*return：自定义扫描响应数据总长度
*/
uint8_t ble_adv_load_scanRspData(uint8_t *scanRspData)
{
//    uint8_t uuid_128[] = {0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e};
//    uint8_t uuid_128_len = sizeof uuid_128;
    
    uint8_t uuid_16[] = {0x41, 0x58};
    uint8_t uuid_16_len = sizeof uuid_16;
    
    uint8_t *p = scanRspData;
    
//    *p++ = uuid_128_len + 1;
//    *p++ = BLE_TYPE_128UUID;
//    memcpy(p, uuid_128, uuid_128_len);
//    p += uuid_128_len;
    
    *p++ = uuid_16_len + 1;
    *p++ = BLE_TYPE_16UUID;
    memcpy(p, uuid_16, uuid_16_len);
    p += uuid_16_len;
    
    return (p - scanRspData);
}

