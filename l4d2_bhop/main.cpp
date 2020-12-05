#include <Windows.h>

auto WINAPI bhop(const HMODULE h_module)
{
	const auto module_base = reinterpret_cast<DWORD>(GetModuleHandle(L"client.dll"));

	for (;;)
	{
		const auto local_player = *reinterpret_cast<DWORD*>(module_base + 0x71A044);

		if(local_player)
		{
			const auto flags = *reinterpret_cast<int*>(local_player + 0xF0);

			if (GetAsyncKeyState(VK_SPACE) && flags == 129 || flags == 131 || flags == 641 || flags == 643)
				*reinterpret_cast<int*>(module_base + 0x739948) = 5;
			else
				*reinterpret_cast<int*>(module_base + 0x739948) = 4;
		}
		if (GetAsyncKeyState(VK_DELETE))
		{
			Beep(150, 500);
			FreeLibraryAndExitThread(h_module, 0);
		}
		Sleep(10);
	}
}

auto APIENTRY dll_main(const HMODULE h_module)
{
	Beep(50, 500);
	CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(bhop), h_module, 0, nullptr));
}
