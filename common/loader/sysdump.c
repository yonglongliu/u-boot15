/*
 * Copyright (C) 2013 Spreadtrum Communications Inc.
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

#include <rtc.h>
#include <boot_mode.h>
#include <common.h>
#include <linux/input.h>
#include "sysdump.h"
#include <linux/mtd/mtd.h>
#include <linux/sizes.h>
#include <asm/arch/check_reboot.h>
#include <mmc.h>
#include <fat.h>
#include <exfat.h>
#include "loader_common.h"

#include <libfdt.h>
#include <fdt.h>
#include <linux/ctype.h>
#include <fdtdec.h>
#include <u-boot/sha1.h>

#ifdef CONFIG_X86
#include <asm/e820.h>
#include <chipram_env.h>
#include "crashlog.h"
#endif

#ifdef CONFIG_X86
#define LLX			"0x%08llx"
#define SYSDUMP_LONG		unsigned long long
#define U32_T_U64(val1,val2)	(u64)((((u64)(val1))<<32)|((u64)(val2)))
#else
#define LLX			"0x%08lx"
#define SYSDUMP_LONG		unsigned long
#endif

#if (defined CONFIG_ARM64) || (defined CONFIG_X86)
typedef uint64_t mem_addr_t;
typedef uint64_t mem_size_t;
#else
typedef uint32_t mem_addr_t;
typedef uint32_t mem_size_t;
#endif

enum {
	FS_FAT32,
	FS_EXFAT,
	FS_INVALID
};

struct sysdump_memory {
	SYSDUMP_LONG addr;
	SYSDUMP_LONG size;
};

int mem_num = 0, re_num = 0, dump_rst_mode;
static struct sysdump_memory linux_memory[5];
static struct sysdump_memory reserved_memory[25];

extern unsigned reboot_reg;
extern unsigned sysdump_flag;
extern int sprd_host_init(int sdio_type);
extern struct rtc_time get_time_by_sec(void);
extern int load_fixup_dt_img(uchar *partition, uchar **dt_start_addr);
extern uint64_t _get_kernel_ramdisk_dt_offset( boot_img_hdr * hdr, uchar *partition);
extern unsigned char board_key_scan(void);
extern int fdt_get_addr_size(const void *fdt, int node, const char *propname,
		   uint64_t *addrp, mem_size_t *sizep);

#ifdef CONFIG_X86
extern ddr_info_t* get_ddr_range(void);
#endif

#ifdef CONFIG_ARM7_RAM_ACTIVE
extern void pmic_arm7_RAM_active(void);
#endif

#ifdef CONFIG_ETB_DUMP
extern unsigned char etb_dump_mem[SZ_32K];
extern u32 etb_buf_size;
extern void sprd_etb_hw_dis(void);
extern void sprd_etb_dump (void);
#endif

#ifdef CONFIG_SPLASH_SCREEN
	extern void set_backlight(uint32_t value);
	extern void lcd_printf(const char *fmt, ...);
	extern void lcd_enable(void);
	#define sysdump_lcd_printf(fmt, args...)   lcd_printf(fmt, ##args)
#else
	#define sysdump_lcd_printf(fmt, args...)
	#define lcd_enable(void)
#endif

void display_writing_sysdump(void)
{
	debugf("%s\n", __FUNCTION__);
#ifdef CONFIG_SPLASH_SCREEN
	vibrator_hw_init();
	set_vibrator(1);
	sysdump_lcd_printf("   -------------------------------  \n"
		   "   Sysdumpping now, keep power on.  \n"
		   "   -------------------------------  \n");
	set_backlight(255);
	set_vibrator(0);
#endif
}
void display_special_mode(void)
{
	debugf("%s\n", __FUNCTION__);
#ifdef CONFIG_SPLASH_SCREEN
	vibrator_hw_init();
	set_vibrator(1);
	sysdump_lcd_printf("   -------------------------------  \n"
		   "   Restart now, keep power on.  \n"
		   "   -------------------------------  \n");
	set_backlight(255);
	set_vibrator(0);
#endif
}
/*display without character*/
void display_sysdump()
{
	debugf("%s\n", __FUNCTION__);
#ifdef CONFIG_SPLASH_SCREEN
	vibrator_hw_init();
	set_vibrator(1);
	set_backlight(255);
	set_vibrator(0);
#endif
}

static void wait_for_keypress()
{
	int key_code;

	do {
		udelay(50 * 1000);
		key_code = board_key_scan();
		if (key_code == KEY_VOLUMEDOWN || key_code == KEY_VOLUMEUP || key_code == KEY_HOME)
			break;
	} while (1);
	debugf("Pressed key: %d\n", key_code);
	sysdump_lcd_printf("Pressed key: %d\n", key_code);
}

int init_mmc_fat(int *fs_type)
{
	struct mmc *mmc;
	block_dev_desc_t *dev_desc = NULL;
	int ret;

	*fs_type = FS_INVALID;
	debugf("init_mmc_fat\n");
	mmc = board_sd_init();
	dev_desc = &mmc->block_dev;
	if(dev_desc==NULL){
		debugf("no mmc block device found\n");
		return -1;
	}

	if (dev_desc ->part_type != PART_TYPE_DOS){
		debugf(" no part_type_dos!\n");
		return -1;
	}
	ret = fat_register_device(dev_desc, 1);
	if (ret == 0) {
		ret = file_fat_detectfs();
		if(ret) {
			debugf("detect fs fat failed\n");
			return -1;
		}
		*fs_type = FS_FAT32;
		return 0;
	}
	debugf("Fat register fail. Try exFat. \n");

	ret = exfat_register_device(dev_desc, 1);
	if(ret < 0) {
		debugf("exFat register fail %d.\n", ret);
		return -1;
	}

	ret = file_exfat_detectfs();
	if(ret) {
		debugf("Detect fs exfat failed\n");
		return -1;
	}
	*fs_type = FS_EXFAT;
	return 0;
}

void write_mem_to_mmc(char *path, char *filename, int fs_type,
	void *memaddr, unsigned long memsize)
{
	int ret = 0;
	unsigned long actwrite = 0;

	if (path) {
		do {} while (0); /* TODO: jianjun.he */
	}

	debugf("writing 0x%lx bytes to sd file %s\n",
		memsize, filename);

	sysdump_lcd_printf("writing 0x%lx bytes to sd file %s\n",
		memsize, filename);

	if (fs_type==FS_FAT32)
		ret = file_fat_write(filename, memaddr, 0, memsize, &actwrite);
	else if (fs_type==FS_EXFAT)
		ret = file_exfat_write(filename, memaddr, memsize);
	else
		ret = -1;

	if (ret != 0) {
		debugf("write file %s to SD Card error, and ret = %d !!!\n", filename, ret);
	}

	return;
}

static size_t get_elfhdr_size(int nphdr)
{
	size_t elfhdr_len;

	elfhdr_len = sizeof(struct elfhdr) +
		(nphdr + 1) * sizeof(struct elf_phdr);
#if SETUP_NOTE
	elfhdr_len += ((sizeof(struct elf_note)) +
		roundup(sizeof(CORE_STR), 4)) * 3 +
		roundup(sizeof(struct elf_prstatus), 4) +
		roundup(sizeof(struct elf_prpsinfo), 4) +
		roundup(sizeof(struct task_struct), 4);
#endif
	elfhdr_len = PAGE_ALIGN(elfhdr_len); //why?

	return elfhdr_len;
}

#if SETUP_NOTE
static int notesize(struct memelfnote *en)
{
	int sz;

	sz = sizeof(struct elf_note);
	sz += roundup((strlen(en->name) + 1), 4);
	sz += roundup(en->datasz, 4);

	return sz;
}

