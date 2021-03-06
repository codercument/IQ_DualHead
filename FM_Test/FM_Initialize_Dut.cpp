#include "stdafx.h"
#include "TestManager.h"
#include "FM_Test.h"
#include "FM_Test_Internal.h"
#include "IQmeasure.h"
#include "vDUT.h"

// This variable is declared in FM_Test_Internal.cpp
extern vDUT_ID      g_FM_Dut;
extern TM_ID        g_FM_Test_ID;

using namespace std;

// Input Parameter Container
map<string, FM_SETTING_STRUCT> l_initializeDutParamMap;

// Return Value Container 
map<string, FM_SETTING_STRUCT> l_initializeDutReturnMap;

struct tagParam
{
	char IMAGE_FILE_NAME[MAX_BUFFER_SIZE];		/*!< Specify which image file name is to be used; for example, BCM_FM.hcd. */
} l_initializeDutParam;

struct tagReturn
{
	char DUT_NAME[MAX_BUFFER_SIZE];				/*!< DUT name. */
    char ERROR_MESSAGE[MAX_BUFFER_SIZE];
} l_initializeDutReturn;

void ClearInitializeDutReturn(void)
{
	l_initializeDutParamMap.clear();
	l_initializeDutReturnMap.clear();
}

//! Initialize FM DUT
/*!
 * Input Parameters
 *
 *  - Mandatory 
 *      -# A string that is used to determine which DUT register function will be used
 *
 * Return Values
 *      -# A string that contains all DUT information, such as FW version, driver version, chip revision, etc.
 *      -# A string for error message
 *
 * \return 0 No error occurred
 * \return -1 DUT failed to insert.  Please see the returned error message for details
 */
FM_TEST_API int FM_Initialize_Dut(void)
{
    int		err = ERR_OK;	
    int		dummyValue = 0;
	char	logMessage[MAX_BUFFER_SIZE] = {'\0'};
	char	vDutErrorMsg[MAX_BUFFER_SIZE] = {'\0'};

    /*---------------------------------------*
     * Clear Return Parameters and Container *
     *---------------------------------------*/
	ClearReturnParameters(l_initializeDutReturnMap);

    /*------------------------*
     * Respond to QUERY_INPUT *
     *------------------------*/
    err = TM_GetIntegerParameter(g_FM_Test_ID, "QUERY_INPUT", &dummyValue);
    if( ERR_OK==err )
    {
        RespondToQueryInput(l_initializeDutParamMap);
        return err;
    }
	else
	{
		// do nothing
	}

    /*-------------------------*
     * Respond to QUERY_RETURN *
     *-------------------------*/
    err = TM_GetIntegerParameter(g_FM_Test_ID, "QUERY_RETURN", &dummyValue);
    if( ERR_OK==err )
    {
        RespondToQueryReturn(l_initializeDutReturnMap);
        return err;
    }
	else
	{
		// do nothing
	}

	try
	{
	   /*-----------------------------------------------------------*
		* Both g_FM_Test_ID and g_FM_Dut need to be valid (>=0) *
		*-----------------------------------------------------------*/
		TM_ClearReturns(g_FM_Test_ID);
		if( g_FM_Test_ID<0 || g_FM_Dut<0 )  
		{
			err = -1;
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[FM] FM_Test_ID or FM_Dut not valid.\n");
			throw logMessage;
		}
		else
		{
			// do nothing
		}

		/*----------------------*
		 * Get input parameters *
		 *----------------------*/
		err = GetInputParameters(l_initializeDutParamMap);
		if ( ERR_OK!=err )
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[FM] Input parameters are not complete.\n");
			throw logMessage;
		}

		// IMAGE_FILE_NAME, Specify which image file name has to be used; for example, BCM_FM.hcd. 
		err = vDUT_AddStringParameter (g_FM_Dut, "IMAGE_FILE_NAME", l_initializeDutParam.IMAGE_FILE_NAME);
		if ( ERR_OK!=err )
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[FM] vDUT_AddStringParameter(IMAGE_FILE_NAME) return error.\n", l_initializeDutParam.IMAGE_FILE_NAME);
			throw logMessage;
		}

		// Initialize DUT
		err = vDUT_Run(g_FM_Dut, "INITIALIZE_DUT");
		if ( ERR_OK!=err )
		{	// Check if vDUT returns "ERROR_MESSAGE" or not; if "Yes", then the error message must be handled and returned to the upper layer.
			err = vDUT_GetStringReturn(g_FM_Dut, "ERROR_MESSAGE", vDutErrorMsg, MAX_BUFFER_SIZE);
			if ( ERR_OK==err )	// Get "ERROR_MESSAGE" from vDut
			{
				err = -1;	// set err to -1; indicates there is an "Error".
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, vDutErrorMsg);
				throw logMessage;
			}
			else	// Return error message
			{
				LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[FM] vDUT_Run(INITIALIZE_DUT) return error.\n");
				throw logMessage;
			}
		}
		else
		{
			// do nothing
		}
	        
		// For retrieval of the DUT information
		err = vDUT_GetStringReturn(g_FM_Dut, "DUT_NAME", l_initializeDutReturn.DUT_NAME, MAX_BUFFER_SIZE);
		if ( ERR_OK!=err )
		{
			err = ERR_OK;	// This is an optional return parameter, thus always return OK
			sprintf_s(l_initializeDutReturn.DUT_NAME, MAX_BUFFER_SIZE, "No Return, Unknown Dut Name.\n");
		}
		else
		{
			// do nothing
		}

		/*-----------------------*
		 *  Return Test Results  *
		 *-----------------------*/
		if (ERR_OK==err)
		{
			sprintf_s(l_initializeDutReturn.ERROR_MESSAGE, MAX_BUFFER_SIZE, "[Info] Function completed.\n");
			ReturnTestResults(l_initializeDutReturnMap);
		}
		else
		{
			// do nothing
		}
	}
    catch(char *msg)
    {
        ReturnErrorMessage(l_initializeDutReturn.ERROR_MESSAGE, msg);
    }
    catch(...)
    {
		ReturnErrorMessage(l_initializeDutReturn.ERROR_MESSAGE, "[FM] Unknown Error!\n");
		err = -1;
    }

    return err;
}

