set(target_name SecUSB)

# Tell CMake where to find the executable source file
add_executable(${target_name}  
   main.cpp
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${target_name} )

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${target_name}  
    pico_stdlib
    pico_multicore
    # comes from Pico-PIO-USB
    # pico_pio_usb
    # TinyUSB
    tinyusb_host
    tinyusb_board
    hardware_pio
)

# use tinyusb implementation
target_compile_definitions(${target_name} PRIVATE PIO_USB_USE_TINYUSB)

# needed so tinyusb can find tusb_config.h
target_include_directories(${target_name}  PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(${target_name} PRIVATE PICO_DEFAULT_UART_BAUD_RATE=115200 PICO_DEFAULT_UART_TX_PIN=16 PICO_DEFAULT_UART_RX_PIN=17)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${target_name}  0)
pico_enable_stdio_uart(${target_name}  1)