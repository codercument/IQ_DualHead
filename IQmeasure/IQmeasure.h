/*! \mainpage IQmeasure Wrapper Library Documentation
 *
 * The IQmeasure Wrapper Library is the wrapper of "IQmeausre_IQapi_Legacy", "IQmeasure_IQapi_SCPI" and "IQmeasure_SCPI".
 * The IQmeasure Wrapper Library brings ease of use to programming LitePoint wireless test instruments,
 * including IQview/IQflex, IQnxn_plus, IQmax, and IQ2010.
 *
 * A number of high-level functions provided by the library greatly reduce the steep learning
 * curve associated with using the C++ IQapi.  The code below shows how easily an EVM measurement
 * for OFDM-54 can be done:
 *
 * \code
  void main(void)
  {
      LP_InitTester("192.168.100.254");
      LP_SetVsa(2412e6, 18, PORT_LEFT, 0, -25);
      LP_VsaDataCapture(200);
      LP_Analyze80211ag();
      double evm = LP_GetScalarMeasurement("evmAll");
      printf("EVM for OFDM-54 = %.2f\n", evm);
  }
 * \endcode
 *
 * Please see below the functions provided by The IQmeasure Wrapper Library:
 * -# Instrument Control Functions:
 *   - LP_Init();
 *   - LP_Term();
 *   - LP_InitTester();
 *   - LP_InitTester2();
 *   - LP_InitTester3();
 *   - LP_InitTester4();
 *   - LP_GetVersion();
 *   - LP_ConClose();
 *   - LP_ConOpen();
 * -# Configuration Functions:
 *   - LP_SetVsg();
 *   - LP_SetVsa();
 *   - LP_SetVsgCw();
 *   - LP_SetVsgModulation();
 *   - LP_SetAnalysisParameterInteger();
 *   - LP_SetAnalysisParameterIntegerArray();
 *   - LP_SaveVsaSignalFile();
 *   - LP_LoadVsaSignalFile();
 *   - LP_SaveVsaGeneratorFile();
 *   - LP_SaveIQDataToModulationFile();
 *   - LP_Agc();
 *   - LP_SetFrameCnt();
 *   - LP_EnableVsgRF();
 *   - LP_EnableSpecifiedVsgRF();
 *   - LP_SetLpcPath();
 * -# Data Capture Functions:
 *   - LP_VsaDataCapture();
 * -# Analysis Functions:
 *   - LP_Analyze80216d();
 *   - LP_Analyze80216e();
 *   - LP_Analyze80211p();
 *   - LP_Analyze80211ag();
 *   - LP_Analyze80211n();
 *   - LP_Analyze80211b();
 *   - LP_AnalyzePower();
 *   - LP_AnalyzeFFT();
 *   - LP_AnalyzeCCDF();
 *   - LP_AnalyzeCW();
 *   - LP_AnalysisWave();
 *   - LP_AnalyzeSidelobe();
 *   - LP_AnalyzePowerRampOFDM();
 *   - LP_AnalyzePowerRamp80211b();
 *   - LP_AnalyzeBluetooth();
 *   - LP_AnalyzeZigbee();
 * -# Result Retrieving Functions:
 *   - LP_GetScalarMeasurement();
 *   - LP_GetStringMeasurement();
 *   - LP_GetVectorMeasurement();
 * -# Error Handling Functions:
 *   - LP_GetErrorString();
 *   - LP_GetIQapiHndlLastErrMsg();
 *
 * \section revision_sec Revision History
 *
 * \subsection revision_3_0_0_1 3.0.0.1
 * Date: June 1, 2012
 * -# IQapi Version: IQapi_scpi 2.0.1.62
 *
 *
 *
 */

/*! \file IQmeasure.h
 * \brief IQmeasure Library Interface functions
 */

/*! @defgroup group1 How to make an accurate measurement?
 * \image html AmplSweepWithIdealSignal.gif "Sweeping ampl Setting with Ideal Signal" width=300
 */

/*! @defgroup group2 How to re-use the capture for multiple analysis?
 *
 */

/*! @defgroup group3 How to transmit a waveform continuously?
 *
 */

/*! @defgroup group4 What is Packet Engine?
 *
 */

#ifndef _IQMEASURE_H_
#define _IQMEASURE_H_


#ifdef IQMEASURE_EXPORTS
	#define IQMEASURE_API extern "C" __declspec(dllexport)
#else
	#define IQMEASURE_API extern "C" __declspec(dllimport)
#endif

#include "iqapiDefines.h"

#define IQLegacy_Dll	"IQmeasure_IQapi_Legacy.dll"
//#define IQXel_Dll		"IQmeasure_IQapi_SCPI.dll"
#define IQXel_Dll		"IQmeasure_SCPI.dll"

//#define IQMeasureVersion                "3.0.0 (08-03-2012)"

#define MAX_MPTA_PORTS			4
#define VERY_LOW_VSG_POWER_DBM	-110

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#define IQMEASURE_IQAPI_CONTROL_ENABLE  1                   // Turn ON(1)/OFF(0) IQapi tester control method, in code compile
#define IQMEASURE_SCPI_CONTROL_ENABLE   1                   // Turn ON(1)/OFF(0) SCPI  tester control method, in code compile

enum IQTESTER_TYPE
{
	IQTYPE_2010,
	IQTYPE_XEL

};

enum LP_TESTER_CONTROL
{
    TESTER_CONTROL_IQAPI    = 0,                            /*!< Using IQapi to control LP tester  */
    TESTER_CONTROL_SCPI     = 1                             /*!< Using SCPI to control LP tester  */
};

enum IQAPI_PORT_ENUM
{
    PORT_OFF   = 1,                       /*!< Port has been disabled. */
    PORT_LEFT  = 2,                       /*!< RF uses left port(RF1).      */
    PORT_RIGHT = 3,                       /*!< RF uses right port(RF2).     */
    PORT_BB    = 4						  /*!< BB ports in use.        */
};

enum LP_MEASUREMENT_VSG_MODE
{
    VSG_NO_MOD_FILE_LOADED = 0,             /*!< No MOD file has been loaded*/
    VSG_SINGLE_MOD_FILE,                    /*!< Single MOD file has been loaded*/
    VSG_MULTI_SEGMENT_MOD_FILE,             /*!< Multi-segment MOD file has been loaded*/
    VSG_INVALID_MODE                        /*!< Invalid VSG mode*/
};

enum LP_ANALYSIS_TYPE_ENUM
{
	ANALYSIS_80211AG,                    /*!< 802.11a/g analysis*/
	ANALYSIS_80211B,                     /*!< 802.11b analysis*/
	ANALYSIS_MIMO,                       /*!< 802.11n MIMO analysis*/
	ANALYSIS_POWER,                      /*!< Power analysis*/
	ANALYSIS_FFT,                        /*!< FFT analysis*/
	ANALYSIS_CCDF,                       /*!< CCDF analysis*/
	ANALYSIS_CW,                         /*!< CW analysis*/
	ANALYSIS_WAVE,                       /*!< Wave analysis*/
	ANALYSIS_SIDELOBE,                   /*!< Sidelobe analysis*/
	ANALYSIS_POWERRAMPOFDM,              /*!< Power Ramp analysis for OFDM*/
	ANALYSIS_POWERRAMP80211B,            /*!< Power Ramp analysis for 802.11b*/
	ANALYSIS_BLUETOOTH,                  /*!< Bluetooth analysis*/
	ANALYSIS_ZIGBEE,                     /*!< Zigbee analysis*/
	ANALYSIS_HT40,                       /*!< 802.11n HT40 spectrum mask analysis*/
	ANALYSIS_80211AC,                    /*!< 802.11ac MIMO analysis*/
	ANALYSIS_80211p,
	ANALYSIS_VHT80,
	ANALYSIS_MAX_NUM                     /*!< Invalid analysis type*/

};

enum LP_TECHNOLOGY_TYPE_ENUM
{
	TECHNOLOGY_80211AG,                    /*!< 802.11a/g analysis*/
	TECHNOLOGY_80211B,                     /*!< 802.11b analysis*/
	TECHNOLOGY_MIMO,                       /*!< 802.11n MIMO analysis*/
	TECHNOLOGY_WAVE,                       /*!< Wave analysis*/
	TECHNOLOGY_BLUETOOTH,                  /*!< Bluetooth analysis*/
	TECHNOLOGY_ZIGBEE,                     /*!< Zigbee analysis*/
	TECHNOLOGY_HT40,                       /*!< 802.11n HT40 spectrum mask analysis*/
	TECHNOLOGY_MAX_NUM                     /*!< Invalid analysis type*/
};

//VSA Capture Sample Rate
enum {SAMPLE_640KHz, SAMPLE_5_12MHz};

//FM Filter Selection
enum {BLACKMAN_HARRIS, HANNING, FLAT_TOP};

//FM Mode Selection
enum {FM_MONO, FM_STEREO, FM_AUTO};

// FM Pre-emphasis Time Constant Select
enum {PRE_EMPHASIS_NONE, PRE_EMPHASIS_25US, PRE_EMPHASIS_50US, PRE_EMPHASIS_75US};

// RDS Phase Shift Selection
enum {RDS_PHASE_SHIFT_NONE, RDS_PHASE_SHIFT_90};

// FM Channel Selection
//Note: LEFT_EQUALS_RIGHT and LEFT_EQUALS_MINUS_RIGHT can be used only for generating audio stimulus for FM RX Test.
// It cannot be used for setting up VSG Tones.

enum {LEFT_ONLY, RIGHT_ONLY, LEFT_RIGHT, LEFT_EQUALS_RIGHT, LEFT_EQUALS_MINUS_RIGHT};

enum IQAPI_ALC_MODES
{
	ALC_MANUAL,	// Indicates ALC Manual is on
	/* This is the default value */
	ALC_AUTO_ON_TIMEOUT, // Indicates ALC Automatic on Timeout
	ALC_OFF,		// Indicates that ALC is off
	ALC_MANUAL_HIGH_PRECISION
};

enum IQMEASURE_ERROR_CODES
{
	ERR_OK,
	ERR_NO_CONNECTION,
	ERR_NOT_INITIALIZED,
	ERR_SAVE_WAVE_FAILED,
	ERR_LOAD_WAVE_FAILED,
	ERR_SET_TX_FAILED,
	ERR_SET_WAVE_FAILED,
	ERR_SET_RX_FAILED,
	ERR_CAPTURE_FAILED,
	ERR_NO_CAPTURE_DATA,
	ERR_VSA_NUM_OUT_OF_RANGE,
	ERR_ANALYSIS_FAILED,
	ERR_NO_VALID_ANALYSIS,
	ERR_VSG_PORT_IS_OFF,
    ERR_NO_MOD_FILE_LOADED,
    ERR_NO_CONT_FOR_MULTI_SEGMENT,
    ERR_MEASUREMENT_NAME_NOT_FOUND,
    ERR_INVALID_ANALYSIS_TYPE,
    ERR_NO_ANALYSIS_RESULT_AVAILABLE,
    ERR_NO_MEASUREMENT_RESULT,
    ERR_INVALID_IP_ADDRESS,
    ERR_GENERAL_ERR,
	ERR_TX_NOT_DONE,
    ERR_SET_TOKEN_FAILED,
    ERR_TOKEN_RETRIEVAL_TIMEDOUT,
	ERR_INVALID_CAPTURE_INDEX,
	ERR_VSG_POWER_EXCEED_LIMIT,
    ERR_ANALYSIS_NULL_POINTER,
    ERR_ANALYSIS_UNSUPPORTED_PARAM_NAME,
    ERR_ANALYSIS_INVALID_PARAM_VALUE,
	ERR_INVALID_DATA_CAPTURE_RANGE,
	ERR_DATARATE_DOES_NOT_EXIST,
	ERR_BUFFER_OVERFLOW,
	ERR_SET_PATH_NOT_DONE,
		//FM Error Codes
	ERR_FM_NOT_INITIALIZED,
	ERR_FM_SET_TX_FAILED,
	ERR_FM_GET_TX_FAILED,
	ERR_FM_SET_AUDIO_TONE_FAILED,
	ERR_FM_GET_AUDIO_TONE_FAILED,
	ERR_FM_NO_CAPTURE_DATA,
	ERR_FM_VSA_CAPTURE_FAILED,
	ERR_FM_SET_RX_FAILED,
	ERR_FM_GET_RX_FAILED,
	ERR_FM_ANALYSIS_FAILED,
	ERR_FM_CAPTURE_AUDIO_FAILED,
	ERR_FM_GENERATE_AUDIO_FAILED,
	ERR_FM_QUERY_AIM_FAILED,
	ERR_FM_SAVE_WAV_AUDIO_FAILED,
	ERR_FM_PLAY_AUDIO_FAILED,
	ERR_FM_LOAD_AUDIO_FAILED,
	ERR_FM_STOP_AUDIO_PLAY_FAILED,
	ERR_GPS,
	ERR_SET_MULTI_THREAD_FAILED,
	ERR_UNKNOWN_TESTER_TYPE,
    ERR_INVALID_TESTER_CONTROL,         // Tester control method not valid (SCPI, IQAPI, ...)
	ERR_NO_RESPONSE_FROM_TESTER,

	ERR_MPTA_NOT_ENABLE,
	ERR_MPTA_NOT_DISENABLE,
	ERR_MPTA_SET_TXRX,
	ERR_MPTA_CAPTURE_FAILED

};

enum IQMEASURE_CAPTURE_NONBLOCKING_STATES
{
	BLOCKING,	// NONBLOCKING is off
	ARM_TRIGGER,
	CHECK_DATA
};



namespace UsedInMTK
{
	#define FFT_Length 2048
	#define FFT_Half_Length 1024
	#define FFT_Freq_Step 39062.5

	IQMEASURE_API enum TX_PATH_ENUM
	{
		eTX_PATH_12,
		eTX_PATH_13,
		eTX_PATH_1,
		eTX_PATH_2,
		eTX_PATH_3,
		eTX_PATH_123,
		eTX_PATH_ALL
	};

	typedef struct
	{
		double cutoff_mhz[20];
		double cutoff_dbr[20];
		double stopband_a_mhz[20];
		double stopband_a_dbr[20];
		double stopband_b_mhz[20];
		double stopband_b_dbr[20];
		double stopband_c_mhz[20];
		double stopband_c_dbr[20];
		double stopband_d_mhz[20];
		double stopband_d_dbr[20];
		double stopband_e_mhz[20];
		double stopband_e_dbr[20];
		double stopband_f_mhz[20];
		double stopband_f_dbr[20];
	} SpectrumMaskSpecification;

	IQMEASURE_API enum LP_SPECTRAL_MASK_ENUM
	{
		SPECTRAL_MASK_OFDM = 0,
		SPECTRAL_MASK_MIMO_HT20,
		SPECTRAL_MASK_MIMO_HT40,
		SPECTRAL_MASK_WiMAX_10MHz,
		SPECTRAL_MASK_WiMAX_7MHz,
		SPECTRAL_MASK_11b = 20,
		SPECTRAL_MASK_ZIGBEE,
		SPECTRAL_MASK_BT,
		SPECTRAL_MASK_BT_EDR,
		SPECTRAL_MASK_NONE = 99,
	};

	enum {PORT1, PORT2, PORT3, PORT4, PORT_CNT, PORT_DONE = -1};
	enum {BM_PORT1=1, BM_PORT2=2, BM_PORT3=4, BM_PORT4=8, BM_PORT_ALL=15};

	void setPathMPTA(int txPath);
}

using namespace UsedInMTK;


/**********************
* Extern Variables  *
**********************/
IQMEASURE_API int  loggerIQmeasure;
IQMEASURE_API int  timerIQmeasure;

/*********************/
/* Internal function */
/*********************/
int LP_Analyze(void);
//FM
int LP_Analyze_FMHndl(void);
int LP_FreeMemory(void);


/***************************/
/* Init and Term Functions */
/***************************/

//! Initializes the MATLAB environment for running IQmeasure
/*!
 * \param[in] IQtype Pointer to IQ tester type. IQXel or IQ legacy testers. It decides what dll to link.
 * \parameter[in] testerControlMethod indicates what method is used to control LP tester: 0 = IQapi, 1 = SCPI command
 * \return 0 if MATLAB initialized OK; non-zero indicates MATLAB failed to initialize.
 * \remakr This function needs to be run only once, typically at the very beginning of a program.
 */
IQMEASURE_API int		LP_Init(int IQtype = IQTYPE_XEL,int testerControlMethod = 0);

//! Terminates the MATLAB environment
/*!
 * \return 0 if MATLAB initialized OK; non-zero indicates MATLAB failed to terminate.
 * \remark This function only needs to be run at the very end when a programm is going to exit.
 *         Calling this function in the middle of a program will cause the program not to function.
 *         Since the programm is exiting anyway, you may skip calling LP_Term().
 */
IQMEASURE_API int		LP_Term(void);

//! Gets the IQapi handle and tester initialized status
/*!
* \param[in] getHndl Pointer to IQapi handle
* \param[in] testerInitialized Pointer to tester initialized status
*
* \return always return ERR_OK
*/
IQMEASURE_API int		LP_GetIQapiHndl(void **getHndl, bool *testerInitialized);

//! Gets the version information
/*!
 * \param[out] buffer The buffer that will return the version information, which includes:
 *   - IQmeasure version
 *   - Source code SVN version
 *   - IQapi version (if used)
 *   -
 *   -
 * \param[in] buf_size Indicates the size of the buffer
 *
 */
