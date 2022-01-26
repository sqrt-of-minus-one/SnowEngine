    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.h                    //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file with string class definition
 *	
 *	This file contains the definition of the String class.
 */

#include "../../Object.h"

#include <string>

namespace snow
{

/**
 *	\brief The SnowEngine string class
 *	
 *	This class is used by SnowEngine functions as string. It is based on std::wstring class. Note
 *	that SnowEngine uses wide characters.
 *
 *	You can use literal `_s` to simply create `snow::String`:
 *	\code
 *		// These two string do the same:
 *		String::format(String(L"Hello %s!"), String(L"SnowEngine"));
 *		String::format(L"Hello %s!"_s, L"SnowEngine"_s);
 *	\endcode
 */
class String : public Object
{
public:
	
	/**
	 *	\brief Create an empty string
	 *	
	 *	The default constrctor creates an empty string.
	 */
	String() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a copy of the passed string.
	 *	\param string The string to copy.
	 */
	String(const String& string) noexcept;

	/**
	 *	\brief Move constructor
	 *	
	 *	Creates a new string by moving the passed one.
	 *	\param string The string that will be moved.
	 */
	String(String&& string) noexcept;

	/**
	 *	\brief Create a string with one character
	 *	
	 *	Creates a new string and put into it the passed character. Note that SnowEngine uses wide
	 *	characters, so you should type `L` prefix:
	 *	\code
	 *		String str1(L'S');
	 *		String str2 = L'E';
	 *	\endcode
	 *	\param ch The character that will be added to string.
	 */
	String(wchar_t ch) noexcept;

	/**
	 *	\brief Create a string from the passed one
	 *	
	 *	Creates a new string from the passed one. Note that SnowEngine uses wide characters, so
	 *	you should type `L` prefix:
	 *	\code
	 *		String str1(L"Snow");
	 *		String str2 = L"Engine";
	 *	\endcode
	 *	\param string Raw string whose value will be assigned to a new one.
	 */
	String(const wchar_t* string) noexcept;

	/**
	 *	\brief Create a string from the passed one
	 *	
	 *	Creates a new string from the passed one. Note that SnowEngine uses wide characters, so
	 *	you should use `std::wstring` instead of `std::string`.
	 *	\param string Standard string whose value will be assigned to a new one.
	 */
	String(const std::wstring& string) noexcept;

	/**
	 *	\brief Create a string by moving the passed one
	 *	
	 *	Creates a new string and moves into it the value of the passed one.
	 *	\param string Standard string whose value will be moved into a new string.
	 */
	String(std::wstring&& string) noexcept;

	/**
	 *	\brief Create a copy of the string
	 *
	 *	Creates a copy of itself.
	 *	\return A copy of the string.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief Calculate a hash code of the string
	 *
	 *	Calculates a hash code of the string using formula:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot (ch[i]))
	 *	\f]
	 *	\f$ n \f$ is the array size, \f$ ch[i] \f$ is the code of i-th character of the string.
	 *	\return A hash code of the string.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief Convert the SnowEngine string to the standard one
	 *
	 *	Converts `snow::String` to `std::wstring`.
	 *	\return The standard string with the value of the SnowEngine string.
	 */
	std::wstring to_std_string() const noexcept;

	/**
	 *	\brief The length of the string
	 *
	 *	Allows to get number of characters in the string.
	 *	\return The length of the string.
	 */
	int size() const noexcept;

	/**
	 *	\brief Whether the string is empty
	 *
	 *	Checks whether the string has at least one character.
	 *	\return `true` if the string has no characters, `false` otherwise.
	 */
	bool is_empty() const noexcept;

	/**
	 *	\brief Clear the string
	 *
	 *	Removes all of the characters in the string.
	 */
	void clear() noexcept;

	/**
	 *	\brief Free the memory that is not used by the string
	 *	
	 *	Frees unused memory and decreases memory usage.
	 */
	void shrink_to_fit();

	/**
	 *	\brief Add the character in the end of the string
	 *
	 *	Push the passed character in the end of the string.
	 *	\param ch The character that will be added.
	 *	\return `true` if the character was successfully added, `false` otherwise.
	 */
	bool add(wchar_t ch);

