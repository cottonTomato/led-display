#include <stdio.h>
#include "driver/ledc.h"
#include "driver/gpio.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO (12)
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_DUTY (4095)
#define LEDC_FREQUENCY (5000)
#define MTR_IN1_IO (14)
#define MTR_IN2_IO (27)
#define MTR_IN1 (0)
#define MTR_IN2 (1)

static void ledc_init()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK};
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_IO,
        .duty = 0,
        .hpoint = 0};
    ledc_channel_config(&ledc_channel);
}

static void mtr_ctrl_init()
{
    int en1_err = gpio_set_level(MTR_IN1_IO, MTR_IN1);
    int en2_err = gpio_set_level(MTR_IN2_IO, MTR_IN2);

    int en1 = gpio_get_level(MTR_IN1_IO);
    int en2 = gpio_get_level(MTR_IN2_IO);

    printf("Err => en1: %d, en2: %d\n", en1_err, en2_err);
    printf("Val => en1: %d, en2: %d", en1, en2);
}

void app_main()
{
    mtr_ctrl_init();
    ledc_init();
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}