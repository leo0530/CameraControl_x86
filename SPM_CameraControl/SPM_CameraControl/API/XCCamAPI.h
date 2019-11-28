// XCCam version 3.01.00 API Header File
// Copyright (C) 2014-2018 TechnoScope Co., Ltd.
#pragma once


#pragma pack( push, 4 )

#ifdef __cplusplus
extern "C" {
#endif

#define XCCAM_LIBRARY_STRUCT_VERSION 30100

#undef	Dllport
#ifdef	_XC_CREATEDLL_
#define	Dllport	__declspec( dllexport ) __cdecl
#else
#define	Dllport	__declspec( dllimport ) __cdecl
#pragma comment( lib, "XCCam" )
#endif

#define	HCAMERA				PVOID
#define	HCTBL				PVOID
#define HNodeMap			PVOID
#define	HFEATURE			PVOID


typedef	enum XCCAM_GIGESTREAMTYPE
{
	XCCAM_GIGEIMAGEDATA		= 1,
	XCCAM_GIGERAWDATA,
	XCCAM_GIGEFILEDATA,
	XCCAM_GIGECHUNKDATA,
	XCCAM_GIGEEXTCHUNKDATA,
	XCCAM_GIGEV2EXTCHUNKDATA = 0x4000,
	XCCAM_GIGEVENDORDATA	= 0x8000,
} XCCAM_GIGESTREAMTYPE;


typedef	enum XCCAM_USBSTREAMTYPE
{
	XCCAM_USBIMAGEDATA		= 1,
	XCCAM_USBCHUNKDATA		= 0x4000,
	XCCAM_USBEXTCHUNKDATA,
} XCCAM_USBSTREAMTYPE;


typedef enum XCCAM_TRANSMITSPEED
{
	XCCAM_S100M				= 0,			//	100M
	XCCAM_S1000M,							//	1G
	XCCAM_SUSB2				= 100,			//	USB 2.0
	XCCAM_SUSB3,							//	USB 3.0
} XCCAM_TRANSMITSPEED;


typedef enum XCCAM_SHIFTID
{
											//	15 14 13 12 ..... 2 1 0
											//
	XCCAM_SFT0				= 0,			//	7-0 bit
	XCCAM_SFT1,								//	8-1 bit
	XCCAM_SFT2,								//	9-2 bit
	XCCAM_SFT3,								//	10-3 bit
	XCCAM_SFT4,								//	11-4 bit
	XCCAM_SFT5,								//	12-5 bit
	XCCAM_SFT6,								//	13-6 bit
	XCCAM_SFT7,								//	14-7 bit
	XCCAM_SFT8,								//	15-8 bit
	XCCAM_SFTAUTO			= -1
} XCCAM_SHIFTID;


typedef enum XCCAM_DIBMODE
{
	XCCAM_DIB32				= 0,			//
	XCCAM_DIB24,							//
} XCCAM_DIBMODE;


typedef enum XCCAM_STOREMODE
{
	XCCAM_MEMmode			= 0,			//	MEMORY mode
	XCCAM_MEMmodeLR,						//	MEMORY mode (Flip horizontal)
	XCCAM_BMPmode,							//	BMP file mode
	XCCAM_BMPmodeLR,						//	BMP file mode (Flip horizontal)
} XCCAM_STOREMODE;


typedef	enum XCCAM_ENDIAN
{
	XCCAM_BIGENDIAN			= 0,			//	Big Endian
	XCCAM_LITTLEENDIAN						//	Little Endian
} XCCAM_ENDIAN;


typedef	enum XCCAM_DEVICETYPE
{
	XCCAM_UNKNOWNDEV		= -1,
	XCCAM_ANYDEV			= 0,
	XCCAM_GIGECAMERA,
	XCCAM_USBCAMERA,
} XCCAM_DEVICETYPE;


typedef enum XCCAM_OPENMODE
{
	XCCAM_AUTO_ACCESS		= 0,
	XCCAM_READONLY_ACCESS,
	XCCAM_CONTROL_ACCESS,
	XCCAM_EXCLUSIVE_ACCESS,
} XCCAM_OPENMODE;


typedef enum XCCAM_FEATURETYPE
{
	XCCAM_INTEGERTYPE		= 0,
	XCCAM_BOOLEANTYPE,
	XCCAM_FLOATTYPE,
	XCCAM_STRINGTYPE,
	XCCAM_COMMANDTYPE,
	XCCAM_ENUMERATIONTYPE,
	XCCAM_CATRGORYTYPE,
	XCCAM_REGISTERTYPE
} XCCAM_FEATURETYPE;


//ステータスコード
typedef enum STATUS_SYSTEMCODE
{
	STATUSXCCAM_POWERUP		= 1,			//	Return from sleep of system
	STATUSXCCAM_DEVICECHANGE,				//	A numerical change in a device is detected
} STATUS_SYSTEMCODE;


typedef enum STATUS_IMAGE
{
	STATUSIMAGE_COMPLETE	= 0,			//	Success Return
	STATUSIMAGE_REQUEST_PENDING,			//	requested is pending completion
	STATUSIMAGE_REQUEST_ERROR,				//	requested is Failure
	STATUSIMAGE_REQUEST_RESTART,			//	requested is Failure
} STATUS_IMAGE;


#pragma warning( push )
#pragma warning( disable : 4200 )


typedef struct XCCAM_GIGEDEVINFO
{
	WORD					Spec_Major;
	WORD					Spec_Minor;
	DWORD					Dev_Mode;
	DWORD					IPConfig;
	DWORD					IPConfigOption;
	BYTE					MACAddr[ 6 ];
	BYTE					IPAddr[ 4 ];
	BYTE					SubMask[ 4 ];
	BYTE					GateWay[ 4 ];
	char					VendorName[ 32 ];
	char					Rsvd;
	char					ModelName[ 32 ];
	char					Rsvd1;
	char					Dev_Ver[ 32 ];
	char					Rsvd2;
	char					Vendor_Info[ 48 ];
	char					Rsvd3;
	char					SerialNumber[ 16 ];
	char					Rsvd4;
	char					UserName[ 16 ];
	DWORD					Rsvd5;
} XCCAM_GIGEDEVINFO, *pXCCAM_GIGEDEVINFO;


typedef struct XCCAM_USBDEVINFO
{
	UINT64					Dev_Capability;
	DWORD					GenCP_Version;
	char					VendorName[ 64 ];
	char					Rsvd;
	char					ModelName[ 64 ];
	char					Rsvd1;
	char					FamilyName[ 64 ];
	char					Rsvd2;
	char					Dev_Version[ 64 ];
	char					Rsvd3;
	char					Vendor_Info[ 64 ];
	char					Rsvd4;
	char					SerialNumber[ 64 ];
	char					Rsvd5;
	char					UserName[ 64 ];
	DWORD					Rsvd6;
} XCCAM_USBDEVINFO, *pXCCAM_USBDEVINFO;


//	XCCAM_CameraInfo
typedef struct XCCAM_DEVINFO
{
	UINT64					UID;
	DWORD					BusNumber;
	XCCAM_DEVICETYPE		DeviceType;
	XCCAM_TRANSMITSPEED		Speed;
	union U
	{
		XCCAM_GIGEDEVINFO		GigEDev;
		XCCAM_USBDEVINFO		UsbDev;
	} u;
} XCCAM_DEVINFO, *pXCCAM_DEVINFO;


//	XCCAM_GetList
typedef struct XCCAM_LIST
{
	DWORD					Count;				//	Number of connected cameras or numbers of Info arrays
	XCCAM_DEVINFO			Info[ 1 ];
} XCCAM_LIST, *pXCCAM_LIST;


//	XCCAM_Open
typedef struct XCCAM_OPENPARAM
{
	XCCAM_DEVICETYPE		DeviceType;
	UINT64					UID;				// Not Zero is AccMode Used
	BYTE					IPAddr[ 4 ];
	char					UserName[ 64 ];
	ULONG					Rsvd;
	XCCAM_OPENMODE			AccMode;
	BOOL					XML_DiskFlag;
} XCCAM_OPENPARAM, *pXCCAM_OPENPARAM;


typedef struct XCCAM_IMAGE
{
	DWORD					Width;
	DWORD					Height;
	BYTE					*pBuffer;
	DWORD					Length;
	DWORD					PixelFormatID;
	XCCAM_ENDIAN			EndianMode;
	STATUS_IMAGE			Status;
} XCCAM_IMAGE, *pXCCAM_IMAGE;


//	XCCAM_StreamComplete
typedef	struct XCCAM_GIGESTREAMINFO
{
	DWORD					Stream_Type;
	UINT64					Fream_ID;
	UINT64					TimeStamp;

	union U
	{
		struct IMAGE
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				Size_Y;
		} Image;

		struct RAW
		{
			UINT64				DataSize;
		} Raw;

		struct FILE
		{
			UINT64				DataSize;
			BYTE				FileName[ 512 ];
		} File;

		struct CHUNK
		{
			DWORD				DataSize;
		} Chunk;

		struct EXT_CHUNK
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				DataSize;
			DWORD				Size_Y;
			DWORD				Chunk_ID;
		} Ext_Chunk;

		struct VENDOR
		{
			BYTE				VendorData[ 512 ];
		} Vendor;
	} u;
} XCCAM_GIGESTREAMINFO, *pXCCAM_GIGESTREAMINFO;


