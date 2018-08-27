#include "doubleLinkedList.h"
#include "ArgumentManager.h"
#include<cmath>
#include<fstream>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Usage: infinitearithmetic \"filename=xyz.txt;digitsPerNode=<number>\"\n";
	}
	ArgumentManager am(argc, argv);
	string filename = am.get("input");
	string digitsPerNode = am.get("digitsPerNode"); //get digits per node and convert them to integer 
	ifstream myfile;
	myfile.open(filename); //open whatever the filename is 

	string line=" ";//stores the string of numbers 
	string num1=" "; //stores the first number
	string num2=" ";//stores the second number
	string op=" ";//stores the operator 

	while (getline(myfile, line)) {
		int  len = line.length();
		for (int i = 0; i < len; i++) {
			if ((line[i] == '*') || (line[i] == '+' || line[i] == '-'))
				op = line[i];

			if (!isdigit(line[i]))
				line[i] = ' ';
		}

		stringstream ss(line.c_str());
		ss >> num1 >> num2;

		int digitsPerN = stoi(digitsPerNode);
		DoubleLinkedList l1(num1, digitsPerN);
		DoubleLinkedList l2(num2, digitsPerN);
		DoubleLinkedList l;

		if (op == "+") {
			l = l1 + l2;
			l1.Print();
			cout << "+";
			l2.Print();
			cout << "=";
			l.Print();
			cout << endl;
		}
		if (op == "*") {
			l = l1 * l2;
			l1.Print();
			cout << "*";
			l2.Print();
			cout << "=";
			l.Print();
			cout << endl;
		}
	}

	system("pause");
	return 0;
}