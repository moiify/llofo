 /**
 ****************************************************************************************
 *
 * @file sps_server.c
 *
 * @brief Serial Port Service Server Implementation.
 *
 * Copyright (C) 2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */
 
/**
 ****************************************************************************************
 * @addtogroup SPS_SERVER
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#if (BLE_SPS_SERVER)

#include "attm_db_128.h"
#include "sps_server_task.h"
#include "sps_server.h"
#include "attm_db.h"
#include "gapc.h"
#include "prf.h"
#include "user_sps_config.h"
#include "prf_utils.h"
#include "attm.h"
#include "custom_common.h"
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
 struct sps_counter ble_data_counter;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Init of the SPS device
 ****************************************************************************************
 */
 
uint8_t sps_init(struct prf_task_env *env, uint16_t *start_hdl, uint16_t app_task, uint8_t sec_lvl, struct spss_db_cfg *params)
{
    //------------------ create the attribute database for the profile -------------------

    // DB Creation Status
    uint8_t status = ATT_ERR_NO_ERROR;

    status = attm_svc_create_db_128(SPSS_IDX_SVC, start_hdl, NULL,
            SPSS_IDX_NB, NULL, env->task, sps_att_db,
            (sec_lvl & PERM_MASK_SVC_AUTH) | (sec_lvl & PERM_MASK_SVC_EKS) | PERM(SVC_PRIMARY, ENABLE));

    //-------------------- allocate memory required for the profile  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
        struct spss_env_tag *spss_env =
                (struct spss_env_tag *) ke_malloc(sizeof(struct spss_env_tag), KE_MEM_ATT_DB);

        // allocate required environment variable
        env->env = (prf_env_t *)spss_env;
        spss_env->shdl = *start_hdl;
        spss_env->max_nb_att = SPSS_IDX_NB;
        spss_env->prf_env.app_task = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        spss_env->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);

        // initialize environment variable
        env->id                     = TASK_ID_SPS_SERVER;
        env->desc.idx_max           = SPSS_IDX_MAX;
        env->desc.state             = spss_env->state;
        env->desc.default_handler   = &sps_server_default_handler;
        co_list_init(&(spss_env->values));
        sps_init_ccc_values(sps_att_db, SPSS_IDX_NB);

        // service is ready, go into an Idle state
        ke_state_set(spss_env->prf_env.prf_task, SPS_SERVER_IDLE);
                
    }
    return status;
}
 
/**
 ****************************************************************************************
 * @brief Destruction of the sps module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void sps_destroy(struct prf_task_env *env)
{
    
    struct spss_env_tag *spss_env = PRF_ENV_GET(SPS_SERVER, spss);
    
   // remove all values present in list
    while (!co_list_is_empty(&(spss_env->values)))
    {
        struct co_list_hdr *hdr = co_list_pop_front(&(spss_env->values));
        ke_free(hdr);
    }

    // free profile environment variables
    env->env = NULL;
    ke_free(spss_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void sps_create(struct prf_task_env *env, uint8_t conidx)
{
    struct spss_env_tag *spss_env = PRF_ENV_GET(SPS_SERVER, spss);
    ASSERT_ERR(conidx < BLE_CONNECTION_MAX);
    
    memset( ( void *)&ble_data_counter, 0, sizeof(struct sps_counter));
    
    spss_env->tx_busy_flag = false;
    spss_env->tx_flow_en = true;
    ke_state_set(spss_env->prf_env.prf_task, SPS_SERVER_ACTIVE);
     
}

 /**
 ****************************************************************************************
 * @brief Handles Disconnection
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 * @param[in]        reason     Detach reason
 ****************************************************************************************
 */
static void sps_cleanup(struct prf_task_env *env, uint8_t conidx, uint8_t reason)
{
    int att_idx;
    ASSERT_ERR(conidx < BLE_CONNECTION_MAX);
    struct spss_env_tag *spss_env = PRF_ENV_GET(SPS_SERVER, spss);

    // Find all ccc fields and clean them
    for (att_idx = 1; att_idx < SPSS_IDX_NB; att_idx++)
    {
        // Find only CCC characteristics
        if (sps_att_db[att_idx].uuid_size == ATT_UUID_16_LEN &&
            *(uint16_t *)sps_att_db[att_idx].uuid == ATT_DESC_CLIENT_CHAR_CFG)
        {
            // Clear CCC value
            sps_set_ccc_value(conidx, att_idx, 0);
        }
    }
     
    spss_env->tx_flow_en = false;
    //Go to idle state
    ke_state_set(spss_env->prf_env.prf_task, SPS_SERVER_IDLE);
        
}

