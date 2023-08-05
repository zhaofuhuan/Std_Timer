// event_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Timer.h"
//#include "epms/Common/CmdHandler.h"
//#include "epms/Common/MachineState.h"
using namespace ExpM;
class Test
{
public:
    static Test& Instance()
    {
        static Test test;
        return test;
    }
public:
    void CycleRun()
    {
        std::cout << "test" << std::endl;
    }
    void CycleRunRegister()
    {
        std::cout << "test register" << std::endl;
    }
};
int main()
{
    std::function<void()>  test1 = std::bind(&Test::CycleRun, &Test::Instance());
    ExpM::Timer::Instance()->Register(100, test1, 1000);
    ExpM::Timer::Instance()->Start();
    //ExpM::Timer::Instance()->Run();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::function<void()>  test2 = std::bind(&Test::CycleRunRegister, &Test::Instance());
    ExpM::Timer::Instance()->Register(110, test2, 1000);
    std::this_thread::sleep_for(std::chrono::seconds(30));

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
