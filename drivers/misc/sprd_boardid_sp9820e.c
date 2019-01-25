#include <common.h>
#include <sprd_adc.h>
#include "otp_helper.h"

#define LB_GPIO    86
#define ADC_CHANNEL_FOR_NV    3


#define HW_GPIO_ID0	33
#define HW_GPIO_ID1	88
#define HW_GPIO_ID2	9


#define DDR_GPIO_ID0    32 
#define DDR_GPIO_ID1    31
#define DDR_GPIO_ID2    160  
#define AUDIOPA_GPIO  161
typedef enum k_less {
	K32 = 0,
	K_LESS,
}k_less_t;

typedef enum crystal_type {
	VCTCXO = 0,
	DCXO,
	TSX,
	TCXO,
}crystal_type_t;

struct clock_table {
	k_less_t k32_less_data;
	crystal_type_t crystal_data;
};

struct hwver_table {
	int	id;
	char *name;
};
struct audiopa_table {
	int	id;
	char *name;
};
struct ddrid_table {
	int	id;
	char *name;
};

static const struct clock_table clock_table[] = {
	{K_LESS, TSX},
	{K32, TCXO},
};

static const int adc2deltanv_table[] = {
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* hw_ver01.nv */
	0 /* hw_ver00.nv */
};

static const struct hwver_table hwver_array[] = {
	{0x2, "F271i_2"},
	{0x5, "F271i_5"},
	{0x6, "F271i_6"},
	{0x7, "F271i_7"},
};
static const struct ddrid_table ddrid_array[] = {
	{0x3, "BWMD3X32L7B-04Gb/MR5:0xFD,MR8:0x1B"},
	{0x7, "GDT41A32BF0-T3E/MR5:0x3,MR8:0x1B"},
	{0x4, "KFO005ES3-ZIb1/MR5:0x3,MR8:0x1B"},
	{0x5, "GDB41A32PF0-P2A/MR5:0xFD,MR8:0x18"},
	{0x6, "GDT41A32PF0-Q3A/MR5:0xFD,MR8:0x1B"},
	{0x7, "GDT41A32BF0-T3E/MR5:0x3,MR8:0x1B"},
	{0x0, "04EMCP04-AL2BM627/MR5:0xFD,MR8:0x18"},
};

static const struct audiopa_table audiopa_array[] = {
	{0x0, "aw87318"},
	{0x1, "tfa9897"},
};
extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_direction_input(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_get(struct gpio_chip *chip, unsigned offset);

static int gpio_state(unsigned int GPIO_NUM)
{
	int value = 0 ;

	sprd_gpio_request(NULL, GPIO_NUM);
	sprd_gpio_direction_input(NULL, GPIO_NUM);
	value = sprd_gpio_get(NULL,GPIO_NUM);

	if(value != 0)
	{
	/* value may be -EINVAL in theory when gpio num is wrong! */
		return 1;
	}
	else
	{
		return 0;
	}
}

static int get_adc_value_board(int channel)
{
	int adc_value=0,vol = 0;

	adc_value = pmic_adc_get_value_by_isen(channel,0,15,2000);
	vol = sprd_chan_small_adc_to_vol(channel, 0 , 0 ,adc_value);
	debugf("result = %d\n",vol);

	if (vol <= 0 || vol >= 1200) {
		errorf("vol is out of ranger [0~1200]\n");
		return -1;
	}

	if (vol >= 9 && vol <= 31)
		vol = 0;
	if (vol >= 180 && vol <= 220)
		vol = 1;
	if (vol >= 275 && vol <= 325)
		vol = 2;
	if (vol >= 465 && vol <= 495)
		vol = 3;
	if (vol >= 584 && vol <= 616)
		vol = 4;
	if (vol >= 762 && vol <= 798)
		vol = 5;
	if (vol >= 920 && vol <= 960)
		vol = 6;
	if (vol >= 1054 && vol <= 1186)
		vol = 7;

	if(vol < 0 || vol > 7) {
		errorf("Adc value of rf band if is wrong, the rfboard.id will be set to -1\n");
		return -1;
	}

	return adc2deltanv_table[vol];
}

static int get_clockid(void)
{
	unsigned int gpio_val = 0;

	gpio_val = gpio_state(LB_GPIO);

	return gpio_val;
}

/* Return rf band info */
int sprd_get_bandinfo(void)
{
	unsigned int adc_val = 0;

	adc_val = get_adc_value_board(ADC_CHANNEL_FOR_NV);
	debugf("rfboard.id = %d\n", adc_val);

	return adc_val;
}

/* Return crystal type */
int sprd_get_crystal(void)
{
	int id = get_clockid();

	return clock_table[id].crystal_data;
}

/* Return 32k less or not */
int sprd_get_32k(void)
{
/* sw auto-adaption */
#ifdef CONFIG_BOARD_ID
	int id = get_clockid();

	return clock_table[id].k32_less_data;
#else
/* dedicate definition */
#ifdef CONFIG_32K_TYPE
        return CONFIG_32K_TYPE;
#else
/* default setting */
        return K_LESS;
#endif
#endif
}

/* Return board id */
int sprd_get_boardid(void)
{
	return get_clockid();
}


char *sprd_get_hwver(void)
{
	unsigned int gpio_val = 0;
	unsigned int shift_bit = 0;
	int i;
	unsigned int len = sizeof(hwver_array) / sizeof(struct hwver_table);

	gpio_val |= (gpio_state(HW_GPIO_ID0) << shift_bit);
	shift_bit++;

	gpio_val |= (gpio_state(HW_GPIO_ID1) << shift_bit);
	shift_bit++;

	gpio_val |= (gpio_state(HW_GPIO_ID2) << shift_bit);
	shift_bit++;
	debugf("gpio_val:%d\n", gpio_val);

	for (i = 0; i < len; i++) {
		if (gpio_val == hwver_array[i].id)
			return hwver_array[i].name;
	}

	if (i == len)
		return NULL;
}
char *sprd_get_ddrid(void)
{
	unsigned int gpio_val = 0;
	unsigned int shift_bit = 0;
	int i;
	unsigned int len = sizeof(ddrid_array) / sizeof(struct ddrid_table);

	gpio_val |= (gpio_state(DDR_GPIO_ID0) << shift_bit);
	shift_bit++;

	gpio_val |= (gpio_state(DDR_GPIO_ID1) << shift_bit);
	shift_bit++;

	gpio_val |= (gpio_state(DDR_GPIO_ID2) << shift_bit);
	shift_bit++;
	debugf("ddr_gpio_val:%d\n", gpio_val);
	for (i = 0; i < len; i++) {
		if (gpio_val == ddrid_array[i].id)
			return ddrid_array[i].name;
	}

	if (i == len)
		return NULL;
}
char *sprd_get_audiopa(void)
{
	unsigned int gpio_val = 0;
	unsigned int shift_bit = 0;
	int i;
	unsigned int len = sizeof(audiopa_array) / sizeof(struct audiopa_table);

	gpio_val |= (gpio_state(AUDIOPA_GPIO) << shift_bit);
	shift_bit++;

	debugf("audiopa_gpio_val:%d\n", gpio_val);
	for (i = 0; i < len; i++) {
		if (gpio_val == audiopa_array[i].id)
			return audiopa_array[i].name;
	}

	if (i == len)
		return NULL;
}
