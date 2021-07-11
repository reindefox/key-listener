#pragma once

#include <Windows.h>
#include <WinUser.h>

LRESULT CALLBACK keyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI keyHook(LPVOID lpParm);