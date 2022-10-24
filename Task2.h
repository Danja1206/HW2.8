#pragma once
#include<iostream>
#include<optional>

class PhoneNumber
{
private:
	uint16_t countryCode, cityNode;
	std::string number;
	std::optional<uint16_t> extension;

public:
	PhoneNumber() = default;
	PhoneNumber(uint16_t couC, uint16_t citC, const std::string& num, const std::optional<uint16_t>& ext) : countryCode(couC), cityNode(citC), number(num), extension(ext)
	{};

	friend bool operator< (const PhoneNumber& phNumL, const PhoneNumber& phNumR);
	friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& phNum);
};