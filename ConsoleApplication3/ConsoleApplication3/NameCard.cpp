#include "pch.h"
#include "NameCard.h"
#include "vld.h"

#include <iostream>

NameCard::NameCard(std::string name, std::vector<std::string> tels, std::vector<std::string> addresss, NameCard::Position position)
	: name(name), position(position)
{
	int index;

	// ��ȭ��ȣ ����
	maxTel = tels.size();
	tel = new std::string*[maxTel];

	index = 0;
	for (auto s : tels)
		tel[index++] = new std::string(s);


	// �ּ� ����
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
{ // �̸�, ���� ��ȭ��ȣ �ּ�
	int index;

	std::cout << "�̸� : " << name << "\n";
	std::cout << "���� : ";
	switch (position)
	{
	case Position::Employee:		std::cout << "���\n"; break;
	case Position::DeputyHead:		std::cout << "�븮\n"; break;
	case Position::HeadOfDepartment:std::cout << "����\n"; break;
	case Position::SectionChief:	std::cout << "����\n"; break;
	case Position::Commander:		std::cout << "����\n"; break;

	default:						std::cout << "����\n"; break;
	}

	for (index = 0; index < maxTel; ++index)
		std::cout << "��ȭ��ȣ : " << *tel[index] << "\n";

	for (index = 0; index < maxAddress; ++index)
		std::cout << " �� �� : " << *address[index] << "\n";
}
