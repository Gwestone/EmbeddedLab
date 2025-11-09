#ifndef FREERTOS_LAB0_PROFILE_H
#define FREERTOS_LAB0_PROFILE_H

#include "main.h"

typedef enum { MODE_DELAY = 0, MODE_BUSY = 1 } run_mode_t;
typedef struct {
    run_mode_t mode; // delay або busy
    uint8_t burstMode; // 0 - звичайний лог; 1 - burst
    uint32_t baseDelayMs; // базова затримка для delay
    uint32_t baseCycles; // базові цикли для busy
    uint8_t step; // крок зміни параметрів між задачами (7 мс або 800 циклів)
    } profile_t;

#endif //FREERTOS_LAB0_PROFILE_H