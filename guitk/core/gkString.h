#pragma once
#include <string>
#include <tchar.h>

namespace guitk {

#ifdef  _UNICODE
	typedef std::wstring String;

#else // !_UNICODE
	typedef std::string String;

#endif // _UNICODE

} // guitk
