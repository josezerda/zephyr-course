#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Onboard LED on NUCLEO-H7S3L8 */
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(CONFIG_LED_BLINK_SLEEP_MS);
    }

    return 0;
}