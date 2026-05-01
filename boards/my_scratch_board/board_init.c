/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

#define LED_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static K_THREAD_STACK_DEFINE(blink_stack, 1024);
static struct k_thread blink_thread;

static void blink_fn(void *a, void *b, void *c)
{
	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep(500);
	}
}

static int my_scratch_board_init(void)
{
	printk("Board Initialized\n");

	if (!gpio_is_ready_dt(&led)) {
		printk("LED GPIO not ready\n");
		return -ENODEV;
	}

	int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		printk("LED GPIO configure failed: %d\n", ret);
		return ret;
	}

	k_thread_create(&blink_thread, blink_stack,
			K_THREAD_STACK_SIZEOF(blink_stack),
			blink_fn, NULL, NULL, NULL,
			K_PRIO_PREEMPT(10), 0, K_NO_WAIT);
	return 0;
}

SYS_INIT(my_scratch_board_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