IQMEASURE_API bool		LP_GetVersion(char *buffer, int buf_size);

/*********************************/
/* Connection Handling Functions */
/*********************************/


//! Initializes a tester
/*!
 * \param[in] ipAddress The IP address of the tester
 *
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_InitTester(char *ipAddress);

//! Initializes a 2x2 802.11n setup
/*!
 * \param[in] ipAddress1 The IP address of the master tester
 * \param[in] ipAddress2 The IP address of the slave tester
 *
 * \return ERR_OK if testers has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_InitTester2(char *ipAddress1, char *ipAddress2);

//! Initializes a 3x3 802.11n setup
/*!
 * \param[in] ipAddress1 The IP address of the master tester
 * \param[in] ipAddress2 The IP address of the slave tester
 * \param[in] ipAddress3 The IP address of the slave tester
 *
 * \return ERR_OK if testers has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_InitTester3(char *ipAddress1, char *ipAddress2, char *ipAddress3);

//! Initializes a 4x4 802.11n setup
/*!
 * \param[in] ipAddress1 The IP address of the master tester
 * \param[in] ipAddress2 The IP address of the slave tester
 * \param[in] ipAddress3 The IP address of the slave tester
 * \param[in] ipAddress4 The IP address of the slave tester
 *
 * \return ERR_OK if testers has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_InitTester4(char *ipAddress1, char *ipAddress2, char *ipAddress3, char *ipAddress4);

/******************/
/* Error handling */
/******************/
IQMEASURE_API char*		LP_GetErrorString(int err);
IQMEASURE_API char*		LP_GetIQapiHndlLastErrMsg();

//! Closes the connection to tester(s)
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_ConClose(void);

//! Re-establish the connection to tester(s)
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_ConOpen(void);

IQMEASURE_API int		LP_SetDefault(void);

//! Establish the connection to tester(s) with dual-head support
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_DualHead_ConOpen(int tokenID, char *ipAddress1, char *ipAddress2=NULL, char *ipAddress3=NULL, char *ipAddress4=NULL);

//! Retrieve the Token ID being used for dual-head operation
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_DualHead_GetTokenID(int *tokenID);


//! Closes the connection to tester(s)
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_DualHead_ConClose();

//! Obtain the control of tester(s) for dual-head operation
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_DualHead_ObtainControl(unsigned int probeTimeMS=100, unsigned int timeOutMS=0);

//! Release the control of tester(s) for dual-head operation
/*!
 * \return ERR_OK if the tester has been successfully initialized; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_DualHead_ReleaseControl();


IQMEASURE_API int		LP_SetAlcMode(IQAPI_ALC_MODES alcMode);
IQMEASURE_API int		LP_GetAlcMode(IQAPI_ALC_MODES* alcMode);

/********************************/
/* Instrument Control Functions */
/********************************/


//! Sets up VSG
/*!
 * \param[in] rfFreqHz The center frequency of VSG (Hz)
 * \param[in] rfGainDb The output power level of VSG (dBm)
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1)
 *				- =3: Right RF port (RF2) (Default)
 *				- =4: Baseband
 * \param[in] setGapPowerOff
 *              - =true: Turn off RF power in the gap between packets
 *              - =false: Does not turn off RF power in the gap between packets
  * \param[in] dFreqShiftHz Frequency Shit
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsg(double rfFreqHz, double rfPowerLeveldBm, int port, bool setGapPowerOff = true, double dFreqShiftHz = 0.0);

//! Sets up VSG Compensation Table
/*!
 * \param[in] dcErrI I part of the DC compensation
 * \param[in] dcErrQ Q part of the DC compensation
 * \param[in] phaseErr Phase compensation
 * \param[in] gainErr Gain compensation
 * \param[in] delayErr Delay compensation
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsg_Compensation(double		  dcErrI,
										 double		  dcErrQ,
										 double		  phaseErr,
										 double		  gainErr,
										 double		  delayErr);
//! Sets up VSG triggerType
/*!
 * \param[in] triggerType Select VSG trigger Type. 0 = IQV_VSG_TRIG_FREE_RUN; 1 = IQV_VSG_TRIG_EXT_1; 2 = IQV_VSG_TRIG_EXT_2
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */

IQMEASURE_API int		LP_SetVsgTriggerType(int trigger);

//! Sets up VSG including gapPOwerrOff parameter
/*!
 * \param[in] rfFreqHz The center frequency of VSG (Hz)
 * \param[in] rfGainDb The output power level of VSG (dBm)
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1)
 *				- =3: Right RF port (RF2) (Default)
 *				- =4: Baseband
 * \param[in] gapPowerOff Turn the GapPowerOff feature On and Off On = 0( means that gap power is Off) Off = 1( means gap power is On)
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsg_GapPower(double rfFreqHz, double rfPowerLeveldBm, int port, int gapPowerOff);

//! Sets up VSGs for IQnxn
/*!
 * \param[in] rfFreqHz The center frequency of all VSGs (Hz)
 * \param[in] rfGainDb[4] The output power levels of VSGs (dBm).  There must be 4 elements in the double array
 * \param[in] port[4] The port to which the VSGs connect. A 4 integer array, with the following options for each element:
 *				- =1: OFF
 *				- =2: Left RF port (RF1)
 *				- =3: Right RF port (RF2) (Default)
 *				- =4: Baseband
 * \param[in] dFreqShiftHz Frequency Shit
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsgNxN(double rfFreqHz, double rfPowerLeveldBm[], int port[], double dFreqShiftHz = 0.0);

//! Sets up VSG for transmitting CW
/*!
 * \param[in] sineFreqHz The center frequency of VSG (Hz)
 * \param[in] offsetFrequencyMHz The offset frequency to the center.  The generated CW frequency (Hz) = sineFreqHz + offsetFrequencyMHz * 1e6
 * \param[in] rfPowerLeveldBm The output power level of CW (dBm)
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1)
 *				- =3: Right RF port (RF2) (Default)
 *				- =4: Baseband
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsgCw(double sineFreqHz, double offsetFrequencyMHz, double rfPowerLeveldBm, int port);

//! Saves Signal Arrays
/*!
 * \param[in] real[N_MAX_TESTERS]
 * \param[in] imag[N_MAX_TESTERS]
 * \param[in] length[N_MAX_TESTERS]
 * \param[in] sampleFreqHz[N_MAX_TESTERS]
 * \param[in] fileNameToSave
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SaveSignalArrays(double *real[N_MAX_TESTERS],
									  double *imag[N_MAX_TESTERS],
									  int length[N_MAX_TESTERS],
									  double sampleFreqHz[N_MAX_TESTERS],
									  char *fileNameToSave);

//! Save I/Q data in memory to MOD file and load to the VSG memory
/*!
 * \param[in] real A double pointer to the I data in memory, for multiple streams
 * \param[in] imag A double pointer to the Q data in memory, for multiple streams
 * \param[in] length An integer array indicating the I/Q data length for each stream
 * \param[in] modFileName The modulation file name
 * \param[in] normalization A flag indicating if normalization is needed.
 *				- 1=Normalize I/Q data (RMS power = 0dBm)
 *				- 0=Do not normalize I/Q data
 * \param[in] loadIQDataToVsg A flag indicating if the I/Q data will be loaded to VSG.
 *				- 1=load I/Q data to VSG
 *				- 0=do not load I/Q data to VSG
 *
 * \return ERR_OK if the function runs OK; otherwise call LP_GetErrorString() for detailed error message.
 *
 * \remark
 *         -# The sampling rate for I/Q data has to be 80MHz
 *         -# For multiple stream I/Q, "real" and "imag" assumes that two dimentional double
 *			  arrays are constructed in memory, the first dimension indicating number of streams, and
 *			  second dimension indicating the length of I/Q data, specified by the length array.
 */
IQMEASURE_API int		LP_SaveIQDataToModulationFile(double *real,
												double *imag,
												int length[N_MAX_TESTERS],
												char *modFileName,
												int  normalization,
												int loadIQDataToVsg);

//! Loads the modulation file (waveform) to VSG and performs auto transmit of the loaded VSG mod file in free run mode
/*!
 * \param[in] modFileName The .mod file to be loaded
 * \param[in] Choose whether to load modFile from internal tester (1) or upload from file (0) default is (0).
 *            This option is only valid with IQxel tester other wise it is ignored.
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsgModulation(char *modFileName, int loadInternalWaveform = 0);

//! Set VSA integer parameter before doing analysis
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_analysis_name "Analysis Name" for all available analysis names
 * \param[in] parameter The parameter will specify which VSA parameter will be set.
 * \param[in] value The int value will be set in VSA.
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetAnalysisParameterInteger(char *measurement, char *parameter, int value);

//! Set VSA integer array before doing analysis
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_analysis_name "Analysis Name" for all available analysis names
 * \param[in] parameter The parameter will specify which VSA parameter will be set.
 * \param[in] value The Integer array will be set in VSA.
 * \param[in] valuesize The size of integer array.
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetAnalysisParameterIntegerArray(char *measurement, char *parameter, int *value, int valuesize);

//! Copy one VSA capture data to another
/*!
 * \param[in] fromVsaNum The VSA number from which data capture will be copied.  Valid values are 1,2,3, or 4.
 * \param[in] toVsaNum The VSA number to which data capture will be copied.  Valid values are 1,2,3, or 4.
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 * \remark Both VSAs have to contain capture data, with the same length.
 */
IQMEASURE_API int		LP_CopyVsaCaptureData(int fromVsaNum, int toVsaNum);

//! Saves the captured data to a file (.sig)
/*!
 * \param[in] sigFileName Specifies the .sig file name
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SaveVsaSignalFile(char *sigFileName);

//! Loads the signal file (.sig) for analysis
/*!
 * \param[in] sigFileName The path for the signal (.sig) file to be loaded
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_LoadVsaSignalFile(char *sigFileName);

//! Saves the captured data into .mod or .iqvsg(IQXel) (For VSG to play)
/*!
 * \param[in] modFileName The path for the signal (.mod) file to be saved
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 * \remark When a captured data is saved to a .mod file, the average power level will be normalized to 0dBm.
 */
IQMEASURE_API int		LP_SaveVsaGeneratorFile(char *modFileName);

//! Sets up VSA for Bluetooth data capturing
/*!
 * \param[in] rfFreqHz The center frequency of Bluetooth RF signal (Hz)
 * \param[in] rfAmplDb The amplitude of the peak power (dBm) of the signal
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1) (Default)
 *				- =3: Right RF port (RF2)
 *				- =4: Baseband
 * \param[in] triggerLevelDb The trigger level (dBm) used for signal trigger (ignored in Free-run and External Trigger Modes)
 * \param[in] triggerPreTime The pre-trigger time used for signal capture
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 * \remark For VSA to work optimally with the input signal, set rfAmplDb to the peak power of the input signal.
 */
IQMEASURE_API int		LP_SetVsaBluetooth(double rfFreqHz, double rfAmplDb, int port, double triggerLevelDb=-25, double triggerPreTime=10e-6);

//! Sets up VSA for data capturing
/*!
 * \param[in] rfFreqHz The center frequency of VSA (Hz)
 * \param[in] rfAmplDb The amplitude of the peak power (dBm) for VSA to work with
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1) (Default)
 *				- =3: Right RF port (RF2)
 *				- =4: Baseband
 * \param[in] extAttenDb The external attenuation (dB).  Set to 0 always.
 * \param[in] triggerLevelDb The trigger level (dBm) used for signal trigger (ignored in Free-run and External Trigger Modes)
 * \param[in] triggerPreTime The pre-trigger time used for signal capture
 * \param[in] dFreqShiftHz Frequency Shit
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 * \remark For VSA to work optimally with the input signal, set rfAmplDb to the peak power of the input signal.
 */
IQMEASURE_API int		LP_SetVsa(double rfFreqHz, double rfAmplDb, int port, double extAttenDb=0, double triggerLevelDb=-25, double triggerPreTime=10e-6, double dFreqShiftHz = 0.0);

IQMEASURE_API int		LP_SetVsaTriggerTimeout(double triggerTimeoutSec);

//! Sets up VSAs for IQnxn
/*!
 * \param[in] rfFreqHz The center frequency of VSA (Hz)
 * \param[in] rfAmplDb[4] The amplitude of the peak power (dBm) for VSA to work with.  A 4 double array.
 * \param[in] port[4] The port to which the VSG connects. A 4 integer array, with the following options for each element:
 *				- =1: OFF
 *				- =2: Left RF port (RF1) (Default)
 *				- =3: Right RF port (RF2)
 *				- =4: Baseband
 * \param[in] extAttenDb The external attenuation (dB).  Set to 0 always.
 * \param[in] triggerLevelDb The trigger level (dBm) used for signal trigger (ignored in Free-run and External Trigger Modes)
 * \param[in] triggerPreTime The pre-trigger time used for signal capture
 * \param[in] dFreqShiftHz Frequency Shit
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 * \remark For VSA to work optimally with the input signal, set rfAmplDb to the peak power of the input signal.
 */
IQMEASURE_API int		LP_SetVsaNxN(double rfFreqHz, double rfAmplDb[], int port[], double extAttenDb=0, double triggerLevelDb=-25, double triggerPreTime=10e-6, double dFreqShiftHz = 0.0);

//! Set Vsa amplitude tolerance in dB
/*!
 * \param[in] amplitudeToleranceDb, the setting of Vsa amplitude tolerance
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsaAmplitudeTolerance(double amplitudeToleranceDb);

//! Performs AGC (Automatic Gain Control) on VSA
/*!
 * \param[out] rfAmplDb The setting of rfAmplDb of VSA set by AGC
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_Agc(double *rfAmplDb, bool allTesters = true);

//! Sets up the number of frames for VSG to transmit
/*!
 * \param[in] frameCnt The number of frames to be transmitted between 0 and 65534, where "0" indicates continuous transmission
 *
 * \return ERR_OK if number of frames accepted; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetFrameCnt(int frameCnt);

IQMEASURE_API int		LP_TxDone(void);

//! Turn ON/OFF the first VSG RF
/*!
 * \param[in] enabled 1 to turn on the first VSG RF; 0 to turn off the first VSG RF
 *
 * \return ERR_OK if the first VSG RF is turned on or off; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_EnableVsgRF(int enabled);

//! Turn ON/OFF the VSG RF for IQnxn
/*!
 * \param[in] vsg1Enabled 1 to turn on the first VSG RF; 0 to turn off the first VSG RF
 * \param[in] vsg2Enabled 1 to turn on the second VSG RF; 0 to turn off the second VSG RF
 * \param[in] vsg3Enabled 1 to turn on the third VSG RF; 0 to turn off the third VSG RF
 * \param[in] vsg4Enabled 1 to turn on the fourth VSG RF; 0 to turn off the fourth VSG RF
 *
 * \return ERR_OK if the first VSG RF is turned on or off; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_EnableVsgRFNxN(int vsg1Enabled, int vsg2Enabled, int vsg3Enabled, int vsg4Enabled);

//! Turn ON/OFF the specified VSG RF
/*!
 * \param[in] enabled 1 to turn on the specified VSG RF; 0 to turn off the specified VSG RF
 * \param[in] vsgNumber The specified VSG.
 *
 * \return ERR_OK if the specified VSG RF is turned on or off; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_EnableSpecifiedVsgRF(int enabled, int vsgNumber);

//! Turn ON/OFF the specified VSA RF
/*!
 * \param[in] enabled 1 to turn on the specified VSA RF; 0 to turn off the specified VSA RF
 * \param[in] vsaNumber The specified VSA.
 *
 * \return ERR_OK if the specified VSA RF is turned on or off; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_EnableSpecifiedVsaRF(int enabled, int vsaNumber);

//! Return the VSA settings
/*!
 * \param[out] freqHz VSA frequency (Hz) setting
 * \param[out] ampl VSA amplitude (dBm);
 * \param[out] port VSA port: 1=PORT_OFF, 2=PORT_LEFT, 3=PORT_RIGHT, 4=PORT_BB;
 * \param[out] rfEnabled VSA RF state: 0=disalbed; 1=enabled
 * \param[out] triggerLevel VSA trigger level
 *
 * \return ERR_OK if the VSA settings are returned; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_GetVsaSettings(double *freqHz, double *ampl, IQAPI_PORT_ENUM *port, int *rfEnabled, double *triggerLevel);

//! Perform VSA data capture
/*!
 * \param[in] samplingTimeSecs Capture time in seconds
 * \param[in] triggerType Trigger type used for capturing.  Valid options are:
 *      - 1 = Free-run
 *      - 2 = External trigger
 *      - 6 = Signal Trigger
 * \param[optinal] modeHT40 Specifies if the capture is for the HT40 mask (802.11n only).  1--HT40 mask mode; 0--Normal mode
 *
 * \return ERR_OK if the data capture is successful; otherwise call LP_GetErrorString() for detailed error message.
 * \remark modeHT40 only needs to set to 1 if the HT40 mask (120MHz) analysis is desired.  For LP_Analyze80211n(), this flag can be set to 0.
 */
IQMEASURE_API int		LP_VsaDataCapture(double samplingTimeSecs, int triggerType=6, double sampleFreqHz=80e6,
									int ht40Mode=OFF, IQMEASURE_CAPTURE_NONBLOCKING_STATES nonBlockingState=BLOCKING );

