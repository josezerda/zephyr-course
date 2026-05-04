#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

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

    while (1) {
        sensor_sample_fetch(dev);
        LOG_DBG("LED ON");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        struct sensor_value val;

        sensor_channel_get(dev, SENSOR_CHAN_ALL, &val);
        LOG_DBG("LED OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}
