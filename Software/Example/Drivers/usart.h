#ifndef __USART_H
#define __USART_H
#include "stm32l1xx.h"
#include "stdio.h"

enum  SERIAL_PORT
{
    SERIAL_PORT1,
    SERIAL_PORT2,
    SERIAL_PORT3,
    SERIAL_PORT4,
    SERIAL_PORT5,
    SERIAL_PORT_MAX,
};

typedef struct
{
    volatile uint8_t *data;
    volatile uint16_t read_index, write_index;
    uint16_t size;
} fifo_buffer_t;

#define FIFO_EMPTY_LEN(buf) ((buf->write_index>=buf->read_index)?(buf->size-buf->write_index+buf->read_index):(buf->read_index - buf->write_index))

#define SERIAL_STATUS_IDLE  0x00
#define SERIAL_STATUS_IT    0x01
#define SERIAL_STATUS_DMA   0x02

typedef struct
{
    fifo_buffer_t Tx_Buffer;
    fifo_buffer_t Rx_Buffer;
    USART_TypeDef *UART;
    IRQn_Type UART_IRQn;
//    DMA_Stream_TypeDef *Rx_DMAStream;
//    DMA_Stream_TypeDef *Tx_DMAStream;
    uint32_t Rx_DMAChannel;
    uint32_t Tx_DMAChannel;
    IRQn_Type UART_TX_IRQn;
    uint32_t Rx_DmaFlags, Tx_DmaFlags;
    uint8_t tx_status;
} serial_t;

void uart_hw_init(void);
void uart_hw_deinit(void);
uint16_t serial_available(void);
uint8_t serial_read_char(void);
uint8_t serial_put_char(uint8_t ch);
uint16_t serial_read(uint8_t *buffer, uint16_t length);
uint16_t serial_write(uint8_t *buffer, uint16_t length);
#endif
