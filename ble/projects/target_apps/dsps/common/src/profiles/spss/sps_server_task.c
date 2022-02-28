/**
 ****************************************************************************************
 *
 * @file sps_server_task.c
 *
 * @brief Serial Port Service Device profile task.
 *
 * Copyright (C) 2016 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup SPS_SERVER_TASK
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwble_config.h"

#if (BLE_SPS_SERVER)

#include "gap.h"
#include "gattc_task.h"

#include "sps_server.h"
#include "sps_server_task.h"

#include "prf_utils.h"
#include "user_sps_config.h"
#include "app_customs.h"
#include "custom_common.h"
#include "arch_console.h"
#include "attm.h"
#ifdef DMA_UART
#include "user_sps_device_dma.h"
#else
#include "user_sps_device.h"
#endif

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
 extern struct sps_counter ble_data_counter;
 
/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
 
/**
 ****************************************************************************************
 * @brief Handles reception of the @ref SPS_SERVER_ENABLE_REQ message.
 * The handler enables the Serial Port Service Device profile.
 * @param[in] msgid Id of the message received .
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance 
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int sps_server_enable_req_handler(ke_msg_id_t const msgid,
                                    struct sps_server_enable_req const *param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
        
    //Save the connection handle associated to the profile
    uint8_t conidx = param->conidx;
      
    // Check if the provided connection exist
    if (conidx == GAP_INVALID_CONIDX)
    {
       // Send error to application
        sps_server_error_ind_send( conidx, PRF_ERR_REQ_DISALLOWED, SPS_SERVER_ERROR_IND, SPS_SERVER_ENABLE_REQ);
    }
    else
    {
        // Go to connected state
        ke_state_set(sps_env->prf_env.prf_task, SPS_SERVER_ACTIVE);
        
        //Initialise flow flags
        sps_env->tx_flow_en = true;
        sps_env->rx_flow_en = true;
        
        // Reset counter
        sps_env->pending_ntf_cmp = 0;
        sps_env->pending_tx_ntf_cmp = false;
        
        //Send response to application
        struct sps_server_enable_cfm * cfm = KE_MSG_ALLOC(SPS_SERVER_ENABLE_CFM,
														  src_id,
														  dest_id,
														  sps_server_enable_cfm);
        cfm->status = 1;
        ke_msg_send(cfm);
    }
    
    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref gattc_cmp_evt message.
 * The handler enables the Serial Port Service Device profile.
 * @param[in] msgid Id of the message received .
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance 
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_cmp_evt_handler(ke_msg_id_t const msgid,
                                struct gattc_cmp_evt const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    if(param->operation == GATTC_NOTIFY)
    {
        ASSERT_WARNING(sps_env->pending_ntf_cmp > 0);
        sps_env->pending_ntf_cmp--;
        if (!sps_env->pending_ntf_cmp && sps_env->pending_tx_ntf_cmp)
        {
            sps_env->pending_tx_ntf_cmp = false;
            ble_data_counter.spss_ble_tx_cmp++;
            struct sps_server_data_tx_cfm * cfm = KE_MSG_ALLOC(SPS_SERVER_DATA_TX_CFM,
                                                               prf_dst_task_get(&(sps_env->prf_env), KE_IDX_GET(src_id)),
                                                               dest_id,
                                                               sps_server_data_tx_cfm);
            cfm->status = param->status;
            ke_msg_send(cfm);
            
        }
    }
    else if( param->operation == GATTC_MTU_EXCH )
    {
        arch_printf("GATTC MTU CMP\r\n");
    }
    else
    {
        arch_printf("GATTC OP %i \r\n", (int)param->operation);
    }           
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Send first part of data in buffer @ref sps_server_data_tx_req message.
 * @param[in] msgid Id of the message received 
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */

static int sps_server_data_tx_req_handler(ke_msg_id_t const msgid,
                                struct sps_server_data_tx_req const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    uint8_t conidx = KE_IDX_GET(dest_id);
    
    if (sps_env->tx_flow_en)
    {
        bool success = sps_server_send_data( (void *)param, SPSS_IDX_TX_DATA_VAL, conidx, param->length );
        if ( success )
        {
            ble_data_counter.spss_ble_tx_ntf_ok++;
            ble_data_counter.spss_ble_tx_data_bytes +=  param->length ;
            sps_env->pending_tx_ntf_cmp = true;
            sps_env->pending_ntf_cmp++;
            return (KE_MSG_NO_FREE);
        }
        else
        {
            ble_data_counter.spss_ble_tx_ntf_fail++;
            sps_env->tx_busy_flag = false;
        }
    }
    return (KE_MSG_CONSUMED);
}
 
/**
 ****************************************************************************************
 * @brief Send flow control state @ref sps_server_rx_flow_ctrl_req message.
 * @param[in] msgid Id of the message received 
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int sps_server_rx_flow_ctrl_req_handler(ke_msg_id_t const msgid,
                                   struct sps_server_rx_flow_ctrl_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
 
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    uint8_t conidx = KE_IDX_GET(dest_id);
    // Set value in data base
    attmdb_att_set_value(sps_env->shdl + SPSS_IDX_FLOW_CTRL_VAL, sizeof(param->flow_control_state), 0, (uint8_t*) &(param->flow_control_state ));

    // Send notification to the client
    sps_server_send_event( SPSS_IDX_FLOW_CTRL_VAL , conidx, (uint8_t *)&param->flow_control_state, sizeof(param->flow_control_state) );
    sps_env->pending_ntf_cmp++;

    //Set flag
    sps_env->rx_flow_en = (param->flow_control_state == FLOW_ON ? true : false);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATT_WRITE_CMD_IND message.
 * Receive and proces incoming data 
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */

