#include "Function.h"

void Function::Function::Set(string str)
{
	if (expression) { delete expression; expression = nullptr; }
	expression = new Expression(str);
}

auto Function::Function::Ans(float x) -> float
{
	return expression->ToValue(x);
}

bool Function::Function::IsExpression()
{
	if (Ans(0) == NAN) return false;
	return true;
}

void Function::Function::DrawSelf(ASNET::Graph::ImageSurface * Surface)
{
	float width = Surface->GetWidth();
	float heigh = Surface->GetHieght();
	ASNET::Graph::Size origin = D2D1::SizeF(width / 2.f, heigh / 2.f);
	//enum the pixel 
	
	//what can i write ?

	
}
