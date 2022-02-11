	#include "DebugApplication.h"


int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	int exitCode = 0;

	{
	DebugApplication app(hInstance);


	exitCode = app.Run();
	}

	return exitCode;
}