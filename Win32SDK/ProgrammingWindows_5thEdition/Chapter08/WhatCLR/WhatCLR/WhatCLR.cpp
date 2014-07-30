#include<windows.h>

const int ID_TIMER = 1;
void FindWindowSize(int*,int*);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    static wchar_t szAppName[] = L"WhatClr";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndcls;
    int cxWindow,cyWindow;

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(DC_BRUSH);
    wndcls.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassW(&wndcls)){
        MessageBoxW(NULL,L"This program requires Windows NT!",szAppName,MB_ICONERROR);
        return 0;
    }

    FindWindowSize(&cxWindow,&cyWindow);
    hwnd = CreateWindowW(szAppName,L"What Color",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER,
        CW_USEDEFAULT,CW_USEDEFAULT,cxWindow,cyWindow,
        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

void FindWindowSize(int *pcxWindow,int *pcyWindow){
    HDC hdcScreen;
    TEXTMETRIC tm;

    hdcScreen = CreateIC(L"DISPLAY",NULL,NULL,NULL);
    GetTextMetrics(hdcScreen,&tm);
    DeleteDC(hdcScreen);

    *pcxWindow = 2*GetSystemMetrics(SM_CXBORDER) + 12*tm.tmAveCharWidth;
    *pcyWindow = 2*GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION) + 2*tm.tmHeight;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static COLORREF cr,crLast;
    static HDC hdcScreen;
    HDC hdc;
    PAINTSTRUCT ps;
    POINT pt;
    RECT rc;
    wchar_t szBuffer[16];

    switch(message){
        case WM_CREATE:
            hdcScreen = CreateDC(L"DISPLAY",NULL,NULL,NULL);
            SetTimer(hwnd,ID_TIMER,100,NULL);
            return 0;

        case WM_TIMER:
            GetCursorPos(&pt);
            cr = GetPixel(hdcScreen,pt.x,pt.y);
            //SetPixel(hdcScreen,pt.x,pt.y,0);
            if(cr != crLast){
                crLast = cr;
                InvalidateRect(hwnd,NULL,FALSE);
            }
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rc);
            wsprintf(szBuffer,L"%02X %02X %02X ",GetRValue(cr),GetGValue(cr),GetBValue(cr));

            DrawText(hdc,szBuffer,-1,&rc,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            DeleteDC(hdcScreen);
            KillTimer(hwnd,ID_TIMER);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,message,wParam,lParam);
}