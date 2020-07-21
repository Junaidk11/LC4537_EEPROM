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

/*******************************************************************
* NAME :            eeprom_errorHandling
*
* DESCRIPTION :     Function used for recovering from severe errors
*
* INPUTS : @param1:  one of the following:
*                       Error_Nil=0U,
                        Error_TwoActiveVS=1U,
                        Error_TwoCopyVS=2U,
                        Error_SetupStateMachine=3U,
                        Error_CopyButNoActiveVS=4U,
                        Error_NoActiveVS=5U,
                        Error_BlockInvalid=6U,
                        Error_NullDataPtr=7U,
                        Error_NoFreeVS=8U,
                        Error_InvalidVirtualSectorParameter=9U,
                        Error_ExceedSectorOnBank=10U,
                        Error_EraseVS=11U,
                        Error_BlockOffsetGtBlockSize=12U,
                        Error_LengthParam=13U,
                        Error_FeeUninit=14U,
                        Error_Suspend=15U,
                        Error_InvalidBlockIndex=16U,
                        Error_NoErase=17U,
                        Error_CurrentAddress=18U,
                        Error_Exceed_No_Of_DataSets=19U
*
*
*
* RETURN : E_OK/E_NOT_OK -> Fee Recovered/Didn't recover from Error
*
*
* NOTES :
*
*/
Std_ReturnType eeprom_errorHandling(Fee_ErrorCodeType errorCode){

    Std_ReturnType errorRecoveryResult = E_NOT_OK;
    if (errorCode == Error_Nil){

    }else if(errorCode == Error_TwoActiveVS){

    }else if(errorCode == Error_TwoCopyVS){

    }else if(errorCode == Error_SetupStateMachine){

    }else if(errorCode == Error_CopyButNoActiveVS){

    }else if(errorCode == Error_NoActiveVS){

    }else if(errorCode == Error_BlockInvalid){

    }else if(errorCode == Error_NullDataPtr){

    }else if(errorCode == Error_NoFreeVS){

    }else if(errorCode == Error_InvalidVirtualSectorParameter){

    }else if(errorCode == Error_ExceedSectorOnBank){

    }else if(errorCode == Error_EraseVS){

    }else if(errorCode == Error_BlockOffsetGtBlockSize){

    }else if(errorCode == Error_LengthParam){

    }else if(errorCode == Error_FeeUninit){

    }else if(errorCode == Error_Suspend){

    }else if(errorCode == Error_InvalidBlockIndex){

    }else if(errorCode == Error_NoErase){

    }else if(errorCode == Error_CurrentAddress){

    }else if(errorCode == Error_Exceed_No_Of_DataSets){

    }

    return errorRecoveryResult;
}

/*******************************************************************
* NAME :            eeprom_write
*
* DESCRIPTION :     Write Information to given Data Block
*
* INPUTS : @param1: EEP0/EEP1
*          @param2: DATA_BLOCK_x
*          @param3: pointer to buffer that holds data to be written to DATA_BLOCK_x
*          @param3: ASYNC/SYNC
*
*
* RETURN : E_OK/E_NOT_OK -> Job Scheduled/Completed OR Job Not-Scheduled/Completion Failed
*
*
* NOTES :  Job Scheduled and Job Not-Scheduled is for ASYNCHRONOUS job requests made to FEE
*          Job Completed and Job Failed are for SYNCHRONOUS job requests made to FEE.
*
*/
uint8_t eeprom_write(uint16_t eepromNumber, uint16_t dataBlock, uint8_t *pDataBuffer, uint8_t sync_or_async){

    Std_ReturnType jobScheduled = E_OK;
    if(sync_or_async == ASYNC){

        jobScheduled = TI_Fee_WriteAsync(dataBlock, pDataBuffer);
        if(jobScheduled == E_OK){
              /* Do nothing as Job scheduled successfully. */
            jobScheduled = E_OK;
        }else if(jobScheduled == E_NOT_OK){

            /* Do something -> Will updated later*/
            jobScheduled = E_NOT_OK;
        }

    }else if(sync_or_async == SYNC){

        jobScheduled = TI_Fee_WriteSync(dataBlock, pDataBuffer);

        if(jobScheduled == E_OK){

            // Check if Job Successful
            if(TI_Fee_GetJobResult(eepromNumber) == JOB_OK){
                   /*  Job completed. DO nothing*/
                jobScheduled = E_OK;
            }else if(TI_Fee_GetJobResult(eepromNumber) == JOB_FAILED){
                  /* Get Last Job Error */

                Fee_ErrorCodeType errorCode = TI_FeeErrorCode(eepromNumber);
                jobScheduled = eeprom_errorHandling(errorCode);

            }

        }else if(jobScheduled == E_NOT_OK){
            // Job Not accepted by the Fee Module -> DO something.
            jobScheduled = E_NOT_OK; // For Synchronous Job request not accepted, what are the possibilities?
        }

   }

    return ((uint8_t)jobScheduled);

}
uint8_t eeprom_read(uint16_t eepromNumber, uint16_t dataBlock, uint16_t startingAddress, uint8_t *pRecieveBuffer, uint16_t dataBlockLength, uint8_t sync_or_async);
uint8_t eeprom_erase(uint16_t eepromNumber, uint16_t dataBlock);
uint8_t eeprom_format(uint32_t formatCode);


