// XCCamRegAPI.h
//
#pragma once


#ifdef __cplusplus
extern "C" {
#endif


//API------------------------------------------------------------------------------------------------------------
/*	C API Interface Functions	*/
BOOL	Dllport XCCAM_ReadReg(HCAMERA hCamera, UINT64 Addr, DWORD* Value);
BOOL	Dllport XCCAM_ReadMem(HCAMERA hCamera, UINT64 Addr, PVOID pBuffer, DWORD* Length);
BOOL	Dllport XCCAM_WriteReg(HCAMERA hCamera, UINT64 Addr, DWORD Value);
BOOL	Dllport XCCAM_WriteMem(HCAMERA hCamera, UINT64 Addr, PVOID pBuffer, DWORD* Length);
BOOL	Dllport XCCAM_WriteRegAll(DWORD Addr, DWORD Value);


BOOL	Dllport XCCAM_OpenPort(HCAMERA* hCamera);
BOOL	Dllport XCCAM_ClosePort(HCAMERA hCamera);
VOID	Dllport XCCAM_ClosePortAll(VOID);
BOOL	Dllport XCCAM_PortInfo(HCAMERA hCamera, XCCAM_DEVINFO* CInfo);
BOOL	Dllport XCCAM_PortReadReg(HCAMERA hCamera, UINT64 Addr, DWORD* Value);
BOOL	Dllport XCCAM_PortReadMem(HCAMERA hCamera, UINT64 Addr, PVOID pBuffer, DWORD* Length);
BOOL	Dllport XCCAM_PortWriteReg(HCAMERA hCamera, UINT64 Addr, DWORD Value);
BOOL	Dllport XCCAM_PortWriteMem(HCAMERA hCamera, UINT64 Addr, PVOID pBuffer, DWORD* Length);


#ifdef __cplusplus
}
#endif
