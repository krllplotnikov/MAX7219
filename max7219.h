#ifndef MAX7219_H_
#define MAX7219_H_

#include <stdio.h>
#include <stdint.h>

#define REG_NOOP 0x00
#define REG_DIGIT_0 0x01
#define REG_DIGIT_1 0x02
#define REG_DIGIT_2 0x03
#define REG_DIGIT_3 0x04
#define REG_DIGIT_4 0x05
#define REG_DIGIT_5 0x06
#define REG_DIGIT_6 0x07
#define REG_DIGIT_7 0x08
#define REG_DECODE_MODE 0x09
#define REG_INTENSITY 0x0A
#define REG_SCAN_LIMIT 0x0B
#define REG_SHUTDOWN 0x0C
#define REG_DISPLAY_TEST 0x0F

typedef uint8_t MAX7219_Register_t;

typedef void (*SPI_Transmit)(uint8_t* data, size_t size);
typedef void (*SPI_ChipSelect)(uint8_t level);

typedef struct{
	SPI_Transmit spiTransmit;
	SPI_ChipSelect spiChipSelect;
}MAX7219_st;

#ifdef __cplusplus
extern "C" {
#endif

void MAX7219_Init(MAX7219_st* max7219, SPI_Transmit spiTransmit, SPI_ChipSelect spiChipSelect);
void MAX7219_WriteReg(MAX7219_st* max7219, MAX7219_Register_t reg, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif
