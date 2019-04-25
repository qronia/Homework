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
		std::cout << "라이프 채널: 결국 인간은 모두 죽는다." << std::endl;
	}
};