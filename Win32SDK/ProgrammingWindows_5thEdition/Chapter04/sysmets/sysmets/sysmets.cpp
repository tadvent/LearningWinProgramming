#define _sysmets3_

#ifdef _sysmets1_
// SysMets No. 1

#include<windows.h>
#include"sysmets.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static wchar_t szAppName[]=L"SysMets1";
    HWND hwnd;

    WNDCLASS wndclass;
    wndclass.style        = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc  = WndProc;
    wndclass.cbClsExtra   = 0;
    wndclass.cbWndExtra   = 0;
    wndclass.hInstance    = hInstance;
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground        = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wndclass.lpszMenuName         = NULL;
    wndclass.lpszClassName        = szAppName;

    if (!RegisterClass (&wndclass)){
        MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                    szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow (szAppName, TEXT ("Get System Metrics No. 1"),
                   WS_OVERLAPPEDWINDOW,
                   CW_USEDEFAULT, CW_USEDEFAULT,
                   CW_USEDEFAULT, CW_USEDEFAULT,
                   NULL, NULL, hInstance, NULL);
    ShowWindow (hwnd, nShowCmd);
    UpdateWindow (hwnd);

    MSG msg;
    while (GetMessage (&msg, NULL, 0, 0)){
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static int    cxChar, cxCaps, cyChar;
    HDC                   hdc;
    int                   i;
    PAINTSTRUCT ps;
    TCHAR                szBuffer [10];
    TEXTMETRIC  tm;
    switch (message){
        case   WM_CREATE:
            hdc = GetDC (hwnd);
            GetTextMetrics (hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC (hwnd, hdc);
            return 0;
        case   WM_PAINT:
            hdc = BeginPaint (hwnd, &ps);
            for (i = 0 ; i < NUMLINES ; i++){
                TextOut(hdc, 0, cyChar * i,sysmetrics[i].szLabel,lstrlen (sysmetrics[i].szLabel));
                TextOut(hdc, 22*cxCaps, cyChar*i, sysmetrics[i].szDesc, lstrlen (sysmetrics[i].szDesc));
                SetTextAlign (hdc, TA_RIGHT | TA_TOP);
                TextOut (hdc, 22 * cxCaps + 40 * cxChar, cyChar * i,   szBuffer,
                    wsprintf (szBuffer, TEXT ("%5d"),GetSystemMetrics (sysmetrics[i].Index)));
                SetTextAlign (hdc, TA_LEFT | TA_TOP);
            }
            EndPaint (hwnd, &ps);
            return 0;
        case   WM_DESTROY:
            PostQuitMessage (0);
            return 0;
    }

    return DefWindowProc (hwnd, message, wParam, lParam);
}

#endif

#ifdef _sysmets2_
// SysMets No. 2

#include<windows.h>
#include"sysmets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    wchar_t szAppName[] = L"SysMets2";
    HWND hwnd;
    WNDCLASS wndcls;

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_VREDRAW | CS_HREDRAW;

    if(!RegisterClass(&wndcls)){
        MessageBox(NULL,L"This app requries WinNT...",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"Get System Metrics No. 2",
                         WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                         NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg,NULL,0,0)) != 0){
        if(bRet == -1){
            MessageBox(NULL,L"An unknown error occurred...", szAppName, MB_ICONERROR);
            return -1;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static int cxChar, cxCaps, cyChar, cyClient, iVscrollPos;
    HDC hdc;
    int i,y;
    PAINTSTRUCT ps;
    wchar_t szBuffer[10];
    TEXTMETRIC tm;

    switch(message){
        case WM_CREATE:
            hdc = GetDC(hwnd);
            GetTextMetrics(hdc,&tm);
            cxChar = tm.tmAveCharWidth;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3:2) * cxChar/2;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            SetScrollRange(hwnd,SB_VERT,0,NUMLINES-1,FALSE);
            SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);
            return 0;

        case WM_SIZE:
            cyClient = HIWORD(lParam);
            return 0;

        case WM_VSCROLL:
            switch(LOWORD(wParam)){
                case SB_LINEUP:
                    iVscrollPos -= 1;
                    break;
                case SB_LINEDOWN:
                    iVscrollPos += 1;
                    break;
                case SB_PAGEUP:
                    iVscrollPos -= cyClient/cyChar;
                    break;
                case SB_PAGEDOWN:
                    iVscrollPos += cyClient/cyChar;
                    break;
                case SB_THUMBPOSITION:
                    iVscrollPos = HIWORD(wParam);
                    break;
                default:
                    break;
            }
            iVscrollPos = max(0,min(iVscrollPos,NUMLINES-1));
            if(iVscrollPos != GetScrollPos(hwnd, SB_VERT)){
                SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);
                InvalidateRect(hwnd,NULL,TRUE);
            }
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            for(i=0;i<NUMLINES;++i){
                y = cyChar * (i-iVscrollPos);
                TextOut(hdc,0,y,sysmetrics[i].szLabel,lstrlen(sysmetrics[i].szLabel));
                TextOut(hdc,22*cxCaps,y,sysmetrics[i].szDesc,lstrlen(sysmetrics[i].szDesc));
                SetTextAlign(hdc,TA_RIGHT | TA_TOP);
                TextOut(hdc,22*cxCaps+40*cxChar,y,szBuffer,
                    wsprintf(szBuffer,L"%5d",GetSystemMetrics(sysmetrics[i].Index)));
                SetTextAlign(hdc,TA_LEFT | TA_TOP);
            }
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}

