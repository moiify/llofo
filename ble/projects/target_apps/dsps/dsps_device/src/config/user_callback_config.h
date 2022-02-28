/**
 ****************************************************************************************
 *
 * @file user_callback_config.h
 *
 * @brief Callback functions configuration file.
 *
 * Copyright (C) 2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _USER_CALLBACK_CONFIG_H_
#define _USER_CALLBACK_CONFIG_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
 
#include "app_api.h"
#include "app_bass.h"
#include "app_suotar.h"
#include "app_callback.h"
#include "app_prf_types.h"
#include "user_spss.h"
#include "user_spss_task.h"

#include "user_sps_device.h"
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Function to be called on the advertising completion event.
 * @param[in] uint8_t GAP Error code
 * @return void
 ****************************************************************************************
 */
void app_advertise_complete(const uint8_t);

/**
 ****************************************************************************************
 * @brief SUOTAR session start or stop event handler.
 * @param[in] suotar_event SUOTAR_START/SUOTAR_STOP
 * @return void
 ****************************************************************************************
 */
void on_suotar_status_change(const uint8_t suotar_event);


/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

#if (BLE_BATT_SERVER)
static const struct app_bass_cb user_app_bass_cb = {
    .on_batt_level_upd_rsp      = NULL,
    .on_batt_level_ntf_cfg_ind  = NULL,
};
#endif

#if (BLE_FINDME_TARGET)
static const struct app_findt_cb user_app_findt_cb = {
    .on_findt_alert_ind         = default_findt_alert_ind_handler,
};
#endif

#if (BLE_PROX_REPORTER)
static const struct app_proxr_cb user_app_proxr_cb = {
    .on_proxr_alert_ind      = default_proxr_alert_ind_handler,
};
#endif

#if (BLE_SUOTA_RECEIVER)
static const struct app_suotar_cb user_app_suotar_cb = {
    .on_suotar_status_change = on_suotar_status_change,
};
#endif

static const struct app_callbacks user_app_callbacks = {
    .app_on_connection              = user_on_connection,
    .app_on_disconnect              = user_on_disconnect,
    .app_on_update_params_rejected  = user_on_update_params_rejected,
    .app_on_update_params_complete  = user_on_update_params_complete,
    .app_on_set_dev_config_complete = user_on_set_dev_config_complete,
    .app_on_adv_nonconn_complete    = NULL,
    .app_on_adv_undirect_complete   = user_on_adv_undirect_complete,
    .app_on_adv_direct_complete     = NULL,
    .app_on_db_init_complete        = user_on_db_init_complete,
    .app_on_scanning_completed      = user_on_scanning_completed,
    .app_on_adv_report_ind          = user_adv_report_ind,
    .app_on_get_dev_appearance      = default_app_on_get_dev_appearance,
    .app_on_get_dev_slv_pref_params = default_app_on_get_dev_slv_pref_params,
    .app_on_set_dev_info            = default_app_on_set_dev_info,
#ifdef USE_DLE
    .app_on_data_length_change      = user_on_data_length_change,
#else
    .app_on_data_length_change      = NULL,
#endif
    .app_on_update_params_request   = default_app_update_params_request,
#if (BLE_APP_SEC)
    .app_on_pairing_request         = default_app_on_pairing_request,
    .app_on_tk_exch_nomitm          = default_app_on_tk_exch_nomitm,
    .app_on_irk_exch                = NULL,
    .app_on_csrk_exch               = default_app_on_csrk_exch,
    .app_on_ltk_exch                = default_app_on_ltk_exch,
    .app_on_pairing_succeded        = NULL,
    .app_on_encrypt_ind             = NULL,
    .app_on_mitm_passcode_req       = NULL,
    .app_on_encrypt_req_ind         = default_app_on_encrypt_req_ind,
    .app_on_security_req_ind        = NULL,
#endif // (BLE_APP_SEC)
};

static const struct default_app_operations user_default_app_operations = {
    .default_operation_adv = default_advertise_operation,
};

static void (*const app_process_catch_rest_cb)(ke_msg_id_t const msgid, void const *param,
                                         ke_task_id_t const dest_id, ke_task_id_t const src_id) = user_catch_rest_hndl;

static const struct arch_main_loop_callbacks user_app_main_loop_callbacks = {
    .app_on_init            = user_on_init,
    
    // By default the watchdog timer is reloaded and resumed when the system wakes up.
    // The user has to take into account the watchdog timer handling (keep it running, 
    // freeze it, reload it, resume it, etc), when the app_on_ble_powered() is being 
    // called and may potentially affect the main loop.
    .app_on_ble_powered     = NULL,
    
    // By default the watchdog timer is reloaded and resumed when the system wakes up.
    // The user has to take into account the watchdog timer handling (keep it running, 
    // freeze it, reload it, resume it, etc), when the app_on_system_powered() is being 
    // called and may potentially affect the main loop.
    .app_on_system_powered  = user_on_system_powered,
    
    .app_before_sleep       = user_before_sleep,
    .app_validate_sleep     = NULL,
    .app_going_to_sleep     = NULL,
    .app_resume_from_sleep  = NULL,
};

//place in this structure the app_<profile>_db_create and app_<profile>_enable functions
//for SIG profiles that do not have this function already implemented in the SDK
//or if you want to override the functionality. Check the prf_func array in the SDK
//for your reference of which profiles are supported.
static const struct prf_func_callbacks user_prf_funcs[] =
{
    {TASK_ID_INVALID,    NULL, NULL}   // DO NOT MOVE. Must always be last
};

#endif // _USER_CALLBACK_CONFIG_H_
