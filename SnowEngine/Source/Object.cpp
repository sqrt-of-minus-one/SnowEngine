    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Object.cpp                  //
////////////////////////////////////////

#include "Object.h"

using namespace snow;

		/* Object: public */

Object::Object()
{
	existing_objects_().insert(this);
}

Object::~Object()
{
	existing_objects_().erase(this);
}

bool Object::is_valid(const Object* object)
{
	return object && existing_objects_().count(object) != 0;
}

		/* Object: private */

std::unordered_set<const Object*>& Object::existing_objects_()
{
	static std::unordered_set<const Object*> existing_objects;
	return existing_objects;
}
