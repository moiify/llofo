/**
 ****************************************************************************************
 *
 * @file user_sps_config.h
 *
 * @brief Serial Port Service profile database structure and initialization.
 *
 * Copyright (C) 2016 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */


#ifndef _USER_SPS_CONFIG_H_
#define _USER_SPS_CONFIG_H_
#if BLE_SPS_SERVER
/**
 ****************************************************************************************
 * @defgroup USER_CONFIG
 * @ingroup USER
 * @brief Custom1/2 Server (CUSTS1/2) profile database structure and initialization.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>
#include "prf_types.h"
#include "attm_db_128.h"
#include "app_prf_types.h"
 
 
/*
 * DEFINES
 ****************************************************************************************
 */

#define SPS_SERVICE_UUID    {0xb7, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}

#define SPS_SERVER_TX_UUID  {0xb8, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}
#define SPS_SERVER_RX_UUID  {0xba, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}
#define SPS_FLOW_CTRL_UUID  {0xb9, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}

#define SPS_SERVER_TX_CHAR_LEN      250
#define SPS_SERVER_RX_CHAR_LEN      250
#define SPS_FLOW_CTRL_CHAR_LEN      1

#define SPS_SERVER_ENABLE_DESC  "Enable SPS Device"
#define SPS_SERVER_TX_DESC      "Server TX Data"
#define SPS_SERVER_RX_DESC      "Server RX Data"
#define SPS_FLOW_CTRL_DESC      "Flow Control"


/* Serial Port Server Data Base Characteristic enum */
enum
{
    SPSS_IDX_SVC = 0,

    SPSS_IDX_TX_DATA_CHAR,
    SPSS_IDX_TX_DATA_VAL,
    SPSS_IDX_TX_DATA_CFG,
    SPSS_IDX_TX_DATA_DESC,

    SPSS_IDX_RX_DATA_CHAR,
    SPSS_IDX_RX_DATA_VAL,
    SPSS_IDX_RX_DATA_CFG,
    SPSS_IDX_RX_DATA_DESC,

    SPSS_IDX_FLOW_CTRL_CHAR,
    SPSS_IDX_FLOW_CTRL_VAL,
    SPSS_IDX_FLOW_CTRL_CFG,
    SPSS_IDX_FLOW_CTRL_DESC,

    SPSS_IDX_NB
};

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */



///  Dialog Wearable Service Service

/// SPS Service
 static const struct att_uuid_128  sps_service = {SPS_SERVICE_UUID};

static const struct att_char128_desc  spss_tx_data_char  = {ATT_CHAR_PROP_NTF, {0,0}, SPS_SERVER_TX_UUID};  
static const struct att_uuid_128  spss_tx_data_val = {SPS_SERVER_TX_UUID};

static const struct att_char128_desc  spss_rx_data_char  = {ATT_CHAR_PROP_WR_NO_RESP, {0,0}, SPS_SERVER_RX_UUID}; 
static const struct att_uuid_128  spss_rx_data_val = {SPS_SERVER_RX_UUID};


static const struct att_char128_desc  spss_flow_ctrl_char  = {ATT_CHAR_PROP_NTF|ATT_CHAR_PROP_WR_NO_RESP|ATT_CHAR_PROP_RD, {0,0}, SPS_FLOW_CTRL_UUID}; 
static const struct att_uuid_128  spss_flow_ctrl_val = {SPS_FLOW_CTRL_UUID};


                                                                     

/*
 * DWS ATTRIBUTES
 ****************************************************************************************
 */

static const uint16_t att_decl_svc       = ATT_DECL_PRIMARY_SERVICE;
static const uint16_t att_decl_char      = ATT_DECL_CHARACTERISTIC;
static const uint16_t att_decl_cfg       = ATT_DESC_CLIENT_CHAR_CFG;
static const uint16_t att_decl_user_desc = ATT_DESC_CHAR_USER_DESCRIPTION;

