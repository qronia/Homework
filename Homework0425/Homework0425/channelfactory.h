#pragma once

/*
	이 클래스는 '팩토리 패턴'을 매우 간단하게 표현한 것입니다.
	
	팩토리 패턴은 대상이 되는 클래스들을 대신해서 만들어주는 클래스를 제공하는 패턴입니다. 
	생성자간 패러미터가 달라도 다형성을 형성하는데에 문제가 없게 해주는 고마운 존재이나,
	여기서는 생성자간 파라미터가 다르지 않아 심플합니다.

	자세한 내용은 팩토리 패턴을 검색하여주십시오.
*/


class Channel;
class ChannelFactory
{
public:
	static Channel* MakeSportChannel();
	static Channel* MakeComedyChannel();
	static Channel* MakeLifeChannel();
	static Channel* MakeShoppingChannel();
};