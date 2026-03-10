#ifndef LORA_TRANSMIT_H
#define LORA_TRANSMIT_H

#ifdef __cplusplus
extern "C" {
#endif

void lora_init(void);
void lora_send(const char *msg);

#ifdef __cplusplus
}
#endif

#endif
