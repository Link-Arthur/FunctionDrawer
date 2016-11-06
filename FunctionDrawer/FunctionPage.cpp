#include "FunctionPage.h"

Function::MainWindow::MainWindow()
{
	std::cout << "Please use the std expression." << endl;
	std::cout << "Such as 1--1 is not support" << endl;
	std::cout << "Such as 1x+2 is not support" << std::endl;
	Width = width;
	Height = height;
	IcoName = L"";
	Title = L"MainWindow";
	Initalize();

	dpiX = Graph->GetDpiX();
	dpiY = Graph->GetDpiY();

	realwidth = dpiX / 96.f*width;
	realheight = dpiY / 96.f*height;
}

void Function::MainPage::ComputeFunction()
{
	string str;
	for (size_t i = 0; i < TextBox.size(); i++)
		str += (char)(TextBox[i]);
	function.Set(str);
	if (!function.IsExpression()) return;
	ClearSurfaceAndRenderAxis();
	function.DrawSelf(Surface);
}

void Function::MainPage::ClearSurfaceAndRenderAxis()
{
	float width = Surface->GetWidth();
	float height = Surface->GetHieght();
	ASNET::Graph::Size origin = D2D1::SizeF(width / 2.f, height / 2.f);
	Surface->Clear();
	for (int i = 1; i <= width; i++)
		Surface->SetPixel(i, (int)origin.height, D2D1::ColorF::Black);
	for (int i = 1; i <= height; i++)
		Surface->SetPixel((int)origin.width, i, D2D1::ColorF::Black);
	Surface->Flush();
}

auto Function::MainPage::FloatToString(float value) -> std::wstring
{
	int val = (int)value;
	std::wstring tmp;
	std::wstring out;
	while (val) {
		tmp += (val % 10) + 48;
		val /= 10;
	}
	for (int i = tmp.size() - 1; i >= 0; i--) {
		out += tmp[i];
	}
	return out;
}

void Function::MainPage::OnInitalize(void * sender)
{
	ParentGraph->LoadFont(Consolas, L"Consolas", fontsize);
	ParentGraph->LoadImageSurface(D2D1::SizeF((float)width, (float)height), Surface);

}

void Function::MainPage::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	graph->DrawImageSurface(Surface, D2D1::RectF(0, 0, (float)width, (float)height));
	std::wstring OutBox = L"Function: " + TextBox;
	std::wstring FPSBox = L"FPS: " + FloatToString(graph->FPS());
	graph->DrawWord(OutBox, D2D1::RectF(0, 0, (float)OutBox.length() * 7.f, fontsize), Consolas);
	graph->DrawWord(FPSBox, D2D1::RectF(0, (float)height - fontsize, (float)FPSBox.length()*7.f, (float)height), Consolas);
}

void Function::MainPage::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
{
	MainWindow* window = (MainWindow*)sender;
	IsCapsLock = window->GetKeyState(ASNET::Keycode::CapsLock);
	IsShift = window->GetKeyState(ASNET::Keycode::Shift);
	if (e->keycode >= ASNET::Keycode::A && e->keycode <= ASNET::Keycode::Z) {
		if (e->keycode != ASNET::Keycode::X) return;
		bool IsBig = IsCapsLock^IsShift;
		if (IsBig) TextBox += (wchar_t)e->keycode;
		else TextBox += (wchar_t)((int)e->keycode + 32);
		ComputeFunction();
		return;
	}
	if (e->keycode >= ASNET::Keycode::Num0 && e->keycode <= ASNET::Keycode::Num9) {
		if (IsShift) {
			if (e->keycode == ASNET::Keycode::Num9) TextBox += '(';
			if (e->keycode == ASNET::Keycode::Num0) TextBox += ')';
			if (e->keycode == ASNET::Keycode::Num8) TextBox += '*';
			if (e->keycode == ASNET::Keycode::Num6) TextBox += '^';
			if (e->keycode == ASNET::Keycode::Num5) TextBox += '%';
		}
		else TextBox += (wchar_t)(e->keycode); 
		ComputeFunction();
		return;
	} 
	if (e->keycode >= ASNET::Keycode::Numpad0 && e->keycode <= ASNET::Keycode::Numpad9) {
		TextBox += (wchar_t)((int)e->keycode - (int)ASNET::Keycode::Numpad0 + 48);
		ComputeFunction();
		return;
	}
	if (e->keycode == ASNET::Keycode::Backspace) {
		if (TextBox.empty()) return;
		TextBox.pop_back();
		ComputeFunction();
		return;
	}
	if (e->keycode == ASNET::Keycode::Add) {
		TextBox += '+';
		ComputeFunction();
		return;
	}
	if (e->keycode == ASNET::Keycode::Subtract) {
		TextBox += '-';
		ComputeFunction();
		return;
	}
	if (e->keycode == ASNET::Keycode::Multiply) {
		TextBox += '*';
		ComputeFunction();
		return;
	}
	if (e->keycode == ASNET::Keycode::Divide) {
		TextBox += '/';
		ComputeFunction();
		return;
	}
	if ((int)e->keycode == 187) {
		if (IsShift) {
			TextBox += '+';
			ComputeFunction();
		}
		return;
	}
	if (e->keycode == ASNET::Keycode::Decimal) {
		TextBox += '.';
		ComputeFunction();
		return;
	}
	if ((int)e->keycode == 189) {
		if (!IsShift) {
			TextBox += '-';
			ComputeFunction();
		}
		return;
	}
	if ((int)e->keycode == 190 && !IsShift) {
		TextBox += '.';
		ComputeFunction();
		return;
	}
}
