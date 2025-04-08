#include "audio.h"

static const ledc_timer_config_t audio_timer_config =
{
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 440,
    .duty_resolution = LEDC_TIMER_8_BIT,
};

static const ledc_channel_config_t audio_channel_config =
{
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty = 0,
    .channel = LEDC_CHANNEL_0,
    .gpio_num = 23,
    .timer_sel = LEDC_TIMER_0,
};

void init_audio(void)
{
    printf("Initializing LEDC for audio.\n");
    ESP_ERROR_CHECK(ledc_timer_config(&audio_timer_config));
    ESP_ERROR_CHECK(ledc_channel_config(&audio_channel_config));
}

void set_audio(uint32_t frequency, uint32_t duty)
{
    if (frequency > 0)
    {
        ESP_ERROR_CHECK(ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0, frequency));
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
    }
    else
    {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
    }
}

void deinit_audio(void)
{
}
