#include "adxl345.h"
#include "adxl345_config.h"
#include "adxl345_registers.h"
#include <assert.h>
#include <string.h>

static adxl345_err_t adxl345_bus_init(adxl345_t const* adxl345)
{
    return adxl345->interface.bus_init ? adxl345->interface.bus_init(adxl345->interface.bus_user)
                                       : ADXL345_ERR_NULL;
}

static adxl345_err_t adxl345_bus_deinit(adxl345_t const* adxl345)
{
    return adxl345->interface.bus_deinit
               ? adxl345->interface.bus_deinit(adxl345->interface.bus_user)
               : ADXL345_ERR_NULL;
}

static adxl345_err_t adxl345_bus_write(adxl345_t const* adxl345,
                                       uint8_t address,
                                       uint8_t const* data,
                                       size_t data_size)
{
    return adxl345->interface.bus_write
               ? adxl345->interface.bus_write(adxl345->interface.bus_user, address, data, data_size)
               : ADXL345_ERR_NULL;
}

static adxl345_err_t adxl345_bus_read(adxl345_t const* adxl345,
                                      uint8_t address,
                                      uint8_t* data,
                                      size_t data_size)
{
    return adxl345->interface.bus_read
               ? adxl345->interface.bus_read(adxl345->interface.bus_user, address, data, data_size)
               : ADXL345_ERR_NULL;
}

adxl345_err_t adxl345_initialize(adxl345_t* adxl345,
                                 adxl345_config_t const* config,
                                 adxl345_interface_t const* interface)
{
    assert(adxl345 && config && interface);

    memset(adxl345, 0, sizeof(*adxl345));
    memcpy(&adxl345->config, config, sizeof(*config));
    memcpy(&adxl345->interface, interface, sizeof(*interface));

    return adxl345_bus_init(adxl345);
}

adxl345_err_t adxl345_deinitialize(adxl345_t* adxl345)
{
    assert(adxl345);

    adxl345_err_t err = adxl345_bus_deinit(adxl345);

    memset(adxl345, 0, sizeof(*adxl345));

    return err;
}

adxl345_err_t adxl345_get_acc_data_x_scaled(adxl345_t const* adxl345, float32_t* scaled)
{
    assert(adxl345 && scaled);

    int16_t raw = {};

    adxl345_err_t err = adxl345_get_acc_data_x_raw(adxl345, &raw);

    *scaled = (float32_t)raw * adxl345->config.scale;

    return err;
}

adxl345_err_t adxl345_get_acc_data_y_scaled(adxl345_t const* adxl345, float32_t* scaled)
{
    assert(adxl345 && scaled);

    int16_t raw = {};

    adxl345_err_t err = adxl345_get_acc_data_y_raw(adxl345, &raw);

    *scaled = (float32_t)raw * adxl345->config.scale;

    return err;
}

adxl345_err_t adxl345_get_acc_data_z_scaled(adxl345_t const* adxl345, float32_t* scaled)
{
    assert(adxl345 && scaled);

    int16_t raw = {};

    adxl345_err_t err = adxl345_get_acc_data_z_raw(adxl345, &raw);

    *scaled = (float32_t)raw * adxl345->config.scale;

    return err;
}

adxl345_err_t adxl345_get_acc_data_scaled(adxl345_t const* adxl345, vec3_float32_t* scaled)
{
    assert(adxl345 && scaled);

    vec3_int16_t raw = {};

    adxl345_err_t err = adxl345_get_acc_data_raw(adxl345, &raw);

    scaled->x = (float32_t)raw.x * adxl345->config.scale;
    scaled->y = (float32_t)raw.y * adxl345->config.scale;
    scaled->z = (float32_t)raw.z * adxl345->config.scale;

    return err;
}

