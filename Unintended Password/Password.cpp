#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"windows.h"
HHOOK hhook;
HWND hwnd_g;
char arr[]="0123456789QWERTYUIOPASDFGHJKLZXCVBNM";
char flag[]="VV88AA225599OOKKQQSSGG88OOQQ88KK88KK22AABB550099BB99GGGG4488QQQQ99WW88QQ";
LRESULT CALLBACK kbpr(int code, WPARAM wParam, LPARAM lParam)
{
	printf("%c",wParam);
	if(code<0)return CallNextHookEx(hhook, code, wParam, lParam);
	
	if(code==HC_ACTION)
	{
		for(int i=0;i<strlen(arr);i++)
		{
			if(arr[i]==wParam)
			{
				SendMessage(hwnd_g, WM_USER+1, 0, arr[ (i+5)%strlen(arr) ]);
				return 1;
			}
		}
	}
	
	return CallNextHookEx(hhook, code, wParam, lParam);
}

void __attribute__ ((constructor)) dsabshcgh()
{
    // Add code here
    hhook=SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)kbpr, 0,GetCurrentThreadId());
    if(hhook==NULL)exit(-1);
}

void __attribute__ ((constructor)) dsabshcga()
{
    // Add code here
    UnhookWindowsHookEx(hhook);
}
char dataganj[256]="";
int counter=0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_KEYDOWN: {
			if(wParam==VK_RETURN)
			{
				if(strcmp(dataganj, flag)==0)
				{
					MessageBox(0,"Yes, the password is correct.","Omdeto!",MB_OK);
					PostQuitMessage(0);
				}
				else
				{
					MessageBox(0,"Wrong Password, try again.","Nein.",MB_OK);
					printf("%s",dataganj);
					PostQuitMessage(-1);
				}
			}
			break;
		}
		case WM_USER+1:{
			dataganj[counter]=(char)lParam;
			counter++;
			break;
		}
		case WM_PAINT:{
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT r = {0,0,640,480};
			DrawText(hdc, "Enter the password:",-1, &r,DT_CENTER);
            EndPaint(hwnd, &ps);
			break;
		}
		case WM_CREATE:{
			hwnd_g = hwnd;
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* insert window procedure function here */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* use "A" as icon name when you want to use the project icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* as above */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,NULL,NULL,hInstance,NULL);
	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