static char *storenote(struct memelfnote *men, char *bufp)
{
	struct elf_note en;

#define DUMP_WRITE(addr,nr) do { memcpy(bufp,addr,nr); bufp += nr; } while(0)

	en.n_namesz = strlen(men->name) + 1;
	en.n_descsz = men->datasz;
	en.n_type = men->type;

	DUMP_WRITE(&en, sizeof(en));
	DUMP_WRITE(men->name, en.n_namesz);

	/* XXX - cast from long long to long to avoid need for libgcc.a */
	bufp = (char*) roundup((unsigned long)bufp,4);
	DUMP_WRITE(men->data, men->datasz);
	bufp = (char*) roundup((unsigned long)bufp,4);

#undef DUMP_WRITE

	return bufp;
}

#endif

static void sysdump_fill_core_hdr(struct pt_regs *regs,
						struct sysdump_mem *sysmem, int mem_num,
						char *bufp, int nphdr, int dataoff)
{
	struct elf_phdr *nhdr, *phdr;
	struct elfhdr *elf;
	struct memelfnote notes[3];
	off_t offset = 0;
	Elf_Off f_offset = dataoff;
	int i;

	/* setup ELF header */
	elf = (struct elfhdr *) bufp;
	bufp += sizeof(struct elfhdr);
	offset += sizeof(struct elfhdr);
	memcpy(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS]	= ELF_CLASS;
	elf->e_ident[EI_DATA]	= ELF_DATA;
	elf->e_ident[EI_VERSION]= EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;
	memset(elf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);
	elf->e_type	= ET_CORE;
	elf->e_machine	= ELF_ARCH;
	elf->e_version	= EV_CURRENT;
	elf->e_entry	= 0;
	elf->e_phoff	= sizeof(struct elfhdr);
	elf->e_shoff	= 0;
	elf->e_flags	= ELF_CORE_EFLAGS;
	elf->e_ehsize	= sizeof(struct elfhdr);
	elf->e_phentsize= sizeof(struct elf_phdr);
	elf->e_phnum	= nphdr;
	elf->e_shentsize= 0;
	elf->e_shnum	= 0;
	elf->e_shstrndx	= 0;

	/* setup ELF PT_NOTE program header */
	nhdr = (struct elf_phdr *) bufp;
	bufp += sizeof(struct elf_phdr);
	offset += sizeof(struct elf_phdr);
	nhdr->p_type	= PT_NOTE;
	nhdr->p_offset	= 0;
	nhdr->p_vaddr	= 0;
	nhdr->p_paddr	= 0;
	nhdr->p_filesz	= 0;
	if ((dump_rst_mode == CMD_WATCHDOG_REBOOT) || (dump_rst_mode == CMD_AP_WATCHDOG_REBOOT) || \
		(dump_rst_mode == CMD_UNKNOW_REBOOT_MODE) || (dump_rst_mode == CMD_EXT_RSTN_REBOOT_MODE) || \
		(dump_rst_mode == CMD_SPECIAL_MODE) || (dump_rst_mode == CMD_VMM_PANIC_MODE) || (dump_rst_mode == CMD_TOS_PANIC_MODE))
		nhdr->p_memsz = 0;
	nhdr->p_flags	= 0;
	nhdr->p_align	= 0;

	/* setup ELF PT_LOAD program header for every area */
	for (i = 0; i < mem_num; i++) {
		phdr = (struct elf_phdr *) bufp;
		bufp += sizeof(struct elf_phdr);
		offset += sizeof(struct elf_phdr);

		phdr->p_type	= PT_LOAD;
		phdr->p_flags	= PF_R|PF_W|PF_X;
		phdr->p_offset	= f_offset;
		phdr->p_vaddr	= sysmem[i].vaddr;
		phdr->p_paddr	= sysmem[i].paddr;
		phdr->p_filesz	= phdr->p_memsz	= sysmem[i].size;
		phdr->p_align	= 0;//PAGE_SIZE;
		f_offset += sysmem[i].size;
	}
#if SETUP_NOTE
	/*
	 * Set up the notes in similar form to SVR4 core dumps made
	 * with info from their /proc.
	 */
	nhdr->p_offset	= offset;

	/* set up the process status */
	notes[0].name = CORE_STR;
	notes[0].type = NT_PRSTATUS;
	notes[0].datasz = sizeof(struct elf_prstatus);
	notes[0].data = &prstatus;

	memset(&prstatus, 0, sizeof(struct elf_prstatus));

	nhdr->p_filesz	= notesize(&notes[0]);
	bufp = storenote(&notes[0], bufp);

	/* set up the process info */
	notes[1].name	= CORE_STR;
	notes[1].type	= NT_PRPSINFO;
	notes[1].datasz	= sizeof(struct elf_prpsinfo);
	notes[1].data	= &prpsinfo;

	memset(&prpsinfo, 0, sizeof(struct elf_prpsinfo));

	strcpy(prpsinfo.pr_fname, "vmlinux");

	nhdr->p_filesz	+= notesize(&notes[1]);
	bufp = storenote(&notes[1], bufp);

	/* set up the task structure */
	notes[2].name	= CORE_STR;
	notes[2].type	= NT_TASKSTRUCT;
	notes[2].datasz	= sizeof(struct task_struct);
	notes[2].data	= current;

	printf("%s: data size is %d, data addr is %p",__func__,notes[2].datasz,notes[2].data);

	nhdr->p_filesz	+= notesize(&notes[2]);
	bufp = storenote(&notes[2], bufp);
#endif
	if (nhdr->p_memsz == 0)
		nhdr->p_offset  = 0;
	else
		nhdr->p_offset  = offset;

	return;
}

char *rstmode[] = {
	"undefind mode",			//CMD_UNDEFINED_MODE=0,
	"power down",				//CMD_POWER_DOWN_DEVICE,
	"normal",				//CMD_NORMAL_MODE,
	"recovery",				//CMD_RECOVERY_MODE,
	"fastboot",				//CMD_FASTBOOT_MODE,
	"alarm",				//CMD_ALARM_MODE,
	"charge",				//CMD_CHARGE_MODE,
	"engtest",				//CMD_ENGTEST_MODE,
	"watchdog timeout",			//CMD_WATCHDOG_REBOOT ,
	"ap watchdog timeout",			//CMD_AP_WATCHDOG_REBOOT ,
	"framework crash",			//CMD_SPECIAL_MODE,
	"manual dump",				//CMD_UNKNOW_REBOOT_MODE,
	"kernel crash",				//CMD_PANIC_REBOOT,
	"vmm panic",				//CMD_VMM_PANIC_MODE
	"tos panic",				//CMD_TOS_PANIC_MODE
	"ext rstn reboot",                      //CMD_EXT_RSTN_REBOOT_MODE,
	"calibration",				//CMD_CALIBRATION_MODE,
	"factory test",				//CMD_FACTORYTEST_MODE,
	"autodloader",				//CMD_AUTODLOADER_REBOOT,
	"autotest",				//CMD_AUTOTEST_MODE,
	"iq reboot",				//CMD_IQ_REBOOT_MODE,
	"sleep",				//CMD_SLEEP_MODE,
	"sprd disk",				//CMD_SPRDISK_MODE,
};

#define GET_RST_MODE(x) rstmode[(x) < 23 ? (x) : 0]

#ifdef CONFIG_NAND_BOOT
/*Copy the data saved in nand flash to ram*/
int read_nand_to_ram( struct mtd_info *mtd, loff_t paddr, unsigned int size, unsigned char *buf)
{
        int ret = 0;
        unsigned int retlen = 0;
        loff_t read_addr = 0;
        unsigned char *read_buf = NULL;
        unsigned int readsize = 0;

        debugf("%s, read 0x%.8x:0x%.8x buf: 0x%.8x\n", __func__, (unsigned int)paddr, size, buf);
        for(read_addr = paddr, read_buf = buf; read_addr < (paddr + size); read_addr += readsize, read_buf += readsize) {
                readsize = (paddr + size - read_addr) > mtd->erasesize ? mtd->erasesize : (paddr + size - read_addr);
                if(mtd->_block_isbad(mtd, read_addr) == 1) {//if met bad block, we just fill it with 0x5a
                        memset(read_buf, 0x5a, readsize);
                        continue;
                }

                ret = mtd->_read(mtd, read_addr, readsize, &retlen, read_buf);
                if(ret != 0 && retlen != readsize) {
                        printf("%s, read addr: 0x%.8x len: 0x%.8x 's value error, ret: %d, retlen: 0x%.8x\n",\
			 __func__, (unsigned int)read_addr, readsize, ret, retlen);
			sysdump_lcd_printf("\nRead nand flash 0x%.8x error, you can dump it use download tools again!\n", read_addr);
			break;
                }
        }
	return ret;
}

