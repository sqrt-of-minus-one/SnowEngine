    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: JsonObject.h                //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Element.h"

#include <map>

namespace snow
{

namespace json
{

class JsonObject : public Element
{
public:
	JsonObject();
	JsonObject(JsonObject&& object);
	
	virtual int hash_code() const noexcept override;
	
	virtual EType get_type() const override;

	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
	
	std::map<String, std::unique_ptr<Element>>& get_content() noexcept;
	const std::map<String, std::unique_ptr<Element>>& get_content() const noexcept;
	
private:
	std::map<String, std::unique_ptr<Element>> content_;
};

}

}
