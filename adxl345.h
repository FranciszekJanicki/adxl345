#ifndef ADXL345_ADXL345_H
#define ADXL345_ADXL345_H

#include "adxl345_config.h"
#include "adxl345_registers.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    adxl345_config_t config;
    adxl345_interface_t interface;
} adxl345_t;

adxl345_err_t adxl345_initialize(adxl345_t* adxl345,
                                 adxl345_config_t const* config,
                                 adxl345_interface_t const* interface);
adxl345_err_t adxl345_deinitialize(adxl345_t* adxl345);

adxl345_err_t adxl345_get_acc_data_x_scaled(adxl345_t const* adxl345,
                                            float32_t* scaled);
adxl345_err_t adxl345_get_acc_data_y_scaled(adxl345_t const* adxl345,
                                            float32_t* scaled);
adxl345_err_t adxl345_get_acc_data_z_scaled(adxl345_t const* adxl345,
                                            float32_t* scaled);
adxl345_err_t adxl345_get_acc_data_scaled(adxl345_t const* adxl345,
                                          vec3_float32_t* scaled);

adxl345_err_t adxl345_get_acc_data_x_raw(adxl345_t const* adxl345,
                                         int16_t* raw);
adxl345_err_t adxl345_get_acc_data_y_raw(adxl345_t const* adxl345,
                                         int16_t* raw);
adxl345_err_t adxl345_get_acc_data_z_raw(adxl345_t const* adxl345,
                                         int16_t* raw);
adxl345_err_t adxl345_get_acc_data_raw(adxl345_t const* adxl345,
                                       vec3_int16_t* raw);

adxl345_err_t adxl345_get_devid_reg(adxl345_t const* adxl345,
                                    adxl345_devid_reg_t* reg);

adxl345_err_t adxl345_get_thresh_tap_reg(adxl345_t const* adxl345,
                                         adxl345_thresh_tap_reg_t* reg);
adxl345_err_t adxl345_set_thresh_tap_reg(adxl345_t const* adxl345,
                                         adxl345_thresh_tap_reg_t const* reg);

adxl345_err_t adxl345_get_ofsx_reg(adxl345_t const* adxl345,
                                   adxl345_ofsx_reg_t* reg);
adxl345_err_t adxl345_set_ofsx_reg(adxl345_t const* adxl345,
                                   adxl345_ofsx_reg_t const* reg);

adxl345_err_t adxl345_get_ofsy_reg(adxl345_t const* adxl345,
                                   adxl345_ofsy_reg_t* reg);
adxl345_err_t adxl345_set_ofsy_reg(adxl345_t const* adxl345,
                                   adxl345_ofsy_reg_t const* reg);

adxl345_err_t adxl345_get_ofsz_reg(adxl345_t const* adxl345,
                                   adxl345_ofsz_reg_t* reg);
adxl345_err_t adxl345_set_ofsz_reg(adxl345_t const* adxl345,
                                   adxl345_ofsz_reg_t const* reg);

adxl345_err_t adxl345_get_dur_reg(adxl345_t const* adxl345,
                                  adxl345_dur_reg_t* reg);
adxl345_err_t adxl345_set_dur_reg(adxl345_t const* adxl345,
                                  adxl345_dur_reg_t const* reg);

adxl345_err_t adxl345_get_latent_reg(adxl345_t const* adxl345,
                                     adxl345_latent_reg_t* reg);
adxl345_err_t adxl345_set_latent_reg(adxl345_t const* adxl345,
                                     adxl345_latent_reg_t const* reg);

adxl345_err_t adxl345_get_window_reg(adxl345_t const* adxl345,
                                     adxl345_window_reg_t* reg);
adxl345_err_t adxl345_set_window_reg(adxl345_t const* adxl345,
                                     adxl345_window_reg_t const* reg);

adxl345_err_t adxl345_get_thresh_act_reg(adxl345_t const* adxl345,
                                         adxl345_thresh_act_reg_t* reg);
adxl345_err_t adxl345_set_thresh_act_reg(adxl345_t const* adxl345,
                                         adxl345_thresh_act_reg_t const* reg);

adxl345_err_t adxl345_get_thresh_inact_reg(adxl345_t const* adxl345,
                                           adxl345_thresh_inact_reg_t* reg);
adxl345_err_t adxl345_set_thresh_inact_reg(
    adxl345_t const* adxl345,
    adxl345_thresh_inact_reg_t const* reg);