adxl345_err_t adxl345_get_acc_data_x_raw(adxl345_t const* adxl345, int16_t* raw)
{
    assert(adxl345 && raw);

    adxl345_data_x_reg_t reg = {};

    adxl345_err_t err = adxl345_get_data_x_reg(adxl345, &reg);

    *raw = reg.data_x;

    return err;
}

adxl345_err_t adxl345_get_acc_data_y_raw(adxl345_t const* adxl345, int16_t* raw)
{
    assert(adxl345 && raw);

    adxl345_data_y_reg_t reg = {};

    adxl345_err_t err = adxl345_get_data_y_reg(adxl345, &reg);

    *raw = reg.data_y;

    return err;
}

adxl345_err_t adxl345_get_acc_data_z_raw(adxl345_t const* adxl345, int16_t* raw)
{
    assert(adxl345 && raw);

    adxl345_data_z_reg_t reg = {};

    adxl345_err_t err = adxl345_get_data_z_reg(adxl345, &reg);

    *raw = reg.data_z;

    return err;
}

adxl345_err_t adxl345_get_acc_data_raw(adxl345_t const* adxl345, vec3_int16_t* raw)
{
    assert(adxl345 && raw);

    adxl345_data_reg_t reg = {};

    adxl345_err_t err = adxl345_get_data_reg(adxl345, &reg);

    raw->x = reg.data_x;
    raw->y = reg.data_y;
    raw->z = reg.data_z;

    return err;
}

adxl345_err_t adxl345_get_devid_reg(adxl345_t const* adxl345, adxl345_devid_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DEVID, &data, sizeof(data));

    reg->devid = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_get_thresh_tap_reg(adxl345_t const* adxl345, adxl345_thresh_tap_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_THRESH_TAP, &data, sizeof(data));

    reg->thresh_tap = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_thresh_tap_reg(adxl345_t const* adxl345,
                                         adxl345_thresh_tap_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->thresh_tap & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_OFSX, &data, sizeof(data));
}

adxl345_err_t adxl345_get_ofsx_reg(adxl345_t const* adxl345, adxl345_ofsx_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_OFSX, &data, sizeof(data));

    reg->ofsx = (int8_t)(data & 0xFF);

    return err;
}

adxl345_err_t adxl345_set_ofsx_reg(adxl345_t const* adxl345, adxl345_ofsx_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (uint8_t)(reg->ofsx & 0xFF);

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_OFSX, &data, sizeof(data));
}

adxl345_err_t adxl345_get_ofsy_reg(adxl345_t const* adxl345, adxl345_ofsy_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_OFSY, &data, sizeof(data));

    reg->ofsy = (int8_t)(data >> 0) & 0xFF;

    return err;
}

adxl345_err_t adxl345_set_ofsy_reg(adxl345_t const* adxl345, adxl345_ofsy_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (uint8_t)(reg->ofsy & 0xFF);

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_OFSY, &data, sizeof(data));
}

adxl345_err_t adxl345_get_ofsz_reg(adxl345_t const* adxl345, adxl345_ofsz_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_OFSZ, &data, sizeof(data));

    reg->ofsz = (int8_t)(data & 0xFF);

    return err;
}

adxl345_err_t adxl345_set_ofsz_reg(adxl345_t const* adxl345, adxl345_ofsz_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (uint8_t)(reg->ofsz & 0xFF);

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_OFSZ, &data, sizeof(data));
}

adxl345_err_t adxl345_get_dur_reg(adxl345_t const* adxl345, adxl345_dur_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DUR, &data, sizeof(data));

    reg->dur = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_dur_reg(adxl345_t const* adxl345, adxl345_dur_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->dur & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_DUR, &data, sizeof(data));
}

adxl345_err_t adxl345_get_latent_reg(adxl345_t const* adxl345, adxl345_latent_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_LATENT, &data, sizeof(data));

    reg->latent = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_latent_reg(adxl345_t const* adxl345, adxl345_latent_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->latent & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_LATENT, &data, sizeof(data));
}

