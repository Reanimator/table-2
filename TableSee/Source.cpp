#include <iostream>
#include <string>
#include "TableSee.h"

using namespace std;

void main()
{
	table<int,std::string> v(15);

	setlocale(NULL, "Russian");

	v.dobavit(12, std::string("����������� ������1"));//����� ����� ������
	v.dobavit(31, std::string("����������� ������2"));//��� ��
	v.dobavit(15, std::string("������ �������� �3"));//� ��� ��

	cout << v[15] << endl;//������������� ����� ����� ������
	cout << v[12] << endl;//��� ��
	cout << v[31] << endl;//� ��� ��

	
		
	cin.get();
}