/**
 ****************************************************************************************
 * @brief  Send flow control state to app
 * @param[in]   flow_ctrl  flow control (FLOW_ON, FLOW OFF)
 * @param[in]   conidx     length of data
 ****************************************************************************************
 */
void sps_server_indicate_tx_flow_ctrl(uint8_t flow_ctrl, uint8_t conidx)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    
    struct sps_server_tx_flow_ctrl_ind * ind = KE_MSG_ALLOC(SPS_SERVER_TX_FLOW_CTRL_IND,
                                                            prf_dst_task_get(&(sps_env->prf_env) ,conidx),
                                                            prf_src_task_get(&(sps_env->prf_env) ,conidx),
                                                            sps_server_tx_flow_ctrl_ind);

    ind->conidx = conidx;
    ind->flow_control_state = flow_ctrl;

    ke_msg_send(ind);
}

/**
 ****************************************************************************************
 * @brief  Forwards received data message to app
 * @param[in]   spss_env   spss environment pointer
 * @param[in]   msg        message pointer
 ****************************************************************************************
 */
void sps_server_data_receive(struct spss_env_tag *spss_env, void *msg )
{
    // Forward the message
    struct ke_msg * kmsg = ke_param2msg(msg);
    kmsg->dest_id = TASK_APP;
    kmsg->src_id  = prf_src_task_get(&(spss_env->prf_env), 0);
    kmsg->id      = SPS_SERVER_DATA_WRITE_IND;
    
    struct sps_val_write_ind *req =  ( struct sps_val_write_ind *) msg; 
    
    ke_msg_send(req);
}

/**
 ****************************************************************************************
 * @brief  Send error indication to app
 * @param[in]   conidx      connection index
 * @param[in]   status      error status
 * @param[in]   ind_msg_id  message id
 * @param[in]   msg_id      error message id
 ****************************************************************************************
 */

void sps_server_error_ind_send(uint8_t conidx, uint8_t status,
                               ke_msg_id_t ind_msg_id, ke_msg_id_t msg_id)
{
    struct prf_server_error_ind *ind = KE_MSG_ALLOC(ind_msg_id,
                                                    TASK_APP,
                                                    prf_get_task_from_id(TASK_ID_SPS_SERVER),
                                                    prf_server_error_ind);

    ind->status    = status;
    ind->msg_id    = msg_id;

    // send the message
    ke_msg_send(ind);
}

/**
 ****************************************************************************************
 * @brief  Send event to peer device, this function allocates a new message
 * @param[in]   att_idx     attribute index
 * @param[in]   conidx      connection index
 * @param[in]   p_data      pointer to data
 * @param[in]   data_len    data length
 ****************************************************************************************
 */

int sps_server_send_event( uint16_t att_idx, uint8_t conidx, uint8_t *p_data, uint16_t data_len )
{
    att_size_t length;
    const uint8_t *ccc_values;
    
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    
    if( conidx == GAP_INVALID_CONIDX )
    {
        return (KE_MSG_CONSUMED);
    }
    uint16_t cfg_hdl =get_cfg_handle( att_idx + sps_env->shdl);
    
    // Check if indications are enabled.
    sps_att_get_value(cfg_hdl - sps_env->shdl, &length, &ccc_values);
    
    if (ccc_values[conidx] != PRF_CLI_START_NTF)
    {
        return (KE_MSG_CONSUMED);
    } 
    // Allocate the GATT notification message
    struct gattc_send_evt_cmd *req = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,
                                                      KE_BUILD_ID(TASK_GATTC,conidx),
                                                      prf_src_task_get(&(sps_env->prf_env),0),
                                                      gattc_send_evt_cmd,
                                                      data_len);
    
    // Fill in the parameter structure
    req->operation = GATTC_NOTIFY;
    req->length = data_len;
    req->handle = sps_env->shdl + att_idx;
    
    memcpy(req->value, p_data, data_len);
    
    // Send the event
    ke_msg_send(req);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief  Forward data to peer device
 * @param[in]   msg       msg from upper layer
 * @param[in]   att_idx   attribute index
 * @param[in]   conidx    connection index
 * @param[in]   data_len    data length
 * @return true on success, false if notifications are not enabled or the connection
 * index is invalid
 ****************************************************************************************
 */