//	XCCAM_StreamComplete
typedef	struct XCCAM_USBSTREAMINFO
{
	DWORD					Stream_Type;
	UINT64					Fream_ID;
	UINT64					TimeStamp;
	UINT64					DataSize;

	union U
	{
		struct IMAGE
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				Size_Y;
		} Image;

		struct CHUNK
		{
			DWORD				Chunk_ID;
		} Chunk;

		struct EXT_CHUNK
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				Size_Y;
			DWORD				Chunk_ID;
		} Ext_Chunk;
	} u;
} XCCAM_USBSTREAMINFO, *pXCCAM_USBSTREAMINFO;


typedef	struct XCCAM_IMAGEDATAINFO
{
	XCCAM_DEVICETYPE		DeviceType;
	union U
	{
		struct CGIGE
		{
			BOOL					Payload_Flag;
			XCCAM_GIGESTREAMINFO	StreamInfo;
		} CGigE;

		struct CUSB
		{
			BOOL					Payload_Flag;
			XCCAM_USBSTREAMINFO		StreamInfo;
		} CUsb;

	} u;
} XCCAM_IMAGEDATAINFO, *pXCCAM_IMAGEDATAINFO;


//	XCCAM_GigEGetPktLog
typedef	struct XCCAM_PKTLOG
{
	UINT64					ToTalPktCount;
	UINT64					ErrorPktCount;
	UINT64					RSendCount;
} XCCAM_PKTLOG, *pXCCAM_PKTLOG;


