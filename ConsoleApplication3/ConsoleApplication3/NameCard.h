#pragma once
#include "pch.h"

#include <string>
#include <vector>



class NameCard
{
public:
	enum class Position : int
	{
		//���, �븮, ����, ����, ����
		Employee, // ���
		DeputyHead, //�븮
		HeadOfDepartment, // ����
		SectionChief, // ����
		Commander, // ����


		None, // ERROR
	};

	NameCard() = delete;
	NameCard(std::string name, std::vector<std::string> tels, std::vector<std::string> addresss, NameCard::Position position);
	~NameCard();

	void Print();

private:
	std::string name;

	std::string **tel;
	unsigned int maxTel;

	std::string **address;
	unsigned int maxAddress;

	Position position;
};