	/**
	 *	\brief Add the passed string in the end of this one
	 *
	 *	Push the passed string in the end of this one.
	 *	\param string The string that will be added.
	 *	\return The number of characters that were successfully added.
	 */
	int add(const String& string);

	/**
	 *	\brief Add the character in the specified position of the string
	 *
	 *	Push the passed character in the specified position of the string.
	 *	\param ch The character that will be added.
	 *	\param pos Index that the inserted character will have.
	 *	\return `true` if the character was successfully added, `false` otherwise.
	 */
	bool add(wchar_t ch, int pos);

	/**
	 *	\brief Add the passed string in the specified position of this one
	 *
	 *	Push the passed string in the specified position of this one.
	 *	\param string The string that will be added.
	 *	\param pos Index that the first character of the inserted string will have.
	 *	\return The number of characters that were successfully added.
	 */
	int add(const String& string, int pos);

	/**
	 *	\brief Remove the character
	 *	
	 *	Removes the specified character from the string.
	 *	\param pos Index of the character that will be removed.
	 *	\return `true` if the character was successfully removed, `false` otherwise.
	 */
	bool remove(int pos);

	/**
	 *	\brief Remove the characters
	 *
	 *	Removes the specified substring. If the passed range is invalid (e. g. if it's out of the
	 *	string range), no character will be removed.
	 *	\param from Index of the first character to remove.
	 *	\param to Index of the first character after removed substring. This character won't be
	 *	removed.
	 *	\return The number of characters that were successfully removed.
	 */
	int remove(int from, int to);

	/**
	 *	\brief Convert the string to an integer
	 *	
	 *	Converts the string to an integer type.
	 *	\return A resultunt integer.
	 *	\throw std::invalid_argument The string is not an integer.
	 */
	int to_int() const;

	/**
	 *	\brief Convert the string to an integer as binary number
	 *	
	 *	Converts the string to an integer type. The string is supposed to be a binary
	 *	representation of a number.
	 *	\return A resultant integer.
	 *	\throw std::invalid_argument The string is not a binary integer.
	 */
	int to_int_bin() const;

	/**
	 *	\brief Convert the string to an integer as octal number
	 *	
	 *	Converts the string to an integer type. The string is supposed to be an octal
	 *	representation of a number.
	 *	\return A resultant integer.
	 *	\throw std::invalid_argument The string is not an octal integer.
	 */
	int to_int_oct() const;

	/**
	 *	\brief Convert the string to an integer as hexadecimal number
	 *	
	 *	Converts the string to an integer type. The string is supposed to be a
	 *	hexadecimal representation of a number.
	 *	\return A resultant integer.
	 *	\throw std::invalid_argument The string is not a hexadecimal integer.
	 */
	int to_int_hex() const;

	/**
	 *	\brief Convert the string to a float
	 *
	 *	Converts the string to a float type. The string is not allowed to be ax exponential
	 *	notation of a number.
	 *	\return A resultant float.
	 *	\throw std::invalid_argument The string is not a float.
	 */
	float to_float() const;

	/**
	 *	\brief Convert the string to a boolean
	 *
	 *	Converts the string to a boolean type. The convertion takes place according to the
	 *	following algorithm:
	 *	1. If the string is empty, `false` is returned.
	 *	1. If the string has value that is contained in the table below the list, the method
	 *	returns the boolean according to the table.
	 *	1. If the string can be converted to a float, `to_float()` method is called. Its result is
	 *	returned as boolean.
	 *	1. `true` is returned otherwise.
	 *
	 *	true values | false values
	 *	------------|-------------
	 *	`true`      | `false`
	 *	`t`         | `f`
	 *	`1`         | `0`
	 *
	 *	\return A resultant boolean.
	 */
	bool to_bool() const;

	/**
	 *	\brief Find the first occurrence of the character in the string
	 *	
	 *	Checks everty character of the string and returns an index of the first match.
	 *	\param ch The desired character.
	 *	\return The index of the first match, or a negative value if no match is found.
	 */
	int find_first(wchar_t ch) const;

	/**
	 *	\brief Find the last occurrence of the character in the string
	 *	
	 *	Checks everty character of the string and returns an index of the last match.
	 *	\param ch The desired character.
	 *	\return The index of the last match, or a negative value if no match is found.
	 */
	int find_last(wchar_t ch) const;
	
