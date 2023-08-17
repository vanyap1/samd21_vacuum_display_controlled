#include <atmel_start.h>

#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"

#include "driver_examples.h"
#include "u8g2.h"

u8g2_t u8g2;
uint16_t seco, mine, hour;


int main(void)
{
	atmel_start_init();
	uint8_t debug_str[] = "             \n\r";
	
	u8g2_Setup_gp1287ai_256x50_f(&u8g2, U8G2_R0, vfd_spi, u8x8_avr_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);
	
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_SetContrast(&u8g2, 7);
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
	
	
	while (1) {
		
		//delay_ms(50);
		//serial_write((void *)&debug_str, sizeof(debug_str));
		
		u8g2_ClearBuffer(&u8g2);
		u8g2_DrawRFrame(&u8g2, 200, 4, 40 ,40, 5);
		u8g2_DrawStr(&u8g2, 0, 16, (char *)debug_str);
		
		//if(cdc_rx_ready()){
		u8g2_DrawStr(&u8g2, 0, 32, (char *)cdc_data_read());
		//}
		
		//u8g2_DrawStr(&u8g2, 0, 33, "Bb");
		u8g2_SendBuffer(&u8g2);
		
		sprintf((char *)debug_str , "%02d:%02d:%02d; %d",  hour, mine, seco, cdc_rx_ready());
		seco ++;
		if(seco>59){seco=0; mine++;}
		if(mine>59){mine=0; hour++;}
		if(hour>99){hour=0;}
		
	}
}
