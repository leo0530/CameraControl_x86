// XCCamAVIFileAPI.h
//
#pragma once


#ifdef __cplusplus
extern "C" {
#endif


#define	HAVIFILE			PVOID


BOOL	Dllport XCCAM_AVIFileOpen(WCHAR* pFileName, DWORD Rate, HAVIFILE* hAviFIle);
BOOL	Dllport XCCAM_AVIFileSetInfo(HAVIFILE hAviFIle, DWORD Width, DWORD Height, DWORD DiBitCount);
BOOL	Dllport XCCAM_AVIFileWrite(HAVIFILE hAviFIle, VOID* pBuffer, DWORD Length);
VOID	Dllport XCCAM_AVIFileClose(HAVIFILE hAviFIle);


#ifdef __cplusplus
}
#endif
