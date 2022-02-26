    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Object.cpp                  //
////////////////////////////////////////

#include "Object.h"

using namespace snow;

Object::Object() noexcept
{
	existing_objects_.insert(this);
}

Object::~Object() noexcept
{
	existing_objects_.erase(this);
}

bool Object::is_valid(const Object* object) noexcept
{
	return object != nullptr && existing_objects_.count(object) != 0;
}

std::set<const Object*> Object::existing_objects_;
