
#include "derivative.h"
#include "UART.h"
/*
 * UART0: TX=PTB1; RX=PTB0;
 * UART1: TX=PTF3; RX=PTF2;
 * UART2: TX=PTD7; RX=PTD6;
 *
 * */
// Baud Rate = 9600, 1 stop bit, 8 bit format, no parity
void init_UART(void)  {
  SIM_SCGC |=  SIM_SCGC_UART1_MASK;  // 20MHz BUS_CLOCK
  UART1_BDH = 0;
  UART1_BDL = 130;                  // 20MHz/9600/16 = ~130
  /*UART1_BDL = 21;		*/				/* 20MHz / 57600/16 = 10 */
  UART1_C1  = 0;                     // Initialize control bits for communication:
                                     // M  = 0 (default, 8 bit format)
                                     // PE (Parity Enable) = 0 (default, no parity)
   UART1_C2 = 0x08;                  // 1 Transmitter on; 0 Receiver off
  SIM_PINSEL1 |= SIM_PINSEL1_UART1PS_MASK; // UART1PS = 1 => UART1_TX on PTF3, UART1_RX on PTF2
}

// sending single Char
void send_char(char send) {
  while((UART1_S1 & UART_S1_TDRE_MASK)==0); // Wait until the buffer is empty
  (void)UART1_S1;                    // Read UART1_S1 register to clear TDRE
  UART1_D=send;                      // Send char
}

void UART_send_String(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)	/*send string up to null */
	{
		send_char(str[j]);
		j++;
	}
}
