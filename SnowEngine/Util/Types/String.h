    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.h                    //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

namespace snow
{

class String : public Object
{
public:
	String() noexcept;
	String(const String& string) noexcept;
	String(String&& string) noexcept;
	String(wchar_t ch) noexcept;
	String(const wchar_t* string) noexcept;
	String(const std::wstring& string) noexcept;
	String(std::wstring&& string) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;
	std::wstring to_std_string() const noexcept;

	int size() const noexcept;
	bool is_empty() const noexcept;
	void clear() noexcept;
	void shrink_to_fit();

	bool add(wchar_t ch);
	int add(const String& string);
	bool add(wchar_t ch, int pos);
	int add(const String& string, int pos);

	bool remove(int pos);
	int remove(int from, int to);

	int to_int() const;
	int to_int_bin() const;
	int to_int_oct() const;
	int to_int_hex() const;
	float to_float() const;
	bool to_bool() const;

	int find_first(wchar_t ch) const;
	int find_last(wchar_t ch) const;
	int find_first(const String& string) const;
	int find_last(const String& string) const;

	bool contains(wchar_t ch) const;
	bool contains(const String& string) const;
	int count(wchar_t ch) const;
	int count(const String& string) const;
	
	String substring(int from, int to) const;
	String reverse() const;
	String to_lower() const;
	String to_upper() const;

	std::wstring::iterator begin() noexcept;
	std::wstring::iterator end() noexcept;
	std::wstring::const_iterator begin() const noexcept;
	std::wstring::const_iterator end() const noexcept;
	std::wstring::const_iterator cbegin() const noexcept;
	std::wstring::const_iterator cend() const noexcept;

	String& operator=(wchar_t ch) noexcept;
	String& operator=(const wchar_t* ch) noexcept;
	String& operator=(const std::wstring& string) noexcept;
	String& operator=(std::wstring&& string) noexcept;
	String& operator=(const String& string) noexcept;
	String& operator=(String&& string) noexcept;

	String operator+(wchar_t ch) const;
	String operator+(const wchar_t* ch) const;
	String operator+(const std::wstring& string) const;
	String operator+(const String& string) const;
	friend String operator+(wchar_t ch, const String& string);
	friend String operator+(const wchar_t* ch, const String& string);
	friend String operator+(const std::wstring& std_str, const String& string);
	
	String& operator+=(wchar_t ch);
	String& operator+=(const wchar_t* ch);
	String& operator+=(const std::wstring& string);
	String& operator+=(const String& string);

	bool operator==(wchar_t ch) noexcept;
	bool operator==(const wchar_t* ch) noexcept;
	bool operator==(const std::wstring& string) noexcept;
	bool operator==(const String& string) noexcept;
	bool operator!=(wchar_t ch) noexcept;
	bool operator!=(const wchar_t* ch) noexcept;
	bool operator!=(const std::wstring& string) noexcept;
	bool operator!=(const String& string) noexcept;

	wchar_t& operator[](int index);
	const wchar_t& operator[](int index) const;

	friend std::wostream& operator<<(std::wostream& stream, const String& string);

	static int compare(const String& first, const String& second);
	static String format(String string, ...);

private:
	std::unique_ptr<std::wstring> string_;
};

String operator""_s(const wchar_t* string, std::size_t length) noexcept;

}

using snow::operator""_s;

