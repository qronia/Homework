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
	enum Setting : int 
	{
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
		return brand;     //brand�� �ּҰ��� ������ �����Ƿ� �װ��� �����ؼ� ���߸�
		//brand���� �˼������Ƿ� *get_brand
	}
	void information()
	{
		cout << "=========TV ����=========" << endl;
		cout << "Brand  :  " << brand << endl;
		cout << "Channel  :  " << channel << endl;
	}
	void change_channel(int e_channel)
	{
		channel = e_channel;
	}

	
	// friend class�� RemoteController�� �����ϱ� ���� ���� �޼����μ�,
	// �޸� ���� ������ �����ϰ��� ��������ϴ�.
private:
	void RegisterRemoteController(RemoteController* target);
	void DeRegisterRemoteController(RemoteController* target);
	

private:
	std::map<uint, Channel*> channels;					// ��ϵ� ä�ε�
	std::list<RemoteController*> connectedController;	// ����� ������

	int channel;                                        //ä��
	char brand[20];                                     //�귣������
	bool power;											// ���� 
	bool channelExist;									// ���� ����Ű�� �ִ� ä���� �����ϴ°�?
	uint currentChannel;								// ���� ����Ű�� �ִ� ä���� ��ȣ
	uint currentVolume;									// ���� ���� ����
};