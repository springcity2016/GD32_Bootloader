/*!
    \file  spi_sd.h
    \brief the header file of SPI sd card driver
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-06-28, V1.0.0, demo for GD32F3x0
*/

#ifndef __SPI_SD_H_
#define __SPI_SD_H_
 
typedef enum
{
    /* SD card reponses error */
    SD_RESPONSE_NO_ERROR                   = (0x00),
    SD_IN_IDLE_STATE                       = (0x01),
    SD_COM_CRC_ERROR                       = (0x08),
    SD_RESPONSE_FAILURE                    = (0xFF),
}sd_error_enum;

/* the SD status: read data response xxx0<status>1 */
#define SD_DATA_OK                         0x05           /* status 010: data accecpted */
#define SD_DATA_CRC_ERROR                  0x0B           /* status 101: data rejected due to a crc error */
#define SD_DATA_WRITE_ERROR                0x0D           /* status 110: data rejected due to a write error */

/* dummy byte */
#define SD_DUMMY_BYTE   0xFF

/* start data tokens */
#define SD_START_DATA_SINGLE_BLOCK_READ    0xFE           /* data token start byte, start single block read */
#define SD_START_DATA_SINGLE_BLOCK_WRITE   0xFE           /* data token start byte, start single block write */

/* commands: cmdx = x | 0x40 */
#define SD_CMD_GO_IDLE_STATE               0              /* CMD0 = 0x40 */
#define SD_CMD_SEND_IF_COND                8              /* CMD8 = 0x48 */
#define SD_CMD_SEND_CSD                    9              /* CMD9 = 0x49 */
#define SD_CMD_SEND_CID                    10             /* CMD10 = 0x4A */
#define SD_CMD_SEND_STATUS                 13             /* CMD13 = 0x4D */
#define SD_CMD_READ_SINGLE_BLOCK           17             /* CMD17 = 0x51 */
#define SD_CMD_WRITE_SINGLE_BLOCK          24             /* CMD24 = 0x58 */
#define SD_CMD_SEND_OP_COND                41             /* ACMD41 = 0x69 */
#define SD_CMD_APP_CMD                     55             /* CMD55 = 0x77 */
#define SD_CMD_READ_OCR                    58             /* CMD58 = 0x7A */

/* chipselect definitions */
#define SD_CS_LOW()    gpio_bit_reset(GPIOF,GPIO_PIN_4);  /* select SD card: chipselect pin low */  
#define SD_CS_HIGH()   gpio_bit_set(GPIOF,GPIO_PIN_4);    /* deselect SD card: chipselect pin high */ 

/* SPI SD card function */
/* SD card initialization */
sd_error_enum sd_card_init(void);  
/* get SD card capacity */
sd_error_enum sd_card_capacity_get(void);
/* read a block from SD card */
sd_error_enum sd_block_read(unsigned char* pbuffer, unsigned int readaddr, unsigned short blocksize);
/* read multiple block from SD card */
sd_error_enum sd_multiblocks_read(unsigned char* pbuffer, unsigned int readaddr, unsigned short blocksize, unsigned int numberofblocks);
/* write a block to SD card */
sd_error_enum sd_block_write(unsigned char* pbuffer, unsigned int writeaddr, unsigned short blocksize);
/* write multiple block to SD card */
sd_error_enum sd_multiblocks_write(unsigned char* pbuffer, unsigned int writeaddr, unsigned short blocksize, unsigned int numberofblocks);
/* get SD card data response */
unsigned char sd_data_response_get(void);
/* read the csd register */
sd_error_enum sd_csd_register_get(unsigned char* sd_csd_table);
/* read the cid register */
sd_error_enum sd_cid_register_get(unsigned char* sd_cid_table);
/* send command to SD card */
unsigned char sd_cmd_send(unsigned char cmdx, unsigned int argument, unsigned char crc);
/* get the SD response */
sd_error_enum sd_response_get(unsigned char response);
/* put SD card in idle state */
sd_error_enum sd_to_idle_state(void);
/* get the SD status */
unsigned short sd_status_get(void);
/* use SPI bus write a byte to SD card */
unsigned char spi_write(unsigned char byte);
/* use SPI bus read a byte from SD card */
unsigned char spi_read(void);

#endif
