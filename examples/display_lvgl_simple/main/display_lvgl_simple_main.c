/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "lv_demos.h"
#include "bsp/esp-bsp.h"

static char *TAG = "app_main";

#define LOG_MEM_INFO    (0)


void slider_event_cb( lv_event_t * e ){
    printf("Clicked\n");
}

void app_main(void)
{
    /* Initialize display and LVGL */
    bsp_display_start();

#if CONFIG_BSP_DISPLAY_LVGL_AVOID_TEAR
    ESP_LOGI(TAG, "Avoid lcd tearing effect");
#if CONFIG_BSP_DISPLAY_LVGL_FULL_REFRESH
    ESP_LOGI(TAG, "LVGL full-refresh");
#elif CONFIG_BSP_DISPLAY_LVGL_DIRECT_MODE
    ESP_LOGI(TAG, "LVGL direct-mode");
#endif
#endif

    /* Set display brightness to 100% */
    bsp_display_backlight_on();

    ESP_LOGI(TAG, "Display LVGL demo");
    bsp_display_lock(0);

    lv_obj_t * slider1 = lv_slider_create(lv_screen_active());

    lv_obj_set_x( slider1, 30 );
    lv_obj_set_y( slider1, 40 );
    lv_obj_set_size( slider1, 200, 30);

    lv_obj_add_event_cb( slider1, slider_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

    lv_obj_t * slider2 = lv_slider_create(lv_screen_active());

    lv_obj_set_x( slider2, 30 );
    lv_obj_set_y( slider2, 200 );
    lv_obj_set_size( slider2, 200, 30);

    lv_obj_add_event_cb( slider2, slider_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/


    // /*Create a chart*/
    // lv_obj_t * chart;
    // chart = lv_chart_create(lv_screen_active());
    // lv_obj_set_size(chart,200, 240);
    // lv_obj_center( chart );
    // // lv_obj_set_x( chart, 30 );
    // // lv_obj_set_y( chart, 100 );

    // lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    // /*Add two data series*/
    // lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    // lv_chart_series_t * ser2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_SECONDARY_Y);
    // int32_t * ser2_y_points = lv_chart_get_y_array(chart, ser2);

    // uint32_t i;
    // for(i = 0; i < 10; i++) {
    //     /*Set the next points on 'ser1'*/
    //     lv_chart_set_next_value(chart, ser1, lv_rand(10, 50));

    //     /*Directly set points on 'ser2'*/
    //     ser2_y_points[i] = lv_rand(50, 90);
    // }

    // lv_chart_refresh(chart); /*Required after direct set*/

    lv_obj_t * label1 = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_text(label1, "This is a long message.  Wrappy wrappy.");
    lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 40);


    bsp_display_unlock();

#if LOG_MEM_INFO
    static char buffer[128];    /* Make sure buffer is enough for `sprintf` */
    while (1) {
        sprintf(buffer, "   Biggest /     Free /    Total\n"
                "\t  SRAM : [%8d / %8d / %8d]\n"
                "\t PSRAM : [%8d / %8d / %8d]",
                heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
                heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
                heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
                heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
                heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
                heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
        ESP_LOGI("MEM", "%s", buffer);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
#endif
}
