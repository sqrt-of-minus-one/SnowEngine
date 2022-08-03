    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Transform.h                 //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../../Math/Vector/Vector2.h"
#include "../../Math/Angle.h"

namespace snow
{

class Transform : public Object
{
public:
	Transform();
	Transform(const Vector2& position = Vector2::ZERO, const Angle& rotation = Angle::ZERO, const Vector2& scale = Vector2(1.f, 1.f));
	Transform(const Transform& transform);
	
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;
	
	const Vector2& get_position() const noexcept;
	const Angle& get_rotation() const noexcept;
	const Vector2& get_scale() const noexcept;
	
	void set_position(const Vector2& position) noexcept;
	void set_rotation(const Angle& rotation) noexcept;
	void set_scale(const Vector2& scale) noexcept;

	Transform& operator=(const Transform& transform) noexcept;
	bool operator==(const Transform& transform) const noexcept;
	bool operator!=(const Transform& transform) const noexcept;

private:
	Vector2 position_;
	Angle rotation_;
	Vector2 scale_;

};