adxl345_err_t adxl345_get_window_reg(adxl345_t const* adxl345, adxl345_window_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_WINDOW, &data, sizeof(data));

    reg->window = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_window_reg(adxl345_t const* adxl345, adxl345_window_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->window & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_WINDOW, &data, sizeof(data));
}

adxl345_err_t adxl345_get_thresh_act_reg(adxl345_t const* adxl345, adxl345_thresh_act_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_THRESH_ACT, &data, sizeof(data));

    reg->thresh_act = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_thresh_act_reg(adxl345_t const* adxl345,
                                         adxl345_thresh_act_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->thresh_act & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_THRESH_ACT, &data, sizeof(data));
}

adxl345_err_t adxl345_get_thresh_inact_reg(adxl345_t const* adxl345,
                                           adxl345_thresh_inact_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err =
        adxl345_bus_read(adxl345, ADXL345_REG_ADDR_THRESH_INACT, &data, sizeof(data));

    reg->thresh_inact = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_thresh_inact_reg(adxl345_t const* adxl345,
                                           adxl345_thresh_inact_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->thresh_inact & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_THRESH_INACT, &data, sizeof(data));
}

adxl345_err_t adxl345_get_time_inact_reg(adxl345_t const* adxl345, adxl345_time_inact_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_TIME_INACT, &data, sizeof(data));

    reg->time_inact = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_time_inact_reg(adxl345_t const* adxl345,
                                         adxl345_time_inact_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->time_inact & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_TIME_INACT, &data, sizeof(data));
}

adxl345_err_t adxl345_get_act_inact_ctl_reg(adxl345_t const* adxl345,
                                            adxl345_act_inact_ctl_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err =
        adxl345_bus_read(adxl345, ADXL345_REG_ADDR_ACT_INACT_CTL, &data, sizeof(data));

    reg->act_ac_dc = (data >> 7U) & 0x01U;
    reg->act_x_en = (data >> 6U) & 0x01U;
    reg->act_y_en = (data >> 5U) & 0x01U;
    reg->act_z_en = (data >> 4U) & 0x01U;
    reg->inact_ac_dc = (data >> 3U) & 0x01U;
    reg->inact_x_en = (data >> 2U) & 0x01U;
    reg->inact_y_en = (data >> 1U) & 0x01U;
    reg->inact_z_en = data & 0x01U;

    return err;
}

adxl345_err_t adxl345_set_act_inact_ctl_reg(adxl345_t const* adxl345,
                                            adxl345_act_inact_ctl_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (reg->act_ac_dc & 0x01U) << 7U;
    data |= (reg->act_x_en & 0x01U) << 6U;
    data |= (reg->act_y_en & 0x01U) << 5U;
    data |= (reg->act_z_en & 0x01U) << 4U;
    data |= (reg->inact_ac_dc & 0x01U) << 3U;
    data |= (reg->inact_x_en & 0x01U) << 2U;
    data |= (reg->inact_y_en & 0x01U) << 1U;
    data |= reg->inact_z_en & 0x01U;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_ACT_INACT_CTL, &data, sizeof(data));
}

adxl345_err_t adxl345_get_thresh_ff_reg(adxl345_t const* adxl345, adxl345_thresh_ff_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_THRESH_FF, &data, sizeof(data));

    reg->thresh_ff = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_thresh_ff_reg(adxl345_t const* adxl345,
                                        adxl345_thresh_ff_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->thresh_ff & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_THRESH_FF, &data, sizeof(data));
}

adxl345_err_t adxl345_get_time_ff_reg(adxl345_t const* adxl345, adxl345_time_ff_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_TIME_FF, &data, sizeof(data));

    reg->time_ff = data & 0xFFU;

    return err;
}

adxl345_err_t adxl345_set_time_ff_reg(adxl345_t const* adxl345, adxl345_time_ff_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= reg->time_ff & 0xFFU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_TIME_FF, &data, sizeof(data));
}

