    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: VisibleComponent.h          //
////////////////////////////////////////

#include "VisibleComponent.h"

#include "../../Actor/Actor.h"
#include "../Camera/CameraComponent.h"

using namespace snow;

		/* VisibleComponent: public */

VisibleComponent::VisibleComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	layer_(0),
	on_draw_id_(CameraComponent::on_draw(actor.get_level(), layer_).bind<VisibleComponent>(*this, &VisibleComponent::draw))
{}

VisibleComponent::~VisibleComponent()
{
	if (on_draw_id_ >= 0)
	{
		CameraComponent::on_draw(get_level(), layer_).unbind(on_draw_id_);
	}
}

void VisibleComponent::set_visible(bool is_visible)
{
	if (is_visible)
	{
		if (on_draw_id_ < 0)
		{
			on_draw_id_ = CameraComponent::on_draw(get_level(), layer_).bind<VisibleComponent>(*this, &VisibleComponent::draw);
		}
	}
	else
	{
		if (on_draw_id_ >= 0)
		{
			CameraComponent::on_draw(get_level(), layer_).unbind(on_draw_id_);
			on_draw_id_ = -1;
		}
	}
}

bool VisibleComponent::is_visible() const
{
	return on_draw_id_ >= 0;
}

void VisibleComponent::set_layer(int layer)
{
	if (is_visible())
	{
		CameraComponent::on_draw(get_level(), layer_).unbind(on_draw_id_);
		on_draw_id_ = CameraComponent::on_draw(get_level(), layer).bind<VisibleComponent>(*this, &VisibleComponent::draw);
	}
	layer_ = layer;
}

int VisibleComponent::get_layer() const
{
	return layer_;
}
