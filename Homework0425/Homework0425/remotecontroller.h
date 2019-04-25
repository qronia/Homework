#pragma once

#include "typedef.h"
#include "tv.h"

/*
	리모트 컨트롤러는 그저 TV를 지정하고 그 TV를 조작하는 것 말고는 하지 않습니다.

	다만 TV가 리모트 컨트롤러가 제거되기 전에 제거되면 메모리 참조 오류가 발생할 여지가 있는데,
	이는 TV 소멸자와 이 클래스의 생성자를 참고하시면 어떻게 해결했는지 한번에 보이실 겁니다.

	TV는 연결된 리모트 컨트롤러들이 어떤것들이 있는지 알수 있어야하고,
	각 리모트 컨트롤러가 연결될 때 그것을 리스트에 추가합니다.
*/


class RemoteController
{
public:
	RemoteController();
	RemoteController(TV* targetTV);
	~RemoteController();

	// 채널 변경
	bool ChangeChannel(uint channelNumber);
	void ChannelUp();
	void ChannelDown();


	// 볼륨 변경
	bool VolumeUp();
	bool VolumeDown();


	// 전원 버튼
	void TogglePower();


	// TV 가리키기
	void ResetTarget();
	void SetTarget(TV* targetTV);

private:
	TV* targetTV;
};