//! Retrieves the captured I/Q raw data from VSA
/*!
 * \param[in] vsaNum Number of VSA (0-3)
 * \param[out] bufferReal[] Returns I samples
 * \param[out] bufferImag[] Returns Q samples
 * \param[in] bufferLength Indicates the length of bufferReal and bufferImag (in bytes)
 *
 * \return ERR_OK if no erros; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_GetSampleData(int vsaNum, double bufferReal[], double bufferImag[], int bufferLength);

//! Get memory addresses for a capture
/*!
 * \param[out] real[] Returns I samples.
 * \param[out] imag[] Returns Q samples.
 * \param[out] length[] Returnes length.
 * \param[in] arraySize Size of array real[], imag[], and length[]
 *
 * \return ERR_OK if no erros; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_GetHndlDataPointers(double *real[],double *imag[],int *length, double *sampleFreqHz, int arraySize);

//! Save I/Q samples in user's memory to LP sig file
/*!
 * \param[in] sigFileName The .sig file name
 * \param[in] real[] start pointer of I samples.
 * \param[in] imag[] start pointer of Q samples.
 * \param[in] length[] Length.
 * \param[in] arraySize Size of array real[], imag[], and length[]
 *
 * \return ERR_OK if no erros; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SaveUserDataToSigFile(char* sigFileName,
                                           double *real[],
                                           double *imag[],
                                           int *length,
                                           double *sampleFreqHz,
                                           int arraySize);

//! Select a portion of the capture for analysis
/*!
 * \param[in] startPositionUs Start position in the capture (us) for analysis
 * \param[in] lengthUs The length (us) in the capture for analysis
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SelectCaptureRangeForAnalysis(double startPositionUs, double lengthUs,
														 int packetsOffset = 0, int packetsLength = 0);
//! Send a SCPI command to IQxel tester
/*!
 * \param[in] The string of SCPI command
 * \return ERR_OK if no errors;
 */
IQMEASURE_API int		LP_ScpiCommandSet(char *scpiCommand);

//! Send a SCPI command to IQxel tester
/*!
 * \param[in] The string of query SCPI command
 * \param[in] The Max size of response message from IQxel
 * \param[out] Response from IQxel tester
 * \param[out] Actual size of response message from IQxel
 * \return ERR_OK if no errors;
*/
IQMEASURE_API int		LP_ScpiCommandQuery(char query[], unsigned int max_size, char response[], unsigned int *actual_size);

// Analysis Functions (TODO: Bluetooth)


//! Perform 802.16d Analysis on current capture
/*!
 * \param[in] sigType Indicates the type of signal. Default: -1
 *		      Valid values are as follows:
 *		      1=downlink signal
 *		      2=uplink signal
 *		     -1=auto-detect
 * \param[in] bandwidthHz Indicates signal bandwidth. Default: -1
 *		      Valid values for the signal bandwidth are as follows:
 *		      -1, 1.25, 1.5, 1.75, 2.5, 3, 3.5, 5, 5.5, 6, 7, 8.75, 10, 11, 12, 14, 15, 20
 *		      -1=auto detect
 * \param[in] cyclicPrefix Indicates signal cyclic prefix ratio. Default: -1
 *            Valid values for signal cyclic prefix ratio are as follows: -1, 1/4, 1/8, 1/16, 1/32
 *            -1=auto detect
 * \param[in] rateId Indicates signal modulation rate. Default: -1
 *            Valid values for signal modulation rate are as follows: 0, 1, 2, 3, 4, 5, 6 and
 *            correspond to {BPSK 1/2, QPSK 1/2, QPSK 3/4, 16-QAM 1/2, 16-QAM 3/4, 64-QAM 2/3, 64-QAM 3/4}, respectively
 *            -1=auto detect
 * \param[in] numSymbols Number of OFDM symbols in burst. Default: -1
 *            -1=auto detect
 * \param[in] ph_corr Phase Correction Mode with the following valid options:
 *         - 1: Phase correction off
 *         - 2: Symbol-by-symbol correction (Default)
 *         - 3: Moving avg. correction (10 symbols)
 * \param[in] ch_corr Channel Estimate with the following options:
 *         - 1: Raw Channel Estimate (based on long trainling symbols) (Default)
 *         - 2: 2nd Order Polyfit
 *         - 3: Full packet estimate
 * \param[in] freq_corr Frequency Sync. Mode with the following options:
 *         - 1: Short Training Symbol
 *         - 2: Long Training Symbol (Default)
 *         - 3: Full Data Packet
 * \param[in] timing_corr Symbol Timing Correction with the following options:
 *         - 1: Symbol Timing Correction Off
 *         - 2: Symbol Timing Correction ON (Default)
 * \param[in] ampl_track Amplitude Tracking with the following options:
 *         - 1: Amplitude tracking off (Default)
 *         - 2: Amplitude tracking on
 * \param[in] decode Decode the payload or not //TODO: check decode
 *         - 0: Decode OFF (Default)
 *         - 1: Decode ON
 *
 * \return ERR_OK if the 802.16d analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_Analyze80216d( double sigType		= -1,
								    double bandwidthHz	= -1,
									double cyclicPrefix	= -1,
									double rateId		= -1,
									double numSymbols	= -1,
								    int ph_corr			= 2,
								    int ch_corr			= 1,
								    int freq_corr		= 2,
								    int timing_corr		= 2,
								    int ampl_track		= 1,
								    double decode		= 0
								    );

//! Perform 802.16e Analysis on current capture
/*!
 * \param[in] sigType Indicates the type of signal. Default: -1
 *		      Valid values are as follows:
 *		      1=downlink signal
 *		      2=uplink signal
 *		     -1=auto-detect
 * \param[in] bandwidthHz Indicates signal bandwidth. Default: -1
 *		      Valid values for the signal bandwidth are as follows:
 *		      -1, 1.25, 1.5, 1.75, 2.5, 3, 3.5, 5, 5.5, 6, 7, 8.75, 10, 11, 12, 14, 15, 20
 *		      -1=auto detect
 * \param[in] cyclicPrefix Indicates signal cyclic prefix ratio. Default: -1
 *            Valid values for signal cyclic prefix ratio are as follows: -1, 1/4, 1/8, 1/16, 1/32
 *            -1=auto detect
 * \param[in] rateId Indicates signal modulation rate. Default: -1
 *            Valid values for signal modulation rate are as follows: 0, 1, 2, 3, 4, 5, 6 and
 *            correspond to {BPSK 1/2, QPSK 1/2, QPSK 3/4, 16-QAM 1/2, 16-QAM 3/4, 64-QAM 2/3, 64-QAM 3/4}, respectively
 *            -1=auto detect
 * \param[in] numSymbols Number of OFDM symbols in burst. Default: -1
 *            -1=auto detect
 * \param[in] ph_corr Phase Correction Mode with the following valid options:
 *         - 1: Phase correction off
 *         - 2: Symbol-by-symbol correction (Default)
 *         - 3: Moving avg. correction (10 symbols)
 * \param[in] ch_corr Channel Estimate with the following options:
 *         - 1: Raw Channel Estimate (based on long trainling symbols) (Default)
 *         - 2: 2nd Order Polyfit
 *         - 3: Full packet estimate
 * \param[in] freq_corr Frequency Sync. Mode with the following options:
 *         - 1: Short Training Symbol
 *         - 2: Long Training Symbol (Default)
 *         - 3: Full Data Packet
 * \param[in] timing_corr Symbol Timing Correction with the following options:
 *         - 1: Symbol Timing Correction Off
 *         - 2: Symbol Timing Correction ON (Default)
 * \param[in] ampl_track Amplitude Tracking with the following options:
 *         - 1: Amplitude tracking off (Default)
 *         - 2: Amplitude tracking on
 * \param[in] decode Decode the payload or not //TODO: check decode
 *         - 0: Decode OFF (Default)
 *         - 1: Decode ON
 * \param[in] map_conf_file The map configuration file.
 *
 * \return ERR_OK if the 802.16e analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_Analyze80216e( double sigType		= -1,
								    double bandwidthHz	= -1,
									double cyclicPrefix	= -1,
									double rateId		= -1,
									double numSymbols	= -1,
								    int ph_corr			= 2,
								    int ch_corr			= 1,
								    int freq_corr		= 2,
								    int timing_corr		= 2,
								    int ampl_track		= 1,
								    double decode		= 0,
								    char *map_conf_file = NULL
									);

//! Perform 802.11p Analysis on current capture
/*!
 * \param[in] ph_corr_mode Phase Correction Mode with the following valid options:
 *         - 1: Phase correction off
 *         - 2: Symbol-by-symbol correction (Default)
 *         - 3: Moving avg. correction (10 symbols)
 * \param[in] ch_estimate Channel Estimate with the following options:
 *         - 1: Raw Channel Estimate (based on long trainling symbols) (Default)
 *         - 2: 2nd Order Polyfit
 *         - 3: Full packet estimate
 * \param[in] sym_tim_corr Symbol Timing Correction with the following options:
 *         - 1: Symbol Timing Correction Off
 *         - 2: Symbol Timing Correction ON (Default)
 * \param[in] freq_sync Frequency Sync. Mode with the following options:
 *         - 1: Short Training Symbol
 *         - 2: Long Training Symbol (Default)
 *         - 3: Full Data Packet
 * \param[in] ampl_track Amplitude Tracking with the following options:
 *         - 1: Amplitude tracking off (Default)
 *         - 2: Amplitude tracking on
 * \param[in] ofdm_mode Specifies OFDM mode with the following options:
 *         - 0: OFDM mode based on IEEE 802.11a or 802.11g standards specification
 *         - 1: OFDM turbo mode based on IEEE 802.11a or 802.11g standards specification
 *         - 2: ASTM DSRC standards specification (Default)
 *         - 3: OFDM quarter rate
 *
 * \return ERR_OK if the 802.11p analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int LP_Analyze80211p(int ph_corr_mode=2, int ch_estimate=1, int sym_tim_corr=2, int freq_sync=2, int ampl_track=1, int ofdm_mode=2);

//! Perform 802.11 a/g Analysis on current capture
/*!
 * \param[in] ph_corr_mode Phase Correction Mode with the following valid options:
 *         - 1: Phase correction off
 *         - 2: Symbol-by-symbol correction (Default)
 *         - 3: Moving avg. correction (10 symbols)
 * \param[in] ch_estimate Channel Estimate with the following options:
 *         - 1: Raw Channel Estimate (based on long trainling symbols) (Default)
 *         - 2: 2nd Order Polyfit
 *         - 3: Full packet estimate
 * \param[in] sym_tim_corr Symbol Timing Correction with the following options:
 *         - 1: Symbol Timing Correction Off
 *         - 2: Symbol Timing Correction ON (Default)
 * \param[in] freq_sync Frequency Sync. Mode with the following options:
 *         - 1: Short Training Symbol
 *         - 2: Long Training Symbol (Default)
 *         - 3: Full Data Packet
 * \param[in] ampl_track Amplitude Tracking with the following options:
 *         - 1: Amplitude tracking off (Default)
 *         - 2: Amplitude tracking on
 * \param[in] prePowStartSec indicates the start point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
          - 8.8e-6: 8.8 micro second (Default)
 * \param[in] prePowStopSec indicates the end point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
 *        - 15.2e-6: 15.2 micro second (Default)
 *
 * \return ERR_OK if the 802.11 a/g analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_Analyze80211ag(int ph_corr_mode=2, int ch_estimate=1, int sym_tim_corr=2, int freq_sync=2, int ampl_track=1, double prePowStartSec = 8.8e-6, double prePowStopSec = 15.2e-6);

//! Perform 802.11 n Analysis on current capture
/*!
 * \param[in] type only "EWC" is supported
 * \param[in] mode Valid options are:
 *         - "nxn": for true 802.11n capture
 *         - "composite: for a composite capture
 *         - "sequential_mimo": for a switched capture
 * \param[in] enablePhaseCorr Phase Correction Mode:
 *         - 0: Disable
 *         - 1: Enable (Default)
 * \param[in] enableSymTimingCorr Symbol Timing Correction:
 *         - 0: Disable
 *         - 1: Enable (Default)
 * \param[in] enableAmplitudeTracking Amplitude Tracking:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] decodePSDU Decode PSDU:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] enableFullPacketChannelEst Channel Estimate on full packet:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] referenceFile PSDU reference file (needed for Composite EVM)
 * \param[in] packetFormat indicates format of the 80211n MIMO packet:
 *         - 0: auto-detect mode (Default)
 *         - 1: mixed format
 *         - 2: greenfield format
 * \param[in] frequency Correction options 
 *         - 2 = frequency correction on short and long legacy training fields (default)
 *         - 3 = frequency correction based on full packet
 *		   - 4 = frequency correction on signal fields (legacy and HT) in addition to short and long training fields
 * \param[in] prePowStartSec indicates the start point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
           - 8.8e-6: 8.8 micro second (Default)
 * \param[in] prePowStopSec indicates the end point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
 *         - 15.2e-6: 15.2 micro second (Default)
 *
 * \return ERR_OK if the 802.11n analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_Analyze80211n(char *type,
                                   char *mode,
                                   int enablePhaseCorr            = 1,
                                   int enableSymTimingCorr        = 1,
                                   int enableAmplitudeTracking    = 0,
                                   int decodePSDU                 = 0,
                                   int enableFullPacketChannelEst = 0,
                                   char *referenceFile=NULL,
                                   int packetFormat = 0,
								   int frequencyCorr = 2,
								   double prePowStartSec = 8.8e-6,
								   double prePowStopSec = 15.2e-6);

// LP_AnalyzeMimo has been replaced by LP_Analyze802.11n
IQMEASURE_API int		LP_AnalyzeMimo(char *type, char *mode, int enablePhaseCorr, int enableSymTimingCorr, int enableAmplitudeTracking, int decodePSDU, int enableFullPacketChannelEst, char *referenceFile);


//! Perform 802.11b Analysis on current capture
/*!
 * \param[in] eq_taps Number of equalizer taps, valid options are:
 *         - 1: Equalizer Off	(Default)
 *         - 5: 5 Taps Equalizer
 *         - 7: 7 Taps Equalizer
 *         - 9: 9 Taps Equalizer
 * \param[in] DCremove11b_flag DC removal, valid options are:
 *         - 0: DC Removal OFF (Default)
 *         - 1: DC Removal ON
 * \param[in] method_11b 802.11b method, valid options are:
 *         - 1: Use 11b standard TX accuracy (Default)
 *         - 2: Use 11b RMS error vector
 * \param[in] prePowStartSec indicates the start point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
          - 8.8e-6: 8.8 micro second (Default)
 * \param[in] prePowStopSec indicates the end point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
 *        - 15.2e-6: 15.2 micro second (Default)
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_Analyze80211b(int eq_taps          = 1,
                                   int DCremove11b_flag = 0,
                                   int method_11b       = 1,
								   double prePowStartSec = 8.8e-6,
								   double prePowStopSec = 15.2e-6);

//! Perform power Analysis on current capture
/*!
 * \param[in] T_interval Gap between packets (bursts).  Ignored
 * \param[in] max_pow_diff_dB Power difference between noise floor and packets.  Ignored
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzePower(double T_interval=0.0, double max_pow_diff_dB=0.0);

//! Perform Generic FFT Analysis on current capture
/*!
 * \param[in] NFFT Number of FFT.  Default to 0
 * \param[in] res_bw Resolution bandwidth.  Default to 100KHz
 * \param[in] window_type FFT window type.  Default to NULL
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzeFFT(double NFFT=0, double res_bw=100e3, char *window_type=NULL);

//! Perform CCDF Analysis on current capture
/*!
 * \return ERR_OK if the CCDE analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzeCCDF();

//! Perform CW Frequency Analysis on current capture (Replaced by LP_AnalyzeCWFreq)
/*!
 * \return ERR_OK if the CW analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzeCW();

//! Perform CW Frequency Analysis on current capture
/*!
 * \return ERR_OK if the CW analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzeCWFreq();

//! Perform Wave Analysis on current capture //TODO: what are results from AnalysisWave()?
/*!
 * \return ERR_OK if the Wave analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalysisWave();

//! Perform Sidelobe Analysis on current capture
/*!
 * \return ERR_OK if the Sidelobe analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzeSidelobe();

//! Perform Power Ramp Analysis (OFDM) on current capture
/*!
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzePowerRampOFDM();

//! Perform Power Ramp Analysis (80211b) on current capture
/*!
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzePowerRamp80211b();

//! Perform Bluetooth Analysis on current capture
/*!
 * \param[in] data_rate, Bluetooth data rate, with the following options:
 *         - 1: 1Mbit/s BDR
 *         - 2: 2Mbit/s EDR
 *         - 3: 3Mbit/s EDR
 *         - 0: Auto detect
 * \param[in] analysis_type, Specifies what type of analysis to perform. Default: 'All'. Valid values are as follows:
 *         - PowerOnly
 *         - 20dbBandwidthOnly
 *         - PowerandFreq
 *         - All  (This is the set default value)
 *		   - ACP  (only does the new ACP analysis)
 *		   - AllPlus  (performs all the analyses that are done by ��All?plus the ACP analysis)
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_AnalyzeBluetooth(double data_rate, char *analysis_type="All"  );

//! Perform Zigbee Analysis Analysis on current capture
/*!
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */

IQMEASURE_API int		LP_AnalyzeZigbee();

