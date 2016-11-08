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

void Function::Function::ComputePoints(ASNET::Graph::Size target)
{
	//one points 
	points.clear();
	//points.push_back(D2D1::Point2F(-1, Ans(-1)/HeightBlock));
	for (size_t i = 0; i <= target.width; i++) {
		float realx = (float)i;
		float realy = Ans(realx*WidthBlock)/HeightBlock;
		points.push_back(D2D1::Point2F(realx, realy));
		if (realy > target.height) break;
		if (realy < 0) break;
	}
}






void Function::Function::Draw(ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	if (!IsExpression()) return;

	for (size_t i = 1; i < points.size(); i++) {
		graph->DrawLine(points[i - 1], points[i], D2D1::ColorF::Red, 4);
	}

}