bool sps_server_send_data( void *msg, uint16_t att_idx, uint8_t conidx, uint16_t data_len )
{
    att_size_t length;
    const uint8_t *ccc_values;
    
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    
    if( conidx == GAP_INVALID_CONIDX )
    {
        return false;
    }
    uint16_t cfg_hdl =get_cfg_handle( att_idx + sps_env->shdl);
    
    // Check if indications are enabled.
    sps_att_get_value(cfg_hdl - sps_env->shdl, &length, &ccc_values);
    
    if (ccc_values[conidx] != PRF_CLI_START_NTF)
    {
        return false;
    } 
    // Allocate the GATT notification message
    struct ke_msg * kmsg = ke_param2msg(msg);
    kmsg->dest_id =    KE_BUILD_ID(TASK_GATTC,conidx);
    kmsg->src_id  =  prf_src_task_get(&(sps_env->prf_env),0);
    kmsg->id = GATTC_SEND_EVT_CMD;
    
    
    struct gattc_send_evt_cmd *req =  ( struct gattc_send_evt_cmd *) msg; 
    
    // Fill in the parameter structure
    req->operation = GATTC_NOTIFY;
    req->length = data_len;
    req->handle = sps_env->shdl + att_idx;
    
    //Send the event
    ke_msg_send(req);
    
    return true;
}
 
/**
 ****************************************************************************************
 * @brief Read characteristic value from.
 * Function checks if attribute exists, and if so return its length and pointer to data.
 * @param[in]  att_idx  Custom attribute index.
 * @param[out] length   Pointer to variable that receive length of the attribute.
 * @param[out] data     Pointer to variable that receive pointer characteristic value.
 * @return 0 on success, ATT_ERR_ATTRIBUTE_NOT_FOUND if there is no value for such attribyte.
 ****************************************************************************************
 */
static int sps_att_get_value(uint8_t att_idx, uint16_t *length, const uint8_t **data)
{
      struct spss_env_tag *spss_env = PRF_ENV_GET(SPS_SERVER, spss);
    // Check value in already present in service
    struct sps_val_elmt *val = (struct sps_val_elmt *) co_list_pick(&spss_env->values);
    ASSERT_ERR(data);
    ASSERT_ERR(length);

    // loop until value found
    while (val != NULL)
    {
        // value is present in service
        if (val->att_idx == att_idx)
        {
            *length = val->length;
            *data = val->data;
            break;
        }

        val = (struct sps_val_elmt *)val->hdr.next;
    }

    if (val == NULL)
    {
        *length = 0;
        *data = NULL;
    }
    return val ? 0 : ATT_ERR_ATTRIBUTE_NOT_FOUND;
}

/**
 ****************************************************************************************
 * @brief Stores characteristic value.
 * @param[in] att_idx  Custom attribut index.
 * @param[in] length   Value length.
 * @param[in] data     Pointer to value data.
 * @return 0 on success.
 ****************************************************************************************
 */
 
static int sps_att_set_value(uint8_t att_idx, uint16_t length, const uint8_t *data)
{
    struct spss_env_tag *spss_env = PRF_ENV_GET(SPS_SERVER, spss);
    // Check value in already present in service
    struct sps_val_elmt *val = (struct sps_val_elmt *) co_list_pick(&(spss_env->values));
    // loop until value found
    while (val != NULL)
    {
        // value is present in service
        if (val->att_idx == att_idx)
        {
            // Value present but size changed, free old value
            if (length != val->length)
            {
                co_list_extract(&spss_env->values, &val->hdr, 0);
                ke_free((void *)val);
                val = NULL;
            }
            break;
        }

        val = (struct sps_val_elmt *)val->hdr.next;
    }

    if (val == NULL)
    {
        // allocate value data
        val = (struct sps_val_elmt *) ke_malloc(sizeof(struct sps_val_elmt) + length, KE_MEM_ATT_DB);
        // insert value into the list
        co_list_push_back(&spss_env->values, &val->hdr);
    }
    val->att_idx = att_idx;
    val->length = length;
    memcpy(val->data, data, length);

    return 0;
}