typedef	struct XCCAM_COLORVALUE
{
	double					R_Value;
	double					G1_Value;
	double					G2_Value;
	double					B_Value;
} XCCAM_COLORVALUE, *pXCCAM_COLORVALUE;


typedef	struct XCCAM_COLORCONVMODE
{
	XCCAM_STOREMODE			StoreMode;
	XCCAM_SHIFTID			ShiftID;
	XCCAM_DIBMODE			DIBMode;
	DWORD					Parallel_Thread;
	BOOL					BayerRevision_G;
} XCCAM_COLORCONVMODE, *pXCCAM_COLORCONVMODE;


//	Event Info
typedef	struct XCCAM_EVENTINFO
{
	USHORT					EventID;
	union U
	{
		struct CGIGE
		{
			WORD					StreamIndex;
			UINT64					BlockID;
			UINT64					TimeStamp;
			DWORD					Length;
			BYTE					Data[ 4 ];
		} CGigE;

		struct CUSB
		{
			UINT64					TimeStamp;
			DWORD					Length;
			BYTE					Data[ 4 ];
		} CUsb;

	} u;
} XCCAM_EVENTINFO, *pXCCAM_EVENTINFO;


//	XCCAM_GetChunkInfoBuffer
//	XCCAM_GetChunkInfoImage
typedef struct XCCAM_CHUNKINFO
{
	DWORD					Count;
	struct INFO
	{
		DWORD					ChunkID;
		DWORD					Length;
		PVOID					pChunkData;
	} Info[1];
} XCCAM_CHUNKINFO, *pXCCAM_CHUNKINFO;


