#ifndef DL_CMD_PROC_H
#define DL_CMD_PROC_H
#include "packet.h"

#define PARTITION_SIZE_LENGTH          (4)
#define MAX_PARTITION_NAME_SIZE   (36)
#define GAP_SIZE_LENGTH   (8)
#define PARTITION_SIZE_LENGTH_V1  (8)
#define REPARTITION_HEADER_MAGIC 0x3A726170
#define BIT64_DATA_LENGTH 0x58
#define BIT64_READ_MIDST_LENGTH 0x0C
#define DATA_CHECKSUM_LENGTH 0x50

#define REPARTITION_UNIT_LENGTH    (MAX_PARTITION_NAME_SIZE *2 + PARTITION_SIZE_LENGTH)
#define REPARTITION_UNIT_LENGTH_V1    (MAX_PARTITION_NAME_SIZE *2 +  PARTITION_SIZE_LENGTH_V1 + GAP_SIZE_LENGTH)
#define REF_INFO_OFF 0XFA000

typedef enum OPERATE_STATUS {
	OPERATE_SUCCESS = 1,
	OPERATE_SYSTEM_ERROR,
	OPERATE_DEVICE_INIT_ERROR,
	OPERATE_INVALID_DEVICE_SIZE,
	OPERATE_INCOMPATIBLE_PART,
	OPERATE_INVALID_ADDR,
	OPERATE_INVALID_SIZE,
	OPERATE_WRITE_ERROR,
	OPERATE_CHECKSUM_DIFF,
	OPERATE_IGNORE
} OPERATE_STATUS;

typedef struct _REPARTITION_TABLE_INFO
{
	unsigned char version;
	unsigned char unit;
	unsigned char table_count;
	unsigned char reserved;
	unsigned int     table_tag;
	unsigned short     table_offset;
	unsigned short     table_size;
} REPARTITION_TABLE_INFO;


int dl_cmd_write_start(dl_packet_t * packet, void *arg);
int dl_cmd_write_midst(dl_packet_t * packet, void *arg);
int dl_cmd_write_end(dl_packet_t * packet, void *arg);
int dl_cmd_read_start(dl_packet_t * packet, void *arg);
int dl_cmd_read_midst(dl_packet_t * packet, void *arg);
int dl_cmd_read_end(dl_packet_t * packet, void *arg);
int dl_cmd_erase(dl_packet_t * packet, void *arg);
int dl_cmd_repartition(dl_packet_t * pakcet, void *arg);
int dl_cmd_reboot (dl_packet_t *pakcet, void *arg);
int dl_powerdown_device(dl_packet_t *packet, void *arg);
int dl_cmd_read_mcptype(dl_packet_t * packet, void *arg);
int dl_cmd_check_rootflag(dl_packet_t * packet, void *arg);
int dl_cmd_get_uid(dl_packet_t *packet, void *arg);
int dl_cmd_get_chip_uid(dl_packet_t *packet, void *arg);
int dl_cmd_get_uid_x86(dl_packet_t *packet, void *arg);
int dl_cmd_end_process(dl_packet_t *packet, void *arg);
int dl_cmd_read_ref_info(dl_packet_t *packet, void *arg);
int dl_cmd_disable_hdlc(dl_packet_t *packet, void *arg);
int dl_cmd_write_datetime(dl_packet_t *packet, void *arg);
#endif /*DL_CMD_PROC_H */
