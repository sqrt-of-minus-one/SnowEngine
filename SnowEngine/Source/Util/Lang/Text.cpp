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

#include "../../Game/Game.h"
#include "../Lang/Lang.h"
#include "../Json/JsonObject.h"
#include "../Json/Value.h"

using namespace snow;

		/* Text: public */

Text::Text() :
	key_()
{}

Text::Text(const Text& text) :
	key_(text.key_)
{}

Text::Text(Text&& text) :
	key_(std::move(text.key_))
{}

Text::Text(const String& key) :
	key_(key)
{}

Text::Text(String&& key) :
	key_(std::move(key))
{}

Text::Text(std::shared_ptr<const json::Element> json) :
	key_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a text: the JSON cannot be nullptr");
	}

	switch (json->get_type())
	{
	case json::EType::STRING_VALUE:
	{
		key_ = std::dynamic_pointer_cast<const json::StringValue>(json)->get();
		break;
	}
	case json::EType::OBJECT:
	{
		std::shared_ptr<const json::JsonObject> object = std::dynamic_pointer_cast<const json::JsonObject>(json);
		if (object->get_content().size() != 1)
		{
			throw std::invalid_argument("Couldn't create a text: the JSON object must only have one element");
		}
		key_ = object->get_content().begin()->first;
		break;
	}
	default:
	{
		throw std::invalid_argument("Couldn't create a text: the JSON must be either a string or a object");
	}
	}
}

String Text::to_string() const
{
	return Lang::get_instance().get_string(key_);
}

std::shared_ptr<json::Element> Text::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ key_, to_string().to_json() });
	return result;
}

const String& Text::get_key() const
{
	return key_;
}

bool Text::is_valid() const noexcept
{
	try
	{
		return Lang::get_instance().is_valid(key_);
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

bool Text::operator==(const Text& text) const noexcept
{
	return key_ == text.key_;
}

bool Text::operator==(const String& key) const noexcept
{
	return key_ == key;
}

bool Text::operator!=(const Text& text) const noexcept
{
	return key_ != text.key_;
}

bool Text::operator!=(const String& key) const noexcept
{
	return key_ != key;
}
