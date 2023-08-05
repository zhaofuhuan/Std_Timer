#include "Thread.h"
namespace ExpM
{
	Thread::Thread():m_thread(nullptr), m_isJoinable(false)
	{
	}
	bool Thread::Join()
	{
		bool ret = true;
		if (m_thread != nullptr)
		{
			/*if (WaitForSingleObject(reinterpret_cast<HANDLE>(m_tHandle), INFINITE) != WAIT_OBJECT_0)
			{
				ret = false;
			}
			CloseHandle(reinterpret_cast<HANDLE>(m_tHandle));*/
			m_thread->join();
			//delete m_thread;
			m_thread = nullptr;
			//std::cout << "delete thread"<<std::endl;
		}
		else
		{
			ret = false;
		}
		m_isJoinable = false;
		return ret;
	}
	Thread::~Thread()
	{
		Join();
	}
	
	bool Thread::Start()
	{
		bool ret = true;
		
		if (m_thread != nullptr)
		{
			ret = false;
		}
		else
		{
			//m_thread = std::move(std::make_unique<std::thread>(new std::thread(std::bind(&Thread::Run, this))));
			m_thread = std::make_unique<std::thread>(std::bind(&Thread::Run, this));
			/*if (m_thread->joinable() == false)
			{
				ret = false;
			}*/
			if (m_thread != nullptr)
			{
				if (m_thread->joinable() == false)
				{
					ret = false;
				}
			}
		}
		m_isJoinable = ret;
		return ret;
	}


	void Thread::Run()
	{
		if (m_tDelegate)
		{
			m_tDelegate();
		}
	}
	bool Thread::IsJoinable() const
	{
		return m_isJoinable;
	}

	/*void Thread::SetDelegate(const Delegate& d)
	{
		m_tDelegate = d;
	}*/
	void Thread::SetDelegate(const Delegate& d)
	{
		m_tDelegate = d;
	}
}
