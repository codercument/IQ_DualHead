#include "stdafx.h"
#include "TestManager.h"
#include "WiFi_MiMo_Test.h"
#include "WiFi_MiMo_Test_Internal.h"
#include "IQmeasure.h"
#include "vDUT.h"

using namespace std;

// This variable is declared in WiFi_Test_Internal.cpp
extern vDUT_ID      g_WiFi_Dut;
extern TM_ID        g_WiFi_Test_ID;
extern bool			g_vDutTxActived;  // IQlite merge; Tracy Yu ; 2012-03-30 

#pragma region Define Input and Return structures (two containers and two structs)

// Input Parameter Container
map<string, WIFI_SETTING_STRUCT> l_writeRFRegisterParamMap;

// Return Value Container 
map<string, WIFI_SETTING_STRUCT> l_writeRFRegisterReturnMap;

struct tagParam
{
	char ADDRESS[MAX_BUFFER_SIZE];       /*!< A command string that is used to store the address of the EEPROM written. */
	char VALUE[MAX_BUFFER_SIZE];         /*!< A command string that is used to store the value to write.                */
} l_writeRFRegisterParam;

struct tagReturn
{
	char WRITE_REGISTER[MAX_BUFFER_SIZE];        /*!< A string contains information that write to register.         */
	char ERROR_MESSAGE[MAX_BUFFER_SIZE];         /*!< A string for error message.                                   */
} l_writeRFRegisterReturn;
#pragma endregion

#ifndef WIN32
int initWriteRFRegisterMIMOContainers = InitializeWriteRFRegisterContainers();
#endif

// These global variables/functions only for WiFi_Write_RF_Register.cpp
int CheckWriteRFRegisterParameters(char *ADDRESS, char *VALUE, char* errorMsg);

//! WiFi_Write_RF_Register
/*!
* Input Parameters
*
*  - Mandatory 
*      -# A command string that is used to Write EEPROM data
*
* Return Values
*      -# A string contains information that return from EEPROM
*      -# A string for error message
*
* \return 0 No error occurred
* \return -1 DUT failed to insert.  Please see the returned error message for details
*/
WIFI_MIMO_TEST_API int WiFi_Write_RF_Register(void)
{
	int  err = ERR_OK;
	int  dummyValue = 0;
	char vErrorMsg[MAX_BUFFER_SIZE] = {'\0'};
	char logMessage[MAX_BUFFER_SIZE] = {'\0'};


	/*---------------------------------------*
	* Clear Return Parameters and Container *
	*---------------------------------------*/
	ClearReturnParameters(l_writeRFRegisterReturnMap);

	/*------------------------*
	* Respond to QUERY_INPUT *
	*------------------------*/
	err = TM_GetIntegerParameter(g_WiFi_Test_ID, "QUERY_INPUT", &dummyValue);
	if( ERR_OK==err )
	{
		RespondToQueryInput(l_writeRFRegisterParamMap);
		return err;
	}
	else
	{
		// do nothing
	}

	/*-------------------------*
	* Respond to QUERY_RETURN *
	*-------------------------*/
	err = TM_GetIntegerParameter(g_WiFi_Test_ID, "QUERY_RETURN", &dummyValue);
	if( ERR_OK==err )
	{
		RespondToQueryReturn(l_writeRFRegisterReturnMap);
		return err;
	}
	else
	{
		// do nothing
	}

	try
	{
		/*-----------------------------------------------------------*
		* Both g_WiFi_Test_ID and g_WiFi_Dut need to be valid (>=0) *
		*-----------------------------------------------------------*/
		if( g_WiFi_Test_ID<0 || g_WiFi_Dut<0 )  
		{
			err = -1;
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] WiFi_Test_ID or WiFi_Dut not valid.\n");
			throw logMessage;
		}
		else
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] WiFi_Test_ID = %d and WiFi_Dut = %d.\n", g_WiFi_Test_ID, g_WiFi_Dut);
		}

		TM_ClearReturns(g_WiFi_Test_ID);

		
		// IQlite merge; Tracy Yu ; 2012-03-30 
		if ( g_vDutTxActived==true )
		{
		   /*-----------*
			*  Tx Stop  *
			*-----------*/
			err = ::vDUT_Run(g_WiFi_Dut, "TX_STOP");		
			if ( ERR_OK!=err )
			{	// Check vDut return "ERROR_MESSAGE" or not, if "Yes", must handle it.
				err = ::vDUT_GetStringReturn(g_WiFi_Dut, "ERROR_MESSAGE", vErrorMsg, MAX_BUFFER_SIZE);
				if ( ERR_OK==err )	// Get "ERROR_MESSAGE" from vDut
				{
					err = -1;	// set err to -1, means "Error".
					LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, vErrorMsg);
					throw logMessage;
				}
				else	// Just return normal error message in this case
				{
					LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] vDUT_Run(TX_STOP) return error.\n");
					throw logMessage;
				}
			}
			else
			{
				g_vDutTxActived = false;
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] vDUT_Run(TX_STOP) return OK.\n");
			}
		}
		else
		{
			// no need for TX_STOP				
		}
		// IQlite merge; Tracy Yu ; 2012-03-30 End

		/*----------------------*
		* Get input parameters *
		*----------------------*/
		err = GetInputParameters(l_writeRFRegisterParamMap);
		if ( ERR_OK!=err )
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] Input parameters are not complete.\n");
			throw logMessage;
		}
		else
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] Get input parameters return OK.\n");
		}

		// Error return of this function is irrelevant
		CheckDutStatus();

		// And clear vDut parameters at beginning.
		vDUT_ClearParameters(g_WiFi_Dut);

		// WRITE_COMMAND
		vDUT_AddStringParameter (g_WiFi_Dut,  "ADDRESS",   l_writeRFRegisterParam.ADDRESS);
		vDUT_AddStringParameter (g_WiFi_Dut,  "VALUE",     l_writeRFRegisterParam.VALUE);

