# Аппаратно независимый драйвер для работы с микросхемой MAX7219
Для того чтобы использовать драйвер нужно:
- Добавить файлы max7219.h и max7219.c в проект
- Объявить функцию передачи данных по SPI
- При инициализации передать указатель на функцию

Пример использования драйвера можно найти в файле MatrixLed (библиотека на базе драйвера для модуля светодиодной матрицы).

Пример использования на STM32:
```C
#include "main.h"
#include "MatrixLed.h"

SPI_HandleTypeDef hspi1;

MatrixLed_st matrixLed;

void MatrixLed_SPI_ChipSelect (uint8_t level){
	HAL_GPIO_WritePin(SPI1_CS1_GPIO_Port, SPI1_CS1_Pin, level);
}
void MatrixLed_SPI_Transmit (uint8_t* data, size_t size){
	HAL_SPI_Transmit(&hspi1, data, size, 10);
}

int main(void)
{
    MatrixLed_Init(&matrixLed, MatrixLed_SPI_Transmit, MatrixLed_SPI_ChipSelect);
    
        while (1)
        {
            uint8_t x = 0;
            uint8_t y = 0;
            while(x < MATRIX_SIZE && y < MATRIX_SIZE){
            MatrixLed_SetPixel(&matrixLed, x, y, 1);
            MatrixLed_DrawDisplay(&matrixLed);
            HAL_Delay(1000);
            MatrixLed_SetPixel(&matrixLed, x, y, 0);
            MatrixLed_DrawDisplay(&matrixLed);
            x++;
            y++;
        }
    }
}
```

Пример использования на ESP32:
```C
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "MatrixLed.h"

#define MOSI_PIN    GPIO_NUM_4
#define CS_PIN      GPIO_NUM_3
#define CLK_PIN     GPIO_NUM_2

spi_device_handle_t spi2;

MatrixLed_st matrixLed;

void MatrixLed_SPI_Transmit(uint8_t* data, size_t size){
    spi_transaction_t transaction = {
        .tx_buffer = data,
        .length = size * 8
    };

    spi_device_polling_transmit(spi2, &transaction);	
}

static void SPI_Init() {
    spi_bus_config_t buscfg={
        .miso_io_num = -1,
        .mosi_io_num = MOSI_PIN,
        .sclk_io_num = CLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 8,
    };

    spi_device_interface_config_t devcfg={
        .clock_speed_hz = 1000000,
        .mode = 0,
        .spics_io_num = CS_PIN,
        .queue_size = 1,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .pre_cb = NULL,
        .post_cb = NULL,
    };

    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST, &devcfg, &spi2);
};

void app_main(void)
{
    SPI_Init();
    MatrixLed_Init(&matrixLed, MatrixLed_SPI_Transmit, NULL);
    
    while (1) {
        uint8_t x = 0;
        uint8_t y = 0;
        while(x < MATRIX_SIZE && y < MATRIX_SIZE){
            MatrixLed_SetPixel(&matrixLed, x, y, 1);
            MatrixLed_DrawDisplay(&matrixLed);
            vTaskDelay(1000/portTICK_PERIOD_MS);
            MatrixLed_SetPixel(&matrixLed, x, y, 0);
            MatrixLed_DrawDisplay(&matrixLed);
            x++;
            y++;
        }    
    }
}

```
Пример использования на AVR:
```C
#include "MatrixLed.h"

MatrixLed_st matrixLed;

void MatrixLed_SPI_ChipSelect(uint8_t level){
  if(!level){
    PORTB &= ~(0x04);
  }
  else{
    PORTB |= 0x04;
  }
}
void MatrixLed_SPI_Transmit(uint8_t* data, size_t size){
  for(size_t i = 0; i < size; i++){
    SPDR = data[i];
    while(!(SPSR & (1 << SPIF)));
  }
}

void SPI_Init(){
  DDRB = (1 << DDB2)|(1 << DDB3)|(1 << DDB5);
  SPCR = (1 << SPE)|(1 << MSTR)|(1 << SPR0);
}

void setup() {
  SPI_Init();
  MatrixLed_Init(&matrixLed, MatrixLed_SPI_Transmit, MatrixLed_SPI_ChipSelect);
}


void loop() {
  uint8_t x = 0;
  uint8_t y = 0;
  while(x < MATRIX_SIZE && y < MATRIX_SIZE){
    MatrixLed_SetPixel(&matrixLed, x, y, 1);
    MatrixLed_DrawDisplay(&matrixLed);
    delay(1000);
    MatrixLed_SetPixel(&matrixLed, x, y, 0);
    MatrixLed_DrawDisplay(&matrixLed);
    x++;
    y++;
  }
}
```