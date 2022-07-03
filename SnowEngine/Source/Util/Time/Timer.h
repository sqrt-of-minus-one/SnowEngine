    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Timer.h                     //
////////////////////////////////////////

#pragma once

#include "../Function/Delegate.h"
		// + Object

#include "TimeInterval.h"

namespace snow
{

class Timer : public Object
{
	friend class TimerManager;

public:
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	void set_function(const Delegate<void>& function);

	float get_period_sec() const;
	void set_period_sec(float period_sec);

	bool is_paused() const;
	void pause();
	void unpause();

	bool is_active() const;
	void remove();

private:
	Timer(const Delegate<void>& function, float delay_sec, float period_sec);

	Delegate<void> function_;
	float period_sec_;
	float left_sec_;
	bool is_paused_;
	bool is_active_;

	void tick_(float delta_sec);
};

}
