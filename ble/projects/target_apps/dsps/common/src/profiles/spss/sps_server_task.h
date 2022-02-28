/**
 ****************************************************************************************
 *
 * @file sps_server_task.h
 *
 * @brief Serial Port Service Device profile task declaration
 *
 * Copyright (C) 2016 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */
 
#ifndef SPS_SERVER_TASK_H_
#define SPS_SERVER_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup SPS_SERVERTASK Serial Port Service Device Task
 * @ingroup SPS_SERVER
 * @brief Serial Port Service Device task implementation
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
 
#if (BLE_SPS_SERVER)

#include <stdint.h>
#include "ke_task.h"


/*
 * INSTANCES
 ****************************************************************************************
 */
/// Maximum number of instances of the SPS_SERVER task
#define SPS_SERVER_IDX_MAX              (1)

/*
 * STATES
 ****************************************************************************************
 */
/// Possible states of the SPS_SERVER task
enum
{
    /// DISABLED state
    SPS_SERVER_DISABLED,
    /// IDLE state
    SPS_SERVER_IDLE,
    /// ACTIVE state
    SPS_SERVER_ACTIVE,
    
    /// Number of states.
    SPS_SERVER_STATE_MAX
};

/*
 * MESSAGES
 ****************************************************************************************
 */
/// Message API of the SPS_SERVER task
enum
{
    /// Create SPS database request
    SPS_SERVER_CREATE_DB_REQ = KE_FIRST_MSG(TASK_ID_SPS_SERVER),
    
    /// Create SPS database response
    SPS_SERVER_CREATE_DB_CFM,
    
    /// Enables the Serial Port Service Device profile. The profile has to be enabled only
    /// once a connection has been established by the application
    SPS_SERVER_ENABLE_REQ,
    
    //Enable confirmation message
    SPS_SERVER_ENABLE_CFM,
    
    /// Request to transmit data
    SPS_SERVER_DATA_TX_REQ,
    
    /// Confirm that data has been sent
    SPS_SERVER_DATA_TX_CFM,
    
    /// Send value to app
    SPS_SERVER_DATA_WRITE_IND,
    
    /// Send flow control status
    SPS_SERVER_RX_FLOW_CTRL_REQ,
    
    /// Indicate flow control state
    SPS_SERVER_TX_FLOW_CTRL_IND,
    
    ///Profile error report
    SPS_SERVER_ERROR_IND,
};

///Parameters of the @ref SPS_SERVER_CREATE_DB_REQ message
struct sps_server_create_db_req
{
    ///Connection handle
    uint16_t conhdl;
    ///SPS Service start handle (0 = automatic handle allocation)
    uint16_t start_hdl;
};

///Parameters of the @ref SPS_SERVER_CREATE_DB_CFM message
struct sps_server_create_db_cfm
{
    ///Connection handle
    uint16_t conhdl;
    ///Status
    uint8_t status;
};

///Parameters of the @ref SPS_SERVER_ENABLE_REQ message
struct sps_server_enable_req
{
    /// Connection handle
    uint16_t conidx;
    /// security level: b0= nothing, b1=unauthenticated, b2=authenticated, b3=authorized; b1 or b2 and b3 can go together
    uint8_t sec_lvl;
};

///Parameters of the @ref SPS_SERVER_ENABLE_CFM message
struct sps_server_enable_cfm
{
    ///Status
    uint8_t status;
};

/// Send an event to peer device
///WARNING, DO NOT ALTER THIS STRUCT, IT SHOULD BE COMPATIBLE WITH gattc_send_evt_cmd struct
struct sps_server_data_tx_req
{
    /// Request type (notification / indication)
    uint8_t operation;
    /// operation sequence number
    uint16_t seq_num;
    /// characteristic handle
    uint16_t handle;
    /// length of packet to send
    uint16_t length;
    /// data value
    uint8_t  data[__ARRAY_EMPTY];
};

///Parameters of the @ref SPS_SERVER_DATA_TX_CFM message
struct sps_server_data_tx_cfm
{
    ///Connection handle
    uint16_t conhdl;
    ///Status
    uint8_t status;
};

 
///Parameters of the @ref SPS_SERVER_RX_FLOW_CTRL_REQ message
struct sps_server_rx_flow_ctrl_req
{
    ///Connection handle
    uint16_t conhdl;
    // flow control state
    uint8_t flow_control_state;
};

///Parameters of the @ref SPS_SERVER_TX_FLOW_CTRL_IND message
struct sps_server_tx_flow_ctrl_ind
{
    ///Connection handle
    uint16_t conidx;
    // flow control state
    uint8_t flow_control_state;
};

/// Parameters of the @ref SPS_DATA_WRITE_IND massage
struct sps_val_write_ind
{
    ///WARNING, DO NOT ALTER THIS STRUCT, IT SHOULD BE COMPATIBLE WITH gattc_write_req_ind struct
    /// Handle of the attribute that has to be written
    uint16_t handle;
    /// offset at which the data has to be written
    uint16_t offset;
    /// Data length to be written
    uint16_t length;
    /// Data to be written in attribute database
    uint8_t  data[__ARRAY_EMPTY];
};

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler sps_server_default_handler;
 
#endif //BLE_SPS_SERVER

/// @} SPS_SERVERTASK

#endif // SPS_SERVER_TASK_H_
