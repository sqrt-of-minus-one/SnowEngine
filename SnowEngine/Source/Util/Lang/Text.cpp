    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Text.cpp                    //
////////////////////////////////////////

//   \_____/     ***     SnowFlake            *****  *           *                               //
//   /\___/\    *   *                         *      *           *                               //
//  / /\ /\ \   *      ****    ***   *     *  *      *    ****   *  *   ***                      //
// =====X=====   ***   *   *  *   *  *     *  *****  *   *   *   * *   *   *     **************  //
//  \ \/_\/ /       *  *   *  *   *  *  *  *  *      *   *   *   **    *****    *  SnowEngine  * //
//   \/___\/    *   *  *   *  *   *  * * * *  *      *   *   *   * *   *        * localization * //
//   /     \     ***   *   *   ***    *   *   *       *   *** *  *  *   ****    *    system    * //

#include "Text.h"

#include "../Game.h"
#include "../Lang/Lang.h"

using namespace snow;

		/* Text: public */

Text::Text() noexcept :
	key_()
{}

Text::Text(const Text& text) noexcept :
	key_(text.key_)
{}

Text::Text(Text&& text) noexcept :
	key_(std::move(text.key_))
{}

Text::Text(const String& key) noexcept :
	key_(key)
{}

Text::Text(String&& key) noexcept :
	key_(std::move(key))
{}

String Text::to_string() const noexcept
{
	try
	{
		return Game::lang.get_string(key_);
	}
	catch (...)
	{
		return key_;
	}
}

int Text::hash_code() const noexcept
{
	return key_.hash_code();
}

const String& Text::get_key() const noexcept
{
	return key_;
}

bool Text::is_valid() const noexcept
{
	try
	{
		return Game::lang.is_valid(key_);
	}
	catch (...)
	{
		return false;
	}
}

Text& Text::operator=(const Text& text)
{
	key_ = text.key_;
	return *this;
}

Text& Text::operator=(Text&& text)
{
	key_ = std::move(text.key_);
	return *this;
}

Text& Text::operator=(const String& key)
{
	key_ = key;
	return *this;
}

Text& Text::operator=(String&& key)
{
	key_ = std::move(key);
	return *this;
}

bool Text::operator==(const Text& text) const
{
	return key_ == text.key_;
}

bool Text::operator==(const String& key) const
{
	return key_ == key;
}

bool Text::operator!=(const Text& text) const
{
	return key_ != text.key_;
}

bool Text::operator!=(const String& key) const
{
	return key_ != key;
}