//! Perform HT40 mask (120MHz) analysis
/*!
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 * \remark Before calling LP_AnalyzeHT40Mask(), modeHT40 needs to set to 1 in LP_VsaDataCapture().
 */
IQMEASURE_API int		LP_AnalyzeHT40Mask();

/*****************************/
/* Result Handling Functions */
/*****************************/


// The following three functions are obsoleted due to the type.
IQMEASURE_API double	LP_GetScalarMeasurment(char *measurement, int index=0);
IQMEASURE_API int		LP_GetVectorMeasurment(char *measurement, double bufferReal[], double bufferImag[], int bufferLength);
IQMEASURE_API int		LP_GetStringMeasurment(char *measurement, char bufferChar[], int bufferLength);

//! Get a scalar measurement result
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_scalar_measurement "Scalar Measurements" for all available measurement names
 * \param[in] index The index of the measurement.  In most case, index would be zero.  For MIMO analysis, some measurements, such as EVM, may have more than one results
 *
 * \return The value of the measurement.  -99999.99 (a special defined negative value) will be returned if no measurement available
 */
IQMEASURE_API double	LP_GetScalarMeasurement(char *measurement, int index=0);

//! Get a vector measurement result
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_vector_measurement "Vector Measurements" for all available measurement names
 * \param[out] bufferReal Returns the real part of vector
 * \param[out] bufferImag Returns the imag part of vector
 * \param[in] bufferLength Indicates the length of bufferReal and bufferImag (in Bytes)
 *
 * \return The number of elements in bufferReal or/and bufferImag
 */
IQMEASURE_API int		LP_GetVectorMeasurement(char *measurement, double bufferReal[], double bufferImag[], int bufferLength);

//! Get a string measurement result
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_string_measurement "String Measurements" for all available measurement names
 * \param[out] bufferChar Returns the string result
 * \param[in] bufferLength Indicates the length of bufferChar (in Bytes)
 *
 * \return The number of elements in bufferChar
 */
IQMEASURE_API int		LP_GetStringMeasurement(char *measurement, char bufferChar[], int bufferLength);

/***********************/
/* Debugging Functions */
/***********************/

//! Plot the data capture
/*!
 * \return ERR_OK
 */
IQMEASURE_API int		LP_PlotDataCapture();
IQMEASURE_API int		LP_Plot(int figNum, double *x, double *y, int length, char *plotArgs, char *title, char *xtitle, char *ytitle, int keepPlot=0);

//! Start IQmeasure internal timer
/*!
 * \return ERR_OK
 */
IQMEASURE_API int		LP_StartIQmeasureTimer();

//! Stop IQmeasure internal timer
/*!
 * \return ERR_OK
 */

IQMEASURE_API int		LP_StopIQmeasureTimer();
//! Start IQmeasure internal timer
/*!
 * \return ERR_OK
 */
IQMEASURE_API int		LP_ReportTimerDurations();


/*-------------------------*
*	IQ2010 Ext Functions   *
*--------------------------*/
//--

/*! @defgroup group_scalar_measurement Measurement Names for IQ2010EXT_GetDoubleMeasurements(), IQ2010EXT_GetStringMeasurement(), IQ2010EXT_GetVectorMeasurement(), IQ2010EXT_GetIntMeasurement()
 *
 * Available measurement names vary for various analysis.  After an analysis has been performed successfully, by calling one of the following functions:
 *   - IQ2010EXT_Analyze80211ag();
 *   - IQ2010EXT_Analyze80211nSISO();
 *   - IQ2010EXT_Analyze80211nComposite();
 *   - IQ2010EXT_Analyze80211b();
 *   - IQ2010EXT_AnalyzePower();
 *   - IQ2010EXT_AnalyzeFFT();
 *   - IQ2010EXT_AnalyzePowerRamp80211b();
 *   - IQ2010EXT_AnalyzeBluetooth();
 *   - IQ2010EXT_AnalyzeSpectralMeasurement();
 *   - IQ2010EXT_AnalyzeMaskMeasurement();
 *   - IQ2010EXT_AnalyzeSpectralMeasurement();
 *
 * \section analysis_80211ag Measurement Names for IQ2010EXT_Analyze80211ag() and IQ2010EXT_AnalyzeSpectralMeasurement() with spectral type 'IQ2010EXT_SPECTRAL_11AG'
 *  - <b>evmAll</b>:  EVM for entire frame.  index value: 0
 *  - <b>evmData</b>:  EVM for data part of the frame.  index value: 0
 *  - <b>evmPilot</b>:  EVM of all pilot part of the frame.  index value: 0
 *  - <b>codingRate</b>:  Coding Rate in the capture.  index value: 0
 *  - <b>freqErr</b>:  Frequency Error in the capture.  index value: 0
 *  - <b>clockErr</b>:  Symbol Clock Error in the capture.  index value: 0
 *  - <b>ampErr</b>:  IQ Match Amplitude Error in the capture.  index value: 0
 *  - <b>ampErrDb</b>:  IQ Match Amplitude Error in dB in the capture.  index value: 0
 *  - <b>phaseErr</b>:  IQ Match Phase Error in the capture.  index value: 0
 *  - <b>rmsPhaseNoise</b>:  Frequency RMS Phase Noise in rms in the capture.  index value: 0
 *  - <b>rmsPowerNoGap</b>:  RMS Power No Gap in the capture.  index value: 0
 *  - <b>rmsPower</b>:  RMS Power in the capture.  index  value: 0
 *  - <b>pkPower</b>:  Peak power in the capture.  index value: 0
 *  - <b>rmsMaxAvgPower</b>:  Average max RMS power in the capture.  index value: 0
 *  - <b>psduCrcFail</b>:  1 = PSDU CRC Check Failed, 0 = PSDU CRC Check Passed.  index value: 0
 *  - <b>plcpCrcPass</b>:  1 = PLCP CRC Check Passed, 0 = PLCP CRC Check Failed.  index value: 0
 *  - <b>dataRate</b>:  Data rate in Mbps in the capture.  index value: 0
 *  - <b>numSymbols</b>:  Number of Symbols in the capture.  index value: 0
 *  - <b>numPsduBytes</b>:  Number of bytes in PSDU.  index value: 0
 *  - <b>SUBCARRIER_LO_B_VSA1</b>:  Subcarrier number for lower region B ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_LO_B_VSA1</b>:  Value at worst margin for lower region B (tester VSA 1).  index value: 0
 *  - <b>SUBCARRIER_LO_A_VSA1</b>:  Subcarrier number for lower region A ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_LO_A_VSA1</b>:  Value at worst margin for lower region A (tester VSA 1).  index value: 0
 *  - <b>SUBCARRIER_UP_A_VSA1</b>:  Subcarrier number for upper region A ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_UP_A_VSA1</b>:  Value at worst margin for upper region A (tester VSA 1).  index value: 0
 *  - <b>SUBCARRIER_UP_B_VSA1</b>:  Subcarrier number for upper region B ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_UP_B_VSA1</b>:  Value at worst margin for upper region B (tester VSA 1).  index value: 0
 *  - <b>LO_LEAKAGE_DBR_VSA1</b>:  LO leakage (tester VSA 1).  index value: 0
 *
 * \section analysis_mimo Measurement Names for IQ2010EXT_Analyze80211nSISO, IQ2010EXT_Analyze80211nComposite() and IQ2010EXT_AnalyzeSpectralMeasurement() with 11N spectral type ( like, IQ2010EXT_SPECTRAL_11N_HT20 or IQ2010EXT_SPECTRAL_11N_HT40 )
 *  - <b>evmAvgAll</b>:  Average EVM of all symbols per stream in the capture. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>packetDetection</b>:  Indicates at least one valid packet detected. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>psduCRC</b>:  Indicates valid CRC on PSDU. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>acquisition</b>:  Indicates at least one valid HT packet detected. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>demodulation</b>:  Indicates demodulated streams (packet may be truncated). Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>dcLeakageDbc</b>:  DC Leakage in dBc per RX. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>rxRmsPowerDb</b>:  RMS power of estimated channels per stream. Dimension is NStreams X NRx. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>freqErrorHz</b>:  Frequency error in Hz. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>symClockErrorPpm</b>:  Symbol clock error in ppm. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>PhaseNoiseDeg_RmsAll</b>:  RMS phase noise, over all received signals. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>IQImbal_amplDb</b>:  IQ gain imbalance in dB per stream. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>IQImbal_phaseDeg</b>:  IQ phase imbalance in degree per stream. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>rateInfo_bandwidthMhz</b>:  Bandwidth in MHz. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>rateInfo_dataRateMbps</b>:  Data Rate in Mbps. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>rateInfo_spatialStreams</b>:  Number in spatial streams. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>analyzedRange</b>:  Start and end point of the signal part that was used for analysis. The API picks the first packet in the input signal for analysis; the following packets are ignored. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>htSig1_htLength</b>:  Information from HT-SIG1: value in Length field as decimal number. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>htSig1_mcsIndex</b>:  Information from HT-SIG1: MCS index as a decimal number. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>htSig1_bandwidth</b>:  Information from HT-SIG1: bandwidth (0) 20MHz (1) 40MHz. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>htSig2_advancedCoding</b>:  Information from HT-SIG2: advanced coding. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>rateInfo_spaceTimeStreams</b>:  Number in Space-Time Streams. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>SUBCARRIER_LO_B_VSA1</b>:  Subcarrier number for lower region B ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_LO_B_VSA1</b>:  Value at worst margin for lower region B (tester VSA 1).  index value: 0
 *  - <b>SUBCARRIER_LO_A_VSA1</b>:  Subcarrier number for lower region A ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_LO_A_VSA1</b>:  Value at worst margin for lower region A (tester VSA 1).  index value: 0
 *  - <b>SUBCARRIER_UP_A_VSA1</b>:  Subcarrier number for upper region A ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_UP_A_VSA1</b>:  Value at worst margin for upper region A (tester VSA 1).  index value: 0
 *  - <b>SUBCARRIER_UP_B_VSA1</b>:  Subcarrier number for upper region B ( tester VSA 1 ).  index value: 0
 *  - <b>VALUE_DB_UP_B_VSA1</b>:  Value at worst margin for upper region B (tester VSA 1).  index value: 0
 *  - <b>LO_LEAKAGE_DBR_VSA1</b>:  LO leakage (tester VSA 1).  index value: 0
 *
 * \section analysis_80211b Measurement Names for IQ2010EXT_Analyze80211b()
 *  - <b>evmPk</b>:  EVM peak value of all symbols in the capture.  index value: 0
 *  - <b>evmAll</b>:  EVM for entire frame in the capture.  index value: 0
 *  - <b>evmInPreamble</b>:  EVM in the preamble of the capture.  index value: 0
 *  - <b>evmInPsdu</b>:  EVM in the PSDU of the capture.  index value: 0
 *  - <b>freqErr</b>:  Frequency Error in the capture.  index value: 0
 *  - <b>clockErr</b>:  Symbol Clock Error in the capture.  index value: 0
 *  - <b>ampErr</b>:  IQ Match Amplitude Error in the capture.  index value: 0
 *  - <b>ampErrDb</b>:  IQ Match Amplitude Error in the capture; specified in dB  index value: 0
 *  - <b>phaseErr</b>:  IQ Match Phase Error in the capture.  index value: 0
 *  - <b>rmsPhaseNoise</b>:  Frequency RMS Phase Noise in the capture.  index value: 0
 *  - <b>rmsPowerNoGap</b>:  RMS Power No Gap in the capture.  index value: 0
 *  - <b>rmsPower</b>:  RMS Power in the capture.  index value: 0
 *  - <b>pkPower</b>:  Peak power in the capture.  index value: 0
 *  - <b>rmsMaxAvgPower</b>:  Average max RMS power in the capture.  index value: 0
 *  - <b>bitRate</b>:  Bit Rate, see 802.11b standard.  index value: 0
 *  - <b>modType</b>:  Mod Type, see 802.11b standard.  index value: 0
 *  - <b>valid</b>:  Checks if the capture is valid.  index value: 0
 *  - <b>P_av_each_burst</b>:  Average power of each burst in the capture.  index value: 0
 *  - <b>P_pk_each_burst</b>:  Peak power of each burst in the capture.  index value: 0
 *  - <b>P_av_all</b>:  Average power in the capture.  index value: 0
 *  - <b>P_peak_all</b>:  Peak power in the capture.  index value: 0
 *  - <b>P_av_no_gap_all</b>:  Average power with no gap in the capture.  index value: 0
 *  - <b>P_av_all_dBm</b>:  Average power in the capture; specified in dBm.  index value: 0
 *  - <b>P_peak_all_dBm</b>:  Peak power in the capture; specified in dBm.  index value: 0
 *  - <b>P_av_no_gap_all_dBm</b>:  Average power with no gap in the capture; specified in dBm  index value: 0
 *  - <b>lockedClock</b>:  Locked Clock, see 802.11b standard.  index value: 0
 *  - <b>plcpCrcFail</b>:  1 = PLCP CRC Check Failed, 0 = PLCP CRC Check Passes.  index value: 0
 *  - <b>psduCrcFail</b>:  1 = PSDU CRC Check Failed, 0 = PSDU CRC Check Passes.  index value: 0
 *  - <b>longPreamble</b>:  1 = Long Preamble, 0 = Short Preamble.  index value: 0
 *  - <b>bitRateInMHz</b>:  Bit rate in Mhz in the capture.  index value: 0
 *  - <b>loLeakageDb</b>:  LO leakage in dBc.  index value: 0
 *  - <b>MaxfreqErr</b>:  Maximum frequency error.  index value: 0
 *
 * \section analysis_Power Measurement Names for IQ2010EXT_AnalyzePower()
 *  - <b>valid</b>:  Indicates valid results (1 valid, 0 invalid).  index value: 0
 *  - <b>P_av_each_burst</b>:  Average power of each burst in the capture.  index value: 0
 *  - <b>P_pk_each_burst</b>:  Peak power of each burst in the capture.  index value: 0
 *  - <b>P_av_all</b>:  Average power of whole capture.  index value: 0
 *  - <b>P_peak_all</b>:  Peak power of whole capture.  index value: 0
 *  - <b>P_av_no_gap_all</b>:  Average power with no gap in the capture.  index value: 0
 *  - <b>P_av_all_dBm</b>:  Average power of whole capture; specified in dBm.  index value: 0
 *  - <b>P_peak_all_dBm</b>:  Peak power of whole capture; specified in dBm.  index value: 0
 *  - <b>P_av_no_gap_all_dBm</b>:  Average power, not counting gaps in dBm.  index value: 0
 *
 * \section analysis_FFT Measurement Names for IQ2010EXT_AnalyzeFFT()
 *  - <b>valid</b>:  Returns (value) whether results are valid or not. 1 valid, 0 invalid.  index value: 0
 *  - <b>length</b>:  Returns length of X and Y Vectors above.  index value: 0
 *
 * \section analysis_Bluetooth Measurement Names for IQ2010EXT_AnalyzeBluetooth()
 *  - <b>dataRateDetect</b>:  Detects which data rate is in capture.  index value: 0
 *  - <b>valid</b>:  Flag indicating whether or not the power portion of the Bluetooth analysis was successful (1), or not (0).  index value: 0
 *  - <b>bandwidth20dB</b>:   20 dB bandwidth value Hz.  index value: 0
 *  - <b>deltaF1Average</b>:  The measurement result for deltaF1Avg as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2. Requires 00001111 data pattern. Results in Hz.  index value: 0
 *  - <b>deltaF2Max</b>:  The measurement result for deltaF2Max as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2. Requires alternating data pattern. Results in Hz.  index value: 0
 *  - <b>deltaF2Average</b>:  The measurement result for deltaF2Avg as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2. Requires alternating data pattern. Results in Hz.  index value: 0
 *  - <b>deltaF2MaxAccess</b>:  Similar to the measurement result for deltaF2Max as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2. Results measured from Access data. Results in Hz.  index value: 0
 *  - <b>deltaF2AvAccess</b>:  Similar to the measurement result for deltaF2Avg as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2. Results measured from Access data. Results in Hz.  index value: 0
 *  - <b>EdrEVMAv</b>:  RMS Differential EVM value (EDR only).  index value: 0
 *  - <b>EdrEVMpk</b>:  Peak Differential EVM value (EDR only).  index value: 0
 *  - <b>EdrEVMvalid</b>:  Indicates validity of EDR EVM Measurements.  index value: 0
 *  - <b>EdrPowDiffdB</b>:  Relative power of EDR section to FM section of packet, in dB.  index value: 0
 *  - <b>freq_deviation</b>:  Similar to the measurement result for deltaF1Avg as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2.
 *					  Results measured from Header data. Results in Hz.  index value: 0
 *  - <b>freq_deviationpktopk</b>:  Peak to Peak Frequency Deviation, in Hz during header.  index value: 0
 *  - <b>freq_estHeader</b>:  Estimates the Frequency Offset during the Header in Hz.  index value: 0
 *  - <b>EdrFreqExtremeEdronly</b>:  Reports the extreme value of the frequency variation during DPSK in Hz. Does not include the offset during the header.  index value: 0
 *  - <b>EdrprobEVM99pass</b>:  The percentage of symbols with EVM below the threshold. Threshold for 2 Mbps is 0.3 for 3 Mbps is 0.2.  index value: 0
 *  - <b>EdrEVMvsTime</b>:  Max DEVM Average as specified in BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2.  index value: 0
 *  - <b>validInput</b>:  Indicates whether or not the input wave was valid.  index value: 0
 *  - <b>maxfreqDriftRate</b>:  1 Mbps only, takes the maximum drift over specified time interval.  index value: 0
 *  - <b>payloadErrors</b>:  Reports the number of data errors in Payload. Not counting CRC. If -1, this value has not been calculated.
 *					 If larger negative number, it reports the length of the payload data vector. This happens when the length of the payload vector is shorter than the length indicated in the payload header.  index value: 0
 *
 * \section analysis_mask Measurement Names for IQ2010EXT_AnalyzeMaskMeasurement() with mask type WIFI_11B
 *  - <b>FREQ_MHZ_LO_B_VSA1</b>:    frequency (M Hz) in region LO_B at worst margin
 *  - <b>MARGIN_DB_LO_B_VSA1</b>:   power (Db) in region LO_B at worst margin
 *  - <b>FREQ_MHZ_LO_A_VSA1</b>:    frequency (M Hz) in region LO_A at worst margin
 *  - <b>MARGIN_DB_LO_A_VSA1</b>:   power (Db) in region LO_A at worst margin
 *  - <b>FREQ_MHZ_UP_A_VSA1</b>:    frequency (M Hz) in region UP_A at worst margin
 *  - <b>MARGIN_DB_UP_A_VSA1</b>:   power (Db) in region UP_A at worst margin
 *  - <b>FREQ_MHZ_UP_B_VSA1</b>:    frequency (M Hz) in region UP_B at worst margin
 *  - <b>MARGIN_DB_UP_B_VSA1</b>:   power (Db) in region UP_B at worst margin
 *  - <b>OBW_MHZ_VSA1</b>:          Occupied Bandwidth measurement in MHz
 *
 * \section analysis_mask Measurement Names for IQ2010EXT_AnalyzeMaskMeasurement() with mask type WIFI_11AG, WIFI_11N_HT20 and WIFI_11N_HT40
 *  - <b>FREQ_MHZ_LO_D_VSA1</b>:    frequency (M Hz) in region LO_D at worst margin
 *  - <b>MARGIN_DB_LO_D_VSA1</b>:   power (Db) in region LO_D at worst margin
 *  - <b>FREQ_MHZ_LO_C_VSA1</b>:    frequency (M Hz) in region LO_C at worst margin
 *  - <b>MARGIN_DB_LO_C_VSA1</b>:   power (Db) in region LO_C at worst margin
 *  - <b>FREQ_MHZ_LO_B_VSA1</b>:    frequency (M Hz) in region LO_B at worst margin
 *  - <b>MARGIN_DB_LO_B_VSA1</b>:   power (Db) in region LO_B at worst margin
 *  - <b>FREQ_MHZ_LO_A_VSA1</b>:    frequency (M Hz) in region LO_A at worst margin
 *  - <b>MARGIN_DB_LO_A_VSA1</b>:   power (Db) in region LO_A at worst margin
 *  - <b>FREQ_MHZ_UP_A_VSA1</b>:    frequency (M Hz) in region UP_A at worst margin
 *  - <b>MARGIN_DB_UP_A_VSA1</b>:   power (Db) in region UP_A at worst margin
 *  - <b>FREQ_MHZ_UP_B_VSA1</b>:    frequency (M Hz) in region UP_B at worst margin
 *  - <b>MARGIN_DB_UP_B_VSA1</b>:   power (Db) in region UP_B at worst margin
 *  - <b>FREQ_MHZ_UP_C_VSA1</b>:    frequency (M Hz) in region UP_C at worst margin
 *  - <b>MARGIN_DB_UP_C_VSA1</b>:   power (Db) in region UP_C at worst margin
 *  - <b>FREQ_MHZ_UP_D_VSA1</b>:    frequency (M Hz) in region UP_D at worst margin
 *  - <b>MARGIN_DB_UP_D_VSA1</b>:   power (Db) in region UP_D at worst margin
 *  - <b>OBW_MHZ_VSA1</b>:          Occupied Bandwidth measurement in MHz
 *
 * \section analysis_spectral Measurement Names for IQ2010EXT_AnalyzeSpectralMeasurement() with spectral type IQ2010EXT_SPECTRAL_11AG, IQ2010EXT_SPECTRAL_11N_HT20, IQ2010EXT_SPECTRAL_11N_HT40 and IQ2010EXT_SPECTRAL_11N
 *  - <b>SUBCARRIER_LO_B_VSA1</b>:  Subcarrier number in region LO_B at worst margin
 *  - <b>VALUE_DB_LO_B_VSA1</b>:    power (Db) in region LO_B at worst margin
 *  - <b>SUBCARRIER_LO_A_VSA1</b>:  Subcarrier number in region LO_A at worst margin
 *  - <b>VALUE_DB_LO_A_VSA1</b>:    power (Db) in region LO_A at worst margin
 *  - <b>SUBCARRIER_UP_B_VSA1</b>:  Subcarrier number in region UP_B at worst margin
 *  - <b>VALUE_DB_UP_B_VSA1</b>:    power (Db) in region UP_B at worst margin
 *  - <b>SUBCARRIER_UP_A_VSA1</b>:  Subcarrier number in region UP_A at worst margin
 *  - <b>VALUE_DB_UP_A_VSA1</b>:    power (Db) in region UP_A at worst margin
 *  - <b>LO_LEAKAGE_DBR_VSA1</b>:   LO leakage
 *
 * \section Rx per Measurement names for IQ2010EXT_RxPer()
 *  - <b>powerLeveldBm</b>:  powerLeveldBm the actual power levels for each enabled port at each power level
 *  - <b>ackRespMaxUs</b>:  ackRespMaxUs maximmum ack response time in us
 *  - <b>ackRespMinUs</b>:  ackRespMinUs minimum ack response time in us
 *  - <b>perPercent</b>:  perPercent the PER result at each power level (%)
 *
 */

