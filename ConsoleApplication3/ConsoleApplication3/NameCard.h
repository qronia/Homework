#pragma once
#include "pch.h"

#include <string>
#include <vector>



class NameCard
{
public:
	enum class Position : int
	{
		//사원, 대리, 부장, 과장, 차장
		Employee, // 사원
		DeputyHead, //대리
		HeadOfDepartment, // 부장
		SectionChief, // 과장
		Commander, // 차장


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