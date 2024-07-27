#include "MatrixLed.h"

void MatrixLed_Init(MatrixLed_st* matrixLed, SPI_Transmit spiTransmit, SPI_ChipSelect spiChipSelect){
	matrixLed->max7219.spiTransmit = spiTransmit;
	matrixLed->max7219.spiChipSelect = spiChipSelect;

	MAX7219_WriteReg(&matrixLed->max7219, REG_NOOP, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_SHUTDOWN, 0x01);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DISPLAY_TEST, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DECODE_MODE, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_INTENSITY, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_SCAN_LIMIT, 0x07);

	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_0, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_1, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_2, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_3, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_4, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_5, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_6, 0x00);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_7, 0x00);
}

void MatrixLed_SetPixel(MatrixLed_st* matrixLed, uint8_t x, uint8_t y, uint8_t state){
	if(state){
		matrixLed->displayBuffer[y] |= (0x80 >> x);
	}
	else{
		matrixLed->displayBuffer[y] &= ~(0x80 >> x);
	}
}

void MatrixLed_DrawDisplay(MatrixLed_st* matrixLed){
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_0, matrixLed->displayBuffer[0]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_1, matrixLed->displayBuffer[1]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_2, matrixLed->displayBuffer[2]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_3, matrixLed->displayBuffer[3]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_4, matrixLed->displayBuffer[4]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_5, matrixLed->displayBuffer[5]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_6, matrixLed->displayBuffer[6]);
	MAX7219_WriteReg(&matrixLed->max7219, REG_DIGIT_7, matrixLed->displayBuffer[7]);
}
