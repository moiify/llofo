/**
 ****************************************************************************************
 *
 * @file user_spss.h
 *
 * @brief SPS Application header file
 *
 * Copyright (C) 2016 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef USER_SPSS_H_
#define USER_SPSS_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup RICOW
 *
 * @brief SPS Application header file.
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwble_config.h"

#if (BLE_SPS_SERVER)

#include <stdint.h>          // standard integer definition
#include <co_bt.h>

#include "sps_server.h"

/*
 * STRUCTURES
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLE DECLARATION
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
 
 /**
 ****************************************************************************************
 * @brief Initialize task variables
 * @return void
 ****************************************************************************************
 */ 
void user_spss_init(void);
 /**
 ****************************************************************************************
 * @brief       user_sps_create_db creates a database for the sps server service
 * @return      none
 ****************************************************************************************
 */
void user_spss_create_db(void);

/**
 ****************************************************************************************
 * @brief       Function used to enable server role
 * @param[in]   Connection handle
 * @return      none
 ****************************************************************************************
 */
void user_spss_enable(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief       Send data over Bluetooth
 * @param[in]   flow control (FLOW_ON or FLOW_OFF)
 * @return      none
 ****************************************************************************************
 */
void user_send_ble_data(const uint8_t *data, uint16_t length);

/**
 ****************************************************************************************
 * @brief       Send flow control over Bluetooth
 * @param[in]   flow control (FLOW_ON or FLOW_OFF)
 * @return      none
 ****************************************************************************************
 */
void user_send_ble_flow_ctrl(uint8_t flow_ctrl);

#endif //BLE_SPS_SERVER

/// @} APP

#endif // USER_SPSS_H_
