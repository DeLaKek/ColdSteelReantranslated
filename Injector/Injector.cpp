#include <iostream>
#include <string>
#include <windows.h>
#include <tlhelp32.h>

int main(int argc, char** argv)
{
	std::wstring gamePathStr;
	std::string dllPathStr;
	
	std::cout << "Enter the path to the game executable (ed8.exe): ";
	std::getline(std::wcin, gamePathStr);

	std::cout << "Enter the path to the mod DLL: ";
	std::getline(std::cin, dllPathStr);

	const wchar_t *gamePath = gamePathStr.c_str();
	const char *dllPath = dllPathStr.c_str();
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess((LPCWSTR)gamePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		std::cout << "Starting the game failed! Error: " << GetLastError() << std::endl;
		return 1;
	}
	
	HANDLE snapshot = 0;
	PROCESSENTRY32 pe32 = {0};
	DWORD exitCode = 0;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(snapshot, &pe32);

	do
	{
		if (wcscmp(pe32.szExeFile, L"ed8.exe") == 0)
		{
			HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, true, pe32.th32ProcessID);
			void *lpBaseAddress = VirtualAllocEx(process, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
			WriteProcessMemory(process, lpBaseAddress, dllPath, strlen(dllPath) + 1, NULL);

			HMODULE kernel32base = GetModuleHandle(L"kernel32.dll");
			HANDLE thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(kernel32base, "LoadLibraryA"),
											   lpBaseAddress, 0, NULL);

			WaitForSingleObject(thread, INFINITE);
			GetExitCodeThread(thread, &exitCode);
			
			VirtualFreeEx(process, lpBaseAddress, 0, MEM_RELEASE);
			CloseHandle(thread);
			CloseHandle(process);
			break;
		}
	}
	while (Process32Next(snapshot, &pe32));

	return 0;
}