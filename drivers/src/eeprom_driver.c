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

    // Call TI Fee x  API to initialize Fee
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

/*******************************************************************
* NAME :            eeprom_read
*
* DESCRIPTION :     Read Data from a Data Block of a given EEPROM
*
* INPUTS : @param1: EEP0/EEP1
*          @param2: DATA_BLOCK_x
*          @param3: Offset from start of Data Block
*          @param4: pointer to buffer that will store data the read from the DATA_BLOCK_x
*          @param5: Length of Data Block / if Length Unknown set this to 0xFFFF
*          @param5: ASYNC/SYNC
*
*
* RETURN : E_OK/E_NOT_OK -> Job Scheduled/Completed OR Job Not-Scheduled/Completion Failed
*
*
* NOTES :  None
*
*/
uint8_t eeprom_read(uint16_t eepromNumber, uint16_t dataBlock, uint16_t startingAddress, uint8_t *pRecieveBuffer, uint16_t dataBlockLength, uint8_t sync_or_async){

        Std_ReturnType jobScheduled = E_OK;
        if(sync_or_async == ASYNC){

            jobScheduled = TI_Fee_Read(dataBlock, startingAddress, pRecieveBuffer, dataBlockLength);
            if(jobScheduled == E_OK){
                  /* Do nothing as Job scheduled successfully. */
                jobScheduled = E_OK;
            }else if(jobScheduled == E_NOT_OK){

                /* Do something -> Will updated later*/
                jobScheduled = E_NOT_OK;
            }

        }else if(sync_or_async == SYNC){

            jobScheduled = TI_Fee_ReadSync(dataBlock, startingAddress, pRecieveBuffer, dataBlockLength);

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

/*******************************************************************
* NAME :            eeprom_erase
*
* DESCRIPTION :     Erase a given Data block asynchronously
*
* INPUTS : @param1: EEP0/EEP1
*          @param2: DATA_BLOCK_x
*
* RETURN : E_OK/E_NOT_OK -> Job Scheduled/Completed OR Job Not-Scheduled/Completion Failed
*
*
* NOTES :  None
*
*/
uint8_t eeprom_erase(uint16_t dataBlock){

   Std_ReturnType jobScheduled = E_OK;

   jobScheduled = TI_Fee_EraseImmediateBlock(dataBlock);

   if(jobScheduled == E_OK){
       // Job Accepted by the TI Fee Module. Need to Call eeprom_BlockingMain periodically to finish job
       jobScheduled = E_OK;
   }else if(jobScheduled == E_NOT_OK){
       // Job Not Accepted by the TI Fee Module. Do Something
       jobScheduled = E_NOT_OK;
   }
   return ((uint8_t)(jobScheduled));
}

/*******************************************************************
* NAME :            eeprom_format
*
* DESCRIPTION :    Synchronous formating of emulated flash.
*                   FORMAT_CONFIGURED_SECTORS_ONLY will format ONLY configured sectors.
*                   FORMAT_EEPROM_BANK7  will format the entire  EEPROM Bank
*
* INPUTS :  @param1: EEP0/EEP1
*           @param2: Format code is one of the Following:
*                               FORMAT_CONFIGURED_SECTORS_ONLY
*                               FORMAT_EEPROM_BANK7
*
*
*
* RETURN : E_OK/E_NOT_OK -> Job Scheduled/Completed OR Job Not-Scheduled/Completion Failed
*
*
* NOTES : For "FORMAT_CONFIGURED_SECTORS_ONLY", FEE needs to be initialized.
*         For "FORMAT_EEPROM_BANK7" FEE doesn't need to be initialized.
*
*         This function should be called only if you want to reconfigure the Data Blocks/Virtual Sectors or detect a serious error condition.
*
*/
uint8_t eeprom_format(uint16_t eepromNumber, uint32_t formatCode){

    bool formatResult = false;
    Std_ReturnType jobScheduled = E_NOT_OK;

    if (formatCode== FORMAT_EEPROM_BANK7){

        // Don't need to check if FEE initialized.
        formatResult = TI_Fee_Format(formatCode);

        if(formatResult == true ){
               //Format successful - Do nothing -> Can add some flag, if need be

        }else{
                // Format Job failed - Determine error
            if(TI_Fee_GetJobResult((uint8)eepromNumber) == JOB_OK){
                           // If format failed, then this block won't enter, will remove  later, it is redundant.

            }else if(TI_Fee_GetJobResult((uint8)eepromNumber) == JOB_FAILED){

                // Error Recovery
                Fee_ErrorCodeType errorCode = TI_FeeErrorCode((uint8)eepromNumber);
                jobScheduled = eeprom_errorHandling(errorCode);
           }
        }

    }else if(formatCode== FORMAT_CONFIGURED_SECTORS_ONLY){

        // Need to check if the FEE module has been initialized before calling TI_Fee_Format with code.

        if(TI_Fee_GetStatus((uint8)eepromNumber)!= UNINIT && TI_Fee_GetStatus((uint8)eepromNumber)== IDLE){

               // Now we can call TI Format with key
            formatResult = TI_Fee_Format(formatCode);
            if(formatResult == true ){
                           //Format successful - Do nothing -> Can add some flag, if need be

            }else{
                    // Format Job failed - Determine error
                if(TI_Fee_GetJobResult((uint8)eepromNumber) == JOB_OK){
                               // If format failed, then this block won't enter, will remove  later, it is redundant.

                }else if(TI_Fee_GetJobResult((uint8)eepromNumber) == JOB_FAILED){

                    // Error Recovery
                    Fee_ErrorCodeType errorCode = TI_FeeErrorCode((uint8)eepromNumber);
                    jobScheduled = eeprom_errorHandling(errorCode);
               }
            }

        }

    }

    return (uint8_t)(jobScheduled);
}


