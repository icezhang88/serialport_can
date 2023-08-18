//
// Created by Icezhang on 2023-03-30.
//

#ifndef HELLO_WORLD_TWAI_H
#define HELLO_WORLD_TWAI_H

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_err.h"
// #include "esp_log.h"
#include "driver/twai.h" // Update from V4.2


#define STANDARD_FRAME 0
#define EXTENDED_FRAME 1

#define DATA_FRAME     0
#define REMOTE_FRAME   1

#define	CMD_RECEIVE 100
#define	CMD_SEND    200


#define CONFIG_CTX_GPIO 21
#define CONFIG_CRX_GPIO 22

static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

typedef struct {
    int16_t command;
    char topic[64];
    int16_t topic_len;
    int32_t canid;
    int16_t ext;
    int16_t rtr;
    int16_t data_len;
    char data[8];
} FRAME_t;

typedef struct {
    uint16_t frame;
    uint32_t canid;
    char * topic;
    int16_t topic_len;
} TOPIC_t;

void init_twai();
void twai_sendControl(int32_t deviceId,int8_t ctlValue[]);
void twai_task(void *pvParameters);
void twai_write(void *pvParameters);
#endif //HELLO_WORLD_TWAI_H