/*! @defgroup group_vector_measurement Measurement Names for IQ2010EXT_GetVectorMeasurement()
 *
 * Available measurement names vary for various analysis.  After an analysis has been performed successfully, by calling
 * one of the following functions:
 *   - IQ2010EXT_Analyze80211ag();
 *   - IQ2010EXT_Analyze80211nSISO();
 *   - IQ2010EXT_Analyze80211nComposite();
 *   - IQ2010EXT_Analyze80211b();
 *   - IQ2010EXT_AnalyzeFFT();
 *   - IQ2010EXT_AnalyzePowerRamp80211b();
 *   - IQ2010EXT_AnalyzeBluetooth();
 *   - IQ2010EXT_AnalyzeMaskMeasurement();
 *
 * \section analysis_80211ag Measurement Names for IQ2010EXT_Analyze80211ag()
 *  - <b>hhEst</b>:  64-element complex vector that represents the FFT output of the two long symbols in the PLCP preamble of the OFDM signal.  index value: 0
 *  - <b>psdu</b>:  The PSDU data. 0/1 values. Includes the MAC Header and the FCS, if present .  index value: 0
 *  - <b>startPointers</b>:  Provides the approximate starting locations of each packet detected in the input data.
 *					 If no packet detected, this is an empty vector.  index value: 0
 *  - <b>plcp</b>:  PLCP (binary) data as 1/0s.  index value: 0
 *
 * \section analysis_mimo Measurement Names for IQ2010EXT_AnalyzeMimo()
 *  - <b>channelEst</b>:  Channel estimate matrix; dimension NStreams x NTones x NRx. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>rxRmsPowerDb</b>:  RMS power of estimated channels; dimension NStreams x NRx. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>isolationDb</b>:  Matrix that indicates isolation between streams; column 1 is for Rx signal containing main power for stream 1, etc; dimension NStreams x NStreams.
 *				   Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *				   Note: Isolation can only be measured with direct-mapping signals.
 *  - <b>evmSymbols</b>:  Per symbol and stream; dimension NStreams x NSymbols. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>evmTones</b>:  Per tone and stream; dimension NStreams x Ntones. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>PhaseNoiseDeg_Symbols</b>:  Per symbol and VSA signal; dimension NRx x Nsymbols. Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *  - <b>demodSymbols</b>: Complex demodulated symbols; dimension NTones x NSymbols x Nstreams.  This provides the symbol constellation I (Re) and Q (Im) arrays.
 *					Each stream will have a corresponding value; therefore, the index value is [0 - (StreamNum-1)]
 *
 * \section analysis_80211b Measurement Names for IQ2010EXT_Analyze80211b()
 *  - <b>evmInPlcp</b>: Evm in PLCP.  index value: 0
 *  - <b>evmErr</b>: Evm error.  index value: 0
 *  - <b>loLeakageDb</b>: LO/DC Leakage [dBc].  index value: 0
 *
 * \section analysis_FFT Measurement Names for IQ2010EXT_AnalyzeFFT()
 *  - <b>x</b>: X-axis values, typically frequency. Vector is returned.  index value: 0
 *  - <b>y</b>: Y-axis values, power in dBm. Vector is returned.  index value: 0
 *
 * \section analysis_PowerRamp80211b Measurement Names for IQ2010EXT_AnalyzePowerRamp80211b()
 *  - <b>on_mask_x</b>: Power on ramp mask x-axis.  index value: 0
 *  - <b>off_mask_x</b>: Power off ramp mask x-axis.  index value: 0
 *  - <b>on_mask_y</b>: Power on ramp mask y-axis.  index value: 0
 *  - <b>off_mask_y</b>: Power off ramp mask y-axis.  index value: 0
 *  - <b>on_power_inst</b>: Instant power on ramp.  index value: 0
 *  - <b>off_power_inst</b>: Instant power off ramp.  index value: 0
 *  - <b>on_power_peak</b>: Power on ramp peak values.  index value: 0
 *  - <b>off_power_peak</b>: Power off ramp peak values.  index value: 0
 *  - <b>on_time_vect</b>: Power on ramp time vector.  index value: 0
 *  - <b>off_time_vect</b>: Power off ramp time vector.  index value: 0
 *  - <b>on_time</b>: Ramp on time.  index value: 0
 *  - <b>off_time</b>: Ramp off time.  index value: 0
 *
 * \section analysis_Bluetooth Measurement Names for IQ2010EXT_AnalyzeBluetooth()
 *  - <b>P_av_each_burst</b>: Average power of each burst.  index value: 0
 *  - <b>P_pk_each_burst</b>: Peak power of each burst.  index value: 0
 *  - <b>complete_burst</b>: Vector indicating whether or not each burst is complete.
 *					  All elements are either (1 beginning and end transitions detected), or (0 burst is missing either beginning or end transition).
 *					  index value: 0
 *  - <b>start_sec</b>: Starting time of each burst, in seconds.  index value: 0
 *  - <b>stop_sec</b>: End time of each burst, in seconds.  index value: 0
 *  - <b>freq_est</b>: Initial freq offset of each burst detected, in Hz.  index value: 0
 *  - <b>freqEstPacketPointer</b>: Pointers to which packet is pointed to in each element of freq_est.  index value: 0
 *  - <b>freq_drift</b>: Initial freq carrier drift of each burst detected, in Hz.  index value: 0
 *  - <b>freqDriftPacketPointer</b>: Pointers to which packet is pointed to in each element of freq_drift.  index value: 0
 *  - <b>freqDeviationPointer</b>: Pointers to which packet is pointed to in each element of the above two measurements.  index value: 0
 *  - <b>EdrFreqvsTime</b>: Enhanced data rate for frequency versus time.  index value: 0
 *  - <b>EdrExtremeOmegaI0</b>: Extreme value of (Omega_0 + Omega_i).  index value: 0
 *
 * \section analysis_mask Measurement Names for IQ2010EXT_AnalyzeMaskMeasurement() with mask type WIFI_11B, WIFI_11AG, WIFI_11N_HT20 and WIFI_11N_HT40
 *  - <b>x</b>: X-axis values, typically frequency. Vector is returned.  index value: 0
 *  - <b>y</b>: Y-axis values, power in dBm. Vector is returned.  index value: 0
 *
 */


/*--------------*
 * TX Functions *
 *--------------*/

//! Perform multiple captures, then user can later perform different analysis based on these captures.
//! Use it along with IQ2010EXT_AddMultiAnalysisCapture() and IQ2010EXT_FinishMultiAnalysisCapture()
/*!
 * \param[in] dataRate Datarate the DUT uses to transmit the signal
 * \param[in] freqMHz Frequency (MHz) at which the DUT transmits
 * \param[in] rmsPowerLeveldBm Estimated DUT RMS power level (dBm) at the tester RF ports
 * \param[in] skipPktCnt Skip count before capture.                                         Max allowed: 255
 * \param[in] rfPort RF port. Valid values are IQV_PORT_LEFT (RF1) and IQV_PORT_RIGHT (RF2).
 * \param[in] triggerLeveldBm Trigger level in dBm
*/
IQMEASURE_API int		LP_IQ2010EXT_NewMultiAnalysisCapture( char		   *dataRate,
                                                        double          freqMHz,
                                                        double	        rmsPowerLeveldBm,
													    int	            skipPktCnt,
													    int		        rfPort,
													    double	        triggerLeveldBm);

//! Add multiple capture type with specified capture length and count. This function should be called after IQ2010EXT_NewMultiAnalysisCapture()
/*!
 * \param[in] analysisType  analysis type
 * \param[in] captureLengthUs Capture length in us.                                         Max allowed: 1023 us
 * \param[in] captureCnt Capture count.                                                     Max allowed: 255
*/
IQMEASURE_API int		LP_IQ2010EXT_AddMultiAnalysisCapture( int		    analysisType,
													    int			captureLengthUs,
													    int			captureCnt);

