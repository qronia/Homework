#pragma once

#include "channel.h"
#include <iostream>

class ChannelFactory;
class LifeChannel : public Channel
{
	friend ChannelFactory;

private:
	LifeChannel() = default;

public:
	virtual ~LifeChannel() = default;
	virtual void Show()
	{
		std::cout << "������ ä��: �ᱹ �ΰ��� ��� �״´�." << std::endl;
	}
};