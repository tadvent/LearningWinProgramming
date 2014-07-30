#include<windows.h>

LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static wchar_t szAppName[] = L"WhatSize";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hInstance = hInstance;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClass(&wndclass)){
        MessageBox(NULL,L"This app requires Win NT!",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"What size is the window?",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,0);

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    BOOL bRet;
    while((bRet = GetMessage(&msg,NULL,0,0)) != 0){
        if(-1 == bRet){
            MessageBox(NULL,L"An unknown error occurred...",szAppName,MB_ICONERROR);
            return -1;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

void Show(HWND hwnd, HDC hdc, int xText, int yText, int iMapMode, wchar_t *szMapMode){
    wchar_t szBuffer[60];
    RECT rect;

    SaveDC(hdc);
    SetMapMode(hdc,iMapMode);
    GetClientRect(hwnd,&rect);
    DPtoLP(hdc,(PPOINT) &rect,2);
    RestoreDC(hdc,-1);
    TextOut(hdc,xText,yText,szBuffer,wsprintf(szBuffer,L"%-20s %7d %7d %7d %7d",szMapMode,
        rect.left,rect.right,rect.top,rect.bottom));
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    static wchar_t szHeading[] = L"Mapping Mode            Left   Right     Top  Bottom";
    static wchar_t szUndLine[] = L"--------------------   -----   -----   -----  ------";
    static int cxChar, cyChar;
    HDC hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(message){
        case WM_CREATE:
            hdc = GetDC(hwnd);
            SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
            GetTextMetrics(hdc,&tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
            SetMapMode(hdc,MM_ANISOTROPIC);
            SetWindowOrgEx(hdc,-5,-3,NULL);
            SetWindowExtEx(hdc,1,1,NULL);
            SetViewportExtEx(hdc,cxChar,cyChar,NULL);
            //SetViewportExtEx(hdc,cxChar,-cyChar,NULL);
            //SetViewportOrgEx(hdc,0, 20*cyChar, NULL);

            TextOut(hdc,1,1,szHeading,lstrlen(szHeading));
            TextOut(hdc,1,2,szUndLine,lstrlen(szUndLine));

            Show(hwnd,hdc,1,3,MM_TEXT,L"TEXT(pixels)");
            Show(hwnd,hdc,1,4,MM_LOMETRIC,L"LOMETRIC(.1 mm)");
            Show(hwnd,hdc,1,5,MM_HIMETRIC,L"HIMETRIC(.01 mm)");
            Show(hwnd,hdc,1,6,MM_LOENGLISH,L"LOENGLISH(.01 in)");
            Show(hwnd,hdc,1,7,MM_HIENGLISH,L"HIENGLISH(.001 in)");
            Show(hwnd,hdc,1,8,MM_TWIPS,L"TWIPS(1/1440 in)");
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}