#pragma once

#include "channel.h"
#include <iostream>

class ChannelFactory;
class SportChannel : public Channel
{
	friend ChannelFactory;

private:
	SportChannel() = default;

public:
	virtual ~SportChannel() = default;
	virtual void Show()
	{
		std::cout << "스포츠 채널: 으오오우우우아아아앙---" << std::endl;
	}
};