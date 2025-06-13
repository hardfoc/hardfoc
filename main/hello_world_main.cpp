
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "ws2812_cpp.hpp" // Include the WS2812 strip header
#include "ws2812_effects.hpp" // Include the WS2812 animator header
#include "../HAL/PinCfg/gpio_config_esp32c6.hpp" // Include the GPIO configuration header

WS2812Strip strip(WS2812_LED_PIN, RMT_CHANNEL_0, 30, LedType::RGB); // Use WS2812_LED_PIN from gpio_config_esp32c6.hpp
WS2812Animator anim(strip);

void printChipInfo(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
}

void app_main(void)
{
    printf("Hello world!\n");

    printChipInfo();
    strip.begin();
    // Reduce brightness for a smoother effect
    strip.setBrightness(64);
    // Use a rainbow cycle animation to showcase the LEDs
    anim.setEffect(WS2812Animator::Effect::RainbowCycle);
    // Run the animation a bit faster than the default
    anim.setSpeed(10);

    while (true) {
        anim.tick();
        vTaskDelay(pdMS_TO_TICKS(20));
    }

    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}