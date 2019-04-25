#include "remotecontroller.h"


// 리모트 컨트롤러는 생성할때 대상 TV를 받거나 받지 않을 수 있습니다.
RemoteController::RemoteController() :targetTV(nullptr) {}
RemoteController::RemoteController(TV * targetTV) : targetTV(targetTV) {
	if (targetTV != nullptr) targetTV->RegisterRemoteController(this);
}

// 삭제시에는 어느 TV든 가리키고있는지 확인하고 가리키고 있다면,
// TV에서 메모리 참조 안전을 위해 가지고 있는 리스트에서 이를 제외하라고 명령합니다.
RemoteController::~RemoteController() {if (targetTV != nullptr) targetTV->DeRegisterRemoteController(this);}




// 대상 TV 변경
void RemoteController::ResetTarget() { targetTV = nullptr; }
void RemoteController::SetTarget(TV * targetTV) { this->targetTV = targetTV; if (targetTV == nullptr) targetTV->RegisterRemoteController(this); }


/*
	아래의 코드부터는 TV를 가리키고 있는지 확인후, 
	가리키고 있다면 대상 TV에 리모트 컨트롤러가 명령받은 명령을 수행하라고 명령합니다.
*/



// 채널 관련 설정
bool RemoteController::ChangeChannel(uint channelNumber)
{
	if (targetTV == nullptr) return false;
	return targetTV->ChangeChannel(channelNumber);
}

void RemoteController::ChannelUp()
{
	if (targetTV == nullptr) return;
	targetTV->ChannelUp();
}

void RemoteController::ChannelDown()
{
	if (targetTV == nullptr) return;
	targetTV->ChannelDown();
}



// 볼륨 관련 설정
bool RemoteController::VolumeUp()
{
	if (targetTV == nullptr) return false;
	return targetTV->VolumeUp();
}

bool RemoteController::VolumeDown()
{
	if (targetTV == nullptr) return false;
	return targetTV->VolumeDown();
}

void RemoteController::TogglePower()
{
	if (targetTV == nullptr) return;
	targetTV->TogglePower();
}


