#include "sprd_cpcmdline.h"
#include "loader_common.h"

char *g_CPcmdlineBuf = NULL;
#if defined( CONFIG_KERNEL_BOOT_CP )
char CPcmdlineBuf[MAX_CP_CMDLINE_LEN];
#endif
extern char *sprd_get_audiopa(void);
extern char *sprd_get_ddrid(void);
static const char *cmd_arr[] = {
	BOOT_MODE,
	CALIBRATION_MODE,
	LTE_MODE,
	AP_VERSION,
	RF_BOARD_ID,
	RF_HW_INFO,
	K32_LESS,
	AUTO_TEST,
#ifdef CONFIG_BOARD_ID
	CRYSTAL_TYPE,
	RF_HW_ID,
#endif
#ifdef CONFIG_HW_VER
	HW_VER,
#endif
#ifdef CONFIG_READ_EMMC_CID
	EMMC_CID,
#endif
#ifdef CONFIG_READ_EMMC_CID2
	EMMC_CID2,
#endif
#ifdef CONFIG_READ_DDR_ID
	DDR_ID,
#endif
#ifdef CONFIG_READ_AUDIO_PA
	AUDIO_PA,
#endif
	CHIPUID,
	NULL
};




struct emmc_id {
	char *manu_id;
	char *name;
};

static const struct emmc_id emmcid_array[] = {
	{"45", "SDIN7DP2-4G"},
	{"70", "EMMC04G-M627"},
	{"15", "KLM4G1FETE-B041001"},
	{"f4", "BWCMAB811G04G"},
};


static bool is_invalid_cmd(const char *cmd)
{
	int i = 0;
	while(NULL != cmd_arr[i])
	{
		if(0 == strcmp(cmd_arr[i], cmd)){
			return true;
		}
		i++;
	}
	return false;
}

static char *cpcmdline_get_lte_mode(void)
{
	char *ltemode = NULL;

#ifdef CONFIG_SUPPORT_TDLTE
	ltemode = "tcsfb";
#elif defined CONFIG_SUPPORT_WLTE
	ltemode = "fcsfb";
#elif defined CONFIG_SUPPORT_LTE
	ltemode = "lcsfb";
#endif

	return ltemode;
}

static void cmdline_prepare(void)
{
#if defined( CONFIG_KERNEL_BOOT_CP )
	g_CPcmdlineBuf = CPcmdlineBuf;
#else
#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
extern void *parse_cpcmdline_addr();
	g_CPcmdlineBuf = (char*)parse_cpcmdline_addr();
#else
#ifdef CALIBRATION_FLAG_CP0
	g_CPcmdlineBuf = (char*)CALIBRATION_FLAG_CP0;
#endif
#ifdef CALIBRATION_FLAG_CP1
	g_CPcmdlineBuf = (char*)CALIBRATION_FLAG_CP1;
#endif
#endif
#endif
	if (g_CPcmdlineBuf)
		memset(g_CPcmdlineBuf, 0, MAX_CP_CMDLINE_LEN);
	debugf("g_CPcmdlineBuf = 0x%p\n" , g_CPcmdlineBuf);
}

static void cmdline_add_cp_cmdline(char *cmd, char* value)
{
	char *p;
	int len;
	//printf("add cmd, cmd = %s, value = %s\n", cmd, value);

	if(!is_invalid_cmd(cmd))return;

	if (NULL == g_CPcmdlineBuf)
		return;

	len = strlen(g_CPcmdlineBuf);
	p = g_CPcmdlineBuf + len;


	if (len + strlen(value) > MAX_CP_CMDLINE_LEN) {
		printf("%s exceed max:%d. cmd:%s value:%s\n", __func__,
			MAX_CP_CMDLINE_LEN, cmd, value);
		return;
	}
	snprintf(p, MAX_CP_CMDLINE_LEN - len, "%s=%s ", cmd, value);
	//printf("cmd = %s\n" , p);
}

