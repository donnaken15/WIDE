
#include "_config.h"
#include "common.h"

#include <stdio.h>
#include <windows.h>
#include <unistd.h>

typedef struct _CONSOLE_SCREEN_BUFFER_INFOEX {
	ULONG		cbSize;
	COORD		dwSize;
	COORD		dwCursorPosition;
	WORD		wAttributes;
	SMALL_RECT	srWindow;
	COORD		dwMaximumWindowSize;
	WORD		wPopupAttributes;
	BOOL		bFullscreenSupported;
	COLORREF	ColorTable[16];
} CONSOLE_SCREEN_BUFFER_INFOEX, *PCONSOLE_SCREEN_BUFFER_INFOEX;
typedef struct _CONSOLE_FONT_INFOEX {
	ULONG cbSize;
	DWORD nFont;
	COORD dwFontSize;
	UINT  FontFamily;
	UINT  FontWeight;
	WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
// WHERE ARE THESE DECLARATIONS
HWND WINAPI GetConsoleWindow();
BOOL WINAPI SetConsoleScreenBufferInfoEx(HANDLE, PCONSOLE_SCREEN_BUFFER_INFOEX);
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE, BOOL, PCONSOLE_FONT_INFOEX);
//BOOL WINAPI WriteConsoleOutputCharacter(HANDLE, LPCSTR, DWORD, COORD, LPDWORD);
BOOL WINAPI WriteConsoleOutputAttribute(HANDLE, const WORD*, DWORD, COORD, LPDWORD);

#ifndef NO_LOGGING
#define NO_LOGGING 1
#endif

BOOL WINAPI ctrlCatch(DWORD signal);

extern HANDLE CON, _HEAP;
extern FILE*LOG;
extern HWND hCon;
#if !NO_LOGGING
#undef wlog // thanks eclipse
wlog(cstr s, ...);
#else
#define wlog
#endif
extern u16 origattr;
setscrsize(u16 w, u16 h);
centerw();
initw();
// <wincon.h:37> didn't see this
enum KEventFlags {
	CTRLKST8_RALT = 1, // ????
	CTRLKST8_LALT = 2,
	CTRLKST8_RCTRL = 4,
	CTRLKST8_LCTRL = 8,
	CTRLKST8_SHIFT = 16,
	CTRLKST8_NUMLOCK = 32,
	CTRLKST8_SCRLOCK = 64,
	CTRLKST8_CAPLOCK = 128,
	CTRLKST8_NOTCHAR = 256, // what do i do with this?????
	// appears on right side control buttons and stuff like pageup/pagedown
};
enum MEventFlags {
	MEVT_NONE   = 0,
	MEVT_LEFT   = 1,
	MEVT_RIGHT  = 2,
	MEVT_MIDDLE = 4,
	MEVT_SCROLLUP = 7864320,
	MEVT_SCROLLDOWN = 4287102976
};
enum CONCOLORS {
	// TIL colors are indexed based on I1R1G1B1
	// IT LITERALLY SAYS IT ON MSDN
	// but who's going to understand it
	C_BLACK,
	C_DKBLUE,
	C_DKGRN,
	C_DKCYAN,
	C_DKRED,
	C_DKPRPL,
	C_DKYLW,
	C_GRAY,
	C_DKGRAY,
	C_BLUE,
	C_GREEN,
	C_CYAN,
	C_RED,
	C_PRPL,
	C_YELLOW,
	C_WHITE
};
#define CONCOLOR(b,f) ((b<<4)|f)


#ifndef CIO_H_
#define CIO_H_
#endif//CIO_H_
