#ifndef ADXL345_ADXL345_REGISTERS_H
#define ADXL345_ADXL345_REGISTERS_H

#include <stdint.h>

typedef struct {
  uint8_t devid : 8;
} adxl345_devid_reg_t;

typedef struct {
  uint8_t thresh_tap : 8;
} adxl345_thresh_tap_reg_t;

typedef struct {
  int8_t ofsx : 8;
} adxl345_ofsx_reg_t;

typedef struct {
  int8_t ofsy : 8;
} adxl345_ofsy_reg_t;

typedef struct {
  int8_t ofsz : 8;
} adxl345_ofsz_reg_t;

typedef struct {
  uint8_t dur : 8;
} adxl345_dur_reg_t;

typedef struct {
  uint8_t latent : 8;
} adxl345_latent_reg_t;

typedef struct {
  uint8_t window : 8;
} adxl345_window_reg_t;

typedef struct {
  uint8_t thresh_act : 8;
} adxl345_thresh_act_reg_t;

typedef struct {
  uint8_t thresh_inact : 8;
} adxl345_thresh_inact_reg_t;

typedef struct {
  uint8_t time_inact : 8;
} adxl345_time_inact_reg_t;

typedef struct {
  uint8_t act_ac_dc : 1;
  uint8_t act_x_en : 1;
  uint8_t act_y_en : 1;
  uint8_t act_z_en : 1;
  uint8_t inact_ac_dc : 1;
  uint8_t inact_x_en : 1;
  uint8_t inact_y_en : 1;
  uint8_t inact_z_en : 1;
} adxl345_act_inact_ctl_reg_t;

typedef struct {
  uint8_t thresh_ff : 8;
} adxl345_thresh_ff_reg_t;

typedef struct {
  uint8_t time_ff : 8;
} adxl345_time_ff_reg_t;

typedef struct {
  uint8_t suppress : 1;
  uint8_t tap_x_en : 1;
  uint8_t tap_y_en : 1;
  uint8_t tap_z_en : 1;
} adxl345_tap_axes_reg_t;

typedef struct {
  uint8_t act_x_src : 1;
  uint8_t act_y_src : 1;
  uint8_t act_z_src : 1;
  uint8_t asleep : 1;
  uint8_t tap_x_src : 1;
  uint8_t tap_y_src : 1;
  uint8_t tap_z_src : 1;
} adxl345_act_tap_status_reg_t;

typedef struct {
  uint8_t low_power : 1;
  uint8_t rate : 4;
} adxl345_bw_rate_reg_t;

typedef struct {
  uint8_t link : 1;
  uint8_t auto_sleep : 1;
  uint8_t measure : 1;
  uint8_t sleep : 1;
  uint8_t wakeup : 2;
} adxl345_power_ctl_reg_t;

typedef struct {
  uint8_t data_ready : 1;
  uint8_t single_tap : 1;
  uint8_t double_tap : 1;
  uint8_t activity : 1;
  uint8_t inactivity : 1;
  uint8_t free_fall : 1;
  uint8_t watermark : 1;
  uint8_t overrun : 1;
} adxl345_int_enable_reg_t;

typedef struct {
  uint8_t data_ready : 1;
  uint8_t single_tap : 1;
  uint8_t double_tap : 1;
  uint8_t activity : 1;
  uint8_t inactivity : 1;
  uint8_t free_fall : 1;
  uint8_t watermark : 1;
  uint8_t overrun : 1;
} adxl345_int_map_reg_t;

typedef struct {
  uint8_t data_ready : 1;
  uint8_t single_tap : 1;
  uint8_t double_tap : 1;
  uint8_t activity : 1;
  uint8_t inactivity : 1;
  uint8_t free_fall : 1;
  uint8_t watermark : 1;
  uint8_t overrun : 1;
} adxl345_int_source_reg_t;

typedef struct {
  uint8_t self_test : 1;
  uint8_t spi : 1;
  uint8_t int_invert : 1;
  uint8_t full_res : 1;
  uint8_t justify : 1;
  uint8_t range : 2;
} adxl345_data_format_reg_t;

typedef struct {
  int16_t data_x : 16;
} adxl345_data_x_reg_t;

typedef struct {
  int16_t data_y : 16;
} adxl345_data_y_reg_t;

typedef struct {
  int16_t data_z : 16;
} adxl345_data_z_reg_t;

typedef struct {
  int16_t data_x : 16;
  int16_t data_y : 16;
  int16_t data_z : 16;
} adxl345_data_reg_t;

typedef struct {
  uint8_t fifo_mode : 2;
  uint8_t trigger : 1;
  uint8_t samples : 5;
} adxl345_fifo_ctl_reg_t;

typedef struct {
  uint8_t fifo_trig : 1;
  uint8_t entries : 6;
} adxl345_fifo_status_reg_t;

#endif // ADXL345_ADXL345_REGISTERS_H