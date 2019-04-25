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
		std::cout << "坪五巨 辰確: 馬馬馬馬馬馬馬馬�K" << std::endl;
	}
};