//! VSA Multi-packet analysis capture. Should use it along with IQ2010EXT_FinishMultiAnalysisCapture(). The function should be called first.
/*!
 * \return ERR_OK if the VSA capture is done successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_InitiateMultiAnalysisCapture(void);

//! VSA multi-packet capture based on the  . The function should be called after IQ2010EXT_AddMultiAnalysisCapture()
/*!
 * \return ERR_OK if the VSA capture is done successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_FinishMultiAnalysisCapture(void);

//! VSA Multi-packet capture. Should use it along with IQ2010EXT_FinishMultiCapture(). The function should be called first.
/*!
 * \param[in] dataRate Datarate the DUT uses to transmit
 * \param[in] freqMHz Frequency (MHz) at which the DUT transmits
 * \param[in] rmsPowerLeveldBm Estimated DUT RMS power level (dBm) at the tester RF ports
 * \param[in] captureLengthUs Capture length in us.                                         Max allowed: 1023 us
 * \param[in] skipPktCnt Skip count before capture.                                         Max allowed: 255
 * \param[in] captureCnt Capture count.                                                     Max allowed: 255
 * \param[in] rfPort RF port. Valid values are IQV_PORT_LEFT (RF1) and IQV_PORT_RIGHT (RF2).
 * \param[in] triggerLeveldBm Trigger level in dBm
 *
 * \return ERR_OK if the VSA capture is initiated successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_InitiateMultiCapture( char				*dataRate,
													 double              freqMHz,
													 double	             rmsPowerLeveldBm,
													 int	             captureLengthUs,
													 int	             skipPktCnt,
													 int	             captureCnt,
													 int				 rfPort,
													 double	             triggerLeveldBm);

//! VSA Multi-packet Capture for HT40. Should use it along with IQ2010EXT_FinishMultiCapture(). The function should be called first.
/*!
 * \param[in] dataRate Datarate the DUT uses to transmit
 * \param[in] freqMHz Frequency (MHz) at which the DUT transmits
 * \param[in] rmsPowerLeveldBm Estimated DUT RMS power level (dBm) at the tester RF ports
 * \param[in] captureLengthUs Capture length in us.                                         Max allowed: 1023 us
 * \param[in] skipPktCnt Skip count before capture.                                         Max allowed: 255
 * \param[in] captureCnt Capture count.                                                     Max allowed: 255
 * \param[in] rfPort RF port. Valid values are IQV_PORT_LEFT (RF1) and IQV_PORT_RIGHT(RF2).
 * \param[in] triggerLeveldBm Trigger-level in dBm
 *
 * \return ERR_OK if the VSA capture is initiated successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_InitiateMultiCaptureHT40( char			   *dataRate,
														 double             freqMHz,
														 double	            rmsPowerLeveldBm,
														 int	            captureLengthUs,
														 int	            skipPktCnt,
														 int	            captureCnt,
														 int                rfPort,
														 double	            triggerLeveldBm);


//! VSA multi-packet capture. Should use it along with IQ2010EXT_InitiateMultiCapture(). The function should be called after IQ2010EXT_InitiateMultiCapture() or IQ2010EXT_InitiateMultiCaptureHT40().
/*!
 * \return ERR_OK if the VSA capture is done successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_FinishMultiCapture(void);

//! Perform 802.11a/g Analysis on Multi-packet Capture
/*!
 * \param[in] ph_corr_mode Phase Correction Mode with the following valid options:
 *         - IQV_PH_CORR_OFF: Phase correction off
 *         - IQV_PH_CORR_SYM_BY_SYM: Symbol-by-symbol correction  (Default)
 *         - IQV_PH_CORR_MOVING_AVG: Moving avg. correction (10 symbols)
 * \param[in] ch_estimate Channel Estimate with the following options:
 *         - IQV_CH_EST_RAW_LONG: Raw Channel Estimate (based on long trainling symbols) (Default)
 *         - IQV_CH_EST_2ND_ORDER: 2nd Order Polyfit
 *         - IQV_CH_EST_RAW_FULL: Full packet estimate
 * \param[in] sym_tim_corr Symbol Timing Correction with the following options:
 *         - IQV_SYM_TIM_OFF: Symbol Timing Correction Off
 *         - IQV_SYM_TIM_ON: Symbol Timing Correction ON (Default)
 * \param[in] freq_sync Frequency Sync. Mode with the following options:
 *         - IQV_FREQ_SYNC_SHORT_TRAIN: Short Training Symbol
 *         - IQV_FREQ_SYNC_LONG_TRAIN: Long Training Symbol (Default)
 *         - IQV_FREQ_SYNC_FULL_PACKET: Full Data Packet
 * \param[in] ampl_track Amplitude Tracking with the following options:
 *         - IQV_AMPL_TRACK_OFF: Amplitude tracking off (Default)
 *         - IQV_AMPL_TRACK_ON: Amplitude tracking on
 *
 * \return ERR_OK if the 802.11 a/g analysis succeeded; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_Analyze80211ag( IQV_PH_CORR_ENUM ph_corr_mode    =IQV_PH_CORR_SYM_BY_SYM,
											   IQV_CH_EST_ENUM ch_estimate      =IQV_CH_EST_RAW_LONG,
											   IQV_SYM_TIM_ENUM sym_tim_corr    =IQV_SYM_TIM_ON,
											   IQV_FREQ_SYNC_ENUM freq_sync     =IQV_FREQ_SYNC_LONG_TRAIN,
											   IQV_AMPL_TRACK_ENUM ampl_track   =IQV_AMPL_TRACK_OFF);

//! Perform 802.11n Analysis on Multi-packet Capture
/*!
 * \param[in] enablePhaseCorr Phase Correction Mode:
 *         - 0: Disable
 *         - 1: Enable (Default)
 * \param[in] enableSymTimingCorr Symbol Timing Correction:
 *         - 0: Disable
 *         - 1: Enable (Default)
 * \param[in] enableAmplitudeTracking Amplitude Tracking:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] decodePSDU Decode PSDU:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] enableFullPacketChannelEst Channel Estimate on full packet:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] packetFormat indicates format of the 80211n MIMO packet:
 *         - 0: auto-detect mode (Default)
 *         - 1: mixed format
 *         - 2: greenfield format
 *
 * \return ERR_OK if the 802.11n analysis is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_Analyze80211nSISO(  int enablePhaseCorr            = 1,
												  int enableSymTimingCorr        = 1,
												  int enableAmplitudeTracking    = 0,
												  int decodePSDU                 = 0,
												  int enableFullPacketChannelEst = 0,
												  int packetFormat               = 0);

//! Perform 802.11n Analysis on Multi-packet Capture in composite mode
/*!
 * \param[in] enablePhaseCorr Phase Correction Mode:
 *         - 0: Disable
 *         - 1: Enable (Default)
 * \param[in] enableSymTimingCorr Symbol Timing Correction:
 *         - 0: Disable
 *         - 1: Enable (Default)
 * \param[in] enableAmplitudeTracking Amplitude Tracking:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] enableFullPacketChannelEst Channel Estimate on full packet:
 *         - 0: Disable (Default)
 *         - 1: Enable
 * \param[in] referenceFile PSDU reference file (needed for Composite EVM)
 * \param[in] packetFormat indicates format of the 80211n MIMO packet:
 *         - 0: auto-detect mode (Default)
 *         - 1: mixed format
 *         - 2: greenfield format
 *
 * \return ERR_OK if the 802.11n analysis is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_Analyze80211nComposite(int enablePhaseCorr            = 1,
													  int enableSymTimingCorr        = 1,
													  int enableAmplitudeTracking    = 0,
													  int enableFullPacketChannelEst = 0,
													  char *referenceFile            = NULL,
													  int packetFormat               = 0);

//! Perform 802.11b Analysis on Multi-packet Capture
/*!
 * \param[in] eq_taps Number of equalizer taps, valid options are as follows:
 *         - IQV_EQ_OFF: Equalizer Off  (Default)
 *         - IQV_EQ_5_TAPS: 5 Taps Equalizer
 *         - IQV_EQ_7_TAPS: 7 Taps Equalizer
 *         - IQV_EQ_9_TAPS: 9 Taps Equalizer
 * \param[in] DCremove11b_flag DC removal, valid options are:
 *         - IQV_DC_REMOVAL_OFF: DC Removal OFF (Default)
 *         - IQV_DC_REMOVAL_ON: DC Removal ON
 * \param[in] method_11b 802.11b method, valid options are as follows:
 *         - IQV_11B_STANDARD_TX_ACC: Use 11b standard TX accuracy (Default)
 *         - IQV_11B_RMS_ERROR_VECTOR: Use 11b RMS error vector
 *
 * \return ERR_OK if the 802.11b analysis is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_Analyze80211b( IQV_EQ_ENUM eq_taps                   = IQV_EQ_OFF,
											  IQV_DC_REMOVAL_ENUM DCremove11b_flag  = IQV_DC_REMOVAL_OFF,
											  IQV_11B_METHOD_ENUM method_11b        = IQV_11B_STANDARD_TX_ACC);

//! Perform power analysis on Multi-packet Capture
/*!
 * \return ERR_OK if the power analysis is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_AnalyzePower(void);

//! Perform FFT analysis on Multi-packet Capture
/*!
 * \param [in] NFFT        Number of points in FFT.                        Default: 0
 * \param [in] res_bwHz    The resolution bandwidth in Hz.                 Default: 100000
 * \param [in] window_type Window type with following options              Default: "blackmanharris"
 *                 - "blackmanharris"
 *                 - "hanning"
 *                 - "flattop"
 *                 - "rect"
*/
IQMEASURE_API int		LP_IQ2010EXT_AnalyzeFFT( double NFFT          = 0,
										   double res_bwHz      = 100000,
										   char *window_type    = "blackmanharris");

//! Perform mask verification and get OBW based on the OBW percentage
/*!
 * \param [in] maskType         indicate what mask type should be applied to the captured data
 * \param [in] obwPercentage    OBW percentage. The valid range should be between 0 - 1
 * \return ERR_OK if the mask measurement is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_AnalyzeMaskMeasurement(int maskType, double obwPercentage);

//! Perform power-ramp analysis for 11B
/*!
 * \return ERR_OK if the mask measurement is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_AnalyzePowerRamp80211b();

//! Perform Bluetooth Analysis on Multi-packet Capture
/*!
 * \param[in] data_rate Bluetooth data rate, with the following options:
 *         - 1: 1Mbit/s BDR
 *         - 2: 2Mbit/s EDR
 *         - 3: 3Mbit/s EDR
 *         - 0: Auto detect
 * \param[in] analysis_type Specifies what type of analysis to perform.                 Default: 'All'.
 *         Valid values are as follows:
 *         - PowerOnly
 *         - 20dbBandwidthOnly
 *         - PowerandFreq
 *         - All  (This is the set default value)
 *		   - ACP  (only does the new ACP analysis)
 *		   - AllPlus  (performs all the analyses that are done by ��All?plus the ACP analysis)
 * \return ERR_OK if the bluetooth analysis is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_AnalyzeBluetooth(double data_rate, char *analysis_type="All");

//! Perform spectral analysis based on the selected spectral type
/*!
 * param [in] spectralType  indicate the spectral type to be applied to the captured data
 * \return ERR_OK if the spectral measurement is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_AnalyzeSpectralMeasurement(int spectralType);

//////! Set Analysis Parameters
/////*!
//// * \param[in] analysisType One of the analysis types defined in IQ2010EXT_ANALYSIS_TYPE_ENUM
//// * \param[in] parameter One of the parameter names for the specified analysis type (see TODO for details)
//// * \param[in] value The value for the specified parameter
//// *
//// * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
//// */
//////IQ2010EXT_API int IQ2010EXT_SetAnalysisParameterInteger(Q2010EXT_ANALYSIS_TYPE_ENUM analysisType,
//////                                                        char *parameter,
//////                                                        int value);



/*--------------*
 * RX Functions *
 *--------------*/

//! IQ2010 ACK-based RX PER Test
/*!
 * \param[in] waveformIndex A wave form index (0 based) of the multi-segment wavefile, specifying which wave form should be used
 * \param[in] freqMHz Frequency (MHz) on which DUT operates
 * \param[in] powerLevelStartdBm The start of power level (dBm at IQ2010 RF ports)
 * \param[in] powerLevelStopdBm The stop of power level (dBm at IQ2010 RF ports)
 * \param[in] stepdB Power level step(dB).  Minimum step is 0.5dB.
 * \param[in] packetCount Number of packets to be transmitted for power level. Maximum number of packets is 32767.
 * \param[in] rfPort The RF ports used for RX PER testing. Valid values are IQV_PORT_LEFT (RF1) and IQV_PORT_RIGHT(RF2).
 * \param[in] ackPowerRmsdBm The DUT ACK RMS Power at the tester port
 * \param[in] ackTriggerLeveldBm The trigger level set to do ACK detection
 *
 * \return ERR_OK if the RX PER is successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 *
 * \remark
 *         -# In most cases, the stop power level would be lower than the start power level, but it could be
 *            higher than the start power level.  In either way, step would be relative, meaning always positive.
 *         -# If only one power level is interested for RX PER, make the powerLevelStopdBm the same as powerLevelStartdBm.
 *         -# power level should be within [-10, -95] dBm
 */
IQMEASURE_API int		LP_IQ2010EXT_RxPer( int               waveformIndex,
									  double            freqMHz,
									  double            powerLevelStartdBm,
									  double            powerLevelStopdBm,
									  double            stepdB,
									  int               packetCount,
									  int				rfPort,
									  double            ackPowerRmsdBm,
									  double            ackTriggerLeveldBm
									  );

/*---------------------------------*
 * Multi-segment Waveform Handling *
 *---------------------------------*/
//! Start a new Multi-segment Waveform Creation
/*!
 *
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 *
 * \remark
 *         -# After calling this function, you can then call IQ2010EXT_AddWaveform()
 */
IQMEASURE_API int		LP_IQ2010EXT_NewMultiSegmentWaveform();

//! Add a Waveform to the Multi-segment Waveform.
/*!
 * \param[in] modFile A .mod file that contains only one data rate
 * \param[out] waveformIndex The waveform index used by IQ2010EXT_RxPer() identifying this data rate
 *
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 *
 * \remark
 *         -# You can only call this function after IQ2010EXT_NewMultiSegmentWaveform() and before IQ2010EXT_FinalizeMultiSegmentWaveform()
 *         - The maximum number of file can be added is 32
 */
IQMEASURE_API int		LP_IQ2010EXT_AddWaveform(const char *modFile, unsigned int *waveformIndex );

//! Finalize the Multi-segment Waveform Creation and Upload to VSG Memory
/*!
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 * \remark
 *         -# You cannot call IQ2010EXT_AddWaveform() anytime after calling this function
 */
IQMEASURE_API int		LP_IQ2010EXT_FinalizeMultiSegmentWaveform();

//! Generate a wave form at VSG by the specified segment index with the packet count
/*!
 * \param[in] waveformIndex index (base 0) to wave form (wave form is preloaded by IQ2010EXT_LoadMultiSegmentWaveFile(...) ) to be played at VSG
 * \param[in] packetCount number of packets to be played
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
//IQMEASURE_API int		LP_IQ2010EXT_VsgSingleSegmentPlay(int waveformIndex, int packetCount);

//! After calling IQ2010EXT_VsgSingleSegmentPlay(...). Should call IQ2010EXT_VsgSingleSegmentStop() to stop the segment played
/*!
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
//IQMEASURE_API int		LP_IQ2010EXT_VsgSingleSegmentStop();

/*--------------------------*
 * Getting result Functions *
 *--------------------------*/

//! Get the number of results for a particular measurement element (pointed to by indexResult) by measurement name
/*!
 * \param [in] measurementName         measurement name
 * \param [in] indexResult             index to a particular measurement element
 * \param [out] numberOfMeasurementElement return number of measurement element
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_GetNumberOfMeasurementElements(char *measurementName, int indexResult, int *numberOfMeasurementElement);

//! Get the number of results for a particular measurement element (pointed to by indexResult) by measurement name
/*!
 * \param [in] measurementName         measurement name
 * \param [out] numberOfPerPowerLevel return number of per power level
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
*/
IQMEASURE_API int		LP_IQ2010EXT_GetNumberOfPerPowerLevels(char *measurementName, int *numberOfPerPowerLevel);

//! Retrieve Analysis Results [Double] in average, minimum and maximum value
/*!
 * \param[in]  measurementName          The measurement name.  Please refer to \ref group_scalar_measurement "Vector Measurements" for all available measurement names.
 * \param[out] average Average value    Average value for all the result(s). Result set can be more than one if the specified capture count is larger than one when using multi-capture function 'IQ2010EXT_VsaMultiCapture(...)'
 * \param[out] minimum Minimum value    Minimum value of all the result(s)
 * \param[out] maximum Maximum value    Maximum value of all the result(s)
 *
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_GetDoubleMeasurements(char *measurementName, double *average, double *minimum, double *maximum);

//! Retrieve Analysis Results [char]
/*!
 * \param[in] measurementName The measurement name.  Please refer to \ref group_scalar_measurement "Vector Measurements" for all available measurement names.
 * \param[out] result Result in 'char' pointer type
 * \param[in] bufferSize Indicates the buffer size of result
 * \param[in] indexResult (starts with 0 as the first set of result) indicates which set of result to be retrieved. It has to be less than the number of capture set in IQ2010EXT_VsaMultiCapture(...)
 *
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_GetStringMeasurement(char *measurementName, char *result, int  bufferSize, int indexResult = 0);

//! Retrieve Analysis Results [Double] in vector format ( more than one value in one particular result set as indicated by indexResult )
/*!
 * \param[in] measurementName The measurement name.  Please refer to \ref group_vector_measurement "Vector Measurements" for all available measurement names
 * \param[out] values Returns the real part of vector
 * \param[in] bufferLength Indicates the length of bufferReal and bufferImag (in number of element)
 * \param[out] *dataSize indicates the number of element in the result. If the dataSize is greater than bufferLength, then only the data with bufferLength will be filled up in the buffer
 * \param[in] indexResult (starts with 0 as the first set of result) indicates which set of result to be retrieved. It has to be less than the number of capture set in IQ2010EXT_VsaMultiCapture(...)
 *
 * \return ERR_OK if successful; otherwise, call IQ2010EXT_GetLastErr() for detailed error message.
 */
IQMEASURE_API int		LP_IQ2010EXT_GetVectorMeasurement(char *measurementName, double values[], int bufferLength, int *dataSize, int indexResult = 0);

//! Retrieve Analysis Results [int]
/*!
 * \param[in] measurementName The measurement name.  Please refer to \ref group_vector_measurement "Vector Measurements" for all available measurement names
 * \param[out] result Result in 'int' type
 * \param[in] indexResult (starts with 0 as the first set of result) indicates which set of result to be retrieved. It has to be less than the number of capture set in IQ2010EXT_VsaMultiCapture(...)
*/
IQMEASURE_API int		LP_IQ2010EXT_GetIntMeasurement(char *measurementName, int *result, int indexResult = 0);

//! Initializes IQ2010 Extension
/*!
 * \return ERR_OK if initialzation is done successfully; otherwise call IQ2010EXT_GetLastErr() for detailed error message.
 * \remark This function has to be called right after IQ2010 software has been connected to the test system
 */
IQMEASURE_API int		LP_IQ2010EXT_Init(void);

//! Exit IQ2010 extension
/*!
 * \return ERR_OK if exiting IQ2010 extension successfully; otherwise call IQ2010EXT_GetLastErr() for detailed error message.
 * \remark This function has to be called if user wants to switch the tester back to legacy mode after using IQ2010 extension.
 */
IQMEASURE_API int		LP_IQ2010EXT_Terminate(void);

/*------------------*
*	GPS Functions	*
*-------------------*/
enum LP_GPS_REPLAY_MODE
{
   GPS_REPLAY_OFF,
   GPS_REPLAY_ON
};

enum LP_GPS_CHANNEL_NUMBER
{
   GPS_CHANNEL_NUMBER_1,	//!< Indicates the first GPS channel
   GPS_CHANNEL_NUMBER_2,	//!< Indicates the second GPS channel
   GPS_CHANNEL_NUMBER_3,	//!< Indicates the third GPS channel
   GPS_CHANNEL_NUMBER_4,	//!< Indicates the fourth GPS channel
   GPS_CHANNEL_NUMBER_5,	//!< Indicates the fifth GPS channel
   GPS_CHANNEL_NUMBER_6	    //!< Indicates the sixth GPS channel
};

//IQMEASURE_API int LP_GPS_GetData(char* inputName, char* &inputValue);
//!
/*! @defgroup gps_measurement Measurement
 *  The process sequence is :
 * 1. Activate Tester
 *    LP_GPS_SetActivate
 * 2. Call the main test function :
 *    LP_GPS_LoadScenarioFile & LP_GPS_PlayScenarioFile
 *    LP_GPS_ModulatedMode
 *    LP_GPS_ContinueWave
 * 3. Deactivate Tester
 *    LP_GPS_SetDeactivate
 * @. Others
 *    LP_GPS_SetData
 *    LP_GPS_SetChannelInfo
 * @. Internal function
 *    LP_GPS_CaculateTesterPower
 */

