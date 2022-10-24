#pragma once
#include"Task1.h"
#include"Task2.h"

#include<vector>
#include<fstream>

class PhoneBook
{
private:
	std::vector<std::pair<Person, PhoneNumber>> record;

public:
	PhoneBook(std::ifstream& fstr);

	void SortByName();
	void SortByPhone();
	std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname);
	void ChangePhoneNumber(const Person& person, const PhoneNumber& newPhNum);

	friend std::ostream& operator<< (std::ostream& out, PhoneBook phBook);
};

class Less
{
private:
	bool sortByPhone;

public:
	Less(bool flag = false) : sortByPhone(flag)
	{};

	bool operator() (const std::pair<Person, PhoneNumber>& left, const std::pair<Person, PhoneNumber>& right)
	{
		if (left.first == right.first || sortByPhone)
			return left.second < right.second;
		else return left.first < right.first;
	}
};