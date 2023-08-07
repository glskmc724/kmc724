#include <stdio.h>

#include "myble.h"
#include "imu.h"

#if (CYBLE_GAP_ROLE_CENTRAL)
static uint8 peripheral_addr[CYBLE_GAP_BD_ADDR_SIZE] = { 0x01, 0x00, 0x00, 0x50, 0xA0, 0x00 };
static CYBLE_GAP_BD_ADDR_T bd_addr;
#endif
#if (CYBLE_GAP_ROLE_PERIPHERAL)
uint8 ble_mtu_rsp = FALSE;
#endif
#if (CYBLE_GAP_ROLE_CENTRAL)
uint8 ble_mtu_req = TRUE;
#endif
extern uint8* ble_mtu_recv;
static CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T recv;

#if (CYBLE_GAP_ROLE_CENTRAL)
static uint8 is_peripheral(uint8* addr);
#endif

void ble_callback(uint32 evt, void* param)
{
    uint8 error_code;
    
    print_ble_state(evt);
    
    switch (evt)
    {
        case CYBLE_EVT_STACK_ON:
#if (CYBLE_GAP_ROLE_CENTRAL)
            CyBle_GapcStartScan(CYBLE_SCANNING_FAST);
#endif
#if (CYBLE_GAP_ROLE_PERIPHERAL)
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
#endif
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            error_code = (*(uint8*)param);
            print_error_code(error_code);
#if (CYBLE_GAP_ROLE_CENTRAL)
            CyBle_GapcStartScan(CYBLE_SCANNING_FAST);
#endif
#if (CYBLE_GAP_ROLE_PERIPHERAL)
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
#endif
            break;
#if (CYBLE_GAP_ROLE_CENTRAL)
        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
            printf("CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT\r\n");
            CYBLE_GAPC_ADV_REPORT_T adv_report;
            memcpy(&adv_report, param, sizeof(CYBLE_GAPC_ADV_REPORT_T));
        
            if (is_peripheral(adv_report.peerBdAddr) == TRUE)
            {
                CyBle_GapcStopScan();
                
                memcpy(bd_addr.bdAddr, adv_report.peerBdAddr, CYBLE_GAP_BD_ADDR_SIZE);
                bd_addr.type = adv_report.peerAddrType;
            }
            break;
        case CYBLE_EVT_GAPC_SCAN_START_STOP:
            printf("CYBLE_EVT_GAPC_SCAN_START_STOP\r\n");
            
            if (cyBle_state == CYBLE_STATE_DISCONNECTED)
            {
                printf("Connect to ");
                for (uint8 i = 0; i < CYBLE_GAP_BD_ADDR_SIZE; i++)
                {
                    printf("%X ", bd_addr.bdAddr[CYBLE_GAP_BD_ADDR_SIZE - i - 1]);
                }
                printf("\r\n");
                printf("result: %X\r\n", CyBle_GapcConnectDevice(&bd_addr));
            }
            break;
#endif
        case CYBLE_EVT_GATT_CONNECT_IND:
            break;
        case CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE:
            printf("CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE\r\n");
#if (CYBLE_GAP_ROLE_CENTRAL)
            CyBle_GapAuthReq(cyBle_connHandle.bdHandle, &cyBle_authInfo);
#endif
            break;
        case CYBLE_EVT_GAP_AUTH_COMPLETE:
#if (CYBLE_GAP_ROLE_PERIPHERAL)
            CyBle_GattcStartDiscovery(cyBle_connHandle);
#endif
            break;
        case CYBLE_EVT_GATTC_DISCOVERY_COMPLETE:
#if (CYBLE_GAP_ROLE_PERIPHERAL)
            CyBle_GattcExchangeMtuReq(cyBle_connHandle, 256);
#endif
            break;
        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
#if (CYBLE_GAP_ROLE_CENTRAL)
            ble_mtu_req = TRUE;
#endif
            break;
        case CYBLE_EVT_GATTC_XCHNG_MTU_RSP:
            printf("TEST\r\n");
#if (CYBLE_GAP_ROLE_PERIPHERAL)
            ble_mtu_rsp = TRUE;
#endif
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            CyBle_GattsWriteRsp(cyBle_connHandle);
            break;
        case CYBLE_EVT_GATTC_WRITE_RSP:
            break;
        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF:
            recv = (*(CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T*)param);
            //memcpy(ble_mtu_recv, recv.handleValPair.value.val, recv.handleValPair.value.len);
            
            IMU imu = (*(IMU*)recv.handleValPair.value.val);
            
            printf("sof=(%d %d %d)\r\n", imu.sof[0], imu.sof[1], imu.sof[2]);
            printf("gyr=(%d %d %d)\r\n", imu.gyr[0], imu.gyr[1], imu.gyr[2]);
            printf("acc=(%d %d %d)\r\n", imu.acc[0], imu.acc[1], imu.acc[2]);
            printf("mag=(%d %d %d)\r\n", imu.mag[0], imu.mag[1], imu.mag[2]);
            
            break;
    }
}

void print_ble_state(uint32 evt)
{
    printf("BLE Callback, evt(%lX), state(", evt); // evt 0x00 ~ 0x7F, 128 events
    switch (cyBle_state)
    {
        case CYBLE_STATE_STOPPED:
            printf("stopped");
            break;
        case CYBLE_STATE_INITIALIZING:
            printf("initializing");
            break;
        case CYBLE_STATE_CONNECTED:
            printf("connected");
            break;
#if (CYBLE_GAP_ROLE_CENTRAL)
        case CYBLE_STATE_SCANNING:
            printf("scanning");
            break;
        case CYBLE_STATE_CONNECTING:
            printf("connecting");
            break;
#endif
#if (CYBLE_GAP_ROLE_PERIPHERAL)
        case CYBLE_STATE_ADVERTISING:
            printf("advertising");
            break;
#endif
        case CYBLE_STATE_DISCONNECTED:
            printf("disconnected");
            break;
        default:
            printf("unknown");
            break;
    }
    printf(")\r\n");
}

