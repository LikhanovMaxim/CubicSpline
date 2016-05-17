#ifndef CubicSpline_H
#define CubicSpline_H
class CubicSpline{
	int n;
	double* x;
	double* y;
	int decN; // n - 1
	double* h;
	// p[0] = u[0] = fi[0] = 0 not used
	double* p;
	double* u;
	double* fi;
	double* m;
	double* a;
	double* b;
	double* c;
	double* d;
	void calculationH();
	void calculationP();//p = λÿμαδΰ
	void calculationU();//u= νώ 
	void calculationFi();
	void calculationHPUFi();
	void calculationM();
	void calculationA();
	void calculationB();
	void calculationC();
	void calculationD();
	void calculationABCD();
	void fileToInput(char *name);
	void initialization();
	void setIntialValue(char* name);
	void run();
	// check for out of bounds
	int getInterval(double tmp);
public:
	CubicSpline();
	CubicSpline(char *name);
	void clear();
	void preparationForWork(char* nameFile);
	bool checkBorder(double tmp);
	double calculationSx(double tmp);
	double getFirstX();
	double getLastX();
};
#endif