#pragma region Prepare input parameters
		err = CheckWriteRFRegisterParameters( l_writeRFRegisterParam.ADDRESS, l_writeRFRegisterParam.VALUE, vErrorMsg );
		if ( ERR_OK!=err )
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, vErrorMsg);
			throw logMessage;
		}
		else
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] Prepare input parameters CheckWriteRFRegisterParameters() return OK.\n");
		}
#pragma endregion

		err = vDUT_Run(g_WiFi_Dut, "WRITE_RF_REGISTER");		
		if ( ERR_OK!=err )
		{	// Check vDut return "ERROR_MESSAGE" or not, if "Yes", must handle it.
			err = ::vDUT_GetStringReturn(g_WiFi_Dut, "ERROR_MESSAGE", vErrorMsg, MAX_BUFFER_SIZE);
			if ( ERR_OK==err )	// Get "ERROR_MESSAGE" from vDut
			{
				err = -1;	// set err to -1, means "Error".
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, vErrorMsg);
				throw logMessage;
			}
			else	// Just return normal error message in this case
			{
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] vDUT_Run(WRITE_RF_REGISTER) return error.\n");
				throw logMessage;
			}
		}
		else
		{
			// TODO: Example, get Return parameters here
			err = ::vDUT_GetStringReturn(g_WiFi_Dut, "WRITE_REGISTER", l_writeRFRegisterReturn.WRITE_REGISTER, MAX_BUFFER_SIZE);
			if ( ERR_OK!=err )
			{
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] No Return, Unknown EEPROM write to address result.\n");
				throw logMessage;
			}
			else
			{
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] vDUT_GetStringReturn(WRITE_REGISTER) return OK.\n");
			}	

			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] vDUT_Run(WRITE_RF_REGISTER) return OK.\n");
		}

		/*-----------------------*
		*  Return Test Results  *
		*-----------------------*/
		if (ERR_OK==err)
		{
			sprintf_s(l_writeRFRegisterReturn.ERROR_MESSAGE, MAX_BUFFER_SIZE, "[Info] Function completed.\n");
			ReturnTestResults(l_writeRFRegisterReturnMap);
		}
		else
		{
			// do nothing
		}
	}
	catch(char *msg)
	{
		ReturnErrorMessage(l_writeRFRegisterReturn.ERROR_MESSAGE, msg);
	}
	catch(...)
	{
		ReturnErrorMessage(l_writeRFRegisterReturn.ERROR_MESSAGE, "[WiFi] Unknown Error!\n");
		err = -1;
	}

	return err;
}

