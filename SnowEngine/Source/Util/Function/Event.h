	////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Delegate.h                  //
////////////////////////////////////////

#pragma once

#include "Delegate.h"

#include "../Container/Map.h"

namespace snow
{

template<typename... T_Args>
class Event : public Object
{
public:
	Event();
	Event(const Event<T_Args...>& event);
	Event(Event<T_Args...>&& event);

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	int count() const;

	int bind(const std::function<void(T_Args...)>& func);

	template<typename T_Class>
	int bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func);

	void unbind(int key);

	void execute(T_Args... args) const;

	void operator()(T_Args... args) const;

private:
	Map<int, std::unique_ptr<Delegate<void, T_Args...>>> functions_;
	int counter_;
};


template<typename... T_Args>
Event<T_Args...>::Event() :
	functions_(),
	counter_(0)
{}

template<typename... T_Args>
Event<T_Args...>::Event(const Event<T_Args...>& event) :
	functions_(event.functions_),
	counter_(event.counter_)
{}

template<typename... T_Args>
Event<T_Args...>::Event(Event<T_Args...>&& event) :
	functions_(std::move(event.functions_)),
	counter_(event.counter_)
{}

template<typename... T_Args>
String Event<T_Args...>::to_string() const noexcept
{
	return L"Event, bound functions: "_s + util::to_string(count());
}

template<typename... T_Args>
int Event<T_Args...>::hash_code() const noexcept
{
	return functions_.hash_code();
}

template<typename... T_Args>
int Event<T_Args...>::count() const
{
	return functions_.size();
}

template<typename... T_Args>
int Event<T_Args...>::bind(const std::function<void(T_Args...)>& func)
{
	std::unique_ptr<Delegate<void, T_Args...>> delegate = std::make_unique<Delegate<void, T_Args...>>();
	delegate->bind(func);
	functions_.add(counter_, std::move(delegate));
	return counter_++;
}

template<typename... T_Args>
template<typename T_Class>
int Event<T_Args...>::bind(T_Class& object, const std::function<void(T_Class&, T_Args...)>& func)
{
	std::unique_ptr<Delegate<void, T_Args...>> delegate = std::make_unique<Delegate<void, T_Args...>>();
	delegate->bind<T_Class>(object, func);
	functions_.add(counter_, std::move(delegate));
	return counter_++;
}

template<typename... T_Args>
void Event<T_Args...>::unbind(int key)
{
	functions_.remove(key);
}

template<typename... T_Args>
void Event<T_Args...>::execute(T_Args... args) const
{
	for (auto& i : functions_)
	{
		i->execute(args...);
	}
}

template<typename... T_Args>
void Event<T_Args...>::operator()(T_Args... args) const
{
	execute(args...);
}

}
