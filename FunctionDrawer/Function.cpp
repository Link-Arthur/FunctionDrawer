#include "Function.h"

Function::Function::Function()
{
	expression = nullptr;
}

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
	if (!expression) return false;
	return expression->IsExpression;
}


void Function::Function::DrawSelf(ASNET::Graph::ImageSurface * Surface)
{
	float width = Surface->GetWidth();
	float heigh = Surface->GetHieght();
	ASNET::Graph::Size origin = D2D1::SizeF(width / 2.f, heigh / 2.f);
	//enum the pixel 
	if (!IsExpression()) return;
	for (int i = 1; i <= width; i++) {
		Surface->SetPixel(i, Ans(i), D2D1::ColorF::Red);
	}
	//what can i write ?
	Surface->Flush();
}
