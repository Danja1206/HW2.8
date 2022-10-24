#include "pch.h"
#include <windows.h>
#include "Task1.h";
#include "Task2.h";
#include "Task3.h";

using namespace std;

ostream& operator<< (ostream& out, const Person& person)
{
	out << person.surname << " " << person.first_name << " " << person.patronymic.value_or("");

	return out;
}

bool operator<(const Person& persL, const Person& persR)
{
	return tie(persL.surname, persL.first_name, persL.patronymic) < tie(persR.surname, persR.first_name, persR.patronymic);

}

bool operator==(const Person& persL, const Person& persR)
{
	return tie(persL.surname, persL.first_name, persL.patronymic) == tie(persR.surname, persR.first_name, persR.patronymic);

}

ostream& operator<<(ostream& out, const PhoneNumber& phNum)
{
	out << "+" << phNum.countryCode << "(" << phNum.cityNode << ")" << phNum.number;
	if (phNum.extension)
		out << " " << phNum.extension.value();
	return out;
}

bool operator<(const PhoneNumber& phNumL, const PhoneNumber& phNumR)
{
	return tie(phNumL.countryCode, phNumL.cityNode, phNumL.number, phNumL.extension) < tie(phNumR.countryCode, phNumR.cityNode, phNumR.number, phNumR.extension);
}

PhoneBook::PhoneBook(ifstream& fstr)
{
	string surname, first_name;
	optional<string>	patronymic;
	uint16_t countryCode, cityNode;
	string number;
	optional<string> ext;
	optional<uint16_t> extension;

	if (fstr.is_open())
	{
		while (fstr >> surname >> first_name >> patronymic.emplace() >> countryCode >> cityNode >> number >> ext.emplace())
		{
			if (patronymic.has_value())
				if (patronymic.value() == "-")
					patronymic = nullopt;
			Person person(surname, first_name, patronymic);
			if (ext.has_value())
				if (ext.value() == "-")
					extension = nullopt;
				else
					extension.emplace() = stoi(ext.value());

			PhoneNumber phoneNum(countryCode, cityNode, number, extension);

			record.push_back(make_pair(person, phoneNum));
		}
	}
	fstr.close();
}

void PhoneBook::SortByName()
{
	Less less;
	sort(record.begin(), record.end(), less);
}

void PhoneBook::SortByPhone()
{
	Less less(true);
	sort(record.begin(), record.end(), less);
}

std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(const std::string& surname)
{
	PhoneNumber number;
	std::string res = "";
	uint8_t count = 0;
	std::for_each(record.begin(), record.end(),
		[&](const auto& rec)
		{
			if (rec.first.getSurname() == surname)
			{
				number = rec.second;
				count++;
			}
		});
	if (count == 0) res = "not found";
	else if (count > 1) res = "found more than 1";
	return std::make_tuple(res, number);
}

void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& newPhNum)
{
	auto find_rec = std::find_if(record.begin(), record.end(),
		[&person](const auto& rec)
		{
			return rec.first == person;
		});
	if (find_rec != record.end()) find_rec->second = newPhNum;
}

std::ostream& operator<<(std::ostream& out, PhoneBook phBook)
{
	for (const auto& [person, number] : phBook.record)
	{
		out << person << std::setw(5) << number << std::endl;
	}
	return out;
}



TEST(L1Test, testingFunc)
{
	setlocale(0, "rus");
	ifstream file("../Input.txt");
	PhoneBook book(file);
	ASSERT_ANY_THROW(book.SortByPhone();
	book.SortByName(););

	auto print_phone_number = [&book](const std::string& surname) {};

	ASSERT_NO_THROW(auto print_phone_number_check = [&book](const string& surname) {
		auto answer = book.GetPhoneNumber(surname);
		ASSERT_TRUE(get<0>(answer).empty());
		};);

	ASSERT_ANY_THROW(
	print_phone_number("Ильич");
	print_phone_number("Иваныч"););

	ASSERT_ANY_THROW(book.ChangePhoneNumber(Person{ "Котов", "Василий", "Елисеевич" },
		PhoneNumber{ 7, 123, "15344458", 0 });
	book.ChangePhoneNumber(Person{ "Миронова", "Маргарита", "Александровна " },
		PhoneNumber{ 16, 465, "9155448", 13 }););
}