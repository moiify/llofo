/** ============================================================================
 *  @file       sharebike.h
 *
 *  @brief      Generic interface for share bike company
 *
 * 
 *  @endcode
 *  ============================================================================
 */

#ifndef BLE_GAP_ADV_MIN_SIZE
#define  BLE_GAP_ADV_MIN_SIZE             4
#endif

#ifndef BLE_GAP_ADV_MAX_SIZE
#define BLE_GAP_ADV_MAX_SIZE 31
#endif

#ifndef BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA
#define BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA          0xFF /**< Manufacturer Specific Data. */
#endif

#ifndef BIKE_COMPANY_IDENTIFIER_CP1
#define BIKE_COMPANY_IDENTIFIER_CP1 0x0059       // ??????
#endif

typedef struct
{
    char isLocationPile;
    int RssiReference;
		char mac[6];
}sharebike_t;

typedef struct
{
    unsigned char len; // type  ? val ????????
    unsigned char type;
    unsigned char val[BLE_GAP_ADV_MIN_SIZE - 2];
} __adv_data_node_short_t;

typedef struct
{
    unsigned char len; // type  ? val ????????
    unsigned char type;
    unsigned char val[BLE_GAP_ADV_MAX_SIZE - 2];
} __adv_data_node_t;

typedef __packed struct
{
    unsigned short id;// 5800
    unsigned char status; // ???
    unsigned int  qr_code; // ???
} __manufacturer_specific_data_t;


/*
    this is share bike use interface.
*/
/*********************************************************************
 * @fn      shareBike_permit
 *
 * @brief   This function provides access services of interface for shared bicycles 
 *					If the return is successful, it means scanning to the electronic post. else,then failed.
 *
 * @param   p_adv_report       advertising data
 *          dataLen         		advertising data len
 *          info                Get info of location pile
 * @return  0   success 
 *          -1  error  
 */
extern int  shareBike_permit(unsigned char * p_adv_report,unsigned char dataLen,sharebike_t *info);
