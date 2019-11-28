//
// CSonyCam Class 3.01.00 Header File
//

#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <objbase.h>
#include <gdiplus.h>

#include "XCCamAPI.h"
#include "XCCamExtensionsAPI.h"
#include "XCCamAVIFileAPI.h"
#define GENICAM_USER_ALWAYS_LINK_RELEASE
#include "GenApi/GenApi.h"
#undef interface



#define TestPktTimeOut 50


#define ImageBMP L"image/bmp"
#define ImageJPEG L"image/jpeg"
#define ImageTIFF L"image/tiff"
#define ImageGIF L"image/gif"
#define ImagePNG L"image/png"


#pragma comment( lib, "gdiplus" )


static VOID CALLBACK ImageCB( HCAMERA hCamera, XCCAM_IMAGE* Image, XCCAM_IMAGEDATAINFO* Info, PVOID Context );


struct	Image_Buffer
{
public:
	Image_Buffer(void* pBuffer)
		: m_pBuf(pBuffer)
		, m_hEvent()
	{
		m_hEvent = ::CreateEvent(NULL, true, false, NULL);
	}

	Image_Buffer(const std::wstring FName, const std::wstring ImageType)
		: m_pBuf()
		, m_hEvent()
		, m_sFileName(FName)
		, m_sImageType(ImageType)
	{
		m_hEvent = ::CreateEvent(NULL, true, false, NULL);
	}

	virtual ~Image_Buffer(void)
	{
		::CloseHandle(m_hEvent);
	}


	void* m_pBuf;
	HANDLE m_hEvent;
	std::wstring m_sFileName;
	std::wstring m_sImageType;

private:
	Image_Buffer(const Image_Buffer&);
	const Image_Buffer& operator = (const Image_Buffer&);
};


class CSonyCam
{
public:
	CSonyCam(const UINT64 UID = 0, XCCAM_DIBMODE DIBCount = XCCAM_DIB32, DWORD Parallel_Thread = 4)
		: m_hCamera()
		, m_pNodeMap()
		, m_bStart_Flag()
		, m_pNewImage()
		, m_pMonoBuffer()
		, m_pDIBBuffer()
		, m_DIBCount(DIBCount)
		, m_Parallel_Thread(Parallel_Thread)
		, m_pBitMapInfo()
		, m_pRGBBitMapInfo()
		, m_iDIBWidth()
		, m_iDIBHeight()
		, m_pImageCodecInfo()
		, m_ImageCount()
		, m_AviFile()
	{
		UINT Len = 0;
		BOOL rtn;
		HNodeMap pMap;
		XCCAM_OPENPARAM OpenReq = {};

		::InitializeCriticalSection(&m_Queue_Section);
		::XCCAM_ExtensionsStart();
		::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

		if(Gdiplus::GetImageEncodersSize(&m_ImageCount, &Len))
			throw "GetImageEncodersSize Error";
		if(!Len)
			throw "GetImageEncodersSize Error";

		try
		{
			m_pImageCodecInfo = (Gdiplus::ImageCodecInfo*)new BYTE[ Len ];
		}
		catch(...)
		{
			throw "Memory Alloc Error";
		}

		if(Gdiplus::GetImageEncoders(m_ImageCount, Len, m_pImageCodecInfo))
			throw "GetImageEncodersSize Error";

		OpenReq.UID = UID;
		rtn = ::XCCAM_Open(&OpenReq, &m_hCamera);
		if(!rtn)
			throw "Camera Not Found";

		rtn = ::XCCAM_GetNodeMap(m_hCamera, &pMap);
		if(!rtn)
			throw "Get NodeMap Error";
		m_pNodeMap = (GenApi::CNodeMapRef*)pMap;
	}


	CSonyCam(const std::string& UserName, XCCAM_DIBMODE DIBCount = XCCAM_DIB32, DWORD Parallel_Thread = 4)
		: m_hCamera()
		, m_pNodeMap()
		, m_bStart_Flag()
		, m_pNewImage()
		, m_pMonoBuffer()
		, m_pDIBBuffer()
		, m_DIBCount(DIBCount)
		, m_Parallel_Thread(Parallel_Thread)
		, m_pBitMapInfo()
		, m_pRGBBitMapInfo()
		, m_iDIBWidth()
		, m_iDIBHeight()
		, m_pImageCodecInfo()
		, m_ImageCount()
		, m_AviFile()
	{
		UINT Len = 0;
		BOOL rtn;
		XCCAM_OPENPARAM OpenReq = {};
		HNodeMap pMap;

		::InitializeCriticalSection(&m_Queue_Section);
		::XCCAM_ExtensionsStart();
		::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

		if(Gdiplus::GetImageEncodersSize(&m_ImageCount, &Len))
			throw "GetImageEncodersSize Error";
		if(!Len)
			throw "GetImageEncodersSize Error";

		try
		{
			m_pImageCodecInfo = (Gdiplus::ImageCodecInfo*)new BYTE[ Len ];
		}
		catch(...)
		{
			throw "Memory Alloc Error";
		}

		if(Gdiplus::GetImageEncoders(m_ImageCount, Len, m_pImageCodecInfo))
			throw "GetImageEncodersSize Error";

		::strcpy_s((char*)&OpenReq.UserName[ 0 ], sizeof(OpenReq.UserName), UserName.c_str());
		rtn = ::XCCAM_Open(&OpenReq, &m_hCamera);
		if(!rtn)
			throw "Camera Not Found";

		rtn = ::XCCAM_GetNodeMap(m_hCamera, &pMap);
		if(!rtn)
			throw "Get NodeMap Error";
		m_pNodeMap = (GenApi::CNodeMapRef*)pMap;
	}