	/**
	 *	\brief Find the first occurrence of the passed string
	 *	
	 *	Checks the string and returns an index of the first substring that is equal to the passed string.
	 *	\param string The desired substring.
	 *	\return The index of the first match, or a negative value if no match is found.
	 */
	int find_first(const String& string) const;

	/**
	 *	\brief Find the last occurrence of the passed string
	 *	
	 *	Checks the string and returns an index of the last substring that is equal to the passed string.
	 *	\param string The desired substring.
	 *	\return The index of the last match, or a negative value if no match is found.
	 */
	int find_last(const String& string) const;

	/**
	 *	\brief Whether the string contains the passed character
	 *
	 *	Scans the string and checks whether is contains the passed character.
	 *	\param ch The desired character.
	 *	\return `true` is the character is found, `false` otherwise.
	 */
	bool contains(wchar_t ch) const;

	/**
	 *	\brief Whether the string contains the passed substring
	 *
	 *	Scans the string and checks whether is contains the passed substring.
	 *	\param string The desired substring.
	 *	\return `true` is the substring is found, `false` otherwise.
	 */
	bool contains(const String& string) const;

	/**
	 *	\brief Number of occurrences of the character in the string
	 *
	 *	Counts occurrences of the character in the string and returns their number.
	 *	\param ch The desired character.
	 *	\return A number of occurrences.
	 */
	int count(wchar_t ch) const;

	/**
	 *	\brief Number of occurrences of the substring
	 *
	 *	Counts occurrences of the substring in the string and returns their number.
	 *	\code
	 *		String str = L"abbbcdbcd";
	 *
	 *		str.count(L"ab"_s); // == 1
	 *		str.count(L"cd"_s); // == 2
	 *		str.count(L"bb"_s); // == 2
	 *	\endcode
	 *	\param ch The desired character.
	 *	\return A number of occurrences.
	 */
	int count(const String& string) const;
	
	/**
	 *	\brief Get the substring of the string
	 *
	 *	Allows to get the substring.
	 *	\code
	 *		String str = L"012345";
	 *
	 *		str.substring(1, 4); // == L"123"_s
	 *		str.substring(4, 5); // == L"4"_s
	 *		str.substring(4, 6); // == L"45"_s
	 *
	 *		// Error (std::invalid_argument):
	 *	//	str.substring(-1, 4);
	 *	//	str.substring(4, 6);
	 *	//	str.substring(4, 2);
	 *	\endcode
	 *	\param from The index of the first character of the substring.
	 *	\param to The index of the first character after the substring (the last character of the
	 *	substring has index `to - 1`).
	 *	\return The desired substring.
	 *	\throw std::invalid_argument The passed range is invalid (e. g. `from > to`).
	 */
	String substring(int from, int to) const;

	/**
	 *	\brief Get the string with inverted character order
	 *
	 *	Creates a copy of the string and inverts its character order. The first character becomes
	 *	the last, and the last becomes the first. The original string is not changed.
	 *	\code
	 *		String str = L"12345";
	 *
	 *		str.reverse(); // == L"54321"_s;
	 *	\endcode
	 *	\return The reversed string.
	 */
	String reverse() const;

	/**
	 *	\breif Get the lowercase string
	 *
	 *	Creates a copy of the string and converts it to lowercase. The original string is not
	 *	changed.
	 *	\return The lowercase string.
	 */
	String to_lower() const;

	/**
	 *	\breif Get the uppercase string
	 *
	 *	Creates a copy of the string and converts it to uppercase. The original string is not
	 *	changed.
	 *	\return The uppercase string.
	 */
	String to_upper() const;

	/**
	 *	\brief The standard iterator to the beginning of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the beginning of the internal `std::wstring`.
	 */
	std::wstring::iterator begin() noexcept;

	/**
	 *	\brief The standard iterator to the end of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the end of the internal `std::wstring`.
	 */
	std::wstring::iterator end() noexcept;

	/**
	 *	\brief The standard iterator to the beginning of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the beginning of the internal `std::wstring`.
	 */
	std::wstring::const_iterator begin() const noexcept;

	/**
	 *	\brief The standard iterator to the end of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the end of the internal `std::wstring`.
	 */
	std::wstring::const_iterator end() const noexcept;

