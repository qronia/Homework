#pragma once

#include "channel.h"
#include <iostream>

class ChannelFactory;
class ShoppingChannel : public Channel
{
	friend ChannelFactory;

private:
	ShoppingChannel() = default;

public:
	virtual ~ShoppingChannel() = default;
	virtual void Show()
	{
		std::cout << "���θ� ä��: �ۡ۸��� �����Դϴ�." << std::endl;
	}
};