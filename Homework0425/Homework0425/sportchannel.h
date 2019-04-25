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
		std::cout << "������ ä��: ����������ƾƾƾ�---" << std::endl;
	}
};