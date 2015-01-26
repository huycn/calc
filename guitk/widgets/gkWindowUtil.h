#pragma once
#include <Windows.h>

#ifndef GET_X_LPARAM
inline int GET_X_LPARAM(LPARAM lParam) {
	return (short)LOWORD(lParam);
}
#endif

#ifndef GET_Y_LPARAM
inline int GET_Y_LPARAM(LPARAM lParam) {
	return (short)HIWORD(lParam);
}
#endif