adxl345_err_t adxl345_get_time_inact_reg(adxl345_t const* adxl345,
                                         adxl345_time_inact_reg_t* reg);
adxl345_err_t adxl345_set_time_inact_reg(adxl345_t const* adxl345,
                                         adxl345_time_inact_reg_t const* reg);

adxl345_err_t adxl345_get_act_inact_ctl_reg(adxl345_t const* adxl345,
                                            adxl345_act_inact_ctl_reg_t* reg);
adxl345_err_t adxl345_set_act_inact_ctl_reg(
    adxl345_t const* adxl345,
    adxl345_act_inact_ctl_reg_t const* reg);

adxl345_err_t adxl345_get_thresh_ff_reg(adxl345_t const* adxl345,
                                        adxl345_thresh_ff_reg_t* reg);
adxl345_err_t adxl345_set_thresh_ff_reg(adxl345_t const* adxl345,
                                        adxl345_thresh_ff_reg_t const* reg);

adxl345_err_t adxl345_get_time_ff_reg(adxl345_t const* adxl345,
                                      adxl345_time_ff_reg_t* reg);
adxl345_err_t adxl345_set_time_ff_reg(adxl345_t const* adxl345,
                                      adxl345_time_ff_reg_t const* reg);

adxl345_err_t adxl345_get_tap_axes_reg(adxl345_t const* adxl345,
                                       adxl345_tap_axes_reg_t* reg);
adxl345_err_t adxl345_set_tap_axes_reg(adxl345_t const* adxl345,
                                       adxl345_tap_axes_reg_t const* reg);

adxl345_err_t adxl345_get_act_tap_status_reg(adxl345_t const* adxl345,
                                             adxl345_act_tap_status_reg_t* reg);

adxl345_err_t adxl345_get_bw_rate_reg(adxl345_t const* adxl345,
                                      adxl345_bw_rate_reg_t* reg);
adxl345_err_t adxl345_set_bw_rate_reg(adxl345_t const* adxl345,
                                      adxl345_bw_rate_reg_t const* reg);

adxl345_err_t adxl345_get_power_ctl_reg(adxl345_t const* adxl345,
                                        adxl345_power_ctl_reg_t* reg);
adxl345_err_t adxl345_set_power_ctl_reg(adxl345_t const* adxl345,
                                        adxl345_power_ctl_reg_t const* reg);

adxl345_err_t adxl345_get_int_enable_reg(adxl345_t const* adxl345,
                                         adxl345_int_enable_reg_t* reg);
adxl345_err_t adxl345_set_int_enable_reg(adxl345_t const* adxl345,
                                         adxl345_int_enable_reg_t const* reg);

adxl345_err_t adxl345_get_int_map_reg(adxl345_t const* adxl345,
                                      adxl345_int_map_reg_t* reg);
adxl345_err_t adxl345_set_int_map_reg(adxl345_t const* adxl345,
                                      adxl345_int_map_reg_t const* reg);

adxl345_err_t adxl345_get_int_source_reg(adxl345_t const* adxl345,
                                         adxl345_int_source_reg_t* reg);

adxl345_err_t adxl345_set_data_format_reg(adxl345_t const* adxl345,
                                          adxl345_data_format_reg_t const* reg);

adxl345_err_t adxl345_get_data_x_reg(adxl345_t const* adxl345,
                                     adxl345_data_x_reg_t* reg);
adxl345_err_t adxl345_get_data_y_reg(adxl345_t const* adxl345,
                                     adxl345_data_y_reg_t* reg);
adxl345_err_t adxl345_get_data_z_reg(adxl345_t const* adxl345,
                                     adxl345_data_z_reg_t* reg);
adxl345_err_t adxl345_get_data_reg(adxl345_t const* adxl345,
                                   adxl345_data_reg_t* reg);

adxl345_err_t adxl345_get_fifo_ctl_reg(adxl345_t const* adxl345,
                                       adxl345_fifo_ctl_reg_t* reg);
adxl345_err_t adxl345_set_fifo_ctl_reg(adxl345_t const* adxl345,
                                       adxl345_fifo_ctl_reg_t const* reg);

adxl345_err_t adxl345_get_fifo_status_reg(adxl345_t const* adxl345,
                                          adxl345_fifo_status_reg_t* reg);

#ifdef __cplusplus
}
#endif

#endif // ADXL345_ADXL345_H