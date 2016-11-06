#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>


/*
the operator we can use:
	+,-,*,/,^,(,),%

//the level of operator 
1.^
2. * / %
3. + - 
*/

using namespace std;

namespace Function {

	

	namespace OperatorFactory{
		namespace Private {
			enum Sign : char {
				plus = '+',
				minus = '-',
				division = '/',
				multiplication = '*',
				modulus = '%',
				pow = '^'
			};
			

			static const Sign Collection[10] = { plus,minus,division,multiplication,modulus,pow };

			static const int  Level[10] = { 1,1,2,2,2,3 };

			static const int  SignCount = 6;
		}
		static int  Level(char op);

		static bool IsOperator(char op);
		
		static bool IsNumber(char op);

		static Private::Sign ToSign(char op);
	};

	 
	class Expression {
	private:
		std::string src;

		friend class Function;

		static auto StringToFloat(string str)->float;

		static auto ComputeExpression(float left, float right, char op)->float;
	public:
		Expression() = default;

		Expression(std::string value = "");

		auto ToExpressionQueue()->queue<string>;

		auto ToValue(float x)->float;
	};

	

}
