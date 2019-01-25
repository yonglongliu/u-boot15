#include <common.h>
#include <malloc.h>
#include <part.h>
#include <sprd_common_rw.h>
#include <ext4fs.h>

#ifdef CONFIG_CMD_UBI
#include <ubi_uboot.h>
#endif
#ifdef  CONFIG_EMMC_BOOT
#include <mmc.h>
#endif
#ifdef CONFIG_UFS_BOOT
#include <sprd_ufs.h>
#endif
#ifdef  CONFIG_NAND_BOOT
#include <jffs2/load_kernel.h>
#include <linux/mtd/partitions.h>
#include <nand.h>
#include <dl_ubi.h>
#endif
static disk_partition_t local_part_info;

int block_dev_read(block_dev_desc_t *dev_desc, uint64_t size, uint64_t offset, char *buf)
{
	lbaint_t start = 0;
	lbaint_t blkcnt = 0;
	char * temp = NULL;
	uint64_t header_sz = 0;
	uint64_t offb = 0;

	if ((0 != size % dev_desc->blksz) || (0 != offset % dev_desc->blksz)) {
		temp = malloc(dev_desc->blksz);
		if (NULL == temp)
			goto fail;
	}

	start = offset / dev_desc->blksz;
	offb = offset % dev_desc->blksz;
	if (0 != offb) {
		header_sz = dev_desc->blksz - offb;
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read start block 0x%x fail\n", start);
			goto fail;
		}
		if (size <= header_sz) {
			memcpy(buf, temp + offb, size);
			size = 0;
		} else {
			memcpy(buf, temp + offb, header_sz);
			start++;
			buf += header_sz;
			size -= header_sz;
		}
	}

	blkcnt = size / dev_desc->blksz;
	if (blkcnt > 0) {
		if (blkcnt != dev_desc->block_read(dev_desc->dev, start, blkcnt, buf)) {
			errorf("read block 0x%x size 0x%x fail\n", start, blkcnt);
			goto fail;
		}
		start += blkcnt;
		buf += (blkcnt * dev_desc->blksz);
		size = size % dev_desc->blksz;
	}

	if (size > 0) {
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read end block 0x%x fail\n", start);
			goto fail;
		}
		memcpy(buf, temp, size);
	}

	if (NULL != temp)
		free(temp);
	return 0;

fail:
	if (NULL != temp)
		free(temp);
	return -1;
}


int block_dev_write(block_dev_desc_t *dev_desc, uint64_t size, uint64_t offset, char *buf)
{
	lbaint_t start = 0;
	lbaint_t blkcnt = 0;
	char * temp = NULL;
	uint64_t header_sz = 0;
	uint64_t offb = 0;

	if ((0 != size % dev_desc->blksz) || (0 != offset % dev_desc->blksz)) {
		temp = malloc(dev_desc->blksz);
		if (NULL == temp)
			goto fail;
	}

	start = offset / dev_desc->blksz;
	offb = offset % dev_desc->blksz;
	if (0 != offb) {
		header_sz = dev_desc->blksz - offb;
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read start block 0x%x for write fail\n", start);
			goto fail;
		}
		if (size <= header_sz) {
			memcpy(temp + offb, buf, size);
			size = 0;
		} else {
			memcpy(temp + offb, buf, header_sz);
			buf += header_sz;
			size -= header_sz;
		}
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("write start block 0x%x fail\n", start);
			goto fail;
		}
		start++;
	}

	blkcnt = size / dev_desc->blksz;

	if (blkcnt > 0) {
		if (blkcnt != dev_desc->block_write(dev_desc->dev, start, blkcnt, buf)) {
			errorf("write block 0x%x size 0x%x fail\n", start, blkcnt);
			goto fail;
		}
		start += blkcnt;
		buf += (blkcnt * dev_desc->blksz);
		size = size % dev_desc->blksz;
	}

	if (size > 0) {
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read end block 0x%x for write fail\n", start);
			goto fail;
		}
		memcpy(temp, buf, size);
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("write end block 0x%x fail\n", start);
			goto fail;
		}
	}

	if (NULL != temp)
		free(temp);
	return 0;

