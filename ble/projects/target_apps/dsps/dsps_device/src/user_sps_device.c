/**
 ****************************************************************************************
 *
 * @file user_sps_device.c
 *
 * @brief DSPS Device project source code file .
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
#include "rwip_config.h"             // SW configuration

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_api.h"
#include "arch_console.h"
#include "gattc.h"
#include "user_sps_device.h"
#include "prf_utils.h"
#include "user_callback_config.h"
#include "local_event.h"
#include "setting.h"
#include "ble_proc.h"
#include "ble_scan_proc.h"
#include "app.h"



enum process_event_response user_spss_process_handler(ke_msg_id_t const msgid,
        void const *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id,
        enum ke_msg_status_tag *msg_ret);

timer_hnd features_timer;
uint8_t conn_idx;
timer_hnd connection_timer;
/*
 * EXTERNAL DEFINITIONS
 ****************************************************************************************
 */
extern struct sps_counter ble_data_counter;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
*/

/**
 ****************************************************************************************
 * @brief Sends a exchange MTU command
 * @param[in]   conidx Connection index
 * @return void
 ****************************************************************************************
 */
static void user_gattc_exc_mtu_cmd(uint8_t conidx)
{
    struct gattc_exc_mtu_cmd *cmd =  KE_MSG_ALLOC(GATTC_EXC_MTU_CMD,
                                     KE_BUILD_ID(TASK_GATTC, conidx),
                                     TASK_APP,
                                     gattc_exc_mtu_cmd);

    cmd->operation=GATTC_MTU_EXCH;
    cmd->seq_num = 0;
    ke_msg_send(cmd);
}
/**
 ****************************************************************************************
 * @brief  Gets the peer device fatures
 * @return void
 *
 ****************************************************************************************
 */
void get_features(void)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    sps_env->peer_supports_dle = 0;

    arch_printf("Send Get Features\r\n");
    struct gapc_get_info_cmd* info_cmd = KE_MSG_ALLOC(GAPC_GET_INFO_CMD,
                                         KE_BUILD_ID(TASK_GAPC,conn_idx),
                                         TASK_APP,
                                         gapc_get_info_cmd);
    // request peer device name.
    info_cmd->operation = GAPC_GET_PEER_FEATURES;

    // send command
    ke_msg_send(info_cmd);
}

/**
 ****************************************************************************************
 * @brief Handles connection event
 * @param[in]   connection_idx Connection index
 * @param[in]   param Parameters of connection
 * @return void
 ****************************************************************************************
 */
void user_on_connection(uint8_t connection_idx, struct gapc_connection_req_ind const *param)
{
    default_app_on_connection(connection_idx, param);
	if(!timer_isTimerStart(TIMER_SCAN_TIMEOUT)) 
	{
		user_scan_start();
		timer_start(TIMER_SCAN_TIMEOUT, USER_SCAN_TIMEOUT_MS, ble_scan_timeout_callback);
	}

    conn_idx = connection_idx;

    features_timer = app_easy_timer(60, get_features);
    setting.isconnected = 1;  
    event_onConnection();
    event_setConnectionID(connection_idx);
    arch_printf("Device connected\r\n");
}

/**
 ****************************************************************************************
 * @brief Handles disconnection event
 * @param[in]   param Parameters of disconnect message
 * @return void
 ****************************************************************************************
 */
void user_on_disconnect( struct gapc_disconnect_ind const *param )
{
    setting.isconnected = 0;
    event_onDisconnection();
	ble_stop_scan();//断开连接时,确保可以进入广播模式
	timer_stop(TIMER_SCAN_TIMEOUT);
    default_app_on_disconnect(param);
    arch_printf("Device disconnected, reason %i\r\n", (int)param->reason);
}

/**
 ****************************************************************************************
 * @brief Handles connection failure
 * @return void
 ****************************************************************************************
 */
void user_on_connect_failed (void)
{
    ASSERT_WARNING(0);
}

/**
 ****************************************************************************************
 * @brief Sends app_gapm_cancel_msg message
 *
 * @return void
 ****************************************************************************************
 */
static void user_gapm_cancel(void)
{
    // Disable Advertising
    struct gapm_cancel_cmd *cmd = app_gapm_cancel_msg_create();
    // Send the message
    app_gapm_cancel_msg_send(cmd);
}

/**
 ****************************************************************************************
 * @brief Sends gapm_start_scan_cmd message
 *
 * @return void
 ****************************************************************************************
 */
void user_scan_start(void)
{
    struct gapm_start_scan_cmd* cmd = KE_MSG_ALLOC(GAPM_START_SCAN_CMD,
                                      TASK_GAPM, TASK_APP,
                                      gapm_start_scan_cmd);

    cmd->op.code = user_scan_conf.code;
    cmd->op.addr_src = user_scan_conf.addr_src;
    cmd->op.state = 0;
    
    cmd->interval = user_scan_conf.interval;
    cmd->window = user_scan_conf.window;
    
    cmd->mode = user_scan_conf.mode;
    cmd->filt_policy = user_scan_conf.filt_policy;
    cmd->filter_duplic = user_scan_conf.filter_duplic;

    // Send the message
    ke_msg_send(cmd);
    // We are now connectable
    ke_state_set(TASK_APP, APP_CONNECTABLE);
}

