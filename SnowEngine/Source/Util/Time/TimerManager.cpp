    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimerManager.cpp            //
////////////////////////////////////////

#include "TimerManager.h"

using namespace snow;

		/* TimerManager: public */

String TimerManager::to_string() const
{
	return L"There are "_s + util::to_string(timers_.size()) + L" timer(s)";
}

int TimerManager::hash_code() const noexcept
{
	return timers_.hash_code();
}

std::shared_ptr<Timer> TimerManager::create_timer(const Delegate<void>& function, float delay_sec, float period_sec)
{
	std::shared_ptr<Timer> p(new Timer(function, delay_sec, period_sec));
	timers_.add(p);
	return p;
}

		/* TimerManager: private */

TimerManager::TimerManager() :
	timers_()
{}

void TimerManager::tick_(float delta_sec)
{
	bool remove_flag = false;
	for (auto i = timers_.begin(); !i.is_end(); !remove_flag && i.next())
											 // if (!remove_flag) i.next();
	{
		remove_flag = false;
		Timer& timer = *(i.get());
		timer.tick_(delta_sec);
		if (!timer.is_active_)
		{
			timers_.remove(i);
			remove_flag = true; // The iterator is already pointing to the next element,
								// we don't need to move it again
		}
	}
}
