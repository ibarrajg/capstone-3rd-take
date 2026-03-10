#ifndef MESSAGE_FRAME_H
#define MESSAGE_FRAME_H

#include <stdint.h>

#define STX           0xAA
#define SRC_ID        0x01
#define TYPE_MSG      0x01
#define MAX_DATA_LEN  64

#ifdef __cplusplus
extern "C" {
#endif

uint8_t calc_crc(uint8_t *buf, int len);

int build_message_frame(
    uint8_t *frame,
    uint8_t dst,
    uint8_t msg_id,
    uint8_t *data,
    uint8_t data_len
);

#ifdef __cplusplus
}
#endif

#endif