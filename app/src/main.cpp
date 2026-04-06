#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(led_app, LOG_LEVEL_DBG);

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    LOG_INF("LED Subsystem starting...");
    LOG_INF("Blink period: %d ms", CONFIG_LED_BLINK_SLEEP_MS);
    LOG_INF("Brightness:   %d", CONFIG_LED_BRIGHTNESS);
    LOG_INF("Fade time:    %d ms", CONFIG_LED_FADE_TIME);

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(CONFIG_LED_BLINK_SLEEP_MS);
        LOG_DBG("LED toggled");
    }

    return 0;
}