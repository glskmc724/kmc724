#ifndef MYBLE_H
#define MYBLE_H

#include "project.h"
#include "debug.h"

void ble_callback(uint32 event, void* event_param);
void print_ble_state(uint32 evt);
void print_error_code(uint8 err);

#endif