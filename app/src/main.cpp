#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(led_app, LOG_LEVEL_DBG);

#define APP_LED_NODE DT_ALIAS(app_led)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(APP_LED_NODE, gpios);

int main(void)
{
    LOG_INF("Heartbeat LED starting...");
    LOG_INF("Blink period: %d ms", CONFIG_APP_HEARTBEAT_PERIOD_MS);

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        LOG_DBG("LED toggled");
    }

    return 0;
}