/**
 ****************************************************************************************
 * @brief Called upon scan completion
 * @return void
 ****************************************************************************************
 */
void user_on_scanning_completed (uint8_t status)//当扫描到道钉则进入
{
//    if(BLE_MODE_SCAN == setting.mode)
//    {
//        //如果是钥匙PKE模式, 持续进行扫描
//        user_scan_start();
//        timer_stop(TIMER_SCAN_TIMEOUT);
//    }
}

/*
 * MAIN LOOP CALLBACKS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Called on device initialization
 * @return void
 ****************************************************************************************
 */
void user_on_init(void)
{
    // SPS application initialization
    arch_printf("SPSS Init\r\n");
    default_app_on_init();
}

/**
 ****************************************************************************************
 * @brief Called on database initialization complete
 * @return void
 ****************************************************************************************
 */
void user_on_db_init_complete(void)
{
    if(setting.mode == BLE_MODE_ADV)
    {
        CALLBACK_ARGS_0(user_default_app_operations.default_operation_adv)
    }
    else
    {
        user_scan_start();
    }

    // Start user timer
    app_timer_set( APP_TIMER_USER_MES, TASK_APP, 1);//10ms
}

/**
 ****************************************************************************************
 * @brief BLE statistics print
 * @return void
 ****************************************************************************************
 */
#if defined(CFG_BLE_METRICS) && defined(CFG_PRINTF)
void user_statistics(void)
{
    uint8_t ble_evt;
    uint8_t  sys_state=ke_state_get(TASK_APP);
    static uint8_t app_last_ble_evt=0;
    int16_t rx_rssi;

    if ( sys_state != APP_CONNECTED)
        return;

    ble_evt = arch_last_rwble_evt_get();
    if (ble_evt != app_last_ble_evt)
    {
        app_last_ble_evt = ble_evt;
        if (app_last_ble_evt == BLE_EVT_END )
        {
            if (!(metrics.rx_pkt%40) )
            {
                rx_rssi = ((474 * metrics.rx_rssi) /1000)-112;
                arch_printf("NofPkt: %i NofErr: %i RSSI: %i CRC: %i SYNC:%i NESN:%i SN:%i\r\n", (int) metrics.rx_pkt, (int)metrics.rx_err, (int)rx_rssi,  (int) metrics.rx_err_crc, (int)metrics.rx_err_sync, (int)metrics.rx_nesn_err, (int)metrics.rx_sn_err );
                arch_printf("NofRxData: %i\r\n",  (int)ble_data_counter.spss_ble_rx_data_bytes );
            }
        }
    }
    return;
}
#endif
/**
 ****************************************************************************************
 * @brief Called on system power up
 * @return GOTO_SLEEP or KEEP_POWERED
 ****************************************************************************************
 */

extern bool user_sps_sleep_flow_off;
arch_main_loop_callback_ret_t user_on_system_powered(void)
{
    //user_sps_sleep_restore();
    //user_ble_pull(true, NULL);
    //#if defined(CFG_BLE_METRICS) && defined(CFG_PRINTF)
    //user_statistics();
    //#endif
    return GOTO_SLEEP;
}

/**
 ****************************************************************************************
 * @brief Called before entering sleep
 * @return void
 ****************************************************************************************
 */
void user_before_sleep(void)
{
    //user_sps_sleep_check();
    arch_disable_sleep();
}

/**
 ****************************************************************************************
 * @brief Called on the reception of GAPC_LE_PKT_SIZE_IND
 * @return void
 ****************************************************************************************
 */
void user_on_data_length_change(struct gapc_le_pkt_size_ind *param, uint16_t src_id)
{
    uint8_t conidx = KE_IDX_GET(src_id);
    user_gattc_exc_mtu_cmd(conidx);
    arch_printf("LE PKT SIZE TX %i %i RX %i %i\r\n", (int)param->max_tx_octets, (int)param->max_tx_time, (int)param->max_rx_octets, (int)param->max_rx_time);
}

/**
 ****************************************************************************************
 * @brief From the features indication msg it checks if DLE is supported
 * @param[in]   gapc_peer_features_ind pointer to features message indication parameters
 * @return void
 ****************************************************************************************
 */