/*dump the data saved in nand flash to sdcard when needed*/
void mtd_dump(int fs_type)
{
	int ret = 0;
	unsigned int write_len = 0, write_addr = 0;
	char *buf = NULL;
	unsigned int part_len = 0x8000000;//The size of each ubipac-part file
	int loop = 0;
	char fname[72];
	struct mtd_info *mtd = NULL;

	buf = CONFIG_SYS_SDRAM_BASE;//After dump memory to sdcard, we suppose the whole memory except u-boot used are avaliable.
	mtd = get_mtd_device_nm(UBIPAC_PART);
	if(mtd == NULL) {
		printf("Can't get the mtd part: %s\n", UBIPAC_PART);
		return;
	}

	debugf("Begin to dump 0x%.8x ubipac to sdcard!\n", mtd->size);
	for(write_addr = 0; write_addr < mtd->size; write_addr += write_len, loop++)
	{
		write_len = (mtd->size - write_addr) > part_len ? part_len : (mtd->size - write_addr);
		debugf("begin to read 0x%.8x value to ubipac%d\n", write_len, loop);
		memset(buf, 0, write_len);
		ret = read_nand_to_ram(mtd, (loff_t)(write_addr), write_len, buf);
		if(ret != 0) {
			printf("%s, read ubipac%d error, the ret is %d\n", __func__, loop, ret);
			break;
		}
		debugf("read ubipac%d end\n", loop);

		memset(fname, 0, 72);
		sprintf(fname, "ubipac%d", loop);
		write_mem_to_mmc(NULL, fname, fs_type, buf, write_len);
		debugf("write ubipac%d end\n", loop);
	}
	put_mtd_device(mtd);
}
#endif

unsigned char *get_dt_addr(void)
{
	unsigned char *dt_addr = DT_ADR;
	boot_img_hdr *hdr = (void *)raw_header;
	if (1 == _get_kernel_ramdisk_dt_offset(hdr, "boot"))
		load_fixup_dt_img("boot", &dt_addr);
	return dt_addr;
}

static int check_dts_reserved_mem_node(unsigned char *fdt_blob)
{
	int nodeoffset = fdt_path_offset(fdt_blob, "/reserved-memory");

	debugf("reserved-memory nodeoffset = %d\n", nodeoffset);

	return nodeoffset;
}

static int get_dts_version(unsigned char *fdt_blob, int nodeoffset)
{
	__be32 *list = NULL;
	int lenp, version;

	list = fdt_getprop(fdt_blob, nodeoffset, "version", &lenp);
	if (list == NULL) {
		debugf("no version property in sysdump node.\n");
		version = 0;
	} else {
		version = fdt_size_to_cpu(*list);
	}

	debugf("dts sysdump version is 0x%x.\n", version);
	return version;
}

static int check_dts_sysdump_node(unsigned char *fdt_blob)
{
	int nodeoffset = fdt_path_offset(fdt_blob, "/sprd-sysdump");

	debugf("sysdump nodeoffset = %d\n", nodeoffset);
	return nodeoffset;
}

static unsigned long get_sprd_dump_size_auto(struct sysdump_mem *sysmem, int mem_num)
{
	int i;
	SYSDUMP_LONG size = 0;

	for(i=0; i<mem_num; i++) {
		size += sysmem[i].size;
	}
#ifdef CONFIG_X86
	debugf("sysdump total size is 0x%llx !!!\n", size);
#else
	debugf("sysdump total size is 0x%lx !!!\n", size);
#endif
	return size;
}

static int fill_mem_from_dts(unsigned char *fdt_blob, int nodeoffset, const char *name, struct sysdump_mem *sprd_dump_mem)
{
	int i = 0;
	int lenp, size, phandle, lookup;
	unsigned long *ptr = NULL, *ptr_end = NULL;

	debugf("Now read dts %s property in the sysdump node !!!\n", name);
	ptr = fdt_getprop(fdt_blob, nodeoffset, name, &lenp);
	__be32 *list = fdt_getprop(fdt_blob, nodeoffset, name, &size);
	if (list == NULL) {
		debugf("ERROR: no %s property !!!\n", name);
		return 0;
	}
	__be32 *list_end = list + size / sizeof(*list);

	while (list < list_end) {
		phandle = be32_to_cpup(list++);
		lookup = fdt_node_offset_by_phandle(fdt_blob, phandle);

		ptr = fdt_getprop(fdt_blob, lookup, "reg", &lenp);
		if (ptr == NULL) {
			debugf("ERROR: no reg in %s property !!!\n", name);
			return 0;
		}
		else {
			ptr_end = ptr + lenp / (sizeof(SYSDUMP_LONG));
			while (ptr < ptr_end) {
				sprd_dump_mem[i].paddr = fdt_addr_to_cpu (*ptr ++);
#ifdef CONFIG_X86
				sprd_dump_mem[i].paddr = (sprd_dump_mem[i].paddr<<32) | fdt_addr_to_cpu(*ptr ++);
#endif
				sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
				sprd_dump_mem[i].size  = fdt_size_to_cpu (*ptr ++);
#ifdef CONFIG_X86
				sprd_dump_mem[i].size  = (sprd_dump_mem[i].size<<32) | fdt_addr_to_cpu(*ptr ++);
#endif
				sprd_dump_mem[i].soff  = 0xffffffff;
				sprd_dump_mem[i].type  = SYSDUMP_RAM;
#ifdef CONFIG_X86
				debugf("sprd_dump_mem[%d].paddr is 0x%llx\n", i, sprd_dump_mem[i].paddr);
				debugf("sprd_dump_mem[%d].size  is 0x%llx\n", i, sprd_dump_mem[i].size);
#else
				debugf("sprd_dump_mem[%d].paddr is 0x%lx\n", i, sprd_dump_mem[i].paddr);
				debugf("sprd_dump_mem[%d].size  is 0x%lx\n", i, sprd_dump_mem[i].size);
#endif
				i++;
			}
		}
	}

	debugf(" the %s memory num is %d\n", name, i);
	return i;
}

