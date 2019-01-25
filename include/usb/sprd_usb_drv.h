/******************************************************************************

  Copyright (C), 2001-2014, Spreatrum Communications Inc.

 ******************************************************************************
  File Name     : sprd_usb_drv.h
  Version       : 1.0 Beta
  Author        : Miao.Zhu
  Created       : 2014/12/25
  Last Modified :
  Description   : This file provides public macroes and declaration of functions.
  Function List : NA
  History       :
  1.Date        : 2014/12/25
    Author      : Miao.Zhu
    Modification: Created file
******************************************************************************/
#ifndef __USB_DRV_H__
#define __USB_DRV_H__


#define MAX_RECV_LENGTH (1024*63)

extern uint8_t usb_get_entry();
extern int usb_get_packet(unsigned char* buf, unsigned int len);
extern void usb_send(unsigned char *buf, unsigned int len);
extern void usb_core_init(unsigned long reg_base_addr,
	uint32_t autodl_mode);
extern void usb_init(unsigned int);

#endif

