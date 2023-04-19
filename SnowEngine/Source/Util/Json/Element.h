    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.h                   //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

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

	virtual EType get_type() const = 0;
	
	void save(const String& filename) const;
	virtual void to_stream(std::wostream& stream, int nesting = 0) const = 0;
	
	static std::unique_ptr<Element> from_string(const String& string);
	static std::unique_ptr<Element> load(const String& filename);
	static std::unique_ptr<Element> from_stream(std::wistream& stream);
	
private:
	static std::unique_ptr<JsonObject> read_object_(std::wistream& stream); // The { character is supposed to be already read
	static std::unique_ptr<Array> read_array_(std::wistream& stream); // The [ character is supposed to be already read
	static String read_string_(std::wistream& stream, wchar_t first); // The " or ' character is supposed to be already read and is passed as argument (first)
	static std::unique_ptr<Element> read_number_(std::wistream& stream, wchar_t first); // The first character is supposed to be already read and is passed as argument (first)
	static bool read_lit_(std::wistream& stream, const String& lit); // The first character is supposed to be already read; returns false if couldn't read a desired literal (lit)
	static void read_comment_(std::wistream& stream); // The / character is supposed to be already read
	static void pass_(std::wistream& stream, wchar_t& c); // Pass the space characters and comments
};

}

}
