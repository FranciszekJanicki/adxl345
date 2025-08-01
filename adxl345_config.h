#ifndef ADXL345_ADXL345_CONFIG_H
#define ADXL345_ADXL345_CONFIG_H

#include "adxl345_registers.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float float32_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} vec3_int16_t;

typedef struct {
    float32_t x;
    float32_t y;
    float32_t z;
} vec3_float32_t;

typedef enum {
    ADXL345_ERR_OK = 0,
    ADXL345_ERR_FAIL = 1 << 0,
    ADXL345_ERR_NULL = 1 << 1,
} adxl345_err_t;

typedef enum {
    ADXL345_REG_ADDR_DEVID = 0x00,
    ADXL345_REG_ADDR_THRESH_TAP = 0x1D,
    ADXL345_REG_ADDR_OFSX = 0x1E,
    ADXL345_REG_ADDR_OFSY = 0x1F,
    ADXL345_REG_ADDR_OFSZ = 0x20,
    ADXL345_REG_ADDR_DUR = 0x21,
    ADXL345_REG_ADDR_LATENT = 0x22,
    ADXL345_REG_ADDR_WINDOW = 0x23,
    ADXL345_REG_ADDR_THRESH_ACT = 0x24,
    ADXL345_REG_ADDR_THRESH_INACT = 0x25,
    ADXL345_REG_ADDR_TIME_INACT = 0x26,
    ADXL345_REG_ADDR_ACT_INACT_CTL = 0x27,
    ADXL345_REG_ADDR_THRESH_FF = 0x28,
    ADXL345_REG_ADDR_TIME_FF = 0x29,
    ADXL345_REG_ADDR_TAP_AXES = 0x2A,
    ADXL345_REG_ADDR_ACT_TAP_STATUS = 0x2B,
    ADXL345_REG_ADDR_BW_RATE = 0x2C,
    ADXL345_REG_ADDR_POWER_CTL = 0x2D,
    ADXL345_REG_ADDR_INT_ENABLE = 0x2E,
    ADXL345_REG_ADDR_INT_MAP = 0x2F,
    ADXL345_REG_ADDR_INT_SOURCE = 0x30,
    ADXL345_REG_ADDR_DATA_FORMAT = 0x31,
    ADXL345_REG_ADDR_DATA_X0 = 0x32,
    ADXL345_REG_ADDR_DATA_X1 = 0x33,
    ADXL345_REG_ADDR_DATA_Y0 = 0x34,
    ADXL345_REG_ADDR_DATA_Y1 = 0x35,
    ADXL345_REG_ADDR_DATA_Z0 = 0x36,
    ADXL345_REG_ADDR_DATA_Z1 = 0x37,
    ADXL345_REG_ADDR_FIFO_CTL = 0x38,
    ADXL345_REG_ADDR_FIFO_STATUS = 0x39,
} adxl345_reg_addr_t;

typedef enum {
    ADXL345_OUTPUT_DATA_RATE_3200HZ = 0b1111,
    ADXL345_OUTPUT_DATA_RATE_1600HZ = 0b1110,
    ADXL345_OUTPUT_DATA_RATE_800HZ = 0b1101,
    ADXL345_OUTPUT_DATA_RATE_400HZ = 0b1100,
    ADXL345_OUTPUT_DATA_RATE_200HZ = 0b1011,
    ADXL345_OUTPUT_DATA_RATE_100HZ = 0b1010,
    ADXL345_OUTPUT_DATA_RATE_50HZ = 0b1001,
    ADXL345_OUTPUT_DATA_RATE_25HZ = 0b1000,
    ADXL345_OUTPUT_DATA_RATE_12HZ5 = 0b0111,
    ADXL345_OUTPUT_DATA_RATE_6HZ25 = 0b0110,
    ADXL345_OUTPUT_DATA_RATE_3HZ125 = 0b0101,
    ADXL345_OUTPUT_DATA_RATE_1HZ563 = 0b0100,
    ADXL345_OUTPUT_DATA_RATE_0HZ782 = 0b0011,
    ADXL345_OUTPUT_DATA_RATE_0HZ39 = 0b0010,
    ADXL345_OUTPUT_DATA_RATE_0HZ195 = 0b0001,
    ADXL345_OUTPUT_DATA_RATE_0HZ098 = 0b0000,
} adxl345_output_data_rate_t;

typedef enum {
    ADXL345_FULL_SCALE_RANGE_2G = 0b00,
    ADXL345_FULL_SCALE_RANGE_4G = 0b01,
    ADXL345_FULL_SCALE_RANGE_8G = 0b10,
    ADXL345_FULL_SCALE_RANGE_16G = 0b11,
} adxl345_full_scale_range_t;

typedef enum {
    ADXL345_WAKE_UP_RATE_8HZ = 0b00,
    ADXL345_WAKE_UP_RATE_4HZ = 0b01,
    ADXL345_WAKE_UP_RATE_2HZ = 0b10,
    ADXL345_WAKE_UP_RATE_1HZ = 0b11,
} adxl345_wake_up_rate_t;

inline float32_t adxl345_range_to_scale(adxl345_full_scale_range_t range)
{
    switch (range) {
        case ADXL345_FULL_SCALE_RANGE_2G:
            return 0.01916F;
        case ADXL345_FULL_SCALE_RANGE_4G:
            return 0.03823F;
        case ADXL345_FULL_SCALE_RANGE_8G:
            return 0.07664F;
        case ADXL345_FULL_SCALE_RANGE_16G:
            return 0.15328F;
    }
}

typedef struct {
    float32_t scale;
} adxl345_config_t;

typedef struct {
    void* bus_user;
    adxl345_err_t (*bus_initialize)(void*);
    adxl345_err_t (*bus_deinitialize)(void*);
    adxl345_err_t (*bus_write_data)(void*, uint8_t, uint8_t const*, size_t);
    adxl345_err_t (*bus_read_data)(void*, uint8_t, uint8_t*, size_t);
} adxl345_interface_t;

#ifdef __cplusplus
}
#endif

#endif // ADXL345_ADXL345_CONFIG_H