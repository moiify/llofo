/**
 ****************************************************************************************
 *
 * @file  user_spss_task.c
 *
 * @brief SPS application Message Handlers.
 *
 * Copyright (C) 2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"        // SW configuration

#if (BLE_APP_PRESENT)

#if (BLE_SPS_SERVER)

#include "user_spss_task.h"
#include "user_spss.h" 
#include "app_task.h"           // Application Task API
#include "sps_server.h"         // SPS functions
#include "sps_server_task.h"
#include "user_sps_config.h"
#include "gpio.h"
#include "arch_console.h"
#include "user_sps_device.h"
#include "prf_utils.h"
#include "app_entry_point.h"

/*
* GLOBAL VARIABLE DEFINITIONS
****************************************************************************************
*/

/*
 * EXTERNAL DEFINITIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

const struct ke_msg_handler user_spss_process_handlers[]=
{
    {SPS_SERVER_ENABLE_CFM,         (ke_msg_func_t)user_sps_server_enable_cfm_handler},
    {SPS_SERVER_DATA_TX_CFM,        (ke_msg_func_t)user_sps_server_data_tx_cfm_handler},
    {SPS_SERVER_TX_FLOW_CTRL_IND,   (ke_msg_func_t)user_sps_server_tx_flow_ctrl_ind_handler},
    {SPS_SERVER_ERROR_IND,          (ke_msg_func_t)user_sps_server_error_ind_handler},
    {SPS_SERVER_DATA_WRITE_IND,     (ke_msg_func_t)user_sps_server_data_write_ind_handler},
    {GATTC_MTU_CHANGED_IND,         (ke_msg_func_t)gattc_mtu_changed_ind_handler},
};

/**
 ****************************************************************************************
 * @brief Process handler for the Application SPSS messages.
 * @param[in] msgid   Id of the message received
 * @param[in] param   Pointer to the parameters of the message
 * @param[in] dest_id ID of the receiving task instance (probably unused)
 * @param[in] src_id  ID of the sending task instance
 * @param[in] msg_ret Result of the message handler
 * @return Returns if the message is handled by the process handler
 ****************************************************************************************
 */

enum process_event_response user_spss_process_handler(ke_msg_id_t const msgid,
                                         void const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id, 
                                         enum ke_msg_status_tag *msg_ret)
{
    return (app_std_process_event(msgid, param,src_id,dest_id,msg_ret, user_spss_process_handlers,
                                         sizeof(user_spss_process_handlers)/sizeof(struct ke_msg_handler)));
}
 
/**
 ****************************************************************************************
 * @brief Handles enable indication of the database
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int user_sps_server_enable_cfm_handler(ke_msg_id_t const msgid,
                                      struct sps_server_enable_cfm const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    //user_ble_pull(false, false);
    arch_printf("SPSS Profile Enabled\r\n");

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles confirmation that data has been sent
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */

int user_sps_server_data_tx_cfm_handler(ke_msg_id_t const msgid,
                                      struct sps_server_data_tx_cfm const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    /* 
    if(param->status == ATT_ERR_NO_ERROR){
        user_ble_pull(false, true);
    } else {
        user_ble_pull(false, false);
    }    
    */
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles indication that data has been received
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int user_sps_server_data_write_ind_handler(ke_msg_id_t const msgid,
                                           struct sps_val_write_ind const *param,
                                           ke_task_id_t const dest_id,
                                           ke_task_id_t const src_id)
{
    //user_ble_push((uint8_t *)param->data, param->length);
    reciv_data_fromBLE_cb((const uint8_t *)param->data, param->length);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles server flow control state request indication
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int user_sps_server_tx_flow_ctrl_ind_handler(ke_msg_id_t const msgid,
                                      struct sps_server_tx_flow_ctrl_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    if(param->flow_control_state == FLOW_ON)
    {
        arch_printf("SERVER TX FLOW ON\r\n");
    }
    else
    {
        arch_printf("SERVER TX FLOW OFF\r\n");
    }
    
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles server error indication
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int user_sps_server_error_ind_handler(ke_msg_id_t const msgid,
                                      struct prf_server_error_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    ASSERT_WARNING(0);
    return (KE_MSG_CONSUMED);
}

/****************************************************************************************
* @brief Handles reception of the @ref GATTC_MTU_CHANGED_IND message.
* @param[in] msgid Id of the message received (probably unused).
* @param[in] param Pointer to the parameters of the message.
* @param[in] dest_id ID of the receiving task instance (probably unused).
* @param[in] src_id ID of the sending task instance.
* @return If the message was consumed or not.
****************************************************************************************
*/
static int gattc_mtu_changed_ind_handler(ke_msg_id_t const msgid, const struct gattc_mtu_changed_ind *param,
                                      ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    
    sps_env->mtu = param->mtu;
    sps_env->tx_size =  param->mtu-3;       
    sps_env->tx_wait_level =  (3*param->mtu)/4;       
    arch_printf("TX SIZE (MTU CHANGED)/LVL %i %i\r\n", (int)sps_env->tx_size, (int)sps_env->tx_wait_level);
    
    return (KE_MSG_CONSUMED);
};
#endif //(BLE_SPS_SERVER)

#endif //(BLE_APP_PRESENT)

/// @} APP