fail:
	if (NULL != temp)
		free(temp);
	return -1;
}

int block_dev_erase(block_dev_desc_t *dev_desc, uint64_t size, uint64_t offset)
{
	lbaint_t start = 0;
	lbaint_t blkcnt = 0;
	char * temp = NULL;
	uint64_t header_sz = 0;
	uint64_t offb = 0;

	if ((0 != size % dev_desc->blksz) || (0 != offset % dev_desc->blksz)) {
		temp = malloc(dev_desc->blksz);
		if (NULL == temp)
			goto fail;
	}

	start = offset / dev_desc->blksz;
	offb = offset % dev_desc->blksz;
	if (0 != offb) {
		header_sz = dev_desc->blksz - offb;
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read start block 0x%x for erase fail\n", start);
			goto fail;
		}
		if (size <= header_sz) {
			memset(temp + offb, 0, size);
			size = 0;
		} else {
			memset(temp + offb, 0, header_sz);
			size -= header_sz;
		}
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("erase start block 0x%x fail\n", start);
			goto fail;
		}
		start++;
	}

	blkcnt = size / dev_desc->blksz;
	if (blkcnt > 0) {
		if (blkcnt != dev_desc->block_erase(dev_desc->dev, start, blkcnt)) {
			errorf("erase block 0x%x size 0x%x fail\n", start, blkcnt);
			goto fail;
		}
		start += blkcnt;
		size = size % dev_desc->blksz;
	}

	if (size > 0) {
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read end block 0x%x for erase fail\n", start);
			goto fail;
		}
		memset(temp, 0, size);
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("erase end block 0x%x fail\n", start);
			goto fail;
		}
	}

	if (NULL != temp)
		free(temp);
	return 0;

fail:
	if (NULL != temp)
		free(temp);
	return -1;
}


#ifdef CONFIG_UFS_BOOT

struct lu_specific_cfg_tbl factory_lu_tbl[] = {
	/*lu_index, bootable,               log2blksz,  blkcnt,  lu_context, memory_type*/
	{0x00,              MAIN_BOOT, 		    0x0C, 		1024,    	0x0,			ENHANCED_MEMORY_1},
	{0x01,              ALTERNATE_BOOT, 0x0C, 		1024,    	0x0,			ENHANCED_MEMORY_1},
	{0x02,              NONE_BOOT, 	    0x0C, 		0        ,    	0xFF,		NORMAL_MEMORY},
	{0	  ,              0		       ,              0	     ,            0	 ,       0       ,		0}
};

struct lu_common_cfg_tbl lu_common_tbl = {
	/*write_protect, 		      provisioning_type,              data_reliability*/
	WRITE_PROTECT_POWERON,  PROV_ENABLE_WITH_TPRZ, DATA_PROTECTED
};


int get_lun_by_bootable(enum lu_bootable target)
{
	int id = 0;
	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (0 == factory_lu_tbl[id].log2blksz)
			break;
		/*TODO, only support single user lu now*/
		if (factory_lu_tbl[id].bootable == target)
			return factory_lu_tbl[id].lu_index;
	}
	return -1;
}

int get_user_lun(disk_partition_t *part_info, char *part_name)
{
	int id = 0;
	int ret = 0;
	block_dev_desc_t *dev_desc;

	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (0 == factory_lu_tbl[id].log2blksz)
			break;
		if (factory_lu_tbl[id].bootable == NONE_BOOT) {
			dev_desc = get_dev("ufs", factory_lu_tbl[id].lu_index);
			if (NULL == dev_desc)
				continue;
			ret = get_partition_info_by_name(dev_desc, part_name, part_info);
			if (0 == ret)
				return factory_lu_tbl[id].lu_index;
		}
	}

	return -1;

}


