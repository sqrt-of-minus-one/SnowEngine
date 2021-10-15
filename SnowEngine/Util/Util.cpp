    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#include "Util.h"

#include "Types/String.h"
#include "../Math/Math.h"

#include <string>

using namespace snow;

String util::to_string(int var) noexcept
{
	if (var == 0)
	{
		return String(L"0");
	}
	else
	{
		String res;
		int a = math::abs(var);
		while (a > 0)
		{
			res += static_cast<wchar_t>(static_cast<int>(L'0') + a % 10);
			a /= 10;
		}
		if (var < 0)
		{
			res += L'-';
		}
		return res.reverse();
	}
}

String util::to_string(float var) noexcept
{
	return std::to_wstring(var);
}

String util::to_string(wchar_t var) noexcept
{
	return String(var);
}

String util::to_string(bool var) noexcept
{
	return var ? L"true"_s : L"false"_s;
}


int util::hash_code(int var) noexcept
{
	return var;
}

int util::hash_code(float var) noexcept
{
	return static_cast<int>(var);
}

int util::hash_code(wchar_t var) noexcept
{
	return static_cast<int>(var);
}

int util::hash_code(bool var) noexcept
{
	return static_cast<int>(var);
}
