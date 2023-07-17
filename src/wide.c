
/*---------------------------\
*        _____ ____   _____  |
| |    |   |   |   \  |      |
| | /\ |   |   |    | |---   |
| |/  \| __|__ |___/  |____  |
|                            |
| Wesley's Intricate         |
| Development Environment    |
|                            *
\---------------------------*/

#include "_config.h"

#include <windows.h>
#include <stdlib.h>
#include <stdarg.h>
#include "wide.h"
#include "cio.h"

int timeBeginPeriod(dd);
int timeEndPeriod(dd);
#define clockresBegin __asm__ ( /*WHY*/ \
						"	push $0x1\n" \
						"	call timeBeginPeriod\n" \
						:: \
					);
#define clockresEnd __asm__ ( \
						"	push $0x1\n" \
						"	call timeEndPeriod\n" \
						:: \
					);

char do_exit = 0;
BOOL WINAPI ctrlCatch(ul signal)
{
	switch (signal)
	{
	case CTRL_C_EVENT:
		do_exit = 1;
		break;
	}
	wlog("Got signal: %08X\n",signal);
	return 1;
}
int argc; char**argv; void*env;
main()
{
	const uint maxEventCount = 128;
	INPUT_RECORD IR[maxEventCount];
	CONSOLE_SCREEN_BUFFER_INFO lastcsbi, newcsbi;
	GetConsoleScreenBufferInfo(CON, &lastcsbi);
	//__getmainargs(&argc,&argv,&env,0);
	int test3 = 0;
	char test4[32];
	u16 test5[32];
	memset(test4, 0, 32);
	memset(test5, 0, 32<<1);
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = 0;
	ci.dwSize = 1;
	SetConsoleCursorInfo(CON, &ci);
	COORD test6 = {5,0};
	wlog("TEXT?\n");
	while (!do_exit)
	{
		// test
		int test2 = 0;
		WriteConsoleOutputCharacter(CON, test4, 32, test6, &test2);
		WriteConsoleOutputAttribute(CON, test5, 32, test6, &test2);
		test6:
		if (test3 < 32)
		{
			test4[test3 & 31] = 'A' + (test6.Y);
			test5[test3 & 31] = CONCOLOR(C_DKBLUE, C_YELLOW) | COMMON_LVB_GRID_RVERTICAL;
		}
		else if (test3 >= 32 && test3 < 64)
		{
			test4[test3 & 31] = '\0';
			test5[test3 & 31] = origattr;
		}
		else if (test3 >= 64)
			{ test3 = 0; test6.Y = (test6.Y + 1) % 26; goto test6; }
		test3++;
		// get user input
#if 0
		ul readevts;
		ReadConsoleInputExA(GetStdHandle(STD_INPUT_HANDLE), IR, maxEventCount, &readevts, 2);
		//wlog("events got: %u\n", readevts);
		for (ul i = 0; i < readevts; i++)
		{
			INPUT_RECORD*k = &IR[i];
			switch (k->EventType)
			{
				case KEY_EVENT:
				{
					break;
				}
				case MOUSE_EVENT:
				{
					break;
				}
				case WINDOW_BUFFER_SIZE_EVENT:
				{
					break;
				}
				case FOCUS_EVENT:
				{
					break;
				}
				case MENU_EVENT:
				{
					break;
				}
			}
#pragma region report events
#if 0
			switch (k->EventType)
			{
			case KEY_EVENT:
				wlog("KEY: pressed '%c'/%3u %s (CTRL: %3u) x%3u, %3u ?\n",
					k->Event.KeyEvent.uChar,
					k->Event.KeyEvent.wVirtualKeyCode,
					k->Event.KeyEvent.bKeyDown ? "down" : "up  ",
					k->Event.KeyEvent.dwControlKeyState,
					k->Event.KeyEvent.wRepeatCount,
					k->Event.KeyEvent.wVirtualScanCode);
				break;
			case MOUSE_EVENT:
				wlog("MOUSE: %3u (CTRL: %3u) (%4u,%4u) %u\n",
					k->Event.MouseEvent.dwButtonState,
					k->Event.MouseEvent.dwControlKeyState,
					k->Event.MouseEvent.dwMousePosition.X,
					k->Event.MouseEvent.dwMousePosition.Y,
					k->Event.MouseEvent.dwEventFlags);
				break;
			case WINDOW_BUFFER_SIZE_EVENT:
				wlog("BUFFER SIZE: (%4u,%4u)\n",
					k->Event.WindowBufferSizeEvent.dwSize.X,
					k->Event.WindowBufferSizeEvent.dwSize.Y);
				break;
			case FOCUS_EVENT:
				wlog("FOCUS: %sfocused\n", k->Event.FocusEvent.bSetFocus ? "  " : "un");
				break;
			case MENU_EVENT:
				wlog("MENU: %u\n", k->Event.MenuEvent.dwCommandId);
				break;
			}
#endif
		}
#endif

		// minimize screen buffer to window because we're not using any other space than that
		GetConsoleScreenBufferInfo(CON, &newcsbi);
		if (lastcsbi.dwSize.X != newcsbi.dwSize.X ||
			lastcsbi.dwSize.Y != newcsbi.dwSize.Y)
		{
			u32 w = newcsbi.srWindow.Right - newcsbi.srWindow.Left,
				h = newcsbi.srWindow.Bottom - newcsbi.srWindow.Top;
			setscrsize(w,h);
			memcpy(&lastcsbi, &newcsbi, sizeof(CONSOLE_SCREEN_BUFFER_INFO));
		}

		clockresBegin;
		Sleep(16);
		clockresEnd;
	}
	FreeConsole();
	fcloseall();
	return 0;
}
// see ll.asm for entry point

