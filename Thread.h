#ifndef Thread_H
#define Thread_H

#include <thread>
#include <string>
#include <functional>
#include <iostream>
namespace ExpM{
	//class Delegate
	//{
	//public:
	//	/**
	//	* @brief 构造函数
	//	*/
	//	Delegate() :m_obj(NULL), m_stub(NULL) {}
	//	/**
	//	* @brief 赋值构造
	//	*/
	//	Delegate& operator = (const Delegate& d)
	//	{
	//		this->m_obj = d.m_obj;
	//		this->m_stub = d.m_stub;
	//		return *this;
	//	}
	//	/**
	//	* @brief 构造函数
	//	*/
	//	~Delegate() {}

	//	template <class T, void(T::*TMethod)()>

	//	/**
	//	* @brief 创建一个线程回调对象
	//	* @param [in] obj 回调对象指针
	//	*/
	//	static Delegate CreateDelegate(T* obj)
	//	{
	//		Delegate d;
	//		d.m_obj = obj;
	//		d.m_stub = &MethodStub<T, TMethod>;
	//		return d;
	//	}
	//	bool IsNull()
	//	{
	//		bool ret = true;
	//		if (m_obj != NULL || m_stub != NULL)
	//		{
	//			ret = false;
	//		}
	//		return ret;
	//	}
	//	void operator ()()
	//	{
	//		return (*m_stub)(m_obj);
	//	}
	//private:
	//	typedef void (*StubType)(void* obj);
	//	/**
	//	* @brief 回调对象
	//	*/
	//	void* m_obj;
	//	/**
	//	* @brief 回调函数
	//	*/
	//	StubType m_stub;

	//	template <class T, void(T::* TMethod)()>
	//	/**
	//	* @brief 执行回调函数
	//	*/
	//	static void MethodStub(void* obj)
	//	{
	//		T* p = static_cast<T*>(obj);
	//		return (p->*TMethod)();
	//	}
	//};
	typedef std::function<void()> Delegate;

	class Thread
	{
	public:
		typedef uint64_t Handle;
		/**
		* @brief 构造函数
		*/
		Thread();
		/**
		* @brief 构造函数
		*/
		virtual ~Thread();
		/**
		* @brief 开启线程
		* @ret true成功
		* @ret false失败
		*/
		bool Start();
		/**
		* @brief 线程joinable
		* @ret true 可joinable
		* @ret false 不可joinable
		*/
		bool IsJoinable() const;
		/**
		* @brief 运行线程
		*/
		virtual void Run();
		/**
		* @brief 设置线程回调对象
		* @paraam [in] 线程回调对象
		*/
		//void SetDelegate(const Delegate& d);
		void SetDelegate(const Delegate& d);
		/**
		* @brief 线程jion
		* @ret true jion成功
		* @ret false jion失败
		*/
		bool Join();
		/**
		* @brief 线程Terminate  存在风险 谨慎使用详见MSDN
		* @ret true Terminate成功
		* @ret false Terminate失败
		*/
		//void Terminate() const;

	private:
		/**
		* @brief 线程
		*/
		//Handle m_tHandle;
		std::unique_ptr<std::thread> m_thread;
		/**
		* @brief 线程回调对象
		*/
		Delegate m_tDelegate;
		/**
		* @brief 线程是否joinable
		*/
		bool m_isJoinable;
	};

}

#endif 

