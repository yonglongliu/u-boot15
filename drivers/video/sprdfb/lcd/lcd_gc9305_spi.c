/* drivers/video/sc8810/lcd_gc9305_spi.c
 *
 *
 *
 *
 * Copyright (C) 2010 Spreadtrum
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "../sprdfb_chip_common.h"
#include "../sprdfb.h"
#include "../sprdfb_panel.h"
#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printf
#else
#define LCD_PRINT(...)
#endif
#define REG32(x)              (*((volatile uint32 *)(x)))
#define GC9305_SpiWriteCmd(cmd) \
{ \
	spi_send_cmd((cmd & 0xFF));\
}

#define  GC9305_SpiWriteData(data)\
{ \
	spi_send_data((data & 0xFF));\
}

#define  GC9305_SpiRead(data,len)\
{ \
	spi_read(data,len);\
}
#define BGRA32toRBG565(b,g,r)		((((r>>3)&0x1f)<<11)|(((g>>2)&0x3f)<<5)|(((b>>3)&0x1f)<<0))
#define LCM_GPIO_RSTN			(50)
#define GC9305_SPI_SPEED 		(48*1000*1000UL)
#define	SPI_MODE_0	(0|0)

extern unsigned char start_send_pixels_flag;

static int32_t gc9305_refresh(struct panel_spec *self,void *base)
{
	int i = 0;
	uint16_t *prgb = (uint16_t *)base;
	uint16_t rgb;
	LCD_PRINT("gc9305_freshbuffer\r\n");
	start_send_pixels_flag = 1;
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	sprd_gpio_set(NULL,91,1);
	for(i = 0 ; i < 240*320;i++)
	{
		rgb = *prgb++;
		GC9305_SpiWriteData(rgb>>8);
		GC9305_SpiWriteData(rgb&0xff);
	}
	start_send_pixels_flag = 0;
	GC9305_SpiWriteCmd(0x29);
	return 0;
}
static int32_t gc9305_reset(void)
{
	static int32_t is_first_run = 1;
	if(is_first_run)
	{
		sprd_gpio_request(NULL,LCM_GPIO_RSTN);
		sprd_gpio_direction_output(NULL,LCM_GPIO_RSTN,1);
		is_first_run = 0;
	}
	sprd_gpio_set(NULL,LCM_GPIO_RSTN,1);
	mdelay(10);
	sprd_gpio_set(NULL,LCM_GPIO_RSTN,0);
	mdelay(10);
	sprd_gpio_set(NULL,LCM_GPIO_RSTN,1);
	mdelay(20);
}

static int32_t gc9305_init(struct panel_spec *self)
{
	uint32_t data = 0;
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	gc9305_reset();


GC9305_SpiWriteCmd(0xfe);
GC9305_SpiWriteCmd(0xef);
GC9305_SpiWriteCmd(0x36);
GC9305_SpiWriteData(0x48);
GC9305_SpiWriteCmd(0x3a);
GC9305_SpiWriteData(0x05);
GC9305_SpiWriteCmd(0x35);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteCmd(0xa4);
GC9305_SpiWriteData(0x44);
GC9305_SpiWriteData(0x44);
GC9305_SpiWriteCmd(0xa5);
GC9305_SpiWriteData(0x42);
GC9305_SpiWriteData(0x42);
GC9305_SpiWriteCmd(0xaa);
GC9305_SpiWriteData(0x88);
GC9305_SpiWriteData(0x88);
GC9305_SpiWriteCmd(0xe8);
GC9305_SpiWriteData(0x21);
GC9305_SpiWriteData(0x72);
GC9305_SpiWriteCmd(0xe3);
GC9305_SpiWriteData(0x01);
GC9305_SpiWriteData(0x18);
GC9305_SpiWriteCmd(0xe1);
GC9305_SpiWriteData(0x10);
GC9305_SpiWriteData(0x0a);
GC9305_SpiWriteCmd(0xAC);
GC9305_SpiWriteData(0x00); 
GC9305_SpiWriteCmd(0xae); 
GC9305_SpiWriteData(0x2b);
GC9305_SpiWriteCmd(0xad); 
GC9305_SpiWriteData(0x33);
GC9305_SpiWriteCmd(0xAf);
GC9305_SpiWriteData(0x55);
GC9305_SpiWriteCmd(0xa6);
GC9305_SpiWriteData(0x29);
GC9305_SpiWriteData(0x29);
GC9305_SpiWriteCmd(0xa7);
GC9305_SpiWriteData(0x27);
GC9305_SpiWriteData(0x27);
GC9305_SpiWriteCmd(0xa8);
GC9305_SpiWriteData(0x17);
GC9305_SpiWriteData(0x17);
GC9305_SpiWriteCmd(0xa9);
GC9305_SpiWriteData(0x26);
GC9305_SpiWriteData(0x26);
GC9305_SpiWriteCmd(0x2a);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0xef);
GC9305_SpiWriteCmd(0x2b);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0x01);
GC9305_SpiWriteData(0x3f);
GC9305_SpiWriteCmd(0xF0);
GC9305_SpiWriteData(0x02);
GC9305_SpiWriteData(0x02);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0x03);
GC9305_SpiWriteData(0x09);
GC9305_SpiWriteData(0x0c);
GC9305_SpiWriteCmd(0xF1);
GC9305_SpiWriteData(0x01);
GC9305_SpiWriteData(0x03);
GC9305_SpiWriteData(0x00);
GC9305_SpiWriteData(0x04);
GC9305_SpiWriteData(0x12);
GC9305_SpiWriteData(0x13);
GC9305_SpiWriteCmd(0xF2);
GC9305_SpiWriteData(0x0c);
GC9305_SpiWriteData(0x07);
GC9305_SpiWriteData(0x34);
GC9305_SpiWriteData(0x03);
GC9305_SpiWriteData(0x04);
GC9305_SpiWriteData(0x46);
GC9305_SpiWriteCmd(0xF3);
GC9305_SpiWriteData(0x14);
GC9305_SpiWriteData(0x0B);
GC9305_SpiWriteData(0x42);
GC9305_SpiWriteData(0x04);
GC9305_SpiWriteData(0x05);
GC9305_SpiWriteData(0x50);
GC9305_SpiWriteCmd(0xF4);
GC9305_SpiWriteData(0x09);
GC9305_SpiWriteData(0x13);
GC9305_SpiWriteData(0x13);
GC9305_SpiWriteData(0x1e);
GC9305_SpiWriteData(0x22);
GC9305_SpiWriteData(0x0F);
GC9305_SpiWriteCmd(0xF5);
GC9305_SpiWriteData(0x08);
GC9305_SpiWriteData(0x0e);
GC9305_SpiWriteData(0x0e);
GC9305_SpiWriteData(0x22);
GC9305_SpiWriteData(0x2b);
GC9305_SpiWriteData(0x0f);
GC9305_SpiWriteCmd(0x11);	
mdelay(120);	
GC9305_SpiWriteCmd(0x29);
GC9305_SpiWriteCmd(0x2c);
	LCD_PRINT("gc9305_init\n");
}

static int32_t gc9305_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	if(is_sleep==1){
		//Sleep In
		GC9305_SpiWriteCmd(0x28);
		mdelay(120);
		GC9305_SpiWriteCmd(0x10);
		mdelay(10);
	}else{
		//Sleep Out
		GC9305_SpiWriteCmd(0x11);
		mdelay(120);
		GC9305_SpiWriteCmd(0x29);
		mdelay(10);
	}
	return 0;
}



static int32_t gc9305_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	uint32_t *test_data[4] = {0};
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;


	GC9305_SpiWriteCmd(0x2A);
	GC9305_SpiWriteData((left>>8));// set left address
	GC9305_SpiWriteData((left&0xff));
	GC9305_SpiWriteData((right>>8));// set right address
	GC9305_SpiWriteData((right&0xff));

	GC9305_SpiWriteCmd(0x2B);
	GC9305_SpiWriteData((top>>8));// set left address
	GC9305_SpiWriteData((top&0xff));
	GC9305_SpiWriteData((bottom>>8));// set bottom address
	GC9305_SpiWriteData((bottom&0xff));
	GC9305_SpiWriteCmd(0x2C);

	return 0;
}
static int32_t gc9305_invalidate(struct panel_spec *self)
{
	LCD_PRINT("gc9305_invalidate\n");

	return self->ops->panel_set_window(self, 0, 0,
		self->width - 1, self->height - 1);
}



static int32_t gc9305_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	LCD_PRINT("gc9305_invalidate_rect \n");

	return self->ops->panel_set_window(self, left, top,
			right, bottom);
}




static unsigned char GC9305_OTP_read_bit(struct panel_spec *self,unsigned char address)
{
	unsigned char  read_value;
	uint32_t lcm_id[1]={0};
	
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;
	spi_clock_set_t spi_clock_set = self->info.spi->ops->spi_clock_set;
	
	GC9305_SpiWriteCmd(0xe5);
	GC9305_SpiWriteData(0x1c);
	GC9305_SpiWriteCmd(0xe6);
	GC9305_SpiWriteData(address);
	GC9305_SpiWriteCmd(0xe5);
	GC9305_SpiWriteData(0x3c);
	
	GC9305_SpiWriteCmd(0xD5);
        GC9305_SpiRead(lcm_id,1);
        read_value=lcm_id[0];
        LCD_PRINT("GC9305_OTP_read_bit = %d\n",read_value);
        return read_value > 0;
}




unsigned char GC9305_OTP_read_byte(struct panel_spec *self,unsigned char address)
{
	unsigned char m=0;
	unsigned char n=0;
	unsigned char bit_value,otp_data;

	otp_data = 0;
	for(m=0;m<8;m++)
	{ 
		n=m<<5;
		n=n|address;
		bit_value = GC9305_OTP_read_bit(self,n) & 0x01;
		otp_data = (bit_value<<m) | otp_data;
 	}
 		
        LCD_PRINT("GC9305_OTP_read_byte = %d\n",otp_data);
 	return otp_data;
}



uint32_t gc9305_manufacture_id(struct panel_spec *self)
{
	unsigned char ID1,ID2,ID3;
	uint32_t data;
        spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;
	spi_clock_set_t spi_clock_set = self->info.spi->ops->spi_clock_set;
	GC9305_SpiWriteCmd(0xFE);
	GC9305_SpiWriteCmd(0xEF);
	GC9305_SpiWriteCmd(0xe4);
	GC9305_SpiWriteData(0x05);
	
	ID1 = GC9305_OTP_read_byte(self,0x14);
	ID2 = GC9305_OTP_read_byte(self,0x15);
	ID3 = GC9305_OTP_read_byte(self,0x16);
	
	GC9305_SpiWriteCmd(0xe5);
	GC9305_SpiWriteData(0x00);
	data = ID1<<16|ID2<<8|ID3;
        LCD_PRINT("gc9305_manufacture_id =0x%x \n",data);

        return data;

}

static int32_t gc9305_read_id(struct panel_spec *self)
{
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;
	spi_clock_set_t spi_clock_set = self->info.spi->ops->spi_clock_set;
	uint32_t i=0;
	uint32_t lcm_id[4]={0};
	uint32_t lcm_id2[1]={0};
	uint32_t otp_id;
	
	spi_clock_set(6000000);
	gc9305_reset();
	
	otp_id = gc9305_manufacture_id(self);
	
	for(i=0;i<4;i++){
		GC9305_SpiWriteCmd(0xFE);
		GC9305_SpiWriteCmd(0xEF);
		GC9305_SpiWriteCmd(0x04);
		GC9305_SpiRead(lcm_id,4);
		LCD_PRINT("sprdfb:gc9305_read_id register 04h id[0-3] = 0x%x %x %x %x\n",lcm_id[0],lcm_id[1],lcm_id[2],lcm_id[3]);
		if((lcm_id[1] == 0x93 && lcm_id[2] == 0x05) && otp_id != 0x119305) 
		{
			spi_clock_set(24000000);
			return 0x9305;
		}
	}
	return 0x00;

}

static struct panel_operations lcd_gc9305_spi_operations = {
	.panel_init = gc9305_init,
	.panel_set_window = gc9305_set_window,
	.panel_invalidate_rect= gc9305_invalidate_rect,
	.panel_invalidate = gc9305_invalidate,
	.panel_enter_sleep = gc9305_enter_sleep,
	.panel_readid          = gc9305_read_id,
	.panel_refresh		=gc9305_refresh,
	//.panel_reset = gc9305_reset,
};

static struct info_spi lcd_gc9305_spi_info = {
	.bus_num = 0,
	.cs = 0,
	.cd_gpio = 138,
	.spi_mode = 1,
	.spi_pol_mode = SPI_MODE_0,
	.speed = GC9305_SPI_SPEED,
};

struct panel_spec lcd_gc9305_spi_spec = {
	.width = 240,
	.height = 320,
	.fps = 33,
	.type = SPRDFB_PANEL_TYPE_SPI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.spi = &lcd_gc9305_spi_info
	},
	.ops = &lcd_gc9305_spi_operations,
};
