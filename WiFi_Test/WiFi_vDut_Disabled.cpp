#include "stdafx.h"
#include "TestManager.h"
#include "WiFi_Test.h"
#include "WiFi_Test_Internal.h"
#include "IQmeasure.h"
#include "vDut.h"

using namespace std;

// Input Parameter Container
map<string, WIFI_SETTING_STRUCT> l_vDutDisabledParamMap;

// Return Value Container 
map<string, WIFI_SETTING_STRUCT> l_vDutDisabledReturnMap;

void ClearDutDisabledReturn(void)
{
	l_vDutDisabledParamMap.clear();
	l_vDutDisabledReturnMap.clear();
}

// WiFi_vDut_Disabled() does not require any inputs

struct tagReturn
{
    char ERROR_MESSAGE[MAX_BUFFER_SIZE];
} l_vDutDisabledReturn;

//! Special Function - Disable the vDut control layer
/*!
 * Input Parameters
 *
 *  - None
 *
 * Return Values
 *      -# ERROR_MESSAGE (char):			A string for error message 
 *
 * \return 0 No error occurred
 * \return -1 DUT failed to insert.  Please see the returned error message for details
 */
WIFI_TEST_API int WiFi_vDut_Disabled(void)
{
    int  err = ERR_OK;
    int  dummyValue = 0;
	char logMessage[MAX_BUFFER_SIZE] = {'\0'};

    /*---------------------------------------*
     * Clear Return Parameters and Container *
     *---------------------------------------*/
	ClearReturnParameters(l_vDutDisabledReturnMap);

    /*------------------------*
     * Respond to QUERY_INPUT *
     *------------------------*/
    err = TM_GetIntegerParameter(g_WiFi_Test_ID, "QUERY_INPUT", &dummyValue);
    if( ERR_OK==err )
    {
        TM_ClearReturns(g_WiFi_Test_ID);
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
        RespondToQueryReturn(l_vDutDisabledReturnMap);
        return err;
    }
	else
	{
		// do nothing
	}

	try
	{
	   /*---------------------------------------*
		* g_WiFi_Test_ID need to be valid (>=0) *
		*---------------------------------------*/		
		if( g_WiFi_Test_ID<0 )  
		{
			err = -1;
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] WiFi_Test_ID not valid.\n");
			throw logMessage;
		}
		else
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] WiFi_Test_ID = %d.\n", g_WiFi_Test_ID);
		}

		TM_ClearReturns(g_WiFi_Test_ID);

	   /*------------------------------------------------------------------*
		* Bypass the Dut control, 0 means bypass, 1 means need Dut control *
		*------------------------------------------------------------------*/
		err = vDUT_ByPassDutControl(0);
		if ( ERR_OK!=err )
		{
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_ERROR, "[WiFi] Fail to bypass vDut control, vDUT_ByPassDutControl(0) return error.\n");
			throw logMessage;
		}
		else
		{
			g_vDutControlDisabled = true;
			LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] vDUT_ByPassDutControl(0) successful.\n");
		} 

	   /*------------------------------*
		* Set g_WiFi_Dut = dummy value *
		*------------------------------*/	
		if ( -1==g_WiFi_Dut )
		{
			g_WiFi_Dut = 99999;
		}
		else
		{
			// do nothing
		}
  
	   /*----------------------------------------------*
		* Disable VSG output signal for Manual RX test *
		*----------------------------------------------*/
		// make sure no signal is generated by the VSG
		//err = ::LP_EnableVsgRF(0);
		//if ( ERR_OK!=err )
		//{
		//	// Just need to give an warning
		//	LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_WARNING, "[WiFi] Fail to turn off VSG, LP_EnableVsgRF(0) return error.\n");
		//	//throw logMessage;
		//}
		//else
		//{
		//	LogReturnMessage(logMessage, MAX_BUFFER_SIZE, LOGGER_INFORMATION, "[WiFi] Turn off VSG LP_EnableVsgRF(0) return OK.\n");
		//}

		/*-----------------------*
		 *  Return Test Results  *
		 *-----------------------*/
		if (ERR_OK==err)
		{
			sprintf_s(l_vDutDisabledReturn.ERROR_MESSAGE, MAX_BUFFER_SIZE, "[Info] Function completed.\n");
			ReturnTestResults(l_vDutDisabledReturnMap);
		}
		else
		{
			// do nothing
		}
	}
    catch(char *msg)
    {
        ReturnErrorMessage(l_vDutDisabledReturn.ERROR_MESSAGE, msg);
    }
    catch(...)
    {
		ReturnErrorMessage(l_vDutDisabledReturn.ERROR_MESSAGE, "[WiFi] Unknown Error!\n");
		err = -1;
    }

    return err;
}

int InitializeDutDisabledContainers(void)
{
    /*------------------*
     * Input Parameters: *
     * (None)           *
     *------------------*/
    l_vDutDisabledParamMap.clear();

    WIFI_SETTING_STRUCT setting;
    setting.unit = "";
    setting.helpText = "";

 	/*-----------------------------------*
     * Return Values:                    *
     * Error Msg while disconnect Tester *
     *-----------------------------------*/

	l_vDutDisabledReturnMap.clear();

    l_vDutDisabledReturn.ERROR_MESSAGE[0] = '\0';
    setting.type = WIFI_SETTING_TYPE_STRING;
    if (MAX_BUFFER_SIZE==sizeof(l_vDutDisabledReturn.ERROR_MESSAGE))    // Type_Checking
    {
        setting.value       = (void*)l_vDutDisabledReturn.ERROR_MESSAGE;
        setting.unit        = "";
        setting.helpText    = "Error message occurred";
        l_vDutDisabledReturnMap.insert( pair<string,WIFI_SETTING_STRUCT>("ERROR_MESSAGE", setting) );
    }
    else    
    {
        printf("Parameter Type Error!\n");
        exit(1);
    }

    return 0;
}

