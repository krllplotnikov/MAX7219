# Аппаратно независимый драйвер для работы с микросхемой MAX7219
Для того чтобы использовать драйвер нужно:
- Добавить файлы max7219.h и max7219.c в проект
- Объявить функцию передачи данных по SPI
- При инициализации передать указатель на функцию

Пример использования драйвера можно найти в файле MatrixLed. Данный пример описывает взаимодествие драйвера с модулем светодиодной матрицы на базе MAX7219

Пример использования на STM32:
```C
#include "main.h"
#include "MatrixLed.h"

SPI_HandleTypeDef hspi1;

MatrixLed_st matrixLed_first;

void MatrixLed_SPI_ChipSelect_first(uint8_t level){
	HAL_GPIO_WritePin(SPI1_CS1_GPIO_Port, SPI1_CS1_Pin, level);
}
void MatrixLed_SPI_Transmit_first(uint8_t* data, size_t size){
	HAL_SPI_Transmit(&hspi1, data, size, 10);
}

int main(void)
{
  MatrixLed_Init(&matrixLed_first, MatrixLed_SPI_Transmit_first, MatrixLed_SPI_ChipSelect_first);

  while (1)
  {
	  uint8_t x = 0;
	  uint8_t y = 0;
	  while(x < MATRIX_SIZE && y < MATRIX_SIZE){
		  MatrixLed_SetPixel(&matrixLed_first, x, y, 1);
		  MatrixLed_DrawDisplay(&matrixLed_first);
		  HAL_Delay(1000);
		  MatrixLed_SetPixel(&matrixLed_first, x, y, 0);
		  MatrixLed_DrawDisplay(&matrixLed_first);
		  x++;
		  y++;
	  }
  }
}

```
Пример использования на Atmega328(на ардуиновские функции не обращайте внимание, использовал их для упрощения кода. Работа с SPI описана без использования использования ардуино):
```C
#include <Arduino.h>
#include "MatrixLed.h"

MatrixLed_st matrixLed_first;

void MatrixLed_SPI_ChipSelect_first(uint8_t level){
  if(!level){
    PORTB &= ~(0x04);
  }
  else{
    PORTB |= 0x04;
  }
}
void MatrixLed_SPI_Transmit_first(uint8_t* data, size_t size){
  for(size_t i = 0; i < size; i++){
    SPDR = data[i];
    while((SPSR & 0x80) == 0);
  }
}

void setup() {
  DDRB = (DDRB & 0xC3) | 0x2C;
  SPCR |= 0x50;
  MatrixLed_Init(&matrixLed_first, MatrixLed_SPI_Transmit_first, MatrixLed_SPI_ChipSelect_first);
}


void loop() {
  uint8_t x = 0;
  uint8_t y = 0;
  while(x < MATRIX_SIZE && y < MATRIX_SIZE){
    MatrixLed_SetPixel(&matrixLed_first, x, y, 1);
    MatrixLed_DrawDisplay(&matrixLed_first);
    delay(1000);
    MatrixLed_SetPixel(&matrixLed_first, x, y, 0);
    MatrixLed_DrawDisplay(&matrixLed_first);
    x++;
    y++;
  }
}
```
