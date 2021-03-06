#pragma once
#include <iostream>
#include <atomic>
/*
单例模式是一种常见的软件设计模式。它的核心结构只包含一个被称为单例的特殊类。它的目的是保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。

todo:
	测试线程安全
*/

#if 1
class Singleton {
	// 1. 饿汉模式，线程安全的
private:
	Singleton() {}
	
public:
	static Singleton* GetInstance()
	{
		static Singleton m_instance;
		return &m_instance;
	}

	void doSomething()
	{
		std::cout << "Singleton doSomething." << std::endl;
		return;
	}
};
#endif

#if 1
class Singleton {
// 2. 懒汉模式
private:
	Singleton() {}
	static Singleton* m_instance;

public:
	static Singleton* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new Singleton();
		}
		return m_instance;
	}

	void doSomething()
	{
		std::cout << "Singleton doSomething." << std::endl;
		return;
	}
};
Singleton* Singleton::m_instance = nullptr;
#endif

#if 1
class Singleton {
	// 3. 改进的懒汉模式-线程安全版
private:
	Singleton() {}
	static Singleton* m_instance;

public:
	static Singleton* GetInstance()
	{
		if (m_instance == nullptr) {
			// pthread_mutex_lock(&mutex);
			if (m_instance == nullptr) {
				m_instance = new Singleton();
				static GC gc;
			}
			// pthread_mutex_unlock(&mutex);
		}
		return m_instance;
	}

	class GC {
	public:
		~GC()
		{
			if (Singleton::m_instance) {
				delete Singleton::m_instance;
				Singleton::m_instance = nullptr;
			}
		}
	};

	void doSomething()
	{
		std::cout << "Singleton doSomething." << std::endl;
		return;
	}
};
Singleton* Singleton::m_instance = nullptr;
#endif

void singletonTest()
{
	Singleton::GetInstance()->doSomething();

	return;
}
