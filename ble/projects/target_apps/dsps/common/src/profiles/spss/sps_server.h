/**
 ****************************************************************************************
 *
 * @file sps_server.h
 *
 * @brief Header file - SPSS
 *
 * Copyright (C) 2016 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef SPS_SERVER_H_
#define SPS_SERVER_H_


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#if (BLE_SPS_SERVER)

#include <stdint.h>
#include "prf_types.h"
#include "prf.h"
#include "attm_db_128.h"

/*
 * DEFINES
 ****************************************************************************************
 */
 
 #define SPSS_IDX_MAX        (1)

///Attribute Table Indexes
enum
{
    SPSS_TX_DATA_CHAR,
    SPSS_RX_DATA_CHAR,
    SPSS_FLOW_CTRL_CHAR,

    SPSS_CHAR_MAX,
};

typedef enum flow_ctrl_states
{
    FLOW_ON     = (uint8_t)0x01,
    FLOW_OFF    = (uint8_t)0x02,
}flow_ctrl_state_t;


/*
 * STRUCTURES
 ****************************************************************************************
 */

///SPS Server environment variable
struct spss_env_tag
{
    /// profile environment
    prf_env_t prf_env;
    /// Service Start Handle
    uint16_t shdl;
    /// To store the DB max number of attributes
    uint8_t max_nb_att;
    /// On-going operation
    struct ke_msg *operation;
    
      /// Peer supports DLE
    uint8_t peer_supports_dle;  

    /// Cursor on connection used to notify peer devices
    uint8_t cursor;
    /// CCC handle index, used during notification/indication busy state
    uint8_t ccc_idx;

    /// List of values set by application
    struct co_list values;
    /// CUSTS1 task state
    ke_state_t state[SPSS_IDX_MAX];
    
    /// Flow control states
    bool tx_flow_en;
    bool rx_flow_en;
        
    /// Updated mtu
    uint16_t mtu;
    uint16_t tx_size;
    uint16_t tx_wait_level;
    /// Pending TX
    bool pending_tx;
    /// Notification completion remaining
    uint8_t pending_ntf_cmp;
    /// Pending notification of data tx
    bool pending_tx_ntf_cmp;
        
    bool tx_busy_flag;

};

struct spss_db_cfg
{
    ///max number of casts1 service characteristics
    uint8_t max_nb_att;
    uint8_t *att_tbl;
    uint8_t *cfg_flag;

    ///Database configuration
    uint16_t features;
};

struct sps_val_elmt
{
    /// list element header
    struct co_list_hdr hdr;
    /// value identifier
    uint8_t att_idx;
    /// value length
    uint8_t length;
    /// value data
    uint8_t data[__ARRAY_EMPTY];
};

struct sps_counter 
{
    uint32_t spss_ble_rx_data_bytes;
    uint32_t spss_ble_tx_data_bytes;
    
    uint32_t spss_ble_tx_ntf_ok;    
    uint32_t spss_ble_tx_ntf_fail;    
    
    uint32_t spss_ble_tx_cmp;
    uint32_t spss_ble_tx_cmp_ok;  
    uint32_t spss_ble_tx_cmp_fail;  
};  

/*
 *  SPS PROFILE ATTRIBUTES VALUES DECLARATION
 ****************************************************************************************
 */


/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

//extern const struct attm_desc_128 sps_att_db[SPSS_IDX_NB];

extern struct spss_env_tag spss_env;

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

 /**
 ****************************************************************************************
 * @brief Create and initialize the SPS database and environment
 ****************************************************************************************
 */
uint8_t sps_init(struct prf_task_env *env, uint16_t *start_hdl, uint16_t app_task, uint8_t sec_lvl, struct spss_db_cfg *params);

/**
 ****************************************************************************************
 * @brief  Send data to app
 * @param[in]        data       Pointer to data
 * @param[in]        length     Length of data
 * @param[in]        conidx     Connection Index
 ****************************************************************************************
 */
void sps_server_indicate_data_rx(const uint8_t *data, uint16_t length, uint8_t conidx);

/**
 ****************************************************************************************
 * @brief  Send flow control state to app
 * @param[in]   flow_ctrl  flow control (FLOW_ON, FLOW OFF)
 * @param[in]   conidx     length of data
 ****************************************************************************************
 */
void sps_server_indicate_tx_flow_ctrl(uint8_t flow_ctrl, uint8_t conidx);

/**
 ****************************************************************************************
 * @brief  Send event to peer device, this function allocates a new message
 * @param[in]   att_idx     attribute index
 * @param[in]   conidx      connection index
 * @param[in]   p_data      pointer to data
 * @param[in]   data_len    data length
 ****************************************************************************************
 */
int sps_server_send_event( uint16_t att_idx, uint8_t conidx, uint8_t *p_data, uint16_t data_len );

/**
 ****************************************************************************************
 * @brief Set value of CCC for given attribute and connection index.
 * @param[in] conidx   Connection index.
 * @param[in] att_idx  CCC attribute index.
 * @param[in] cc       Value to store.
 ****************************************************************************************
 */
void sps_set_ccc_value(uint8_t conidx, uint8_t att_idx, uint16_t ccc);
/**
 ****************************************************************************************
 * @brief Sets initial values for all Clinet Characteristic Configurations.
 * @param[in]  att_db     Custom service attribute definition table.
 * @param[in]  max_nb_att Number of elements in att_db.
 ****************************************************************************************
 */
void sps_init_ccc_values(const struct attm_desc_128 *att_db, int max_nb_att);

/**
 ****************************************************************************************
 * @brief Retrieve SPS profile interface
 *
 * @return SPS service profile interface
 ****************************************************************************************
 */
 
const struct prf_task_cbs* spss_prf_itf_get(void);

/**
 ****************************************************************************************
 * @brief  Gets att index from handle
 ****************************************************************************************
 */
uint8_t sps_get_att_idx(uint16_t handle, uint8_t *att_idx);
/**
 ****************************************************************************************
 * @brief Read value of CCC for given attribute and connection index.
 * @param[in]  conidx   Connection index.
 * @param[in]  att_idx  Custom attribute index.
 * @return Value of CCC.
 ****************************************************************************************
 */
uint16_t sps_get_ccc_value(uint8_t conidx, uint8_t att_idx);
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
static int sps_att_get_value(uint8_t att_idx, uint16_t *length, const uint8_t **data);
/**
 ****************************************************************************************
 * @brief  Send error indication to app
 * @param[in]   conidx      connection index
 * @param[in]   status      error status
 * @param[in]   ind_msg_id  message id
 * @param[in]   msg_id      error message id
 ****************************************************************************************
 */
void sps_server_error_ind_send(uint8_t conidx, uint8_t status, ke_msg_id_t ind_msg_id, ke_msg_id_t msg_id);

/**
 ****************************************************************************************
 * @brief  Forward data to peer device
 * @param[in]   msg         msg from upper layer
 * @param[in]   att_idx     attribute index
 * @param[in]   conidx      connection index
 * @param[in]   data_len    data length
 * @return true on success, false if notifications are not enabled or the connection
 * index is invalid
 ****************************************************************************************
 */
bool sps_server_send_data( void *msg, uint16_t att_idx, uint8_t conidx, uint16_t data_len );
/**
 ****************************************************************************************
 * @brief  Forwards received data message to app
 * @param[in]   spss_env   spss environment pointer
 * @param[in]   msg        message pointer
 ****************************************************************************************
 */
void sps_server_data_receive(struct spss_env_tag *spss_env, void *msg );

#endif /* BLE_SPS_SERVER */

/// @} SPS_SERVER_DEV

#endif // SPS_SERVER_H_
