#pragma once

#include "typedef.h"
#include "tv.h"

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

private:
	TV* targetTV;
};