adxl345_err_t adxl345_get_tap_axes_reg(adxl345_t const* adxl345, adxl345_tap_axes_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_TAP_AXES, &data, sizeof(data));

    reg->suppress = (data >> 3U) & 0x01U;
    reg->tap_x_en = (data >> 2U) & 0x01U;
    reg->tap_y_en = (data >> 1U) & 0x01U;
    reg->tap_z_en = data & 0x01U;

    return err;
}

adxl345_err_t adxl345_set_tap_axes_reg(adxl345_t const* adxl345, adxl345_tap_axes_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_TAP_AXES, &data, sizeof(data));

    data &= ~((0x01U << 3U) | (0x01U << 2U) | (0x01U << 1U) | 0x01U);

    data |= (reg->suppress & 0x01U) << 3U;
    data |= (reg->tap_x_en & 0x01U) << 2U;
    data |= (reg->tap_y_en & 0x01U) << 1U;
    data |= reg->tap_z_en & 0x01U;

    err |= adxl345_bus_write(adxl345, ADXL345_REG_ADDR_TAP_AXES, &data, sizeof(data));

    return err;
}

adxl345_err_t adxl345_get_act_tap_status_reg(adxl345_t const* adxl345,
                                             adxl345_act_tap_status_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err =
        adxl345_bus_read(adxl345, ADXL345_REG_ADDR_ACT_TAP_STATUS, &data, sizeof(data));

    reg->act_x_src = (data >> 6U) & 0x01U;
    reg->act_y_src = (data >> 5U) & 0x01U;
    reg->act_z_src = (data >> 4U) & 0x01U;
    reg->asleep = (data >> 3U) & 0x01U;
    reg->tap_x_src = (data >> 2U) & 0x01U;
    reg->tap_x_src = (data >> 1U) & 0x01U;
    reg->tap_x_src = data & 0x01U;

    return err;
}

adxl345_err_t adxl345_get_bw_rate_reg(adxl345_t const* adxl345, adxl345_bw_rate_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_BW_RATE, &data, sizeof(data));

    reg->low_power = (data >> 4U) & 0x01U;
    reg->rate = data & 0x0FU;

    return err;
}

adxl345_err_t adxl345_set_bw_rate_reg(adxl345_t const* adxl345, adxl345_bw_rate_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_BW_RATE, &data, sizeof(data));

    data &= ~((0x01U << 4U) | 0x0FU);

    data |= (reg->low_power & 0x01U) << 4U;
    data |= reg->rate & 0x0FU;

    err |= adxl345_bus_write(adxl345, ADXL345_REG_ADDR_BW_RATE, &data, sizeof(data));

    return err;
}

adxl345_err_t adxl345_get_power_ctl_reg(adxl345_t const* adxl345, adxl345_power_ctl_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_POWER_CTL, &data, sizeof(data));

    reg->link = (data >> 5U) & 0x01U;
    reg->auto_sleep = (data >> 4U) & 0x01U;
    reg->measure = (data >> 3U) & 0x01U;
    reg->sleep = (data >> 2U) & 0x01U;
    reg->wakeup = data & 0x03U;

    return err;
}

adxl345_err_t adxl345_set_power_ctl_reg(adxl345_t const* adxl345,
                                        adxl345_power_ctl_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_POWER_CTL, &data, sizeof(data));

    data &= ~((0x01U << 5U) | (0x01U << 4U) | (0x01U << 3U) | (0x01U << 2U) | 0x03U);

    data |= (reg->link & 0x01U) << 5U;
    data |= (reg->auto_sleep & 0x01U) << 4U;
    data |= (reg->measure & 0x01U) << 3U;
    data |= (reg->sleep & 0x01U) << 2U;
    data |= reg->wakeup & 0x03U;

    err |= adxl345_bus_write(adxl345, ADXL345_REG_ADDR_POWER_CTL, &data, sizeof(data));

    return err;
}

