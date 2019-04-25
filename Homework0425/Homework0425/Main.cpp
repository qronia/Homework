#include <iostream>
#include <conio.h>

#include "tv.h"
#include "channelfactory.h"
#include "remotecontroller.h"

#define getch() _getch()

using namespace std;

int main()
{
	int channelNumber;
	char input;
	TV tv;
	RemoteController rc(&tv);

	cout << "========== 초기 생성 시도 ===========\n";
	if( tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "코메디 채널 생성 실패\n";
	if( tv.AddChannel(2, ChannelFactory::MakeLifeChannel())) cout << "생활 채널 생성 실패\n";
	if( tv.AddChannel(3, ChannelFactory::MakeShoppingChannel())) cout << "쇼핑 채널 생성 실패\n";
	if( tv.AddChannel(4, ChannelFactory::MakeSportChannel())) cout << "스포츠 채널 생성 실패\n";
	if (tv.AddChannel(5, ChannelFactory::MakeComedyChannel())) cout << "코메디 채널 생성 실패\n";

	cout << "========== 재생성 시도 ===========\n";
	if (tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "코메디 채널 생성 실패\n";
	if (tv.AddChannel(2, ChannelFactory::MakeLifeChannel())) cout << "생활 채널 생성 실패\n";
	if (tv.AddChannel(3, ChannelFactory::MakeShoppingChannel())) cout << "쇼핑 채널 생성 실패\n";
	if (tv.AddChannel(4, ChannelFactory::MakeSportChannel())) cout << "스포츠 채널 생성 실패\n";
	if (tv.AddChannel(5, ChannelFactory::MakeComedyChannel())) cout << "코메디 채널 생성 실패\n";



	cout << "========== 2회의 삭제 시도 ===========\n";
	if(tv.RemoveChannel(1)) cout << "1채널 삭제 실패\n";
	if(tv.RemoveChannel(1)) cout << "1채널 삭제 실패\n";


	cout << "========== 2회의 재추가 시도 ===========\n";
	if (tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "코메디 채널 생성 실패\n";
	if (tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "코메디 채널 생성 실패\n";



	cout << "========== 전원 키기 전 시청 ===========\n";
	tv();

	cout << "========== 전원 키고 시청 ===========\n";
	rc.TogglePower();
	tv();

	cout << "========== 전원 킨 채로 채널 수정 가능한지? ===========\n";
	if (!tv.RemoveChannel(1) ) cout << "실패\n";
	else cout << "성공\n";


	cout << "============= 시청 테스트 =============\nENTER를 누르면 커스텀 테스트를 진행합니다.";
	cout.flush();
	getchar();

	while (true)
	{
		system("cls");
		tv();

		cout << "\n\n q,a : 채널 Up&Down\n";
		cout << "w,s : 볼륨 Up&Down\n";
		cout << "p : 전원 토글\n";
		cout << "e : TV를 향해 리모콘!\n";
		cout << "d : 이상한곳 향해 리모콘!\n";
		cout << "t : 채널 번호 직접 입력" << endl;
		cout << "z : 테스트 종료\n";
		cout.flush();

		input = getch();

		switch (input)
		{
		case 'q': rc.ChannelUp();	break;
		case 'a': rc.ChannelDown(); break;

		case 'w': rc.VolumeUp();	break;
		case 's': rc.VolumeDown();	break;

		case 't':
			cout << "새 번호를 입력:";
			cout.flush();
			cin >> channelNumber;
			rc.ChangeChannel(channelNumber);
			break;

		case 'p': rc.TogglePower(); break;

		case 'e': rc.SetTarget(&tv);break;
		case 'd': rc.ResetTarget(); break;

		case 'z': return 0;

		default: break;
		}
	}


	cout.flush();
	getchar();
	return 0;
}