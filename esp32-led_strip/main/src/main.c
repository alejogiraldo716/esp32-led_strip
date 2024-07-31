/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include "esp_log.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "led_strip.h"
#include "led_pattern.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IO (32) // The GPIO pin that is used for the LED
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // 13 bits for duty resolution
#define LEDC_FREQUENCY (1)              // 5 kHz for LEDC PWM frequency

#define LEDC_MAX_DUTY (8192)                                        // Maximum duty cycle value (100%)
#define LEDC_PWM_PERCENTAGE 75                                      // 50% duty cycle
#define LEDC_PWM_DUTY ((LEDC_MAX_DUTY * LEDC_PWM_PERCENTAGE) / 100) // 50% duty cycle

#define BLINK_GPIO 2
#define CONFIG_BLINK_PERIOD 500

#define RMT_TX_GPIO 18 // Must be less than GPIO_NUM_33
#define STRIP_LED_NUMBER 30
#define STRIP_LED_LEN STRIP_LED_NUMBER
#define RMT_TX_CHANNEL RMT_CHANNEL_0

static const char *TAG = "example";
static uint8_t s_led_state = 0;

void led_strip_struct_init(struct led_strip_t *led_strip)
{

    if (led_strip == NULL)
    {
        ESP_LOGE(TAG, "led_strip is NULL");
        return;
    }

    led_strip->rmt_channel = RMT_CHANNEL_0;
    led_strip->gpio = RMT_TX_GPIO;
    led_strip->rgb_led_type = RGB_LED_TYPE_WS2812;
    led_strip->led_strip_length = STRIP_LED_LEN;
    led_strip->access_semaphore = xSemaphoreCreateBinary();

    led_strip->led_strip_buf_1 = malloc(sizeof(struct led_color_t) * led_strip->led_strip_length);
    led_strip->led_strip_buf_2 = malloc(sizeof(struct led_color_t) * led_strip->led_strip_length);

    led_strip_init(led_strip);
}

void led_pwm_init(void)
{
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_DUTY_RES, // pwm duty resolution 13 bits
        .freq_hz = LEDC_FREQUENCY,        // Frequency of PWM signal 5 kHz
        .speed_mode = LEDC_MODE,          // High speed mode
        .timer_num = LEDC_TIMER,          // Timer index
        .clk_cfg = LEDC_AUTO_CLK          // Auto select the source clock
    };
    ledc_timer_config(&ledc_timer);

    // Configure the PWM channel
    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL,
        .duty = 0, // Initial duty cycle 0 %
        .gpio_num = LEDC_OUTPUT_IO,
        .speed_mode = LEDC_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER};
    ledc_channel_config(&ledc_channel);

    // Set the duty cycle
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_PWM_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

void device_info_print(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
    {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
}

void app_main(void)
{
    configure_led();
    led_pwm_init();
    printf("This is an example!\n");
    device_info_print();

    struct led_strip_t led_strip;
    led_strip_struct_init(&led_strip);
    led_strip_clear(&led_strip);
    led_strip_show(&led_strip);
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    struct led_color_t color = {0, 0, 0};

    while (1)
    {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        blink_led();
        /* Toggle the LED state */
        s_led_state = !s_led_state;

        for (int i = 0; i < STRIP_LED_NUMBER; i++)
        {
            static led_pattern_color_t color_iterator = LED_COLOR_OFF;
            color_iterator++;
            led_pattern_set_RGB(LED_COLOR_W, &color);
            led_strip_set_pixel_color(&led_strip, i, &color);
            led_strip_show(&led_strip);
            vTaskDelay(80 / portTICK_PERIOD_MS);
            if (color_iterator == LED_COLOR_MAX)
            {
                color_iterator = LED_COLOR_OFF;
            }
        }

    }
}
