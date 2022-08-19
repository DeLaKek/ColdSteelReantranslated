#include <windows.h>

DWORD returnAddress = 0x656A06;
unsigned char *hookLocation = (unsigned char*)0x656A00;

//The "Haha..." I want to inject, with the header (only in voiced lines) and footer, as well as a pointer
unsigned char funnyTextVoiced[18] = {0x11, 0x9C, 0xC7, 0x00, 0x00, 0x48, 0x61, 0x68, 0x61,
							         0x2E, 0x2E, 0x2E, 0x02, 0x00, 0x1C, 0x1A, 0xE9, 0x03};
unsigned char funnyTextUnvoiced[13] = {0x48, 0x61, 0x68, 0x61, 0x2E, 0x2E, 0x2E,
									   0x02, 0x00, 0x1C, 0x1A, 0xE9, 0x03};
unsigned char *ptrLaugh;


__declspec(naked) void laughPrint()
{
	unsigned char *headerTemp;

	__asm
		mov dword ptr ss:[headerTemp], esi

	/*The voiced lines begin with a 5 byte header, of which the first byte is 0x11,
	  if it doesn't have a header, it's an unvoiced line*/

	if (*headerTemp == 0x11)
	{
		for (int i = 0; i < 5; i++)
			funnyTextVoiced[i] = *(unsigned char*)(headerTemp + i);
		ptrLaugh = (unsigned char*)&funnyTextVoiced;
	}
	else
		ptrLaugh = (unsigned char*)&funnyTextUnvoiced;

	__asm
	{
		mov dword ptr ss:[ebp-8], eax
		mov esi, dword ptr ss:[ptrLaugh]
		mov dword ptr ss:[ebp-4], esi
		jmp returnAddress
	}
}



BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	DWORD oldProtect;
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		VirtualProtect((void*)hookLocation, 6, PAGE_EXECUTE_READWRITE, &oldProtect);
		*hookLocation = 0xE9;
		*(DWORD*)(hookLocation + 1) = (DWORD)&laughPrint - ((DWORD)hookLocation + 5);
		*(hookLocation + 5) = 0x90;
	}

	return true;
}