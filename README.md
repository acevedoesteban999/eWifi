# eWifi

The eWifi module is an implementation for handling WiFi functionality on the ESP32. This module allows you to set up a SoftAP (Access Point) and manage WiFi connections.

## Dependencies

- [eStore](https://github.com/acevedoesteban999/eStore)


## How to Use

```c
#include "eWifi.h"

void app_main() {
    // Set SSID and password
    ewifi_set_ssid_pass("SSID", "PASS");

    // Initialize
    ewifi_init();
}
```
