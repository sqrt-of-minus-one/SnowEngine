    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: FloatRect.h                 //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Vector2.h"

namespace snow
{

class FloatRect : public Object
{
public:
	FloatRect();
	FloatRect(const FloatRect& rect);
	FloatRect(const Vector2& position, const Vector2& size);
	
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;
	
	const Vector2& get_position() const;
	Vector2 get_corner_position() const;
	const Vector2& get_size() const;
	
	void set_position(const Vector2& position);
	void set_corner_position(const Vector2& corner_position);
	void set_size(const Vector2& size);
	
	bool overlap(const FloatRect& rect) const;
	float perimeter() const;
	float area() const;
	
	FloatRect& operator=(const FloatRect& rect);
	bool operator==(const FloatRect& rect) const;
	bool operator!=(const FloatRect& rect) const;

private:
	Vector2 position_;
	Vector2 size_;
};

}