/**
 ****************************************************************************************
 * @brief Sets initial values for all Clinet Characteristic Configurations.
 * @param[in]  att_db     Custom service attribute definition table.
 * @param[in]  max_nb_att Number of elements in att_db.
 ****************************************************************************************
 */
void sps_init_ccc_values(const struct attm_desc_128 *att_db, int max_nb_att)
{
    // Default values 0 means no notification
    uint8_t ccc_values[BLE_CONNECTION_MAX] = {0};
    int i;

    // Start form 1, skip service description
    for (i = 1; i < max_nb_att; i++)
    {
        // Find only CCC characteristics
        if (att_db[i].uuid_size == ATT_UUID_16_LEN &&
            *(uint16_t *)att_db[i].uuid == ATT_DESC_CLIENT_CHAR_CFG)
        {
            // Set default values for all possible connections
            sps_att_set_value(i, sizeof(ccc_values), ccc_values);
        }
    }
}

/**
 ****************************************************************************************
 * @brief  Gets att index from handle
 * @param[in]     handle      handle  
 * @param[in|out] att_idx   attribute index
 ****************************************************************************************
 */
uint8_t sps_get_att_idx(uint16_t handle, uint8_t *att_idx)
{
    struct spss_env_tag *spss_env = PRF_ENV_GET(SPS_SERVER, spss);
    uint8_t status = PRF_APP_ERROR;

    if (handle >= spss_env->shdl && handle < spss_env->shdl + spss_env->max_nb_att)
    {
        *att_idx = handle - spss_env->shdl;
        status = GAP_ERR_NO_ERROR;
    }

    return status;
}

/**
 ****************************************************************************************
 * @brief Read value of CCC for given attribute and connection index.
 * @param[in]  conidx   Connection index.
 * @param[in]  att_idx  Custom attribute index.
 * @return Value of CCC.
 ****************************************************************************************
 */
uint16_t sps_get_ccc_value(uint8_t conidx, uint8_t att_idx)
{
    uint16_t length;
    const uint8_t *value;
    uint16_t ccc_value;

    ASSERT_ERR(conidx < BLE_CONNECTION_MAX);

    sps_att_get_value(att_idx, &length, &value);
    ASSERT_ERR(length);
    ASSERT_ERR(value);

    ccc_value = value[conidx];

    return ccc_value;
}

/**
 ****************************************************************************************
 * @brief Set value of CCC for given attribute and connection index.
 * @param[in] conidx   Connection index.
 * @param[in] att_idx  CCC attribute index.
 * @param[in] cc       Value to store.
 ****************************************************************************************
 */
void sps_set_ccc_value(uint8_t conidx, uint8_t att_idx, uint16_t ccc)
{
    uint16_t length;
    const uint8_t *value;
    uint8_t new_value[BLE_CONNECTION_MAX];
    ASSERT_ERR(conidx < BLE_CONNECTION_MAX);

    sps_att_get_value(att_idx, &length, &value);
    ASSERT_ERR(length);
    ASSERT_ERR(value);
    memcpy(new_value, value, length);
    // For now there are only two valid values for ccc, store just one byte other is 0 anyway
    new_value[conidx] = (uint8_t)ccc;
    sps_att_set_value(att_idx, length, new_value);
}


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// SPS Task interface required by profile manager
const struct prf_task_cbs sps_itf =
{
        (prf_init_fnct) sps_init,
        sps_destroy,
        sps_create,
        sps_cleanup,
};

 /*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Retrieve SPS profile interface
 *
 * @return SPS service profile interface
 ****************************************************************************************
 */

const struct prf_task_cbs* spss_prf_itf_get(void)
{
    return &sps_itf;
}



#endif // BLE_SPS_SERVER

/// @} SPS_SERVER

