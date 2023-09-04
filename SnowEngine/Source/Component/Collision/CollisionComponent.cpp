    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CollisionComponent.cpp      //
////////////////////////////////////////

#include "CollisionComponent.h"

#include "../../Actor/Actor.h"
#include "../../Game/ConfigManager.h"
#include "../../Math/Math.h"

using namespace snow;

		/* CollisionComponent: public */

CollisionComponent::CollisionComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	boundary_rect_(),
	min_chunk_(static_cast<Point2>(boundary_rect_.get_position()) / CURRENT_CONFIG.chunks_collision_size),
	max_chunk_(static_cast<Point2>(boundary_rect_.get_position() + boundary_rect_.get_size()) / CURRENT_CONFIG.chunks_collision_size)
{}

CollisionComponent::~CollisionComponent()
{
	auto& level_chunks = collision_chunks_[&get_level()];
	for (int i = min_chunk_.get_x(); i <= max_chunk_.get_x(); i++)
	{
		auto& x_chunks = level_chunks[i];
		for (int j = min_chunk_.get_y(); j <= max_chunk_.get_y(); j++)
		{
			x_chunks[j].erase(this);
		}
	}
}

std::set<CollisionComponent*> CollisionComponent::get_overlap() const
{
	std::set<CollisionComponent*> ret;
	const auto& level_chunks = collision_chunks_.at(&get_level());

	// Get the components from the same chunk
	for (int i = min_chunk_.get_x(); i <= max_chunk_.get_x(); i++)
	{
		const auto& x_chunks = level_chunks.at(i);
		for (int j = min_chunk_.get_y(); j <= max_chunk_.get_y(); j++)
		{
			const auto& chunk_components = x_chunks.at(j);
			for (CollisionComponent* k : chunk_components)
			{
				ret.insert(k);
			}
		}
	}

	// Check if components overlap
	for (auto i = ret.begin(); i != ret.end(); )
	{
		if (*i == this || !is_valid(*i) || !overlap(**i))
		{
			i = ret.erase(i);
		}
		else
		{
			i++;
		}
	}
	return ret;
}

		/* CollisionComponent: protected */

void CollisionComponent::when_begin_play()
{
	Component::when_begin_play();

	setup_chunks_();
}

void CollisionComponent::when_transformed(const Transform& new_level_transform)
{
	Component::when_transformed(new_level_transform);

	setup_chunks_();
}

		/* CollisionComponent: private */

void CollisionComponent::setup_chunks_()
{
	DoubleRect new_boundary_rect = get_boundary_rect();
	Point2 new_min_chunk = static_cast<Point2>(new_boundary_rect.get_position()) / CURRENT_CONFIG.chunks_collision_size;
	Point2 new_max_chunk = static_cast<Point2>(new_boundary_rect.get_position() + new_boundary_rect.get_size()) / CURRENT_CONFIG.chunks_collision_size;
	auto& level_chunks = collision_chunks_[&get_level()];
	for (int i = min_chunk_.get_x(); i <= max_chunk_.get_x(); i++)
	{
		auto& x_chunks = level_chunks[i];
		for (int j = min_chunk_.get_y(); j <= max_chunk_.get_y(); j++)
		{
			if (i < new_min_chunk.get_x() || i > new_max_chunk.get_x() || j < new_min_chunk.get_y() || j > new_max_chunk.get_y())
			{
				x_chunks[j].erase(this);
			}
		}
	}
	for (int i = new_min_chunk.get_x(); i <= new_max_chunk.get_x(); i++)
	{
		auto& x_chunks = level_chunks[i];
		for (int j = new_min_chunk.get_y(); j <= new_max_chunk.get_y(); j++)
		{
			if (i >= min_chunk_.get_x() && i <= max_chunk_.get_x() && j >= min_chunk_.get_y() && j <= max_chunk_.get_y())
			{
				x_chunks[j].insert(this);
			}
		}
	}
	boundary_rect_ = new_boundary_rect;
	min_chunk_ = new_min_chunk;
	max_chunk_ = new_max_chunk;
}

std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<CollisionComponent*>>>> CollisionComponent::collision_chunks_;
