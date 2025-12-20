#ifndef FREERTOS_LAB0_UTILS_H
#define FREERTOS_LAB0_UTILS_H
#include "main.h"
#include "task_context.h"

void printRTT(char *message);
void busyWait(uint32_t ms);
uint8_t crc8_sae_j1850(unsigned char const *data, size_t len);

void burst_flush(task_context_t* ctx);
void log_or_burst(task_context_t* ctx, const char* message);
void init_mprintf(void);
void mprintf(const char *format, ...);

int16_t parseMessage(char* message);

#endif //FREERTOS_LAB0_UTILS_H