	/**
	 *	\brief The standard iterator to the beginning of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the beginning of the internal `std::wstring`.
	 */
	std::wstring::const_iterator cbegin() const noexcept;

	/**
	 *	\brief The standard iterator to the end of the internal `std::wstring`
	 *
	 *	It's not recommended to use this method directly. It is needed for the for each loop to be
	 *	possible.
	 *	\return The standard iterator to the end of the internal `std::wstring`.
	 */
	std::wstring::const_iterator cend() const noexcept;

	/**
	 *	\brief Assigning the character to the string
	 *
	 *	Clears the string and assigns to it the passed character.
	 *	\param ch The character to assign.
	 *	\return The reference to itself.
	 */
	String& operator=(wchar_t ch) noexcept;

	/**
	 *	\brief Assigning to the string the row string
	 *
	 *	Clears the string and assigns to it the passed row string.
	 *	\param ch The row string to assign.
	 *	\return The reference to itself.
	 */
	String& operator=(const wchar_t* ch) noexcept;

	/**
	 *	\brief Assigning to the string the standard `std::wstring`
	 *
	 *	Clears the string and assigns to it the passed standart string.
	 *	\param ch The standard `std::wstring` to assign.
	 *	\return The reference to itself.
	 */
	String& operator=(const std::wstring& string) noexcept;

	/**
	 *	\brief Assigning to the string the standard `std::wstring`
	 *
	 *	Clears the string and assigns to it the passed standart string by moving it.
	 *	\param ch The standard `std::wstring` whose value will be moved.
	 *	\return The reference to itself.
	 */
	String& operator=(std::wstring&& string) noexcept;

	/**
	 *	\brief Assigning to the string the another one
	 *
	 *	Clears the string and assigns to it the passed string.
	 *	\param ch The string to assign.
	 *	\return The reference to itself.
	 */
	String& operator=(const String& string) noexcept;

	/**
	 *	\brief Assigning to the string the another one
	 *
	 *	Clears the string and assigns to it the passed string by moving it.
	 *	\param ch The string whose value will be moved.
	 *	\return The reference to itself.
	 */
	String& operator=(String&& string) noexcept;

	/**
	 *	\brief Concatenate the string and the character
	 *
	 *	Creates a new string by adding the passed character to the end of the string.
	 *	\param ch The character that will be added.
	 *	\return The resultant string.
	 */
	String operator+(wchar_t ch) const;

	/**
	 *	\brief Concatenate two strings
	 *
	 *	Creates a new string by adding to the end of the string the passed row string.
	 *	\param ch The row string that will be added.
	 *	\return The resultant string.
	 */
	String operator+(const wchar_t* ch) const;

	/**
	 *	\brief Concatenate two strings
	 *
	 *	Creates a new string by adding to the end of the string the passed standard `std::wstring`.
	 *	\param string The standard string that will be added.
	 *	\return The resultant string.
	 */
	String operator+(const std::wstring& string) const;

	/**
	 *	\brief Concatenate two strings
	 *
	 *	Creates a new string by adding to the end of the string the passed string.
	 *	\param string The string that will be added.
	 *	\return The resultant string.
	 */
	String operator+(const String& string) const;

	/**
	 *	\brief Concatenate the passed character and the string
	 *
	 *	Creates a new string by adding the passed string after the passed character.
	 *	\param ch The character that will be in the beginning of the resultant string.
	 *	\param string The string that will be in the end of the resultant string.
	 *	\return The resultant string.
	 */
	friend String operator+(wchar_t ch, const String& string);

	/**
	 *	\brief Concatenate two strings
	 *
	 *	Creates a new string by concatenating two passed strings.
	 *	\param ch The row string that will be in the beginning of the resultant string.
	 *	\param string The string that will be in the end of the resultant string.
	 *	\return The resultant string.
	 */
	friend String operator+(const wchar_t* ch, const String& string);

	/**
	 *	\brief Concatenate two strings
	 *
	 *	Creates a new string by concatenating two passed strings.
	 *	\param ch The standard `std::wstring` that will be in the beginning of the resultant string.
	 *	\param string The string that will be in the end of the resultant string.
	 *	\return The resultant string.
	 */
	friend String operator+(const std::wstring& std_str, const String& string);

	String operator*(int value) const;

