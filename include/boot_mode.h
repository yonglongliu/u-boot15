#ifndef _BOOT_MODE_H_
#define _BOOT_MODE_H_
#include <common.h>

#define BACKLIGHT_ON 25
#define BACKLIGHT_OFF 0
#define LCD_ON 1
#define LCD_OFF 0

typedef enum {
	CMD_UNDEFINED_MODE=0,
	CMD_POWER_DOWN_DEVICE,
	CMD_NORMAL_MODE,
	CMD_RECOVERY_MODE,
	CMD_FASTBOOT_MODE,
	CMD_ALARM_MODE,
	CMD_CHARGE_MODE,
	CMD_ENGTEST_MODE,
	CMD_WATCHDOG_REBOOT,
	CMD_AP_WATCHDOG_REBOOT,
	CMD_SPECIAL_MODE,
	CMD_UNKNOW_REBOOT_MODE,
	CMD_PANIC_REBOOT,
	CMD_VMM_PANIC_MODE,   //0xd
	CMD_TOS_PANIC_MODE,
	CMD_EXT_RSTN_REBOOT_MODE,
	CMD_CALIBRATION_MODE,
	CMD_FACTORYTEST_MODE,
	CMD_AUTODLOADER_REBOOT,
	CMD_AUTOTEST_MODE,
	CMD_IQ_REBOOT_MODE,
	CMD_SLEEP_MODE,
	CMD_SPRDISK_MODE,

	/*this is not a mode name ,beyond CMD_MAX_MODE means overflow*/
	CMD_MAX_MODE
}boot_mode_enum_type;


#define CHECK_BOOTMODE_FUN_NUM 15
typedef boot_mode_enum_type (*CBOOT_FUNC) (void);
typedef void (*CBOOT_MODE_ENTRY) (void);

#define MODE_REGIST( index, fun) \
    do{\
            array[index]  = fun;\
        }while(0)


int get_mode_from_file(void);
int pctool_mode_detect(void);
int is_bat_low(void);
int alarm_flag_check(void);
int cali_file_check(void);
int read_adc_calibration_data(char *buffer,int size);
int pctool_mode_detect_uart(void);
int sprdisk_mode_detect(void);

#ifdef CONFIG_AUTOLOAD_MODE
void autoload_mode(void);
#endif

void normal_mode(void);
void recovery_mode(void);
void charge_mode(void);
void fastboot_mode(void);
void alarm_mode(void);
void engtest_mode(void);
void calibration_mode(void);
void factorytest_mode(void);
void watchdog_mode(void);
void ap_watchdog_mode(void);
void unknow_reboot_mode(void);
void special_mode(void);
void panic_reboot_mode(void);
void autodloader_mode(void);
void iq_mode(void);
void autotest_mode(void);
void sprdisk_mode(void);

boot_mode_enum_type get_mode_from_arg(char* mode_name);
boot_mode_enum_type get_mode_from_pctool(void);
boot_mode_enum_type get_mode_from_bat_low(void);
boot_mode_enum_type write_sysdump_before_boot_extend(void);
boot_mode_enum_type get_mode_from_file_extend(void);
boot_mode_enum_type get_mode_from_watchdog(void);
boot_mode_enum_type get_mode_from_alarm_register(void);
boot_mode_enum_type get_mode_from_charger(void);
boot_mode_enum_type get_mode_from_keypad(void);
boot_mode_enum_type get_mode_from_gpio_extend(void);

void vlx_nand_boot(char * kernel_pname, int backlight_set, int lcd_enable);
#endif
