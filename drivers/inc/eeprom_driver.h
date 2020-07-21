/*
 * eeprom_driver.h
 *
 *  Created on: Jul 20, 2020
 *      Author: Junaid
 */

#ifndef DRIVERS_INC_EEPROM_DRIVER_H_
#define DRIVERS_INC_EEPROM_DRIVER_H_



/*
 *  Include files
 */

#include "ti_fee.h"
#include "HL_sys_common.h"


/*
 *  EEPROMs Definition
 */

#define EEP0    0U
#define EEP1    1U

/*
 * Data Block Definitions ; Add more blocks to ti_fee_cfg.c, followed by adding their define below.
 */


#define DATA_BLOCK_1    1U
#define DATA_BLOCK_2    2U
#define DATA_BLOCK_3    3U
#define DATA_BLOCK_4    4U



/*
 *  Asynchronous and Synchronous Macros
 */
#define ASYNC    0U
#define SYNC     1U


/*
 *  Format EEPROM Bank - Need to send following code
 */
#define BANK7_FORMAT_CODE 0xA5A5A5A5U
/*
 *  Supported APIs
 */

/*
 *  Initialize FEE, create the Virtual Sectors and Add Data Blocks
 */
void eeprom_Init();

/*
 *  Write to a Data Block using Asynchronous method or synchronous method
 *  Return = Job scheduled successfully or Failed
 */
uint8_t eeprom_write(uint16_t eepromNumber, uint16_t dataBlock, uint8_t *pDataBuffer, uint8_t sync_or_async);

/*
 *  Read a given number of bytes from a Data Block of the EEPROM, given the starting Address in the block ; if Block Length unknown = set dataBlockLength to 0xFFFF
 */

uint8_t eeprom_read(uint16_t eepromNumber, uint16_t dataBlock, uint16_t startingAddress, uint8_t *pRecieveBuffer, uint16_t dataBlockLength, uint8_t sync_or_async);


uint8_t eeprom_erase(uint16_t eepromNumber, uint16_t dataBlock);

/*
 *  Call this functions to format Flash Bank 7
 */
uint8_t eeprom_format(uint32_t formatCode);

/*
 *  EEPROM error handling
 */
uint8_t eeprom_errorHandling(uint8_t errorCode);


#endif /* DRIVERS_INC_EEPROM_DRIVER_H_ */
