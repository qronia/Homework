#pragma once


// 다형성을 위한 추상 클래스.
class Channel
{
public:
	virtual ~Channel() {}
	virtual void Show() = 0;
};