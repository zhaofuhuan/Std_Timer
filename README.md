# Std_Timer
一种基于Std thread, mutex, condition_varibale,function 实现的定时器  
# 出发点
项目当中，不可避免的需要使用一些回调事件, 我们希望这些事件间隔一段时间执行一次，同时，在不需要这些事件执行的时候，可以注销掉;
基于上述的需要，这里提供了一个支持事件间隔执行的定时器，间隔的时间可以自定义,可以随时注册事件, 以及注销事件；
# 使用方法
Timer类为定时器类；
注册事件的函数：Timer::Register(const int32_t eventId, const Delegate& delegate, const int32_t interval)

param1(eventId):事件的id;

param2(delegate):事件的委托;  委托即为：typedef std::function<void()> Delegate

param3(interval)：事件的执行的间隔时间；

注销事件的函数：UnRegister(const int32_t eventId);

param(eventId):事件的id;

开启定时器函数:Timer::Start()

关闭定时器函数:Timer::Stop()
# 注意
在使用该定时器类的时候，需要保证主线程不会挂掉，定时器本身的线程为主线程的子线程，主线程挂掉，子线程随之挂掉；


