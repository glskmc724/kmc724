#include <stdio.h>

#include "imu.h"

void EBIMU_send_command(uint8 cmd, double data)
{
    char str[64];
    
    switch (cmd)
    {
        case SET_BAUDRATE:
            sprintf(str, "<sb%d>", (uint8)data);
            break;
        case SET_OUTPUT_RATE:
            sprintf(str, "<sor%d>", (uint16)data);
            break;
        case SET_OUTPUT_CODE:
            sprintf(str, "<soc%d>", (uint8)data);
            break;
        case SET_OUTPUT_FORMAT:
            sprintf(str, "<sof%d>", (uint8)data);
            break;
        case SET_OUTPUT_GYRO:
            sprintf(str, "<sog%d>", (uint8)data);
            break;
        case SET_OUTPUT_ACCELERO:
            sprintf(str, "<soa%d>", (uint8)data);
            break;
        case SET_OUTPUT_MAGNETO:
            sprintf(str, "<som%d>", (uint8)data);
            break;
        case SET_OUTPUT_DISTANCE:
            sprintf(str, "<sod%d>", (uint8)data);
            break;
        case SET_OUTPUT_TEMPERATURE:
            sprintf(str, "<sot%d>", (uint8)data);
            break;
        case SET_OUTPUT_TIMESTAMP:
            sprintf(str, "<sots%d>", (uint8)data);
            break;
        case SET_ENABLE_MAGNETO:
            sprintf(str, "<sem%d>", (uint8)data);
            break;
        case SET_SENS_GYRO:
            sprintf(str, "<ssg%d>", (uint8)data);
            break;
        case SET_SENS_ACCELERO:
            sprintf(str, "<ssa%d>", (uint8)data);
            break;
        case SET_LPF_GYRO:
            sprintf(str, "<lpfg%d>", (uint8)data);
            break;
        case SET_LPF_ACCELERO:
            sprintf(str, "<lpfa%d>", (uint8)data);
            break;
        case SET_FILTER_FACTOR:
            sprintf(str, "<sff%d>", (uint8)data);
            break;
        case SET_FILTER_FACTOR_ACCELERO:
            sprintf(str, "<sffa%d>", (uint8)data);
            break;
        case SET_FILTER_FACTOR_MAGNETO:
            sprintf(str, "<sffm%d>", (uint8)data);
            break;
        case RAA_ALGORITHM_PARAM_LEVEL:
            sprintf(str, "<raa_l%.2lf>", data);
            break;
        case RAA_ALGORITHM_PARAM_TIMEOUT:
            sprintf(str, "<raa_t%ld>", (uint32)data);
            break;
        case RHA_ALGORITHM_PARAM_LEVEL:
            sprintf(str, "<rha_l%.2f>", data);
            break;
        case RHA_ALGORITHM_PARAM_TIMEOUT:
            sprintf(str, "<rha_t%ld>", (uint32)data);
            break;
        case AG_CALIBER_PARAM_ENABLE:
            sprintf(str, "<agc_e%d>", (uint8)data);
            break;
        case AG_CALIBER_PARAM_THRESHOLD:
            sprintf(str, "<agc_t%.2f>", (double)data);
            break;
        case AG_CALIBER_PARAM_DRIFT:
            sprintf(str, "<agc_d%.2f>", (double)data);
            break;
        case AV_CANCEL_PARAM_GYRO_ENABLE:
            sprintf(str, "<avcg_e%d>", (uint8)data);
            break;
        case AV_CANCEL_PARAM_ACCELERO_ENABLE:
            sprintf(str, "<avca_e%d>", (uint8)data);
            break;
        case POS_FILTER_PARAM_SL:
            sprintf(str, "<posf_sl%.4f>", (double)data);
            break;
        case POS_FILTER_PARAM_ST:
            sprintf(str, "<posf_st%d>", (uint16)data);
            break;
        case POS_FILTER_PARAM_SR:
            sprintf(str, "<posf_sr%.4f>", (double)data);
            break;
        case POS_FILTER_PARAM_AR:
            sprintf(str, "<posf_ar%.4f>", (double)data);
            break;
        case POS_ZERO:
            sprintf(str, "<posz>");
            break;
        // CALIBRATION은 물리적으로 조절하고, 조절이 끝나면 '>'를 입력해주어야 한다.
        // 이건 추후에 구현 예정
        case CALIBRATION_GYRO:
            sprintf(str, "<cg>");
            break;
        case CALIBRATION_ACCELERO_FREE:
            sprintf(str, "<caf>");
            break;
        case CALIBRATION_ACCELERO_SIMPLE:
            sprintf(str, "<cas>");
            break;
        case CALIBRATION_MAGNETO_FREE:
            sprintf(str, "<cmf>");
            break;
        case CALIBRATION_MAGNETO_XY:
            sprintf(str, "<cnxy>");
            break;
        case CALIBRATION_MAGNETO_PXY:
            sprintf(str, "<+cnxy>");
            break;
        case CALIBRATION_MAGNETO_Z:
            sprintf(str, "<cnz>");
            break;
        case CALIBRATION_MAGNETO_PZ:
            sprintf(str, "<+cnz>");
            break;
        case SET_MOTION_OFFSET:
            sprintf(str, "<cmo>");
            break;
        case SET_MOTION_OFFSET_X:
            sprintf(str, "<cmox>");
            break;
        case SET_MOTION_OFFSET_Y:
            sprintf(str, "<cmoy>");
            break;
        case SET_MOTION_OFFSET_Z:
            sprintf(str, "<cmoz>");
            break;
        case SET_MOTION_OFFSET_XY:
            sprintf(str, "<cmoxy>");
            break;
        case CLEAR_MOTION_OFFSET:
            sprintf(str, "<cmoc>");
            break;
        // CONFIGURATION is also wait until input character '>'.
        case CONFIGURATION:
            sprintf(str, "<cfg>");
            break;
        case POWER_ON_START:
            sprintf(str, "<pons%d>", (uint8)data);
            break;
        case START:
            sprintf(str, "<start>");
            break;
        case STOP:
            sprintf(str, "<stop>");
            break;
        case LOAD_FACTORORY_SETTINGS:
            sprintf(str, "<lf>");
            break;
        case RESET:
            sprintf(str, "<reset>");
            break;
        case VERSION_CHECK:
            sprintf(str, "<ver>");
            break;
    }
    
    //printf("%s\r\n", str);
    UART_IMU_UartPutString(str);
    
    uint8 ch;
    
    while ((ch = UART_IMU_UartGetChar()) != '<');
    while ((ch = UART_IMU_UartGetChar()) != 'o');
    while ((ch = UART_IMU_UartGetChar()) != 'k');
    while ((ch = UART_IMU_UartGetChar()) != '>');
    
    printf("OK\r\n");
}

