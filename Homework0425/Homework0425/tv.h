#pragma once

#include <map>
#include <list>
#include "typedef.h"

/*
	현실세계의 TV를 대상으로 삼아 클래스 연습을 하기 위해 만든 클래스입니다.

	전원이 꺼져있어야만 채널에 대한 설정을 할 수 있으며, 
	전원이 켜져있어야만 시청에 관련된 조작인 볼륨 조정, 채널 변경 등이 가능합니다.

	특이사항으로는 리모트 컨트롤러 클래스(RemoteController)와 연동된다는 점인데,
	리모트 컨트롤러는 TV를 가리키고 있어야하므로 TV가 먼저 삭제되면 메모리 참조 오류가 발생할 가능성이 생겨버립니다.
	그에 해당하는 테스트 코드를 준비시켜드리진 않았지만, 
	현재 TV 소멸자에서 대상 컨트롤러에 들어가 ResetTarget을 호출하는 것으로 연결을 해제하고 있습니다.
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

	// 채널 설정. 전원이 꺼져있어야만 동작
	bool AddChannel(uint channelNumber, Channel* channel);
	bool RemoveChannel(uint channelNumber);


	// 채널 조작 관련 (전원 ON)
	uint GetChannel();
	bool ChangeChannel(uint channelNumber);
	void ChannelUp();
	void ChannelDown();

	// 볼륨 조작 관련 (전원 ON)
	uint GetVolume();
	bool ChangeVolume(uint currentVolume) = delete;
	bool VolumeUp();
	bool VolumeDown();

	// 전원 조작 관련
	bool IsPowered();
	bool PowerOn();
	bool PowerOff();
	void TogglePower();

	// 이용!
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
		return brand;     //brand가 주소값을 가지고 있으므로 그것을 참조해서 들어가야만
		//brand명을 알수있으므로 *get_brand
	}
	void information()
	{
		cout << "=========TV 정보=========" << endl;
		cout << "Brand  :  " << brand << endl;
		cout << "Channel  :  " << channel << endl;
	}
	void change_channel(int e_channel)
	{
		channel = e_channel;
	}

	
	// friend class인 RemoteController를 보조하기 위해 만든 메서드들로서,
	// 메모리 참조 오류를 방지하고자 만들었습니다.
private:
	void RegisterRemoteController(RemoteController* target);
	void DeRegisterRemoteController(RemoteController* target);
	

private:
	std::map<uint, Channel*> channels;					// 등록된 채널들
	std::list<RemoteController*> connectedController;	// 연결된 리모컨

	int channel;                                        //채널
	char brand[20];                                     //브랜드저장
	bool power;											// 전원 
	bool channelExist;									// 현재 가리키고 있는 채널이 존재하는가?
	uint currentChannel;								// 현재 가리키고 있는 채널의 번호
	uint currentVolume;									// 현재 볼륨 상태
};