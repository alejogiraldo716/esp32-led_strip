#ifndef LED_PATTERN_H
#define LED_PATTERN_H

#include <stdio.h>
#include <stdlib.h>
#include "led_strip.h"




typedef enum led_pattern_color_t
{
    LED_COLOR_OFF,
    LED_COLOR_R,
    LED_COLOR_G,
    LED_COLOR_B,
    LED_COLOR_W,
    LED_COLOR_MAX,
} led_pattern_color_t;




void led_pattern_set_RGB(led_pattern_color_t color, struct led_color_t *led_strip);








#endif // LED_PATTERN_H