/// Full DWS Database Description - Used to add attributes into the database
static const struct attm_desc_128 sps_att_db[SPSS_IDX_NB] =
{
        // SPS Service Declaration
    [SPSS_IDX_SVC]                      = {(uint8_t*)&att_decl_svc, ATT_UUID_128_LEN, PERM(RD, ENABLE),
                                            sizeof(sps_service), sizeof(sps_service), (uint8_t*)&sps_service},

    // TX Data Characteristic Declaration
    [SPSS_IDX_TX_DATA_CHAR]             = {(uint8_t*)&att_decl_char, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                           0,0,NULL},
    // TX Data Characteristic Value
    [SPSS_IDX_TX_DATA_VAL]              = {(uint8_t*)spss_tx_data_val.uuid, ATT_UUID_128_LEN, PERM(NTF, ENABLE),
                                            SPS_SERVER_TX_CHAR_LEN, 0, NULL},
    // TX Data  Characteristic Configuration Descriptor
    //WRITE_REQ 删了会导致蓝牙广播不出来
    [SPSS_IDX_TX_DATA_CFG]              = {(uint8_t*)&att_decl_cfg, ATT_UUID_16_LEN, PERM(RD, ENABLE) | PERM(WR, ENABLE)  | PERM(WRITE_REQ, ENABLE),
                                            sizeof(uint16_t), 0, NULL},
    // TX Data Characteristic User Description
    [SPSS_IDX_TX_DATA_DESC]             = {(uint8_t*)&att_decl_user_desc, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                            sizeof(SPS_SERVER_TX_DESC) - 1, sizeof(SPS_SERVER_TX_DESC) - 1, SPS_SERVER_TX_DESC},
     // RX Data Characteristic Declaration
    [SPSS_IDX_RX_DATA_CHAR]             = {(uint8_t*)&att_decl_char, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                           0,0,NULL},
    // RX Data Characteristic Value
    [SPSS_IDX_RX_DATA_VAL]              = {(uint8_t*)spss_rx_data_val.uuid, ATT_UUID_128_LEN, PERM(WR, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                                            SPS_SERVER_RX_CHAR_LEN, 0, NULL},
    // RX Data  Characteristic Configuration Descriptor
    [SPSS_IDX_RX_DATA_CFG]              = {(uint8_t*)&att_decl_cfg, ATT_UUID_16_LEN, PERM(RD, ENABLE) | PERM(WR, ENABLE) | PERM(WRITE_REQ, ENABLE),
                                            sizeof(uint16_t), 0, NULL},
    // RX Data Characteristic User Description
    [SPSS_IDX_RX_DATA_DESC]             = {(uint8_t*)&att_decl_user_desc, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                            sizeof(SPS_SERVER_RX_DESC) - 1, sizeof(SPS_SERVER_RX_DESC) - 1, SPS_SERVER_RX_DESC},
    // Flow Control Characteristic Declaration
    [SPSS_IDX_FLOW_CTRL_CHAR]           = {(uint8_t*)&att_decl_char, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                            0,0,NULL},         
    // Flow Control Characteristic Value
    [SPSS_IDX_FLOW_CTRL_VAL]            = {(uint8_t*)spss_flow_ctrl_val.uuid, ATT_UUID_128_LEN, PERM(RD, ENABLE) | PERM(WR, ENABLE) | PERM(NTF, ENABLE)  | PERM(WRITE_COMMAND, ENABLE),
                                            SPS_FLOW_CTRL_CHAR_LEN, 0, NULL},
    // Flow Control  Characteristic Configuration Descriptor
    [SPSS_IDX_FLOW_CTRL_CFG]            = {(uint8_t*)&att_decl_cfg, ATT_UUID_16_LEN, PERM(RD, ENABLE) | PERM(WR, ENABLE)  | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                                            sizeof(uint16_t), 0, NULL},
    // Flow Control Characteristic User Description
    [SPSS_IDX_FLOW_CTRL_DESC]           = {(uint8_t*)&att_decl_user_desc, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                            sizeof(SPS_FLOW_CTRL_DESC) - 1, sizeof(SPS_FLOW_CTRL_DESC) - 1, SPS_FLOW_CTRL_DESC},
                                            
};

#endif
#endif 