	CSonyCam(XCCAM_OPENPARAM& OpenReq, XCCAM_DIBMODE DIBCount = XCCAM_DIB32, DWORD Parallel_Thread = 4)
		: m_hCamera()
		, m_pNodeMap()
		, m_bStart_Flag()
		, m_pNewImage()
		, m_pMonoBuffer()
		, m_pDIBBuffer()
		, m_DIBCount(DIBCount)
		, m_Parallel_Thread(Parallel_Thread)
		, m_pBitMapInfo()
		, m_pRGBBitMapInfo()
		, m_iDIBWidth()
		, m_iDIBHeight()
		, m_pImageCodecInfo()
		, m_ImageCount()
		, m_AviFile()
	{
		UINT Len = 0;
		BOOL rtn;
		HNodeMap pMap;

		::InitializeCriticalSection(&m_Queue_Section);
		::XCCAM_ExtensionsStart();
		::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

		if(Gdiplus::GetImageEncodersSize(&m_ImageCount, &Len))
			throw "GetImageEncodersSize Error";
		if(!Len)
			throw "GetImageEncodersSize Error";

		try
		{
			m_pImageCodecInfo = (Gdiplus::ImageCodecInfo*)new BYTE[ Len ];
		}
		catch(...)
		{
			throw "Memory Alloc Error";
		}

		if(Gdiplus::GetImageEncoders(m_ImageCount, Len, m_pImageCodecInfo))
			throw "GetImageEncodersSize Error";

		rtn = ::XCCAM_Open(&OpenReq, &m_hCamera);
		if(!rtn)
			throw "Camera Not Found";

		rtn = ::XCCAM_GetNodeMap(m_hCamera, &pMap);
		if(!rtn)
			throw "Get NodeMap Error";
		m_pNodeMap = (GenApi::CNodeMapRef*)pMap;
	}


	virtual ~CSonyCam(void)
	{
		if(m_bStart_Flag)
			StreamStop();

		if(m_hCamera)
			::XCCAM_Close(m_hCamera);

		::DeleteCriticalSection(&m_Queue_Section);

		if(m_AviFile)
			::XCCAM_AVIFileClose(m_AviFile);

		if(m_pMonoBuffer)
			delete[] m_pMonoBuffer;
		if(m_pDIBBuffer)
			delete[] m_pDIBBuffer;
		if(m_pBitMapInfo)
			delete[] m_pBitMapInfo;
		if(m_pRGBBitMapInfo)
			delete[] m_pRGBBitMapInfo;
		if(m_pImageCodecInfo)
			delete[] m_pImageCodecInfo;
	}


	std::string GetVendorName(void)
	{
		BOOL rtn;
		XCCAM_DEVINFO Info;


		rtn = ::XCCAM_CameraInfo(m_hCamera, &Info);
		if(!rtn)
			return "";

		switch(Info.DeviceType)
		{
		case XCCAM_GIGECAMERA:
			return (char*)Info.u.GigEDev.VendorName;
			break;
		case XCCAM_USBCAMERA:
			return (char*)Info.u.UsbDev.VendorName;
			break;
		}
		return "";
	}


	std::string GetModelName(void)
	{
		BOOL rtn;
		XCCAM_DEVINFO Info;


		rtn = ::XCCAM_CameraInfo(m_hCamera, &Info);
		if(!rtn)
			return "";

		switch(Info.DeviceType)
		{
		case XCCAM_GIGECAMERA:
			return (char*)Info.u.GigEDev.ModelName;
			break;
		case XCCAM_USBCAMERA:
			return (char*)Info.u.UsbDev.ModelName;
			break;
		}
		return "";
	}


	std::string GetSerialNumber(void)
	{
		BOOL rtn;
		XCCAM_DEVINFO Info;


		rtn = ::XCCAM_CameraInfo(m_hCamera, &Info);
		if(!rtn)
			return "";

		switch(Info.DeviceType)
		{
		case XCCAM_GIGECAMERA:
			return (char*)Info.u.GigEDev.SerialNumber;
			break;
		case XCCAM_USBCAMERA:
			return (char*)Info.u.UsbDev.SerialNumber;
			break;
		}
		return "";
	}


	UINT64 GetUniqueID(void)
	{
		BOOL rtn;
		XCCAM_DEVINFO Info;


		rtn = ::XCCAM_CameraInfo(m_hCamera, &Info);
		if(!rtn)
			return 0;

		return Info.UID;
	}