//! Calling LP_GPS_SetActivate to activate Tester.
IQMEASURE_API int		LP_GPS_SetActivate();

//! Calling LP_GPS_LoadScenarioFile to load scenario file.
/*!
 * \param[in] fileName     : Path of the scenario file.
 * \param[in] triggerState : Trigger State.
*/
IQMEASURE_API int		LP_GPS_LoadScenarioFile(char* fileName, IQV_GPS_TRIGGER_STATE triggerState);

//! Calling LP_GPS_PlayScenarioFile to start playing scenario file.
/*!
 * \param[in] power        : Power at the DUT.
 * \param[in] pathloss     : Cable loss.
*/
IQMEASURE_API int		LP_GPS_PlayScenarioFile(double powerDbm, double pathlossDb);

//! Calling LP_GPS_ModulatedMode to transmit modulate mode signal.
/*!
 * \param[in] Nav_Mode         : Navigation mode. 0 means OFF (Default), "IQV_OPERATION_MODE_MODULATION_NAV_DATA_OFF" and 1 means ON, "IQV_OPERATION_MODE_MODULATION".
 * \param[in] pathloss         : Cable loss.
 * \param[in] powerA[6]        : Power array of each channel at the DUT.
 * \param[in] satelliteNumA[6] : Satellite number array of each channel.
 * \param[in] dopplerFrequenc  : Doppler frequence revise.
 * \param[in] triggerState     : Trigger State.
*/
IQMEASURE_API int		LP_GPS_ModulatedMode(int Nav_Mode, double pathlossDb, double powerA[6], int satelliteNumA[6], int dopplerFrequency, IQV_GPS_TRIGGER_STATE triggerState);

//! Calling LP_GPS_ContinueWave to transmit continue wave signal.
/*!
 * \param[in] power        : Power at the DUT.
 * \param[in] pathloss     : Cable loss.
 * \param[in] triggerState : Trigger State.
 * \param[in] freqOffset   : Frequency offset for Continuous Wave.
*/
IQMEASURE_API int		LP_GPS_ContinueWave(double powerDbm, double pathlossDb, IQV_GPS_TRIGGER_STATE triggerState, int freqOffset);

//! Calling LP_GPS_SetDeactivate to stop and deactivate Tester.
IQMEASURE_API int		LP_GPS_SetDeactivate();

//! Calling LP_GPS_GetChannelInfo to get information of each channel.
/*!
 * \param[in] channelNumber   : channel number.
 * \param[in] satelliteNumber : apply satellite number of the channel.
 * \param[in] powerDbm        : apply power of the channel.
*/
IQMEASURE_API int		LP_GPS_GetChannelInfo(IQV_GPS_CHANNEL_NUMBER channelNumber,
										 int *satelliteNumber,
										 double *powerDbm,
										 IQV_GPS_MODULATION_STATE *modulationState);

//! Calling LP_GPS_SetChannelInfo to set information of each channel.
/*!
 * \param[in] channelNumber   : channel number.
 * \param[in] satelliteNumber : setup satellite number of the channel.
 * \param[in] powerDbm        : setup power of the channel.
*/
IQMEASURE_API int		LP_GPS_SetChannelInfo(IQV_GPS_CHANNEL_NUMBER channelNumber,
										int satelliteNumber,
										double powerDbm,
										IQV_GPS_MODULATION_STATE modulationState);

//! Calling LP_GPS_SetData to set information of the tester.
/*!
 * \param[in] inputName  : setup function name.
 * \param[in] inputValue : setup value of the function.
 * <b>SetParamOperationMode</b>    :
 *        <b>IQV_OPERATION_MODE_MODULATION_OFF</b>
 *        <b>IQV_OPERATION_MODE_MODULATION</b>
 *        <b>IQV_OPERATION_MODE_CW</b>
 *        <b>IQV_OPERATION_MODE_MODULATION_NAV_DATA_OFF</b>
 * <b>SetParamPowerDbm</b>         :
 *        <b>[tester Power]</b>
 * <b>SetParamModulationState</b>  :
 *        <b>IQV_MODULATION_STATE_OFF</b>
 *        <b>IQV_MODULATION_STATE_ON</b>
 * <b>SetParamDopplerFrequency</b> :
 *        <b>[doppler Frequency]</b>
 * <b>SetParamRfOutput</b>         :
 *        <b>IQV_RF_OUTPUT_OFF</b>
 *        <b>IQV_RF_OUTPUT_ON</b>
 * <b>SetParamTriggerState</b>     :
 *        <b>IQV_TRIGGER_STATE_INT</b>
 *        <b>IQV_TRIGGER_STATE_EXT</b>
 * <b>SetReplayScenarioMode</b>    :
 *        <b>IQV_GPS_REPLAY_OFF</b>
 *        <b>IQV_GPS_REPLAY_ON</b>
*/
IQMEASURE_API int		LP_GPS_SetData(const char* inputName, const char* inputValue);
IQMEASURE_API double	LP_GPS_CaculateTesterPower(double powerDbm, double pathlossDb);

IQMEASURE_API int LP_PrintGlonassParameters(bool forceUpdate = true);
IQMEASURE_API int LP_Glonass_SetOperationMode(IQV_GPS_OPERATION_MODE operationMode);
IQMEASURE_API int LP_Glonass_SetPower(double powerdBm);
IQMEASURE_API int LP_Glonass_SetFrequency(int frequencyChannel);
IQMEASURE_API int LP_Glonass_SetRfOutput(IQV_GPS_RF_OUTPUT rfOutput);
IQMEASURE_API int LP_Glonass_SetActivate(void);
IQMEASURE_API int LP_Glonass_SetDeactivate();

//! spcified the path that is used to invoke LitePoint Connectivity server.
/*!
 * \param[in] litePointConnectionPath The path of connectivity server.
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetLpcPath(char *litePointConnectionPath);

/*----------------------------*
*		FM Functions		  *
*-----------------------------*/

//FM IQMeasure functions - merged on 08/09/2010

//! Set FM VSG Parameters
/*!
 * \param[in] carrierFreqHz Sets the FM Carrier Frequency (Hz).
 * \param[in] carrierPowerdBm Sets the FM Carrier Power (dBm).
 * \param[in] modulationEnable Sets the FM Modulation (ON/OFF).
 * \param[in] totalFmDeviationHz Sets the Total Peak FM Deviation (Hz). Note : totalFmPeakDeviationHz = Audio Deviation + Pilot Deviation( if stereo is enabled) + RDS Deviation( if RDS is enabled).
 * \param[in] stereoEnable Enable or Disable Stereo Mode ( ON/OFF).
 * \param[in] pilotDeviationHz Sets the Pilot Deviation(Hz) and will be used if Stereo is Enabled.
 * \param[in] rdsEnable Enable or Disable RDS ( ON/OFF).
 * \param[in] rdsDeviationHz Sets the RDS Deviation(Hz) and will be used if RDS is Enabled.
 * \param[in] preEmphasisMode Sets the Pre-Emphasis Filter value in us(Example: 0, 25, 50, 75).

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_SetVsg(unsigned int carrierFreqHz = 100000000,
							   double carrierPowerdBm = -40,
							   int modulationEnable = ON,
							   unsigned int totalFmDeviationHz = 75000,
							   int stereoEnable = OFF,
							   unsigned int pilotDeviationHz = 7500,
							   int rdsEnable = OFF,
							   unsigned int rdsDeviationHz = 2000,
							   unsigned int preEmphasisUs = PRE_EMPHASIS_75US,
							   char* rdsTransmitString = "LP_rds_transmit") ;

//! Return the FM VSG Parameters that is currently setup in the Tester
/*!
 * \param[out] carrierFreqHz Returns the FM Carrier Frequency (Hz).
 * \param[out] carrierPowerdBm Returns the FM Carrier Power (dBm).
 * \param[out] modulationEnabled Returns the FM Modulation State(1: ON/0: OFF).
 * \param[out] totalFmDeviationHz Returns the Total Peak FM Deviation (Hz). Note : totalFmPeakDeviationHz = Audio Deviation + Pilot Deviation( if stereo is enabled) + RDS Deviation( if RDS is enabled).
 * \param[out] stereoEnabled Returns Stereo Mode (1: ON/0: OFF).
 * \param[out] pilotDeviationHz Returns the Pilot Deviation(Hz) and will be used if Stereo is Enabled.
 * \param[out] rdsEnabled Returns RDS status(1: ON/0: OFF).
 * \param[out] rdsDeviationHz Returns the RDS Deviation(Hz) and will be used if RDS is Enabled.
 * \param[out] preEmphasisMode Returns the Pre-Emphasis Filter value.


 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_GetVsgSettings(unsigned int *carrierFreqHz,
									   double *carrierPowerdBm,
									   int *modulationEnabled,
									   unsigned int *totalFmDeviationHz,
									   int *stereoEnabled,
									   unsigned int *pilotDeviationHz,
									   int *rdsEnabled,
									   unsigned int *rdsDeviationHz,
									   unsigned int *preEmphasisMode
									   );

//! Sets the Single tone audio signal parameters for VSG Transmit: Stereo mode assigns the single tone to a left and right channel and the phase relationship between the channels is arbitrary.
/*!
 * \param[in] audioToneFreqHz Sets the single tone audio frequency (Hz).
 * \param[in] leftRightChannelSelect Sets the channel information for a stereo Tone. LEFT assigns single tone to LEFT Channel only ,RIGHT assigns single tone to RIGHT Channel only , LEFT_RIGHT assigns single tone to LEFT and RIGHT Channel with arbitrary phase relationship.
 * \param[in] audioToneAmpdB Sets the audio signal power for the single tone(dB). Note: 0 dB corresponds to 1Vpp.
 * \param[in] stereo Indicates if Stereo is Enabled or not ( ON / OFF).Note: The Stereo Mode is enabled in the LP_FM_SetVsg function.

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_SetAudioSingleTone(double audioToneFreqHz,
										   int leftRightChannelSelect,
										   double audioToneAmpPercent,
										   int stereo);

//! Sets the multi tone audio signal parameters: upto maximum of 12 tones. Note: Stereo tone limits the maximum Left Channels and Right Channels to 6 and there is not defined phase relationship between the channels.
/*!
 * \param[in] freqHz Sets an array of audio tones (Hz). Note: Maximum size = 12.
 * \param[in] channelSelect Sets an array of audio tones channel corresponding to freqHz tones.LEFT assigns single tone to LEFT Channel only ,RIGHT assigns single tone to RIGHT Channel only. This array is ignored if Stereo is not enabled in the LP_FM_SetVsg Function. Note: Maximum size = 12.
 * \param[in] amplitudePercent Sets an array of audio signal power corresponding to freqHz tones (dB).
 * \param[in] stereo Indicates if Stereo is Enabled or not ( ON / OFF).Note: The Stereo Mode is enabled in the LP_FM_SetVsg function.
 * \param[in] toneCount Provides information about the total number of tones that will be set.

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_SetAudioToneArray(double* freqHz,
										  int* channelSelect,
										  double* amplitudePercent,
										  int stereo,
										  unsigned int toneCount);

//! Sets the multi tone audio signal parameters: upto maximum of 12 tones. Note: Stereo tone limits the maximum Left Channels and Right Channels to 6 and there is not defined phase relationship between the channels.
/*!
 * \param[in] freqHz Sets an array of audio tones (Hz). Note: Maximum size = 12.
 * \param[in] channelSelect Sets an array of audio tones channel corresponding to freqHz tones.LEFT assigns single tone to LEFT Channel only ,RIGHT assigns single tone to RIGHT Channel only. This array is ignored if Stereo is not enabled in the LP_FM_SetVsg Function. Note: Maximum size = 12.
 * \param[in] amplitudeDeviationHz Sets an array of individual audio signal deviation corresponding to freqHz tones (Hz).
 * \param[in] stereo Indicates if Stereo is Enabled or not ( ON / OFF).Note: The Stereo Mode is enabled in the LP_FM_SetVsg function.
 * \param[in] toneCount Provides information about the total number of tones that will be set.

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_SetAudioToneArrayDeviation(double* freqHz,
										  int* channelSelect,
										  double* amplitudeDeviationHz,
										  int stereo,
										  unsigned int toneCount);

//! Returns the multi tone audio signal Parameters
/*!
 * \param[out] freqHz Returns an array of audio tones (Hz).
 * \param[out] channelSelect Returns an array of audio tones channel corresponding to freqHz tones.
 * \param[out] amplitudePercent Returns an array of audio signal power corresponding to freqHz tones (dB). Note: 0 dB corresponds to 1Vpp.
 * \param[in] toneCount Provides information about the total number of tones that will be returned.

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_GetAudioToneArray(double *freqHz,
										  int *channelSelect,
										  double *amplitudePercent,
										  unsigned int toneCount);

//! Clears all the Audio tones
/*!
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_DeleteAudioTones();

//! Starts FM VSG Transmit
/*!
 * \return ERR_OK RR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_StartVsg();

//! Stops FM VSG Transmit
/*!
 * \return ERR_OK
 */
IQMEASURE_API int		LP_FM_StopVsg();

//! IQMeasure FM VSG AM Distortion setup and Enable/Disable
/*!
 * \param[in] amDistortionEnable Enable AM Distortion settings ( ON/OFF).
 * \param[in] amFrequencyHz Sets the AM Modulating Frequency (Hz).
 * \param[in] amDepthPercent Sets the am Distortion depth (percent).

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_SetVsgDistortion(int amDistortionEnable = OFF,
										 unsigned int amFrequencyHz = 1000,
										 unsigned int amDepthPercent = 30);

//! Get FM VSG AM Distortion Parameters currently applied to the tester
/*!
 * \param[out] amDistortionEnableStatus Returns AM Distortion Status (1: ON/0: OFF).
 * \param[out] amFrequencyHz Returns the AM Modulating Frequency (Hz).
 * \param[out] amDepthPercent Returns the am Distortion depth (percent).

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_GetVsgDistortion(double *amDistortionEnableStatus,
										 unsigned int *amFrequencyHz,
										 unsigned int *amDepthPercent);

//! Setup FM VSG Interference Parameters and Start transmit
/*!
 * \param[in] interfererRelativePowerdBm Sets the Interfering Carrier Power (dBm) - relative to the main carrier. Note: The total power(Main Carrier Power + Interference Carrier Power is limited to -40 dBm
 * \param[in] interfererCarrierOffsetHz Sets the FM Carrier Frequency Offset from the Main Carrier Frequency (Hz).
 * \param[in] interfererPeakFreqDeviationHz Sets the total peak FM Deviation (Hz) of the Interferer.
 * \param[in] interfererModulationEnable Enable or Disable FM Modulation on the Interferer ( ON/OFF).
 * \param[in] interfererAudioFreqHz Sets the Single tone audio frequency(Hz) corresponding to the interferencePeakDeviationHz.

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_StartVsgInterference(double interfererRelativePowerdBm,
											 int interfererCarrierOffsetHz,
											 int interfererPeakFreqDeviationHz,
											 int interfererModulationEnable,
											 unsigned int interfererAudioFreqHz);

//! Get FM VSG Interference Parameters currently applied to the tester
/*!
 * \param[in] interfererRelativePowerdBm Returns the Interfering Carrier Power (dBm) - relative to the main carrier. Note: The total power is limited to -40 dBm
 * \param[in] interfererCarrierOffsetHz Returns the FM Carrier Frequency Offset from the Main Carrier Frequency (Hz).
 * \param[in] interfererPeakFreqDeviationHz Returns the total peak FM Deviation (Hz) of the Interferer.
 * \param[in] interfererModulationEnabled Returns FM Modulation Status on the Interferer (1: ON/0: OFF).
 * \param[in] interfererAudioFreqHz Returns the Single tone audio frequency(Hz).

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_GetVsgInterferenceSettings(double *interfererRelativePowerdBm,
												   int *interfererCarrierOffsetHz,
												   int *interfererPeakFreqDeviationHz,
												   int *interfererModulationEnabled,
												   unsigned int *interfererAudioFreqHz);

//! Stops FM VSG Interference Transmit
/*!
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_StopVsgInterference();

//! Set FM VSA Parameters
/*!
 * \param[in] carrierFreqHz Sets the VSA Carrier Frequency (Hz)
 * \param[in] expectedPeakInputPowerdBm Sets the Expected Peak input power (dBm)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_SetVsa(unsigned int carrierFreqHz = 100e6,
							   double expectedPeakInputPowerdBm = -20);

//! Get FM VSA Parameters currently applied to the tester
/*!
 * \param[out] getCarrierFreqHz Gets the VSA Carrier Frequency (Hz)
 * \param[out] getInputPowerdBm Gets the Expected Peak input power (dBm)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_GetVsaSettings(unsigned int *carrierFreqHz,
									   double *expectedPeakInputPowerdBm);

//! Start VSA Data capture
/*!
 * \param[in] captureTimemillisec Sets the VSA Capture Time (ms)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_VsaDataCapture(double captureTimemillisec = 170.67);

//! performs RF Analysis on the VSA Data Capture
/*!
 * \param[in] rfRBWHz Specifies the RF Resolution Bandwidth (Hz)
 * \param[in] rfOBWPercent Specifies the RF Occupied Bandwidth (percent)
 * \param[in] rfPowerMeasBWHz Specifies the RF Power Measurement Bandwidth (Hz)
 * \param[in] windowType Specifies the Window type (BLACKMAN_HARRIS, HANNING, FLAT_TOP)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_Analyze_RF(int rfRBWHz = 200,
								   int rfOBWPercent = 99,
								   int rfPowerMeasBWHz = 200000,
								   int windowType = BLACKMAN_HARRIS);

//! performs Demod Analysis on the VSA Data Capture
/*!
 * \param[in] audioRBWHz Specifies the Audio Resolution Bandwidth (Hz)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_Analyze_Demod(int audioRBWHz = 100);

//! performs Mono Audio Analysis on the VSA Data Capture ( or ) Audio waveform data loaded using LP_FM_LoadAudioCapture function
/*!
 * \param[in] audioRBWHz Specifies the Audio Resolution Bandwidth (Hz)
 * \param[in] audioFreqLowLimitHz Specifies the lower bound (Hz) of analyzed range for audio analysis (Hz)
 * \param[in] audioFreqHiLimitHz Specifies the Upper bound (Hz) of analyzed range for audio analysis (Hz)
 * \param[in] filterCount Specifies total number of audio filters to be applied Note: MAX = 3
 * \param[in] filterType1 Type of filter to be applied
 * \param[in] filterParam1 Filter parameter corresponding to filterType1
 * \param[in] filterType2 Type of filter to be applied
 * \param[in] filterParam2  Filter parameter corresponding to filterType2
 * \param[in] filterType3 Type of filter to be applied
 * \param[in] filterParam3  Filter parameter corresponding to filterType3

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_Analyze_Audio_Mono(int audioRBWHz = 50,
										   int audioFreqLowLimitHz = 300,
										   int audioFreqHiLimitHz = 15000,
										   int filterCount = 3,
									       int filterType1 = 2,
									       double filterParam1 = 15000,
									       int filterType2 = 6,
									       double filterParam2 = 0,
									       int filterType3 = 3,
									       double filterParam3 = 75e-6 );

//! performs Stereo Audio Analysis on the VSA Data Capture ( or ) Audio waveform data loaded using LP_FM_LoadAudioCapture function
/*!
 * \param[in] audioRBWHz Specifies the Audio Resolution Bandwidth (Hz)
 * \param[in] audioFreqLowLimitHz Specifies the lower bound (Hz) of analyzed range for audio analysis (Hz)
 * \param[in] audioFreqHiLimitHz Specifies the Upper bound (Hz) of analyzed range for audio analysis (Hz)
 * \param[in] filterCount Specifies total number of audio filters to be applied Note: MAX = 3
 * \param[in] filterType1 Type of filter to be applied
 * \param[in] filterParam1 Filter parameter corresponding to filterType1
 * \param[in] filterType2 Type of filter to be applied
 * \param[in] filterParam2  Filter parameter corresponding to filterType2
 * \param[in] filterType3 Type of filter to be applied
 * \param[in] filterParam3  Filter parameter corresponding to filterType3

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_Analyze_Audio_Stereo(int audioRBWHz,
										     int audioFreqLowLimitHz,
										     int audioFreqHiLimitHz,
											 int filterCount,
											 int filterType1,
											 double filterParam1,
											 int filterType2,
											 double filterParam2,
											 int filterType3,
											 double filterParam3);

//! Get an FM scalar measurement result
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_fm_scalar_measurement "Scalar FM Measurements" for all available measurement names
 * \param[in] index The index of the measurement.  In most case, index would be zero.
 *
 * \return The value of the measurement.  -99999.99 (a special defined negative value) will be returned if no measurement available
 */
