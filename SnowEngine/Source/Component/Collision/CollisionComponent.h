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

#include "../../Math/Shape/IntRect.h"

namespace snow
{

class Actor;

class CollisionComponent : public Component
{
public:
	CollisionComponent(Actor& actor, Component* parent, const Transform& transform);
	~CollisionComponent();

	virtual bool overlap(const CollisionComponent& collision_component_) const = 0;
	std::vector<CollisionComponent*> get_overlap() const;

protected:

	virtual IntRect get_boundary_rect() = 0;

private:
	IntRect boundary_rect_;
	Point2 min_chunk_;
	Point2 max_chunk_;

	static std::map<const Level*, std::unordered_map<int /*x*/, std::unordered_map<int /*y*/, std::unordered_set<CollisionComponent*>>>> collision_chunks_;

	void update_chunks_(Component& component, const Transform& new_transform);
};

}