void InitializeInitializeDutContainers(void)
{
    /*------------------*
     * Input Parameters: *
     *------------------*/
    l_initializeDutParamMap.clear();

    FM_SETTING_STRUCT setting;

    setting.unit        = "";
    setting.helpText    = "Specify which image file name to be used, such as BCM_FM.hcd.";
    setting.type = FM_SETTING_TYPE_STRING;
    strcpy_s(l_initializeDutParam.IMAGE_FILE_NAME, MAX_BUFFER_SIZE, "FM.hcd");
    if (MAX_BUFFER_SIZE==sizeof(l_initializeDutParam.IMAGE_FILE_NAME))    // Type_Checking
    {
        setting.value       = (void*)l_initializeDutParam.IMAGE_FILE_NAME;
        l_initializeDutParamMap.insert( pair<string,FM_SETTING_STRUCT>("IMAGE_FILE_NAME", setting) );
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
    l_initializeDutReturnMap.clear();

    l_initializeDutReturn.DUT_NAME[0] = '\0';
    setting.type = FM_SETTING_TYPE_STRING;
    if (MAX_BUFFER_SIZE==sizeof(l_initializeDutReturn.DUT_NAME))    // Type_Checking
    {
        setting.value       = (void*)l_initializeDutReturn.DUT_NAME;
        setting.unit        = "";
        setting.helpText    = "DUT name.";
        l_initializeDutReturnMap.insert( pair<string,FM_SETTING_STRUCT>("DUT_NAME", setting) );
    }
    else    
    {
        printf("Parameter Type Error!\n");
        exit(1);
    }

    l_initializeDutReturn.ERROR_MESSAGE[0] = '\0';
    setting.type = FM_SETTING_TYPE_STRING;
    if (MAX_BUFFER_SIZE==sizeof(l_initializeDutReturn.ERROR_MESSAGE))    // Type_Checking
    {
        setting.value       = (void*)l_initializeDutReturn.ERROR_MESSAGE;
        setting.unit        = "";
        setting.helpText    = "Error message occurred";
        l_initializeDutReturnMap.insert( pair<string,FM_SETTING_STRUCT>("ERROR_MESSAGE", setting) );
    }
    else    
    {
        printf("Parameter Type Error!\n");
        exit(1);
    }

    return;
}

