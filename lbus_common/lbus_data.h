#ifndef _LBUS_DATA_H_
#define _LBUS_DATA_H_
#include <stdint.h>

#define __packed __attribute__ ((packed))

#define PAGE_SIZE 1024

enum lbus_cmd {
	NOP = 0, // reserved
	PING,
	GET_DATA,
	SET_GROUPS,
	LED_SET_16BIT = 10,
	LED_COMMIT,
	RESET_TO_BOOTLOADER = 122,
	ERASE_CONFIG,
	SET_ADDRESS,
	READ_MEMORY,
	FLASH_FIRMWARE,
	RESET_TO_FIRMWARE
};

enum lbus_state {
	LBUS_STATE_IN_BOOTLOADER = 1,
	LBUS_STATE_IN_FIRMWARE = 2
};

enum lbus_data {
	LBUS_DATA_STATUS = 1,
	LBUS_DATA_ADDRESS,
	LBUS_DATA_FIRMWARE_VERSION,
	LBUS_DATA_BOOTLOADER_VERSION,
	LBUS_DATA_FIRMWARE_NAME_LENGTH,
	LBUS_DATA_FIRMWARE_NAME
};

struct lbus_hdr {
	// always send a packet length so controllers can skip
	// unknown commands
	uint16_t length;
	uint8_t addr;
	uint8_t cmd;
} __packed;

struct lbus_GET_DATA {
	uint16_t type;
} __packed;

struct lbus_LED_SET_16BIT {
	uint16_t led;
	uint16_t color[];
} __packed;

struct lbus_SET_ADDRESS {
	uint8_t naddr;
} __packed;

struct lbus_READ_MEMORY {
	uint32_t address;
} __packed;

struct lbus_FLASH_FIRMWARE {
	uint16_t page_id;
	uint8_t data[PAGE_SIZE];
	uint32_t crc;
} __packed;

#endif
