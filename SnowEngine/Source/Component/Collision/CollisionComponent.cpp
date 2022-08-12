    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CollisionComponent.cpp      //
////////////////////////////////////////

#include "CollisionComponent.h"

#include "../../Actor/Actor.h"
#include "../../Game/Game.h"
#include "../../Game/Config.h"
#include "../../Math/Math.h"

using namespace snow;

		/* CollisionComponent: public */

CollisionComponent::CollisionComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	boundary_rect_(),
	min_chunk_(static_cast<Point2>(boundary_rect_.get_position()) / Game::config.collision_chunk_size),
	max_chunk_(static_cast<Point2>(boundary_rect_.get_position() + boundary_rect_.get_size()) / Game::config.collision_chunk_size)
{}

CollisionComponent::~CollisionComponent()
{
	auto& map = collision_chunks_[&get_level()];
	for (int i = min_chunk_.get_x(); i < max_chunk_.get_x(); i++)
	{
		auto& map_map = map[i];
		for (int j = min_chunk_.get_y(); j < max_chunk_.get_y(); j++)
		{
			map_map[j].erase(this);
		}
	}
}

std::vector<CollisionComponent*> CollisionComponent::get_overlap() const
{
	std::vector<CollisionComponent*> ret;
	std::unordered_set<CollisionComponent*> checked;
	const auto& map = collision_chunks_.at(&get_level());
	for (int i = min_chunk_.get_x(); i < max_chunk_.get_x(); i++)
	{
		const auto& map_map = map.at(i);
		for (int j = min_chunk_.get_y(); j < max_chunk_.get_y(); j++)
		{
			const auto& set = map_map.at(j);
			for (CollisionComponent* k : set)
			{
				if (k != this && checked.find(k) == checked.end() && Object::is_valid(k))
				{
					checked.insert(k);
					if (overlap(*k))
					{
						ret.push_back(k);
					}
				}
			}
		}
	}
	return ret;
}

		/* CollisionComponent: protected */

void CollisionComponent::when_begin_play()
{
	Component::when_begin_play();

	when_transformed(get_level_transform());
}

void CollisionComponent::when_transformed(const Transform& new_level_transform)
{
	FloatRect new_boundary_rect = get_boundary_rect();
	Point2 new_min_chunk = static_cast<Point2>(new_boundary_rect.get_position()) / Game::config.collision_chunk_size;
	Point2 new_max_chunk = static_cast<Point2>(new_boundary_rect.get_position() + new_boundary_rect.get_size()) / Game::config.collision_chunk_size;
	auto& map = collision_chunks_[&get_level()];
	for (int i = min_chunk_.get_x(); i < max_chunk_.get_x(); i++)
	{
		auto& map_map = map[i];
		for (int j = min_chunk_.get_y(); j < max_chunk_.get_y(); j++)
		{
			if (i < new_min_chunk.get_x() || i > new_max_chunk.get_x() || j < new_min_chunk.get_y() || j > new_max_chunk.get_y())
			{
				map_map[j].erase(this);
			}
		}
	}
	for (int i = new_min_chunk.get_x(); i < new_max_chunk.get_x(); i++)
	{
		auto& map_map = map[i];
		for (int j = new_min_chunk.get_y(); j < new_max_chunk.get_y(); j++)
		{
			if (i < min_chunk_.get_x() || i > max_chunk_.get_x() || j < min_chunk_.get_y() || j > max_chunk_.get_y())
			{
				map_map[j].insert(this);
			}
		}
	}
	boundary_rect_ = new_boundary_rect;
	min_chunk_ = new_min_chunk;
	max_chunk_ = new_max_chunk;
}

		/* CollisionComponent: private */

std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<CollisionComponent*>>>> CollisionComponent::collision_chunks_;
