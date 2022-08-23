    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ClickableComponent.h        //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "../../Util/Input/Keys.h"
#include "../../Math/Shape/FloatRect.h"
#include "../../Math/Vector/Point2.h"

namespace snow
{

class Actor;

class ClickableComponent : public Component
{
	friend class Input;
	friend class Game;

public:
	ClickableComponent(Actor& actor, Component* parent, const Transform& transform);
	~ClickableComponent();

	virtual bool is_inside(const Vector2& position) const = 0;

	virtual FloatRect get_boundary_rect() const = 0;

	bool is_mouse_over() const;

	EventBinder<EButton /*button*/> on_pressed;
	EventBinder<EButton /*button*/> on_released;

	static std::vector<ClickableComponent*> get_clicked(const Level& level, const Vector2& position);

protected:
	virtual void when_begin_play() override;
	virtual void when_transformed(const Transform& new_level_transform) override;
	virtual void when_pressed(EButton button);
	virtual void when_released(EButton button);

private:
	FloatRect boundary_rect_;
	Point2 min_chunk_;
	Point2 max_chunk_;

	Event<EButton /*button*/> on_pressed_;
	Event<EButton /*button*/> on_released_;

	static std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<ClickableComponent*>>>> clickable_chunks_;
};

}
