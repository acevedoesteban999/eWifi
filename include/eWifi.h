#pragma once

#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "eStore.h"
#include "lwip/inet.h"

#define ESP_WIFI_SSID "ESP32"
#define ESP_WIFI_PASS "ESP32_PASSW"
#define MAX_STA_CONN 4

void wifi_init_softap(void);
