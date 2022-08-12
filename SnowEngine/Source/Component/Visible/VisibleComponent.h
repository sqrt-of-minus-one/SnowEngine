    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: VisibleComponent.h          //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <map>
#include <list>

namespace sf
{
class RenderWindow;
}

namespace snow
{

class Actor;

class VisibleComponent : public Component
{
public:
	VisibleComponent(Actor& actor, Component* parent, const Transform& transform);
	~VisibleComponent();

	virtual void draw(sf::RenderWindow& window) = 0;

	static const std::map<Level*, std::list<VisibleComponent*>>& get_visible_components();

private:
	static std::map<Level*, std::list<VisibleComponent*>> visible_components_;
};

}
