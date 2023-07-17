
#include "cio.h"
// Console functions/logging

HANDLE CON, _HEAP;
FILE*STDOUT,*LOG;
HWND hCon;
#if !NO_LOGGING
wlog(cstr s, ...)
{
	va_list va;
	va_start(va, s);
	int retval = vfprintf(LOG, s, va);
	va_end(va);
	fflush(LOG); // immediately show in eclipse
	return retval;
}
#endif
#if 0
cprintf(cstr s, ...)
{
	va_list va;
	va_start(va, s);
	uint retval = vfprintf(STDOUT, s, va);
	va_end(va);
	return retval;
}
#else
#define cprintf
#endif

setscrsize_auto(u16 w, u16 h) // i hate this
{
	RECT oldsize;
	dd retval;
	if (retval = setscrsize(w, h)) // @suppress("Assignment in condition")
	{
		RECT newsize;
		// WHY DOESN'T THIS UPDATE INSTANTLY WHEN EXECUTING OR WAIT WHEN IT PERFORMS!!!!?!?!?!
		dd DELAY = 0;
		do {
			GetWindowRect(hCon, &newsize);
			Sleep(1);
			DELAY++;
		} while(
			oldsize.left == newsize.left &&
			oldsize.right == newsize.right &&
			oldsize.top == newsize.top &&
			oldsize.bottom == newsize.bottom
		);
		if (DELAY > 1)
			wlog("SCREEN BUFFER UPDATING LATE!!! (%u CHECKS)\n",DELAY);
		return retval;
	}
	return 0;
}
// use when user prefers to resize or whatever
// above was created to deal with window
// centering not working because of
// screen buffer not changing immediately
// or function waiting until it finally does it
setscrsize(u16 w, u16 h)
{
	RECT oldsize;
	GetWindowRect(hCon, &oldsize);
	{
		// if size is the same
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(CON, &csbi);
		if (w == csbi.dwSize.X && h == csbi.dwSize.Y) return 0;
	}
	SMALL_RECT sr = {0, 0, w, h};
	if (SetConsoleWindowInfo(CON, 1, &sr))
		return SetConsoleScreenBufferSize(CON, (COORD){w+1, h+1});
	return 0;
}
centerw()
{
	RECT r;
	GetWindowRect(hCon, &r);
	SetWindowPos(hCon, 0,
		(GetSystemMetrics(SM_CXSCREEN) - (r.right - r.left)) >> 1,
		(GetSystemMetrics(SM_CYSCREEN) - (r.bottom - r.top)) >> 1,
		0, 0, SWP_NOSIZE);
}
char io_w[2] = "w";
u16 origattr = CONCOLOR(C_BLACK,C_GRAY);
// initialize console window and properties
initw()
{
	LOG = stderr;
	if (!_isatty(fileno(LOG)))
		freopen_s(0,"NUL",io_w,LOG);
	wlog("WIDE Initialization\n");
	hCon = GetConsoleWindow();
	// supports launch from command prompt or my IDE or explorer
	// so console will always appear or use the one already open
	if (!IsWindow(hCon) && !_isatty(fileno(stdout)))
		AllocConsole();
	else
		ShowWindow(hCon, SW_SHOW);
	DWORD unused;
	ReadConsoleOutputAttribute(CON, &origattr, 1, (COORD){0, 0}, &unused);
	if (freopen_s(&STDOUT,"CONOUT$",io_w,stdout)) return;
	wlog("Setting console info\n");
	u32 w = 80,
		h = 30;
	CON = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
			CONSOLE_TEXTMODE_BUFFER, 0);
	SetConsoleActiveScreenBuffer(CON);
	SetConsoleScreenBufferSize(CON, (COORD){w*2, h*2}); // why
	setscrsize_auto(w, h);
	if (!SetConsoleCtrlHandler(ctrlCatch,1)) wlog("Unable to set control key handler.");
	SetConsoleMode(CON,
		0x20 | // ENABLE_INSERT_MODE
		ENABLE_MOUSE_INPUT |
		ENABLE_PROCESSED_INPUT |
		ENABLE_WINDOW_INPUT |
		8 // DISABLE_NEWLINE_AUTO_RETURN // NOT EVEN WORKING!!
	);
	SetConsoleTitleA("WIDE");
	centerw();
	return 0;
}