	PBITMAPINFO GetBMPINFO(void)
	{
		ULONG Length = 0;
		BOOL rtn = ::XCCAM_GetBMPINFO(m_hCamera, NULL, &Length, FALSE);
		if(!rtn)
			return NULL;

		if(m_pRGBBitMapInfo)
		{
			delete[] m_pRGBBitMapInfo;
			m_pRGBBitMapInfo = NULL;
		}

		try
		{
			m_pRGBBitMapInfo = (BITMAPINFO*)new BYTE[ Length ];
		}
		catch(...)
		{
			m_pRGBBitMapInfo = NULL;
			return NULL;
		}

		rtn = ::XCCAM_GetBMPINFO(m_hCamera, m_pRGBBitMapInfo, &Length, FALSE);
		if(!rtn)
			return NULL;

		return m_pRGBBitMapInfo;
	}

	ULONG GetVersion(void)
	{
		BOOL rtn;
		XCCAM_DEVINFO Info;


		rtn = ::XCCAM_CameraInfo(m_hCamera, &Info);
		if(!rtn)
			return 0;

		switch(Info.DeviceType)
		{
		case XCCAM_GIGECAMERA:
			return (Info.u.GigEDev.Spec_Major << 16) | Info.u.GigEDev.Spec_Minor;
			break;
		case XCCAM_USBCAMERA:
			return Info.u.UsbDev.GenCP_Version;
			break;
		}
		return 0;
	}


	void* GetNodeMap(void) { return m_pNodeMap; }


	bool GetFeature(const char* FName, INT64& Value)
	{
		std::string strFName = FName;
		return GetFeature(strFName, Value);
		\
	}


	bool GetFeature(const std::string FName, INT64& Value)
	{
		GenApi::INode* pNode = m_pNodeMap->_GetNode(FName.c_str());

		if(!pNode)
			return false;
		if(!GenApi::IsAvailable(pNode))
			return false;
		if(!GenApi::IsReadable(pNode))
			return false;

		switch(pNode->GetPrincipalInterfaceType())
		{
		case GenApi::intfIInteger:
			{
				GenApi::CIntegerPtr ptrInt = pNode;
				Value = *ptrInt();
				return true;
			}

		case GenApi::intfIEnumeration:
			{
				GenApi::CEnumerationPtr ptrEnum = pNode;
				GenApi::CEnumEntryPtr ptrEnt = ptrEnum->GetCurrentEntry();
				Value = ptrEnt->GetValue();
				return true;
			}

		case GenApi::intfIFloat:
			{
				GenApi::CFloatPtr ptrFloat = pNode;
				Value = (INT64)*ptrFloat();
				return true;
			}
		}
		return false;
	}


	bool GetFeature(const char* FName, double& Value)
	{
		std::string strFName = FName;
		return GetFeature(strFName, Value);
	}


	bool GetFeature(const std::string FName, double& Value)
	{
		GenApi::INode* pNode = m_pNodeMap->_GetNode(FName.c_str());

		if(!pNode)
			return false;
		if(!GenApi::IsAvailable(pNode))
			return false;
		if(!GenApi::IsReadable(pNode))
			return false;

		switch(pNode->GetPrincipalInterfaceType())
		{
		case GenApi::intfIInteger:
			{
				GenApi::CIntegerPtr ptrInt = pNode;
				Value = (double)*ptrInt();
				return true;
			}

		case GenApi::intfIEnumeration:
			{
				GenApi::CEnumerationPtr ptrEnum = pNode;
				GenApi::CEnumEntryPtr ptrEnt = ptrEnum->GetCurrentEntry();
				Value = (double)ptrEnt->GetValue();
				return true;
			}

		case GenApi::intfIFloat:
			{
				GenApi::CFloatPtr ptrFloat = pNode;
				Value = *ptrFloat();
				return true;
			}
		}
		return false;;
	}


	bool GetFeature(const char* FName, std::string& Value)
	{
		std::string strFName = FName;
		return GetFeature(strFName, Value);
	}


	bool GetFeature(const std::string FName, std::string& Value)
	{
		GenApi::INode* pNode = m_pNodeMap->_GetNode(FName.c_str());

		if(!pNode)
			return false;
		if(!GenApi::IsAvailable(pNode))
			return false;
		if(!GenApi::IsReadable(pNode))
			return false;

		switch(pNode->GetPrincipalInterfaceType())
		{
		case GenApi::intfIString:
			{
				GenApi::CStringPtr ptrString = pNode;
				Value = ptrString->GetValue();
				return true;
			}

		case GenApi::intfIEnumeration:
			{
				GenApi::CEnumerationPtr ptrEnum = pNode;
				GenApi::CEnumEntryPtr ptrEnt = ptrEnum->GetCurrentEntry();
				Value = ptrEnt->GetSymbolic();
				return true;
			}
		}
		return false;
	}


	bool GetFeature(const char* FName, BYTE& Value, UINT32& Length)
	{
		std::string strFName = FName;
		return GetFeature(strFName, Value, Length);
	}


