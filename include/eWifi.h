#pragma once

#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "eStore.h"
#include "lwip/inet.h"

#define MAX_STA_CONN 4
void wifi_init_softap(void);

void wifi_set_ssid_pass(char *SSID, char *PASS);
