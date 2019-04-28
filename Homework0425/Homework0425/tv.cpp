#include "tv.h"

#include <iostream>
#include <algorithm>
#include "channel.h"
#include "remotecontroller.h"


TV::TV() :power(false), channelExist(false), currentChannel(1),currentVolume((Setting::VolumeMax + Setting::VolumeMin) / 2){}
TV::~TV()
{
	for (auto i : channels) delete i.second; // Channel* 형식이고, 동적으로 생성했기 때문에 힙에 있으므로 하나씩 삭제 처리 해주어야한다.
	for (auto i : connectedController) i->ResetTarget(); // TV가 없어지면 가리킬 대상도 없어져야 안전한 처리가 가능하다.
}

// 리모트 컨트롤러의 안전 처리를 위해. 이들은 TV가 먼저 없어질 경우를 위한 처리를 위해 필요한 함수들이다.
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



// 채널 설정 관련. 전원이 올라가있으면 조작할 수 없다.
// Channel은 포인터 형식으로 들어와야한다. 이것은 다형성을 위해서이며, 
// 간략화된 팩토리 패턴이 적용된 ChannelFactory 클래스를 이용하도록 한다.
bool TV::AddChannel(uint channelNumber, Channel* newChannel)
{
	// 전원이 올라가 있거나 대상이 존재하면 처리를 거부한다.
	if (power || channels.find(channelNumber) != channels.end()) return false;

	// stl의 std::map의 추가 방법중 하나
	channels[channelNumber] = newChannel;

	// 처음 추가하는 채널이었을 경우엔 대상 채널을 가리키게 한다.
	if (channels.size() == 1)
	{
		currentChannel = channelNumber;
		channelExist = true;
	}
	// 가리키고 있던 채널 번호에 생성한 것이라면 가리키고 있는 채널은 존재하게 되므로,
	else if (currentChannel == channelNumber) channelExist = true;
	return true;
}

// AddChannel와 로직이 비슷하므로 위를 참고.
bool TV::RemoveChannel(uint channelNumber)
{
	if (power || channels.find(channelNumber) == channels.end()) return false;

	channels.erase(channelNumber);
	if(channelNumber == currentChannel) channelExist = false;
	return true;
}





// 채널 정보 및 조작 관련
uint TV::GetChannel() { return currentChannel; }
bool TV::ChangeChannel(uint channelNumber)
{
	// 전원이 꺼져있거나 채널이 없을 경우 거부합니다.
	if (!power || channels.size() == 0) return false;

	// 대상 채널로 전환하고 대상이 존재하지 않으면 존재하지 않는다고 저장하고 실패했음을 알립니다.
	// 존재한다면 존재한다고 저장하고 성공했음을 알립니다.
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
		// 현재 채널 번호보다 큰 다른 채널을 찾았다면 그 채널의 번호를 적용합니다.
		if (currentChannel < i.first)
		{
			currentChannel = i.first;
			return;
		}
	}

	// 없었다면 처음의 채널을 가리킵니다.
	currentChannel = channels.begin()->first;
}

// 위의 로직과 비슷합니다.
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






// 볼륨 정보 및 조작 관련
uint TV::GetVolume() { return currentVolume; }
bool TV::VolumeUp()
{
	if (!power) return false;

	// 현재 볼륨이 최대인지 검사하고 최대라면 처리를 거부합니다.
	if (currentVolume == Setting::VolumeMax) return false;
	++currentVolume; return true;
}
bool TV::VolumeDown()
{
	if (!power) return false;

	if(currentVolume == Setting::VolumeMin) return false;
	--currentVolume; return true;
}



// 전원 조작 및 조사 관련
bool TV::IsPowered() { return power; }
bool TV::PowerOn() { if (power) return false; return power = true;}
bool TV::PowerOff() { if (!power) return false; return power = false; }
void TV::TogglePower() { power = !power; }

// 이용 -> 시청!
void TV::operator()() { View(); }

void TV::View()
{
	std::cout << "====== TV ======\n";
	if (!power)
	{
		std::cout << "[까--만--화--면]\n\n" << std::endl;
		return;
	}

	std::cout << "볼륨 : " << currentVolume << "\n";
	std::cout << currentChannel << "번 채널 시청중.\n";

	if (!channelExist)
		std::cout << "bzzzzzzzzzzzzzzzzzz\n\n" << std::endl;
	else 
		channels[currentChannel]->Show();

	std::cout << "\n\n" << std::endl;
}