	bool GetFeature(const  std::string FName, BYTE& Value, UINT32& Length)
	{
		GenApi::CRegisterPtr ptrReg = m_pNodeMap->_GetNode(FName.c_str());
		INT64 Len;

		if(!ptrReg)
			return false;
		if(!GenApi::IsAvailable(ptrReg))
			return false;
		if(!GenApi::IsReadable(ptrReg))
			return false;

		Len = ptrReg->GetLength();
		if(Len > Length)
			Len = Length;

		ptrReg->Get(&Value, Len);

		Length = (UINT32)Len;
		return true;
	}


	bool GetFeature(const char* FName, bool& Value)
	{
		std::string strFName = FName;
		return GetFeature(strFName, Value);
	}


	bool GetFeature(const std::string FName, bool& Value)
	{
		GenApi::CBooleanPtr ptrBool = m_pNodeMap->_GetNode(FName.c_str());

		if(!ptrBool)
			return false;
		if(!GenApi::IsAvailable(ptrBool))
			return false;
		if(!GenApi::IsReadable(ptrBool))
			return false;

		Value = ptrBool->GetValue();
		return true;
	}


	bool SetFeature(const char* FName, const INT64 Value)
	{
		std::string strFName = FName;
		return SetFeature(strFName, Value);
	}


	bool SetFeature(const std::string FName, const INT64 Value)
	{
		GenApi::INode* pNode = m_pNodeMap->_GetNode(FName.c_str());

		if(!pNode)
			return false;
		if(!GenApi::IsAvailable(pNode))
			return false;
		if(!GenApi::IsWritable(pNode))
			return false;

		switch(pNode->GetPrincipalInterfaceType())
		{
		case GenApi::intfIInteger:
			{
				GenApi::CIntegerPtr ptrInt = pNode;
				*ptrInt = Value;
				return true;
			}

		case GenApi::intfIEnumeration:
			{
				GenApi::CEnumerationPtr ptrEnum = pNode;
				ptrEnum->SetIntValue(Value);
				return true;
			}

		case GenApi::intfIFloat:
			{
				GenApi::CFloatPtr ptrFloat = pNode;
				*ptrFloat = (double)Value;
				return true;
			}
		}
		return false;
	}


	bool SetFeature(const char* FName, const double Value)
	{
		std::string strFName = FName;
		return SetFeature(strFName, Value);
	}


	bool SetFeature(const std::string FName, const double Value)
	{
		GenApi::INode* pNode = m_pNodeMap->_GetNode(FName.c_str());

		if(!pNode)
			return false;
		if(!GenApi::IsAvailable(pNode))
			return false;
		if(!GenApi::IsWritable(pNode))
			return false;

		switch(pNode->GetPrincipalInterfaceType())
		{
		case GenApi::intfIInteger:
			{
				GenApi::CIntegerPtr ptrInt = pNode;
				*ptrInt = (INT64)Value;
				return true;
			}

		case GenApi::intfIEnumeration:
			{
				GenApi::CEnumerationPtr ptrEnum = pNode;
				ptrEnum->SetIntValue((INT64)Value);
				return true;
			}

		case GenApi::intfIFloat:
			{
				GenApi::CFloatPtr ptrFloat = pNode;
				*ptrFloat = Value;
				return true;
			}
		}
		return false;
	}


	bool SetFeature(const char* FName, const char* Value)
	{
		std::string strFName = FName;
		std::string strValue = Value;
		return SetFeature(strFName, strValue);
	}


	bool SetFeature(const std::string FName, const std::string Value)
	{
		GenApi::INode* pNode = m_pNodeMap->_GetNode(FName.c_str());

		if(!pNode)
			return false;
		if(!GenApi::IsAvailable(pNode))
			return false;
		if(!GenApi::IsWritable(pNode))
			return false;

		switch(pNode->GetPrincipalInterfaceType())
		{
		case GenApi::intfIString:
			{
				GenApi::CStringPtr ptrString = pNode;
				*ptrString = Value.c_str();
				return true;
			}

		case GenApi::intfIEnumeration:
			{
				GenApi::CEnumerationPtr ptrEnum = pNode;
				*ptrEnum = Value.c_str();
				return true;
			}
		}
		return false;
	}


	bool SetFeature(const char* FName, BYTE& Value, UINT32& Length)
	{
		std::string strFName = FName;
		return SetFeature(strFName, Value, Length);
	}


	bool SetFeature(const std::string FName, BYTE& Value, UINT32& Length)
	{
		GenApi::CRegisterPtr ptrReg = m_pNodeMap->_GetNode(FName.c_str());
		INT64 Len;

		if(!ptrReg)
			return false;
		if(!GenApi::IsAvailable(ptrReg))
			return false;
		if(!GenApi::IsWritable(ptrReg))
			return false;

		Len = ptrReg->GetLength();
		if(Len > Length)
			Len = Length;

		ptrReg->Set(&Value, Len);

		Length = (UINT32)Len;
		return true;
	}


	bool SetFeature(const char* FName, const bool Value)
	{
		std::string strFName = FName;
		return SetFeature(strFName, Value);
	}