/* this function only support FAT filesysdump Now*/
static int sysdump_cyclic_storage(int fs_type, unsigned long long dump_size)
{
	char path[72] = {0};
	char path_rename[72] = {0};
	int i, j, mod, ret = 0;
	unsigned char key_code = 0;
	bool delete_flag = false;
	bool nospace_flag = false;
	dir_entry *dentptr = NULL;

	/*setp 1. check available space: delete or format*/
	mod = fat_checksys(dump_size);
	if (mod & FSNOSPACE) {
		nospace_flag = true;
		for (i = 1; i <= SYSDUMP_FOLDER_NUM; i++) {
			sprintf(path, SYSDUMP_FOLDER_NAME"/%d", i);
			path[strlen(path)] = '\0';
			dentptr = check_folder_flag(path);
			if(dentptr == NULL)
				break;
		}

		if (i != 1 ) {
			for(j = i; j != 1;) {
				sprintf(path, SYSDUMP_FOLDER_NAME"/%d", --j);
				path[strlen(path)] = '\0';
				ret = delete_folder(path);
				if(ret != 0) {
					debugf("ERROR: delete files or folder failed !!!\n");
					return -1;
				}
				mod = fat_checksys(dump_size);
				if (!(mod & FSNOSPACE)) {
					nospace_flag = false;
					break;
				}
			}
		}

		if (nospace_flag) {
			sysdump_lcd_printf("\nHello Baby: SD Card have not enough space !!!");
			sysdump_lcd_printf("\npress volumedown to format SD Card !!!\notherwise press volumeup to skip sysdump !!!\n");
			do {
				udelay(50 * 1000);
				key_code = board_key_scan();
				if (key_code == KEY_VOLUMEDOWN) {
					if (fs_type == FS_FAT32) {
						fat_format();
						break;
					}else
						return -1;
				} else if (key_code == KEY_VOLUMEUP) {
					return -1;
				}
			} while (1);
		}
	}

	/*step 2. enter /ylog/sysdump*/
	if(do_new_folder(SYSDUMP_FOLDER_NAME)) {
		debugf("ERROR: creat %s folder failed !!!\n", SYSDUMP_FOLDER_NAME);
		return -1;
	}

	/*step 3. check existed folder*/
	for (i = 1; i <= SYSDUMP_FOLDER_NUM; ++i) {
		sprintf(path, SYSDUMP_FOLDER_NAME"/%d", i);
		path[strlen(path)] = '\0';
		dentptr = check_folder_flag(path);
		if(dentptr == NULL)
			break;
	}

	/*setp 4. delete folder greater than set number*/
	if (i > SYSDUMP_FOLDER_NUM) {
		debugf("there existed %d history log !!!\n", SYSDUMP_FOLDER_NUM);
		i --;
		sprintf(path, SYSDUMP_FOLDER_NAME"/%d", i);
		path[strlen(path)] = '\0';
		ret = delete_folder(path);
		if(ret != 0)
			debugf("Error: delete files or folder\n");
	}

	/*setp 5. rename folder*/
	for(j = i - 1; j > 0 && i != 1; j = j - 2) {
		sprintf(path, SYSDUMP_FOLDER_NAME"/%d", j++);
		path[strlen(path)] = '\0';
		sprintf(path_rename, SYSDUMP_FOLDER_NAME"/%d", j);
		path_rename[strlen(path_rename)] ='\0';
		debugf("rename folder from %s to %s !!!\n", path, path_rename);
		ret = rename_folder(path, path_rename);
		if (ret != 0) {
			debugf("ERROR: delete files or folder failed !!!\n");
			break;
		}
	}

	/*setp 6. create a new folder "1"*/
	sprintf(path, SYSDUMP_FOLDER_NAME"/%d", 1);
	path[strlen(path)] = '\0';
	debugf("create folder 1 !!!\n");
	ret = do_new_folder(path);
	if (ret != 0) {
		debugf("ERROR: creat %s folder failed !!!\n", path);
		return -1;
	}

	return 0;
}

static void reorder_reserved_memory_by_addr(struct sysdump_memory *memArray, int size)
{
	int i, j, min;
	struct sysdump_memory temp;

	for (i=0; i<size; i++) {
		min = i;
		for (j=i+1; j<size; j++) {
			if (memArray[min].addr > memArray[j].addr) {
				min = j;
			}
		}

		if (min != i) {
			temp.addr = memArray[min].addr;
			temp.size = memArray[min].size;
			memArray[min].addr = memArray[i].addr;
			memArray[min].size = memArray[i].size;
			memArray[i].addr = temp.addr;
			memArray[i].size = temp.size;
		}
	}

	return;
}

#ifdef CONFIG_X86
static u32 e820_map_auto_detect(struct e820entry *entries)
{
	u32 e820_entries_detect = 0;
	int i = 0;
	ddr_info_t* ddr_info = get_ddr_range();
	e820_entries_detect = ddr_info->section_number;

	entries->addr = U32_T_U64(ddr_info->sec_info[0].start_address_high,ddr_info->sec_info[0].start_address_low)+VMM_RESERVE_SIZE;
	entries->size  = U32_T_U64(ddr_info->sec_info[0].end_address_high,ddr_info->sec_info[0].end_address_low)-entries->addr;
	entries->type  = E820_RAM;
	debugf("e820 entry addr = 0x%08llx, entry size = 0x%llx !!!\n", entries->addr, entries->size);
	entries++;

	for (i = 1; i < e820_entries_detect; i++) {
		entries->addr = U32_T_U64(ddr_info->sec_info[i].start_address_high,ddr_info->sec_info[i].start_address_low);
		entries->size  = U32_T_U64(ddr_info->sec_info[i].end_address_high,ddr_info->sec_info[i].end_address_low)-entries->addr;
		entries->type  = E820_RAM;
		debugf("e820 entry addr = 0x%08llx, entry size = 0x%llx !!!\n", entries->addr, entries->size);
		entries++;
	}

	debugf("e820 total num is %d !!!\n", e820_entries_detect);
	return e820_entries_detect;
}
#endif

static int get_total_dump_memory(struct sysdump_mem *sprd_dump_mem)
{
	int k, i = 0; mem_num = 0;

#ifdef CONFIG_X86
	struct e820entry x86_entries[5] = {0};
	mem_num = e820_map_auto_detect(x86_entries);

	if (VMM_RESERVE_SIZE) {
		debugf("dump vmm memory region !!!\n");
		sprd_dump_mem[0].paddr = 0;
		sprd_dump_mem[0].vaddr = 0;
		sprd_dump_mem[0].size  = VMM_RESERVE_SIZE;
		sprd_dump_mem[0].soff  = 0xffffffff;
		sprd_dump_mem[0].type  = SYSDUMP_RAM;
		i ++;
	}

	for (k = 0; k < mem_num; k++) {
		sprd_dump_mem[i].paddr = x86_entries[k].addr;
		sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
		sprd_dump_mem[i].size = x86_entries[k].size + 1;
		sprd_dump_mem[i].soff  = 0xffffffff;
		sprd_dump_mem[i].type  = SYSDUMP_RAM;
		i ++;
	}

	mem_num = i;
	for (k = 0; k < mem_num; k++)
		debugf("linux memory addr = 0x%llx, size = 0x%llx !!!\n", sprd_dump_mem[k].paddr,sprd_dump_mem[k].size);
#else
	phys_addr_t ddr_base = CONFIG_SYS_SDRAM_BASE;
	phys_size_t ddr_size = get_real_ram_size();

	sprd_dump_mem[0].paddr = ddr_base;
	sprd_dump_mem[0].vaddr =  __va(sprd_dump_mem[i].paddr);
	sprd_dump_mem[0].size = ddr_size;
	sprd_dump_mem[0].soff  = 0xffffffff;
	sprd_dump_mem[0].type  = SYSDUMP_RAM;

	i ++;
	mem_num = i;
	for (k = 0; k < mem_num; k++)
		debugf("linux memory addr = 0x%lx, size = 0x%lx!!!\n", sprd_dump_mem[k].paddr, sprd_dump_mem[k].size);
#endif

	return mem_num;
}

