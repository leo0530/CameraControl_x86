#ifndef _CGLOBAL
#define _CGLOBAL

#include <afx.h>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

union FloatUnion
{
	float r;//单精度浮点数，32位
	unsigned long l;//无符号整形，32位
};

//两个32位整数拼成一个64位整数，a位低32位，b位高32位
#define MAKELONGLONG(a, b) ((unsigned __int64)(((DWORD)(a)) | ((unsigned __int64)((DWORD)(b))) << 32)) 
#define _IP_MARK "."

class CGlobal
{
	static __int64 atoi64_t(char *arrTmp)//字符串转64位整型
	{
		int len = 0;
		int i = 0;
		int j = 0;
		__int64 nTmpRes = 0;
		__int64 ntmp10 = 1;
		if (arrTmp == NULL)
		{
			return 0;
		}
		len = strlen(arrTmp);

		for (i = len - 1; i >= 0; i--)
		{
			ntmp10 = 1;
			for (j = 1; j<(len - i); j++)
			{
				ntmp10 = ntmp10 * 10;
			}
			nTmpRes = nTmpRes + (arrTmp[i] - 48)* ntmp10;
		}

		return nTmpRes;
	}


	static int itoa64_t(__int64 n, char *p, int len)////64位整型转字符串
	{
		char arrTmp[128];
		int i = 0;
		int j = 0;

		__int64 tmp;

		int numTmp = 0;
		if (p == NULL)
		{
			return 1;
		}

		for (i = 0;; i++)
		{
			numTmp = n % 10;
			tmp = n / 10;

			if (numTmp == 0 && tmp == 0)
			{
				break;
			}

			arrTmp[i] = numTmp + 48;
			n = tmp;
		}
		arrTmp[i] = 0;
		if (len < strlen(arrTmp))
		{
			return 1;
		}
		else
		{
			for (i = strlen(arrTmp) - 1, j = 0; i >= 0; i--, j++)
			{
				p[j] = arrTmp[i];
			}
		}
		return 0;

	}

	static CString DatatoHexString(BYTE* pBuf, ULONG Length)//char*转换成16进制CString
	{
		CString HexString;
		CString Str;


		for (ULONG idx = 0; idx < Length; idx++)
		{
			if (isgraph(pBuf[idx]) && pBuf[idx] != 0x5c)
				Str.Format(_T("%C"), pBuf[idx]);
			else
				Str.Format(_T("\\%02X"), pBuf[idx]);
			HexString += Str;
		}
		return HexString;
	}


	static void HexStringToData(BYTE* pBuf, CString& HexString)//16进制CString转换成char*
	{
		ULONG idx1 = 0;

		for (int idx = 0; idx < HexString.GetLength(); idx++, idx1++)
		{
			if (HexString[idx] != 0x5c)
				pBuf[idx1] = (BYTE)HexString[idx];
			else
			{
				CString Str;
				TCHAR* pEnd;

				idx++;
				Str += HexString[idx];
				idx++;
				Str += HexString[idx];
				pBuf[idx1] = (BYTE)_tcstoul(Str, &pEnd, 16);
			}
		}
	}

	static void Delay(int ms)//精确到毫秒的延时
	{
		LARGE_INTEGER litmp;
		LONGLONG QPart1, QPart2;
		double dfMinus, dfFreq, dfTim;
		QueryPerformanceFrequency(&litmp);
		dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
		QueryPerformanceCounter(&litmp);
		QPart1 = litmp.QuadPart;// 获得初始值
		do
		{
			QueryPerformanceCounter(&litmp);
			QPart2 = litmp.QuadPart;//获得中止值
			dfMinus = (double)(QPart2 - QPart1);
			dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒
		} while (dfTim<0.001*ms);
	}

	//string转CString
	static CString StringToCString(string str) {
#ifdef _UNICODE
		//如果是unicode工程
		USES_CONVERSION; CString s(str.c_str());
		CString ans(str.c_str());
		return ans;
#else
		//如果是多字节工程 
		CString ans;
		ans.Format("%s", str.c_str());
		return ans;
#endif // _UNICODE  
	}

	//4个byte拼成32位int
	static int ConvertTo32(int hh, int hl, int lh, int ll)
	{
		hh = 0XFFFFFF | (hh << 24);
		hl = 0XFF00FFFF | (hl << 16);
		lh = 0XFFFF00FF | (lh << 8);
		ll = 0XFFFFFF00 | ll;
		return hh&hl&lh&ll;
	}

	//32位整形转换成IP
	static string IntToIP(unsigned long num)
	{

		string strRet = "";
		for (int i = 0; i < 4; i++)
		{
			unsigned long tmp = (num >> ((3 - i) * 8)) & 0xFF;

			char chBuf[8] = "";
			_itoa_s(tmp, chBuf, 10);
			strRet += chBuf;

			if (i < 3)
			{
				strRet += _IP_MARK;
			}
		}

		return strRet;
	}

	//	CString转string
	static string CStringToString(CString str)
	{
		std::string ss(CW2A(str.GetString()));
		return ss;
	}

	//浮点数转32位整形数
	static unsigned long FloatToInt(float fData)
	{
		FloatUnion x;
		x.r = fData;

		return x.l;
	}

	//32位整形数转浮点数
	static float IntToFloat(unsigned long l)
	{
		FloatUnion x;
		x.l = l;

		return x.r;
	}

	// 获取应用程序当前路径
	static CString GetAppPath(void)
	{
		TCHAR szFilePath[MAX_PATH + 1] = { 0 };
		GetModuleFileName(NULL, szFilePath, MAX_PATH);
		(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
		CString str_url = szFilePath;  // 例如str_url==e:\program\Debug\

		return str_url;//CString();
	}
};
#endif // _CGLOBAL