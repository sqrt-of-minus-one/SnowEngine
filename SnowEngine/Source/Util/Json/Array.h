    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

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
	
	std::vector<std::unique_ptr<Element>>& get_content() noexcept;
	const std::vector<std::unique_ptr<Element>>& get_content() const noexcept;
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
	
private:
	std::vector<std::unique_ptr<Element>> content_;
};

}

}