static int recalculate_kernel_memory(unsigned char *fdt_blob, int nodeoffset, int ofs_remem, int dts_version, struct sysdump_mem *sprd_dump_mem)
{
	char *pStr=NULL;
	char nodename[256];
	struct sysdump_memory *entries = NULL;
	int j = 0, mem_used = 0, i = 0, k, offset, str_len;
	SYSDUMP_LONG maddr, msize, base_addr;
	SYSDUMP_LONG old_addr = 0, old_size=0;

	/* get linux memory region */
#ifdef CONFIG_X86
	struct e820entry x86_entries[5] = {0};

	if (dts_version == 0xa1)
		mem_num = e820_map_auto_detect(x86_entries);
	for (k = 0; k < mem_num; k++) {
		linux_memory[k].addr = x86_entries[k].addr;
		linux_memory[k].size = x86_entries[k].size;
		debugf("linux memory addr = 0x%llx, size = 0x%llx !!!\n", linux_memory[k].addr, linux_memory[k].size);
	}
#else
	struct sysdump_mem arm_entries[5] = {0};

	mem_num = fill_mem_from_dts(fdt_blob, nodeoffset, "memory-region", arm_entries);
	for (k = 0; k < mem_num; k++) {
		linux_memory[k].addr = arm_entries[k].paddr;
		linux_memory[k].size = arm_entries[k].size - 1;
		debugf("linux memory addr = 0x%lx, size = 0x%lx!!!\n", linux_memory[k].addr, linux_memory[k].size);
	}
#endif

	/* get linux reserved-memory region */
	for (offset = fdt_first_subnode(fdt_blob, ofs_remem); offset >= 0; offset = fdt_next_subnode(fdt_blob, offset)) {

		sprintf(nodename, "%s", fdt_get_name(fdt_blob, offset, NULL));
		str_len = strlen(nodename);
		nodename[str_len] = '\0';
		pStr = strstr(nodename, "sysdump-uboot");
		if (pStr) {
			debugf("find sysdump-uboot reserved memory\n" );
			continue;
		}
		fdt_get_addr_size(fdt_blob, offset, "reg", &maddr, &msize);
		reserved_memory[re_num].addr = maddr;
		reserved_memory[re_num].size = msize;
#ifdef CONFIG_X86
		//	debugf("reserved-memory addr is %llx\n", reserved_memory[re_num].addr);
		//	debugf("reserved-memory size is %llx\n", reserved_memory[re_num].size);
#else
		//	debugf("reserved-memory addr is %lx\n", reserved_memory[re_num].addr);
		//	debugf("reserved-memory size is %lx\n", reserved_memory[re_num].size);
#endif
		re_num++;
	}
	debugf("reserved-memory num is %d !!!\n", re_num);

	/* reorder reserved-memory by addr */
	reorder_reserved_memory_by_addr(reserved_memory, re_num);

	entries = linux_memory;
#ifdef CONFIG_X86
	base_addr = VMM_RESERVE_SIZE;
#else
	base_addr = linux_memory[0].addr;
#endif
	for (k = 0; k < re_num; k++) {
		maddr = reserved_memory[k].addr;
		msize = reserved_memory[k].size;
#ifdef CONFIG_X86
		debugf("base_addr is 0x%llx\n", base_addr);
		debugf("fdt addr is 0x%llx\n", maddr);
		debugf("fdt size is 0x%llx\n", msize);
#else
		debugf("base_addr is 0x%lx\n", base_addr);
		debugf("fdt addr is 0x%lx\n", maddr);
		debugf("fdt size is 0x%lx\n", msize);
#endif

		if ((maddr + msize) > (entries->addr + entries->size +1)) {  //next entry
			base_addr = entries->addr + entries->size + 1;
			entries++;  mem_used++;

			if (base_addr == old_addr+old_size) {
				base_addr = entries->addr;
			} else if (base_addr > old_addr+old_size) {
				debugf("d1\n");
				sprd_dump_mem[i].paddr = old_addr + old_size;
				sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
				sprd_dump_mem[i].size  = base_addr - sprd_dump_mem[i].paddr;
				sprd_dump_mem[i].soff  = 0xffffffff;
				sprd_dump_mem[i].type  = SYSDUMP_RAM;
				base_addr = entries->addr;
				i++;
			}

			if(maddr == base_addr) {
				base_addr += msize;
			} else if (maddr > base_addr) {
				debugf("d2\n");
				if (maddr <= (entries->size + 1)) {
					sprd_dump_mem[i].paddr = base_addr;
					sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
					sprd_dump_mem[i].size  = maddr - base_addr;
					sprd_dump_mem[i].soff  = 0xffffffff;
					sprd_dump_mem[i].type  = SYSDUMP_RAM;
					base_addr = maddr + msize;
					i++;
				} else {
					sprd_dump_mem[i].paddr = base_addr;
					sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
					sprd_dump_mem[i].size  = entries->addr + entries->size - base_addr + 1;
					sprd_dump_mem[i].soff  = 0xffffffff;
					sprd_dump_mem[i].type  = SYSDUMP_RAM;
					i++;
					entries++;
					mem_used++;
					base_addr = entries->addr;
				}
			}
		} else {   //this entry
			if (maddr == base_addr) {
				base_addr += msize;
			} else if (maddr > base_addr) {
				debugf("d3\n");
				sprd_dump_mem[i].paddr = base_addr;
				sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
				sprd_dump_mem[i].size  = maddr - base_addr;
				sprd_dump_mem[i].soff  = 0xffffffff;
				sprd_dump_mem[i].type  = SYSDUMP_RAM;
				base_addr = maddr + msize;
				i++;
			} else {
				debugf("ERROR: maddr < base_addr !!!\n");
				return 0;
			}
		}

			old_addr = maddr;
			old_size = msize;
	}

	if (mem_used <= mem_num-1) {
		for (j=mem_used; j<=mem_num-1; j++) {
			if (j == mem_used) {
				if ((maddr+msize) < (entries->addr + entries->size + 1)) {
					debugf("d4\n");
					sprd_dump_mem[i].paddr = maddr+msize;
					sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
					sprd_dump_mem[i].size  = entries->addr + entries->size + 1 - sprd_dump_mem[i].paddr;
					sprd_dump_mem[i].soff  = 0xffffffff;
					sprd_dump_mem[i].type  = SYSDUMP_RAM;
					i++;
				}
				entries++;
			} else {
				debugf("d5\n");
				sprd_dump_mem[i].paddr = entries->addr;
				sprd_dump_mem[i].vaddr = __va(sprd_dump_mem[i].paddr);
				sprd_dump_mem[i].size  = entries->size + 1;
				sprd_dump_mem[i].soff  = 0xffffffff;
				sprd_dump_mem[i].type  = SYSDUMP_RAM;
				i++;
				entries++;
			}
		}
	}

	debugf(" linux memory need dump %d region !!!\n", i);
	return i;
}

#ifdef CONFIG_ARM
static int fill_dump_mem_auto_arm(unsigned char *fdt_blob, int nodeoffset, int ofs_remem,
				int dts_version, struct sysdump_mem *sprd_dump_mem)
{
	int ret = 0, i = 0;
	int arm_dump_mem_num = 0;
	 struct sysdump_mem *temp_mem = sprd_dump_mem;

	/* calculate linux memory region */
	debugf("calculate linux memory region !!!\n");
	ret = recalculate_kernel_memory(fdt_blob, nodeoffset, ofs_remem, dts_version, sprd_dump_mem);
	if (ret == 0)
		debugf("ERROR: ARM: linux memory recalculation failed !!!\n");
	else {
		i += ret;
		temp_mem += ret;
	}

	/* calculate specific reserved-memory*/
	debugf("read reserved-memory region from sysdump node !!!\n");
	ret = fill_mem_from_dts(fdt_blob, nodeoffset, "memory-region-re", temp_mem);
	if (ret == 0)
		debugf("ERROR: ARM: memory-region-re dump failed !!!\n");
	else
		i += ret;

	arm_dump_mem_num = i;
	debugf("auto arm_dump_mem_num is %d\n", arm_dump_mem_num);

	for (i = 0; i < arm_dump_mem_num; i++) {
		debugf("auto arm_dump_mem[%d].paddr is 0x%lx\n", i, sprd_dump_mem[i].paddr);
		debugf("auto arm_dump_mem[%d].size  is 0x%lx\n", i, sprd_dump_mem[i].size);
	}

	return arm_dump_mem_num;
}
#endif

