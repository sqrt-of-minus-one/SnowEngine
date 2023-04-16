    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.h                   //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

namespace snow
{

namespace json
{

class JsonObject;
class Array;

enum class EType
{
	OBJECT,
	ARRAY,
	STRING_VALUE,
	INT_VALUE,
	DOUBLE_VALUE,
	BOOL_VALUE,
	NULL_VALUE
};

class Element : public Object
{
public:
	virtual String to_string() const override;
	
	void save(const String& filename) const;
	virtual void to_stream(std::wostream& stream, int nesting = 0) const = 0;
	virtual EType get_type() const = 0;
	
	static std::unique_ptr<Element> from_string(const String& string);
	static std::unique_ptr<Element> load(const String& filename);
	
private:
	static std::unique_ptr<Element> read_element_(std::wistream& stream);
	static std::unique_ptr<JsonObject> read_object_(std::wistream& stream);
	static std::unique_ptr<Array> read_array_(std::wistream& stream);
	static String read_string_(std::wistream& stream, wchar_t first);
	static std::unique_ptr<Element> read_number_(std::wistream& stream, wchar_t first);
	static bool read_lit_(std::wistream& stream, const String& lit);
	static void read_comment_(std::wistream& stream);
};

}

}
