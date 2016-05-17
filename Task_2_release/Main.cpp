#include<iostream>
#include"CubicSpline.h"
using namespace std;
int main(){
	setlocale(LC_CTYPE, "");
	char name[50];
	char str[256];
	double x;
	cout << "Введите имя файла, с которого будет считываться информация:\n";
	cin >> name;
	CubicSpline alg;
	alg.preparationForWork(name);
	cout << "Введите x в отрезке от "<< alg.getFirstX() << " до " << alg.getLastX() << " (для выхода введите 'exit'):" << endl;
	cin >> str;
	x = atof(str);
	while (strcmp(str, "exit")){
		if (alg.checkBorder(x)){
			cout << "S(x) = " << alg.calculationSx(x) << endl;
		}
		else{
			cout << "Выход за границы!" << endl;
		}
		cin >> str;
		x = atof(str);
	}
	return 0;
}