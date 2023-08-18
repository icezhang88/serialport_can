
#include "twai.h"

static const char *TAG = "TWAI";

#include "esp_log.h"


/**
 * 初始化can
 */
void init_twai(){
    static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CONFIG_CTX_GPIO, CONFIG_CRX_GPIO, TWAI_MODE_NORMAL);
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
   
    ESP_ERROR_CHECK(twai_start());
    
}
/**
 * 发送can的控制指令
 * @param deviceId
 * @param ctlValue
 */
void twai_sendControl(int32_t deviceId,int8_t ctlValue[]){
    twai_message_t message;
    message.identifier=deviceId;
    message.flags=0;
    message.data_length_code=8;
     ESP_LOGI(TAG,"deviceId:%x",deviceId);
    for (int i = 0; i < 8; i++) {
        message.data[i]=ctlValue[i];
        ESP_LOGI(TAG,"twai ctlValue:%d",message.data[i]);

    }

    for (int i = 0; i < 5; i++) {
        ESP_LOGI(TAG,"can send open!!!!!");
        twai_transmit(&message, pdMS_TO_TICKS(100));

        vTaskDelay(pdMS_TO_TICKS(100));
    }

}

/**
 * can 通讯控制测试
 * @param pvParameters
 */
void twai_write(void *pvParameters) {
    ESP_LOGI(TAG, "write task start");
    while (true) {
        twai_message_t message_open;
        message_open.identifier = 0x43a;
        message_open.flags = 0;
        message_open.data_length_code = 8;
        message_open.data[0] = 0x64;
        message_open.data[1] = 0x64;
        message_open.data[2] = 0x64;
        message_open.data[3] = 0x64;
        message_open.data[4] = 0x64;
        message_open.data[5] = 0x64;
        message_open.data[6] = 0x64;
        message_open.data[7] = 0x64;
        ESP_LOGI(TAG,"bag start !!!!!");
        for (int i = 0; i < 50; ++i) {
            ESP_LOGI(TAG,"can send open!!!!!");
            twai_transmit(&message_open, pdMS_TO_TICKS(100));

            vTaskDelay(pdMS_TO_TICKS(100));
        }

        vTaskDelay(pdMS_TO_TICKS(2000));

        twai_message_t message_close;
        message_close.identifier = 0x43a;
        message_close.flags = 0;
        message_close.data_length_code = 8;
        message_close.data[0] = 0x00;
        message_close.data[1] = 0x00;
        message_close.data[2] = 0x00;
        message_close.data[3] = 0x00;
        message_close.data[4] = 0x00;
        message_close.data[5] = 0x00;
        message_close.data[6] = 0x00;
        message_close.data[7] = 0x00;
        ESP_LOGI(TAG,"bag stop close !!!!!");
        for (int i = 0; i < 50; ++i) {
            twai_transmit(&message_close, pdMS_TO_TICKS(100));
            ESP_LOGI(TAG,"can send clouse!!!!!");
            vTaskDelay(pdMS_TO_TICKS(100));
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}



