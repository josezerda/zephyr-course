#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "led_sensor.h"

LOG_MODULE_REGISTER(led_app, LOG_LEVEL_DBG);

int main(void)
{
    const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(led_sensor));

    if (!device_is_ready(dev)) {
        LOG_ERR("LED sensor not ready");
        return -ENODEV;
    }

    LOG_INF("LED sensor driver demo starting...");
    LOG_INF("Blink period: %d ms", CONFIG_APP_HEARTBEAT_PERIOD_MS);

    /* Extension API: reset the blink_count in the driver's data struct */
    led_sensor_set_blink_count(dev, 0);
    LOG_INF("blink_count reset via extension API");

    while (1) {
        struct sensor_value val;

        sensor_sample_fetch(dev);
        LOG_DBG("LED ON");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        sensor_channel_get(dev, SENSOR_CHAN_ALL, &val);
        LOG_INF("LED OFF — blink_count: %d", val.val1);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}