int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf)
{
	int dev_id = 0;
	uint64_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_lun_by_bootable(MAIN_BOOT);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_lun_by_bootable(ALTERNATE_BOOT);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_user_lun(&part_info, part_name);
		if (-1 == dev_id) {
			dev_id = get_lun_by_bootable(ALTERNATE_BOOT);
		} else {
			part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size) {
				errorf("uboot read size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
				return -1;
			}
		}
	} else {
		dev_id = get_user_lun(&part_info, part_name);
		part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("read size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			return -1;
		}
	}

	if (-1 == dev_id)
		return -1;

	dev_desc = get_dev("ufs", dev_id);
	if (NULL == dev_desc)
		return -1;
	/*TODO, can not support spl and uboot whole partition reading*/
	if (0 == size)
		size = total_part_size;

	offset += part_start;

	debugf("UFS read in byte, size=0x%llx, offset=0x%llx\n", size, offset);
	return block_dev_read(dev_desc, size, offset, buf);

}


int common_raw_write(char *part_name, uint64_t size, uint64_t updsize, uint64_t offset, char *buf)
{
	int dev_id = 0;
	uint64_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_lun_by_bootable(MAIN_BOOT);
	} else if(0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_lun_by_bootable(ALTERNATE_BOOT);
	} else if(0 == strcmp(part_name, "uboot")) {
		dev_id = get_user_lun(&part_info, part_name);
		if (-1 == dev_id) {
			dev_id = get_lun_by_bootable(ALTERNATE_BOOT);
		} else {
			part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size) {
				errorf("uboot write size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
				return -1;
			}
		}
	} else {
		dev_id = get_user_lun(&part_info, part_name);
		part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("write size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			return -1;
		}
	}

	if (-1 == dev_id)
		return -1;

	dev_desc = get_dev("ufs", dev_id);
	if (NULL == dev_desc)
		return -1;

	offset += part_start;

	return block_dev_write(dev_desc, size, offset, buf);

}


int common_raw_erase(char *part_name, uint64_t size, uint64_t offset)
{
	int dev_id = 0;
	lbaint_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	ulong ret = 0;
	int type = NONE_BOOT;
	if (0 == strcmp(part_name, "erase_all")) {
		debugf("erase all the flash\n");
		for (type = NONE_BOOT; type <= ALTERNATE_BOOT; type++) {
			dev_id = get_lun_by_bootable(type);
			if (-1 == dev_id)
				return -1;
			dev_desc = get_dev("ufs", dev_id);
			if (NULL == dev_desc)
				return -1;
			ret = dev_desc->block_erase(dev_desc->dev, 0, dev_desc->lba);
			if (ret != dev_desc->lba)
				return -1;
		}
		return 0;
	}

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_lun_by_bootable(MAIN_BOOT);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_lun_by_bootable(ALTERNATE_BOOT);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_user_lun(&part_info, part_name);
		if (-1 == dev_id) {
			dev_id = get_lun_by_bootable(ALTERNATE_BOOT);
		} else {
			part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size) {
				errorf("uboot erase size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
				return -1;
			}
		}
	} else {
		dev_id = get_user_lun(&part_info, part_name);
		part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("erase size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			return -1;
		}
	}

	if (-1 == dev_id)
		return -1;

	dev_desc = get_dev("ufs", dev_id);
	if (NULL == dev_desc)
		return -1;

	if (0 == size)
		size = total_part_size;

	offset += (uint64_t)part_start;

	return block_dev_erase(dev_desc, size, offset);

}

int common_write_backstage(char *part_name, uint32_t size, uint64_t offset, char *buf)
{
	static int dev_id = 0;
	lbaint_t start = 0;
	lbaint_t blk_num = 0;
	uint64_t total_part_size = 0;
	block_dev_desc_t *dev_desc = NULL;
	int ret = 0;
	if (0 != strcmp(part_name, local_part_info.name))
		dev_id = get_user_lun(&local_part_info, part_name);

	/*invoker must guarantee that the size and offset aligned to the block size*/
	if (0 != size % local_part_info.blksz || 0 != offset % local_part_info.blksz) {
		errorf("input size or offset not aligned, size(0x%x), offset(0x%x)\n", size, offset);
		return -1;
	}

	if (0 != (ulong)buf % 4) {
		errorf("input buffer must aligned to 4! buffer(0x%lx)\n", (ulong)buf);
		return -1;
	}

	blk_num = size / local_part_info.blksz;
	start = local_part_info.start + (offset / local_part_info.blksz);
	if (blk_num + start > local_part_info.size + local_part_info.start) {
		errorf("backstage write size overflow the total partition size\n");
		return -1;
	}

	/*only none boot lun support backstage write*/
	if (blk_num != ufs_write_backstage(dev_id, start, blk_num, buf))
		return -1;

	return 0;
}

