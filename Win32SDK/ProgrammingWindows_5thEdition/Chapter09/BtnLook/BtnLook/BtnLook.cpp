#include<windows.h>

struct {
    int iStyle;
    TCHAR *szText;
}
button[] = {
    BS_PUSHBUTTON,      L"PUSHBUTTON",
    BS_DEFPUSHBUTTON,   L"DEFPUSHBUTTON",
    BS_CHECKBOX,        L"CHECKBOX",
    BS_AUTOCHECKBOX,    L"AUTOCHECKBOX",
    BS_RADIOBUTTON,     L"RADIOBUTTON",
    BS_3STATE,          L"3STATE",
    BS_AUTO3STATE,      L"AUTO3STATE",
    BS_GROUPBOX,        L"GROUPBOX",
    BS_AUTORADIOBUTTON, L"AUTORADIOBUTTON",
    BS_OWNERDRAW,       L"OWNERDRAW"
};

const int NUM = sizeof(button)/sizeof(button[0]);

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szAppName[] = L"BtnLook";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(DC_BRUSH);
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hInstance = hInstance;
    wndclass.lpfnWndProc = WndProc;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClass(&wndclass)){
        MessageBox(NULL,L"requires win nt...",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,L"Button Look",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    static HWND hwndButton[NUM];
    static RECT rect;
    static TCHAR szTop[] = L"message         wParam         lParam",
                 szUnd[] = L"_______         ______         ______",
                 szFormat[] = L"%-16s%04X-%04X      %04X-%04X",
                 szBuffer[50];
    static int cxChar,cyChar;
    HDC hdc;
    PAINTSTRUCT ps;
    int i;

    switch(message){
        case WM_CREATE:
            cxChar = LOWORD(GetDialogBaseUnits());
            cyChar = HIWORD(GetDialogBaseUnits());

            for(i=0;i<NUM;++i)
                hwndButton[i] = CreateWindowW(L"button",button[i].szText,
                    WS_CHILD | WS_VISIBLE | button[i].iStyle,
                    cxChar,cyChar*(1+2*i),20*cxChar,7*cyChar/4,
                    hwnd,(HMENU)i,((LPCREATESTRUCT)lParam)->hInstance,NULL);
            return 0;

        case WM_SIZE:
            rect.left = 24*cxChar;
            rect.top = 2*cyChar;
            rect.right = LOWORD(lParam);
            rect.bottom = HIWORD(lParam);
            return 0;

        case WM_PAINT:
            InvalidateRect(hwnd,&rect,TRUE);

            hdc = BeginPaint(hwnd,&ps);
            SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
            SetBkMode(hdc,TRANSPARENT);

            TextOut(hdc,24*cxChar,cyChar,szTop,lstrlen(szTop));
            TextOut(hdc,24*cxChar,cyChar,szUnd,lstrlen(szUnd));

            EndPaint(hwnd,&ps);
            return 0;

        case WM_DRAWITEM:
        case WM_COMMAND:
            ScrollWindow(hwnd,0,-cyChar,&rect,&rect);
            hdc = GetDC(hwnd);
            SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
            TextOut(hdc,24*cxChar,cyChar*(rect.bottom/cyChar-1),szBuffer,
                wsprintf(szBuffer,szFormat,message == WM_DRAWITEM? L"WM_DRAWITEM":L"WM_COMMAND",
                HIWORD(wParam),LOWORD(wParam),HIWORD(lParam),LOWORD(lParam)));
            ReleaseDC(hwnd,hdc);
            ValidateRect(hwnd,&rect);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,message,wParam,lParam);
}