/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_spi_m_sync.h>

#include <hal_usart_sync.h>

#include <hal_usart_sync.h>

#include <hal_delay.h>

#include "hal_usb_device.h"

extern struct spi_m_sync_descriptor VFD_SPI;

extern struct usart_sync_descriptor CDC;

extern struct usart_sync_descriptor USART;

void VFD_SPI_PORT_init(void);
void VFD_SPI_CLOCK_init(void);
void VFD_SPI_init(void);

void CDC_PORT_init(void);
void CDC_CLOCK_init(void);
void CDC_init(void);

void USART_PORT_init(void);
void USART_CLOCK_init(void);
void USART_init(void);

void delay_driver_init(void);

void USB_0_CLOCK_init(void);
void USB_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
