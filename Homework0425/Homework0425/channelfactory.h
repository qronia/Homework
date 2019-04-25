#pragma once

/*
	�� Ŭ������ '���丮 ����'�� �ſ� �����ϰ� ǥ���� ���Դϴ�.
	
	���丮 ������ ����� �Ǵ� Ŭ�������� ����ؼ� ������ִ� Ŭ������ �����ϴ� �����Դϴ�. 
	�����ڰ� �з����Ͱ� �޶� �������� �����ϴµ��� ������ ���� ���ִ� ���� �����̳�,
	���⼭�� �����ڰ� �Ķ���Ͱ� �ٸ��� �ʾ� �����մϴ�.

	�ڼ��� ������ ���丮 ������ �˻��Ͽ��ֽʽÿ�.
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