adxl345_err_t adxl345_get_int_enable_reg(adxl345_t const* adxl345, adxl345_int_enable_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_INT_ENABLE, &data, sizeof(data));

    reg->data_ready = (data >> 7U) & 0x01U;
    reg->single_tap = (data >> 6U) & 0x01U;
    reg->double_tap = (data >> 5U) & 0x01U;
    reg->activity = (data >> 4U) & 0x01U;
    reg->inactivity = (data >> 3U) & 0x01U;
    reg->free_fall = (data >> 2U) & 0x01U;
    reg->watermark = (data >> 1U) & 0x01U;
    reg->overrun = data & 0x01U;

    return err;
}

adxl345_err_t adxl345_set_int_enable_reg(adxl345_t const* adxl345,
                                         adxl345_int_enable_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (reg->data_ready & 0x01U) << 7U;
    data |= (reg->single_tap & 0x01U) << 6U;
    data |= (reg->double_tap & 0x01U) << 5U;
    data |= (reg->activity & 0x01U) << 4U;
    data |= (reg->inactivity & 0x01U) << 3U;
    data |= (reg->free_fall & 0x01U) << 2U;
    data |= (reg->watermark & 0x01U) << 1U;
    data |= reg->overrun & 0x01U;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_INT_ENABLE, &data, sizeof(data));
}

adxl345_err_t adxl345_get_int_map_reg(adxl345_t const* adxl345, adxl345_int_map_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_INT_MAP, &data, sizeof(data));

    reg->data_ready = (data >> 7U) & 0x01U;
    reg->single_tap = (data >> 6U) & 0x01U;
    reg->double_tap = (data >> 5U) & 0x01U;
    reg->activity = (data >> 4U) & 0x01U;
    reg->inactivity = (data >> 3U) & 0x01U;
    reg->free_fall = (data >> 2U) & 0x01U;
    reg->watermark = (data >> 1U) & 0x01U;
    reg->overrun = data & 0x01U;

    return err;
}

adxl345_err_t adxl345_set_int_map_reg(adxl345_t const* adxl345, adxl345_int_map_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (reg->data_ready & 0x01U) << 7U;
    data |= (reg->single_tap & 0x01U) << 6U;
    data |= (reg->double_tap & 0x01U) << 5U;
    data |= (reg->activity & 0x01U) << 4U;
    data |= (reg->inactivity & 0x01U) << 3U;
    data |= (reg->free_fall & 0x01U) << 2U;
    data |= (reg->watermark & 0x01U) << 1U;
    data |= reg->overrun & 0x01U;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_INT_MAP, &data, sizeof(data));
}

adxl345_err_t adxl345_get_int_source_reg(adxl345_t const* adxl345, adxl345_int_source_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_INT_SOURCE, &data, sizeof(data));

    reg->data_ready = (data >> 7U) & 0x01U;
    reg->single_tap = (data >> 6U) & 0x01U;
    reg->double_tap = (data >> 5U) & 0x01U;
    reg->activity = (data >> 4U) & 0x01U;
    reg->inactivity = (data >> 3U) & 0x01U;
    reg->free_fall = (data >> 2U) & 0x01U;
    reg->watermark = (data >> 1U) & 0x01U;
    reg->overrun = data & 0x01U;

    return err;
}

adxl345_err_t adxl345_set_int_source_reg(adxl345_t const* adxl345,
                                         adxl345_int_source_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (reg->data_ready & 0x01U) << 7U;
    data |= (reg->single_tap & 0x01U) << 6U;
    data |= (reg->double_tap & 0x01U) << 5U;
    data |= (reg->activity & 0x01U) << 4U;
    data |= (reg->inactivity & 0x01U) << 3U;
    data |= (reg->free_fall & 0x01U) << 2U;
    data |= (reg->watermark & 0x01U) << 1U;
    data |= reg->overrun & 0x01U;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_INT_SOURCE, &data, sizeof(data));
}

