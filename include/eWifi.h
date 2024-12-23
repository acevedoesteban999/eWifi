#pragma once

#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "eStore.h"
#include "lwip/inet.h"

#define MAX_STA_CONN 4
void ewifi_init(void);

void ewifi_set_ssid_pass(char *SSID, char *PASS);
