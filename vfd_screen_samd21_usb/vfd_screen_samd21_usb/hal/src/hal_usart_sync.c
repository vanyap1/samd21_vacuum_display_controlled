/**
 * \file
 *
 * \brief I/O USART related functionality implementation.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include "hal_usart_sync.h"
#include <utils_assert.h>
#include <utils.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

static int32_t usart_sync_write(struct io_descriptor *const io_descr, const uint8_t *const buf, const uint16_t length);
static int32_t usart_sync_read(struct io_descriptor *const io_descr, uint8_t *const buf, const uint16_t length);

/**
 * \brief Initialize usart interface
 */
int32_t usart_sync_init(struct usart_sync_descriptor *const descr, void *const hw, void *const func)
{
	int32_t init_status;
	ASSERT(descr && hw);
	init_status = _usart_sync_init(&descr->device, hw);
	if (init_status) {
		return init_status;
	}

	descr->io.read  = usart_sync_read;
	descr->io.write = usart_sync_write;

	return ERR_NONE;
}

/**
 * \brief Uninitialize usart interface
 */
int32_t usart_sync_deinit(struct usart_sync_descriptor *const descr)
{
	ASSERT(descr);
	_usart_sync_deinit(&descr->device);

	descr->io.read  = NULL;
	descr->io.write = NULL;

	return ERR_NONE;
}

/**
 * \brief Enable usart interface
 */
int32_t usart_sync_enable(struct usart_sync_descriptor *const descr)
{
	ASSERT(descr);
	_usart_sync_enable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Disable usart interface
 */
int32_t usart_sync_disable(struct usart_sync_descriptor *const descr)
{
	ASSERT(descr);
	_usart_sync_disable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Retrieve I/O descriptor
 */
int32_t usart_sync_get_io_descriptor(struct usart_sync_descriptor *const descr, struct io_descriptor **io)
{
	ASSERT(descr && io);

	*io = &descr->io;
	return ERR_NONE;
}

/**
 * \brief Specify action for flow control pins
 */
int32_t usart_sync_set_flow_control(struct usart_sync_descriptor *const  descr,
                                    const union usart_flow_control_state state)
{
	ASSERT(descr);
	_usart_sync_set_flow_control_state(&descr->device, state);

	return ERR_NONE;
}

/**
 * \brief Set usart baud rate
 */
int32_t usart_sync_set_baud_rate(struct usart_sync_descriptor *const descr, const uint32_t baud_rate)
{
	ASSERT(descr);
	_usart_sync_set_baud_rate(&descr->device, baud_rate);

	return ERR_NONE;
}

/**
 * \brief Set usart data order
 */
int32_t usart_sync_set_data_order(struct usart_sync_descriptor *const descr, const enum usart_data_order data_order)
{
	ASSERT(descr);
	_usart_sync_set_data_order(&descr->device, data_order);

	return ERR_NONE;
}

/**
 * \brief Set usart mode
 */
int32_t usart_sync_set_mode(struct usart_sync_descriptor *const descr, const enum usart_mode mode)
{
	ASSERT(descr);
	_usart_sync_set_mode(&descr->device, mode);

	return ERR_NONE;
}

/**
 * \brief Set usart parity
 */
int32_t usart_sync_set_parity(struct usart_sync_descriptor *const descr, const enum usart_parity parity)
{
	ASSERT(descr);
	_usart_sync_set_parity(&descr->device, parity);

	return ERR_NONE;
}

/**
 * \brief Set usart stop bits
 */
int32_t usart_sync_set_stopbits(struct usart_sync_descriptor *const descr, const enum usart_stop_bits stop_bits)
{
	ASSERT(descr);
	_usart_sync_set_stop_bits(&descr->device, stop_bits);

	return ERR_NONE;
}

/**
 * \brief Set usart character size
 */
int32_t usart_sync_set_character_size(struct usart_sync_descriptor *const descr, const enum usart_character_size size)
{
	ASSERT(descr);
	_usart_sync_set_character_size(&descr->device, size);

	return ERR_NONE;
}

/**
 * \brief Retrieve the state of flow control pins
 */
int32_t usart_sync_flow_control_status(const struct usart_sync_descriptor *const descr,
                                       union usart_flow_control_state *const     state)
{
	ASSERT(descr && state);
	*state = _usart_sync_get_flow_control_state(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Check if the usart transmitter is empty
 */
int32_t usart_sync_is_tx_empty(const struct usart_sync_descriptor *const descr)
{
	ASSERT(descr);
	return _usart_sync_is_ready_to_send(&descr->device);
}

/**
 * \brief Check if the usart receiver is not empty
 */
int32_t usart_sync_is_rx_not_empty(const struct usart_sync_descriptor *const descr)
{
	ASSERT(descr);
	return _usart_sync_is_byte_received(&descr->device);
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t usart_sync_get_version(void)
{
	return DRIVER_VERSION;
}

/*
 * \internal Write the given data to usart interface
 *
 * \param[in] descr The pointer to an io descriptor
 * \param[in] buf Data to write to usart
 * \param[in] length The number of bytes to write
 *
 * \return The number of bytes written.
 */
static int32_t usart_sync_write(struct io_descriptor *const io_descr, const uint8_t *const buf, const uint16_t length)
{
	uint32_t                      offset = 0;
	struct usart_sync_descriptor *descr  = CONTAINER_OF(io_descr, struct usart_sync_descriptor, io);

	ASSERT(io_descr && buf && length);
	while (!_usart_sync_is_ready_to_send(&descr->device))
		;
	do {
		_usart_sync_write_byte(&descr->device, buf[offset]);
		while (!_usart_sync_is_ready_to_send(&descr->device))
			;
	} while (++offset < length);
	while (!_usart_sync_is_transmit_done(&descr->device))
		;
	return (int32_t)offset;
}

/*
 * \internal Read data from usart interface
 *
 * \param[in] descr The pointer to an io descriptor
 * \param[in] buf A buffer to read data to
 * \param[in] length The size of a buffer
 *
 * \return The number of bytes read.
 */
static int32_t usart_sync_read(struct io_descriptor *const io_descr, uint8_t *const buf, const uint16_t length)
{
	uint32_t                      offset = 0;
	struct usart_sync_descriptor *descr  = CONTAINER_OF(io_descr, struct usart_sync_descriptor, io);

	ASSERT(io_descr && buf && length);
	do {
		while (!_usart_sync_is_byte_received(&descr->device))
			;
		buf[offset] = _usart_sync_read_byte(&descr->device);
	} while (++offset < length);

	return (int32_t)offset;
}