int common_query_backstage(char *part_name, uint32_t size, char *buf)
{
	lbaint_t blk_num = 0;
	if (0 != strcmp(part_name, local_part_info.name))
		return -1;
	blk_num = size / local_part_info.blksz;
	if (blk_num != ufs_query_backstage(blk_num))
		return -1;

	return 0;
}

int common_repartition(disk_partition_t *partitions, int parts_count)
{
	int dev_id = 0;
	block_dev_desc_t *dev_desc;
	int counter = 0;
	int ret = 0;

	ret = ufs_lu_reconstruct(factory_lu_tbl, &lu_common_tbl);
	if (UFS_SUCCESS != ret)
		return -1;

	/*future extention, now we only have one none boot lu*/
	dev_id = get_lun_by_bootable(NONE_BOOT);
	if (-1 == dev_id)
		return -1;

	dev_desc = get_dev("ufs", dev_id);
	if (NULL == dev_desc)
		return -1;

	while (counter < 3) {
		ret = gpt_restore(dev_desc, SPRD_DISK_GUID_STR, partitions, parts_count);
		if (0 == ret)
			break;
		counter++;
	}

	if (3 == counter) {
		return -1;
	} else {
		init_part(dev_desc);
		return 0;
	}
}

int32_t common_get_lba_size(void)
{
	int id = 0;
	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (0 == factory_lu_tbl[id].log2blksz)
			break;
		if (NONE_BOOT == factory_lu_tbl[id].bootable)
			return (1 << factory_lu_tbl[id].log2blksz);
	}
	errorf("No NONE_BOOT LU in factory lu table, can not get lba size\n");
	return -1;
}

int do_fs_file_read(char *mpart, char *filenm, void *buf, int len)
{
#ifdef CONFIG_FS_EXT4
	static int dev_id = 0;
	disk_partition_t info;
	block_dev_desc_t *dev_desc;
	loff_t len_read = 0;

	dev_id = get_user_lun(&info, mpart);

	dev_desc = get_dev("ufs", dev_id);
	if (NULL == dev_desc) {
		errorf("ext4_read_content get dev error\n");
		return -1;
	}

	/* set the device as block device */
	ext4fs_set_blk_dev(dev_desc, &info);

	/* mount the filesystem */
	if (!ext4fs_mount(info.size)) {
		errorf("Bad ext4 partition:%s\n",  mpart);
		ext4fs_close();
		return -1;
	}

	/* start read */
	if (ext4_read_file(filenm, buf, 0, len, &len_read) == -1) {
		errorf("** Error ext4_read_file() **\n");
		ext4fs_close();
		return -1;
	}
	debugf("read %s ok, len : 0x%llx", filenm, len_read);
	ext4fs_close();
	return 0;
#else
	return -1;
#endif

}

int do_fs_file_write(char *mpart, char *filenm, void *buf, int len)
{
	/*do not write in uboot now*/
	return -1;
}


#endif

#ifdef CONFIG_EMMC_BOOT
int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf)
{
	uint64_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	int ret = 0;

	if (0 == strcmp(part_name, "splloader")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			ret = 0;
			dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
		} else {
			part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size) {
				errorf("uboot read size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
				ret = -1;
			}
		}
	} else {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("read size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			ret = -1;
		}
	}

	if (-1 == ret || NULL == dev_desc)
		return -1;

	if (0 == size)
		size = total_part_size;

	offset += part_start;

	return block_dev_read(dev_desc, size, offset, buf);

}


int common_raw_write(char *part_name, uint64_t size, uint64_t updsize, uint64_t offset, char *buf)
{
	uint64_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	int ret = 0;

	if (0 == strcmp(part_name, "splloader")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			debugf("no uboot partition in user hardwarepart, write to boot2\n");
			dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
			ret = 0;
		} else {
			part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size)
				ret = -1;
		}
	} else {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("write size(0x%llx) + offset(0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			ret = -1;
		}
	}

	if (-1 == ret || NULL == dev_desc)
		return -1;

	offset += part_start;

	return block_dev_write(dev_desc, size, offset, buf);

}

