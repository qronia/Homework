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

	cout << "========== �ʱ� ���� �õ� ===========\n";
	if( tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "�ڸ޵� ä�� ���� ����\n";
	if( tv.AddChannel(2, ChannelFactory::MakeLifeChannel())) cout << "��Ȱ ä�� ���� ����\n";
	if( tv.AddChannel(3, ChannelFactory::MakeShoppingChannel())) cout << "���� ä�� ���� ����\n";
	if( tv.AddChannel(4, ChannelFactory::MakeSportChannel())) cout << "������ ä�� ���� ����\n";
	if (tv.AddChannel(5, ChannelFactory::MakeComedyChannel())) cout << "�ڸ޵� ä�� ���� ����\n";

	cout << "========== ����� �õ� ===========\n";
	if (tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "�ڸ޵� ä�� ���� ����\n";
	if (tv.AddChannel(2, ChannelFactory::MakeLifeChannel())) cout << "��Ȱ ä�� ���� ����\n";
	if (tv.AddChannel(3, ChannelFactory::MakeShoppingChannel())) cout << "���� ä�� ���� ����\n";
	if (tv.AddChannel(4, ChannelFactory::MakeSportChannel())) cout << "������ ä�� ���� ����\n";
	if (tv.AddChannel(5, ChannelFactory::MakeComedyChannel())) cout << "�ڸ޵� ä�� ���� ����\n";



	cout << "========== 2ȸ�� ���� �õ� ===========\n";
	if(tv.RemoveChannel(1)) cout << "1ä�� ���� ����\n";
	if(tv.RemoveChannel(1)) cout << "1ä�� ���� ����\n";


	cout << "========== 2ȸ�� ���߰� �õ� ===========\n";
	if (tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "�ڸ޵� ä�� ���� ����\n";
	if (tv.AddChannel(1, ChannelFactory::MakeComedyChannel())) cout << "�ڸ޵� ä�� ���� ����\n";



	cout << "========== ���� Ű�� �� ��û ===========\n";
	tv();

	cout << "========== ���� Ű�� ��û ===========\n";
	rc.TogglePower();
	tv();

	cout << "========== ���� Ų ä�� ä�� ���� ��������? ===========\n";
	if (!tv.RemoveChannel(1) ) cout << "����\n";
	else cout << "����\n";


	cout << "============= ��û �׽�Ʈ =============\nENTER�� ������ Ŀ���� �׽�Ʈ�� �����մϴ�.";
	cout.flush();
	getchar();

	while (true)
	{
		system("cls");
		tv();

		cout << "\n\n q,a : ä�� Up&Down\n";
		cout << "w,s : ���� Up&Down\n";
		cout << "p : ���� ���\n";
		cout << "e : TV�� ���� ������!\n";
		cout << "d : �̻��Ѱ� ���� ������!\n";
		cout << "t : ä�� ��ȣ ���� �Է�" << endl;
		cout << "z : �׽�Ʈ ����\n";
		cout.flush();

		input = getch();

		switch (input)
		{
		case 'q': rc.ChannelUp();	break;
		case 'a': rc.ChannelDown(); break;

		case 'w': rc.VolumeUp();	break;
		case 's': rc.VolumeDown();	break;

		case 't':
			cout << "�� ��ȣ�� �Է�:";
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