	bool SetFeature(const std::string FName, const bool Value)
	{
		GenApi::CBooleanPtr ptrBool = m_pNodeMap->_GetNode(FName.c_str());

		if(!ptrBool)
			return false;
		if(!GenApi::IsAvailable(ptrBool))
			return false;
		if(!GenApi::IsWritable(ptrBool))
			return false;

		*ptrBool = Value;
		return true;
	}


	bool SetFeature(const char* FName)
	{
		std::string strFName = FName;
		return SetFeature(strFName);
	}


	bool SetFeature(const std::string FName)
	{
		GenApi::CCommandPtr ptrCmd = m_pNodeMap->_GetNode(FName.c_str());

		if(!ptrCmd)
			return false;
		if(!GenApi::IsAvailable(ptrCmd))
			return false;
		if(!GenApi::IsWritable(ptrCmd))
			return false;

		ptrCmd->Execute();
		return true;
	}


	bool StreamStart(void)
	{
		BOOL rtn;
		ULONG Length;
		XCCAM_COLORCONVMODE Mode = {};
		Mode.StoreMode = XCCAM_BMPmode;
		Mode.DIBMode = m_DIBCount;
		Mode.Parallel_Thread = m_Parallel_Thread;

		if(m_bStart_Flag)
			return false;

		m_CallCount = 0;
		m_DIBCallCount = 0;

		m_pNewImage = NULL;

		rtn = ::XCCAM_SetConvMode(m_hCamera, &Mode, NULL);
		if(!rtn)
			return false;

		rtn = ::XCCAM_ResourceAlloc(m_hCamera);
		if(!rtn)
			return false;

		Length = 0;
		rtn = ::XCCAM_GetBMPINFO(m_hCamera, NULL, &Length, TRUE);
		if(!rtn)
		{
			::XCCAM_ResourceRelease(m_hCamera);
			return false;
		}

		if(m_pBitMapInfo)
		{
			delete[] m_pBitMapInfo;
			m_pBitMapInfo = NULL;
		}

		try
		{
			m_pBitMapInfo = (BITMAPINFO*)new BYTE[ Length ];
		}
		catch(...)
		{
			m_pBitMapInfo = NULL;
			::XCCAM_ResourceRelease(m_hCamera);
			return false;
		}

		rtn = ::XCCAM_GetBMPINFO(m_hCamera, m_pBitMapInfo, &Length, TRUE);
		if(!rtn)
		{
			::XCCAM_ResourceRelease(m_hCamera);
			return false;
		}

		rtn = ::XCCAM_SetImageCallBack(m_hCamera, this, ImageCB, 5, FALSE);
		if(!rtn)
		{
			::XCCAM_ResourceRelease(m_hCamera);
			return false;
		}

		rtn = ::XCCAM_ImageStart(m_hCamera);
		if(!rtn)
		{
			::XCCAM_SetImageCallBack(m_hCamera, NULL, NULL, 0, FALSE);
			::XCCAM_ResourceRelease(m_hCamera);
			return false;
		}

		m_bStart_Flag = true;
		return true;
	}


	bool StreamStop(void)
	{
		if(!m_bStart_Flag)
			return false;

		::XCCAM_ImageStop(m_hCamera);
		::XCCAM_SetImageCallBack(m_hCamera, NULL, NULL, 0, FALSE);
		::XCCAM_ResourceRelease(m_hCamera);

		::EnterCriticalSection(&m_Queue_Section);
		while(!m_Queue_List.empty())
		{
			delete m_Queue_List[ 0 ];
			m_Queue_List.erase(m_Queue_List.begin());
		}
		while(!m_QueueFile_List.empty())
		{
			delete m_QueueFile_List[ 0 ];
			m_QueueFile_List.erase(m_QueueFile_List.begin());
		}
		::LeaveCriticalSection(&m_Queue_Section);

		m_bStart_Flag = false;
		return true;
	}


	bool SetMaxPacketSize(void)
	{
		bool Add_Flag = ::XCCAM_TestStream(m_hCamera, TestPktTimeOut) ? true : false;
		GenApi::CIntegerPtr ptrInt = m_pNodeMap->_GetNode("GevSCPSPacketSize");

		if(!ptrInt)
		{
			GenApi::CIntegerPtr pSel = m_pNodeMap->_GetNode("DeviceStreamChannelSelector");
			if(pSel)
			{
				if(GenApi::IsWritable(pSel))
					*pSel = pSel->GetMin();
			}
			ptrInt = m_pNodeMap->_GetNode("DeviceStreamChannelPacketSize");
			if(!ptrInt)
				return false;
		}

		ULONG Count = (ULONG)((*ptrInt() - ptrInt->GetMin()) / ptrInt->GetInc());

		while(true)
		{
			if(Add_Flag)
				Count++;
			else
				if(Count)
					Count--;

			INT64 PktSize = ptrInt->GetInc() * Count + ptrInt->GetMin();

			if(PktSize > ptrInt->GetMax())
				break;

			INT64 SavePkt = *ptrInt();
			*ptrInt = PktSize;

			BOOL rtn = ::XCCAM_TestStream(m_hCamera, TestPktTimeOut);

			if(Add_Flag && !rtn)
			{
				*ptrInt = SavePkt;
				break;
			}
			if(!Add_Flag && rtn)
				break;

			if(PktSize <= ptrInt->GetMin())
				break;
		}

		return ::XCCAM_TestStream(m_hCamera, TestPktTimeOut) ? true : false;
	}


