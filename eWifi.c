#include "eWifi.h"


char ESP_WIFI_SSID[32] = DEFAULT_SSID;
char ESP_WIFI_PASS[64] = DEFAULT_PASS;

void ewifi_event_handler(void *arg, esp_event_base_t event_base,int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI("", "station " MACSTR " join, AID=%d", MAC2STR(event->mac), event->aid);
    } 
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI("", "station " MACSTR " leave, AID=%d", MAC2STR(event->mac), event->aid);
    }
}

void ewifi_set_ssid_pass(char*SSID,char*PASS){
    estore_init();
    estore_write_string("ewifi_ssid",ESP_WIFI_SSID);
    estore_write_string("ewifi_pass",ESP_WIFI_PASS);
}

void ewifi_init(void)
{
    estore_init();
    estore_read_string("ewifi_ssid",ESP_WIFI_SSID,sizeof(ESP_WIFI_SSID));
    estore_read_string("ewifi_pass",ESP_WIFI_PASS,sizeof(ESP_WIFI_PASS));
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &ewifi_event_handler, NULL));
    
    wifi_config_t wifi_config = {
        .ap = {
            .ssid_len = strlen(ESP_WIFI_SSID),
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    strncpy((char *)wifi_config.ap.ssid, ESP_WIFI_SSID, sizeof(wifi_config.ap.ssid));
    strncpy((char *)wifi_config.ap.password, ESP_WIFI_PASS, sizeof(wifi_config.ap.password));

    if (strlen(ESP_WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(esp_netif_get_handle_from_ifkey("WIFI_AP_DEF"), &ip_info);

    char ip_addr[16];
    inet_ntoa_r(ip_info.ip.addr, ip_addr, 16);
    ESP_LOGI("", "Set up softAP with IP: %s", ip_addr);

    ESP_LOGI("", "ewifi_init finished. SSID:'%s' password:'%s'",
             ESP_WIFI_SSID, ESP_WIFI_PASS);
}