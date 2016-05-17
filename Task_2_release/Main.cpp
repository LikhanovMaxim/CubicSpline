#include<iostream>
#include"CubicSpline.h"
using namespace std;
int main(){
	setlocale(LC_CTYPE, "");
	char name[50];
	char str[256];
	double x;
	cout << "������� ��� �����, � �������� ����� ����������� ����������:\n";
	cin >> name;
	CubicSpline alg;
	alg.preparationForWork(name);
	cout << "������� x � ������� �� "<< alg.getFirstX() << " �� " << alg.getLastX() << " (��� ������ ������� 'exit'):" << endl;
	cin >> str;
	x = atof(str);
	while (strcmp(str, "exit")){
		if (alg.checkBorder(x)){
			cout << "S(x) = " << alg.calculationSx(x) << endl;
		}
		else{
			cout << "����� �� �������!" << endl;
		}
		cin >> str;
		x = atof(str);
	}
	return 0;
}