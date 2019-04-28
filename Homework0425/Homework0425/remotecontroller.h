#pragma once

#include "typedef.h"
#include "tv.h"
#include <string>

/*
	����Ʈ ��Ʈ�ѷ��� ���� TV�� �����ϰ� �� TV�� �����ϴ� �� ����� ���� �ʽ��ϴ�.

	�ٸ� TV�� ����Ʈ ��Ʈ�ѷ��� ���ŵǱ� ���� ���ŵǸ� �޸� ���� ������ �߻��� ������ �ִµ�,
	�̴� TV �Ҹ��ڿ� �� Ŭ������ �����ڸ� �����Ͻø� ��� �ذ��ߴ��� �ѹ��� ���̽� �̴ϴ�.

	TV�� ����� ����Ʈ ��Ʈ�ѷ����� ��͵��� �ִ��� �˼� �־���ϰ�,
	�� ����Ʈ ��Ʈ�ѷ��� ����� �� �װ��� ����Ʈ�� �߰��մϴ�.
*/


class RemoteController
{
public:
	RemoteController();
	RemoteController(TV* targetTV);
	~RemoteController();

	// ä�� ����
	bool ChangeChannel(uint channelNumber);
	void ChannelUp();
	void ChannelDown();


	// ���� ����
	bool VolumeUp();
	bool VolumeDown();


	// ���� ��ư
	void TogglePower();


	// TV ����Ű��
	void ResetTarget();
	void SetTarget(TV* targetTV);

public:
	void init(int e_channel, char *e_brand)
	{
		channel = e_channel;
		strcpy(brand, e_brand);
	}
	int get_channel()
	{
		return channel;
	}
	char *get_brand()
	{
		return brand;
	}
	//==== = > �����ܿ� �Էµ� ä���� TV ä�� �������� �����ܿ� ����
	void set_channel(int e_channel) 
	{
	channel = e_channel;
	}

private:
	TV* targetTV;
	int channel;
	char brand[20];
};