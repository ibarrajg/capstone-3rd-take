#include "lora_transmit.h"
#include <string.h>

#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LORA_UART UART_NUM_1
#define LORA_TX_PIN 17    // CHANGE if your wiring is different
#define LORA_RX_PIN 18    // CHANGE if your wiring is different

void lora_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 9600,   // E22 default
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = 0
    };

    uart_driver_install(LORA_UART, 256, 256, 0, NULL, 0);
    uart_param_config(LORA_UART, &uart_config);
    uart_set_pin(
        LORA_UART,
        LORA_TX_PIN,
        LORA_RX_PIN,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    );
}

void lora_send(const char *msg)
{
    uart_write_bytes(LORA_UART, msg, strlen(msg));
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
    }

    return len;
}
