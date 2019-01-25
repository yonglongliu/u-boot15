#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>
#include <sprd_led.h>

#define ANA_BTLC_CTRL   SCI_ADDR(ANA_BTLC_BASE, 0x0000)
#define ANA_BLTC_R_DUTY SCI_ADDR(ANA_BTLC_BASE, 0x0008)
#define ANA_BLTC_G_DUTY SCI_ADDR(ANA_BTLC_BASE, 0x0018)
#define ANA_BLTC_B_DUTY SCI_ADDR(ANA_BTLC_BASE, 0x0028)

#define BLTC_EN          BIT(9)
#define RTC_BLTC_EN      BIT(7)
#define RGB_PD_SW        BIT(0)
#define RGB_V            (0x1f0)
#define WHTLED_PD        BIT(0)
#define WHTLED_SERIES_EN BIT(8)
#define R_RUN            BIT(0)
#define R_TYPE           BIT(1)
#define G_RUN            BIT(4)
#define G_TYPE           BIT(5)
#define B_RUN            BIT(8)
#define B_TYPE           BIT(9)

static uint32_t init = 0;

// TODO: difference between sc2723 and sc2731
void sprd_led_init(void)
{
#ifdef CONFIG_ADIE_SC2731
	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BLTC_EN);
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN0, RTC_BLTC_EN);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_PD_SW);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_V);
	ANA_REG_OR(ANA_REG_GLB_WHTLED_CTRL, WHTLED_PD);
	ANA_REG_OR(ANA_REG_GLB_WHTLED_CTRL, WHTLED_SERIES_EN);

	printf("[LED] init led\n");

	init = 1;
#endif
}

void sprd_led_disable(LedType type)
{
#ifdef CONFIG_ADIE_SC2731
	uint32_t bits;

	if (!init)
		return;

	switch (type) {
	case Red:
		bits = R_RUN;
		break;
	case Green:
		bits = G_RUN;
		break;
	case Blue:
		bits = B_RUN;
		break;
	default:
		break;
	}

	ANA_REG_BIC(ANA_BTLC_CTRL, bits);

	printf("[LED] disable led, type=%d\n", type);
#endif
}

void sprd_led_set_brightness(LedType type, uint32_t brightness)
{
#ifdef CONFIG_ADIE_SC2731
	uint32_t bits, reg;

	if (!init)
		return;

	if (brightness > BRIGHTNESS_MAX)
		brightness = BRIGHTNESS_MAX;

	switch (type) {
	case Red:
		bits = R_RUN | R_TYPE;
		reg = ANA_BLTC_R_DUTY;
		break;
	case Green:
		bits = G_RUN | G_TYPE;
		reg = ANA_BLTC_G_DUTY;
		break;
	case Blue:
		bits = B_RUN | B_TYPE;
		reg = ANA_BLTC_B_DUTY;
		break;
	default:
		break;
	}

	ANA_REG_OR(ANA_BTLC_CTRL, bits);
	ANA_REG_MSK_OR(reg, (brightness << 8) | 0xFF, 0xFFFF);

	printf("[LED] set brightness, type=%d, brightness=%u\n", type, brightness);
#endif
}
