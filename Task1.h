#pragma once
#include<optional>
#include<iostream>


class Person
{
private:
	std::string surname, first_name;
	std::optional<std::string>	patronymic;

public:
	Person(const std::string& sname, const std::string& fname, const std::optional<std::string>& ptr) : surname(sname), first_name(fname), patronymic(ptr)
	{};

	std::string getSurname() const { return surname; };

	friend std::ostream& operator<< (std::ostream& out, const Person& person);
	friend bool operator< (const Person& persL, const Person& persR);
	friend bool operator== (const Person& persL, const Person& persR);
};