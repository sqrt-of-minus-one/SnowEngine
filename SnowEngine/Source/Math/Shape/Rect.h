    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Rect.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"

namespace snow
{

class Rect : public Object
{
public:
	Rect();
	Rect(const Rect& rect);
	Rect(const Vector2& position, const Vector2& size);
	
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;
	
	const Vector2& get_position() const;
	Vector2 get_corner_position() const;
	const Vector2& get_size() const;
	
	void set_position(const Vector2& position);
	void set_corner_position(const Vector2& corner_position);
	void set_size(const Vector2& size);
	
	bool overlap(const Rect& rect) const;
	float perimeter() const;
	float area() const;
	
	Rect& operator=(const Rect& rect);
	bool operator==(const Rect& rect) const;
	bool operator!=(const Rect& rect) const;

private:
	Vector2 position_;
	Vector2 size_;
};

}
