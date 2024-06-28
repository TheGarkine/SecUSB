#Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/pico-sdk)

# Include build functions from Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C%2B%2B standards
project(pico_wireless_usb C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Add the RF24 libraries
# include(thirdparty/RF24/CMakeLists.txt)
# include(thirdparty/RF24Network/CMakeLists.txt)
# include(thirdparty/RF24Mesh/CMakeLists.txt)
# include(thirdparty/tiny-AES-C/CMakeLists.txt)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

#TinyUSB
#include(${PICO_TINYUSB_PATH}/CMakeLists.txt)

# Add the Pio library
add_subdirectory(thirdparty/Pico-PIO-USB)

# Build the firmware
add_subdirectory(src)