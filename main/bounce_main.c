#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_4 GPIO_NUM_4 // ---RED LED --- RES --- GND
#define LED_5 GPIO_NUM_5 // ---BLUE LED --- RES --- GND

#define LED_6 GPIO_NUM_6 // --- RES --- BLUE LED --- GND
                        // --- RES --- RED LED --- 3V3
                        // червоний світлодіод розвернуто так 
                        // що він дозволяє GPIO6 поглинати струм з 3V3
                        
void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_4) | (1ULL << LED_5) | (1ULL << LED_6),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    
    gpio_config(&io_conf);

    while (1) {
        gpio_set_level(LED_4, 1);
        gpio_set_level(LED_5, 0);
        gpio_set_level(LED_6, 0);
        
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_4, 0);
        gpio_set_level(LED_5, 1);
        gpio_set_level(LED_6, 1);
        
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}