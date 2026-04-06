#include <zephyr/kernel.h>

int main(void)
{
#ifdef CONFIG_LED_SUBSYSTEM
    while (1) {
        k_msleep(CONFIG_LED_BLINK_SLEEP_MS);
    }
#endif
    return 0;
}