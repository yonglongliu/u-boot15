#include "uboot_sec_drv.h"

static smc_param param;
/**
start_addr must be 32 bits addr
there are two ways if you want to use 64 bits addr:
1. put 64 bits addr to your own structure, then pass structure's addr here
2. seperate 64 bits addr to two 4 bytes and then put them into param, then call tee_smc_call
*/
smc_param *tee_common_call(uint32_t funcid, uint32_t start_addr, uint32_t lenth)
{
	memset(&param, 0x00, sizeof(smc_param));
	param.a0 = TEESMC_SIPCALL_WITH_ARG;
	param.a1 = funcid;
	param.a2 = start_addr;
	param.a3 = lenth;
	tee_smc_call(&param);
	return &param;
}
