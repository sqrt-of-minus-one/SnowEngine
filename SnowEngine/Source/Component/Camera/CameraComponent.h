    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CameraComponent.h           //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <map>

#include <SFML/Graphics/View.hpp>

#include "../../Math/Shape/FloatRect.h"

namespace snow
{

class Actor;

class CameraComponent : public Component
{
public:
	CameraComponent(Actor& actor, Component* parent, const Transform& transform);
	~CameraComponent();

	FloatRect get_viewport() const;
	void set_viewport(const FloatRect& rect);

	static const std::map<Level*, std::list<CameraComponent*>> get_camera_components();

protected:
	virtual void tick(float delta_sec) override;
	virtual void when_transformed(const Transform& new_level_transform) override;

private:
	sf::View view_;

	static std::map<Level*, std::list<CameraComponent*>> camera_components_;
};

}
