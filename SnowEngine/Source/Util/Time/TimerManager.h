    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimerManager.h              //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Container/LinkedList.h"
#include "Timer.h"

namespace snow
{

class TimerManager : public Object
{
	friend class Game;

public:
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	std::shared_ptr<Timer> create_timer(const Delegate<void>& function, float delay_sec, float period_sec = 0);
	
private:
	TimerManager();

	LinkedList<std::shared_ptr<Timer>> timers_;

	void tick_(float delta_sec);
};

}
