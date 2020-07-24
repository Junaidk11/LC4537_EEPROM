/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
//#include "ti_fee.h"

#include "../drivers/inc/eeprom_driver.h"
/* USER CODE END */

/* Include Files */
#include "HL_sys_common.h"
/* USER CODE BEGIN (1) */


uint16 u16JobResult,Status;
Std_ReturnType oResult=E_OK;
unsigned char read_data[8]={0};

// Added for TMS570LC4537

uint8_t jobStatus;

uint8 SpecialRamBlock[8];
uint8 SpecialRamBlock1[8];

unsigned char pattern;
uint16 u16writecounter;

unsigned int  FeeVirtualSectorNumber;
unsigned char VsState, u8EEPIndex;
unsigned char u8VirtualSector;
uint8 Test_Recovery;
uint8 Test_Cancel;

void delay(void)
{
    unsigned int dummycnt=0x0000FFU;
    do
    {
        dummycnt--;
    }
    while(dummycnt>0);
}
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
    //unsigned int BlockOffset, Length;
    unsigned char *Read_Ptr=read_data;

    unsigned int loop;

    /* Initialize RAM array.*/
    for(loop=0;loop<8;loop++)SpecialRamBlock[loop] = loop;

    /* Initialize FEE. This will create Virtual sectors, initialize global variables etc.*/
    eeprom_Init();

    // Format Flash Bank 7 -> Just for TMS570LC4357,  has connection issues, want to start with a clean Bank to establish Connection.
    jobStatus = eeprom_Format(EEP0, FORMAT_EEPROM_BANK7);



    eeprom_Write(EEP0, DATA_BLOCK_1, &SpecialRamBlock[0], SYNC);


    /*
    TI_Fee_WriteSync(BlockNumber, &SpecialRamBlock[0]); */

    /* Read the block with unknown length */
     //BlockOffset = 2; // Read from 02->07, Last 2 Bytes will 'FF'  'FF'

     jobStatus = eeprom_Read(EEP0, DATA_BLOCK_1, 0, Read_Ptr, UNKNOWN_BLOCK_LENGTH, SYNC);




    /* Invalidate a written block
    TI_Fee_InvalidateBlock(BlockNumber);
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0);
    }
    while(Status!=IDLE); */

    /* Format bank 7 */
    while(TI_Fee_GetStatus(0)!= IDLE);
    TI_Fee_Format(0xA5A5A5A5U);

    while(1);
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
