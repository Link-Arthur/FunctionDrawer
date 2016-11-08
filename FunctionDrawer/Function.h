#pragma once

#include"Expression.h"
#include<ASNET.h>

namespace Function {

	static float WidthBlock = 0.02f;
	static float HeightBlock = 0.02f;

	class Function {
	private:
		Expression* expression;
		std::vector<ASNET::Graph::Point> points;
	public:
		

		Function();

		void Set(string str);

		auto Ans(float x)->float;

		bool IsExpression();

		void ComputePoints(ASNET::Graph::Size target);

		void Draw(ASNET::Graph::Direct3D::GraphDirect3D* graph);
	};

}