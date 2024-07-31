# idf_component_register(SRCS "main.c"
#                     PRIV_REQUIRES spi_flash
#                     INCLUDE_DIRS "."
#                     REQUIRES "driver")


file(GLOB srcs
        "*.c"
        # "managers/wifi_manager/*.c"
)

set(dirs
        "../inc"
        # "../inc/managers"
)

set(components
        "nvs_flash"
        # "esp_http_server"
        "driver"
        # "json"
        # "bt"
        # "console"
        # "ulp"
        # "fatfs"
        # "audio_stream"
        # "audio_sal"
        # "audio_hal"
        # "esp_peripherals"
        # "app_update"
        # "esp_https_ota"
        # "esp_http_client"
        # "log"
        # "mdns"
        # "wpa_supplicant"
        # "lwip"
)

idf_component_register(
        REQUIRES ${components}
        SRCS ${srcs}
        INCLUDE_DIRS ${dirs}
)
