#include "pch.h"
#include "NameCard.h"
#include "vld.h"

#include <iostream>

NameCard::NameCard(std::string name, std::vector<std::string> tels, std::vector<std::string> addresss, NameCard::Position position)
	: name(name), position(position)
{
	int index;

	// 전화번호 복사
	maxTel = tels.size();
	tel = new std::string*[maxTel];

	index = 0;
	for (auto s : tels)
		tel[index++] = new std::string(s);


	// 주소 복사
	maxAddress = addresss.size();
	address = new std::string*[maxAddress];

	index = 0;
	for (auto s : addresss)
		address[index++] = new std::string(s);
}

NameCard::~NameCard()
{
	int i;
	for (i = 0; i < maxAddress; ++i) delete address[i];
	delete[] address;

	for (i = 0; i < maxTel; ++i) delete tel[i];
	delete[] tel;
}

void NameCard::Print()
{ // 이름, 직급 전화번호 주소
	int index;

	std::cout << "이름 : " << name << "\n";
	std::cout << "직급 : ";
	switch (position)
	{
	case Position::Employee:		std::cout << "사원\n"; break;
	case Position::DeputyHead:		std::cout << "대리\n"; break;
	case Position::HeadOfDepartment:std::cout << "부장\n"; break;
	case Position::SectionChief:	std::cout << "과장\n"; break;
	case Position::Commander:		std::cout << "차장\n"; break;

	default:						std::cout << "인턴\n"; break;
	}

	for (index = 0; index < maxTel; ++index)
		std::cout << "전화번호 : " << *tel[index] << "\n";

	for (index = 0; index < maxAddress; ++index)
		std::cout << " 주 소 : " << *address[index] << "\n";
}
