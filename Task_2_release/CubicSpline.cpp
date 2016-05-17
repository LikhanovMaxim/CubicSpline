#include<iostream>
#include"CubicSpline.h"
#include"Algorithm.h"
using namespace std;
void CubicSpline :: calculationH(){
	for (int i = 0; i < decN; i++){
		h[i] = x[i + 1] - x[i];
	}
}
void CubicSpline :: calculationP(){
	for (int i = 1; i < decN; i++){
		p[i] = h[i] / (h[i - 1] + h[i]);
	}
}
void CubicSpline :: calculationU(){
	for (int i = 1; i < decN; i++){
		u[i] = h[i - 1] / (h[i - 1] + h[i]);
	}
}
void CubicSpline :: calculationFi(){
	for (int i = 1; i < decN; i++){
		fi[i] = u[i] * (y[i + 1] - y[i]) / h[i];
		fi[i] += p[i] * (y[i] - y[i - 1]) / h[i - 1];
		fi[i] *= 3;
	}
}
void CubicSpline :: calculationHPUFi(){
	calculationH();
	calculationP();
	calculationU();
	calculationFi();
}
void CubicSpline :: calculationM(){
	double* mainDiagonal = new double[n];
	mainDiagonal[0] = 1;
	for (int i = 1; i < decN; i++){
		mainDiagonal[i] = 2;
	}
	mainDiagonal[decN] = 1;
	double* f = new double[n];
	f[0] = f[decN] = 0;
	for (int i = 1; i < decN; i++){
		f[i] = fi[i];
	}
	m = solveMatrix(n, p, mainDiagonal, u, f);
}
void CubicSpline :: calculationA(){
	for (int i = 0; i < decN; i++){
		a[i] = y[i];
	}
}
void CubicSpline :: calculationB(){
	for (int i = 0; i < decN; i++){
		b[i] = m[i];
	}
}
void CubicSpline :: calculationC(){
	for (int i = 0; i < decN; i++){
		c[i] = 3 * (y[i + 1] - y[i]) / pow(h[i], 2);
		c[i] -= (2 * m[i] + m[i + 1]) / h[i];
	}
}
void CubicSpline :: calculationD(){
	for (int i = 0; i < decN; i++){
		d[i] = m[i + 1] + m[i];
		d[i] /= pow(h[i], 2);
		d[i] -= 2 * (y[i + 1] - y[i]) / pow(h[i], 3);
	}
}
void CubicSpline :: calculationABCD(){
	calculationA();
	calculationB();
	calculationC();
	calculationD();
}
void CubicSpline :: fileToInput(char *name){
	FILE *f;
	float cur;
	f = fopen(name, "r");
	if (!f){
		cout << "Ошибка открытия файла:" << name << endl;
		exit(1);
	}
	fscanf(f, "%d", &n);
	x = new double[n];
	y = new double[n];
	for (int i = 0; i < n; i++){
		fscanf(f, "%f", &cur);
		x[i] = cur;
	}
	for (int i = 0; i < n; i++){
		fscanf(f, "%f", &cur);
		y[i] = cur;
	}
	fclose(f);
}
void CubicSpline :: initialization(){
	m = new double[n];
	for (int i = 0; i < n; i++){
		m[i] = 0;
	}
	decN = n - 1;
	h = new double[decN];
	p = new double[decN];
	u = new double[decN];
	fi = new double[decN];
	a = new double[decN];
	b = new double[decN];
	c = new double[decN];
	d = new double[decN];
	for (int i = 0; i < decN; i++){
		h[i] = p[i] = u[i] = fi[i] = 0;
		a[i] = b[i] = c[i] = d[i] = 0;
	}
}
void CubicSpline :: setIntialValue(char* name){
	fileToInput(name);
	initialization();
}
void CubicSpline :: run(){
	calculationHPUFi();
	calculationM();
	calculationABCD();
}
int CubicSpline :: getInterval(double tmp){
	if (tmp == x[0]){
		return 0;
	}
	int index;
	for (index = 0; tmp > x[index]; index++){}
	return index - 1;
}
CubicSpline :: CubicSpline(){}
CubicSpline :: CubicSpline(char *name){
	preparationForWork(name);
}
void CubicSpline :: clear(){
	n = 0; decN = 0;
	delete[] x;
	delete[] y;
	delete[] h;
	delete[] p;
	delete[] u;
	delete[] fi;
	delete[] m;
	delete[] a;
	delete[] b;
	delete[] c;
	delete[] d;
}
void CubicSpline :: preparationForWork(char* nameFile){
	clear();
	setIntialValue(nameFile);
	run();
}
bool CubicSpline :: checkBorder(double tmp){
	if (tmp<x[0] || tmp> x[decN]){
		return false;
	}
	return true;
}
double CubicSpline :: calculationSx(double tmp){
	int i = getInterval(tmp);
	double cur = tmp - x[i];
	return a[i] + b[i] * cur + c[i] * pow(cur, 2) + d[i] * pow(cur, 3);
}
double CubicSpline :: getFirstX(){
	return x[0];
}
double CubicSpline :: getLastX(){
	return x[decN];
}