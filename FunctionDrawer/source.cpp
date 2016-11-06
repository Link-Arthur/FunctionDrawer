#include"FunctionPage.h"

using namespace Function;

MainWindow* Window = new MainWindow();

int main() {
	Window->AddPage(new MainPage());
	Window->ShowPage(0);
	Window->Run();
	Window->Release();
}