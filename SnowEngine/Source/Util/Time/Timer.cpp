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
	return String::format(L"Timer (period %fs; %fs left"_s, period_sec_, left_sec_) +
		(is_paused_ ? L"; paused)" : L")");
}

std::shared_ptr<json::Element> Timer::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ L"period_sec"_s, util::to_json(period_sec_) });
	result->get_content().insert({ L"left_sec"_s, util::to_json(left_sec_) });
	result->get_content().insert({ L"is_paused"_s, util::to_json(is_paused_) });
	return result;
}

void Timer::set_function(const Delegate<void>& function)
{
	function_.bind(function);
}

double Timer::get_period_sec() const
{
	return period_sec_;
}

void Timer::set_period_sec(double period_sec)
{
	period_sec_ = period_sec;
	left_sec_ = period_sec_;
}

double Timer::get_left_sec() const
{
	return left_sec_;
}

bool Timer::is_paused() const
{
	return is_paused_;
}

void Timer::pause()
{
	is_paused_ = true;
}

void Timer::unpause()
{
	if (is_active_)
	{
		is_paused_ = false;
	}
}

bool Timer::is_active() const
{
	return is_active_;
}

void Timer::remove()
{
	is_paused_ = true;
	is_active_ = false;
}

		/* Timer: private */

Timer::Timer(const Delegate<void>& function, double delay_sec, double period_sec) :
	function_(function),
	period_sec_(period_sec),
	left_sec_(delay_sec),
	is_paused_(false),
	is_active_(true)
{}

void Timer::tick_(double delta_sec)
{
	if (!is_paused_)//&& (left_sec_ -= delta_sec) <= 0.)
	{
		static double err = 0.;
		
		// Kahan summation algorithm to reduce error
		double tmp1 = -delta_sec - err;
		double tmp2 = left_sec_ + tmp1;
		err = (tmp2 - left_sec_) - tmp1;
		left_sec_ = tmp2;

		if (left_sec_ <= 0.)
		{
			function_.execute();
			if (period_sec_ > 0.)
			{
				left_sec_ += period_sec_;
			}
			else
			{
				left_sec_ = 0.;
				is_paused_ = true;
				is_active_ = false;
			}
		}
	}
}