//	XCCAM_FeatureInfo
typedef	struct XCCAM_FEATUREINFO
{
	XCCAM_FEATURETYPE		FType;
	UINT64					PollingTime;
	union U
	{
		struct INTREG
		{
			INT64				MinValue;
			INT64				MaxValue;
			INT64				IncValue;
		} IntReg;

		struct FLOATREG
		{
			double				MinValue;
			double				MaxValue;
			double				IncValue;
			BOOL				HasInc;
		} FloatReg;

		struct STRINGREG
		{
			UINT64				MaxLength;
		} StringReg;

		struct REG
		{
			INT64				Addr;
			UINT64				Length;
		} Reg;
	} u;
} XCCAM_FEATUREINFO, *pXCCAM_FEATUREINFO;


typedef	VOID(CALLBACK* SYSTEMFUNC)(STATUS_SYSTEMCODE Statsu, PVOID Context);
typedef	VOID(CALLBACK* IMAGEFUNC)(HCAMERA hCamera, XCCAM_IMAGE* Image, XCCAM_IMAGEDATAINFO* Info, PVOID Context);
typedef	VOID(CALLBACK* EVENTFUNC)(HCAMERA hCamera, XCCAM_EVENTINFO* EventInfo, PVOID Context);
typedef	VOID(CALLBACK* ACTIONACKFUNC)(UINT64 UID, PVOID Context);


