/*
 * Configuration file for the POD-G3 Board.
 *
 * Copyright (C) 2017 Ray Allen Manufacturing LLC
 *		      Peter Taylor <ptaylor@rayallen.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "at91-sama5_common.h"

#define CONFIG_MISC_INIT_R

/* SDRAM */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE           ATMEL_BASE_DDRCS
#define CONFIG_SYS_SDRAM_SIZE		0x08000000

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_INIT_SP_ADDR		0x210000
#else
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_SDRAM_BASE + 4 * 1024 - GENERATED_GBL_DATA_SIZE)
#endif

#define CONFIG_SYS_LOAD_ADDR		0x22000000 /* load address */

/* SerialFlash */
#ifdef CONFIG_CMD_SF
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED		30000000
#endif

/* NAND flash */
#undef CONFIG_CMD_NAND

/* I2C */
#define AT24MAC_ADDR		0x5c
#define AT24MAC_REG		0x9a

/* LCD */
#ifdef CONFIG_ATMEL_HLCD
#define CONFIG_SYS_WHITE_ON_BLACK
#endif

#ifdef CONFIG_SYS_USE_MMC

/* bootstrap + u-boot + env in sd card */
#undef FAT_ENV_DEVICE_AND_PART
#undef CONFIG_BOOTCOMMAND

  #ifdef CONFIG_SYS_ENV_BOOT1
    /* env binary is created independently and written to boot1 */
    #undef  CONFIG_ENV_OVERWRITE
    #undef  CONFIG_ENV_IS_IN_FAT
    #define CONFIG_ENV_IS_IN_MMC
    #define CONFIG_SYS_MMC_ENV_DEV	 0   /* mmcblk0 */
    #define CONFIG_SYS_MMC_ENV_PART	 2   /* boot1 */
    #undef  CONFIG_ENV_OFFSET
    #define CONFIG_ENV_OFFSET  0
    #undef  CONFIG_ENV_SIZE
    #define CONFIG_ENV_SIZE  0x80000   /* 1M/2 */
    #undef  CONFIG_ENV_OFFSET_REDUND
    #define CONFIG_ENV_OFFSET_REDUND  0x80000

  #else

    #define FAT_ENV_DEVICE_AND_PART	"1"
    #define CONFIG_BOOTCOMMAND	"fatload mmc 1:1 0x21000000 at91-sama5d2_xplained.dtb; " \
				    "fatload mmc 1:1 0x22000000 zImage; " \
				    "bootz 0x22000000 - 0x21000000"
    #undef CONFIG_BOOTARGS
    #define CONFIG_BOOTARGS \
	    "console=ttyS0,115200 earlyprintk root=/dev/mmcblk1p2 rw rootwait"

  #endif

#endif    /* CONFIG_SYS_USE_MMC */


/* SPL */
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0x200000
#define CONFIG_SPL_MAX_SIZE		0x10000
#define CONFIG_SPL_BSS_START_ADDR	0x20000000
#define CONFIG_SPL_BSS_MAX_SIZE		0x80000
#define CONFIG_SYS_SPL_MALLOC_START	0x20080000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x80000

#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SYS_MONITOR_LEN		(512 << 10)

#ifdef CONFIG_SYS_USE_MMC
#define CONFIG_SPL_LDSCRIPT		arch/arm/mach-at91/armv7/u-boot-spl.lds
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME		"u-boot.img"

#elif CONFIG_SYS_USE_SERIALFLASH
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x10000

#endif

#endif
