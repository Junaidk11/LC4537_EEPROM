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
#include "HL_hal_stdtypes.h"


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
 *  Format Keys
 *
 */
#define FORMAT_CONFIGURED_SECTORS_ONLY    0xA5A5A5A5U
#define FORMAT_EEPROM_BANK7               0x5A5A5A5AU


/*
 *  Supported APIs
 */

void eeprom_Init();
void eepromBlockingMain();
uint8_t eeprom_write(uint16_t eepromNumber, uint16_t dataBlock, uint8_t *pDataBuffer, uint8_t sync_or_async);
uint8_t eeprom_read(uint16_t eepromNumber, uint16_t dataBlock, uint16_t startingAddress, uint8_t *pRecieveBuffer, uint16_t dataBlockLength, uint8_t sync_or_async);
uint8_t eeprom_erase(uint16_t dataBlock);
uint8_t eeprom_format(uint16_t eepromNumber, uint32_t formatCode);


#endif /* DRIVERS_INC_EEPROM_DRIVER_H_ */
