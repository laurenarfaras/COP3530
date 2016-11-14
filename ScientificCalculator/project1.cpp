#include "project1.h"
#include<string>
#define _USE_MATH_DEFINES

using namespace std;

unordered_map<string, double> varVals;
bool DBZ = false;
bool UDV = false;

//this method takes in a string and turns it into a list of Tokens
list<Token>* stringToTokenList(string str) {

	list<Token> *tokens = new list<Token>;

	//iterates through the string
	for (int i = 0; i < str.length(); i++) {

		if (str.at(i) == ' ') {

			//whitespace, nothing

		} else if (isdigit(str.at(i)) || str.at(i) == '.') {

			//check to see if it is a number
			string digit = "";

			while (i < str.length() && (isdigit(str.at(i)) || str.at(i) == '.')) {

				digit = digit + str.at(i);
				i++;

			}

			i--;
			tokens->push_back(Token("NUMBER", stod(digit)));

		} else if (str[i] == '+') {
			//check to see if char is an addition operator
			tokens->push_back(Token("OPERATOR", "+", "LEFT", 10, 2));

		} else if (str[i] == '-') {
			//check to see if char is a subtraction operator
			tokens->push_back(Token("OPERATOR", "-", "LEFT", 10, 2));

		} else if (str[i] == '*') {
			//check to see if char is a multiplication operator
			tokens->push_back(Token("OPERATOR", "*", "LEFT", 20, 2));

		} else if (str[i] == '/') {
			//check to see if char is a division operator
			tokens->push_back(Token("OPERATOR", "/", "LEFT", 20, 2));

		} else if (str[i] == '^') {
			//check to see if char is an exponentiation operator
			tokens->push_back(Token("OPERATOR", "^", "RIGHT", 30, 2));

		} else if (str[i] == '(') {
			//check to see if char is a left parenthesis
			tokens->push_back(Token("LEFTPARENTHESIS", "("));

		} else if (str[i] == ')') {
			//check to see if char is a right parenthesis
			tokens->push_back(Token("RIGHTPARENTHESIS", ")"));

		} else if (i+2 < str.length() && (str.compare(i, 3, "sin") == 0)) {
			//check to see if sin function
			i += 2;
			tokens->push_back(Token("OPERATOR", "sin", "RIGHT", 40, 1));

		} else if (i+2 < str.length() && (str.compare(i, 3, "cos") == 0)) {
			//check to see if cos function
			i += 2;
			tokens->push_back(Token("OPERATOR", "cos", "RIGHT", 40, 1));

		} else if (i+2 < str.length() && (str.compare(i, 3, "log") == 0)) {
			//check to see if log function
			i += 2;
			tokens->push_back(Token("OPERATOR", "log", "RIGHT", 40, 1));

		} else if (isalpha(str.at(i))) {
			//check to see if it is a variable
			string alpha = "";

			while (i < str.length() && isalpha(str.at(i))) {
				alpha = alpha + str.at(i);
				i++;
			}
			i--;

			double c;
			unordered_map<string,double>::const_iterator itr = varVals.find (alpha);

  		if ( itr == varVals.end() ) {
    		cout << "Undeclared-Variable" << endl;
				UDV = true;
				break;

  		} else {
				c = itr->second;
				tokens->push_back(Token("NUMBER", c));
			}

		}

	}
 return tokens;
}


//this method puts the list of tokens into a queue in postfix form
queue<Token>* shuntingYard(list<Token> *tokens) {

	queue<Token> *outputQueue = new queue<Token>;
	stack<Token> *operatorStack = new stack<Token>;

	//while there are tokens to be read
	while (!tokens->empty()) {

		//read a token
		Token t = tokens->front();

		//if the token is a number
		if (t.tokenType == "NUMBER"){

			//then push it onto the output queue
			outputQueue->push(t);
			//cout << t.val << " " << t.symbol << "\n";

			//if the token is an operator
		} else if (t.tokenType == "OPERATOR") {


			while (!operatorStack->empty()) {
				Token o2 = operatorStack->top();
				//check to make sure that the top of stack is operator
				if (o2.tokenType != "OPERATOR") {
					break;
				}

				//if t is left assoc and precedence is <= o2
				//if t is right assoc and precedence < o2
				if ((t.associativity == "LEFT") && (t.precedence <= o2.precedence)) {

					outputQueue->push(operatorStack->top());
					operatorStack->pop();

				} else if ((t.associativity == "RIGHT") && (t.precedence < o2.precedence)) {

					outputQueue->push(operatorStack->top());
					operatorStack->pop();

				} else {

					break;

				}

			}

			operatorStack->push(t);

			//if the token is a left parenthesis
		} else if (t.tokenType == "LEFTPARENTHESIS") {

			//push it onto the stack
			operatorStack->push(t);

			//if the token is right parenthesis
		} else if (t.tokenType == "RIGHTPARENTHESIS") {

			//until the token at the top of the stack is a left parenthesis
			while (operatorStack->top().tokenType != "LEFTPARENTHESIS") {

				//pop operators off the stack onto the output queue
				outputQueue->push(operatorStack->top());
				//cout << operatorStack->top().val << " " << operatorStack->top().symbol << "\n";
				operatorStack->pop();

		}

		// pop the left parenthesis from the stack
		operatorStack->pop();

	}
	tokens->pop_front();
}

	//when there are no more tokens to read
	//while there are stil operator tokens in the stack
	while (!operatorStack->empty()) {

			outputQueue->push(operatorStack->top());
			//cout << operatorStack->top().val << " " << operatorStack->top().symbol << "\n";
			operatorStack->pop();

	}
	return outputQueue;
}