	friend String operator*(int value, const String& string);
	
	/**
	 *	\brief Add the character to the end of the string
	 *
	 *	Adds the passed character to the end of the string (`add()` method does the same):
	 *	\code
	 *		String str;
	 *		wchar_t c;
	 *		// ...
	 *		str += c;   // These two strings
	 *		str.add(c); //   do the same
	 *	\endcode
	 *	\param ch The character that will be added.
	 *	\return The reference to itself.
	 */
	String& operator+=(wchar_t ch);
	
	/**
	 *	\brief Add the row string to the end of the string
	 *
	 *	Adds the passed row string to the end of the string (`add()` method does the same):
	 *	\code
	 *		String str;
	 *		const wchar_t* c;
	 *		// ...
	 *		str += c;   // These two strings
	 *		str.add(c); //   do the same
	 *	\endcode
	 *	\param ch The row string that will be added.
	 *	\return The reference to itself.
	 */
	String& operator+=(const wchar_t* ch);
	
	/**
	 *	\brief Add the standard `std::wstring` to the end of the string
	 *
	 *	Adds the passed standard `std:wstring` to the end of the string (`add()` method does the
	 *	same):
	 *	\code
	 *		String str;
	 *		std::wstring std_str;
	 *		// ...
	 *		str += std_str;   // These two strings
	 *		str.add(std_str); //   do the same
	 *	\endcode
	 *	\param string The standard `std::wstring` that will be added.
	 *	\return The reference to itself.
	 */
	String& operator+=(const std::wstring& string);
	
	/**
	 *	\brief Add to the end of the string the another one
	 *
	 *	Adds the passed string to the end of the string (`add()` method does the string.
	 *	\code
	 *		String str1;
	 *		String str2;
	 *		// ...
	 *		str1 += str2;   // These two strings
	 *		str1.add(str2); //   do the same
	 *	\endcode
	 *	\param string The string that will be added.
	 *	\return The reference to itself.
	 */
	String& operator+=(const String& string);

	String& operator*=(int value);

	/**
	 *	\brief Compare the string and the character
	 *
	 *	The string and the character are equal if the string only contains this character.
	 *	\param ch The character to compare.
	 *	\return `true` if the string is equal to the character, `false` otherwise.
	 */
	bool operator==(wchar_t ch) const noexcept;

	/**
	 *	\brief Compare two strings
	 *
	 *	Two strings are equal if they contain the same characters in the same order.
	 *	\param ch The row string to compare.
	 *	\return `true` if the strings are equal, `false` otherwise.
	 */
	bool operator==(const wchar_t* ch) const noexcept;

	/**
	 *	\brief Compare two strings
	 *
	 *	Two strings are equal if they contain the same characters in the same order.
	 *	\param string The standard `std::wstring` to compare.
	 *	\return `true` if the strings are equal, `false` otherwise.
	 */
	bool operator==(const std::wstring& string) const noexcept;

	/**
	 *	\brief Compare two strings
	 *
	 *	Two strings are equal if they contain the same characters in the same order.
	 *	\param string The string to compare.
	 *	\return `true` if the strings are equal, `false` otherwise.
	 */
	bool operator==(const String& string) const noexcept;

	/**
	 *	\brief Compare the string and the character
	 *
	 *	The string and the character are equal if the string only contains this character.
	 *	\param ch The character to compare.
	 *	\return `true` if the string is not equal to the character, `false` otherwise.
	 */
	bool operator!=(wchar_t ch) const noexcept;

	/**
	 *	\brief Compare two strings
	 *
	 *	Two strings are equal if they contain the same characters in the same order.
	 *	\param ch The row string to compare.
	 *	\return `true` if the strings are not equal, `false` otherwise.
	 */
	bool operator!=(const wchar_t* ch) const noexcept;

	/**
	 *	\brief Compare two strings
	 *
	 *	Two strings are equal if they contain the same characters in the same order.
	 *	\param string The standard `std::wstring` to compare.
	 *	\return `true` if the strings are not equal, `false` otherwise.
	 */
	bool operator!=(const std::wstring& string) const noexcept;

	/**
	 *	\brief Compare two strings
	 *
	 *	Two strings are equal if they contain the same characters in the same order.
	 *	\param string The string to compare.
	 *	\return `true` if the strings are not equal, `false` otherwise.
	 */
	bool operator!=(const String& string) const noexcept;

