#include <stdio.h>

#include "imu.h"
#include "debug.h"
#include "myble.h"

static uint32 ms_cnt = 0;
#if (CYBLE_GAP_ROLE_PERIPHERAL)
extern uint8 ble_mtu_rsp;
#endif
#if (CYBLE_GAP_ROLE_CENTRAL)
extern uint8 ble_mtu_req;
#endif
uint8 ble_mtu_recv[256];

void systick_isr_callback(void);

int main(void)
{
    CyGlobalIntEnable;

    IMU imu;
    CYBLE_GATTS_HANDLE_VALUE_NTF_T ntf;
    
    CySysTickStart();
    UART_DBG_Start();
    UART_IMU_Start();
    CyBle_Start(ble_callback);
    
//#if (CYBLE_GAP_ROLE_PERIPHERAL)
    EBIMU_send_command(SET_OUTPUT_RATE, 0);
    EBIMU_send_command(SET_OUTPUT_CODE, 2);
    EBIMU_send_command(SET_OUTPUT_GYRO, 1);
    EBIMU_send_command(SET_OUTPUT_ACCELERO, 1);
    EBIMU_send_command(SET_OUTPUT_MAGNETO, 1);
//#endif

    for (uint8 i = 0; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
    {
        if (CySysTickGetCallback(i) == NULL)
        {
            CySysTickSetCallback(i, systick_isr_callback);
            break;
        }
    }
    
    while (1)
    {
        if (cyBle_state == CYBLE_STATE_CONNECTED)
        {
//#if (CYBLE_GAP_ROLE_PERIPHERAL)
            if(CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE)
            {
#if (CYBLE_GAP_ROLE_PERIPHERAL)
                if (ble_mtu_rsp == TRUE)
#endif
#if (CYBLE_GAP_ROLE_CENTRAL)
                if (ble_mtu_req == TRUE)
#endif
                {
                    if (ms_cnt == 0) // 100ms
                    {
                        imu = EBIMU_recv_data();
                        
                        ntf.attrHandle = 0x0001;
                        ntf.value.val = (uint8*)&imu;
                        ntf.value.len = sizeof(IMU);
                        
                        CyBle_GattsNotification(cyBle_connHandle, &ntf);
                    }
                }
            }
//#endif
        }
        CyBle_ProcessEvents();
    }
}

void systick_isr_callback(void)
{
    // Callback 1 ms
    ms_cnt = (ms_cnt + 1) % 100;
}
