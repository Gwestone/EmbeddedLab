cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

set(LIBS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Libs)

# RTT CONFIG -----------------------------------------------------------------

set(RTT_DIR ${LIBS_DIRECTORY}/RTT)
set(RTT_SOURCES
        ${RTT_DIR}/RTT/SEGGER_RTT.c
        ${RTT_DIR}/RTT/SEGGER_RTT_printf.c
        ${RTT_DIR}/Syscalls/SEGGER_RTT_Syscalls_GCC.c)

set(RTT_INCLUDE_DIR
        ${RTT_DIR}/Config
        ${RTT_DIR}/RTT)

# FREERTOS CONFIG -------------------------------------------------------------

set(FREERTOS_SOURCES_DIR ${LIBS_DIRECTORY}/FreeRTOS/Source)
set(FREERTOS_INCLUDE_DIR ${FREERTOS_SOURCES_DIR}/include)

set(FREERTOS_SOURCES
        ${FREERTOS_SOURCES_DIR}/croutine.c
        ${FREERTOS_SOURCES_DIR}/event_groups.c
        ${FREERTOS_SOURCES_DIR}/list.c
        ${FREERTOS_SOURCES_DIR}/queue.c
        ${FREERTOS_SOURCES_DIR}/stream_buffer.c
        ${FREERTOS_SOURCES_DIR}/tasks.c
        ${FREERTOS_SOURCES_DIR}/timers.c
)

set(FREERTOS_PORTABLE_DIR ${FREERTOS_SOURCES_DIR}/portable/GCC/ARM_CM4F)

#this file can be a list for all source files in curent port
set(FREERTOS_PORTABLE_SOURCES ${FREERTOS_PORTABLE_DIR}/port.c)
set(FREERTOS_MEMORY_MANAGEMENT_SCHEME ${FREERTOS_SOURCES_DIR}/portable/MemMang/heap_4.c)


#-------------------------------------------------------------------------------------------------------
#   DO NOT CROSS THE LINE ALL INCLUDE CONFIGS ARE HERE
#-------------------------------------------------------------------------------------------------------

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
        INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Core/Inc) # The config file directory
target_compile_definitions(freertos_config
        INTERFACE
        projCOVERAGE_TEST=0)

set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING "")

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(PROJECT_NAME FreeRTOS_lab0)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Core/Inc/utils.h
        Core/Src/utils.c)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
        #${FREERTOS_SOURCES}
        ${FREERTOS_PORTABLE_SOURCES}
        ${FREERTOS_MEMORY_MANAGEMENT_SCHEME}
        ${RTT_SOURCES}
)

add_subdirectory(${FREERTOS_SOURCES_DIR})

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        ${FREERTOS_INCLUDE_DIR}
        ${FREERTOS_PORTABLE_DIR}
        ${RTT_INCLUDE_DIR}
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    freertos_kernel
    freertos_config
    # Add user defined libraries
)