#endif

#ifdef _sysmets3_
// SysMets No. 3

#include<windows.h>
#include"sysmets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    wchar_t szAppName[] = L"SysMets3";
    HWND hwnd;
    WNDCLASS wndcls;

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_VREDRAW | CS_HREDRAW;

    if(!RegisterClass(&wndcls)){
        MessageBox(NULL,L"This app requries WinNT...",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"Get System Metrics No. 3",
                         WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                         NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg,NULL,0,0)) != 0){
        if(bRet == -1){
            MessageBox(NULL,L"An unknown error occurred...", szAppName, MB_ICONERROR);
            return -1;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth;
    HDC hdc;
    int i,x,y,iVertPos,iHorzPos,iPaintBeg,iPaintEnd;
    PAINTSTRUCT ps;
    SCROLLINFO si;
    wchar_t szBuffer[10];
    TEXTMETRIC tm;

    switch(message){
        case WM_CREATE:
            hdc = GetDC(hwnd);
            GetTextMetrics(hdc,&tm);
            cxChar = tm.tmAveCharWidth;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3:2) * cxChar/2;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            //Save the width of the three columns
            iMaxWidth = 40*cxChar + 22*cxCaps;
            return 0;

        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            //Set vertical scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = NUMLINES - 1;
            si.nPage = cyClient / cyChar;
            SetScrollInfo(hwnd,SB_VERT,&si,TRUE);
            //Set Horizontal scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = 2 + iMaxWidth/cxChar;
            si.nPage = cxClient/cxChar;
            SetScrollInfo(hwnd,SB_HORZ,&si,TRUE);
            return 0;

        case WM_VSCROLL:
            //Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd,SB_VERT,&si);
            //Save the position for comparison later on
            iVertPos = si.nPos;
            switch(LOWORD(wParam)){
                case SB_TOP:
                    si.nPos = si.nMin;
                    break;
                case SB_BOTTOM:
                    si.nPos = si.nMax;
                    break;
                case SB_LINEUP:
                    si.nPos -= 1;
                    break;
                case SB_LINEDOWN:
                    si.nPos += 1;
                    break;
                case SB_PAGEUP:
                    si.nPos -= si.nPage;
                    break;
                case SB_PAGEDOWN:
                    si.nPos += si.nPage;
                    break;
                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;
                default:
                    break;
            }
            //Set the position and then retrieve it. Due to adjustments
            //by Windows it may not be the same as the value set.
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd,SB_VERT,&si,TRUE);
            GetScrollInfo(hwnd,SB_VERT,&si);
            //If the position has changed, scroll the window and update it
            if(si.nPos != iVertPos){
                ScrollWindow(hwnd,0,cyChar*(iVertPos - si.nPos),NULL,NULL);
                UpdateWindow(hwnd);
            }
            return 0;

        case WM_HSCROLL:
            //Get all the horizontal scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            //Save the position for comparison later on
            GetScrollInfo(hwnd,SB_HORZ,&si);
            iHorzPos = si.nPos;
            switch(LOWORD(wParam)){
                case SB_LINELEFT:
                    si.nPos -= 1;
                    break;
                case SB_LINERIGHT:
                    si.nPos += 1;
                    break;
                case SB_PAGELEFT:
                    si.nPos -= si.nPage;
                    break;
                case SB_PAGERIGHT:
                    si.nPos += si.nPage;
                    break;
                case SB_THUMBPOSITION:
                    si.nPos = si.nTrackPos;
                    break;
                default:
                    break;
            }
            //Set the position and then retrieve it. Due to adjustments
            //by Windows it may not be the same as the value set.
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd,SB_HORZ,&si,TRUE);
            GetScrollInfo(hwnd,SB_HORZ,&si);
            //If the position has changed, scroll the window
            if(si.nPos != iHorzPos){
                ScrollWindow(hwnd,cxChar*(iHorzPos-si.nPos),0,NULL,NULL);
            }
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            //Get vertical scroll bar position
            si.cbSize = sizeof(si);
            si.fMask = SIF_POS;
            GetScrollInfo(hwnd,SB_VERT,&si);
            iVertPos = si.nPos;
            //Get horizontal scroll bar position
            GetScrollInfo(hwnd,SB_HORZ,&si);
            iHorzPos = si.nPos;
            //Find painting limits
            iPaintBeg = max(0,iVertPos + ps.rcPaint.top/cyChar);
            iPaintEnd = min(NUMLINES-1,iVertPos + ps.rcPaint.bottom/cyChar);
            for(i=iPaintBeg;i<=iPaintEnd;++i){
                x = cxChar * (1-iHorzPos);
                y = cyChar * (i-iVertPos);
                TextOut(hdc,x,y,sysmetrics[i].szLabel,lstrlen(sysmetrics[i].szLabel));
                TextOut(hdc,x+22*cxCaps,y,sysmetrics[i].szDesc,
                    lstrlen(sysmetrics[i].szDesc));
                SetTextAlign(hdc,TA_RIGHT | TA_TOP);
                TextOut(hdc,x+22*cxCaps+40*cxChar,y,szBuffer,
                    wsprintf(szBuffer,L"%5d",GetSystemMetrics(sysmetrics[i].Index)));
                SetTextAlign(hdc,TA_LEFT | TA_TOP);
            }
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}

#endif