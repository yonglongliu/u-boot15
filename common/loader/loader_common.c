#include "loader_common.h"
#include <mmc.h>
#include <fat.h>
#if defined(CONFIG_OF_LIBFDT)
#include <libfdt.h>
#include <fdt_support.h>
#endif
#include <sprd_common_rw.h>
#include <linux/usb/usb_uboot.h>

#ifdef CONFIG_MINI_TRUSTZONE
#include "trustzone_def.h"
#endif

#include "sprd_cpcmdline.h"

#if defined (CONFIG_SECBOOT)
#include "secureboot/sec_common.h"
#endif
unsigned char raw_header[8192];
unsigned int g_charger_mode = 0;
char serial_number_to_transfer[SP15_MAX_SN_LEN];

/*for verified boot*/
unsigned int g_fb_lockflag = 0;

extern int charger_connected(void);
extern void modem_entry(void);

unsigned short calc_checksum(unsigned char *dat, unsigned long len)
{
	unsigned short num = 0;
	unsigned long chkSum = 0;
	while (len > 1) {
		num = (unsigned short)(*dat);
		dat++;
		num |= (((unsigned short)(*dat)) << 8);
		dat++;
		chkSum += (unsigned long)num;
		len -= 2;
	}
	if (len) {
		chkSum += *dat;
	}
	chkSum = (chkSum >> 16) + (chkSum & 0xffff);
	chkSum += (chkSum >> 16);
	return (~chkSum);
}

unsigned char _chkNVEcc(uint8_t *buf, uint64_t size, uint32_t checksum)
{
	uint16_t crc;

	crc = calc_checksum(buf, (unsigned long)size);
	debugf("_chkNVEcc calcout 0x%x, org 0x%x\n", crc, (uint16_t)checksum);
	return (crc == (uint16_t) checksum);
}

/*modif to support the sp15 64 bit sn NO */
char *get_product_sn(void)
{
	SP09_PHASE_CHECK_T phase_check_sp09;
	SP15_PHASE_CHECK_T phase_check_sp15;
	uint32_t magic;

	memset(serial_number_to_transfer, 0x0, SP15_MAX_SN_LEN);

	strcpy(serial_number_to_transfer, "0123456789ABCDEF");
	if (0 != common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(magic), (uint64_t)0, (char *)&magic)) {
		errorf("read miscdata error.\n");
		return serial_number_to_transfer;
	}
	if(magic == SP09_SPPH_MAGIC_NUMBER){
		if(common_raw_read(PRODUCTINFO_FILE_PATITION,sizeof(phase_check_sp09), (uint64_t)0, (char *)&phase_check_sp09)){
			debugf("sp09 read miscdata error.\n");
			return serial_number_to_transfer;
		}
		if(strlen(phase_check_sp09.SN1)){
			memcpy(serial_number_to_transfer, phase_check_sp09.SN1, SP09_MAX_SN_LEN);
		}
	}else if(magic == SP15_SPPH_MAGIC_NUMBER){
		if(common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(phase_check_sp15), (uint64_t)0 ,(char *)&phase_check_sp15)){
			debugf("sp15 read miscdata error.\n");
			return serial_number_to_transfer;
		}
		if(strlen(phase_check_sp15.SN1)){
			memcpy(serial_number_to_transfer, phase_check_sp15.SN1, SP15_MAX_SN_LEN);
		}
	}
	return serial_number_to_transfer;
}

#if defined (CONFIG_SECBOOT)
/*
* flag:1 means jump secure check or verify.
* flag:0 means normal check
* default: 0
*/
unsigned int get_fblockflag(void)
{
	unsigned char tmp_buffer[PDT_INFO_LOCK_FLAG_SECTION_SIZE];
	unsigned char * tmp_p = tmp_buffer;
	int ret;

	memset(tmp_buffer, 0, sizeof(tmp_buffer));
	if (common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(tmp_buffer), PDT_INFO_LOCK_FLAG_OFFSET, (char *)tmp_buffer)) {
		debugf("read miscdata error.\n");
	}

	ret = sprd_sec_verify_unlockstatus(tmp_p, PDT_INFO_LOCK_FLAG_MAX_SIZE);
	debugf("sprd_sec_verify_unlockstatus ret %d.\n", ret);

	if(ret != 0) {
		g_fb_lockflag = VBOOT_STATUS_LOCK; /*default lock status.*/
	}
	else {
		g_fb_lockflag = VBOOT_STATUS_UNLOCK; /*unlock status.*/
	}

	return g_fb_lockflag;
}

