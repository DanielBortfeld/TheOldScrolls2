// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

template<class T>
class Singleton
{
private:

	static std::shared_ptr<T> instance;

public:

	static std::shared_ptr<T> GetInstance();

	Singleton() = default;
	virtual ~Singleton() = default;
};

template<class T>
std::shared_ptr<T> Singleton<T>::instance;

template<class T>
inline std::shared_ptr<T> Singleton<T>::GetInstance()
{
	if (instance.get() == nullptr)
	{
		instance = std::make_shared<T>();
	}
	return instance;
}

#endif // !SINGLETON_H
