    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.cpp                   //
////////////////////////////////////////

#pragma once

#include "Level.h"

#include "../Util/Util.h"

using namespace snow;

Level::Level() noexcept :
	Level(L"SnowEngine Level "_s + util::to_string(number_++))
{}

Level::Level(const String& name) noexcept :
	name(name)
{}

String Level::to_string() const noexcept
{
	return L"Level \"" + name + L"\"";
}

int Level::hash_code() const noexcept
{
	return name.hash_code();
}

int Level::number_ = 0;