int common_raw_erase(char *part_name, uint64_t size, uint64_t offset)
{
	uint64_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	int ret = 0;

	if (0 == strcmp(part_name, "erase_all")) {
		debugf("erase all the flash\n");
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT1);
		total_part_size = emmc_get_capacity(PARTITION_BOOT1);
		if (NULL == dev_desc || 0 == total_part_size)
			return -1;
		if (0 != block_dev_erase(dev_desc, total_part_size, 0))
			return -1;

		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
		total_part_size = emmc_get_capacity(PARTITION_BOOT2);
		if (NULL == dev_desc || 0 == total_part_size)
			return -1;
		if (0 != block_dev_erase(dev_desc, total_part_size, 0))
			return -1;

		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		total_part_size = emmc_get_capacity(PARTITION_USER);
		if (NULL == dev_desc || 0 == total_part_size)
			return -1;
		if (0 != block_dev_erase(dev_desc, total_part_size, 0))
			return -1;
		return 0;
	}

	if (0 == strcmp(part_name, "splloader")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT1);
		total_part_size = emmc_get_capacity(PARTITION_BOOT1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
		total_part_size = emmc_get_capacity(PARTITION_BOOT2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			ret = 0;
			dev_desc = get_dev_hwpart("mmc", 0, PARTITION_BOOT2);
			total_part_size = emmc_get_capacity(PARTITION_BOOT2);
		} else {
			part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		}
	} else {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
	}

	if (-1 == ret || NULL == dev_desc || 0 == total_part_size)
		return -1;

	if (0 == size) {
		size = total_part_size;
		offset = part_start;
	} else if (size + offset > total_part_size) {
		return -1;
	} else {
		offset += part_start;
	}

	if(block_dev_erase(dev_desc, size, offset))
		return -1;
		
	if (0 == strcmp(part_name, "uboot")) {
		uchar buf[512] = { 0x5A };
		printf("Use Write 5A pattern to uboot partition for check download status\n");
		 if (common_raw_write(part_name,(uint64_t)1, (uint64_t)0, (uint64_t)0, buf))
			return -1;
	}
	return 0;
}

int common_write_backstage(char *part_name, uint32_t size, uint64_t offset, char *buf)
{
	lbaint_t start = 0;
	lbaint_t blk_num = 0;
	uint64_t total_part_size = 0;
	block_dev_desc_t *dev_desc = NULL;
	int ret = 0;
	if (0 != strcmp(part_name, local_part_info.name)) {
		dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
		ret = get_partition_info_by_name(dev_desc, part_name, &local_part_info);
	}

	/*invoker must guarantee that the size and offset aligned to the block size*/
	if (0 != size % local_part_info.blksz || 0 != offset % local_part_info.blksz) {
		errorf("input size or offset not aligned, size(0x%x), offset(0x%x)\n", size, offset);
		ret = -1;
	}

	blk_num = size / local_part_info.blksz;
	start = local_part_info.start + (offset / local_part_info.blksz);
	if (blk_num + start > local_part_info.size + local_part_info.start) {
		errorf("backstage write size overflow the total partition size\n");
		ret = -1;
	}

	if (-1 == ret)
		return -1;

	/*only user partition can use backstage write*/
	if (blk_num != emmc_write_backstage(PARTITION_USER, start, blk_num, buf))
		return -1;

	return 0;
}


int common_query_backstage(char *part_name, uint32_t size, char *buf)
{
	lbaint_t blk_num = 0;
	if (0 != strcmp(part_name, local_part_info.name))
		return -1;
	blk_num = size / local_part_info.blksz;
	if (blk_num != emmc_query_backstage(PARTITION_USER, blk_num, buf))
		return -1;

	return 0;
}