IQMEASURE_API double	LP_FM_GetScalarMeasurement(char *measurement, int index=0);

//! Get a vector measurement result
/*!
 * \param[in] measurement The measurement name.  Please refer to \ref group_fm_vector_measurement "Vector FM Measurements" for all available measurement names
 * \param[out] bufferReal Returns the real part of vector
 * \param[out] bufferImag Returns the imag part of vector
 * \param[in] bufferLength Indicates the length of bufferReal and bufferImag (in Bytes)
 *
 * \return The number of elements in bufferReal or/and bufferImag
 */
IQMEASURE_API int		LP_FM_GetVectorMeasurement(char *measurement, double bufferReal[], double bufferImag[], int bufferLength);

//! Captures the Audio data using the AIM Module
/*!
 * \param[in] saveFileLocation Specifies the location including the file name where the wav file needs to be stored( Path)
 * \param[in] captureDurationSec Specifies the capture duration ( seconds)
 * \param[in] samplingRate Specifies the sampling rate ( Hz)
 * \param[in] stereo Specifies the stereo status (ON/OFF)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_AudioDataCapture(char* saveFileLocation,
										 double captureDurationMilliSec,
										 int samplingRate,
										 int stereo);

//! Loads the Audio wave file for Audio Analysis
/*!
 * \param[in] fileName Specifies the full path of the file that is to be loaded ( Path)

 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_FM_LoadAudioCapture(char* fileName);

IQMEASURE_API int		LP_FM_AudioStimulusGenerateAndPlayMultiTone(double sampleRateHz = 48000,
													double deviationPercent = 100,
													double peakVoltageLevelVolts = 1,
													int toneCount = 1,
													int stereoEnable = 0,
													int* leftRightRelation = NULL,
													double* freqHz = NULL,
													double durationMilliSeconds = 500,
													char* audioWaveFileOutput = NULL);
IQMEASURE_API int		LP_FM_AudioStimulusGenerateAndPlaySingleTone(double sampleRateHz = 48000,
													double deviationPercent = 100,
													double peakVoltageLevelVolts = 1,
													int stereoEnable = 0,
													int leftRightRelation = LEFT_EQUALS_RIGHT,
													double freqHz = 1000,
													double durationMilliSeconds = 500,
													char* audioWaveFileOutput = NULL);
IQMEASURE_API int		LP_FM_StopAudioPlay();


//! Get memory addresses for a capture
/*!
* \param[in] dut
* \param[in] captureIndex
* \param[out] real
* \param[out] imag
* \param[out] length
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_GetCapture(int    dut,
                                int    captureIndex,
                                double *real[],
                                double *imag[],
                                int    length[]);

//! Enable/Disable Multi-thread
/*!
* \param[in] enableMultiThread
* \param[in] numberOfThreads
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_EnableMultiThread(int enableMultiThread,
									   int numberOfThreads);
IQMEASURE_API int		LP_SetUserDataPtr(void *userData);

//! Set default NFC
/*!
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_SetDefaultNfc();

//! Set Tx Amplitude
/*!
* \param[in] userSignalAmplitudeType - in A/m or Volt
* \param[in] userSignalAmplitude
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_SetNfcTxAmplitude(IQV_USER_SIGNAL_AMPLITUDE_TYPE userSignalAmplitudeType, double userSignalAmplitude);

//! Set Trigger Mask NFC
/*!
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_SetTriggerMaskNfc();

//! Initiate NFC
/*!
* \param[in] filename - File name of the wave file
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_InitiateNfc(char *fileName);

//! Set Rx NFC
/*!
* \param[in] triggerTimeout - trigger timeout
* \param[in] sampleingTimeSecs - sampleing time
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_SetRxNfc(double triggerTimeout, double sampleingTimeSecs);

//! Set Tx NFC
/*!
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_SetTxNfc();

//! Continuous Data Capture Handling
/*!
* \param[in] dcContEnum - type of data capture handling
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_ContCapture(IQV_DC_CONT_ENUM dcContEnum);

//! Terminate NFC
/*!
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_TerminateNfc();

//! Analysis NFC
/*!
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_AnalysisNfc();

//! Loads the modulation file (waveform) to VSG
/*!
 * \param[in] modFileName The .mod file to be loaded
 * \param[in] autoPlay - Lets the user to turn of autoPlay On or Off(TRUE or FALSE)
 * \param[in] loadInternalWaveform - Load the waveform from Local PC or internal tester (Valid setting for IQxel only)
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsgModulation_SetPlayCondition(char *modFileName, bool autoPlay = false, int loadInternalWaveform = 0);

//! Sets up VSA for Bluetooth data capturing and lets user select the VSA IF
/*!
 * \param[in] rfFreqHz The center frequency of Bluetooth RF signal (Hz)
 * \param[in] rfAmplDb The amplitude of the peak power (dBm) of the signal
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1) (Default)
 *				- =3: Right RF port (RF2)
 *				- =4: Baseband
 * \param[in] triggerLevelDb The trigger level (dBm) used for signal trigger (ignored in Free-run and External Trigger Modes)
 * \param[in] triggerPreTime The pre-trigger time used for signal capture
 * \param[in] btShiftHz The VSA IF Freq (Hz). Default : 7MHz
 * \param[in] extAttenDb The external attenuation (dB).  Set to 0 always.
 *
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 * \remark For VSA to work optimally with the input signal, set rfAmplDb to the peak power of the input signal.
 */
IQMEASURE_API int		LP_SetVsaBluetooth_BTShiftHz(double rfFreqHz, double rfAmplDb, int port, double extAttenDb = 0, double triggerLevelDb = -25, double triggerPreTime = 10e-6, double btShiftHz = 7e6);
IQMEASURE_API int		LP_FM_SetVsa_Agc_On(unsigned int carrierFreqHz, double expectedPeakInputPowerdBm);

//IQmeasure_DTNA

//! Sets up VSG including selecting the triggerType
/*!
 * \param[in] rfFreqHz The center frequency of VSG (Hz)
 * \param[in] rfGainDb The output power level of VSG (dBm)
 * \param[in] port The port to which the VSG connects, with the following options:
 *				- =1: OFF
 *				- =2: Left RF port (RF1)
 *				- =3: Right RF port (RF2) (Default)
 *				- =4: Baseband
 * \param[in] triggerType Select VSG trigger Type. 0 = IQV_VSG_TRIG_FREE_RUN; 1 = IQV_VSG_TRIG_EXT_2; 2 = IQV_VSG_TRIG_EXT_1
 * \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SetVsg_triggerType(double rfFreqHz, double rfPowerLeveldBm, int port, int triggerType);

//! Saves the captured data to a file (.sig)
/*!
 * \param[in] sigFileName Specifies the .sig file name
 *
 * \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
 */
IQMEASURE_API int		LP_SaveVsaSignalFileText(char *txtFileName);

//! Saves the captured data to a txt file (.txt)
/*!
* \param[in] sigFileName Specifies the .sig file name
*
* \return ERR_OK if successful; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_SaveTruncateCapture(char *sigFileName);

//! Perform VHT80 mask (240MHz) analysis
/*!
* \return ERR_OK if no errors; otherwise call LP_GetErrorString() for detailed error message.
* \remark Before calling LP_AnalyzeVHT80Mask(), modeHT40 needs to set to 2 in LP_VsaDataCapture().
*/
IQMEASURE_API int		LP_AnalyzeVHT80Mask();

//!Following functions for fast power measurement, since API analysis power requires at least 10us data, but MPS for OFDM only need 8us
IQMEASURE_API int		LP_FastCalGetPowerData (int bGetOrFree);
IQMEASURE_API int		LP_PwrCalFreeElement(void);
IQMEASURE_API int		LP_PwrCalFastGetElement(void);
IQMEASURE_API int		LP_FastCalMeasPower (unsigned int start_time, unsigned int  stop_time, double *result);


IQMEASURE_API int		SetTesterHwVersion(double hwVersion);
IQMEASURE_API int		GetTesterHwVersion(double *hwVersion);


IQMEASURE_API int		LP_SetIQmeasureUseInsDrv(int bUseInsDrv = 0);

//! Perform 802.11 ac Analysis on current capture
/*!
* \param[in] mode Valid options are:
*         - "nxn": for true 802.11ac capture
*         - "composite": for a composite capture
*         - "sequential_mimo": for a switched capture
* \param[in] enablePhaseCorr Phase Correction Mode:
*         - 0: Disable
*         - 1: Enable (Default)
* \param[in] enableSymTimingCorr Symbol Timing Correction:
*         - 0: Disable
*         - 1: Enable (Default)
* \param[in] enableAmplitudeTracking Amplitude Tracking:
*         - 0: Disable (Default)
*         - 1: Enable
* \param[in] decodePSDU Decode PSDU:
*         - 0: Disable (Default)
*         - 1: Enable
* \param[in] enableFullPacketChannelEst Channel Estimate on full packet:
*         - 0: Disable (Default)
*         - 1: Enable
* \param[in] frequencyCorr Frequency Correlation:
*         - 1:Frequency correction on short legacy training fields
*         - 2:Frequency correction on long legacy training fields
*         - 3:Frequency correction based on whole packet
*         - 4:Frequency correction on signal fields (legacy and HT) in addition to long training fields
* \param[in] numberOfPacketToAnalysis number of packets to be analyzed for average EVM:
          - 0 means all packet(s),
          - 1 for first packet,
          - 2 for the first 2 packets
          . . . etc
        If number of numberOfPacketToAnalysis is greater than the captured packet, the maximum captured packet (complete packet) will be used
* \param[in] referenceFile PSDU reference file (needed for Composite EVM)
* \param[in] packetFormat indicates format of the 80211AC MIMO packet:
*         - 0: auto-detect mode (Default)
*         - 1: mixed format (11n)
*         - 2: greenfield format (11n)
*         - 3: legacy format (11a/g)
*         - 4: VHT format (11ac)
* \param[in] prePowStartSec indicates the start point of preamble for power measurement result "powerPreambleDbm"(IQxel Only):
          - 8.8e-6: 8.8 micro second (Default)
* \param[in] prePowStopSec indicates the end point of preamble for power measurement result "powerPreambleDbm" (IQxel Only):
*         - 15.2e-6: 15.2 micro second (Default)

*
* \return ERR_OK if the 802.11n analysis succeeded; otherwise call LP_GetErrorString() for detailed error message.
*/
IQMEASURE_API int		LP_Analyze80211ac(char *mode ="nxn",
									int enablePhaseCorr            = 1,
									int enableSymTimingCorr        = 1,
									int enableAmplitudeTracking    = 0,
									int decodePSDU                 = 0,
									int enableFullPacketChannelEst = 0,
									int frequencyCorr = 2,
									char *referenceFile=NULL,
									int packetFormat = 0,
									int numberOfPacketToAnalysis = 1,
									double prePowStartSec = 8.8e-6,
								    double prePowStopSec = 15.2e-6);


//IQMEASURE_API int LpDllGetVersion (char *manufacturer, char* modelNumber, char* serialNumber, char *firmwareRevision);
IQMEASURE_API int		LpDllGetVersion (char *verInfo);
IQMEASURE_API int		LpGetSysError (char *errMsg);
IQMEASURE_API int		LP_LoadUserData(double bufferReal[], double bufferImag[], int bufferLength, double sampleFreqHz);

IQMEASURE_API int		LP_FM_SetAudioToneModeAmplitude(void);// IQlite Merge; Tracy Yu; 2012-04-06
IQMEASURE_API int		LP_FM_SetFrequency(unsigned int carrierFreqHz, double carrierPowerdBm);  // IQlite Merge; Tracy Yu; 2012-04-06
IQMEASURE_API int		LP_FM_SetCarrierPower(double carrierPowerdBm );  // IQlite Merge; Buddy; 2012-04-06

//With these two functions, we can know which tester is used in xxx_Test_Ext.dll.
//Hence, we can determine if HT40 mask test can be tested in some channels.
IQMEASURE_API int       LP_SetTesterName(char * pcName);
IQMEASURE_API char*     LP_GetTesterName();



// MPTA Functions
IQMEASURE_API bool LP_MptaAvailable();
// conflict with IQsequence, removed 8/15/12
//IQMEASURE_API bool LP_MptaGetSerialNumber(char *serialNumber,int buf_size);
IQMEASURE_API int LP_MptaEnable();
IQMEASURE_API int LP_MptaDisable();
IQMEASURE_API int LP_MptaSetupCapture(TX_PATH_ENUM tx_path, double rfFreqHz, double peakSignaldB, double CaptureTimeUs);

IQMEASURE_API int LP_Analyze80211n_Seq(char *type,
                                   int enablePhaseCorr            = 1,
                                   int enableSymTimingCorr        = 1,
                                   int enableAmplitudeTracking    = 0,
                                   int decodePSDU                 = 0,
                                   int enableFullPacketChannelEst = 0,
                                   char *referenceFile			  = NULL,
								   int numSections				  = 2,
								   double sectionLenSec			  = 200e-6);

IQMEASURE_API int LP_AnalyzeObw(double obwPercentage = 0.99);	//0 <= obwPercentage <= 1
IQMEASURE_API int LP_GetResultSpectralMask(int bandwidth_index, double *ViolationPercent, int *length, double *freqs_MHz, double *trace_dBm, double *mask);
IQMEASURE_API int LP_GetResultSpectralMask_HT40(double *ViolationPercent, int *length, double *freqs_MHz, double *trace_dBm, double *mask);

IQMEASURE_API int LP_LoResultSpectralFlatness11AG(int* carrierNo, double* margin, double* loLeakage, bool* flatnessPass, int* sub_carrier, double* data_per_carrier, double* average_center_power);
IQMEASURE_API int LP_LoResultSpectralFlatness11N(int wifiMode, int* carrierNo, double* margin, double* loLeakage, bool* flatnessPass, int* sub_carrier, double* data_per_carrier, double* average_center_power, int streamIndex);  // streamIndex = 0, 1, 2, 3 (zero based)







#endif // end of _IQMEASURE_H_
