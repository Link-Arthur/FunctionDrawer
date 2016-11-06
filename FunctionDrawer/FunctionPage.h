#pragma once
#include<ASNET.Window.h>

#include<string>

#include"Function.h"
using namespace std;

namespace Function {

	static int width = 800;
	static int height = 600;
	static float dpiX;
	static float dpiY;
	static float realwidth;
	static float realheight;
	static float fontsize = 12;


	class MainWindow :public ASNET::Window {
	private:
	public:
		MainWindow();
	}; 

	class MainPage :public ASNET::Page::Page {
	private:
		//Resource
		ASNET::Graph::Font* Consolas;
		ASNET::Graph::ImageSurface* Surface;
	private:
		bool     IsCapsLock;
		bool     IsShift;
		wstring  TextBox;

		Function function;
	private:
		void ComputeFunction();
		void ClearSurfaceAndRenderAxis();
		auto FloatToString(float value)->std::wstring;
	protected:
		void OnInitalize(void* sender)override;
		void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
		void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e)override;
	public:
		MainPage() = default;
	};


}