//API------------------------------------------------------------------------------------------------------------
/*	C API Interface Functions	*/
VOID	Dllport XCCAM_SetCallBack(PVOID Context, SYSTEMFUNC SysTemFunc);
BOOL	Dllport XCCAM_SetStructVersion(DWORD Version);
VOID	Dllport XCCAM_GetErrorMsg(char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_GetList(XCCAM_LIST* List);
BOOL	Dllport XCCAM_Open(XCCAM_OPENPARAM* OpenParam, HCAMERA* hCamera);
BOOL	Dllport XCCAM_Close(HCAMERA hCamera);
VOID	Dllport XCCAM_CloseAll(VOID);
BOOL	Dllport XCCAM_Camera(HCAMERA hCamera, BOOL* Connect);
BOOL	Dllport XCCAM_CameraInfo(HCAMERA hCamera, XCCAM_DEVINFO* CInfo);
BOOL	Dllport XCCAM_GetNodeMap(HCAMERA hCamera, HNodeMap* pNodeMap);
BOOL	Dllport XCCAM_GetFeatureHandle(HCAMERA hCamera, HFEATURE* hFeature);
BOOL	Dllport XCCAM_ResourceAlloc(HCAMERA hCamera);
BOOL	Dllport XCCAM_ResourceRelease(HCAMERA hCamera);
BOOL	Dllport XCCAM_SetConvMode(HCAMERA hCamera, XCCAM_COLORCONVMODE* Mode, XCCAM_COLORVALUE* ColorValue);
BOOL	Dllport XCCAM_GetBMPINFO(HCAMERA hCamera, BITMAPINFO* Info, DWORD* Lengeh, BOOL Priority_MONO);
BOOL	Dllport XCCAM_ConvExec(HCAMERA hCamera, XCCAM_IMAGE* Image, BYTE* OutBuf);
BOOL	Dllport XCCAM_GetChunkInfo(HCAMERA hCamera, XCCAM_IMAGE* Image, XCCAM_CHUNKINFO* Info);
BOOL	Dllport XCCAM_ImageStart(HCAMERA hCamera);
BOOL	Dllport XCCAM_ImageStop(HCAMERA hCamera);
BOOL	Dllport XCCAM_ImageAlloc(HCAMERA hCamera, XCCAM_IMAGE** Image);
BOOL	Dllport XCCAM_ImageFree(HCAMERA hCamera, XCCAM_IMAGE* Image);
BOOL	Dllport XCCAM_ImageFreeAll(HCAMERA hCamera);
BOOL	Dllport XCCAM_ImageReq(HCAMERA hCamera, XCCAM_IMAGE* Image);
BOOL	Dllport XCCAM_ImageComplete(HCAMERA hCamera, XCCAM_IMAGE* Image, DWORD TimeOut, XCCAM_IMAGEDATAINFO* Info);
BOOL	Dllport XCCAM_ImageReqAbortAll(HCAMERA hCamera);
BOOL	Dllport XCCAM_VSyncReq(HCAMERA hCamera, PVOID* Hd);
BOOL	Dllport XCCAM_VSyncComplete(HCAMERA hCamera, PVOID Hd, DWORD TimeOut);
BOOL	Dllport XCCAM_SetImageCallBack(HCAMERA hCamera, PVOID Context, IMAGEFUNC ImageFunc, DWORD BufferCount, BOOL InfoSet_Flag);
BOOL	Dllport XCCAM_SetEventCallBack(HCAMERA hCamera, PVOID Context, EVENTFUNC EventFunc);
BOOL	Dllport XCCAM_SetCmdTimeOut(HCAMERA hCamera, DWORD TimeOut);
DWORD	Dllport XCCAM_GetLibraryRevision(VOID);
VOID	Dllport XCCAM_ReDetection(VOID);


/************************************************/
/*	GigE Only API								*/
/************************************************/
BOOL	Dllport XCCAM_ControlCamera(HCAMERA hCamera, BOOL* Yes);
BOOL	Dllport XCCAM_GetGigEPktLog(HCAMERA hCamera, XCCAM_PKTLOG* Log);
BOOL	Dllport XCCAM_TestStream(HCAMERA hCamera, DWORD TimeOut);
BOOL	Dllport XCCAM_ResourceAllocGigE(HCAMERA hCamera, BYTE* IPAddr, BOOL Recover);
BOOL	Dllport XCCAM_HeartbeatMode(HCAMERA hCamera, DWORD TimeOut);
BOOL	Dllport XCCAM_BandAdjust(HCAMERA hCamera, DWORD BandSize);
BOOL	Dllport XCCAM_LostPktMode(HCAMERA hCamera, BOOL LostFlag, BYTE ClearData);
BOOL	Dllport XCCAM_ActionCommand(HCAMERA hCamera, BOOL Unicast, DWORD device_key, DWORD group_key, DWORD group_mask);
BOOL	Dllport XCCAM_ActionCommandAll(DWORD device_key, DWORD group_key, DWORD group_mask);
BOOL	Dllport XCCAM_ActionCommandTime(HCAMERA hCamera, BOOL Unicast, DWORD device_key, DWORD group_key, DWORD group_mask, UINT64 TimeValue);
BOOL	Dllport XCCAM_ActionCommandAllTime(DWORD device_key, DWORD group_key, DWORD group_mask, UINT64 TimeValue);
BOOL	Dllport XCCAM_SetActionAckCallBack(PVOID Context, ACTIONACKFUNC ActionAckFunc);


/************************************************/
/*	USB Only API								*/
/************************************************/
BOOL	Dllport XCCAM_SetPacketSizeUSB(HCAMERA hCamera, ULONG Length);
BOOL	Dllport XCCAM_StreamResetUSB(HCAMERA hCamera);


/************************************************/
/*	Color Conversion API						*/
/************************************************/
BOOL	Dllport XCCAM_CreateConvHandle(HCTBL* hTbl, XCCAM_COLORCONVMODE* CMode, XCCAM_COLORVALUE* CValue);
VOID	Dllport XCCAM_CloseConvHandle(HCTBL hTbl);
VOID	Dllport XCCAM_CloseAllConvHandle(VOID);
BOOL	Dllport XCCAM_ColorConvExec(HCTBL hTbl, XCCAM_IMAGE* Image, BYTE* OutBuf);
BOOL	Dllport XCCAM_ColorConvGetBMPINFO(HCTBL hTbl, XCCAM_IMAGE* Image, BITMAPINFO* Info);
BOOL	Dllport XCCAM_GetMonoBMPINFO(XCCAM_IMAGE* Image, BITMAPINFO* BmpInfo);


/************************************************/
/*	Feature API									*/
/************************************************/
BOOL	Dllport XCCAM_CategoryName(HFEATURE hFeature, DWORD Index, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_FeatureName(HFEATURE hFeature, char* Category, DWORD Index, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_FeatureType(HFEATURE hFeature, char* FeatureName, XCCAM_FEATURETYPE* Type);
BOOL	Dllport XCCAM_FeatureInfo(HFEATURE hFeature, char* FeatureName, XCCAM_FEATUREINFO* Info);
BOOL	Dllport XCCAM_FeatureDisplayName(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_FeatureDescription(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_FeatureToolTip(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_FeatureUnit(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_EnumerationEntryName(HFEATURE hFeature, char* FeatureName, DWORD Index, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_EnumerationEntryDisplayName(HFEATURE hFeature, char* FeatureName, char* EntryName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_EnumerationEntryDescription(HFEATURE hFeature, char* FeatureName, char* EntryName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_EnumerationEntryToolTip(HFEATURE hFeature, char* FeatureName, char* EntryName, char* Buffer, DWORD Length);
BOOL	Dllport XCCAM_EnumerationEntryValue(HFEATURE hFeature, char* FeatureName, char* EntryName, INT64* Value);
BOOL	Dllport XCCAM_EnumerationEntryIsAvailable(HFEATURE hFeature, char* FeatureName, char* EntryName, BOOL* IsAnser);
BOOL	Dllport XCCAM_GetFeatureInteger(HFEATURE hFeature, char* FeatureName, INT64* Value, BOOL CacheClear);
BOOL	Dllport XCCAM_SetFeatureInteger(HFEATURE hFeature, char* FeatureName, INT64 Value);
BOOL	Dllport XCCAM_GetFeatureFloat(HFEATURE hFeature, char* FeatureName, double* Value, BOOL CacheClear);
BOOL	Dllport XCCAM_SetFeatureFloat(HFEATURE hFeature, char* FeatureName, double Value);
BOOL	Dllport XCCAM_GetFeatureString(HFEATURE hFeature, char* FeatureName, char* Value, DWORD Length, BOOL CacheClear);
BOOL	Dllport XCCAM_SetFeatureString(HFEATURE hFeature, char* FeatureName, char* Value);
BOOL	Dllport XCCAM_GetFeatureBoolean(HFEATURE hFeature, char* FeatureName, BOOL* Value, BOOL CacheClear);
BOOL	Dllport XCCAM_SetFeatureBoolean(HFEATURE hFeature, char* FeatureName, BOOL Value);
BOOL	Dllport XCCAM_GetFeatureEnumeration(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length, BOOL CacheClear);
BOOL	Dllport XCCAM_SetFeatureEnumeration(HFEATURE hFeature, char* FeatureName, char* Buffer);
BOOL	Dllport XCCAM_GetFeatureRegister(HFEATURE hFeature, char* FeatureName, BYTE* Buffer, DWORD Length, BOOL CacheClear);
BOOL	Dllport XCCAM_SetFeatureRegister(HFEATURE hFeature, char* FeatureName, BYTE* Buffer, DWORD Length);
BOOL	Dllport XCCAM_FeatureCommand(HFEATURE hFeature, char* FeatureName);
BOOL	Dllport XCCAM_FeatureIsAvailable(HFEATURE hFeature, char* FeatureName, BOOL* IsAnser);
BOOL	Dllport XCCAM_FeatureIsWritable(HFEATURE hFeature, char* FeatureName, BOOL* IsAnser);
BOOL	Dllport XCCAM_FeatureIsReadable(HFEATURE hFeature, char* FeatureName, BOOL* IsAnser);


#ifdef __cplusplus
}
#endif

#pragma warning( pop )
#pragma pack( pop )
