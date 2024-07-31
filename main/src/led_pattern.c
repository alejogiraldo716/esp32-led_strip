#include "led_pattern.h"



void led_pattern_set_RGB(led_pattern_color_t color, struct led_color_t *led_strip)
{
    switch (color)
    {
    case LED_COLOR_OFF:
        led_strip->red = 0;
        led_strip->green = 0;
        led_strip->blue = 0;
        break;
    case LED_COLOR_R:
        led_strip->red = 255;
        led_strip->green = 0;
        led_strip->blue = 0;
        break;
    case LED_COLOR_G:   
        led_strip->red = 0;
        led_strip->green = 255;
        led_strip->blue = 0;
        break;
    case LED_COLOR_B:
        led_strip->red = 0;
        led_strip->green = 0;
        led_strip->blue = 255;
        break;
    case LED_COLOR_W:
        led_strip->red = 255;
        led_strip->green = 255;
        led_strip->blue = 255;
        break;
    default:
        break;
    }
}