void print_error_code(uint8 err)
{
    // Specification of the Bluetooth System, v4.2, Volume 2 Part D, Error Code Description
    switch (err)
    {
        case 0x01:
            printf("Unknown HCI Command");
            break;
        case 0x02:
            printf("Unknown Connection Identifier");
            break;
        case 0x03:
            printf("Hardware Failure");
            break;
        case 0x04:
            printf("Page Timeout");
            break;
        case 0x05:
            printf("Authentication Failure");
            break;
        case 0x06:
            printf("PIN or key Missing");
            break;
        case 0x07:
            printf("Memory Capacity Exceeded");
            break;
        case 0x08:
            printf("Connection Timeout");
            break;
        case 0x09:
            printf("Connection Limit Exceeded");
            break;
        case 0x0A:
            printf("Synchronous Connection Limit to a Device Exceeded");
            break;
        case 0x0B:
            printf("ACL Connection Already Exists");
            break;
        case 0x0C:
            printf("Command Disallowed");
            break;
        case 0x0D:
            printf("Connection Rejected due to Limited Resources");
            break;
        case 0x0E:
            printf("Connection Rejected due to Security Reasons");
            break;
        case 0x0F:
            printf("Connection Rejected due to Unacceptable BD_ADDR");
            break;
        case 0x10:
            printf("Connection Accept Timeout Exceeded");
            break;
        case 0x11:
            printf("Unsupported Feature or Parameter Value");
            break;
        case 0x12:
            printf("Invalid HCI Command Parameters");
            break;
        case 0x13:
            printf("Remote User Terminated Connection");
            break;
        case 0x14:
            printf("Remote Device Terminated Connection due to Low Resources");
            break;
        case 0x15:
            printf("Remote Device Terminated Connection due to Power Off");
            break;
        case 0x16:
            printf("Connection Terminated by Local Host");
            break;
        case 0x17:
            printf("Repeated Attempts");
            break;
        case 0x18:
            printf("Pairing not Allowed");
            break;
        case 0x19:
            printf("Unknown LMP PDU");
            break;
        case 0x1A:
            printf("Unsupported Remote Feature / Unsupported LMP Feature");
            break;
        case 0x1B:
            printf("SCO Offset Rejected");
            break;
        case 0x1C:
            printf("SCO Interval Rejected");
            break;
        case 0x1D:
            printf("SCO Air Mode Rejected");
            break;
        case 0x1E:
            printf("Invalid LMP Parameters / Invalid LL Parameters");
            break;
        case 0x1F:
            printf("Unspecified Error");
            break;
        case 0x20:
            printf("Unsupported LMP Parameter Value / Unsupportred LL Parameter Value");
            break;
        case 0x21:
            printf("Role Change Not Allowed");
            break;
        case 0x22:
            printf("LMP Response Timeout / LL Response Timeout");
            break;
        case 0x23:
            printf("LMP Error Transaction Collision");
            break;
        case 0x24:
            printf("LMP PDU Not Allowed");
            break;
        case 0x25:
            printf("Encyption Mode Not Acceptable");
            break;
        case 0x26:
            printf("Link Key cannot be Changed");
            break;
        case 0x27:
            printf("Required QoS Not Supported");
            break;
        case 0x28:
            printf("Instant Passed");
            break;
        case 0x29:
            printf("Pairing with Unit Key Not Supported");
            break;
        case 0x2A:
            printf("Different Transaction Collision");
            break;
        case 0x2C:
            printf("QoS Unacceptable Parameter");
            break;
        case 0x2D:
            printf("QoS Rejected");
            break;
        case 0x2E:
            printf("Channel Assessment Not Supported");
            break;
        case 0x2F:
            printf("Insufficient Security");
            break;
        case 0x30:
            printf("Parameter out of Mandatory Range");
            break;
        case 0x32:
            printf("Role swith Pending");
            break;
        case 0x34:
            printf("Reserved Slot Violation");
            break;
        case 0x35:
            printf("Role Switch Failed");
            break;
        case 0x36:
            printf("Extended Inquiry Response Too Large");
            break;
        case 0x37:
            printf("Simple Pairing Not Supported By Host");
            break;
        case 0x38:
            printf("Host Busy-Pairing");
            break;
        case 0x39:
            printf("Connection Rejected Due To Not Suitable Channel Found");
            break;
        case 0x3A:
            printf("Controller Busy");
            break;
        case 0x3B:
            printf("Unacceptable Connection Parameters");
            break;
        case 0x3C:
            printf("Directed Advertising Timeout");
            break;
        case 0x3D:
            printf("Connection Terminated Due To MIC Failure");
            break;
        case 0x3E:
            printf("Connection Failed To Be Established");
            break;
        case 0x3F:
            printf("MAC Connection Failed");
            break;
        case 0x40:
            printf("Coarse Clock Adjustment Rejected but Will Try to Adjusting Using Clock Dragging");
            break;
    }
    printf("\r\n");
}

#if (CYBLE_GAP_ROLE_CENTRAL)
uint8 is_peripheral(uint8* addr)
{
    for (uint8 i = 0; i < CYBLE_GAP_BD_ADDR_SIZE; i++)
    {
        if (addr[i] != peripheral_addr[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}
#endif