int common_repartition(disk_partition_t *partitions, int parts_count)
{
	block_dev_desc_t *dev_desc;
	int counter = 0;
	int ret = 0;

	memset(&local_part_info, 0 , sizeof(disk_partition_t));
	dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
	if (NULL == dev_desc) {
		errorf("get mmc device hardware part(%d) fail\n", PARTITION_USER);
		return -1;
	}

	while (counter < 3) {
		ret = gpt_restore(dev_desc, SPRD_DISK_GUID_STR, partitions, parts_count);
		if (0 == ret)
			break;
		counter++;
	}

	if (3 == counter) {
		return -1;
	} else {
		init_part(dev_desc);
		return 0;
	}
}

int32_t common_get_lba_size(void)
{
	block_dev_desc_t *dev_desc;

	dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
	if (NULL == dev_desc)
		return -1;

	return (int32_t)dev_desc->blksz;
}

int do_fs_file_read(char *mpart, char *filenm, void *buf, int len)
{
#ifdef CONFIG_FS_EXT4
	disk_partition_t info;
	block_dev_desc_t *dev_desc;
	loff_t len_read = 0;

	dev_desc = get_dev("mmc", 0);
	if (NULL == dev_desc) {
		errorf("ext4_read_content get dev error\n");
		return -1;
	}

	if (get_partition_info_by_name(dev_desc, mpart, &info) == -1) {
		errorf("## Valid EFI partition not found ##\n");
		return -1;
	}

	/* set the device as block device */
	ext4fs_set_blk_dev(dev_desc, &info);

	/* mount the filesystem */
	if (!ext4fs_mount(info.size)) {
		errorf("Bad ext4 partition:%s\n",  mpart);
		ext4fs_close();
		return -1;
	}

	/* start read */
	if (ext4_read_file(filenm, buf, 0, len, &len_read) == -1) {
		ext4fs_close();
		return -1;
	}
	debugf("read %s ok, len : 0x%llx", filenm, len_read);
	ext4fs_close();
	return 0;
#else
	return -1;
#endif
}

int do_fs_file_write(char *mpart, char *filenm, void *buf, int len)
{
	/*do not write in uboot now*/
	return -1;
}

#endif



#ifdef CONFIG_NAND_BOOT
extern int ubifs_init(void);
extern struct ubi_selected_dev cur_ubi;

int uboot_ubi_read(struct ubi_volume_desc *desc, char *buf,
			   int offset, int size)
{
	int err, lnum, off, len, tbuf_size, i = 0;
	size_t count_save = size;
	void *tbuf;
	unsigned long long tmp;
	struct ubi_volume *vol = NULL;
	struct ubi_device *ubi = NULL;
	loff_t offp = offset;

	vol = desc->vol;
	ubi = desc->vol->ubi;

	//printf("read %i bytes from volume %d to %x(buf address)\n",
	       //(int) size, vol->vol_id, (unsigned)buf);

	if (vol->updating) {
		printf("updating");
		return -EBUSY;
	}
	if (vol->upd_marker) {
		printf("damaged volume, update marker is set");
		return -EBADF;
	}
	if (offp == vol->used_bytes)
		return 0;

	if (size == 0) {
		printf("Read [%lu] bytes\n", (unsigned long) vol->used_bytes);
		size = vol->used_bytes;
	}

	if (vol->corrupted)
		printf("read from corrupted volume %d", vol->vol_id);
	if (offp + size > vol->used_bytes)
		count_save = size = vol->used_bytes - offp;

	tbuf_size = vol->usable_leb_size;
	if (size < tbuf_size)
		tbuf_size = ALIGN(size, ubi->min_io_size);
	tbuf = malloc(tbuf_size);
	if (!tbuf) {
		printf("NO MEM\n");
		return -ENOMEM;
	}
	len = size > tbuf_size ? tbuf_size : size;

	tmp = offp;
	off = do_div(tmp, vol->usable_leb_size);
	lnum = tmp;
	do {
		if (off + len >= vol->usable_leb_size)
			len = vol->usable_leb_size - off;
		err = ubi_eba_read_leb(ubi, vol, lnum, tbuf, off, len, 0);
		if (err) {
			printf("read err %x\n", err);
			break;
		}
		off += len;
		if (off == vol->usable_leb_size) {
			lnum += 1;
			off -= vol->usable_leb_size;
		}

		size -= len;
		offp += len;

		memcpy(buf, tbuf, len);

		buf += len;
		len = size > tbuf_size ? tbuf_size : size;
	} while (size);
	free(tbuf);
	return err ? err : count_save - size;
}