/* i: memory region form dts */
static void write_to_mmc(char *path, char *filename, int fs_type,
	void *memaddr, struct sysdump_mem *mem, int i)
{
#ifdef CONFIG_RAMDUMP_NO_SPLIT
	sprintf(filename,
		SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_"LLX"-"LLX"_dump.lst",
		i + 1, mem[i].paddr, mem[i].paddr+mem[i].size -1);
	write_mem_to_mmc(path, filename, fs_type, memaddr, mem[i].size);
#else
	int j;
	if (mem[i].size <= SZ_8M) {
		sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_"LLX,
			i + 1,mem[i].paddr);
		write_mem_to_mmc(path, filename, fs_type, memaddr, mem[i].size);
	} else {
		for (j = 0; j < mem[i].size / SZ_8M; j++) {
			sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_%03d_"LLX,
				i + 1, j, mem[i].paddr+j*SZ_8M);
			write_mem_to_mmc(path, filename, fs_type, memaddr + j*SZ_8M, SZ_8M);
		}
		if (mem[i].size % SZ_8M) {
			sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_%03d_"LLX,
				i + 1, j, mem[i].paddr+j*SZ_8M);
			write_mem_to_mmc(path, filename, fs_type, memaddr + j*SZ_8M, (mem[i].size % SZ_8M));
		}
	}
#endif
}

#ifdef CONFIG_X86
/*
 * i: memory region form dts
 * k: number k block in i
 */
static void write_to_mmc_x86(char *path, char *filename, int fs_type,
				void *memaddr, struct sysdump_mem *mem,
				int i, int k, unsigned long size)
{
	unsigned long long vaddr = mem[i].paddr+k*SYSDUMP_256M;

#ifdef CONFIG_RAMDUMP_NO_SPLIT
	sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_%03d_"LLX"-"LLX"_dump.lst",
		i + 1, k, vaddr, vaddr+size -1);
	write_mem_to_mmc(path, filename, fs_type, memaddr, size);
#else
	int j;
	if (size <= SZ_8M) {
		sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_"LLX, i + 1, vaddr);
		write_mem_to_mmc(path, filename, fs_type, memaddr, size);
	} else {
		for (j = 0; j < size/SZ_8M; j++) {
			sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_%03d_"LLX,
				i + 1, j, vaddr+j*SZ_8M);
			write_mem_to_mmc(path, filename, fs_type, memaddr + j*SZ_8M, SZ_8M);
		}
		if (size%SZ_8M) {
			sprintf(filename, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT"_%03d_"LLX,
				i + 1, j, vaddr+j*SZ_8M);
			write_mem_to_mmc(path, filename, fs_type, memaddr + j*SZ_8M, (size % SZ_8M));
		}
	}
#endif
}

static int fill_dump_mem_auto_x86(unsigned char *fdt_blob, int nodeoffset, int ofs_remem,
				int dts_version, struct sysdump_mem *sprd_dump_mem)
{
	unsigned long long temp_size = 0;
	int x86_dump_mem_num, ret, j= 0, i = 0;
	struct sysdump_mem *temp_mem = sprd_dump_mem; 

	/* step1: vmm region */
	if (VMM_RESERVE_SIZE) {
		debugf("dump vmm memory region !!!\n");
		sprd_dump_mem[0].paddr = 0;
		sprd_dump_mem[0].vaddr = 0;
		sprd_dump_mem[0].size  = VMM_RESERVE_SIZE;
		sprd_dump_mem[0].soff  = 0xffffffff;
		sprd_dump_mem[0].type  = SYSDUMP_RAM;
		i++;
		temp_mem++;
	}

	debugf("dump reset mode is 0x%x\n", dump_rst_mode);

	/* step2: memory region from kernel dts */
	if (dump_rst_mode == CMD_TOS_PANIC_MODE) {
		debugf("read security memory region from sysdump node !!!\n");
		ret = fill_mem_from_dts(fdt_blob, nodeoffset, "memory-region-se", temp_mem);
		if (ret == 0)
			debugf("ERROR: X86: memory-region-se dump failed !!!\n");
		else {
			i += ret;
			temp_mem += ret;
		}
	}

	/* step3: auto calculate linux memory region */
	if (dump_rst_mode != CMD_TOS_PANIC_MODE) {

		/* calculate specific reserved-memory*/
		debugf("read reserved-memory region from sysdump node !!!\n");
		ret = fill_mem_from_dts(fdt_blob, nodeoffset, "memory-region-re", temp_mem);
		if (ret == 0)
			debugf("ERROR: x86: memory-region-re dump failed !!!\n");
		else {
			i += ret;
			temp_mem += ret;
		}

		/* calculate linux memory region */
		debugf("calculate linux memory region !!!\n");
		ret = recalculate_kernel_memory(fdt_blob, nodeoffset, ofs_remem, dts_version, temp_mem);
		if (ret == 0)
			debugf("ERROR: x86: linux memory recalculation failed !!!\n");
		else {
			i += ret;
			temp_mem += ret;
		}

	}

	/* step4: return */
	x86_dump_mem_num = i;
	debugf("auto x86_dump_mem_num is %d\n", x86_dump_mem_num);
	for (i = 0; i < x86_dump_mem_num; i++) {
		debugf("auto x86_dump_mem[%d].paddr is 0x%llx\n", i, sprd_dump_mem[i].paddr);
		debugf("auto x86_dump_mem[%d].size  is 0x%llx\n", i, sprd_dump_mem[i].size);
	}

	return x86_dump_mem_num;
}
#endif

