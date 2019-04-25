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
		std::cout << "¼îÇÎ¸ô Ã¤³Î: ¡Û¡Û¸ôÀÇ ±¤°íÀÔ´Ï´Ù." << std::endl;
	}
};