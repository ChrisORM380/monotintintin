#include "monotintintin.h"

BOOL
CALLBACK
MsgBoxRefreshWndProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
)
{
	UNREFERENCED_PARAMETER(lParam);
	RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
	return TRUE;
}

BOOL
CALLBACK
MsgBoxWndProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
)
{
	UNREFERENCED_PARAMETER(lParam);
	EnableWindow(hwnd, FALSE);
	SetWindowTextW(hwnd, L"really?");
	return TRUE;
}

VOID
WINAPI
MsgBoxCorruptionThread(
	_In_ HWND hwndMsgBox
)
{
	BITMAPINFO bmi = { 0 };
	HANDLE hHeap;
	PRGBQUAD prgbPixels;
	HDC hdcMsgBox;
	HDC hdcTempMsgBox;
	HBITMAP hbmMsgBox;
	RECT rcMsgBox;
	INT w;
	INT h;

	GetWindowRect(hwndMsgBox, &rcMsgBox);
	w = rcMsgBox.right - rcMsgBox.left;
	h = rcMsgBox.bottom - rcMsgBox.top;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

	hHeap = GetProcessHeap();
	prgbPixels = (PRGBQUAD)HeapAlloc(hHeap, 0, w * h * sizeof(RGBQUAD));

	hdcMsgBox = GetDC(hwndMsgBox);
	hdcTempMsgBox = CreateCompatibleDC(hdcMsgBox);
	hbmMsgBox = CreateDIBSection(hdcMsgBox, &bmi, 0, &prgbPixels, NULL, 0);
	SelectObject(hdcTempMsgBox, hbmMsgBox);

	for (;; )
	{
		for (INT32 i = 0; i < w * h; i++)
		{
			prgbPixels[i].rgb = (XorYeet32() & 0xff) * (XorYeet32() & 0x10101);
		}

		BitBlt(hdcMsgBox, 0, 0, w, h, hdcTempMsgBox, 0, 0, SRCCOPY);
		EnumChildWindows(hwndMsgBox, MsgBoxRefreshWndProc, 0);
		Sleep(10);
	}
}

LRESULT
CALLBACK
MsgBoxHookProc(
	_In_ INT nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	HWND hwndMsgBox;

	if (nCode == HCBT_ACTIVATE)
	{
		hwndMsgBox = (HWND)wParam;

		ShowWindow(hwndMsgBox, SW_SHOW);

		EnumChildWindows(hwndMsgBox, MsgBoxWndProc, 0);
		CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MsgBoxCorruptionThread, hwndMsgBox, 0, NULL);

		return 0;
	}

	return CallNextHookEx(hMsgHook, nCode, wParam, lParam);
}

VOID
WINAPI
MessageBoxThread(VOID)
{
	hMsgHook = SetWindowsHookExW(WH_CBT, MsgBoxHookProc, NULL, GetCurrentThreadId());
	MessageBoxW(NULL, L"really?", L"really?", MB_ABORTRETRYIGNORE | MB_ICONERROR);
	UnhookWindowsHookEx(hMsgHook);
}
VOID
WINAPI
CursorDraw(VOID)
{
	CURSORINFO curInf = { sizeof(CURSORINFO) };

	for (;; )
	{
		GetCursorInfo(&curInf);

		for (INT i = 0; i < (INT)(XorYeet32() % 5 + 1); i++)
		{
			DrawIcon(hdcDesktop, XorYeet32() % (rcScrBounds.right - rcScrBounds.left - GetSystemMetrics(SM_CXCURSOR)) - rcScrBounds.left,
				XorYeet32() % (rcScrBounds.bottom - rcScrBounds.top - GetSystemMetrics(SM_CYCURSOR)) - rcScrBounds.top, curInf.hCursor);
		}
		DestroyCursor(curInf.hCursor);
		Sleep(XorYeet32() % 11);
	}
}