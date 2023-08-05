#include "TimeUtils.h"

#ifdef _WIN32
#include <Windows.h>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib ")
#else
#include <time.h>
#endif

namespace ExpM{
	TimeUtils::TimeUtils() {}
	TimeUtils::~TimeUtils() {}

	std::string TimeUtils::GetNowTime()
	{
#ifdef _WIN32
		char stime[7];
		SYSTEMTIME local_Time;
		GetLocalTime(&local_Time);
		sprintf_s(stime, sizeof(stime), "%2d%2d%2d", local_Time.wHour, local_Time.wMinute, local_Time.wSecond);
		std::string strTime(stime);
		return strTime;
		//printf("开始时间: %d年%d月%d日  %d:%d:%d.%d\n",
		//	local_Time.wYear,
		//	local_Time.wMonth,
		//	local_Time.wDay,
		//	local_Time.wHour, //北京东八区时间
		//	local_Time.wMinute,
		//	local_Time.wSecond,
		//	local_Time.wMilliseconds);
#else
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);

		struct tm* tm_info = localtime(&ts.tv_sec);

		char buffer[30];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
		return std::string(buffer);
		//printf("Current date and time: %s.%03ld\n", buffer, ts.tv_nsec / 1000000);


#endif
		
	}
	int32_t TimeUtils::GetTime()
	{
		return static_cast<int32_t>(timeGetTime());
	}
}