static int gattc_write_req_ind_handler(ke_msg_id_t const msgid, const struct gattc_write_req_ind *param,
                                      ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    struct gattc_write_cfm * cfm;
    uint8_t att_idx = 0;
    uint8_t conidx = KE_IDX_GET(src_id);
    uint8_t nofree = 0;
     
    // retrieve handle information
    uint8_t status = sps_get_att_idx(param->handle, &att_idx);
    att_perm_type perm;

    ASSERT_ERR(param->offset == 0);
         
    if (status == ATT_ERR_NO_ERROR)
    {
        if ( (att_idx==SPSS_IDX_TX_DATA_CFG) || (att_idx==SPSS_IDX_FLOW_CTRL_CFG) )
        {
            struct attm_elmt elem = {0};

            // Find the handle of the Characteristic Value
            uint16_t value_hdl = get_value_handle(param->handle);
            ASSERT_ERR(value_hdl);

            // Get permissions to identify if it is NTF or IND.
            attmdb_att_get_permission(value_hdl, &perm, 0, &elem);
            status = check_client_char_cfg(PERM_IS_SET(perm, NTF, ENABLE), param);

            if (status == ATT_ERR_NO_ERROR)
            {
                sps_set_ccc_value(conidx, att_idx, *(uint16_t *)param->value);
            }
            //If the notifications of the flow control are enabled, we should send our flow control value    
            if (att_idx==SPSS_IDX_FLOW_CTRL_CFG)
            {   
                // Extract value before check
                uint16_t ntf_cfg = co_read16p(&param->value[0]);
                
                //provide ble flow control state when flow control att is configured to 0x0100
                if (ntf_cfg == PRF_CLI_START_NTF)
                {
                    uint8_t flow = (sps_env->rx_flow_en ? FLOW_ON : FLOW_OFF);
                    // Set value in data base
                    attmdb_att_set_value(sps_env->shdl + SPSS_IDX_FLOW_CTRL_VAL, sizeof(flow), 0, &flow);
                
                    // Send notification to the client
                    sps_server_send_event( SPSS_IDX_FLOW_CTRL_VAL, conidx, &flow, sizeof(flow) );
                    sps_env->pending_ntf_cmp++;
                } 
             }
        }
        else if (att_idx==SPSS_IDX_FLOW_CTRL_VAL)
        {
            //update ble flow control flag
            if(param->value[0] == FLOW_ON)
            {
                sps_env->tx_flow_en = true;
                sps_server_indicate_tx_flow_ctrl(FLOW_ON, conidx);
                sps_env->pending_tx = false;
            }
            else if (param->value[0] == FLOW_OFF)
            {
                sps_env->tx_flow_en = false;
                sps_server_indicate_tx_flow_ctrl(FLOW_OFF, conidx);
            }
         }
         else if (att_idx==SPSS_IDX_RX_DATA_VAL)
         {
                ble_data_counter.spss_ble_rx_data_bytes += param->length;
         }
     }
         
    if ( (status == ATT_ERR_NO_ERROR) && (att_idx==SPSS_IDX_RX_DATA_VAL) )
    {
        // Inform APP
        sps_server_data_receive( sps_env, (void *) param);
        nofree = 1;
    }
    

    //Send write response
    cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    cfm->status = status;
    ke_msg_send(cfm);
    
    if( nofree )
          return (KE_MSG_NO_FREE);
    else    
          return (KE_MSG_CONSUMED);
}
 
/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_READ_REQ_IND message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_read_req_ind_handler(ke_msg_id_t const msgid, struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    struct gattc_read_cfm * cfm;
    uint8_t att_idx = 0;
    uint8_t conidx = KE_IDX_GET(src_id);
    // retrieve handle information
    uint8_t status = sps_get_att_idx(param->handle, &att_idx);
    uint16_t length = 0;
    uint16_t ccc_val = 0;
   

    // If the attribute has been found, status is GAP_ERR_NO_ERROR
    if (status == GAP_ERR_NO_ERROR)
    {
        if ( (att_idx==SPSS_IDX_TX_DATA_CFG) || (att_idx==SPSS_IDX_FLOW_CTRL_CFG) )
        {
            ccc_val = sps_get_ccc_value(conidx, att_idx);
            length = 2;
        }
        else
        {
            status = PRF_APP_ERROR;
        }
    }

    // Send read response
    cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM,
                           src_id,
                           dest_id,
                           gattc_read_cfm,
                           length);
        
    cfm->handle = param->handle;
    cfm->status = status;
    cfm->length = length;

    if (status == GAP_ERR_NO_ERROR)
    {
        memcpy(cfm->value, &ccc_val, length);
    }

    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}

/*
 * TASK DESCRIPTOR DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler sps_default_state[] =
{
    {SPS_SERVER_ENABLE_REQ,         (ke_msg_func_t)sps_server_enable_req_handler},
    {GATTC_CMP_EVT,                 (ke_msg_func_t)gattc_cmp_evt_handler},
    {GATTC_WRITE_REQ_IND,           (ke_msg_func_t)gattc_write_req_ind_handler},
    {SPS_SERVER_DATA_TX_REQ,        (ke_msg_func_t)sps_server_data_tx_req_handler},
    {SPS_SERVER_RX_FLOW_CTRL_REQ,   (ke_msg_func_t)sps_server_rx_flow_ctrl_req_handler},
    {GATTC_READ_REQ_IND,            (ke_msg_func_t)gattc_read_req_ind_handler},

}; 

const struct ke_state_handler sps_server_default_handler = KE_STATE_HANDLER(sps_default_state);

#endif /*#if BLE_SPS_SERVER*/

/// @} SPS_SERVER_TASK
