#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

static const struct device *const sensor_dev =
	DEVICE_DT_GET(DT_NODELABEL(led_sensor));

static int cmd_sensor_fetch(const struct shell *sh, size_t argc, char **argv)
{
	int ret = sensor_sample_fetch(sensor_dev);

	if (ret) {
		shell_error(sh, "sensor_sample_fetch failed: %d", ret);
		return ret;
	}

	shell_print(sh, "fetch OK — LED on");
	return 0;
}

static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv)
{
	struct sensor_value val;
	int ret = sensor_channel_get(sensor_dev, SENSOR_CHAN_ALL, &val);

	if (ret) {
		shell_error(sh, "sensor_channel_get failed: %d", ret);
		return ret;
	}

	shell_print(sh, "LED off — blink_count: %d", val.val1);
	return 0;
}

static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
	shell_print(sh, "device : %s", sensor_dev->name);
	shell_print(sh, "ready  : %s", device_is_ready(sensor_dev) ? "yes" : "no");
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
	SHELL_CMD(fetch, NULL, "Call sensor_sample_fetch (LED on)",  cmd_sensor_fetch),
	SHELL_CMD(read,  NULL, "Call sensor_channel_get (LED off, print blink_count)", cmd_sensor_read),
	SHELL_CMD(info,  NULL, "Print device name and ready state",  cmd_sensor_info),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "LED sensor commands", NULL);
