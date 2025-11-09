#ifndef FREERTOS_LAB0_BURST_H
#define FREERTOS_LAB0_BURST_H

#include "main.h"

#define BURST_N 5
typedef struct {
    char name[12]; // ім’я задачі ("T02_0" тощо)
    uint32_t iter; // номер ітерації (0..Ni)
    uint32_t checksum; // контрольна сума (оновлюється кожну ітерацію)
    uint32_t delayTicksOrCycles; // затримка або тривалість навантаження
    uint32_t seed; // початкове "зерно" для checksum - IDX згідно з варіантом
    char line1[BURST_N][64]; // буфер рядків для burst логів
    char line2[BURST_N][64];
    uint8_t bcnt; // скільки рядків накопичено
} task_context_t;

#endif //FREERTOS_LAB0_BURST_H