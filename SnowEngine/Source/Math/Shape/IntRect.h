    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: IntRect.h                   //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Vector/Point2.h"

namespace snow
{

class IntRect : public Object
{
public:
	IntRect();
	IntRect(const IntRect& rect);
	IntRect(const Point2& position, const Point2& size);
	
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;
	
	const Point2& get_position() const;
	Point2 get_corner_position() const;
	const Point2& get_size() const;
	
	void set_position(const Point2& position);
	void set_corner_position(const Point2& corner_position);
	void set_size(const Point2& size);
	
	bool overlap(const IntRect& rect) const;
	int perimeter() const;
	int area() const;
	
	IntRect& operator=(const IntRect& rect);
	bool operator==(const IntRect& rect) const;
	bool operator!=(const IntRect& rect) const;

private:
	Point2 position_;
	Point2 size_;
};

}
