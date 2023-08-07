#ifndef EBIMU_H
#define EBIMU_H

#include "project.h"

typedef struct
{
    short sof[3];
    short gyr[3];
    short acc[3];
    short mag[3];
    uint8 aaa[248-24];
} IMU;

enum {  // Output Command
        SET_BAUDRATE,
        SET_OUTPUT_RATE,
        SET_OUTPUT_CODE,
        SET_OUTPUT_FORMAT,
        SET_OUTPUT_GYRO,
        SET_OUTPUT_ACCELERO,
        SET_OUTPUT_MAGNETO,
        SET_OUTPUT_DISTANCE,
        SET_OUTPUT_TEMPERATURE,
        SET_OUTPUT_TIMESTAMP,
        // Sensor Command
        SET_ENABLE_MAGNETO,
        SET_SENS_GYRO,
        SET_SENS_ACCELERO,
        SET_LPF_GYRO,
        SET_LPF_ACCELERO,
        SET_FILTER_FACTOR,
        SET_FILTER_FACTOR_ACCELERO,
        SET_FILTER_FACTOR_MAGNETO,
        RAA_ALGORITHM_PARAM_LEVEL,
        RAA_ALGORITHM_PARAM_TIMEOUT,
        RHA_ALGORITHM_PARAM_LEVEL,
        RHA_ALGORITHM_PARAM_TIMEOUT,
        AG_CALIBER_PARAM_ENABLE,
        AG_CALIBER_PARAM_THRESHOLD,
        AG_CALIBER_PARAM_DRIFT,
        AV_CANCEL_PARAM_GYRO_ENABLE,
        AV_CANCEL_PARAM_ACCELERO_ENABLE,
        POS_FILTER_PARAM_SL,
        POS_FILTER_PARAM_ST,
        POS_FILTER_PARAM_SR,
        POS_FILTER_PARAM_AR,
        POS_ZERO,
        // Calibration Command
        CALIBRATION_GYRO,
        CALIBRATION_ACCELERO_FREE,
        CALIBRATION_ACCELERO_SIMPLE,
        CALIBRATION_MAGNETO_FREE,
        CALIBRATION_MAGNETO_XY,
        CALIBRATION_MAGNETO_PXY,
        CALIBRATION_MAGNETO_Z,
        CALIBRATION_MAGNETO_PZ,
        SET_MOTION_OFFSET,
        SET_MOTION_OFFSET_X,
        SET_MOTION_OFFSET_Y,
        SET_MOTION_OFFSET_Z,
        SET_MOTION_OFFSET_XY,
        CLEAR_MOTION_OFFSET,
        // ETC Command
        CONFIGURATION,
        POWER_ON_START,
        START,
        STOP,
        LOAD_FACTORORY_SETTINGS,
        RESET,
        VERSION_CHECK
};

void EBIMU_send_command(uint8 cmd, double data);
void EBIMU_poll(void);
IMU EBIMU_recv_data(void);

#endif