    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Function.h                  //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <functional>

namespace snow
{

template<typename T_Ret, typename... T_Args>
class Function : public Object
{
public:
	Function() noexcept;
	Function(const Function<T_Ret, T_Args...>& function);
	Function(Function<T_Ret, T_Args...>&& function) noexcept;
	Function(const std::function<T_Ret(T_Args...)>& function);
	Function(std::function<T_Ret(T_Args...)>&& function) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	void swap(Function<T_Ret, T_Args...>& function) noexcept;

	Function<T_Ret, T_Args...>& operator=(const Function<T_Ret, T_Args...>& function);
	Function<T_Ret, T_Args...>& operator=(Function<T_Ret, T_Args...>&& function);
	Function<T_Ret, T_Args...>& operator=(const std::function<T_Ret(T_Args...)>& function);
	Function<T_Ret, T_Args...>& operator=(std::function<T_Ret(T_Args...)>&& function);
	operator bool() const noexcept;
	T_Ret operator()(T_Args... args) const;

private:
	std::function<T_Ret(T_Args...)> func_;

};


template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>::Function() noexcept :
	func_()
{}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>::Function(const Function<T_Ret, T_Args...>& function) :
	func_(function.func_)
{}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>::Function(Function<T_Ret, T_Args...>&& function) noexcept :
	func_(std::move(function.func_))
{}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>::Function(const std::function<T_Ret(T_Args...)>& function) :
	func_(function)
{}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>::Function(std::function<T_Ret(T_Args...)>&& function) noexcept :
	func_(std::move(function))
{}

template<typename T_Ret, typename... T_Args>
String Function<T_Ret, T_Args...>::to_string() const noexcept
{
	return L"The function (arguments: "_s + util::to_string(static_cast<int>(sizeof...(T_Args))) + L")";
}

template<typename T_Ret, typename... T_Args>
int Function<T_Ret, T_Args...>::hash_code() const noexcept
{
	return reinterpret_cast<int>(func_.target<T_Ret(T_Args...)>());
}

template<typename T_Ret, typename... T_Args>
void Function<T_Ret, T_Args...>::swap(Function<T_Ret, T_Args...>& function) noexcept
{
	func_.swap(function.func_);
}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>& Function<T_Ret, T_Args...>::operator=(const Function<T_Ret, T_Args...>& function)
{
	func_ = function.func_;
}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>& Function<T_Ret, T_Args...>::operator=(Function<T_Ret, T_Args...>&& function)
{
	func_ = std::move(function.func_);
}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>& Function<T_Ret, T_Args...>::operator=(const std::function<T_Ret(T_Args...)>& function)
{
	func_ = function;
}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>& Function<T_Ret, T_Args...>::operator=(std::function<T_Ret(T_Args...)>&& function)
{
	func_ = std::move(function);
}

template<typename T_Ret, typename... T_Args>
Function<T_Ret, T_Args...>::operator bool() const noexcept
{
	return static_cast<bool>(func_);
}

template<typename T_Ret, typename... T_Args>
T_Ret Function<T_Ret, T_Args...>::operator()(T_Args... args) const
{
	return func_(args...);
}

}
