
#include "Timer.h"
#include <vector>
namespace ExpM{
	Timer* Timer::m_timer = nullptr;
	Timer::Timer() :m_isRunning(false) {}
	Timer* Timer::Instance()
	{
		if (m_timer == nullptr)
		{
			m_timer = new Timer();
		}
		return m_timer;
	}
	bool Timer::Register(const int32_t eventId, const Delegate& delegate, const int32_t interval)
	{
		bool ret = true;
		m_mutex.lock();
		TimeEvent event(eventId, interval, delegate);
		event.m_nextTime = interval + GetTime();
		if (m_timeEvent.find(eventId) == m_timeEvent.end())
		{
			m_timeEvent[eventId] = event;
			m_condition.notify_one();
		}
		else
		{
			ret = false;
		}
		m_mutex.unlock();
		return ret;
	}
	bool Timer::UnRegister(const int32_t eventId)
	{
		bool ret = true;
		m_mutex.lock();
		auto event = m_timeEvent.find(eventId);
		if (event != m_timeEvent.end())
		{
			m_timeEvent.erase(event);
		}
		else
		{
			ret = false;
		}
		m_mutex.unlock();
		return ret;
	}
	int32_t Timer::GetTime()
	{
		return TimeUtils::GetTime();
	}
	bool Timer::Start()
	{
		bool ret = true;
		m_mutex.lock();
		if (m_isRunning)
		{
			ret = false;
		}
		else
		{
			m_isRunning = true;
			Delegate loop = std::bind(&Timer::Loop, this);
			m_thread.SetDelegate(loop);
			ret = m_thread.Start();
		}
		m_mutex.unlock();
		return ret;
	}
	/*void Timer::Run()
	{
		while (m_isRunning)
		{
		}
	}*/
	void Timer::Stop()
	{
		//mutex.lock();
		m_isRunning = false;
		m_condition.notify_all();
		if (m_thread.IsJoinable() == true)
		{
			m_thread.Join();
		}
	}
	int32_t Timer::CheckTimeEvent()
	{
		std::vector<Delegate> vecDelegate;
		int32_t wtime = waitTime;

		m_mutex.lock();//后追加  用于server的main函数中在 start函数之后 重新register()函数；

		for (auto& event : m_timeEvent)
		{
			int32_t nowtime = GetTime();
			if (event.second.m_nextTime - nowtime <= 0)
			{
				event.second.m_nextTime += event.second.m_interval;
				vecDelegate.push_back(event.second.m_delegate);
			}
		
			int32_t wt = event.second.m_nextTime - nowtime;
			if (wt < wtime)
			{
				wtime = wt;
			}
			
		}

		m_mutex.unlock();

		for (auto& del : vecDelegate)
		{
			del();
		}
		return wtime;
	}
	void Timer::Loop()
	{
		while (m_isRunning)
		{
			int32_t wt = CheckTimeEvent();
			if (wt > 0)
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_condition.wait_for(lock, std::chrono::milliseconds(wt));
			}
		}
		//return;
	}
}