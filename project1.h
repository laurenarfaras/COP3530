#include <iostream>
#include <string>
#include <math.h>
#include <list>
#include <unordered_map>
#include <stack>
#include <queue>
extern bool DBZ;
extern bool UDV;

using namespace std;

class Token {

	public:

	string tokenType = "";

	//if a number
	double val = 0.0;

	//if an operator
	string symbol = "";
	string associativity = "";
	int precedence = 0;
	int paramCount = 0;

	//number constructor
	Token(string type, double number) {
		tokenType = type;
		val = number;
	}

	//parenthesis constructor
	Token(string type, string sym) {
		tokenType = type;
		symbol = sym;
	}

	//operator constructor
	Token(string type, string sym, string assoc, int prec, int param) {
		tokenType = type;
		symbol = sym;
		associativity = assoc;
		precedence = prec;
		paramCount = param;
	}

	Token() {}


};
