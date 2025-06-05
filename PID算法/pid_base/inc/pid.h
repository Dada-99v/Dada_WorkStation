#ifndef __PID_H__
#define __PID_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief PID control parameters
 *
 */
typedef struct {
    int32_t Kp;                      // PID Kp parameter
    int32_t Ki;                      // PID Ki parameter
    int32_t Kd;                      // PID Kd parameter
    int32_t     e;                  /* 误差值 */
    int32_t     target;             /* 目标值 */
    int32_t     current;            /* 当前实际值 */
    int32_t     p_out;              /* Kp系数计算输出值 */
    int32_t     i_out;              /* Ki系数计算输出值 */
    int32_t     d_out;              /* Kd系数计算输出值 */
    int32_t     total_out;          /* 当前输出值 */
    int32_t     IntegralLimit;      /* 积分限幅值 */
    int32_t     MaxOutout;          /* 输出限幅值 */
    int32_t     last_e;             /* 上次偏差记录 */
    /* float类型数据精度更高，需要引入大小比较 */
    // float max_output;              // PID maximum output limitation
    // float min_output;              // PID minimum output limitation
    // float max_integral;            // PID maximum integral value limitation
    // float min_integral;            // PID minimum integral value limitation
} _pid;

/**
 * @brief PID control configuration
 *
 */
typedef struct {
    _pid init_param; // Initial parameters
} pid_ctrl_config_t;

void pid_calc(_pid* pid);

#ifdef __cplusplus
}
#endif

#endif  /* __PID_H__ */
