/**
 ****************************************************************************************
 *
 * @file nvds.c
 *
 * @brief Non Volatile Data Storage (NVDS) driver
 *
 * Copyright (C) RivieraWaves 2009-2013
 * Copyright (C) 2017 Modified by Dialog Semiconductor
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup NVDS
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <string.h>      // string definitions
#include <stddef.h>      // standard definitions
#include "nvds.h"        // nvds definitions
#include "arch.h"        // main
#include "co_math.h"     // math operations
#include "co_bt.h"
#include "co_utils.h"
#include "hw_otpc.h"
#include "rwip_config.h"

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const struct nvds_data_struct nvds_data_storage =
{
    .lpclk_drift                   = CFG_NVDS_TAG_LPCLK_DRIFT,
    .bd_address                    = CFG_NVDS_TAG_BD_ADDRESS,
    /// Default Channel Assessment Timer duration (20s - Multiple of 10ms)
    .ble_ca_timer_dur              = CFG_NVDS_TAG_BLE_CA_TIMER_DUR,
    /// Default Channel Reassessment Timer duration (Multiple of Channel Assessment Timer duration)
    .ble_cra_timer_dur             = CFG_NVDS_TAG_BLE_CRA_TIMER_DUR,
    /// Default Minimal RSSI Threshold - -48dBm
    .ble_ca_min_rssi               = CFG_NVDS_TAG_BLE_CA_MIN_RSSI,
    /// Default number of packets to receive for statistics
    .ble_ca_nb_pkt                 = CFG_NVDS_TAG_BLE_CA_NB_PKT,
    /// Default number of bad packets needed to remove a channel
    .ble_ca_nb_bad_pkt             = CFG_NVDS_TAG_BLE_CA_NB_BAD_PKT,
};

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

uint8_t nvds_get_func(uint8_t tag, nvds_tag_len_t *lengthPtr, uint8_t *buf)
{
    extern struct bd_addr dev_bdaddr;
    uint8_t status = NVDS_FAIL;

    switch (tag)
    {
        case NVDS_TAG_BD_ADDRESS:
        {
            //check if dev_bdaddr is not zero
            if(memcmp(&dev_bdaddr, &co_null_bdaddr, NVDS_LEN_BD_ADDRESS))
            {
                memcpy(buf, &dev_bdaddr, NVDS_LEN_BD_ADDRESS);
                *lengthPtr = NVDS_LEN_BD_ADDRESS;
                status = NVDS_OK;
            }
            else
            {
                memcpy(buf, nvds_data_storage.bd_address, NVDS_LEN_BD_ADDRESS);
                *lengthPtr = NVDS_LEN_BD_ADDRESS;
                status = NVDS_OK;
            }
        } break;

        case NVDS_TAG_LPCLK_DRIFT:
        {
            if (*lengthPtr < NVDS_LEN_LPCLK_DRIFT)
            {
                *lengthPtr = 0;
                status = NVDS_LENGTH_OUT_OF_RANGE;
            }
            else
            {
                memcpy(buf, &nvds_data_storage.lpclk_drift, NVDS_LEN_LPCLK_DRIFT);
                *lengthPtr = NVDS_LEN_LPCLK_DRIFT;
                status = NVDS_OK;
            }
        } break;

        case NVDS_TAG_BLE_CA_TIMER_DUR:
        {
            if (*lengthPtr < NVDS_LEN_BLE_CA_TIMER_DUR)
            {
                *lengthPtr = 0;
                status = NVDS_LENGTH_OUT_OF_RANGE;
            }
            else
            {
                memcpy(buf, &nvds_data_storage.ble_ca_timer_dur, NVDS_LEN_BLE_CA_TIMER_DUR);
                *lengthPtr = NVDS_LEN_BLE_CA_TIMER_DUR;
                status = NVDS_OK;
            }
        } break;

        case NVDS_TAG_BLE_CRA_TIMER_DUR:
        {
            if (*lengthPtr < NVDS_LEN_BLE_CRA_TIMER_DUR)
            {
                *lengthPtr = 0;
                status = NVDS_LENGTH_OUT_OF_RANGE;
            }
            else
            {
                memcpy(buf, &nvds_data_storage.ble_cra_timer_dur, NVDS_LEN_BLE_CRA_TIMER_DUR);
                *lengthPtr = NVDS_LEN_BLE_CRA_TIMER_DUR;
                status = NVDS_OK;
            }
        } break;

        case NVDS_TAG_BLE_CA_MIN_RSSI:
        {
            if (*lengthPtr < NVDS_LEN_BLE_CA_MIN_RSSI)
            {
                *lengthPtr = 0;
                status = NVDS_LENGTH_OUT_OF_RANGE;
            }
            else
            {
                memcpy(buf, &nvds_data_storage.ble_ca_min_rssi, NVDS_LEN_BLE_CA_MIN_RSSI);
                *lengthPtr = NVDS_LEN_BLE_CA_MIN_RSSI;
                status = NVDS_OK;
            }
        } break;

        case NVDS_TAG_BLE_CA_NB_PKT:
        {
            if (*lengthPtr < NVDS_LEN_BLE_CA_NB_PKT)
            {
                *lengthPtr = 0;
                status = NVDS_LENGTH_OUT_OF_RANGE;
            }
            else
            {
                memcpy(buf, &nvds_data_storage.ble_ca_nb_pkt, NVDS_LEN_BLE_CA_NB_PKT);
                *lengthPtr = NVDS_LEN_BLE_CA_NB_PKT;
                status = NVDS_OK;
            }
        } break;


        case NVDS_TAG_BLE_CA_NB_BAD_PKT:
        {
            if (*lengthPtr < NVDS_LEN_BLE_CA_NB_BAD_PKT)
            {
                *lengthPtr = 0;
                status = NVDS_LENGTH_OUT_OF_RANGE;
            }
            else
            {
                memcpy(buf, &nvds_data_storage.ble_ca_nb_bad_pkt, NVDS_LEN_BLE_CA_NB_BAD_PKT);
                *lengthPtr = NVDS_LEN_BLE_CA_NB_BAD_PKT;
                status = NVDS_OK;
            }
        } break;

    } // switch

    return status;
}

/// NVDS API implementation - required by ROM function table
uint8_t nvds_init_func(uint8_t *base, uint32_t len)
{
    return NVDS_OK;
}

/// NVDS API implementation - required by ROM function table
uint8_t nvds_del_func(uint8_t tag)
{
    return NVDS_FAIL;
}

/// NVDS API implementation - required by ROM function table
uint8_t nvds_put_func(uint8_t tag, nvds_tag_len_t length, uint8_t *buf)
{
    return NVDS_FAIL;
}

void nvds_read_data_from_otp(uint32_t address, uint8_t *userData, uint16_t dataLen)
{
    uint8_t *otp_bdaddr;
    otp_bdaddr = (uint8_t *)(address);   //where in OTP header is BDADDR
    /*
     * Reset OTP controller
     */
    SetWord32(OTPC_MODE_REG, HW_OTPC_MODE_STBY);    // Set OTPC to standby
    SetBits16(SYS_CTRL_REG, OTPC_RESET_REQ, 1);     // Reset the OTPC
    SetBits16(SYS_CTRL_REG, OTPC_RESET_REQ, 0);     // Get the OTPC out of Reset

    /*
     * Initialize the POR registers
     */
    SetWord32(OTPC_NWORDS_REG, OTPC_NWORDS_REG_RESET);
    SetWord32(OTPC_TIM1_REG, OTPC_TIM1_REG_RESET);
    SetWord32(OTPC_TIM2_REG, OTPC_TIM2_REG_RESET);

    /*
     * Enable OTPC clock
     */
    SetBits16(CLK_AMBA_REG, OTP_ENABLE, 1);

    /*
     * Wait for a while for the OTP settling time.
     */
    for(volatile int i = 0; i < 100; i++);
    
    hw_otpc_manual_read_on(false);
    
    memcpy(userData, otp_bdaddr, dataLen);
    
    hw_otpc_manual_read_off();
    SetBits16(CLK_AMBA_REG, OTP_ENABLE, 0);
}

/// @} NVDS
