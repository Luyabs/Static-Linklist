#include <iostream>
#include "SLink.h"
#include "SNode.h"

using namespace std;

int main()
{	//检验深赋值运算和深拷贝运算
	cout << "先检验从数组转换构造和深拷贝构造:" << endl;
	double array[10];
	for (int i = 0; i < 10; i++)
		array[i] = 0.1 * (i * i);
	SLink<double> linktemplate(array, 10);
	SLink<double> linkcopystruction(linktemplate);
	linktemplate.Traverse();
	linkcopystruction.Traverse();
	cout << "没有错误" << endl;


	SLink<double> link;
	char c = '$';	//switch控制符
	double e = 0;	//元素
	int i;			//位置
	const char* filename = "SList.txt";		//保存文件

	while (c != '0')
	{
		cout << endl << "1. 生成静态链表(会重置链表).";
		cout << endl << "x. 从已有静态链表生成静态链表(会重置链表).";
		cout << endl << "2. 显示静态链表.";
		cout << endl << "3. 设置元素值.";
		cout << endl << "4. 删除元素.";
		cout << endl << "5. 插入元素.";
		cout << endl << "6. 定位元素位置";
		cout << endl << "7. 通过位置搜索元素.";
		cout << endl << "8. 求链表长度";
		cout << endl << "9. 重置链表";
		cout << endl << "a. 将链表完全倒置";
		cout << endl << "b. 将链表按升降序排序";
		cout << endl << "c. 扩充链表的最大容量";
		cout << endl << "d. 从文件中读取链表(会重置链表)";
		cout << endl << "e. 覆盖保存链表到文件";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~9,a~e,x):";
		cin >> c;
		switch (c)
		{
		case '1':
			link.Reset();
			cout << endl << "输入e(e = -666时退出):";
			cin >> e;
			while (e != -666) {
				try
				{
					link.Insert(e);
				}
				catch (int)
				{
					cout << "当前链表长度达到最大长度，需要先扩容才能插入新的值" << endl;
					break;
				}
				cin >> e;
			}
			break;
		case 'x':
			link.Reset();
			link = linktemplate;
			cout << "从最上方链表深赋值静态链表" << endl;
			break;
		case '2':
			link.Traverse(true, cout);
			break;
		case '3':
			cout << endl << "输入位置:";
			cin >> i;
			cout << endl << "输入元素值:";
			cin >> e;
			try
			{
				link.Set(i, e);
				cout << "设置成功." << endl;
			}
			catch (int)
			{
				cout << "位置范围错." << endl;
			}
			break;
		case '4':
			cout << endl << "输入位置:";
			cin >> i;
			try
			{
				e = link.Delete(i);
				cout << "元素 " << e << " 已删除" << endl;
			}
			catch (int)
			{
				cout << "删除的元素位置不在链表存储范围内" << endl;
			}
			break;
		case '5':
			cout << endl << "输入位置:";
			cin >> i;
			cout << endl << "输入元素值:";
			cin >> e;
			try
			{
				link.Insert(i, e);
			}
			catch (int(err))
			{
				if (err == OVER_FLOW)
					cout << "当前链表长度达到最大长度，需要先扩容才能插入新的值" << endl;
				else if (err == RANGE_ERROR)
					cout << "插入的元素位置出现错误" << endl;
			}
			break;
		case '6':
			cout << endl << "输入元素e的值:";
			cin >> e;
			i = link.Find(e);
			if (i == NOT_FOUND)
				cout << "元素不存在." << endl;
			else
				cout << "元素" << e << "的序号为：" << i << endl;
			break;
		case '7':
			cout << endl << "输入元素e的位置:";
			cin >> i;
			try
			{
				e = link.Search(i);
				cout << "该位置元素的值:" << e << endl;
			}
			catch (int)
			{
				cout << "位置范围错." << endl;
			}
			break;
		case '8':
			cout << endl << "单链表的长度为:" << link.Length() << endl;
			break;
		case '9':
			link.Reset();
			if (link.Length() == 0)
				cout << endl << "链表已重置" << endl;
			else
				cout << endl << "链表未重置，错误待发现" << endl;
			break;
		case 'a':
			link.Reverse();
			cout << endl << "逆序后的链表：" << endl;
			link.Traverse(true, cout);
			break;
		case 'b':
			cout << "按升序排序输入1；按降序排序输入2；输入其他任意数字将不执行排序" << endl;
			cin >> i;
			switch (i)
			{
			case 1:
				link.Sort();
				cout << endl << "排序后的链表：" << endl;
				link.Traverse(true, cout);
				break;
			case 2:
				link.Sort();
				link.Reverse();
				cout << endl << "排序后的链表：" << endl;
				link.Traverse(true, cout);
				break;
			default:
				cout << endl << "不执行排序" << endl;
				break;
			}
			break;
		case 'c':
			cout << endl << "将链表的最大容量扩容至(至少大于" << MAXSIZE << "):";
			cin >> i;
			try
			{ 
				link.Enlarge(i);
			    cout << endl << "扩容成功" << endl;
			}
			catch (int)
			{
				cout << endl << "链表的最大容量扩容至(至少大于" << MAXSIZE << "):";
			}
			break;
		case 'd':
			cout << endl << "正在从" << filename << "文件中读取链表";
			link.Load(filename);
			cout << endl << "读取成功" << endl;
			break;
		case 'e':
			cout << endl << "正在覆盖保存链表至" << filename << "文件";
			link.Save(filename);
			cout << endl << "保存成功" << endl;
			break;
		}

	}
}
