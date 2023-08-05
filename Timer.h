#ifndef Timer_H
#define Timer_H

#include <mutex>
#include <condition_variable>
#include <map>
#include "TimeUtils.h"
#include "Thread.h"
#include <iostream>
#include <stdint.h>
#include <functional>
namespace ExpM{
	class TimeEvent
	{
		friend class Timer;
	public:
		TimeEvent() :m_eventId(0), m_interval(0), m_nextTime(0), m_delegate() {}
		TimeEvent(const int32_t eventId, const int32_t interval, Delegate del) :m_eventId(eventId),
			m_interval(interval), m_nextTime(0), m_delegate(del) {}

		TimeEvent(const int32_t eventId, Delegate del) :m_eventId(eventId),
			m_interval(0), m_nextTime(0), m_delegate(del)
		{}

		TimeEvent& operator =(const TimeEvent& tEvent)
		{
			this->m_eventId = tEvent.m_eventId;
			this->m_interval = tEvent.m_interval;
			this->m_nextTime = tEvent.m_nextTime;
			this->m_delegate = tEvent.m_delegate;
			return *this;
		}
	public:
		int32_t m_eventId;
		int32_t m_interval;
		int32_t m_nextTime;
		std::function<void()> m_delegate;
	};
	static const uint64_t waitTime = 1000;
	class Timer
	{
	public:
		Timer();
		virtual ~Timer() {
		};
		static Timer* Instance();
		bool Register(const int32_t eventId, const Delegate& delegate, const int32_t interval);
		bool UnRegister(const int32_t eventId);
		static int32_t GetTime();
		bool Start();
		void Stop();
		int32_t CheckTimeEvent();
		void Loop();
	private:
		static Timer* m_timer;/////////////////////
		bool m_isRunning;
		std::map<int32_t, TimeEvent> m_timeEvent;
		Thread m_thread;
		std::mutex m_mutex;
		std::condition_variable m_condition;
		
	};
}

#endif