	/**
	 *	\brief Get the specified character of the string
	 *
	 *	Allows to get access to the character with the passed index. Returns the reference so you
	 *	are able to modify the character.
	 *	\param index The index of the desired character.
	 *	\return The reference to the desired character.
	 *	\throw std::out_of_range The index is out of the string bounds.
	 */ 
	wchar_t& operator[](int index);

	/**
	 *	\brief Get the specified character of the string
	 *
	 *	Allows to get access to the character with the passed index. Returns the constant
	 *	reference so you cannot modify the character.
	 *	\param index The index of the desired character.
	 *	\return The constant reference to the desired character.
	 *	\throw std::out_of_range The index is out of the string bounds.
	 */ 
	const wchar_t& operator[](int index) const;

	/**
	 *	\brief Push the string to the output stream
	 *
	 *	This operator is used to pust the string to the output stream. Note that SnowEngine uses
	 *	wide characters so you should use wide streams (e. g. `std::wcout` instead of `std::cout`;
	 *	`std::wofstream` instead of `std::ofstream` etc.)
	 *	\param stream The wide output stream, e. g. `std::wcout`.
	 *	\param string The string.
	 *	\return The passed output stream.
	 */
	friend std::wostream& operator<<(std::wostream& stream, const String& string);

	/**
	 *	\brief Lexicographical comparison of two strings
	 *
	 *	This method uses `std::wstring::compare()` to compare two strings.
	 *	\param first The first string to compare.
	 *	\param second The second string to compare.
	 *	\return A negative value, if the first string appears before the second one in
	 *	lexicographical order; a positive value, if the first string appears after the second one;
	 *	zero, if the strings are equal.
	 */
	static int compare(const String& first, const String& second);

	/**
	 *	\brief Format the string by inserting into it the passed values
	 *
	 *	The principle of this method is similar to the `printf()`. The method searches character
	 *	sequences starting with `%` and replaces it with the passed values according to the table
	 *	below.
	 *
	 *	Sequence     | Is replaced with
	 *	-------------|------------------
	 *	`%%`         | `%`.
	 *	`%b`         | The integer in binary representation.
	 *	`%c`         | The character (`wchar_t` type).
	 *	`%d` or `%i` | The integer in decimal representation.
	 *	`%f`         | The float number.
	 *	`%h`         | The integer in hexadecimal representation.
	 *	`%o`         | The integer in octal representation.
	 *	`%s`         | The string (`snow::String` type).
	 *
	 *	After percent sign there may be a number. It defines how many positions will be allocated
	 *	for the value. In this case the value will be right-aligned. Empty positions will be
	 *	filled with space characters (or zeros, if the number after percent sign starts with
	 *	zero). Note that this doesn't work for `%%`, `%c` and `%s`. If the value is large enough,
	 *	it won't fit in the specified number of positions.
	 *
	 *	Here are some examples:
	 *	\code
	 *		String str1 =
	 *			String::format(L"Hello, %s! I want to tell you, %s."_s, L"world", L"hi");
	 *		str1 == L"Hello, world! I want to tell you, hi."_s;
	 *
	 *		String str2 =
	 *			String::format(L"Player name: %s. Health: %f/%d. Score: %04d"_s, L"player", 56.3f, 100, 19);
	 *		str2 == L"Player name: player. Health: 53.6/100. Score: 0019";
	 *
	 *		String str3 =
	 *			String::format(L"Dec: %4d\nBin: %4b\nOct: %4o\nHex: %4h"_s, 10, 10, 10, 10);
	 *		// str3:
	 *		//	Dec: 0010
	 *		//	Bin: 1010
	 *		//	Oct: 0012
	 *		//	Hex: 000A
	 *
	 *		String str4 =
	 *			String::format(L"Health: %d%%"_s, 75);
	 *		str4 == L"Health: 75%"_s;
	 *	\endcode
	 *	\param string The original string.
	 *	\param ... The values that will be inserted in the string.
	 *	\return The formatted string.
	 */
	static String format(String string, ...);

private:
	std::wstring string_;
};

String operator""_s(const wchar_t* string, std::size_t length) noexcept;

}

using snow::operator""_s;