int InitializeWriteRFRegisterContainers(void)
{
	/*------------------*
	* Input Parameters: *
	*------------------*/
	l_writeRFRegisterParamMap.clear();

	WIFI_SETTING_STRUCT setting;

	sprintf_s(l_writeRFRegisterParam.ADDRESS, MAX_BUFFER_SIZE, "%s", "");
	setting.type = WIFI_SETTING_TYPE_STRING;
	if (MAX_BUFFER_SIZE==sizeof(l_writeRFRegisterParam.ADDRESS))    // Type_Checking
	{
		setting.value = (void*)l_writeRFRegisterParam.ADDRESS;
		setting.unit        = "";
		setting.helpText    = "The address that is used to write RF Register.";
		l_writeRFRegisterParamMap.insert( pair<string,WIFI_SETTING_STRUCT>("ADDRESS", setting) );
	}
	else    
	{
		printf("Parameter Type Error!\n");
		exit(1);
	}

	sprintf_s(l_writeRFRegisterParam.VALUE, MAX_BUFFER_SIZE, "%s", "");
	setting.type = WIFI_SETTING_TYPE_STRING;
	if (MAX_BUFFER_SIZE==sizeof(l_writeRFRegisterParam.VALUE))    // Type_Checking
	{
		setting.value = (void*)l_writeRFRegisterParam.VALUE;
		setting.unit        = "";
		setting.helpText    = "The value that is used to write RF Register.";
		l_writeRFRegisterParamMap.insert( pair<string,WIFI_SETTING_STRUCT>("VALUE", setting) );
	}
	else    
	{
		printf("Parameter Type Error!\n");
		exit(1);
	}

	/*----------------*
	* Return Values: *
	* ERROR_MESSAGE  *
	*----------------*/
	l_writeRFRegisterReturnMap.clear();

	// TODO: Example, add Return parameters here
	l_writeRFRegisterReturn.WRITE_REGISTER[0] = '\0';
	setting.type = WIFI_SETTING_TYPE_STRING;
	if (MAX_BUFFER_SIZE==sizeof(l_writeRFRegisterReturn.WRITE_REGISTER))    // Type_Checking
	{
		setting.value       = (void*)l_writeRFRegisterReturn.WRITE_REGISTER;
		setting.unit        = "";
		setting.helpText    = "The value had been written to BB Register.";
		l_writeRFRegisterReturnMap.insert( pair<string,WIFI_SETTING_STRUCT>("WRITE_REGISTER", setting) );
	}
	else    
	{
		printf("Parameter Type Error!\n");
		exit(1);
	}

	l_writeRFRegisterReturn.ERROR_MESSAGE[0] = '\0';
	setting.type = WIFI_SETTING_TYPE_STRING;
	if (MAX_BUFFER_SIZE==sizeof(l_writeRFRegisterReturn.ERROR_MESSAGE))    // Type_Checking
	{
		setting.value       = (void*)l_writeRFRegisterReturn.ERROR_MESSAGE;
		setting.unit        = "";
		setting.helpText    = "Error message occurred";
		l_writeRFRegisterReturnMap.insert( pair<string,WIFI_SETTING_STRUCT>("ERROR_MESSAGE", setting) );
	}
	else    
	{
		printf("Parameter Type Error!\n");
		exit(1);
	}

	return 0;
}

//-------------------------------------------------------------------------------------
// This is a function for checking the input parameters before the test.
// 
//-------------------------------------------------------------------------------------
int CheckWriteRFRegisterParameters(char *ADDRESS, char *VALUE, char* errorMsg)
{
	int    err = ERR_OK;
	//int    dummyInt = 0;
	char   logMessage[MAX_BUFFER_SIZE] = {'\0'};

	try
	{
		if((0==strlen(ADDRESS))||(0==strlen(VALUE)))
		{
			err = -1;
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] Invalid ADDRESS or LENGTH.\n");
			throw logMessage;
		}
		else
		{
			// do nothing
		}
		sprintf_s(errorMsg, MAX_BUFFER_SIZE, "[WiFi] CheckWriteRFRegisterParameters() Confirmed.\n");
	}
	catch(char *msg)
	{
		sprintf_s(errorMsg, MAX_BUFFER_SIZE, msg);
	}
	catch(...)
	{
		sprintf_s(errorMsg, MAX_BUFFER_SIZE, "[WiFi] Unknown Error!\n");
	}

	return err;
}

// IQlite merge; Tracy Yu ; 2012-03-30
void CleanupWriteRFRegister()
{
	l_writeRFRegisterParamMap.clear();
	l_writeRFRegisterReturnMap.clear();
}