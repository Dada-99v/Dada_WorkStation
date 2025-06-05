#include "pid.h"

void limit(int32_t *a, int32_t b) {
    if (*a > b) {
        *a = b;
    }
}

void pid_calc(_pid* pid) {
    /* 误差值 */
    pid->e = pid->target - pid->current;

    pid->p_out = (int32_t)(pid->Kp * pid->e);

    /* 积分分离 */
    if (fabs(pid->e) < I_Band) {
        pid->i_out += (int32_t) (pid->Ki * pid->e);

        /* 积分限幅 */
        limit(&(pid->i_out), pid->IntegralLimit);
    } else {
        pid->i_out = 0;
    }

    pid->d_out = (int32_t)(pid->Kd * (pid->e - pid->last_e));

    pid->total_out = pid->p_out + pid->i_out + pid->d_out;
    /* pid输出限幅 */
    limit(&(pid->total_out), pid->MaxOutout);

    pid->last_e = pid->e;
}