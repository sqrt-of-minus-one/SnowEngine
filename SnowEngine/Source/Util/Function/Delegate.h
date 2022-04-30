    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Delegate.h                  //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Types/String.h"

#include <functional>

namespace snow
{

namespace
{

template<typename T_Ret, typename... T_Args>
struct IFunctionContainer_
{
public:
	virtual bool is_valid() const = 0;
	virtual T_Ret execute(T_Args... args) = 0;
	virtual std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> copy() const = 0;
	virtual int hash() const = 0;
};

template<typename T_Ret, typename... T_Args>
struct FunctionContainer_ : public IFunctionContainer_<T_Ret, T_Args...>
{
public:
	FunctionContainer_(const std::function<T_Ret(T_Args...)> func);

	std::function<T_Ret(T_Args...)> function;

	virtual bool is_valid() const override;
	virtual T_Ret execute(T_Args... args) override;
	virtual std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> copy() const override;
	virtual int hash() const override;
};

template<typename T_Class, typename T_Ret, typename... T_Args>
struct MethodContainer_ : public IFunctionContainer_<T_Ret, T_Args...>
{
public:
	MethodContainer_(T_Class* object, const std::function<T_Ret(T_Class&, T_Args...)> func);

	T_Class* object;
	std::function<T_Ret(T_Class&, T_Args...)> function;

	virtual bool is_valid() const override;
	virtual T_Ret execute(T_Args... args) override;
	virtual std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> copy() const override;
	virtual int hash() const override;
};

}

template<typename T_Ret, typename... T_Args>
class Delegate : public Object
{
public:
	Delegate();
	Delegate(const Delegate<T_Ret, T_Args...>& delegate);

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	bool is_valid() const noexcept;

	void bind(const std::function<T_Ret(T_Args...)>& func);

	template<typename T_Class>
	void bind(T_Class& object, const std::function<T_Ret(T_Class&, T_Args...)>& func);

	void unbind();

	T_Ret execute(T_Args... args);

	T_Ret operator()(T_Args... args);
	operator bool() const noexcept;

private:
	std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> func_;
	bool is_method_;
};


template<typename T_Ret, typename... T_Args>
FunctionContainer_<T_Ret, T_Args...>::FunctionContainer_(const std::function<T_Ret(T_Args...)> func) :
	function(func)
{}

template<typename T_Ret, typename... T_Args>
bool FunctionContainer_<T_Ret, T_Args...>::is_valid() const
{
	return static_cast<bool>(function);
}

template<typename T_Ret, typename... T_Args>
T_Ret FunctionContainer_<T_Ret, T_Args...>::execute(T_Args ...args)
{
	if (is_valid())
	{
		return function(args...);
	}
	else if (!std::is_same<T_Ret, void>::value) // No exception if return type is void
	{
		throw std::logic_error("Attempt to call an empty delegate");
	}
}

template<typename T_Ret, typename... T_Args>
std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> FunctionContainer_<T_Ret, T_Args...>::copy() const
{
	return std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>>(new FunctionContainer_<T_Ret, T_Args...>(function));
}

template<typename T_Ret, typename... T_Args>
int FunctionContainer_<T_Ret, T_Args...>::hash() const
{
	return reinterpret_cast<int>(&function);
}

template<typename T_Class, typename T_Ret, typename... T_Args>
MethodContainer_<T_Class, T_Ret, T_Args...>::MethodContainer_(T_Class* object, const std::function<T_Ret(T_Class&, T_Args...)> func) :
	object(object),
	function(func)
{}

template<typename T_Class, typename T_Ret, typename... T_Args>
bool MethodContainer_<T_Class, T_Ret, T_Args...>::is_valid() const
{
	return static_cast<bool>(function) && Object::is_valid(object);
}

template<typename T_Class, typename T_Ret, typename... T_Args>
T_Ret MethodContainer_<T_Class, T_Ret, T_Args...>::execute(T_Args ...args)
{
	if (is_valid())
	{
		return function(*object, args...);
	}
	else if (!std::is_same<T_Ret, void>::value) // No exception if return type is void
	{
		throw std::logic_error("Attempt to call an empty delegate");
	}
}

template<typename T_Class, typename T_Ret, typename... T_Args>
inline std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>> MethodContainer_<T_Class, T_Ret, T_Args...>::copy() const
{
	return std::unique_ptr<IFunctionContainer_<T_Ret, T_Args...>>(new MethodContainer_<T_Class, T_Ret, T_Args...>(object, function));
}

template<typename T_Class, typename T_Ret, typename... T_Args>
int MethodContainer_<T_Class, T_Ret, T_Args...>::hash() const
{
	return reinterpret_cast<int>(&function) - reinterpret_cast<int>(object);
}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::Delegate() :
	func_(nullptr),
	is_method_(false)
{}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::Delegate(const Delegate<T_Ret, T_Args...>& delegate) :
	func_(nullptr),
	is_method_(delegate.is_method_)
{
	if (delegate.func_)
	{
		func_ = delegate.func_->copy();
	}
}

template<typename T_Ret, typename... T_Args>
String Delegate<T_Ret, T_Args...>::to_string() const noexcept
{
	if (is_valid())
	{
		if (is_method_)
		{
			return L"Delegate (method)"_s;
		}
		else
		{
			return L"Delegate (function)"_s;
		}
	}
	else
	{
		return L"Empty delegate"_s;
	}
}

template<typename T_Ret, typename... T_Args>
int Delegate<T_Ret, T_Args...>::hash_code() const noexcept
{
	if (is_valid())
	{
		return func_->hash();
	}
	else
	{
		return 0;
	}
}

template<typename T_Ret, typename... T_Args>
bool Delegate<T_Ret, T_Args...>::is_valid() const noexcept
{
	return func_ && func_->is_valid();
}

template<typename T_Ret, typename... T_Args>
void Delegate<T_Ret, T_Args...>::bind(const std::function<T_Ret(T_Args...)>& func)
{
	func_.reset(new FunctionContainer_<T_Ret, T_Args...>(func));
}

template<typename T_Ret, typename ...T_Args>
template<typename T_Class>
void Delegate<T_Ret, T_Args...>::bind(T_Class& object, const std::function<T_Ret(T_Class&, T_Args...)>& func)
{
	func_.reset(new MethodContainer_<T_Class, T_Ret, T_Args...>(&object, func));
}


template<typename T_Ret, typename... T_Args>
void Delegate<T_Ret, T_Args...>::unbind()
{
	func_.reset();
}

template<typename T_Ret, typename... T_Args>
T_Ret Delegate<T_Ret, T_Args...>::execute(T_Args ...args)
{
	if (func_)
	{
		return func_->execute(args...);
	}
	else if (!std::is_same<T_Ret, void>::value) // No exception if return type is void
	{
		throw std::logic_error("Attempt to call an empty delegate");
	}
}

template<typename T_Ret, typename... T_Args>
T_Ret Delegate<T_Ret, T_Args...>::operator()(T_Args ...args)
{
	return execute(args...);
}

template<typename T_Ret, typename... T_Args>
Delegate<T_Ret, T_Args...>::operator bool() const noexcept
{
	return is_valid();
}

}
