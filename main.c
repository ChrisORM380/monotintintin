#include "monotintintin.h"

#pragma region Public Variables
HWND hwndDesktop;
HDC hdcDesktop;
RECT rcScrBounds;
HHOOK hMsgHook;
INT nCounter = 0;
bool hasPayloadsFinished = false;
#pragma endregion Public Variables

VOID
WINAPI
Initialize(VOID)
{
	HMODULE hModUser32 = LoadLibraryW(L"user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModUser32, "SetProcessDPIAware");
	if (SetProcessDPIAware)
		SetProcessDPIAware();
	FreeLibrary(hModUser32);

	hwndDesktop = HWND_DESKTOP;
	hdcDesktop = GetDC(hwndDesktop);

	SeedXorshift32((DWORD)__rdtsc());
	InitializeSine();
	EnumDisplayMonitors(NULL, NULL, &MonitorEnumProc, 0);
	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)TimerThread, NULL, 0, NULL));
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HANDLE hCursorDraw, hAudioThread, hGdiThread;

	Initialize();
	if (MessageBoxW(NULL, L"WARNING!\n\nYou have ran a Trojan known as monotintintin.exe, where unlike Monoxide.exe, doesn't have that full capacity to delete all of your data and your operating system.\n\nBUT... By continuing, you keep in mind that the creator will not be responsible for any damage caused by this trojan and it is highly recommended that you run this in a testing virtual machine where a snapshot has been made before execution for the sake of entertainment and analysis.\n\nAre you sure you want to run this?", L"Malware alert - monotintintin.exe [Monoxide by wipet, modded by ChrisRM_380]", MB_ICONWARNING | MB_YESNO) != IDYES)
		return FALSE;
	if (MessageBoxW(NULL, L"FINAL WARNING!!!\n\nEven though this Trojan doesn't have a lot of destructive potential, You might lose all of your unsaved data if you continue, from uncontrollably flashy lights and loud noises. The creator will not be responsible for any of the damage caused. This is not meant to be malicious but simply for entertainment and educational purposes.\n\nAre you sure you want to continue? This is your final chance to stop this program from execution. \nIf you run this, you might get a seizure. Loud noises & flashing lights ahead.", L"Final alert - monotintintin.exe [Monoxide by wipet, modded by ChrisRM_380]", MB_ICONWARNING | MB_YESNO) != IDYES)
		return FALSE;

	//Sleep(5000);
	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MessageBoxThread, NULL, 0, NULL));
	//Sleep(1000);

	hCursorDraw = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)CursorDraw, NULL, 0, NULL);

	CreateMutexW(NULL, TRUE, L"monotintintin.exe");

	pAudioSequences[0] = (AUDIO_SEQUENCE_PARAMS){ 49152, 49152 * 32, AudioSequence1,  NULL, NULL };
	pAudioSequences[1] = (AUDIO_SEQUENCE_PARAMS){ 8192,  8192 * 32, AudioSequence2,  NULL, NULL };
	pAudioSequences[2] = (AUDIO_SEQUENCE_PARAMS){ 8192,  8192 * 32, AudioSequence3,  NULL, NULL };
	pAudioSequences[3] = (AUDIO_SEQUENCE_PARAMS){ 16384, 16384 * 32, AudioSequence4,  NULL, NULL };
	pAudioSequences[4] = (AUDIO_SEQUENCE_PARAMS){ 8192,  8192 * 32, AudioSequence5,  NULL, NULL };
	pAudioSequences[5] = (AUDIO_SEQUENCE_PARAMS){ 16384,  16384 * 32, AudioSequence6,  NULL, NULL };
	pAudioSequences[6] = (AUDIO_SEQUENCE_PARAMS){ 9600, 9600 * 32, AudioSequence7,  NULL, NULL };
	pAudioSequences[7] = (AUDIO_SEQUENCE_PARAMS){ 49152, 49152 * 32, AudioSequence8,  NULL, NULL };
	pAudioSequences[8] = (AUDIO_SEQUENCE_PARAMS){ 49152, 49152 * 32, AudioSequence9,  NULL, NULL };
	pAudioSequences[9] = (AUDIO_SEQUENCE_PARAMS){ 10240,  10240 * 32, AudioSequence10, NULL, NULL };
	pAudioSequences[10] = (AUDIO_SEQUENCE_PARAMS){ 11025,  11025 * 32, AudioSequence11, NULL, NULL };
	pAudioSequences[11] = (AUDIO_SEQUENCE_PARAMS){ 9600,  9600 * 32, AudioSequence12, NULL, NULL };
	pAudioSequences[12] = (AUDIO_SEQUENCE_PARAMS){ 16384, 16384 * 32, AudioSequence13, NULL, NULL };
	pAudioSequences[13] = (AUDIO_SEQUENCE_PARAMS){ 49152, 49152 * 32, AudioSequence14, NULL, NULL };
	pAudioSequences[14] = (AUDIO_SEQUENCE_PARAMS){ 49152, 49152 * 32, AudioSequence15, NULL, NULL };
	pAudioSequences[15] = (AUDIO_SEQUENCE_PARAMS){ 49152, 49152 * 32, AudioSequence16, NULL, NULL };
	pAudioSequences[16] = (AUDIO_SEQUENCE_PARAMS){ 8192, 8192 * 32, AudioSequence17, NULL, NULL };
	pAudioSequences[24] = (AUDIO_SEQUENCE_PARAMS){ 38250, 38250 * 32, FinalAudioSequence, NULL, NULL };

	pGdiShaders[0] = (GDI_SHADER_PARAMS){ GdiShader1,  NULL,          PostGdiShader1 };
	pGdiShaders[1] = (GDI_SHADER_PARAMS){ GdiShader2,  NULL,          PostGdiShader2 };
	pGdiShaders[2] = (GDI_SHADER_PARAMS){ GdiShader3,  NULL,          PostGdiShader3 };
	pGdiShaders[3] = (GDI_SHADER_PARAMS){ GdiShader4,  NULL,          PostGdiShader2 };
	pGdiShaders[4] = (GDI_SHADER_PARAMS){ GdiShader5,  NULL,          PostGdiShader4 };
	pGdiShaders[5] = (GDI_SHADER_PARAMS){ GdiShader6,  NULL,          PostGdiShader2 };
	pGdiShaders[6] = (GDI_SHADER_PARAMS){ GdiShader7,  NULL,          PostGdiShader5 };
	pGdiShaders[7] = (GDI_SHADER_PARAMS){ GdiShader8,  PreGdiShader1, PostGdiShader6 };
	pGdiShaders[8] = (GDI_SHADER_PARAMS){ GdiShader9,  NULL,          NULL };
	pGdiShaders[9] = (GDI_SHADER_PARAMS){ GdiShader10, NULL,          NULL };
	pGdiShaders[10] = (GDI_SHADER_PARAMS){ GdiShader11, NULL,          NULL };
	pGdiShaders[11] = (GDI_SHADER_PARAMS){ GdiShader12, NULL,          NULL };
	pGdiShaders[12] = (GDI_SHADER_PARAMS){ GdiShader13, NULL,          NULL };
	pGdiShaders[13] = (GDI_SHADER_PARAMS){ GdiShader14, NULL,          PostGdiShader2 };
	pGdiShaders[14] = (GDI_SHADER_PARAMS){ GdiShader15, NULL,          NULL };
	pGdiShaders[15] = (GDI_SHADER_PARAMS){ GdiShader16, NULL,          NULL };
	pGdiShaders[16] = (GDI_SHADER_PARAMS){ GdiShader17, NULL,          NULL };
	pGdiShaders[17] = (GDI_SHADER_PARAMS){ GdiShader18, NULL,          NULL };
	pGdiShaders[18] = (GDI_SHADER_PARAMS){ GdiShader19, NULL,          NULL };
	pGdiShaders[19] = (GDI_SHADER_PARAMS){ GdiShader20, NULL,          PostGdiShader2 };
	pGdiShaders[20] = (GDI_SHADER_PARAMS){ GdiShader21, NULL,          PostGdiShader2 };
	pGdiShaders[24] = (GDI_SHADER_PARAMS){ FinalGdiShader, NULL, NULL };

	hAudioThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)AudioPayloadThread, NULL, 0, NULL);

	for (;; )
	{
		hGdiThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)GdiShaderThread, &pGdiShaders[XorYeet32() % 21], 0, NULL);
		WaitForSingleObject(hGdiThread, (XorYeet32() % 3) ? PAYLOAD_MS : ((XorYeet32() % 5) * (PAYLOAD_MS / 4)));
		CloseHandle(hGdiThread);

		if (/*nCounter >= ((180 * 1000) / TIMER_DELAY) ||*/ hasPayloadsFinished)
		{
			break;
		}
	}

	TerminateThread(hAudioThread, 0);
	CloseHandle(hAudioThread);

	TerminateThread(hCursorDraw, 0);
	CloseHandle(hCursorDraw);

	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)GdiShaderThread, &pGdiShaders[24], 0, NULL));
	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)AudioSequenceThread, &pAudioSequences[24], 0, NULL));
	Sleep(3000);
}