#include "tv.h"

#include <iostream>
#include <algorithm>
#include "channel.h"
#include "remotecontroller.h"


TV::TV() :power(false), channelExist(false), currentChannel(1),currentVolume((Setting::VolumeMax + Setting::VolumeMin) / 2){}
TV::~TV()
{
	for (auto i : channels) delete i.second; // Channel* �����̰�, �������� �����߱� ������ ���� �����Ƿ� �ϳ��� ���� ó�� ���־���Ѵ�.
	for (auto i : connectedController) i->ResetTarget(); // TV�� �������� ����ų ��� �������� ������ ó���� �����ϴ�.
}

// ����Ʈ ��Ʈ�ѷ��� ���� ó���� ����. �̵��� TV�� ���� ������ ��츦 ���� ó���� ���� �ʿ��� �Լ����̴�.
void TV::RegisterRemoteController(RemoteController * target) 
{
	if (target == nullptr) return;
	connectedController.push_back(target);
}

void TV::DeRegisterRemoteController(RemoteController * target)
{ 
	if (target == nullptr) return;
	connectedController.remove(target); 
}



// ä�� ���� ����. ������ �ö������� ������ �� ����.
// Channel�� ������ �������� ���;��Ѵ�. �̰��� �������� ���ؼ��̸�, 
// ����ȭ�� ���丮 ������ ����� ChannelFactory Ŭ������ �̿��ϵ��� �Ѵ�.
bool TV::AddChannel(uint channelNumber, Channel* newChannel)
{
	// ������ �ö� �ְų� ����� �����ϸ� ó���� �ź��Ѵ�.
	if (power || channels.find(channelNumber) != channels.end()) return false;

	// stl�� std::map�� �߰� ����� �ϳ�
	channels[channelNumber] = newChannel;

	// ó�� �߰��ϴ� ä���̾��� ��쿣 ��� ä���� ����Ű�� �Ѵ�.
	if (channels.size() == 1)
	{
		currentChannel = channelNumber;
		channelExist = true;
	}
	// ����Ű�� �ִ� ä�� ��ȣ�� ������ ���̶�� ����Ű�� �ִ� ä���� �����ϰ� �ǹǷ�,
	else if (currentChannel == channelNumber) channelExist = true;
	return true;
}

// AddChannel�� ������ ����ϹǷ� ���� ����.
bool TV::RemoveChannel(uint channelNumber)
{
	if (power || channels.find(channelNumber) == channels.end()) return false;

	channels.erase(channelNumber);
	if(channelNumber == currentChannel) channelExist = false;
	return true;
}





// ä�� ���� �� ���� ����
uint TV::GetChannel() { return currentChannel; }
bool TV::ChangeChannel(uint channelNumber)
{
	// ������ �����ְų� ä���� ���� ��� �ź��մϴ�.
	if (!power || channels.size() == 0) return false;

	// ��� ä�η� ��ȯ�ϰ� ����� �������� ������ �������� �ʴ´ٰ� �����ϰ� ���������� �˸��ϴ�.
	// �����Ѵٸ� �����Ѵٰ� �����ϰ� ���������� �˸��ϴ�.
	currentChannel = channelNumber;
	if (channels.find(channelNumber) == channels.end())
	{
		channelExist = false;
		return false;
	}

	channelExist = true;
	return true;
}
void TV::ChannelUp()
{
	if (!power || channels.size() == 0) return;
	channelExist = true;

	for(auto i: channels)
	{
		// ���� ä�� ��ȣ���� ū �ٸ� ä���� ã�Ҵٸ� �� ä���� ��ȣ�� �����մϴ�.
		if (currentChannel < i.first)
		{
			currentChannel = i.first;
			return;
		}
	}

	// �����ٸ� ó���� ä���� ����ŵ�ϴ�.
	currentChannel = channels.begin()->first;
}

// ���� ������ ����մϴ�.
void TV::ChannelDown()
{
	if (!power || channels.size() == 0) return;
	channelExist = true;

	for (auto i = channels.rbegin(); i!=channels.rend(); ++i)
	{
		if (currentChannel > i->first)
		{
			currentChannel = i->first;
			return;
		}
	}

	currentChannel = channels.rbegin()->first;
}






// ���� ���� �� ���� ����
uint TV::GetVolume() { return currentVolume; }
bool TV::VolumeUp()
{
	if (!power) return false;

	// ���� ������ �ִ����� �˻��ϰ� �ִ��� ó���� �ź��մϴ�.
	if (currentVolume == Setting::VolumeMax) return false;
	++currentVolume; return true;
}
bool TV::VolumeDown()
{
	if (!power) return false;

	if(currentVolume == Setting::VolumeMin) return false;
	--currentVolume; return true;
}



// ���� ���� �� ���� ����
bool TV::IsPowered() { return power; }
bool TV::PowerOn() { if (power) return false; return power = true;}
bool TV::PowerOff() { if (!power) return false; return power = false; }
void TV::TogglePower() { power = !power; }

// �̿� -> ��û!
void TV::operator()() { View(); }

void TV::View()
{
	std::cout << "====== TV ======\n";
	if (!power)
	{
		std::cout << "[��--��--ȭ--��]\n\n" << std::endl;
		return;
	}

	std::cout << "���� : " << currentVolume << "\n";
	std::cout << currentChannel << "�� ä�� ��û��.\n";

	if (!channelExist)
		std::cout << "bzzzzzzzzzzzzzzzzzz\n\n" << std::endl;
	else 
		channels[currentChannel]->Show();

	std::cout << "\n\n" << std::endl;
}