char *sprd_get_emmcid(void)
{
	extern char *emmc_cid;
	int i,j;
	unsigned int len = sizeof(emmcid_array) / sizeof(struct emmc_id);
	char *value;
	value = sprd_get_ddrid();
	char *temp;
		temp = "04EMCP04-AL2BM627/MR5:0xFD,MR8:0x18";
	printf("sprd_get_emmcid = %s,%s\n",emmc_cid,value); 
	if((strcmp(emmc_cid,"70") == 0) && (strcmp(value,temp) == 0)){
			value = "04EMCP04-AL2BM627";
			return value;
		}
		
	for (i = 0; i < len; i++) {
			j = strcmp(emmc_cid,emmcid_array[i].manu_id);
			printf("sprd_get_emmcid = %s\n",emmcid_array[i].manu_id);
		if (strcmp(emmc_cid,emmcid_array[i].manu_id) == 0)
		{
			printf("emmcid_array[i] = %d,%s\n",i,emmcid_array[i].manu_id);
			return emmcid_array[i].name;
		}
	}

	if (i == len)
		return NULL;
}

void cp_cmdline_fixup(void)
{
	char *value = NULL;
	int boardid = 0;
	int value_less = 0;
	char buf[30] = {0};
	unsigned char v32kless;
	extern char *emmc_cid2;
	cmdline_prepare();

	// androd boot mode
	value = getenv("bootmode");
	if (NULL != value)
	{
		cmdline_add_cp_cmdline(BOOT_MODE, value);
	}

	// calibration parameters
	value = get_calibration_parameter();
	if (NULL != value)
	{
		if (NULL != strstr(value, CALIBRATION_MODE))
		{
			// "calibration=%d,%d,146 ", must skipp calibration=
			value += strlen(CALIBRATION_MODE) + 1;
			cmdline_add_cp_cmdline(CALIBRATION_MODE, value);
		} else if (NULL != strstr(value, AUTO_TEST)) {
			// "autotest=1", must skipp autotest=
			value += strlen(AUTO_TEST) + 1;
			cmdline_add_cp_cmdline(AUTO_TEST, value);
		}
	}

	// lte mode
	value = cpcmdline_get_lte_mode();
	if(NULL != value)
	{
		cmdline_add_cp_cmdline(LTE_MODE, value);
	}

	//chip uid
#ifdef CONFIG_READ_UID
	{
		unsigned int block0;
		unsigned int block1;
		get_efuse_uid_ex(&block0,&block1);
		sprintf(buf,"0x%08x,0x%08x",block0,block1);
		cmdline_add_cp_cmdline(CHIPUID,buf);
	}
#endif
/* crystal and rf band auto adaption used on some platforms, such as sharkl, pike series */
#if (defined(CONFIG_SC9833) || defined(CONFIG_SOC_SHARKLJ1) || defined(CONFIG_SOC_SHARKLE) || defined(CONFIG_SOC_PIKE2) || defined(CONFIG_SOC_SHARKL3) || defined(CONFIG_SOC_SP9853I))
#if (defined(CONFIG_BOARD_ID) || defined(CONFIG_BAND_DETECT))
	//rf band auto adaption
	boardid = sprd_get_bandinfo();
	sprintf(buf,"%d",boardid);
	cmdline_add_cp_cmdline(RF_BOARD_ID, buf);
#endif
#ifdef CONFIG_BOARD_ID
	//board id
	value_less=sprd_get_boardid();
	sprintf(buf,"%d",value_less);
	cmdline_add_cp_cmdline(RF_HW_ID, buf);

	//26m crystal auto adaption
	sprintf(buf,"%d", sprd_get_crystal());
	cmdline_add_cp_cmdline(CRYSTAL_TYPE, buf);
#endif
	//32k crystal auto adaption
	sprintf(buf,"%d", sprd_get_32k());
	cmdline_add_cp_cmdline(K32_LESS, buf);
#endif


#ifdef CONFIG_HW_VER
	/* need extern, or else get error pointer */
	extern char *sprd_get_hwver(void);
	value = sprd_get_hwver();
	if (NULL != value)
		cmdline_add_cp_cmdline(HW_VER, value);
#endif
#ifdef CONFIG_READ_EMMC_CID
	value = sprd_get_emmcid();
	cmdline_add_cp_cmdline(EMMC_CID, value);
#endif
#ifdef CONFIG_READ_EMMC_CID2
	cmdline_add_cp_cmdline(EMMC_CID2, emmc_cid2);
#endif
#ifdef CONFIG_READ_DDR_ID
	value = sprd_get_ddrid();
	cmdline_add_cp_cmdline(DDR_ID, value);
#endif
#ifdef CONFIG_READ_AUDIO_PA
	value = sprd_get_audiopa();
	cmdline_add_cp_cmdline(AUDIO_PA, value);
#endif
	debugf("cp cmdline: %s\n", g_CPcmdlineBuf);
}

char *cp_getcmdline(void)
{
	return g_CPcmdlineBuf;
}

