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

void canvas_event_cb( lv_event_t * e ){
    lv_indev_t * indev = lv_event_get_indev(e);
    lv_point_t p;
       
    /*Search the pressed area*/
    lv_indev_get_point(indev, &p);
    printf("X:%ld, Y:%ld\n", p.x, p.y);
}

lv_point_t p;

void obj_event_cb( lv_event_t * e ){
    lv_event_code_t code = lv_event_get_code(e);

    if ( code == LV_EVENT_CLICKED ) {
        lv_indev_t * indev = lv_event_get_indev(e);
    
        /*Search the pressed area*/
        lv_indev_get_point(indev, &p);

        printf("Click X:%ld, Y:%ld\n", p.x, p.y);

        lv_obj_t * obj = lv_event_get_target(e);
        lv_obj_invalidate(obj);

    } else if ( code == LV_EVENT_DRAW_MAIN ) {

        printf( "Draw main\n" );

        bsp_display_lock(0);

        // Nope.  You can't just draw on an object, you need a layer.
        // lv_obj_t * obj = lv_event_get_target(e);

        lv_layer_t * layer = lv_event_get_layer(e);

        if ( layer ) {
            lv_draw_line_dsc_t dsc;
            lv_draw_line_dsc_init(&dsc);
            dsc.color = lv_palette_main(LV_PALETTE_RED);
            dsc.width = 2;
            dsc.round_end = 0;
            dsc.round_start = 0;
            dsc.p1.x = p.x;
            dsc.p1.y = p.y;
            dsc.p2.x = p.x + 10;
            dsc.p2.y = p.y + 10;
            lv_draw_line(layer, &dsc);
        }

        bsp_display_unlock();
    } else {
        printf("Event code %d\n", code);
    }
}

#define CANVAS_WIDTH  120
#define CANVAS_HEIGHT 140

#define BSP_LCD_TOUCH_INT 14

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

    lv_obj_t * obj1;
    obj1 = lv_obj_create(lv_screen_active());
    lv_obj_add_flag( obj1, LV_OBJ_FLAG_CLICKABLE );
    lv_obj_set_size(obj1, 240, 280);
    lv_obj_center(obj1);
    //lv_obj_align(obj1, LV_ALIGN_CENTER, , -30);

    lv_obj_add_event_cb(obj1, obj_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

    // /*Create a buffer for the canvas*/
    // LV_DRAW_BUF_DEFINE_STATIC(draw_buf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888);
    // LV_DRAW_BUF_INIT_STATIC(draw_buf);

    // // lv_draw_buf_t *draw_buf = lv_draw_buf_create( CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888, LV_DRAW_BUF_STRIDE(CANVAS_WIDTH, LV_COLOR_FORMAT_ARGB8888) );
    // // lv_draw_buf_init(draw_buf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888, LV_DRAW_BUF_STRIDE(CANVAS_WIDTH, LV_COLOR_FORMAT_ARGB8888), NULL, 0);

    // /*Create a canvas and initialize its palette*/
    // lv_obj_t * canvas = lv_canvas_create(lv_screen_active());
    // lv_obj_add_flag( canvas, LV_OBJ_FLAG_CLICKABLE );
    // lv_canvas_set_draw_buf(canvas, &draw_buf);

    // lv_canvas_fill_bg(canvas, lv_color_hex3(0xccc), LV_OPA_COVER);
    // lv_obj_center(canvas);

    // lv_layer_t layer;
    // lv_canvas_init_layer(canvas, &layer);

    // lv_draw_rect_dsc_t dsc;
    // lv_draw_rect_dsc_init(&dsc);
    // dsc.bg_color = lv_palette_main(LV_PALETTE_RED);
    // dsc.border_color = lv_palette_main(LV_PALETTE_BLUE);
    // dsc.border_width = 3;
    // dsc.outline_color = lv_palette_main(LV_PALETTE_GREEN);
    // dsc.outline_width = 2;
    // dsc.outline_pad = 2;
    // dsc.outline_opa = LV_OPA_50;
    // dsc.radius = 5;
    // dsc.border_width = 3;

    // lv_area_t coords = {10, 10, 40, 30};

    // lv_draw_rect(&layer, &dsc, &coords);

    // lv_canvas_finish_layer(canvas, &layer);

    // lv_obj_add_event_cb( canvas, canvas_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/


    // lv_obj_t * slider1 = lv_slider_create(lv_screen_active());

    // lv_obj_set_x( slider1, 30 );
    // lv_obj_set_y( slider1, 40 );
    // lv_obj_set_size( slider1, 200, 30);

    // lv_obj_add_event_cb( slider1, slider_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

    // lv_obj_t * slider2 = lv_slider_create(lv_screen_active());

    // lv_obj_set_x( slider2, 30 );
    // lv_obj_set_y( slider2, 200 );
    // lv_obj_set_size( slider2, 200, 30);

    // lv_obj_add_event_cb( slider2, slider_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/


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


    // while (1) {

    //     printf( " CST816 INT %d\n", gpio_get_level( BSP_LCD_TOUCH_INT ) );

    //     vTaskDelay(pdMS_TO_TICKS(100));
    // }

}
