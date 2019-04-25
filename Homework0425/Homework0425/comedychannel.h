#pragma once

#include "channel.h"
#include <iostream>

class ChannelFactory;
class ComedyChannel : public Channel
{
	friend ChannelFactory;

private:
	ComedyChannel() = default;

public:
	virtual ~ComedyChannel() {}
	virtual void Show()
	{
		std::cout << "�ڸ޵� ä��: �����������������K" << std::endl;
	}
};