static int _boot_ubi_attach_mtd(const char *mtdpart)
{
	struct mtd_device *dev;
	struct part_info *part;
	struct mtd_info *mtd;
	struct mtd_partition mtd_part;
	char mtd_dev[16];
	u8 pnum;
	int ret;

	ret = find_dev_and_part(mtdpart, &dev, &pnum, &part);
	if(ret){
		printf("--->main partition %s miss<---\n",mtdpart);
		return -1;
	}
	if(dev->id->type != MTD_DEV_TYPE_NAND){
		printf("mtd dev %s not a nand device!\n",mtdpart);
		return -1;
	}
	sprintf(mtd_dev, "%s%d", MTD_DEV_TYPE(dev->id->type), dev->id->num);
	mtd = get_mtd_device_nm(mtd_dev);

	memset(&mtd_part, 0, sizeof(mtd_part));
	mtd_part.name = mtdpart;
	mtd_part.size = part->size;
	mtd_part.offset = part->offset;
	add_mtd_partitions(mtd, &mtd_part, 1);
	mtd = get_mtd_device_nm(mtdpart);
	ret = ubi_attach_mtd_dev(mtd, UBI_DEV_NUM_AUTO, 0,CONFIG_MTD_UBI_BEB_LIMIT);
	if(ret<0){
		printf("--->ubi attach mtd %s failed<---\n",mtdpart);
	}
	return ret;
}


int nand_ubi_dev_init(void)
{
	int ret;
	static int initialized=0;
	static int dev_num=-1;

	if(!initialized){
		//init mtd & ubi devices
		ret = mtdparts_init();
		if(ret){
			printf("mtdparts init error...\n");
			return -1;
		}
		printf("ubi init start\n");
		ret = ubi_init();
		if(ret){
			printf("ubi init error...\n");
			return -1;
		}
		//ubi attach mtd dev, and get the new ubi dev num
		dev_num = _boot_ubi_attach_mtd(UBIPAC_PART);
		initialized = 1;
	}

	return dev_num;
}


int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf)
{
	int ubi_dev_num;
	struct ubi_volume_desc *vol;
	ubi_dev_num = nand_ubi_dev_init();
	if(ubi_dev_num < 0){
		//dev num can't be a negative
		printf("read failed...\n");
		return;
	}
	vol = ubi_open_volume_nm(ubi_dev_num, part_name, UBI_READONLY);
	if (IS_ERR(vol)){
		printf("cannot open \"%s\", error %d", part_name, (int)PTR_ERR(vol));
		return -1;
	}
	uboot_ubi_read(vol, buf, offset, size);

	return 0;
}


int common_raw_write(char *part_name, uint64_t size, uint64_t updsize, uint64_t offset, char *buf)
{
#if 0
	nand_info_t *nand;
	int ret;
	dl_part_type part_type = PART_TYPE_MIN;
	struct mtd_partition mtd_part;
	ubi_volume_desc *vol;

	nand = _get_cur_nand();
	if (strcmp(part_name, "splloader") == 0) {
		ret = sprd_nand_write_spl(buf, nand);
		return ret;
	} else {
	ret = _get_mtd_partition_info(part_name, &mtd_part);
		if (ret) {
		part_type = PART_TYPE_MTD;
		}
	} else {
	vol = ubi_open_volume_nm(cur_ubi.dev_num, part_name, UBI_READWRITE);
		if (0 != IS_ERR(vol)) {
		part_type = PART_TYPE_UBI;
		}
	}

	switch (part_type) {
	case PART_TYPE_MTD:
		ret = nand_write_skip_bad(nand, offset, &size, NULL, mtd_part.size, buf, 0);
		if (ret) {
			/*mark a block as badblock */
			printf("nand write error %d, mark bad block 0x%llx\n", ret, mtd_part.offset & ~(nand->erasesize - 1));
			nand->_block_markbad(nand, mtd_part.offset & ~(nand->erasesize - 1));
			return ret;
		}
		break;
	case PART_TYPE_UBI:
		ret = fdl_ubi_volume_write(cur_ubi.dev, part_name, buf, size);
		if (ret) {
			printf("ubi volume write error %d!\n", ret);
			return ret;
		}
		break;
	default:
		debugf("part type error!\n");
		return -1;
	}
	return 0;
#endif
}

