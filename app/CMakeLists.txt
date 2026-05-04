cmake_minimum_required(VERSION 3.20.0)

list(APPEND ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../drivers)

function(app_set_runner_args)
  board_runner_args(stm32cubeprogrammer "--extload=MX25UW25645G_NUCLEO-H7S3L8.stldr")
endfunction()

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
