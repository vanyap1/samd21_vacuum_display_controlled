/*
* Code generated from Atmel Start.
*
* This file will be overwritten when reconfiguring your Atmel Start project.
* Please copy examples or other code you want to keep to a separate file
* to avoid losing it when reconfiguring.
*/


#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"
#include <u8g2.h>

uint32_t offset = 0;
uint8_t sercom_data_ready = 0;
uint8_t rx_buff[256] = "test";
/**
* Example of using VFD_SPI to write "Hello World" using the IO abstraction.
*/
static uint8_t example_VFD_SPI[12] = "Hello World!";

void VFD_SPI_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&VFD_SPI, &io);

	spi_m_sync_enable(&VFD_SPI);
	io_write(io, example_VFD_SPI, 12);
}
void vfd_write_data(uint8_t* buff, uint16_t len){
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&VFD_SPI, &io);
	spi_m_sync_enable(&VFD_SPI);
	io_write(io, buff, len);
	
}

void vfd_cs_set(bool state){
	gpio_set_pin_level(VFD_CS, !state);
}

uint8_t u8x8_avr_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr){
	//uint8_t cycles;

	switch(msg)
	{
		case U8X8_MSG_DELAY_NANO:     // delay arg_int * 1 nano second
		//delay_us(10);
		break;
		case U8X8_MSG_DELAY_100NANO:    // delay arg_int * 100 nano seconds
		//delay_us(10);
		break;
		case U8X8_MSG_DELAY_10MICRO:    // delay arg_int * 10 micro seconds
		
		//delay_us(10);
		break;
		case U8X8_MSG_DELAY_MILLI:      // delay arg_int * 1 milli second
		
		//delay_us(10);
		break;
		default:
		return 0;
	}
	return 0;
}
uint8_t vfd_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	
	switch(msg)
	{
		case U8X8_MSG_BYTE_SEND:
		vfd_write_data(arg_ptr, arg_int);
		break;
		case U8X8_MSG_BYTE_INIT:
		/* disable chipselect */
		vfd_cs_set(0);
		break;
		case U8X8_MSG_BYTE_SET_DC:
		u8x8_gpio_SetDC(u8x8, arg_int);
		break;
		case U8X8_MSG_BYTE_START_TRANSFER:
		vfd_cs_set(1);
		break;
		case U8X8_MSG_BYTE_END_TRANSFER:
		vfd_cs_set(0);
		break;
		default:
		return 0;
	}
	return 1;
}


void CDC_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&CDC, &io);
	usart_sync_enable(&CDC);
	io_write(io, (uint8_t *)"Hello World!", 12);
}

void USART_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART, &io);
	usart_sync_enable(&USART);
	io_write(io, (uint8_t *)"Hello World!", 12);
}

void serial_write(uint8_t *data, uint8_t data_len){
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&CDC, &io);
	usart_sync_enable(&CDC);
	io_write(io, data, data_len);
}

uint8_t cdc_rx_ready(){
	return sercom_data_ready;
}

const char* cdc_data_read(void){
	sercom_data_ready = 0;
	//offset=0;
	gpio_set_pin_level(LED, true);
	return (void *)rx_buff;
}

void SERCOM3_Handler() {
	if (SERCOM3->USART.INTFLAG.bit.RXC)
	{
		gpio_set_pin_level(LED, false);
		SERCOM3->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_RXC;
		SERCOM3->USART.CTRLA.bit.RXPO = 0;
		uint8_t databyte = SERCOM3->USART.DATA.reg;
		if (databyte == '\r'){
			sercom_data_ready = 1;
			offset=0;
		}
		rx_buff[offset] = databyte;
		offset++;
	}

	if (SERCOM3->USART.INTFLAG.bit.TXC)
	{
		SERCOM3->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_TXC;
	}
}