	bool Capture(void* pBuffer)
	{
		if(!m_pNewImage)
			return false;

		try
		{
			::XCCAM_ConvExec(m_hCamera, m_pNewImage, (BYTE*)pBuffer);
		}
		catch(...)
		{
		}
		return true;
	}


	bool QueueCapture(void* pBuffer)
	{
		Image_Buffer* pQbuf;


		::EnterCriticalSection(&m_Queue_Section);

		for(std::vector<Image_Buffer*>::iterator Iter = m_Queue_List.begin(); Iter != m_Queue_List.end(); Iter++)
		{
			if((*Iter)->m_pBuf == pBuffer)
			{
				::LeaveCriticalSection(&m_Queue_Section);
				return false;
			}
		}

		try
		{
			pQbuf = new Image_Buffer(pBuffer);
		}
		catch(...)
		{
			pQbuf = NULL;
		}
		if(pQbuf)
			m_Queue_List.push_back(pQbuf);

		::LeaveCriticalSection(&m_Queue_Section);

		return pQbuf ? true : false;
	}


	bool QueueCaptureComplete(void* pBuffer, const UINT32 TimeOut)
	{
		std::vector<Image_Buffer*>::iterator Iter;
		ULONG rtn = WAIT_ABANDONED;


		::EnterCriticalSection(&m_Queue_Section);

		for(Iter = m_Queue_List.begin(); Iter != m_Queue_List.end(); Iter++)
		{
			if((*Iter)->m_pBuf == pBuffer)
				break;
		}
		if(Iter != m_Queue_List.end())
		{
			::LeaveCriticalSection(&m_Queue_Section);
			rtn = ::WaitForSingleObject((*Iter)->m_hEvent, TimeOut);
			::EnterCriticalSection(&m_Queue_Section);
			if(rtn == WAIT_OBJECT_0)
			{
				delete *Iter;
				m_Queue_List.erase(Iter);
			}
		}

		::LeaveCriticalSection(&m_Queue_Section);
		return rtn == WAIT_OBJECT_0 ? true : false;
	}


	bool CaptureFile(const WCHAR* FName, const WCHAR* ImageType)
	{
		std::wstring strFName = FName;
		std::wstring strImageType = ImageType;
		return CaptureFile(strFName, strImageType);
	}


	bool CaptureFile(const std::wstring& FName, const std::wstring& ImageType)
	{
		if(!m_pNewImage)
			return false;

		return SaveImageFile(FName, ImageType);
	}


	bool QueueCaptureFile(const WCHAR* FName, const WCHAR* ImageType)
	{
		std::wstring strFName = FName;
		std::wstring strImageType = ImageType;
		return QueueCaptureFile(strFName, strImageType);
	}


	bool QueueCaptureFile(const std::wstring& FName, const std::wstring& ImageType)
	{
		CLSID Clsid;
		Image_Buffer* pQbuf;


		if(!GetEncoderClsid(ImageType, Clsid))
			return false;


		::EnterCriticalSection(&m_Queue_Section);

		for(std::vector<Image_Buffer*>::iterator Iter = m_QueueFile_List.begin(); Iter != m_QueueFile_List.end(); Iter++)
		{
			if((*Iter)->m_sFileName == FName)
			{
				::LeaveCriticalSection(&m_Queue_Section);
				return false;
			}
		}

		try
		{
			pQbuf = new Image_Buffer(FName, ImageType);
		}
		catch(...)
		{
			pQbuf = NULL;
		}
		if(pQbuf)
			m_QueueFile_List.push_back(pQbuf);

		::LeaveCriticalSection(&m_Queue_Section);

		return pQbuf ? true : false;
	}


	bool QueueCaptureFileComplete(const WCHAR* FName, const UINT32 TimeOut)
	{
		std::wstring strFName = FName;
		return QueueCaptureFileComplete(strFName, TimeOut);
	}


	bool QueueCaptureFileComplete(const std::wstring& FName, const UINT32 TimeOut)
	{
		std::vector<Image_Buffer*>::iterator Iter;
		ULONG rtn = WAIT_ABANDONED;


		::EnterCriticalSection(&m_Queue_Section);
		for(Iter = m_QueueFile_List.begin(); Iter != m_QueueFile_List.end(); Iter++)
		{
			if((*Iter)->m_sFileName == FName)
				break;
		}
		if(Iter != m_QueueFile_List.end())
		{
			::LeaveCriticalSection(&m_Queue_Section);
			rtn = ::WaitForSingleObject((*Iter)->m_hEvent, TimeOut);
			::EnterCriticalSection(&m_Queue_Section);
			if(rtn == WAIT_OBJECT_0)
			{
				delete *Iter;
				m_QueueFile_List.erase(Iter);
			}
		}
		::LeaveCriticalSection(&m_Queue_Section);
		return rtn == WAIT_OBJECT_0 ? true : false;
	}


