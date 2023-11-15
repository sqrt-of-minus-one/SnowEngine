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

#include "../../Game/ConfigManager.h"
#include "../Lang/LangManager.h"
#include "../Json/JsonObject.h"
#include "../Json/Value.h"

using namespace snow;

		/* Text: public */

Text::Text() :
	table_(),
	id_()
{}

Text::Text(const Text& text) :
	table_(text.table_),
	id_(text.id_)
{}

Text::Text(Text&& text) :
	table_(std::move(text.table_)),
	id_(std::move(text.id_))
{}

Text::Text(const String& key) :
	table_(),
	id_()
{
	std::pair<String, String> pair = LangManager::key_to_table_and_id(key);
	table_ = std::move(pair.first);
	id_ = std::move(pair.second);
}

Text::Text(const String& table, const String& key) :
	table_(table),
	id_(key)
{
	if (key.empty())
	{
		table_.clear();
	}
	else if (table_.empty())
	{
		table_ = CURRENT_CONFIG.lang_default_table;
	}
}

Text::Text(std::shared_ptr<const json::Element> json) :
	table_(),
	id_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a text: the JSON cannot be nullptr");
	}

	switch (json->get_type())
	{
	case json::EType::STRING_VALUE:
	{
		id_ = util::json_to_string(json);
		break;
	}
	case json::EType::OBJECT:
	{
		std::shared_ptr<const json::JsonObject> object = std::dynamic_pointer_cast<const json::JsonObject>(json);
		if (object->get_content().size() != 1)
		{
			throw std::invalid_argument("Couldn't create a text: the JSON object must only have one element");
		}
		id_ = object->get_content().begin()->first;
		break;
	}
	default:
	{
		throw std::invalid_argument("Couldn't create a text: the JSON must be either a string or an object");
	}
	}
}

String Text::to_string() const
{
	return LangManager::get_instance().get_string(table_, id_);
}

std::shared_ptr<json::Element> Text::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ get_key(), util::to_json(to_string()) });
	return result;
}

String Text::get_key() const
{
	if (!id_.empty() && !table_.empty())
	{
		table_ + L'.' + id_;
	}
	else
	{
		return L"";
	}
}

const String& Text::get_table() const
{
	return table_;
}

const String& Text::get_id() const
{
	return id_;
}

bool Text::is_valid() const noexcept
{
	try
	{
		return LangManager::get_instance().is_valid(get_key());
	}
	catch (...)
	{
		return false;
	}
}

Text& Text::operator=(const Text& text)
{
	table_ = text.table_;
	id_ = text.id_;
	return *this;
}

Text& Text::operator=(Text&& text)
{
	id_ = std::move(text.id_);
	return *this;
}

Text& Text::operator=(const String& key)
{
	std::pair<String, String> pair = LangManager::key_to_table_and_id(key);
	table_ = std::move(pair.first);
	id_ = std::move(pair.second);
	return *this;
}

bool Text::operator==(const Text& text) const noexcept
{
	return table_ == text.table_ && id_ == text.id_;
}

bool Text::operator==(const String& key) const noexcept
{
	return *this == Text(key);
}

bool Text::operator!=(const Text& text) const noexcept
{
	return !(*this == text);
}

bool Text::operator!=(const String& key) const noexcept
{
	return !(*this == key);
}
