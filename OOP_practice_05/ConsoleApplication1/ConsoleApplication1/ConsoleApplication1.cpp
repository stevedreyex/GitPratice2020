#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
using namespace std;
void InputWeight(double weight)
{
	cout << "please enter your weight(kg): " << endl;
	cin >> weight;
}
double GetBMI(double height, double weight)
{
	double bmi;
	bmi = weight / pow(height / 100, 2);
	return bmi;
}
int main(cli::array<System::String ^> ^args)
{
	double height = 0;
	double weight = 0;
	cout << "please enter your height(cm): " << endl;
	cin >> height; InputWeight(weight);
	cout << "BMI = ";
	cout << GetBMI(height, weight);
	system("pause"); return 0;
}
