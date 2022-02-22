    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Event.h                     //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "Function.h"
#include "../Container/LinkedList.h"

namespace snow
{

template<typename... T_Args>
class Event : public Object
{
public:
	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	bool bind(const Function<void, T_Args...>& function);
	bool bind(Function<void, T_Args...>&& function);
	bool bind(const std::function<void(T_Args...)>& function);
	bool bind(std::function<void(T_Args...)>&& function);
	void unbind_all();
	int functions_number() const;
	void execute(T_Args... args);

private:
	LinkedList<std::shared_ptr<Function<void, T_Args...>>> funcs_;
};


template<typename... T_Args>
String Event<T_Args...>::to_string() const noexcept
{
	return L"The event (bound functions: "_s + util::to_string(functions_number()) + L")";
}

template<typename... T_Args>
int Event<T_Args...>::hash_code() const noexcept
{
	return funcs_.hash_code();
}

template<typename... T_Args>
bool Event<T_Args...>::bind(const Function<void, T_Args...>& func)
{
	return funcs_.add(std::make_shared<Function<void, T_Args...>>(func));
}

template<typename... T_Args>
bool Event<T_Args...>::bind(Function<void, T_Args...>&& func)
{
	return funcs_.add(std::make_shared<Function<void, T_Args...>>(std::forward(func)));
}

template<typename... T_Args>
bool Event<T_Args...>::bind(const std::function<void(T_Args...)>& func)
{
	return funcs_.add(std::make_shared<Function<void, T_Args...>>(func));
}

template<typename... T_Args>
bool Event<T_Args...>::bind(std::function<void(T_Args...)>&& func)
{
	return funcs_.add(std::make_shared<Function<void, T_Args...>>(std::forward<std::function<void(T_Args...)>>(func)));
}

template<typename... T_Args>
void Event<T_Args...>::unbind_all()
{
	funcs_.clear();
}

template<typename... T_Args>
int Event<T_Args...>::functions_number() const
{
	return funcs_.size();
}

template<typename... T_Args>
void Event<T_Args...>::execute(T_Args... args)
{
	for (auto& i : funcs_)
	{
		(*i)(args...);
	}
}
}
