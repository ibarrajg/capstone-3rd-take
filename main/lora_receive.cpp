#include "lora_receive.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LORA_UART UART_NUM_1   // SAME UART as transmit
#define LORA_RX_BUFFER 256

void lora_rx_init(void)
{
    // RX uses the SAME UART config as TX
    // Do NOT re-install driver if TX already did it
    // This function exists for clarity & future expansion
}

int lora_receive(char *buffer, int max_len)
{
    int len = uart_read_bytes(
        LORA_UART,
        (uint8_t *)buffer,
        max_len - 1,
        pdMS_TO_TICKS(10)
    );

    if (len > 0) {
        buffer[len] = '\0';
        return len;
    }

    return 0;
}
