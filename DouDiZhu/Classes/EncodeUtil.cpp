#include <cstdlib>
#include <string>

//#include "cocos2d/Libraries/libiconv/include/iconv.h"
#include "iconv.h"
#include "EncodeUtil.h"
#include "MacroUtil.h"

#ifdef WIN32
#pragma comment(lib, "libiconv.lib")
#endif

namespace util
{
	const char* GBToUTF8(const char* str)
	{
		if (IsUTF8(str, strlen(str)))
		{
			return str;
		}
		const char* strUtf = "";
		if (strlen(str) == 0)
		{
			return strUtf;
		}
		iconv_t iconvH;
		iconvH = iconv_open("utf-8", "gbk");
		if (iconvH == 0)
		{
			return strUtf;
		}
		/*const */char* strChar = (char*)str;
		/*const */char** pin = &strChar;
		size_t strLength = strlen(strChar);
		char* outbuf = (char*)malloc(strLength * 4);
		char* pBuff = outbuf;
		memset(outbuf, 0, strLength * 4);
		size_t outLength = strLength * 4;
		if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
		{
			strUtf = str_format("%s", pBuff);
			iconv_close(iconvH);
			return strUtf;
		}
		strUtf = pBuff;
		iconv_close(iconvH);
		return strUtf;
	}

	bool IsUTF8(const void* pBuffer_, long lstrSize_)
	{
		bool bIsUTF8 = true;
		unsigned char* start = (unsigned char*)pBuffer_;
		unsigned char* end = (unsigned char*)pBuffer_ + lstrSize_;
		while (start < end)
		{
			// (10000000): 值小于0x80的为ASCII字符 
			if (*start < 0x80)
			{
				start++;
			}
			// (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符  
			else if (*start < (0xC0))
			{
				bIsUTF8 = false;
				break;
			}
			// (11100000): 此范围内为2字节UTF-8字符
			else if (*start < (0xE0))
			{
				if (start >= end - 1)
					break;
				if ((start[1] & (0xC0)) != 0x80)
				{
					bIsUTF8 = false;
					break;
				}
				start += 2;
			}
			// (11110000): 此范围内为3字节UTF-8字符
			else if (*start < (0xF0))
			{
				if (start >= end - 2)
					break;
				if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
				{
					bIsUTF8 = false;
					break;
				}
				start += 3;
			}
			else
			{
				bIsUTF8 = false;
				break;
			}
		}
		return bIsUTF8;
	}

	const char *strongGBToUTF8(const char* str_) 
	{
		const char* strUtf = "";
		if (strlen(str_) == 0)
		{
			return strUtf;
		}
		iconv_t iconvH;
		iconvH = iconv_open("utf-8", "gbk");
		if (iconvH == 0)
		{
			return strUtf;
		}
		/*const */char* strChar = (char*)str_;
		/*const */char** pin = &strChar;
		size_t strLength = strlen(strChar);
		char* outbuf = (char*)malloc(strLength * 4);
		char* pBuff = outbuf;
		memset(outbuf, 0, strLength * 4);
		size_t outLength = strLength * 4;
		if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
		{
			strUtf = str_format("%s", pBuff);
			iconv_close(iconvH);
			return strUtf;
		}
		strUtf = pBuff;
		iconv_close(iconvH);
		return strUtf;
	}
}