#include "Expression.h"





auto Function::Expression::StringToFloat(string str) -> float
{
	float ans = 0;
	size_t pos = 0;
	for (pos = 0; pos < str.length(); pos++) {
		if (str[pos] == '.') break;
		ans = ans * 10 + str[pos] - '0';
	}
	pos++;
	float i = 0.1f;
	for (pos; pos < str.length(); pos++) {
		if (str[pos] == '.') return NAN;
		ans += i*(float)(str[pos] - '0');
		i *= 0.1f;
	}
	return ans;
}

auto Function::Expression::ComputeExpression(float left, float right, char op) -> float
{
	if (op == OperatorFactory::Private::plus) return left + right;
	if (op == OperatorFactory::Private::minus) return left - right;
	if (op == OperatorFactory::Private::division && right != 0) return left / right;
	if (op == OperatorFactory::Private::multiplication) return left*right;
	if (op == OperatorFactory::Private::pow) return pow(left, right);
	return NAN;
}

Function::Expression::Expression(std::string value)
{
	src = value;
	IsExpression = false;
	ExpressionQueue = ToExpressionQueue();
}



#define STACKDEBUG if (Stack.empty()){std::cout<<"Error: Expression Is Not Right"<<std::endl; IsExpression=false; return queue<string>();};
#define OUTDEBUG if (Stack.top()=='('){std::cout<<"Error: Expression Is Not Right"<<std::endl; IsExpression=false; return queue<string>();};



auto Function::Expression::ToExpressionQueue() -> queue<string>
{
	queue<string> out;

	stack<char> Stack;

	for (size_t pos = 0; pos < src.length(); pos++) {
		char value = src[pos];
		if (value == ' ') continue;
		if (OperatorFactory::IsNumber(value) || value == 'x') {
			string num = ""; num += value;
			if (value == 'x') { out.push("x"); continue; }
			while (pos + 1 < src.length() && OperatorFactory::IsNumber(src[pos + 1])) { pos++; num += src[pos]; }
			out.push(num); continue;
		}
		if (OperatorFactory::IsOperator(value)) {
			//because is all from left to right
			int level = OperatorFactory::Level(value);
			while (!Stack.empty() && level <= OperatorFactory::Level(Stack.top())) {
				string op = ""; op += Stack.top();
				out.push(op);
				Stack.pop();
			}
			Stack.push(value); continue;
		}
		if (value == '(') { Stack.push(value); continue; }
		if (value == ')') {
			while (!Stack.empty() && Stack.top() != '(') {
				string op = ""; op += Stack.top();
				out.push(op);
				Stack.pop();
			}
			STACKDEBUG;
			Stack.pop(); continue;
		}
	}

	while (!Stack.empty()) {
		OUTDEBUG;
		string op = ""; op += Stack.top();
		out.push(op);
		Stack.pop();
	}
	IsExpression = true;
	return out;
}


#undef STACKDEBUG
#undef OUTDEBUG


#define EXPRESSIONDEBUG {std::cout<<"GetValue: Expression Is Not Right."<<std::endl; IsExpression=false; return NAN;}

auto Function::Expression::ToValue(float x) -> float
{
	if (!IsExpression) return false;
	stack<float> Stack;
	queue<string> ExpressionQueue = this->ExpressionQueue;
	if (ExpressionQueue.empty()) EXPRESSIONDEBUG;
	while (!ExpressionQueue.empty()) {
		string value = ExpressionQueue.front();
		ExpressionQueue.pop();
		if (OperatorFactory::IsOperator(value[0])) {
			if (Stack.size() < 2) EXPRESSIONDEBUG;
			float left = Stack.top(); Stack.pop();
			float right = Stack.top(); Stack.pop();
			float result = ComputeExpression(left, right, value[0]);
			if (result == NAN) EXPRESSIONDEBUG;
			Stack.push(result);
		}else {
			float number = Expression::StringToFloat(value);
			if (number == NAN && value[0] != 'x')  EXPRESSIONDEBUG;
			if (value[0] == 'x') number = x;
			Stack.push(number);
		}
	}

	if (Stack.size() > 1) EXPRESSIONDEBUG;
	IsExpression = true;
	return Stack.top();
	
}

#undef EXPRESSIONDEBUG



int Function::OperatorFactory::Level(char op)
{
	for (size_t i = 0; i < Private::SignCount; i++) {
		if (op == Private::Collection[i]) return Private::Level[i];
	}
	return 0;
}

bool Function::OperatorFactory::IsOperator(char op)
{
	for (size_t i = 0; i < Private::SignCount; i++) {
		if (op == Private::Collection[i]) return true;
	}
	return false;
}

bool Function::OperatorFactory::IsNumber(char op)
{
	if (op >= '0' && op <= '9') return true;
	if (op == '.') return true;
	return false;
}

Function::OperatorFactory::Private::Sign Function::OperatorFactory::ToSign(char op)
{
	return Private::Sign(op);
}
