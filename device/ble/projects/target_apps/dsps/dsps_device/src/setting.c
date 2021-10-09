#include "setting.h"
#include "protocol.h"
#include <string.h>
#include "nvds.h"

extern struct nvds_data_struct nvds_data_storage;

ST_BLE_STATE setting = 
{
    .mode = BLE_MODE_ADV,
    .adv  = {
                .name = "XiaoanTech", //simcom会通信覆盖此配置
                .nameLen = 10,
                .meanufData = "\x12\x34\x56",
                .meanufDataLen = 3,
            },
    .scan = {
                .supposedName = "PKE_Xiaoan",
                .cfgedKeyID = {0},
                .keyNum = 0,
                .key = {0}
            },
    .address = {0},
    .isHeartBeatOn = 1,
    .isconnected = 0,
    .protocol_type = PROTOCOL_XIAOAN,
    .beaconRssi = 70,
    .lastbeaconRssi = 70,
    .updateBeaconRssi = 0
};

void setting_set_address(const uint8_t *address)
{
    memcpy(nvds_data_storage.bd_address, address, BLE_ADDRESS_LEN);
    memcpy(setting.address, nvds_data_storage.bd_address, BLE_ADDRESS_LEN);
}

void setting_set_address_from_imei(uint8_t *imei)
{
    uint8_t addr[BLE_ADDRESS_LEN];
    for(int i = 0; i < BLE_ADDRESS_LEN; i++)
    {
        uint8_t tmp1, tmp2;
        tmp1 = imei[2 * i + 3] - 0x30;
        tmp2 = imei[2 * i + 4] - 0x30;
        addr[i] = ((tmp1 << 4) & 0xFF) | (tmp2 & 0xFF);
    }
    setting_set_address(addr);
}

ENUM_BLE_RETURN setting_isParamConfiged(void)
{
    uint8_t defaultADDR[] = CFG_NVDS_TAG_BD_ADDRESS;
    if(memcmp(defaultADDR, nvds_data_storage.bd_address, BLE_ADDRESS_LEN) == 0)
    {
        return BLE_FAILED;
    }
    return BLE_SUCCESS;
}