	bool CaptureAVIFile(const WCHAR* FName, const UINT32 Rate)
	{
		std::wstring strFName = FName;
		return CaptureAVIFile(strFName, Rate);
	}


	bool CaptureAVIFile(const std::wstring& FName, const UINT32 Rate)
	{
		BOOL rtn;

		::EnterCriticalSection(&m_Queue_Section);
		rtn = ::XCCAM_AVIFileOpen((WCHAR*)FName.c_str(), Rate, &m_AviFile);
		::LeaveCriticalSection(&m_Queue_Section);
		return rtn ? true : false;
	}


	void CaptureAVIFile(void)
	{
		::EnterCriticalSection(&m_Queue_Section);
		::XCCAM_AVIFileClose(m_AviFile);
		m_AviFile = NULL;
		::LeaveCriticalSection(&m_Queue_Section);
	}


	static XCCAM_LIST* GetCameraList(void)
	{
		ULONG Count = 0;


		::XCCAM_SetStructVersion(XCCAM_LIBRARY_STRUCT_VERSION);

		if(m_pCameraList)
		{
			delete m_pCameraList;
			m_pCameraList = NULL;
		}

		do
		{
			if(!::XCCAM_GetList((XCCAM_LIST*)&Count))
				break;

			m_pCameraList = (XCCAM_LIST*)new BYTE[ sizeof(ULONG) + sizeof(XCCAM_DEVINFO) * Count ];
			m_pCameraList->Count = Count;

			if(!::XCCAM_GetList(m_pCameraList))
				break;

			return m_pCameraList;

		} while(false);

		if(m_pCameraList)
		{
			delete m_pCameraList;
			m_pCameraList = NULL;
		}

		m_pCameraList = new XCCAM_LIST;
		m_pCameraList->Count = 0;
		return m_pCameraList;
	}


	void ImageProc(XCCAM_IMAGE* pImage)
	{
		std::vector<Image_Buffer*>::iterator Iter;

		m_pNewImage = pImage;
		m_iWidth = pImage->Width;
		m_iHeight = pImage->Height;
		m_CallCount++;

		::EnterCriticalSection(&m_Queue_Section);
		if(m_AviFile)
		{
			if(m_CallCount == 1)
				::XCCAM_AVIFileSetInfo(m_AviFile, m_iWidth, m_iHeight, m_pBitMapInfo->bmiHeader.biBitCount);
			if(m_pBitMapInfo->bmiHeader.biBitCount == 8)
			{
				if(MonoConv())
					::XCCAM_AVIFileWrite(m_AviFile, (BYTE*)m_pMonoBuffer, m_iDIBLength);
			}
			else
			{
				if(ConvBMP())
					::XCCAM_AVIFileWrite(m_AviFile, (BYTE*)m_pDIBBuffer, m_iDIBLength);
			}
		}
		for(Iter = m_Queue_List.begin(); Iter != m_Queue_List.end(); Iter++)
		{
			if(::WaitForSingleObject((*Iter)->m_hEvent, 0) == WAIT_TIMEOUT)
			{
				try
				{
					::XCCAM_ConvExec(m_hCamera, pImage, (BYTE*)(*Iter)->m_pBuf);
				}
				catch(...)
				{
				}
				::SetEvent((*Iter)->m_hEvent);
				break;
			}
		}
		for(Iter = m_QueueFile_List.begin(); Iter != m_QueueFile_List.end(); Iter++)
		{
			if(::WaitForSingleObject((*Iter)->m_hEvent, 0) == WAIT_TIMEOUT)
			{
				SaveImageFile((*Iter)->m_sFileName, (*Iter)->m_sImageType);
				::SetEvent((*Iter)->m_hEvent);
				break;
			}
		}
		::LeaveCriticalSection(&m_Queue_Section);
	}

	static XCCAM_LIST* m_pCameraList;


private:
	CSonyCam( const CSonyCam& );
	const CSonyCam& operator = ( const CSonyCam& );


protected:
	HCAMERA m_hCamera;
	GenApi::CNodeMapRef* m_pNodeMap;
	bool m_bStart_Flag;
	XCCAM_IMAGE *m_pNewImage;
	void* m_pMonoBuffer;
	void* m_pDIBBuffer;
	ULONG m_iDIBWidth;
	ULONG m_iDIBHeight;
	ULONG m_iDIBLength;
	XCCAM_DIBMODE m_DIBCount;
	bool m_bDIBMono_Flag;
	ULONG m_Parallel_Thread;
	BITMAPINFO* m_pBitMapInfo;
	BITMAPINFO* m_pRGBBitMapInfo;
	ULONG m_iWidth;
	ULONG m_iHeight;
	std::vector<Image_Buffer*> m_Queue_List;
	std::vector<Image_Buffer*> m_QueueFile_List;
	Gdiplus::ImageCodecInfo* m_pImageCodecInfo;
	UINT m_ImageCount;
	HAVIFILE m_AviFile;
	UINT64 m_CallCount;
	UINT64 m_DIBCallCount;

