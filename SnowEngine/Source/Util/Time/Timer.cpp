    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Timer.cpp                   //
////////////////////////////////////////

#include "Timer.h"

#include "../Json/JsonObject.h"
#include "../Util.h"

using namespace snow;

		/* Timer: public */

String Timer::to_string() const
{
	return string::format(L"Timer (period %fs; %fs left",
		time::std_to_sec(period_),
		get_left_sec()) +
		(is_paused_ ? L"; paused)" : L")");
}

std::shared_ptr<json::Element> Timer::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ L"period_sec", util::to_json(time::std_to_sec(period_)) });
	result->get_content().insert({ L"left_sec", util::to_json(get_left_sec()) });
	result->get_content().insert({ L"is_paused", util::to_json(is_paused_) });
	return result;
}

void Timer::set_function(const Delegate<void>& function)
{
	function_.bind(function);
}

double Timer::get_period_sec() const
{
	return time::std_to_sec(period_);
}

void Timer::set_period_sec(double period_sec)
{
	if (period_sec > 0.)
	{
		period_ = time::sec_to_std(period_sec);
		expires_ = time::now() + period_;
		if (is_paused_)
		{
			paused_ = time::now();
		}
	}
	else
	{
		period_ = time::sec_to_std(0.);
	}
}

double Timer::get_left_sec() const
{
	return time::std_to_sec(expires_ - (is_paused_ ? paused_ : time::now()));
}

bool Timer::is_paused() const
{
	return is_paused_;
}

void Timer::pause()
{
	if (!is_paused_)
	{
		paused_ = time::now();
		is_paused_ = true;
	}
}

void Timer::unpause()
{
	if (is_active_ && is_paused_)
	{
		expires_ += time::now() - paused_;
		is_paused_ = true;
	}
}

bool Timer::is_active() const
{
	return is_active_;
}

void Timer::remove()
{
	is_active_ = false;
	is_paused_ = true;
}

		/* Timer: private */

Timer::Timer(const Delegate<void>& function, double delay_sec, double period_sec) :
	function_(function),
	period_(time::sec_to_std(period_sec > 0. ? period_sec : 0.)),
	expires_(time::now() + time::sec_to_std(delay_sec)),
	paused_(),
	is_paused_(false),
	is_active_(true)
{}

void Timer::tick_(double delta_sec)
{
	const TimePoint& now = time::now();
	if (!is_paused_ && now >= expires_)
	{
		function_.execute();
		if (period_.count() > 0)
		{
			expires_ += period_;
		}
		else
		{
			remove();
		}
	}
}
