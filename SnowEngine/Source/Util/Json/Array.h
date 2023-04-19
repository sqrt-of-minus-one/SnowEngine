    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
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

#include <vector>

namespace snow
{

namespace json
{

class Array : public Element
{
public:
	Array();
	Array(Array&& object);
	
	virtual int hash_code() const noexcept override;
	
	virtual EType get_type() const override;
	
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
	
	std::vector<std::unique_ptr<Element>>& get_content() noexcept;
	const std::vector<std::unique_ptr<Element>>& get_content() const noexcept;
	
private:
	std::vector<std::unique_ptr<Element>> content_;
};

}

}