int set_fblockflag(unsigned int flag)
{
	unsigned char tmp_buffer_flag[PDT_INFO_LOCK_FLAG_MAX_SIZE] __attribute__((aligned(4096)));
	unsigned char tmp_buffer[PDT_INFO_LOCK_FLAG_SECTION_SIZE];
	//unsigned int fb_lockflag_old = VBOOT_STATUS_LOCK;
	//unsigned int fb_lockflag_new = VBOOT_STATUS_LOCK;

	memset(tmp_buffer_flag, 0, sizeof(tmp_buffer_flag));
	memset(tmp_buffer, 0, sizeof(tmp_buffer));

	if (flag == VBOOT_STATUS_UNLOCK) {
		strcat(tmp_buffer_flag, "VerifiedBoot-UNLOCK");
	}
	else if(flag == VBOOT_STATUS_LOCK) {
		strcat(tmp_buffer_flag, "VerifiedBoot-LOCK");
	}
	else {
		debugf("lockflag is invalid.\n");
		return -2;
	}

	//fb_lockflag_old = get_fblockflag();
	if (common_raw_read(PRODUCTINFO_FILE_PATITION, PDT_INFO_LOCK_FLAG_SECTION_SIZE, PDT_INFO_LOCK_FLAG_OFFSET, (char *)tmp_buffer)) {
		debugf("read miscdata error.\n");
		return -1;
	}

#ifdef DEBUG_LOCK_CTRL
	dumpHex("data before encrypt.", tmp_buffer_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);
#endif

#if defined CONFIG_VBOOT_V2
	uboot_encrypt_data(tmp_buffer_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);
#endif

#ifdef DEBUG_LOCK_CTRL
	dumpHex("data after encrypt.", tmp_buffer_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);
#endif

	/*data ready*/
	memcpy((char *)tmp_buffer , tmp_buffer_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);

	/*write to emmc*/
	if (common_raw_write(PRODUCTINFO_FILE_PATITION, sizeof(tmp_buffer), sizeof(tmp_buffer), PDT_INFO_LOCK_FLAG_OFFSET, (char *)tmp_buffer)) {
		debugf("write miscdata error.\n");
		return -1;
	}

	//fb_lockflag_new = get_fblockflag();
	//debugf("old value:%d, new value:%d\n", fb_lockflag_old, fb_lockflag_new);
	return 0;
}
#endif

