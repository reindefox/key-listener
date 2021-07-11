#include "listener.h"

HHOOK hKeyboardHook;

LRESULT CALLBACK keyboardEvent(int nCode, WPARAM wParam, LPARAM lParam) {
	if ((nCode == HC_ACTION && wParam == WM_SYSKEYDOWN) || wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT hookKey = *((KBDLLHOOKSTRUCT*)lParam);

		// Here we get the key code of any pressed key

		switch (hookKey.vkCode) {
		default:
			break;
		}
	}

	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

DWORD WINAPI keyHook(LPVOID lpParm) {
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	if (!hInstance) {
		hInstance = LoadLibrary((LPCWSTR)lpParm);
		return 1;
	}

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)keyboardEvent, hInstance, NULL);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hKeyboardHook);

	return 0;
}

int main(int argc, char** argv) {
	HANDLE hThread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)keyHook, (LPVOID)argv[0], NULL, nullptr);

	if (hThread) {
		WaitForSingleObject(hThread, INFINITE);
	}
	else {
		return 1;
	}
}