/*
* Code generated from Atmel Start.
*
* This file will be overwritten when reconfiguring your Atmel Start project.
* Please copy examples or other code you want to keep to a separate file
* to avoid losing it when reconfiguring.
*/
#include <stdint.h>
#include <stdbool.h>
#include <u8g2.h>

#ifndef DRIVER_EXAMPLES_H_INCLUDED
#define DRIVER_EXAMPLES_H_INCLUDED

#ifdef __cplusplus
extern "C" {
	#endif

	void VFD_SPI_example(void);
	void CDC_example(void);
	void vfd_write_data(uint8_t* buff, uint16_t len);
	void vfd_cs_set(bool state);
	uint8_t u8x8_avr_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
	uint8_t vfd_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
	void USART_example(void);
	void serial_write(uint8_t *data, uint8_t data_len);
	uint8_t cdc_rx_ready();
	const char* cdc_data_read(void);


	#ifdef __cplusplus
}
#endif
#endif // DRIVER_EXAMPLES_H_INCLUDED
