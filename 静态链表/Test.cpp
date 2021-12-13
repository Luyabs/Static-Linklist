#include <iostream>
#include "SLink.h"
#include "SNode.h"

using namespace std;

int main()
{
	SLink<double> link;
	char c = '$';
	double e = 0;

	while (c != 0)
	{
		cout << endl << "1. 生成单链表.";
		cout << endl << "2. 显示单链表.";
		cout << endl << "3. 取指定位置的元素.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~9,a~b):";
		cin >> c;
		switch (c)
		{
		case '1':
			link.Reset();
			cout << endl << "输入e(e = 666时退出):";
			cin >> e;
			while (e != 0) {
				link.Insert(e);
				cin >> e;
			}
			break;
		case '2':
			link.Traverse(true, cout);
			break;
		case '3':
			cout << endl << "输入元素e:";
			cin >> e;
			e = link.Find(e);
			if (link.Find(e) == -1)
				cout << "元素不存在." << endl;
			else
				cout << "元素的位置:" << e << endl;
			break;
		}
	}
}
