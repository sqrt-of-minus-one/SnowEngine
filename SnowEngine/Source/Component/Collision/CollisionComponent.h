    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CollisionComponent.h        //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "../../Math/Shape/FloatRect.h"
#include "../../Math/Vector/Point2.h"

namespace snow
{

class Actor;

class CollisionComponent : public Component
{
public:
	CollisionComponent(Actor& actor, Component* parent, const Transform& transform);
	~CollisionComponent();

	virtual bool overlap(const CollisionComponent& collision_component) const = 0;
	std::vector<CollisionComponent*> get_overlap() const;

	virtual FloatRect get_boundary_rect() const = 0;

protected:
	virtual void when_begin_play() override;
	virtual void when_transformed(const Transform& new_level_transform) override;

private:
	FloatRect boundary_rect_;
	Point2 min_chunk_;
	Point2 max_chunk_;

	static std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<CollisionComponent*>>>> collision_chunks_;
};

}
