    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: VisibleComponent.h          //
////////////////////////////////////////

#include "VisibleComponent.h"

#include "../../Actor/Actor.h"

using namespace snow;

		/* VisibleComponent: public */

VisibleComponent::VisibleComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform)
{
	visible_components_[&actor.get_level()].push_back(this);
}

VisibleComponent::~VisibleComponent()
{
	auto& list = visible_components_[&get_level()];
	for (auto i = list.begin(); i != list.end(); i++)
	{
		if (*i == this)
		{
			list.erase(i);
			break;
		}
	}
}

const std::map<Level*, std::list<VisibleComponent*>>& VisibleComponent::get_visible_components()
{
	return visible_components_;
}

		/* VisibleComponent: protected */

void VisibleComponent::tick(float delta_sec)
{
	Component::tick(delta_sec);
}

		/* VisibleComponent: private */

std::map<Level*, std::list<VisibleComponent*>> VisibleComponent::visible_components_;