void check_features(struct gapc_peer_features_ind *param )
{
    volatile uint8_t features1 =   *(uint8_t *)&param->features[0];
    volatile uint8_t features2 =   *(uint8_t *)&param->features[1];
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    if( features1 & 0x20 )
    {
        arch_printf("DLE ON\r\n");
        sps_env->peer_supports_dle = 1;
    }
    else
    {
        arch_printf("DLE OFF\r\n");
        sps_env->peer_supports_dle = 0;
    }
}

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
                          ke_task_id_t const src_id)
{
    struct gapc_cmp_evt const *cmp_param = param;
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    uint8_t conidx = KE_IDX_GET(src_id);
    switch(msgid)
    {
        case GAPC_PEER_FEATURES_IND:
            arch_printf("GAPC_PEER_FEATURES_IND\r\n");
            check_features( (struct gapc_peer_features_ind *)param);
            arch_printf("PARAM UPDATE START\r\n");
            app_easy_gap_param_update_start(conidx);
            break;
        case GAPC_CMP_EVT:
            switch(cmp_param->operation)
            {
                case GAPC_GET_PEER_FEATURES:
                    if( cmp_param->status == GAP_ERR_NO_ERROR )
                    {
                        arch_printf("GAPC_PEER_FEATURES_IND OK\r\n");
                    }
                    else if ( cmp_param->status == LL_ERR_UNSUPPORTED_REMOTE_FEATURE )
                    {
                        sps_env->peer_supports_dle = 0;
                        arch_printf("GAPC_PEER_FEATURES_IND UNSUPPORTED, DLE OFF\r\n");
                        arch_printf("PARAM UPDATE START\r\n");
                        app_easy_gap_param_update_start(conidx);
                    }
                    else
                    {
                        sps_env->peer_supports_dle = 0;
                        arch_printf("GAPC_PEER_FEATURES_IND UKN STATUS, DLE OFF\r\n");
                        arch_printf("PARAM UPDATE START\r\n");
                        app_easy_gap_param_update_start(conidx);
                    }

                    break;
                default:
                    arch_printf("xxxx %i\r\n",(int)cmp_param->operation);
                    break;
            }
            break;
        case GAPC_PARAM_UPDATE_REQ_IND:
            arch_printf("GAPC_PARAM_UPDATE_REQ_IND msgid %i\r\n",(int)msgid);
            break;
        default:
            arch_printf("other msgid %i\r\n",(int)msgid);
            break;

    }
}

/**
 ****************************************************************************************
 * @brief Callback of the GAPC_UPDATE_PARAMS (parameter update is complete)
 * @param[in]   src_id the source id of the task
 * @return void
 ****************************************************************************************
 */
void user_on_update_params_complete(uint16_t src_id)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    uint8_t conidx = KE_IDX_GET(src_id);

    arch_printf("PARAM UPDATE COMPLETE\r\n");
#ifdef USE_DLE
    if( sps_env->peer_supports_dle )
    {
        arch_printf("SEND LEN REQ\r\n");
        app_easy_gap_set_data_packet_length(conidx, 251, 2120);
    }
    else
#endif
        user_gattc_exc_mtu_cmd(conidx);
}

/**
 ****************************************************************************************
 * @brief Callback of the GAPC_UPDATE_PARAMS rejection (parameter update is rejected)
 * @param[in]   status status of the message
 * @param[in]   src_id the source id of the task
 * @return void
 ****************************************************************************************
 */
void user_on_update_params_rejected(uint8_t status,  uint16_t src_id)
{
    struct spss_env_tag *sps_env = PRF_ENV_GET(SPS_SERVER, spss);
    uint8_t conidx = KE_IDX_GET(src_id);
    arch_printf("PARAM UPDATE REJECTED\r\n");
#ifdef USE_DLE
    if( sps_env->peer_supports_dle )
    {
        arch_printf("SEND LEN REQ\r\n");
        app_easy_gap_set_data_packet_length(conidx, 251, 2120);
    }
    else
#endif
        user_gattc_exc_mtu_cmd(conidx);

}

void user_adv_report_ind(struct gapm_adv_report_ind const *param)//扫描到广播信息，对信息进行解析
{
    ble_scan_cb((ST_SCAN_INFO *)param);
}

void user_on_adv_undirect_complete(uint8_t status)
{
    //广播完成了
    app_easy_gap_advertise_with_timeout_stop();

    //启动 130ms 的扫描
    if(!timer_isTimerStart(TIMER_SCAN_TIMEOUT))
    {
        ble_start_scan();
        timer_start(TIMER_SCAN_TIMEOUT, USER_SCAN_TIMEOUT_MS, ble_scan_timeout_callback);
    }
}

void user_on_set_dev_config_complete(void)
{
    // Add the first required service in the database
    if (app_db_init_start())
    {
        // No more service to add, start advertising
        setting.isconnected = 0;
        if(BLE_MODE_ADV == setting.mode)
        {
            // No service to add in the DB -> Start Advertising
            CALLBACK_ARGS_0(user_default_app_operations.default_operation_adv);
        }
//        else
//        {
//            //蓝牙钥匙PKE模式, 执行长时间扫描
//            user_scan_start();
//            timer_stop(TIMER_SCAN_TIMEOUT);
//        }
        // Start user timer
        app_timer_set( APP_TIMER_USER_MES, TASK_APP, 1);//10ms
    }
}

/// @} APP