// this method evaluates the operator with the arguments given
// and returns the answer in a double
double evaluate(list<double> values, string oper) {

	double arg0 = values.front();
	values.pop_front();

	if (oper == "sin" || oper == "cos" || oper == "log") {

		if (oper == "sin") {
			arg0 = sin(arg0);
		} else if (oper == "cos") {
			arg0 = cos(arg0);
		} else if (oper == "log") {
			arg0 = log(arg0);
		}

	} else {

		double arg1 = values.front();
		values.pop_front();

		if (oper == "+") {

			arg0 += arg1;

		} else if (oper == "-") {

			arg0 = arg1 - arg0;

		} else if (oper == "*") {

			arg0 *= arg1;

		} else if (oper == "/") {

			if (arg0 == 0) {
				cout << "Division-By-Zero" << endl;
				DBZ = true;
				return 0;
			} else {
				arg0 = arg1 / arg0;
			}

		} else if (oper == "^") {

			arg0 = pow(arg1, arg0);

		} else {

			// unknown operator

		}

	}


	return arg0;

}


// algorithm for evaluating a postfix expression
double calculate (queue<Token> *postfix) {

	stack<double> operandStack;

	// while there are input tokens left
	while (!postfix->empty()) {

		// read the next token from input
		Token t = postfix->front();

		// if the token is a value
		if (t.tokenType == "NUMBER") {

			// push it onto the stack
			operandStack.push(t.val);

			// otherwise, the token is an operator
		} else {

			// operator takes n arguments
			int arguments = t.paramCount;

				list<double> values;
				for (int i = 0; i < arguments; i++) {

					values.push_back(operandStack.top());
					operandStack.pop();

				}

				// evaluate the operator, with the values as arguments
				double result = evaluate(values, t.symbol);
				// push the returned results, if any, back onto the stack
				operandStack.push(result);

		}

		postfix->pop();

	}

	// if there is only one value in the stack
	if (operandStack.size() == 1) {

		// that is the result of the calculation
		return operandStack.top();

		// otherwise, there are more values in the stack
	} else {

		// error, the user input has too many values
		return -1;

	}

}

void assignVar(string str) {

	string varName = "";
	string expression = "";
	bool hasEqual = false;

	for (int i = 3; i < str.length(); i++) {

		if (isalpha(str.at(i)) && !hasEqual) {

			while (i < str.length() && isalpha(str.at(i))) {
				varName = varName + str.at(i);
				++i;
			}

		} else if (str.at(i) == '=' && !hasEqual) {

			hasEqual = true;

		} else if (hasEqual) {

			expression = expression + str.at(i);

		} else {
			//nothing
		}

	}

	list<Token> *varToken = stringToTokenList(expression);

	queue<Token> *revPol = shuntingYard(varToken);

	double answer = calculate(revPol);

	varVals[varName] = answer;

}

int main() {

	varVals["Pi"] = M_PI;
	varVals["e"] = M_E;

	string str;
	int x = 0;

	while (x == 0) {

		DBZ = false;
		UDV = false;

		getline(cin, str);

		if (str == "quit") {

			x = 1; break;

		} else if (str.compare(0, 3, "let") == 0) {

			assignVar(str);
			//cout << "let" << endl;

		} else {

			list<Token> *tokens = stringToTokenList(str);

			queue<Token> *postfix = shuntingYard(tokens);

			double answer = calculate(postfix);

			if (!DBZ && !UDV) {
				cout << answer << endl;
			}

		}

	}

	return 0;

}
