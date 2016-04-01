#include "usart.h"
#include "sim900.h"

#define BUFFER_SIZE   (512)
static serial_t serial_port;
static uint8_t tx_buffer[BUFFER_SIZE];
static uint8_t rx_buffer[BUFFER_SIZE];


void uart_hw_init(void)
{
    serial_t *serial = &serial_port;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;                                          //定义GPIO初始化结构体
    USART_InitTypeDef USART_InitStructure;                                        //定义USART初始化结构体
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);       

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);
	  /* Connect alternate function */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 |GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);			  

    /*配置USART1的模式*/
    USART_InitStructure.USART_BaudRate = 115200;                                  //设置USART的波特率为115200
    USART_InitStructure.USART_Parity = USART_Parity_No;                           //设置USART的校验位为None
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                   //设置USART的数据位为8bit
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                        //设置USART的停止位为1
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //失能硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               //设置USART的模式为发送接收模式
    USART_Init(USART1, &USART_InitStructure);                                     //初始化USART1
    USART_Cmd(USART1, ENABLE);                                                    //使能USART
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    serial = &serial_port;
    /* init serial1 port */
    serial->UART = USART1;
    serial->UART_IRQn = USART1_IRQn;


    serial->Tx_Buffer.data = tx_buffer;
    serial->Tx_Buffer.size = BUFFER_SIZE;
    serial->Tx_Buffer.read_index = 0;
    serial->Tx_Buffer.write_index = 0;

    serial->Rx_Buffer.data = rx_buffer;
    serial->Rx_Buffer.size = BUFFER_SIZE;
    serial->Rx_Buffer.read_index = 0;
    serial->Rx_Buffer.write_index = 0;
}

uint16_t serial_available(void)
{
    uint16_t len = 0;

    serial_t *serial = &serial_port;
    // CurrDataCounter = serial->Rx_DMAStream->NDTR;

    if (serial->Rx_Buffer.read_index > serial->Rx_Buffer.write_index)
    {
        len = serial->Rx_Buffer.size + serial->Rx_Buffer.write_index - serial->Rx_Buffer.read_index;
    }
    else if (serial->Rx_Buffer.read_index  < serial->Rx_Buffer.write_index)
    {
        len = serial->Rx_Buffer.write_index - serial->Rx_Buffer.read_index;
    }

    //serial->Rx_Buffer.write_index = CurrDataCounter;

    return len;
}
uint8_t serial_read_char(void)
{
    uint8_t ch = 0;

    ch = serial_port.Rx_Buffer.data[serial_port.Rx_Buffer.read_index];
    serial_port.Rx_Buffer.read_index = (serial_port.Rx_Buffer.read_index + 1) % serial_port.Rx_Buffer.size;

    return ch;
}
uint8_t serial_put_char(uint8_t ch)
{

    while (!(serial_port.UART->SR & USART_FLAG_TXE));
    serial_port.UART->DR = ch;

    return ch;
}
uint16_t serial_read(uint8_t *buffer, uint16_t length)
{
    uint16_t i = 0;

    serial_t *serial = &serial_port;
    for (i = 0; i < length; i++)
    {
        buffer[i] = serial->Rx_Buffer.data[serial->Rx_Buffer.read_index];
        serial->Rx_Buffer.read_index = (serial->Rx_Buffer.read_index + 1) % serial->Rx_Buffer.size;
    }
    return i;
}

uint16_t serial_write(uint8_t *buffer, uint16_t length)
{
    uint16_t i = 0;

    serial_t *serial = &serial_port;
    for (i = 0; i < length; i++)
    {
        serial->Tx_Buffer.data[serial->Tx_Buffer.write_index] = buffer[i];
        serial->Tx_Buffer.write_index = (serial->Tx_Buffer.write_index + 1) % serial->Rx_Buffer.size;
    }
    //USART_ITConfig(serial->UART, USART_IT_TXE, ENABLE);
    return i;

}

//void USART1_IRQHandler(void)
//{
//    serial_t *serial = &serial_port;
//    uint32_t status = serial->UART->SR;
//    /* enter interrupt */
//    if (status & USART_FLAG_RXNE)
//    {   
////#ifdef SIM_DEBUG
//					  while (!(USART3->SR & USART_FLAG_TXE));
//       USART3->DR = USART1->DR;
//			 
////#else
//        serial->Rx_Buffer.data[serial->Rx_Buffer.write_index] = serial->UART->DR;
//        serial->Rx_Buffer.write_index = (serial->Rx_Buffer.write_index + 1) % serial->Rx_Buffer.size;
////#endif
//    }
//    if (status & USART_FLAG_TXE)
//    {
//        if (serial->Tx_Buffer.read_index != serial->Tx_Buffer.write_index)
//        {
//            serial->UART->DR = serial->Tx_Buffer.data[serial->Tx_Buffer.read_index];
//            serial->Tx_Buffer.read_index = (serial->Tx_Buffer.read_index + 1) % serial->Tx_Buffer.size;
//        }
//        else
//        {
//            serial->Tx_Buffer.read_index = 0;
//            serial->Tx_Buffer.write_index = 0;
//            USART_ITConfig(serial->UART, USART_IT_TXE, DISABLE);
//        }
//    }
//}





