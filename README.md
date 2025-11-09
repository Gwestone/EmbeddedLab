# Yuri Skoda's template repo for embedded system's course
## Purpose
to use it as template in next freeRTOS Embedded sytems course assignments
## How to setup
- Copy project to your CLion using create project from URL
- Add ```-DCMAKE_TOOLCHAIN_FILE=./cmake/gcc-arm-none-eabi.cmake``` to cmake options
- copy directories License annd Source from your local installation of FreeRTOS to @/Libs/FreeRTOS in the base of project
- now project should be building with the led blinking if your system uses C13 pin for LED

## To reuse project
- change FREERTOS_PORTABLE_SOURCES variable in cmakelists.txt to new port
## Check if everything is ok
- pull branch master or lab_1
- if it prints warnings about task's timings misalighnment something into rtt console then project is misconfigured