int common_raw_erase(char *part_name, uint64_t size, uint64_t offset)
{
	
}



int common_repartition(disk_partition_t *partitions, int parts_count)
{
	
}

int32_t common_get_lba_size(void)
{
	
}

int do_fs_file_read(char *mpart, char *filenm, void *buf, int len)
{
#if 1

	int ret=-1;
	static int is_ubifs_init = 0;
	if(is_ubifs_init == 0){
		ubifs_init();
		is_ubifs_init = 1;
	}


	ret = uboot_ubifs_mount(mpart);
	if(ret){
		printf("do_fs_file_read:mount %s failed!\n",mpart);
		return ret;
	}
	ret = ubifs_load(filenm, buf, len);
	if(ret)
		printf("do_fs_file_read:file %s not found!\n", filenm);
	return ret;
	#endif
}
int do_fs_file_write(char *mpart, char *filenm, void *buf, int len)
{
	/*do not write in uboot now*/
	return -1;
}





int do_raw_data_write(char *part, u32 updsz, u32 size, u32 off, char *buf)
{
	int ret =-1;
	int i =0;
	int ubi_dev;
	u8 pnum;
	loff_t offset;
	size_t length,wlen=0;
	struct mtd_device *dev;
	struct mtd_info *nand;
	struct part_info *mtdpart;
	struct ubi_volume_desc *vol;
	nand_erase_options_t opts;

try_mtd:
	ret = find_dev_and_part(part, &dev, &pnum, &mtdpart);
	if (ret)
		goto try_ubi;
	else if (dev->id->type != MTD_DEV_TYPE_NAND)
		goto end;

	offset = mtdpart->offset+off;
	length = size;
	nand = &nand_info[dev->id->num];
	memset(&opts, 0x0, sizeof(opts));
	opts.offset = offset;
	opts.length = length;
	opts.quiet = 1;
	opts.spread = 1;

	ret = nand_erase_opts(nand, &opts);
	if (ret) {
		printf("erase %s failed.\n",part);
		goto end;
	}
	//write spl part with header
	if(strcmp(part, "splloader")==0){
		ret = sprd_nand_write_spl(buf, nand);
		goto end;
	}

	while((size != wlen) && (i++<0xff)) {
		ret = nand_write_skip_bad(nand, offset, &length, NULL, mtdpart->size, buf, 0);
		wlen += length;
		buf += length;
		offset += length;

		if(ret){
			//mark a block as badblock
			printf("nand write error %d, mark bad block 0x%llx\n",ret,offset&~(nand->erasesize-1));
			nand->_block_markbad(nand,offset &~(nand->erasesize-1));
		}
	}
	goto end;

try_ubi:
	ubi_dev = nand_ubi_dev_init();
	if (ubi_dev<0) {
		printf("do_raw_data_write: ubi init failed.\n");
		return ret;
	}
	vol = ubi_open_volume_nm(ubi_dev, part, UBI_READWRITE);
	if (IS_ERR(vol)) {
		printf("cannot open \"%s\", error %d",
			  part, (int)PTR_ERR(vol));
		return ret;
	}

	//set total size to be updated in this volume
	if (updsz) {
		ret = ubi_start_update(vol->vol->ubi, vol->vol, updsz);
		if (ret < 0) {
			printf("Cannot start volume %s update\n",part);
			return ret;
		}
	}

	ret = ubi_more_update_data(vol->vol->ubi, vol->vol, buf, size);
	if (ret < 0) {
		printf("Couldnt write data in volume %s\n",part);
		return ret;
	}
	ret = 0;
	ubi_close_volume(vol);

end:
	if (ret)
		printf("do_raw_data_write error.\n");
	return ret;
}

#endif


