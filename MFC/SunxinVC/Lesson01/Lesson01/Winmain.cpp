//#include<iostream>
#include<windows.h>
#include<stdio.h>
//using namespace std;

LRESULT CALLBACK mainwndproc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    ){
        WNDCLASS mainwnd;
        mainwnd.cbClsExtra=0;
        mainwnd.cbWndExtra=0;
        mainwnd.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
        mainwnd.hCursor=LoadCursor(NULL,IDC_HAND);
        mainwnd.hIcon=LoadIcon(NULL,IDI_WINLOGO);
        mainwnd.hInstance=hInstance;
        mainwnd.lpfnWndProc=mainwndproc;
        mainwnd.lpszClassName=TEXT("mainwnd");
        mainwnd.lpszMenuName=NULL;
        mainwnd.style=CS_HREDRAW|CS_VREDRAW;
        RegisterClass(&mainwnd);

        HWND hMainwnd;
        hMainwnd=CreateWindow(TEXT("mainwnd"),TEXT("Hello World"),WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
        ShowWindow(hMainwnd,SW_SHOWNORMAL);
        UpdateWindow(hMainwnd);

        MSG msg;
        while(GetMessage(&msg,NULL,NULL,NULL)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return 0;
}

LRESULT CALLBACK mainwndproc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    ){
        TCHAR str[30];
        static int lbut=0,rbut=0;
        switch(uMsg){
            case WM_PAINT:
                HDC hdc;
                PAINTSTRUCT ps;
                hdc=BeginPaint(hwnd,&ps);
                TextOut(hdc,5,5,TEXT("第一个窗口哦~~"),strlen(TEXT("第一个窗口哦~~")));
                EndPaint(hwnd,&ps);
                break;
            case WM_CHAR:
                sprintf_s(str,TEXT("你刚刚点了 %c 键，呵呵"),wParam);
                MessageBox(hwnd,str,TEXT("按键"),0);
                break;
            case WM_LBUTTONDOWN:
                sprintf_s(str,TEXT("第%d次点左键了哦！"),++lbut);
                MessageBox(hwnd,str,TEXT("鼠标"),0);
                break;
            case WM_RBUTTONDOWN:
                sprintf_s(str,TEXT("第%d次点右键了哦！"),++rbut);
                MessageBox(hwnd,str,TEXT("鼠标"),0);
                break;
            case WM_CLOSE:
                if(IDYES==MessageBox(hwnd,TEXT("要退出吗？"),TEXT("确认"),MB_YESNO)){
                    DestroyWindow(hwnd);
                }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hwnd,uMsg,wParam,lParam);
        }
        return 0;
}