/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
#include "stdio.h"
#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "gd32f3x0.h"
#include "spi_sd.h"

#define BLOCK_SIZE			(512)



static int RAM_disk_status(void);
static int MMC_disk_status(void);
static int USB_disk_status(void);

static int RAM_disk_initialize(void);
static int MMC_disk_initialize(void);
static int USB_disk_initialize(void);

static int RAM_disk_read(BYTE *buff, DWORD sector, UINT count);
static int MMC_disk_read(BYTE *buff, DWORD sector, UINT count);
static int USB_disk_read(BYTE *buff, DWORD sector, UINT count);

static int RAM_disk_write(BYTE *buff, DWORD sector, UINT count);
static int MMC_disk_write(BYTE *buff, DWORD sector, UINT count);
static int USB_disk_write(BYTE *buff, DWORD sector, UINT count);

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_status();
		stat = result;
		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_status();
		stat = result;
		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_status();
		stat = result;
		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_initialize();
		stat = result;
		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_initialize();
		stat = result;
		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();
		stat = result;
		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_read(buff, sector, count);
		res = (DRESULT)result;
		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);
		res = (DRESULT)result;
		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here
		result = USB_disk_read(buff, sector, count);
		res = (DRESULT)result;
		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_write((BYTE*)buff, sector, count);
		res = (DRESULT)result;
		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here
		result = MMC_disk_write((BYTE*)buff, sector, count);
		res = (DRESULT)result;
		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here
		result = USB_disk_write((BYTE*)buff, sector, count);
		res = (DRESULT)result;
		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}

static int RAM_disk_status(void)
{
	return RES_OK;
}
static int MMC_disk_status(void)
{
	return RES_OK;
}
static int USB_disk_status(void)
{
	return RES_OK;
}

static int RAM_disk_initialize(void)
{
	return RES_OK;
}
static int MMC_disk_initialize(void)
{
	sd_error_enum status;
	/*-------------------------- SD Init ----------------------------- */
	status = sd_card_init();
	if (status!=SD_RESPONSE_NO_ERROR )
	{
		return STA_NOINIT;
	}
	else
	{
		return RES_OK;
	}	
}
static int USB_disk_initialize(void)
{
	return RES_OK;
}

static int RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{
	return RES_OK;
}
static int MMC_disk_read(BYTE *buff, DWORD sector, UINT count)
{
  	if (count > 1)
  	{  
    	sd_multiblocks_read(buff, sector, BLOCK_SIZE, count);
    	spi_write(0xff);
  	}
  	else
  	{
    	sd_block_read(buff, sector, BLOCK_SIZE);
    	spi_write(0xff);
  	}
  	return RES_OK;
}
static int USB_disk_read(BYTE *buff, DWORD sector, UINT count)
{
	return RES_OK;
}

static int RAM_disk_write(BYTE *buff, DWORD sector, UINT count)
{
	return RES_OK;
}
static int MMC_disk_write(BYTE *buff, DWORD sector, UINT count)
{
  	if (count > 1)
  	{
    	sd_multiblocks_write((uint8_t *)buff, sector, BLOCK_SIZE, count);
    	spi_write(0xff);
  	}
  	else
  	{
    	sd_block_write((uint8_t *)buff,sector, BLOCK_SIZE);
    	spi_write(0xff);
  	}
  	return RES_OK;
}
static int USB_disk_write(BYTE *buff, DWORD sector, UINT count)
{
	return RES_OK;
}