	CRITICAL_SECTION m_Queue_Section;


	bool GetEncoderClsid(const std::wstring& ImageType, CLSID& Clsid)
	{
		for(UINT idx = 0; idx < m_ImageCount; idx++)
		{
			if(ImageType == m_pImageCodecInfo[ idx ].MimeType)
			{
				Clsid = m_pImageCodecInfo[ idx ].Clsid;
				return true;
			}
		}
		return false;
	}


	bool SaveImageFile(const std::wstring& FName, const std::wstring& ImageType)
	{
		CLSID Clsid;
		Gdiplus::Status rtn;


		HANDLE hFile = ::CreateFileW(FName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			::CloseHandle(hFile);
			return false;
		}

		if(!GetEncoderClsid(ImageType, Clsid))
			return false;

		Gdiplus::Bitmap* pBMPImage;
		if(m_pBitMapInfo->bmiHeader.biBitCount == 8)
		{
			if(!MonoConv())
				return false;
			pBMPImage = new Gdiplus::Bitmap(m_pBitMapInfo, m_pMonoBuffer);
		}
		else
		{
			if(!ConvBMP())
				return false;
			pBMPImage = new Gdiplus::Bitmap(m_pBitMapInfo, m_pDIBBuffer);
		}

		rtn = pBMPImage->Save(FName.c_str(), &Clsid);

		delete pBMPImage;

		return rtn ? false : true;
	}


	bool ConvBMP(void)
	{
		if(m_iDIBWidth != m_iWidth || m_iDIBHeight != m_iHeight)
		{
			if(m_pDIBBuffer)
			{
				delete[] m_pDIBBuffer;
				m_pDIBBuffer = NULL;
			}
			if(m_pMonoBuffer)
			{
				delete[] m_pMonoBuffer;
				m_pMonoBuffer = NULL;
			}

			try
			{
				m_iDIBLength = m_pBitMapInfo->bmiHeader.biBitCount == 24 ?
					(m_iWidth * 3 + 3) / 4 * 4 * m_iHeight
					: m_iWidth * m_iHeight * 4;
				m_pDIBBuffer = new BYTE[ m_iDIBLength ];
				ZeroMemory(m_pDIBBuffer, m_iDIBLength);
			}
			catch(...)
			{
				m_pDIBBuffer = NULL;
				m_iDIBWidth = 0;
				m_iDIBHeight = 0;
				return false;
			}
			m_iDIBWidth = m_iWidth;
			m_iDIBHeight = m_iHeight;
		}

		if(m_CallCount != m_DIBCallCount)
		{
			try
			{
				::XCCAM_ConvExec(m_hCamera, m_pNewImage, (BYTE*)m_pDIBBuffer);
			}
			catch(...)
			{
			}
			m_DIBCallCount = m_CallCount;
		}
		return true;
	}


	bool MonoConv(void)
	{
		if(m_iDIBWidth != m_iWidth || m_iDIBHeight != m_iHeight)
		{
			if(m_pDIBBuffer)
			{
				delete[] m_pDIBBuffer;
				m_pDIBBuffer = NULL;
			}
			if(m_pMonoBuffer)
			{
				delete[] m_pMonoBuffer;
				m_pMonoBuffer = NULL;
			}

			try
			{
				m_iDIBLength = (m_iWidth + 3) / 4 * 4 * m_iHeight;
				m_pMonoBuffer = new BYTE[ m_iDIBLength ];
				ZeroMemory(m_pMonoBuffer, m_iDIBLength);
			}
			catch(...)
			{
				m_pMonoBuffer = NULL;
				m_iDIBWidth = 0;
				m_iDIBHeight = 0;
				return false;
			}
			m_iDIBWidth = m_iWidth;
			m_iDIBHeight = m_iHeight;
		}

		if(m_CallCount != m_DIBCallCount)
		{
			for(ULONG idx = 0; idx < m_iHeight; idx++)
				CopyMemory(&((char*)m_pMonoBuffer)[ (m_iWidth + 3) / 4 * 4 * (m_iHeight - idx - 1) ], &((char*)m_pNewImage->pBuffer)[ m_iWidth * idx ], m_iWidth);
			m_DIBCallCount = m_CallCount;
		}
		return true;
	}
};


#ifndef _XCCAM_CAMERALIST_DEF_
#define _XCCAM_CAMERALIST_DEF_
XCCAM_LIST* CSonyCam::m_pCameraList = NULL;
#else
extern XCCAM_LIST* CSonyCam::m_pCameraList;
#endif


static VOID CALLBACK ImageCB(HCAMERA hCamera, XCCAM_IMAGE* Image, XCCAM_IMAGEDATAINFO* Info, PVOID Context)
{
	CSonyCam* pCam = (CSonyCam*)Context;

	pCam->ImageProc(Image);
}