void fdt_fixup_all(u8 *fdt_blob)
{
	uint32_t fdt_size;
	boot_img_hdr *hdr = raw_header;
	int err;
	char  *boot_mode_type_str;

	if (fdt_check_header(fdt_blob) != 0) {
		errorf("image is not a fdt\n");
	}

#ifdef CONFIG_SPLASH_SCREEN
	fdt_fixup_lcdid(fdt_blob);
	fdt_fixup_lcdmoduleid(fdt_blob);
	fdt_fixup_lcdbase(fdt_blob);
	fdt_fixup_lcdsize(fdt_blob);
#endif

#ifndef CONFIG_ZEBU
	fdt_fixup_adc_calibration_data(fdt_blob);
#endif
	//fdt_fixup_dram_training(fdt_blob);
	fdt_fixup_ddr_size(fdt_blob);
	fdt_fixup_sysdump_uboot(fdt_blob);
	fdt_fixup_sysdump_magic(fdt_blob);
#ifdef CONFIG_SECURE_BOOT
	fdt_fixup_secureboot_param(fdt_blob);
#endif
#ifdef CONFIG_NAND_BOOT
	fdt_fixup_mtd(fdt_blob);
#endif

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
extern int fdt_fixup_cp_coupling_info(void *blob);
	fdt_fixup_cp_coupling_info(fdt_blob);
#endif
	/*max let cp_cmdline_fixup befor fdt_fixup_cp_boot*/
	cp_cmdline_fixup();
	fdt_fixup_cp_boot(fdt_blob);

	boot_mode_type_str = getenv("bootmode");
	if (NULL != boot_mode_type_str)
	{
		if(!strncmp(boot_mode_type_str, "sprdisk", 7)) {
			fdt_fixup_memleakon(fdt_blob);
		}
	}

	/*for verified boot*/
	fdt_fixup_verified_boot(fdt_blob);
	fdt_fixup_flash_lock_state(fdt_blob);

#ifdef CONFIG_VBOOT_V2
	/*for Android O VBooot*/
	fdt_fixup_ando_vboot(fdt_blob);
#endif

	fdt_fixup_serialno(fdt_blob);
	fdt_fixup_chosen_bootargs_board_private(fdt_blob);

#ifdef CONFIG_SANSA_SECBOOT
	//fdt_fixup_socid(fdt_blob);
#endif

	/* for non iq mode, remove reserved iq memory from dtb */
	fdt_fixup_iq_reserved_mem(fdt_blob);

#ifdef CONFIG_BOARD_KERNEL_CMDLINE
	/* board kernel cmdline in header of boot.img */
	fdt_fixup_board_kernel_cmdline(fdt_blob);
#endif

	/* if enabled, set loglevel = 7*/
	fdt_fixup_loglevel(fdt_blob);
	return;
}

void fdt_fixup_all_x86(u8 *fdt_blob)
{
	uint32_t fdt_size;
	boot_img_hdr *hdr = raw_header;
	int err;
	char  *boot_mode_type_str;

	if (fdt_check_header(fdt_blob) != 0) {
		errorf("image is not a fdt\n");
	}

#ifdef CONFIG_SPLASH_SCREEN
	fdt_fixup_lcdid(fdt_blob);
	fdt_fixup_lcdmoduleid(fdt_blob);
	fdt_fixup_lcdbase(fdt_blob);
	fdt_fixup_lcdsize(fdt_blob);
#endif

	fdt_fixup_adc_calibration_data(fdt_blob);

	fdt_fixup_serialno(fdt_blob);

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
extern int fdt_fixup_cp_coupling_info(void *blob);
	fdt_fixup_cp_coupling_info(fdt_blob);
#endif

	/*max let cp_cmdline_fixup befor fdt_fixup_cp_boot*/
	cp_cmdline_fixup();

	fdt_fixup_cp_boot(fdt_blob);

	/*for verified boot*/
	fdt_fixup_verified_boot(fdt_blob);
	fdt_fixup_flash_lock_state(fdt_blob);

#ifdef CONFIG_VBOOT_V2
		/*for Android O VBooot*/
		fdt_fixup_ando_vboot(fdt_blob);
#endif

	/* for non iq mode, remove reserved iq memory from dtb */
	fdt_fixup_iq_reserved_mem(fdt_blob);

	fdt_fixup_pmic_wa(fdt_blob);

#ifdef CONFIG_BOARD_KERNEL_CMDLINE
	/* board kernel cmdline in header of boot.img */
	fdt_fixup_board_kernel_cmdline(fdt_blob);
#endif

	/* if enabled, set loglevel = 7*/
	fdt_fixup_loglevel(fdt_blob);
}

