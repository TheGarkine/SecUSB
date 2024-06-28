# Secure USB Charging

## Development

Make sure to download and update all submodules:

``` bash
git submodule update --init --recursive
```

## Limitations

- We are currently only supporting HID devices (mouse, keyboard, etc.) and MSC device (USB Drives). Relating to [this](https://github.com/hathach/tinyusb/issues/1097) issue, vendor-type devices are not recognized. Since the data lanes are not forwarded to the system, you can use it with any USB-A Port without problem!