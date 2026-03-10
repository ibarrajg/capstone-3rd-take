
#ifdef __cplusplus
extern "C" {
#endif

// declarations
#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "message.h"
#include "lora_transmit.h"
#include "lora_receive.h"
#include "message_frame.h"
#ifdef __cplusplus
}
#endif
// task functions outside void app_main
 
void console_task(void *arg)
{
    char msg[128] ={0}; // initializing the buffer


    uint8_t frame[256];
    uint8_t msg_id = 0;
    uint8_t dst = 0x05; // node cddrmo 

    while (1) {

        get_message(msg, sizeof(msg));

        if (msg[0] != '\0') {

            msg_id++;

            size_t msg_len = strlen(msg);   // compute length AFTER checking msg

            int frame_len = build_message_frame(
                frame,
                dst,
                msg_id,
                (uint8_t*)msg,
                msg_len
            );

            if (frame_len > 0) {
                lora_send((char*)frame);
                printf("LoRa frame sent\n");
            }
        }
    }
}
    

void lora_rx_task(void *arg)
{
    char rx_msg[128];

    while (1) {
        if (lora_receive(rx_msg, sizeof(rx_msg)) > 0) {
            printf("LoRa received: %s\n", rx_msg);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

//void app_main

void app_main(void)
{
    //esp32 uart communication configuration
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 0,
    .flags = {
        .backup_before_sleep = 0,
    }
    
};
    //driver install
    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    
    //initializes the esp32 to talk to the lora module
    lora_init();

    // task creation inside app_main for task functions outside app_main
    xTaskCreate(console_task, "console_task", 4096, NULL, 5, NULL);
    xTaskCreate(lora_rx_task, "lora_rx_task", 4096, NULL, 5, NULL); 
    //the message function is called through the task created by app_main, then in turn tasks do the work
}
