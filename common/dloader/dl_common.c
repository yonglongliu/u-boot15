#include <common.h>
#include "dl_common.h"

unsigned short fdl_calc_checksum(unsigned char *data, unsigned long len)
{
	unsigned short num = 0;
	unsigned long chkSum = 0;
	while(len>1) {
		num = (unsigned short)(*data);
		data++;
		num |= (((unsigned short)(*data))<<8);
		data++;
		chkSum += (unsigned long)num;
		len -= 2;
	}
	if(len) {
		chkSum += *data;
	}
	chkSum = (chkSum >> 16) + (chkSum & 0xffff);
	chkSum += (chkSum >> 16);
	return (~chkSum);
}

unsigned char fdl_check_crc(uint8_t* buf, uint32_t size,uint32_t checksum)
{
	uint16_t crc;

	crc = fdl_calc_checksum(buf,size);
	debugf("fdl_check_crc  calcout = 0x%x,org = 0x%x\n",crc,checksum);
	return (crc == (uint16_t)checksum);
}

//This param src must be 4 byte aligned.
unsigned long Get_CheckSum (const unsigned char *src, int len)
{
    unsigned long sum =0;

    while (len > 3)
    {
        //sum += *((unsigned long *)src)++;
        sum += *src++;
        sum += *src++;
        sum += *src++;
        sum += *src++;

        len-=4;
    }

    while (len)
    {
        sum +=*src++;
        len--;
    }

    return sum;
}

