#include "utils.h"

#include <string.h>

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

uint8_t crc8_sae_j1850(unsigned char const *data, size_t len) {
    uint8_t crc = 0xFF;
    size_t i, j;

    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0) {
                crc = (uint8_t)((crc << 1) ^ 0x1D); // Shift and XOR with polynomial 0x1D
            } else {
                crc <<= 1; // Just shift left
            }
        }
    }

    return crc ^ 0xFF;
}

void burst_flush(task_context_t* ctx) {
    for (int i = 0; i < ctx->bcnt; i++) {
        printRTT(ctx->line1[i]);
    }
    ctx->bcnt = 0;
}

void log_or_burst(task_context_t* ctx, const char* message) {
    if (ctx->bcnt < BURST_SIZE) {
        strcpy(ctx->line1[ctx->bcnt], message);
        ctx->line1[ctx->bcnt][63] = '\0';
        ctx->bcnt++;
    }

    if (ctx->bcnt >= BURST_SIZE) {
        burst_flush(ctx);
    }
}