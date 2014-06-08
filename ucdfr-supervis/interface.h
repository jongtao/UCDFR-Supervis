#ifndef INTERFACE_H
#define INTERFACE_H


void send_str(const char *s);
uint8_t recv_str(char *buf, uint8_t size);
void usb_terminal(uint16_t *events, uint8_t *state);


#endif
