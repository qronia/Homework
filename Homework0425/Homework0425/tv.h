#pragma once

#include <map>
#include <list>
#include "typedef.h"

/*
	���Ǽ����� TV�� ������� ��� Ŭ���� ������ �ϱ� ���� ���� Ŭ�����Դϴ�.

	������ �����־�߸� ä�ο� ���� ������ �� �� ������, 
	������ �����־�߸� ��û�� ���õ� ������ ���� ����, ä�� ���� ���� �����մϴ�.

	Ư�̻������δ� ����Ʈ ��Ʈ�ѷ� Ŭ����(RemoteController)�� �����ȴٴ� ���ε�,
	����Ʈ ��Ʈ�ѷ��� TV�� ����Ű�� �־���ϹǷ� TV�� ���� �����Ǹ� �޸� ���� ������ �߻��� ���ɼ��� ���ܹ����ϴ�.
	�׿� �ش��ϴ� �׽�Ʈ �ڵ带 �غ���ѵ帮�� �ʾ�����, 
	���� TV �Ҹ��ڿ��� ��� ��Ʈ�ѷ��� �� ResetTarget�� ȣ���ϴ� ������ ������ �����ϰ� �ֽ��ϴ�.
*/


class Channel;
class RemoteController;
class TV
{
	friend RemoteController;

public:
	enum Setting : int {
		ChannelMin = 1,
		ChannelMax = 99,

		VolumeMax = 10,
		VolumeMin = 0,
	};

public:
	TV();
	~TV();

	// ä�� ����. ������ �����־�߸� ����
	bool AddChannel(uint channelNumber, Channel* channel);
	bool RemoveChannel(uint channelNumber);


	// ä�� ���� ���� (���� ON)
	uint GetChannel();
	bool ChangeChannel(uint channelNumber);
	void ChannelUp();
	void ChannelDown();

	// ���� ���� ���� (���� ON)
	uint GetVolume();
	bool ChangeVolume(uint currentVolume) = delete;
	bool VolumeUp();
	bool VolumeDown();

	// ���� ���� ����
	bool IsPowered();
	bool PowerOn();
	bool PowerOff();
	void TogglePower();

	// �̿�!
	void View();
	void operator()();

	
	// friend class�� RemoteController�� �����ϱ� ���� ���� �޼����μ�,
	// �޸� ���� ������ �����ϰ��� ��������ϴ�.
private:
	void RegisterRemoteController(RemoteController* target);
	void DeRegisterRemoteController(RemoteController* target);
	

private:
	std::map<uint, Channel*> channels;					// ��ϵ� ä�ε�
	std::list<RemoteController*> connectedController;	// ����� ������

	bool power;											// ���� 
	bool channelExist;									// ���� ����Ű�� �ִ� ä���� �����ϴ°�?
	uint currentChannel;								// ���� ����Ű�� �ִ� ä���� ��ȣ
	uint currentVolume;									// ���� ���� ����
};