adxl345_err_t adxl345_get_data_format_reg(adxl345_t const* adxl345, adxl345_data_format_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err =
        adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DATA_FORMAT, &data, sizeof(data));

    reg->self_test = (data >> 7U) & 0x01U;
    reg->spi = (data >> 6U) & 0x01U;
    reg->int_invert = (data >> 5U) & 0x01U;
    reg->full_res = (data >> 3U) & 0x01U;
    reg->justify = (data >> 2U) & 0x01U;
    reg->range = data & 0x03U;

    return err;
}

adxl345_err_t adxl345_set_data_format_reg(adxl345_t const* adxl345,
                                          adxl345_data_format_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err =
        adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DATA_FORMAT, &data, sizeof(data));

    data &=
        ~((0x01U << 7U) | (0x01U << 6U) | (0x01U << 5U) | (0x01U << 3U) | (0x01U << 2U) | 0x03U);

    data |= (reg->self_test & 0x01U) << 7U;
    data |= (reg->spi & 0x01U) << 6U;
    data |= (reg->int_invert & 0x01U) << 5U;
    data |= (reg->full_res & 0x01U) << 3U;
    data |= (reg->justify & 0x01U) << 2U;
    data |= reg->range & 0x03U;

    err |= adxl345_bus_write(adxl345, ADXL345_REG_ADDR_DATA_FORMAT, &data, sizeof(data));

    return err;
}

adxl345_err_t adxl345_get_data_x_reg(adxl345_t const* adxl345, adxl345_data_x_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data[2] = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DATA_X0, data, sizeof(data));

    reg->data_x = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

adxl345_err_t adxl345_get_data_y_reg(adxl345_t const* adxl345, adxl345_data_y_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data[2] = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DATA_Y0, data, sizeof(data));

    reg->data_y = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

adxl345_err_t adxl345_get_data_z_reg(adxl345_t const* adxl345, adxl345_data_z_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data[2] = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DATA_Z0, data, sizeof(data));

    reg->data_z = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

adxl345_err_t adxl345_get_data_reg(adxl345_t const* adxl345, adxl345_data_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data[6] = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_DATA_X0, data, sizeof(data));

    reg->data_x = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));
    reg->data_y = (int16_t)((data[2] & 0xFF) | ((data[3] & 0xFF) << 8));
    reg->data_z = (int16_t)((data[4] & 0xFF) | ((data[5] & 0xFF) << 8));

    return err;
}

adxl345_err_t adxl345_get_fifo_ctl_reg(adxl345_t const* adxl345, adxl345_fifo_ctl_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err = adxl345_bus_read(adxl345, ADXL345_REG_ADDR_FIFO_CTL, &data, sizeof(data));

    reg->fifo_mode = (data >> 6U) & 0x03U;
    reg->trigger = (data >> 5U) & 0x01U;
    reg->samples = data & 0x0FU;

    return err;
}

adxl345_err_t adxl345_set_fifo_ctl_reg(adxl345_t const* adxl345, adxl345_fifo_ctl_reg_t const* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    data |= (reg->fifo_mode & 0x03U) << 6U;
    data |= (reg->trigger & 0x01U) << 5U;
    data |= reg->samples & 0x1FU;

    return adxl345_bus_write(adxl345, ADXL345_REG_ADDR_FIFO_CTL, &data, sizeof(data));
}

adxl345_err_t adxl345_get_fifo_status_reg(adxl345_t const* adxl345, adxl345_fifo_status_reg_t* reg)
{
    assert(adxl345 && reg);

    uint8_t data = {};

    adxl345_err_t err =
        adxl345_bus_read(adxl345, ADXL345_REG_ADDR_FIFO_STATUS, &data, sizeof(data));

    reg->fifo_trig = (data >> 7U) & 0x01U;
    reg->entries = data & 0x3FU;

    return err;
}
