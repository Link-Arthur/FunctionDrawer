#pragma once

#include"Expression.h"
#include<ASNET.h>

namespace Function {

	static float Block = 0.02f;

	class Function {
	private:
		Expression* expression;
	public:
		Function() = default;

		void Set(string str);

		auto Ans(float x)->float;

		bool IsExpression();

		void DrawSelf(ASNET::Graph::ImageSurface* Surface);
	};

}