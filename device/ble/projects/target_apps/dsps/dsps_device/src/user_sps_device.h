/**
 ****************************************************************************************
 *
 * @file user_sps_device.h
 *
 * @brief DSPS Device project source code include file.
 *
 * Copyright (C) 2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _USER_SPS_DEVICE_H_
#define _USER_SPS_DEVICE_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup RICOW
 *
 * @brief 
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwble_config.h"
#include "app_task.h"                  // application task
#include "gapc_task.h"                 // gap functions and messages
#include "gapm_task.h"                 // gap functions and messages
#include "app.h"                       // application definitions
#include "co_error.h"                  // error code definitions
#include "ble_scan_proc.h"
#include "app_callback.h"

/****************************************************************************
Add here supported profiles' application header files.
i.e.
#if (BLE_DIS_SERVER)
#include "app_dis.h"
#include "app_dis_task.h"
#endif
*****************************************************************************/
#include "user_spss.h"
#include "user_spss_task.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#ifdef DEBUG_PRINT
#define DBG_PRN(...) arch_printf(__VA_ARGS__) 
#else
#define DBG_PRN(...)
#endif

#ifdef DEBUG_PRINT_L2
#define DBG_PRN2(...) arch_printf(__VA_ARGS__)  // 2nd Level debug
#else
#define DBG_PRN2(...)
#endif
 

#define DBG1_ON GPIO_SetActive(GPIO_DBG1_PORT,GPIO_DBG1_PIN)
#define DBG1_OFF GPIO_SetInactive(GPIO_DBG1_PORT,GPIO_DBG1_PIN)

#define DBG2_ON GPIO_SetActive(GPIO_DBG2_PORT,GPIO_DBG2_PIN)
#define DBG2_OFF GPIO_SetInactive(GPIO_DBG2_PORT,GPIO_DBG2_PIN)

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
void user_scan_start(void);

/**
 ****************************************************************************************
 * @brief Handles connection event
 * @param[in]   connection_idx Connection index
 * @param[in]   param Parameters of connection
 * @return void
 ****************************************************************************************
 */
void user_on_connection(uint8_t connection_idx, struct gapc_connection_req_ind const *param);

/**
 ****************************************************************************************
 * @brief Handles disconnection event
 * @param[in]   param Parameters of disconnect message
 * @return void
 ****************************************************************************************
 */
void user_on_disconnect( struct gapc_disconnect_ind const *param );

/**
 ****************************************************************************************
 * @brief Handles connection failure
 * @return void
 ****************************************************************************************
 */
void user_on_connect_failed (void);

/**
 ****************************************************************************************
 * @brief Called upon scan completion
 * @param[in]   status scanning status
 * @return void
 ****************************************************************************************
 */
void user_on_scanning_completed(uint8_t status);


/*
 * MAIN LOOP CALLBACKS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Called on device initialization
 ****************************************************************************************
 */
void user_on_init(void);

/**
 ****************************************************************************************
 * @brief Called on system power up
 * @return GOTO_SLEEP or KEEP_POWERED
 ****************************************************************************************
 */
arch_main_loop_callback_ret_t user_on_system_powered(void);

/**
 ****************************************************************************************
 * @brief Called before entering sleep
 * @return void
 ****************************************************************************************
 */
void user_before_sleep(void);
/**
 ****************************************************************************************
 * @brief Called on database initialization complete
 * @return void
 ****************************************************************************************
 */
void user_on_db_init_complete(void);

/**
 ****************************************************************************************
 * @brief Called on the reception of GAPC_LE_PKT_SIZE_IND
 * @return void
 ****************************************************************************************
 */
 
void user_on_data_length_change (struct gapc_le_pkt_size_ind *param, uint16_t src_id);

/**
 ****************************************************************************************
 * @brief Handles the messages that are not handled by the SDK internal mechanisms.
 * @param[in] msgid      Id of the message received.
 * @param[in] param      Pointer to the parameters of the message.
 * @param[in] dest_id    ID of the receiving task instance.
 * @param[in] src_id     ID of the sending task instance.
 * @return void
 ****************************************************************************************
*/
void user_catch_rest_hndl(ke_msg_id_t const msgid,
                          void const *param,
                          ke_task_id_t const dest_id,
                          ke_task_id_t const src_id);
/**
 ****************************************************************************************
 * @brief Callback of the GAPC_UPDATE_PARAMS (parameter update is complete)
 * @param[in]   src_id the source id of the task
 * @return void
 ****************************************************************************************
 */                                                 
void user_on_update_params_complete(uint16_t src_id);

/**
 ****************************************************************************************
 * @brief Callback of the GAPC_UPDATE_PARAMS rejection (parameter update is rejected)
 * @param[in]   status status of the message
 * @param[in]   src_id the source id of the task
 * @return void
 ****************************************************************************************
 */
void user_on_update_params_rejected(uint8_t status,  uint16_t src_id);
    
void user_adv_report_ind(struct gapm_adv_report_ind const *param);

void user_on_adv_undirect_complete(uint8_t status);


void user_on_set_dev_config_complete(void);
/// @} APP

#endif //_USER_SPS_DEVICE_H_
