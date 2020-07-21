/*
 * eeprom_driver.c
 *
 *  Created on: Jul 20, 2020
 *      Author: Junaid
 */

#include "../inc/eeprom_driver.h"


void Delay(){

    unsigned int dummycnt=0x0000FFU;
      do
      {
          dummycnt--;
      }while(dummycnt>0);

}
/*******************************************************************
* NAME :            eepromBlockingMain
*
* DESCRIPTION :     TI_Fee_MainFunction called using this function to execute last schedule job.
*
* INPUTS : None
*
* RETURN : None
*
*
* NOTES :  This is the Blocking Implementation of TI_Fee_MainFunction, later will implement the Interrupt Method
*
*/

void eepromBlockingMain(){

    uint16_t feeModuleStatus;

    do{

        TI_Fee_MainFunction();
        Delay();
        feeModuleStatus = TI_Fee_GetStatus(EEP0);

    }while(feeModuleStatus!=IDLE);

}

/*******************************************************************
* NAME :            eeprom_Init
*
* DESCRIPTION :     Initializes Flash EEPROM Emulation. Creates Virtual Sectors & Adds Data Blocks.
*
* INPUTS : None
*
* RETURN : None
*
*
* NOTES :  None
*
*/

void eeprom_Init(){

    // Call TI Fee Init API to initialize Fee
    TI_Fee_Init();

    // Periodically call TI_Fee_MainFunction() to initialize the FEE, for now we use software delay, will add Timer Interrupt for every 2-5ms
    eepromBlockingMain();

}

uint8_t eeprom_write(uint16_t eepromNumber, uint16_t dataBlock, uint8_t *pDataBuffer, uint8_t sync_or_async);
uint8_t eeprom_read(uint16_t eepromNumber, uint16_t dataBlock, uint16_t startingAddress, uint8_t *pRecieveBuffer, uint16_t dataBlockLength, uint8_t sync_or_async);
uint8_t eeprom_erase(uint16_t eepromNumber, uint16_t dataBlock);
uint8_t eeprom_format(uint32_t formatCode);
uint8_t eeprom_errorHandling(uint8_t errorCode);