void EBIMU_poll(void)
{
    UART_IMU_UartPutChar('*');
    CyDelay(10);
}

IMU EBIMU_recv_data(void)
{
    uint16 hex;
    uint16 chksum = 0;
    int cnt = 0;   
    IMU data;
    
    EBIMU_poll();
    
    hex = (UART_IMU_UartGetChar() << 8) | UART_IMU_UartGetChar();

    if (hex == 0x5555)
    {
        chksum = 0;
        cnt = 0;

        while (chksum != hex)
        {
            for (uint8 i = 0; i < 3; i++)
            {
                chksum += ((hex & 0xFF00) >> 8) + (hex & 0x00FF);
                hex = (UART_IMU_UartGetChar() << 8) | UART_IMU_UartGetChar();
                
                switch (cnt)
                {
                    case 0:
                        data.sof[i] = hex;
                        break;
                    case 1:
                        data.gyr[i] = hex;
                        break;
                    case 2:
                        data.acc[i] = hex;
                        break;
                    case 3:
                        data.mag[i] = hex;
                        break;
                }
            }
            
            cnt += 1;
            
            if (cnt == 3)
            {
                chksum += ((hex & 0xFF00) >> 8) + (hex & 0x00FF);
                hex = (UART_IMU_UartGetChar() << 8) | UART_IMU_UartGetChar();
            }
        }
    }
    return data;
}