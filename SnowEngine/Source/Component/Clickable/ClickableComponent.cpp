    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ClickableComponent.cpp      //
////////////////////////////////////////

#include "ClickableComponent.h"

#include "../../Actor/Actor.h"
#include "../../Component/Camera/CameraComponent.h"
#include "../../Util/Input/Input.h"
#include "../../Game/Game.h"
#include "../../Game/Config.h"
#include "../../Math/Math.h"

using namespace snow;

		/* ClickableComponent: public */

ClickableComponent::ClickableComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	boundary_rect_(),
	min_chunk_(static_cast<Point2>(boundary_rect_.get_position()) / Game::config.clickable_chunk_size),
	max_chunk_(static_cast<Point2>(boundary_rect_.get_position() + boundary_rect_.get_size()) / Game::config.clickable_chunk_size),
	on_pressed_(),
	on_released_(),
	on_pressed(on_pressed_),
	on_released(on_released_)
{}

ClickableComponent::~ClickableComponent()
{
	auto& map = clickable_chunks_[&get_level()];
	for (int i = min_chunk_.get_x(); i < max_chunk_.get_x(); i++)
	{
		auto& map_map = map[i];
		for (int j = min_chunk_.get_y(); j < max_chunk_.get_y(); j++)
		{
			map_map[j].erase(this);
		}
	}
}

bool ClickableComponent::is_mouse_over() const
{
	auto iter = CameraComponent::get_camera_components().find(&get_level());
	if (iter != CameraComponent::get_camera_components().end())
	{
		const auto& cameras = iter->second;
		for (const CameraComponent* i : cameras)
		{
			if (is_inside(Input::get_instance().get_level_mouse_position(*i)))
			{
				return true;
			}
		}
	}
	return false;
}

std::vector<ClickableComponent*> ClickableComponent::get_clicked(const Level& level, const Vector2& position)
{
	std::vector<ClickableComponent*> ret;
	try
	{
		const auto& map = clickable_chunks_.at(&level)
				.at(static_cast<int>(position.get_x()) / Game::config.clickable_chunk_size.get_x())
				.at(static_cast<int>(position.get_y()) / Game::config.clickable_chunk_size.get_y());
		for (ClickableComponent* i : map)
		{
			if (i->is_inside(position))
			{
				ret.push_back(i);
			}
		}
		return ret;
	}
	catch (std::out_of_range e)
	{
		return ret;
	}
}

		/* ClickableComponent: protected */

void ClickableComponent::setup_chunks()
{
	FloatRect new_boundary_rect = get_boundary_rect();
	Point2 new_min_chunk = static_cast<Point2>(new_boundary_rect.get_position()) / Game::config.clickable_chunk_size;
	Point2 new_max_chunk = static_cast<Point2>(new_boundary_rect.get_position() + new_boundary_rect.get_size()) / Game::config.clickable_chunk_size;
	auto& map = clickable_chunks_[&get_level()];
	for (int i = min_chunk_.get_x(); i <= max_chunk_.get_x(); i++)
	{
		auto& map_map = map[i];
		for (int j = min_chunk_.get_y(); j <= max_chunk_.get_y(); j++)
		{
			if (i < new_min_chunk.get_x() || i > new_max_chunk.get_x() || j < new_min_chunk.get_y() || j > new_max_chunk.get_y())
			{
				map_map[j].erase(this);
			}
		}
	}
	for (int i = new_min_chunk.get_x(); i <= new_max_chunk.get_x(); i++)
	{
		auto& map_map = map[i];
		for (int j = new_min_chunk.get_y(); j <= new_max_chunk.get_y(); j++)
		{
			if (i >= min_chunk_.get_x() && i <= max_chunk_.get_x() && j >= min_chunk_.get_y() && j <= max_chunk_.get_y())
			{
				map_map[j].insert(this);
			}
		}
	}
	boundary_rect_ = new_boundary_rect;
	min_chunk_ = new_min_chunk;
	max_chunk_ = new_max_chunk;
}

void ClickableComponent::when_begin_play()
{
	Component::when_begin_play();

	setup_chunks();
}

void ClickableComponent::when_transformed(const Transform& new_level_transform)
{
	Component::when_transformed(new_level_transform);

	setup_chunks();
}

void ClickableComponent::when_pressed(EButton button)
{}

void ClickableComponent::when_released(EButton button)
{}

		/* ClickableComponent: private */

std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<ClickableComponent*>>>> ClickableComponent::clickable_chunks_;
