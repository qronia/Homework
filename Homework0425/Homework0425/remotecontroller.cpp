#include "remotecontroller.h"


// ����Ʈ ��Ʈ�ѷ��� �����Ҷ� ��� TV�� �ްų� ���� ���� �� �ֽ��ϴ�.
RemoteController::RemoteController() :targetTV(nullptr) {}
RemoteController::RemoteController(TV * targetTV) : targetTV(targetTV) {
	if (targetTV != nullptr) targetTV->RegisterRemoteController(this);
}

// �����ÿ��� ��� TV�� ����Ű���ִ��� Ȯ���ϰ� ����Ű�� �ִٸ�,
// TV���� �޸� ���� ������ ���� ������ �ִ� ����Ʈ���� �̸� �����϶�� ����մϴ�.
RemoteController::~RemoteController() {if (targetTV != nullptr) targetTV->DeRegisterRemoteController(this);}




// ��� TV ����
void RemoteController::ResetTarget() { targetTV = nullptr; }
void RemoteController::SetTarget(TV * targetTV) { this->targetTV = targetTV; if (targetTV == nullptr) targetTV->RegisterRemoteController(this); }


/*
	�Ʒ��� �ڵ���ʹ� TV�� ����Ű�� �ִ��� Ȯ����, 
	����Ű�� �ִٸ� ��� TV�� ����Ʈ ��Ʈ�ѷ��� ��ɹ��� ����� �����϶�� ����մϴ�.
*/



// ä�� ���� ����
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



// ���� ���� ����
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