void write_sysdump_before_boot(int rst_mode)
{
	sha1_context ctx;
	struct rtc_time tm;
	int dts_version = 0;       /* 0:old version, memory region transfer by DTS;  0xA1: auto calculate linux memory region */
	struct sysdump_mem *mem;
	char txt_info[2000] = {0};
	unsigned char sha1sum[20];
	dir_entry *dentptr = NULL;
	SYSDUMP_LONG max_size = 0;
	unsigned char *dt_addr = NULL;
	struct sysdump_info *infop = NULL;
	int nodeoffset = 0, ofs_remem = 0;
	unsigned long sprd_sysdump_magic = 0;
	unsigned char sysdump_checksum[1000] = {0};
	int i, j, k, sprd_dump_mem_num, ret, fs_type;
	struct sysdump_mem sprd_dump_mem[MAX_NUM_DUMP_MEM];
	int mod, key_code, auto_test_flag = 0, s_length =0, chk_length = 0, dt_fail = 0;
	char fnbuf[72] = {0}, fnbuf_rename[72] = {0}, *path, *waddr, *string, *check_sum;

#ifdef CONFIG_X86
	unsigned long mem_virt;
        int m = 0, n = 0, n_max = 1024;
        uint32_t crash_data[n_max];
#endif
	dump_rst_mode = rst_mode;
	sprd_sysdump_magic = SPRD_SYSDUMP_MAGIC;
	infop = (struct sysdump_info *)sprd_sysdump_magic;

	debugf("rst_mode:0x%x, Check if need to write sysdump info of 0x%08lx to file...\n", rst_mode,
	sprd_sysdump_magic);

	if (!sysdump_flag)
		rst_mode = CMD_NORMAL_MODE;

	if ((rst_mode == CMD_WATCHDOG_REBOOT) || (rst_mode == CMD_AP_WATCHDOG_REBOOT) || (rst_mode == CMD_UNKNOW_REBOOT_MODE) || \
		(rst_mode == CMD_EXT_RSTN_REBOOT_MODE) || ((rst_mode == CMD_PANIC_REBOOT) && !memcmp(infop->magic, SYSDUMP_MAGIC, sizeof(infop->magic))) \
		|| (rst_mode == CMD_SPECIAL_MODE) || (rst_mode == CMD_VMM_PANIC_MODE) || (rst_mode == CMD_TOS_PANIC_MODE)) {

		debugf("Now enter in sysdump!!!\n");

		dt_addr = get_dt_addr();
		nodeoffset = check_dts_sysdump_node(dt_addr);
		if (nodeoffset < 0) {
			debugf("ERROR: device tree must have /sprd-sysdump node %s !!!\n", fdt_strerror(nodeoffset));
			dt_fail = 1;
		}

		if(!dt_fail)
			dts_version = get_dts_version(dt_addr, nodeoffset);
		memset(infop->magic, 0, sizeof(infop->magic));

#ifdef CONFIG_SPLASH_SCREEN
		extern int drv_lcd_init(void);
		drv_lcd_init();
		lcd_splash(LOGO_PART);
		lcd_enable();
#endif

		/* display on screen */
		display_writing_sysdump();
		#define CONSOLE_COLOR_RED (0x1f<<11)
		#define CONSOLE_COLOR_GREEN 0x07e0
		sysdump_lcd_printf("\nReset mode: %s\n\n",GET_RST_MODE(rst_mode));

		memset(infop->reason, '\0', sizeof(infop->reason));
		memcpy(infop->reason, GET_RST_MODE(rst_mode), strlen(GET_RST_MODE(rst_mode)));

		if (init_mmc_fat(&fs_type)) {
			debugf("ERROR: init_mmc_fat,fs_type=%d.\n", fs_type);
			sysdump_lcd_printf("\ninit_mmc_fat failed, Please check SD Card!!!.\nPress volume up key (Exp power key) to continue...");
                        wait_for_keypress();
			goto FINISH;
		}

		if (!dt_fail) {
			ofs_remem = check_dts_reserved_mem_node(dt_addr);
			if (ofs_remem < 0) {
				debugf("ERROR: device tree must have /reserved-memory node %s.\n", fdt_strerror(ofs_remem));
				goto FINISH;
			}
		}

		if (!dt_fail) {
#ifdef CONFIG_X86
		sprd_dump_mem_num = fill_dump_mem_auto_x86(dt_addr, nodeoffset, ofs_remem, dts_version, sprd_dump_mem);
		infop->dump_mem_paddr = (unsigned long long)sprd_dump_mem;
#else
		sprd_dump_mem_num = fill_dump_mem_auto_arm(dt_addr, nodeoffset, ofs_remem, 0, sprd_dump_mem);
		infop->dump_mem_paddr = (unsigned long)sprd_dump_mem;
#endif
		} else {
			sprd_dump_mem_num = get_total_dump_memory(sprd_dump_mem);
			infop->dump_mem_paddr = (unsigned long)sprd_dump_mem;
		}

		infop->mem_num = sprd_dump_mem_num;
		infop->elfhdr_size = get_elfhdr_size(infop->mem_num);
		memset((char *)infop + sizeof(*infop), 0, infop->elfhdr_size);
		sysdump_fill_core_hdr(NULL,
					sprd_dump_mem,
					sprd_dump_mem_num,
					(char *)infop + sizeof(*infop),
					infop->mem_num + 1,
					infop->elfhdr_size);

		if ((rst_mode == CMD_WATCHDOG_REBOOT) || (rst_mode == CMD_AP_WATCHDOG_REBOOT) || \
			(rst_mode == CMD_UNKNOW_REBOOT_MODE) || (rst_mode == CMD_EXT_RSTN_REBOOT_MODE) || \
			(rst_mode == CMD_SPECIAL_MODE) || (rst_mode == CMD_VMM_PANIC_MODE) || (rst_mode == CMD_TOS_PANIC_MODE))
			infop->crash_key = 0;

		if (strlen(infop->dump_path)) {
			debugf("sysdump path length is %d !!!\n", strlen(infop->dump_path));
			path = infop->dump_path;
		} else {
			debugf("sysdump use default path !!!\n");
			path = NULL;
			memset(infop->dump_path, '\0', sizeof(infop->dump_path));
                }

	max_size = get_sprd_dump_size_auto(sprd_dump_mem, sprd_dump_mem_num);
	max_size += (unsigned long)infop->elfhdr_size;
	debugf("FAT32 max space size is %lx\n",max_size);
	if (fs_type == FS_FAT32) {
		debugf("FileSystem is FAT32 !!!\n");

		mod = fat_checksys(max_size);
		if (mod & FSFATAL) {
			sysdump_lcd_printf("\nHello Baby: SD Card is demaged !!!");
			do {
				udelay(50 * 1000);
				key_code = board_key_scan();
				if (key_code == KEY_VOLUMEDOWN) {
					fat_format();
					break;
				} else if(key_code == KEY_VOLUMEUP)
					goto FINISH;
			} while (1);
		}

		ret = sysdump_cyclic_storage(fs_type,max_size);
		if (ret < 0)
			goto FINISH;

		debugf("check sysdump_auto_test.txt start!!!\n");
		if(check_folder_flag(SYSDUMP_AUTO_TEST)) {
			auto_test_flag = 1;
			debugf("Now has existed sysdump_auto_test.txt, so jump wait_for_keypress !!!\n");
		}
		debugf("check sysdump_auto_test.txt end!!!\n");

	} else if (fs_type == FS_EXFAT) {
		debugf("FileSystem is exFAT !!!\n");

		mod = exfat_checksys(max_size);
		if (mod & FSSMSIZE) {
			debugf("SD card volume size is smaller then dumped size. Skip sysdump !!!\n");
			goto FINISH;
		}

		if (mod &(FSFATAL | FSNOSPACE)) {
			if (mod & FSFATAL)
				sysdump_lcd_printf("\nHello Baby: SD Card is demaged !!!");
			else if (mod & FSNOSPACE)
				sysdump_lcd_printf("\nHello Baby: SD Card has not enough space !!!");

			sysdump_lcd_printf("\npress volumedown to format SD Card !!!\notherwise press volumeup to skip sysdump !!!\n");
			do {
				udelay(50 * 1000);
				key_code = board_key_scan();
				if (key_code == KEY_VOLUMEDOWN) {
					int ret;
					sysdump_lcd_printf("\nNow volumedown key is pressed !!!\nSD Card format starts........\n");
					ret = exfat_format();
					if (ret != 0) {
						sysdump_lcd_printf("\nSD Card format failed !!! Skip sysdump !!!\n");
						goto FINISH;
					}
					debugf("SD Card formatting done !!!\n");
					break;
				} else if(key_code == KEY_VOLUMEUP) {
					sysdump_lcd_printf("\nvolumedup key is pressed and don't format SD Card !!!\nsysdump will be skipped !!!\n");
					goto FINISH;
				}
			} while (1);
		}
	}
	else {
		sysdump_lcd_printf("Invalid file system... Sysdump will be skipped !!!\n");
		goto FINISH;
	}

		tm = get_time_by_sec();
		sprintf(infop->time, "%04d-%02d-%02d_%02d:%02d:%02d",
			tm.tm_year, tm.tm_mon, tm.tm_mday, \
			tm.tm_hour,tm.tm_min, tm.tm_sec);

		debugf("time is %04d.%02d.%02d_%02d:%02d:%02d\n", tm.tm_year, tm.tm_mon, \
			tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

#ifdef CONFIG_X86
	n = crash_data_receive(crash_data, n_max);
	char info_crash_data[9216] = {0};/* info_crash_data's size = n_max*sizeof("%08X\n") */
	if (n < 0) {
		debugf("error receiving crash log\n");
	}else{
		debugf("crash log size: %d words\n", n);
		for (m = 0; m < n; m += 1) {
			debugf("%08X\n", crash_data[m]);
			snprintf(info_crash_data+9*m,9216,"%08X\n",crash_data[m]);
		}
		sprintf(fnbuf,SYSDUMP_FOLDER_NAME"/1/Crashlog_%04d_%02d_%02d_%02d_%02d_%02d.txt", \
			tm.tm_year, tm.tm_mon, tm.tm_mday, \
			tm.tm_hour, tm.tm_min, tm.tm_sec);
		write_mem_to_mmc(path, fnbuf, fs_type, (char *)(info_crash_data), strlen(info_crash_data));
	}
#endif
		sprintf(fnbuf,SYSDUMP_FOLDER_NAME"/1/%04d_%02d_%02d_%02d_%02d_%02d.txt", \
			tm.tm_year, tm.tm_mon, tm.tm_mday, \
			tm.tm_hour, tm.tm_min, tm.tm_sec);

		string = txt_info;
		s_length = sprintf(txt_info,"-%s%s\n-%s%x\n-%s%x\n-%s%s\n-%s%d\n-%s%d\n-%s%d\n-%s"LLX"\n\n",
			"time is ",
			infop->time,
			"reboot reg is ",
			reboot_reg,
			"reset mode is ",
			dump_rst_mode,
			"reason is ",
			infop->reason,
			"elfhdr_size is ",
			infop->elfhdr_size,
			"mem_num is ",
			infop->mem_num,
			"crash_key is ",
			infop->crash_key,
			"dump_mem_paddr is ",
			infop->dump_mem_paddr);

		/* record linux memory & reserved memory & dump memory to txt file */
		for(i = 0; i < mem_num; i++) {
			s_length += sprintf(string + s_length, "linux memory %d: "LLX"-"LLX"\n", i + 1,
				linux_memory[i].addr, linux_memory[i].addr + linux_memory[i].size);
		}

		for(i = 0; i < re_num; i++) {
			s_length += sprintf(string + s_length, "reserved memory %d: "LLX"-"LLX"\n", i + 1,
				reserved_memory[i].addr, reserved_memory[i].addr + reserved_memory[i].size);
		}

		for(i = 0; i < sprd_dump_mem_num; i++) {
			s_length += sprintf(string + s_length, "sprd dump memory %d: "LLX"-"LLX"\n", i + 1,
				sprd_dump_mem[i].paddr, sprd_dump_mem[i].paddr + sprd_dump_mem[i].size -1);
		}
		debugf("txt_info is 0x%x and s_length is 0x%x\n", strlen(txt_info),s_length);
		write_mem_to_mmc(path, fnbuf, fs_type, (char *)(txt_info), s_length);
		/* record memory finished */

		sprintf(fnbuf, SYSDUMP_FOLDER_NAME"/1/"SYSDUMP_CORE_NAME_FMT, 0);
		write_mem_to_mmc(path, fnbuf, fs_type,
			(char *)infop + sizeof(*infop), infop->elfhdr_size);

		/*sysdump header checksum start*/
		check_sum = sysdump_checksum;
		sha1_starts(&ctx);
		sha1_update(&ctx, (char *)infop + sizeof(*infop), infop->elfhdr_size);
		sha1_finish(&ctx,sha1sum);
		chk_length += sprintf(check_sum + chk_length, SYSDUMP_CORE_NAME_FMT" ", 0);
		for(j = 0; j < 20; j++)
			chk_length += sprintf(check_sum + chk_length, "%02x", sha1sum[j]);
		chk_length += sprintf(check_sum + chk_length, "\n");
		/*sysdump header checksum end*/

#ifdef CONFIG_ARM7_RAM_ACTIVE
		pmic_arm7_RAM_active();
#endif

		mem = (struct sysdump_mem *)infop->dump_mem_paddr;
		for (i = 0; i < sprd_dump_mem_num; i++) {
			if (0xffffffff != mem[i].soff)
				waddr = (char *)infop + sizeof(*infop) +
						infop->elfhdr_size + mem[i].soff;
			else {
				debugf("mem[%d].paddr is %llx\n", i, mem[i].paddr);
				debugf("mem[%d].size  is %llx\n", i, mem[i].size);
#ifdef CONFIG_X86
				if (mem[i].paddr > SYSDUMP_4GB) {  //if mem[i].paddr > SYSDUMP_4GB, mem[i].size should <= 512M
					cpu_paging_disable();
					mem_virt = cpu_page_remap(SYSDUMP_MAPPING_ADDR, mem[i].size, mem[i].paddr);

					if (!SPLIT_MEM_REGION) {
						cpu_paging_enable();
						memmove((void *)SYSDUMP_COPY_PADDR, (void *)mem_virt, mem[i].size);
						cpu_paging_disable();
						waddr = SYSDUMP_COPY_PADDR;
					} else {
						for (k=0; k<mem[i].size/SYSDUMP_256M; k++) {
							cpu_paging_enable();
							memmove((void *)SYSDUMP_COPY_PADDR, (void *)mem_virt+SYSDUMP_256M*k, SYSDUMP_256M);
							cpu_paging_disable();
							write_to_mmc_x86(path, fnbuf, fs_type, SYSDUMP_COPY_PADDR+k*SYSDUMP_256M, mem, i, k, SYSDUMP_256M);
						}
						if (mem[i].size%SYSDUMP_256M) {
							cpu_paging_enable();
							memmove((void *)SYSDUMP_COPY_PADDR, (void *)mem_virt+SYSDUMP_256M*k, mem[i].size%SYSDUMP_256M);
							cpu_paging_disable();
							write_to_mmc_x86(path, fnbuf, fs_type, SYSDUMP_COPY_PADDR+k*SYSDUMP_256M, mem, i, k, mem[i].size%SYSDUMP_256M);
						}
						goto FINISH_write_mmc;
					}
				} else
#endif
				{
					waddr = mem[i].paddr;
				}

			}

			/*dump memory checksum start*/
			if(((unsigned int)waddr < CONFIG_SYS_TEXT_BASE) && (((unsigned int)waddr + mem[i].size) > CONFIG_SYS_TEXT_BASE))
				debugf("this memory section include uboot image, don't verify memory !!!\n");
			else {
				debugf("calculate dump memory "LLX"-"LLX" sha1 checksum !!!\n",(SYSDUMP_LONG)waddr, (SYSDUMP_LONG)waddr + mem[i].size - 1);
				sha1_starts(&ctx);
				sha1_update(&ctx, waddr, mem[i].size);
				sha1_finish(&ctx,sha1sum);
				chk_length += sprintf(check_sum + chk_length, SYSDUMP_CORE_NAME_FMT"_"LLX"-"LLX"_dump.lst ",
						i + 1, mem[i].paddr, mem[i].paddr + mem[i].size -1);
				for(j = 0; j < 20; j++)
					chk_length += sprintf(check_sum + chk_length, "%02x", sha1sum[j]);
				chk_length += sprintf(check_sum + chk_length, "\n");
			}
			/*dump memory checksum end*/

			write_to_mmc(path, fnbuf, fs_type, waddr, mem, i);
		}

FINISH_write_mmc:
		/* write dump memory checksum to sd card*/
		debugf(" writing dump memory checksum to sd card !!!\n");
		sprintf(fnbuf,SYSDUMP_FOLDER_NAME"/1/sysdump-checksum.txt", \
                        tm.tm_year, tm.tm_mon, tm.tm_mday, \
                        tm.tm_hour, tm.tm_min, tm.tm_sec);
		debugf("sysdump_checksum is 0x%x and check_length is 0x%x\n", strlen(sysdump_checksum), chk_length);
		write_mem_to_mmc(path, fnbuf, fs_type, (char *)(sysdump_checksum), chk_length);

#ifdef CONFIG_ETB_DUMP
		debugf ("\n Start to dump ETB trace data\n");
		sprd_etb_hw_dis();
		sprd_etb_dump();
		write_mem_to_mmc(0, "etbdata_uboot.bin", fs_type, &etb_dump_mem[0], etb_buf_size * 4);
		debugf ("\n Dump ETB data finished\n");
#endif

#ifdef CONFIG_NAND_BOOT
		sysdump_lcd_printf("\nBegin to dump nand flash:\n");
		mtd_dump(fs_type);
#endif
		debugf("\nwriting done.\nPress any key to continue...");
		sysdump_lcd_printf("\nWriting done.\nPress any key (Exp power key) to continue...");
		if(!auto_test_flag)
			wait_for_keypress();
FINISH:
		debugf ("sysdump  finish or happen abnormally!!!\n");
#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR)
		reset_to_normal(CMD_NORMAL_MODE);
#endif
	} else
		debugf("no need dump memory !!!\n");

	return;
}
