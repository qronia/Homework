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
		std::cout << "코메디 채널: 하하하하하하하하핳" << std::endl;
	}
};