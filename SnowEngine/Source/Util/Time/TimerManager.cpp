    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimerManager.cpp            //
////////////////////////////////////////

#include "TimerManager.h"

#include "../Util.h"
#include "Timer.h"

using namespace snow;

		/* TimerManager: public */

TimerManager& TimerManager::get_instance()
{
	static TimerManager timer_manager;
	return timer_manager;
}

String TimerManager::to_string() const
{
	return L"There are "_s + util::to_string(static_cast<int>(timers_.size())) + L" timer(s)";
}

int TimerManager::hash_code() const noexcept
{
	int hash = 0;
	int sign = 1;
	for (const auto& i : timers_)
	{
		hash += sign * i->hash_code();
		sign = -sign;
	}
	return sign;
}

std::shared_ptr<Timer> TimerManager::create_timer(const Delegate<void>& function, double delay_sec, double period_sec)
{
	std::shared_ptr<Timer> p(new Timer(function, delay_sec, period_sec));
	timers_.push_back(p);
	return p;
}

		/* TimerManager: private */

TimerManager::TimerManager() :
	timers_()
{}

void TimerManager::tick_(double delta_sec)
{
	for (auto i = timers_.begin(); i != timers_.end(); )
	{
		Timer& timer = **i;
		timer.tick_(delta_sec);
		if (!timer.is_active_)
		{
			i = timers_.erase(i);
		}
		else
		{
			i++;
		}
	}
}
