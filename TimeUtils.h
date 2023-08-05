#ifndef TimeUtils_H
#define TimeUtils_H
#include <string>
//#include <epms/Common/TypeDefine.h>
namespace ExpM{
	class  TimeUtils
	{
	public:
		static std::string GetNowTime();
		static int32_t GetTime();
	private:
		TimeUtils();
		~TimeUtils();
	};
}
#endif

