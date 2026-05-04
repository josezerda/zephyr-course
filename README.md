Welcome to the Zephyr RTOS training! This repository includes a ready-to-use
development environment based on Zephyr 4.3.0, which you can set up in one of
three ways:

---

## Manual Zephyr Setup

Follow the following guide:
- [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#).

Make sure to select appropriate OS and to perform all steps till
[Build the Blinky Sample](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#build-the-blinky-sample).

---

## Clone and Build This Project

### l2-task1

Execute:

```bash
git clone https://github.com/josezerda/zephyr-course.git
cd zephyr-course
source ~/zephyrproject/.venv/bin/activate
west init
west update
west build -p always -b nucleo_h7s3l8 ~/zephyrproject/zephyr/samples/basic/blinky
west flash
```

### l3-task1

Execute:

```bash
cd app
west build -b nucleo_h7s3l8/stm32h7s3xx/ext_flash_app
west build -t menuconfig
```

![Blinky funcionando](docs/images/blinky.jpg)

![Kconfig funcionando](docs/images/Kconfig.png.png)

---

### l5-task2: Custom Board From Scratch

Board structure for `my_scratch_board`:

| File | Purpose |
|---|---|
| `board.yml` | Board metadata (name, SoC) |
| `Kconfig.my_scratch_board` | Selects `SOC_STM32H7S3XX` |
| `Kconfig.defconfig` | Board-level Kconfig defaults |
| `my_scratch_board.dts` | Minimal DTS: clocks, USART3, flash, RAM |
| `my_scratch_board_defconfig` | Enables UART, console, GPIO |
| `board.cmake` | STM32CubeProgrammer flash runner |
| `CMakeLists.txt` | Compiles `board_init.c` |
| `board_init.c` | `SYS_INIT` prints "Board Initialized" before `main()` |

---

### l6-task1: Sensor Driver for On-Board LED

New module: `drivers/` — registered as a Zephyr extra module via `ZEPHYR_EXTRA_MODULES` in `app/CMakeLists.txt`.

| File | Purpose |
|---|---|
| `drivers/zephyr/module.yml` | Registers the module's cmake, Kconfig, and DTS root |
| `drivers/CMakeLists.txt` | Conditionally adds `sensor/` subdirectory |
| `drivers/Kconfig` | Sources `sensor/Kconfig` |
| `drivers/sensor/led_sensor/led_sensor.c` | Driver: `sample_fetch` → LED on, `channel_get` → LED off |
| `drivers/sensor/led_sensor/Kconfig` | `LED_SENSOR` symbol, `default y`, select `SENSOR` |
| `drivers/dts/bindings/sensor/custom,led-sensor.yaml` | DT binding defining the `gpios` phandle-array property |
| `drivers/dts/bindings/vendor-prefixes.txt` | Registers the `custom` vendor prefix |

Modified app files:

- `app/CMakeLists.txt` — adds `ZEPHYR_EXTRA_MODULES`
- `app/app.overlay` — adds `led_sensor: led-sensor` node on PD10
- `app/prj.conf` — adds `CONFIG_SENSOR=y`, `CONFIG_LED_SENSOR=y`
- `app/src/main.cpp` — uses `sensor_sample_fetch` / `sensor_channel_get` to blink the LED

> **Key gotcha:** `module.yml` must use `build.settings.dts_root: .` (not `dts.bindings`) for Zephyr to include the module's `dts/bindings/` in the DTS compilation path.