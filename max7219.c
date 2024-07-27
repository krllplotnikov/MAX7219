#include "max7219.h"

void MAX7219_Init(MAX7219_st* max7219, SPI_Transmit spiTransmit, SPI_ChipSelect spiChipSelect){
	max7219->spiTransmit = spiTransmit;
	max7219->spiChipSelect = spiChipSelect;
}

void MAX7219_WriteReg(MAX7219_st* max7219, MAX7219_Register_t reg, uint8_t data){
	if(max7219->spiChipSelect != NULL){
		max7219->spiChipSelect(0);
	}
	max7219->spiTransmit(&reg, 1);
	max7219->spiTransmit(&data, 1);
	if(max7219->spiChipSelect != NULL){
		max7219->spiChipSelect(1);
	}
}
