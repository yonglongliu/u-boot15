/*
 * Copyright (C) 2017 spreadtrum.com
 *
 */
 #ifndef _SPRD_RPMB_H
 #define _SPRD_RPMB_H

/*
blk_data: for save read data;
blk_index: the block index for read;
block_count: the read count;
success return 0 ;
*/
uint8_t rpmb_blk_read(char *blk_data, uint16_t blk_index, uint8_t block_count);

 /**@retrun 0 rpmb key unwritten*/
int is_wr_rpmb_key(void);
uint8_t rpmb_get_wr_cnt(void);

#endif // _SPRD_RPMB_H
