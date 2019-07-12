/////////////////////////////////////////////////////////////////////////
///@file utility.cpp
///@brief	工具函数
///@copyright	上海信易信息科技股份有限公司 版权所有
/////////////////////////////////////////////////////////////////////////


#include "utility.h"

#include <string>
#include <chrono>
#include <cstring>
#include <ctime>
#include <stdio.h>

std::string GenerateUniqFileName()
{	
	static char base[] = "/tmp/myfileXXXXXX";
	char fname[1024];
	strcpy(fname, base);
	mkstemp(fname);
	return fname;
}

long long GetLocalEpochNano()
{
    auto now = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    return ns.count();
}

long long GetLocalEpochMilli()
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds mi = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	return mi.count();
}

std::string GuessTradingDay()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* t = std::localtime(&now);
	if (t->tm_hour >= 16)
	{
		//Friday, Saturday, Sunday
		if (t->tm_wday == 5)
		{
			now += 3600 * 24 * 3;
		}
		else if (t->tm_wday == 6)
		{
			now += 3600 * 24 * 2;
		}
		else
		{
			now += 3600 * 24 * 1;
		}
	}
	else
	{
		if (t->tm_wday == 6)
		{
			now += 3600 * 24 * 2;
		}
		else if (t->tm_wday == 0)
		{
			now += 3600 * 24 * 1;
		}
	}
	t = std::localtime(&now);
	char buf[16];
	snprintf(buf, 16, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	return std::string(buf);
}

void SplitString(const std::string& str
	, std::vector<std::string>& vecs, int len)
{
	std::string strLeave = str;
	int i = 0;
	vecs.clear();
	while (strLeave.length() > len)
	{
		std::string strMsg = strLeave.substr(i*len,len);
		vecs.push_back(strMsg);
		strLeave = strLeave.substr((i + 1)*len);
	}
	if (strLeave.length() > 0)
	{
		vecs.push_back(strLeave);
	}
}

void CutDigital(std::string& instId)
{
	//TODO::
}