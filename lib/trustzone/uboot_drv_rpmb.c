/*
 * Copyright (c) 2013-2014, spreadtrum.com.
 *
 */

#include "uboot_sec_drv.h"
#include <mmc.h>
#include <sprd_rpmb.h>

u64 rpmb_size __attribute__((aligned(4096)));
int is_rpmb_key __attribute__((aligned(4096)));
u64 rpmb_data_blocks __attribute__((aligned(4096)));

int uboot_set_rpmb_size(void)
{
    rpmb_size = emmc_get_capacity(PARTITION_RPMB);
    printf("%s: rpmb size %lld\n", __func__, rpmb_size);
    smc_param *param = tee_common_call(FUNCTYPE_SET_RPMB_SIZE, (uint32_t)(&rpmb_size), sizeof(rpmb_size));

    return param->a0;
}


int uboot_is_wr_rpmb_key(void)
{
    is_rpmb_key = -1;
    is_rpmb_key = is_wr_rpmb_key();
    if (0 == is_rpmb_key) {
        printf("%s rpmb unwritten, call tos \n", __func__);
        smc_param *param = tee_common_call(FUNCTYPE_IS_WR_RPMB_KEY, (uint32_t)(&is_rpmb_key), sizeof(is_rpmb_key));
        return param->a0;
    } else {
        return -1;
    }
}

uint8_t __weak rpmb_get_wr_cnt(void)
{
    return 1;
}

int  uboot_set_rpmb_data_blocks(void)
{
    uint8_t rpmb_sec_cnt = 0;

    rpmb_sec_cnt = rpmb_get_wr_cnt();
    rpmb_data_blocks = rpmb_sec_cnt;
    printf("%s: rpmb data blocks %lld\n", __func__, rpmb_data_blocks);
    smc_param *param = tee_common_call(FUNCTYPE_SET_RPMB_DATA_BLOCKS, (uint32_t)(&rpmb_data_blocks), sizeof(rpmb_data_blocks));

    return param->a0;
}
