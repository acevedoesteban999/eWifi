# eWifi

The eWifi module is an implementation for handling WiFi functionality on the ESP32. This module allows you to set up a SoftAP (Access Point) and manage WiFi connections.

## Features

- Initialize SoftAP mode.
- Set SSID and password.
- Handle WiFi events for station connection and disconnection.

## Main Functions

- `void ewifi_init()`: Initializes the SoftAP mode.
- `void ewifi_set_ssid_pass(char* SSID, char* PASS)`: Sets the SSID and password for the SoftAP.
- `void ewifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)`: Handles WiFi events.

## Example Usage

```c
#include "eWifi.h"

void app_main() {
    // Set SSID and password
    ewifi_set_ssid_pass("MySSID", "MyPassword");

    // Initialize SoftAP mode
    ewifi_init();
}
```
