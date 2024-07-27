#ifndef MATRIXLED_H_
#define MATRIXLED_H_

#include "max7219.h"
#define MATRIX_SIZE 8

typedef struct{
	MAX7219_st max7219;
	uint8_t displayBuffer[MATRIX_SIZE];
}MatrixLed_st;

#ifdef __cplusplus
extern "C" {
#endif

void MatrixLed_Init(MatrixLed_st* matrixLed, SPI_Transmit spiTransmit, SPI_ChipSelect spiChipSelect);
void MatrixLed_SetPixel(MatrixLed_st* matrixLed, uint8_t x, uint8_t y, uint8_t state);
void MatrixLed_DrawDisplay(MatrixLed_st* matrixLed);

#ifdef __cplusplus
}
#endif

#endif /* INC_MATRIXLED_H_ */