#ifdef CONFIG_X86
static int start_linux_x86()
{
	struct boot_params *base_ptr;
	struct boot_img_hdr *boot_hdr = (void *)raw_header;
	uint64_t load_address;
	char *bzImage_addr = KERNEL_ADR;
	ulong bzImage_size = 0;
	ulong initrd_addr = RAMDISK_ADR;
	ulong initrd_size = PAD_SIZE(boot_hdr->ramdisk_size, KERNL_PAGE_SIZE);
	int image_64bit = 0;

	debugf("initrd_size: 0x%lx\n", initrd_size);
	disable_interrupts();
	wbinvd();

#ifndef CONFIG_ZEBU
	/*start modem CP */
	modem_entry();
#endif

	/* Setup board for maximum PC/AT Compatibility */
	setup_pcat_compatibility();
	/* Lets look for */
	base_ptr = load_zimage(bzImage_addr, bzImage_size, &load_address);

	if (!base_ptr) {
		puts("## Kernel loading failed ...\n");
		return -1;
	}
	if (setup_zimage(base_ptr, (char *)base_ptr + COMMAND_LINE_OFFSET,
			0, initrd_addr, initrd_size)) {
		puts("Setting up boot parameters failed ...\n");
		return -1;
	}
	image_64bit = image_check64(base_ptr);
	/* we assume that the kernel is in place */
	return boot_linux_kernel((ulong)base_ptr, load_address, image_64bit);
}
#endif

#ifdef CONFIG_ARM
static int start_linux(uchar *dt_addr)
{
#ifdef CONFIG_OF_LIBFDT
	void (*theKernel) (int zero, int arch, u32 params);
	theKernel = (void (*)(void *, int, int, int))KERNEL_ADR;

	/*disable all caches */
	cleanup_before_linux();

	/*start modem CP */
#ifndef CONFIG_ZEBU
	modem_entry();
#endif

#ifdef CONFIG_MINI_TRUSTZONE
	trustzone_entry(TRUSTZONE_ADR + 0x200);
#endif
	/* jump to kernel with register set */
	theKernel(0, machine_arch_type, (u32)dt_addr);
#else
	void (*theKernel) (int zero, int arch, u32 params);
	u32 machine_type = 0;

	machine_type = machine_arch_type;	/* get machine type */
	theKernel = (void (*)(int, int, u32))KERNEL_ADR;	/* set the kernel address */

	/*start modem CP */
	cp_cmdline_fixup();

	/*disable all caches */
	cleanup_before_linux();

	/*start modem CP */
	modem_entry();

	/* jump to kernel with register set */
	theKernel(0, machine_type, VLX_TAG_ADDR);
#endif /*CONFIG_OF_LIBFDT */
	while (1) ;
	return 0;
}
#endif
static int start_linux_armv8(uchar *dt_addr)
{
	void (*theKernel) (void *dtb_addr, int zero, int arch, int reserved);
	theKernel = (void (*)(void *, int, int, int))KERNEL_ADR;

	/*before switch to el2,flush all cache */
	/*FIXME: cleanup_before_linux() will cause panic here, we need to find the solution*/
	flush_dcache_range(CONFIG_SYS_SDRAM_BASE, CONFIG_SYS_SDRAM_END);
#ifdef CONFIG_DUAL_DDR
	flush_dcache_range(CONFIG_SYS_SDRAM_BASE2, CONFIG_SYS_SDRAM_END2);
#endif

	/*sharkle and sharklj1 need disable mmu and cache before jump into kernel*/
	cleanup_before_linux();

	/*start modem CP */
	modem_entry();

#ifdef CONFIG_MINI_TRUSTZONE
	trustzone_entry(TRUSTZONE_ADR + 0x200);
#endif

	/*kernel must run in el2, so here switch to el2 */
	armv8_switch_to_el2();
	theKernel(dt_addr, 0, 0, 0);

	/*never enter here*/
	while (1) ;
	return 0;
}


void vlx_entry(uchar *dt_addr)
{
	/* the last time to write log */
	write_log_last();

#ifdef DFS_ON_ARM7
	cp_dfs_param_for_arm7();
#endif
	/*shutdown usb ldo, can't shutdown it in the ldo_sleep.c because download mode must use usb */
	usb_driver_exit();

#ifdef CONFIG_ARM64
	smp_kick_all_cpus();
	start_linux_armv8(dt_addr);
#endif
#ifdef CONFIG_ARM
	start_linux(dt_addr);
#endif
#ifdef CONFIG_X86
	start_linux_x86();
#endif
}
