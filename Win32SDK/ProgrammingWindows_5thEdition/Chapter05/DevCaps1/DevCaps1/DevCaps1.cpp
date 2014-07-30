#include<windows.h>

//#define NUMLINES ((int)(sizeof(devcaps)/sizeof(devcaps[0])))

struct {
    int iIndex;
    wchar_t *szLabel;
    wchar_t *szDesc;
}
devcaps[] = {
    HORZSIZE,     TEXT ("HORZSIZE"),    TEXT ("Width in millimeters:"),
    VERTSIZE,     TEXT ("VERTSIZE"),    TEXT ("Height in millimeters:"),
    HORZRES,      TEXT ("HORZRES"),     TEXT ("Width in pixels:"),
    VERTRES,      TEXT ("VERTRES"),     TEXT ("Height in raster lines:"),
    BITSPIXEL,    TEXT ("BITSPIXEL"),   TEXT ("Color bits per pixel:"),
    PLANES,       TEXT ("PLANES"),      TEXT ("Number of color planes:"),
    NUMBRUSHES,   TEXT ("NUMBRUSHES"),  TEXT ("Number of device brushes:"),
    NUMPENS,      TEXT ("NUMPENS"),     TEXT ("Number of device pens:"),
    NUMMARKERS,   TEXT ("NUMMARKERS"),  TEXT ("Number of device markers:"),
    NUMFONTS,     TEXT ("NUMFONTS"),    TEXT ("Number of device fonts:"),
    NUMCOLORS,    TEXT ("NUMCOLORS"),   TEXT ("Number of device colors:"),
    PDEVICESIZE,  TEXT ("PDEVICESIZE"), TEXT ("Size of device structure:"),
    ASPECTX,      TEXT ("ASPECTX"),     TEXT ("Relative width of pixel:"),
    ASPECTY,      TEXT ("ASPECTY"),     TEXT ("Relative height of pixel:"),
    ASPECTXY,     TEXT ("ASPECTXY"),    TEXT ("Relative diagonal of pixel:"),
    LOGPIXELSX,   TEXT ("LOGPIXELSX"),  TEXT ("Horizontal dots per inch:"),
    LOGPIXELSY,   TEXT ("LOGPIXELSY"),  TEXT ("Vertical dots per inch:"),
    SIZEPALETTE,  TEXT ("SIZEPALETTE"), TEXT ("Number of palette entries:"),
    NUMRESERVED,  TEXT ("NUMRESERVED"), TEXT ("Reserved palette entries:"),
    COLORRES,     TEXT ("COLORRES"),    TEXT ("Actual color resolution:")
};

const int NUMLINES = sizeof(devcaps)/sizeof(devcaps[0]);

LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    static wchar_t szAppName[] = L"DevCaps1";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hInstance = hInstance;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClass(&wndclass)){
        MessageBox(NULL,L"This app requires Windows NT!",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"Device Capabilities",WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
                        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    BOOL bRet;
    while((bRet = GetMessage(&msg,NULL,0,0)) != 0){
        if(bRet == -1){
            MessageBox(NULL,L"An unknown error occurred!",szAppName,MB_ICONERROR);
            return -1;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    static int cxChar, cxCaps, cyChar;
    wchar_t szBuffer[10];
    HDC hdc;
    int i;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(message){
        case WM_CREATE:
            hdc = GetDC(hwnd);
            GetTextMetrics(hdc,&tm);
            cxChar = tm.tmAveCharWidth;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3:2) * cxChar / 2;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            for(i=0;i<NUMLINES;++i){
                TextOut(hdc,0,cyChar * i,devcaps[i].szLabel,lstrlen(devcaps[i].szLabel));
                TextOut(hdc,14*cxCaps,cyChar*i,devcaps[i].szDesc,lstrlen(devcaps[i].szDesc));
                SetTextAlign(hdc,TA_RIGHT | TA_TOP);
                TextOut(hdc,14*cxCaps+35*cxChar,cyChar*i,szBuffer,
                        wsprintf(szBuffer,L"%5d",GetDeviceCaps(hdc,devcaps[i].iIndex)));
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