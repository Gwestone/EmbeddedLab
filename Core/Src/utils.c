#include "utils.h"

void printRTT(char *message) {
    uint32_t time_ms = xTaskGetTickCount() * portTICK_PERIOD_MS;
    SEGGER_RTT_printf(0, "[%5lu ms] %s", time_ms, message);
}

void busyWait(uint32_t ms) {
    TickType_t targetTick = xTaskGetTickCount() + pdMS_TO_TICKS(ms);

    // Busy loop - burns CPU cycles until target time is reached
    // For 100 MHz: ~25000 iterations per millisecond works well
    while (xTaskGetTickCount() < targetTick) {
        for (volatile uint32_t i = 0; i < 25000; i++) {
            __NOP();
        }
    }
}