#include<windows.h>

LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR LpCmdLine,int nCmdShow){
    MSG msg;
    WNDCLASS wndcls;
    HWND hwnd;
    wchar_t szAppName[] = L"KeyView1";

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WindowProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassW(&wndcls)){
        MessageBoxW(NULL,L"This program requires Windows NT!",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"Key View No.1",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    static int cxClientMax,cyClientMax,cxClient,cyClient,cxChar,cyChar;
    static int cLinesMax,cLines;
    static PMSG pmsg;
    static RECT rectScroll;
    static wchar_t szTop[] = L"Message          Key        Char " L" Repeat Scan Ext ALT Prev Tran";
    static wchar_t szUnd[] = L"_____________ ______      _______" L" ______ ____ ___ ___ ____ ____";
    static wchar_t *szFormat[2] = {
        L"%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s",
        L"%-13s             0x%04X%1s%c%6u %4d %3s %3s %4s %4s"
    };
    static wchar_t *szYes = L"Yes";
    static wchar_t *szNo = L"No";
    static wchar_t *szDown = L"Down";
    static wchar_t *szUp = L"Up";

    static wchar_t *szMessage[] = {
        L"WM_KEYDOWN",L"WM_KEYUP",L"WM_CHAR",L"WM_DEADCHAR",
        L"WM_SYSKEYDOWN",L"SYSKEYUP",L"WM_SYSCHAR",L"WM_SYSDEADCHAR"
    };

    HDC hdc;
    int i,iType;
    PAINTSTRUCT ps;
    wchar_t szBuffer[128],szKeyName[32];
    TEXTMETRIC tm;

    switch(message){
        case WM_CREATE:
        case WM_DISPLAYCHANGE:
            //Get maximum size of client area
            cxClientMax = GetSystemMetrics(SM_CXMAXIMIZED);
            cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);
            //Get character size for fixed-pitch font
            hdc = GetDC(hwnd);
            SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
            GetTextMetrics(hdc,&tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight;
            ReleaseDC(hwnd,hdc);
            //Allocate memory for display lines
            if(pmsg)free(pmsg);
            cLinesMax = cyClientMax/cyChar;
            pmsg = (PMSG)malloc(cLinesMax*sizeof(MSG));
            cLines = 0;
            //fall through
        case WM_SIZE:
            if(message == WM_SIZE){
                cxClient = LOWORD(lParam);
                cyClient = HIWORD(lParam);
            }
            //Calculate scrolling rectangle
            rectScroll.left = 0;
            rectScroll.right = cxClient;
            rectScroll.top = cyChar;
            rectScroll.bottom = cyChar*(cyClient/cyChar);

            InvalidateRect(hwnd,NULL,TRUE);
            return 0;

        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_DEADCHAR:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_SYSCHAR:
        case WM_SYSDEADCHAR:
            //Rearrange storage array
            for(i=cLinesMax-1;i>0;--i)pmsg[i]=pmsg[i-1];
            //Store new message
            pmsg[0].hwnd = hwnd;
            pmsg[0].message = message;
            pmsg[0].wParam = wParam;
            pmsg[0].lParam = lParam;
            cLines = min(cLines+1,cLinesMax);
            //Scroll up the display
            ScrollWindow(hwnd,0,-cyChar,&rectScroll,&rectScroll);
            break;  //i.e., call DefWindowProc so Sys messages work

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
            SetBkMode(hdc,TRANSPARENT);
            TextOut(hdc,0,0,szTop,lstrlen(szTop));
            TextOut(hdc,0,0,szUnd,lstrlen(szUnd));
            for(i=0;i<min(cLines,cyClient/cyChar-1);++i){
                iType = pmsg[i].message == WM_CHAR ||
                    pmsg[i].message == WM_SYSCHAR ||
                    pmsg[i].message == WM_DEADCHAR ||
                    pmsg[i].message == WM_SYSDEADCHAR;
                GetKeyNameText(pmsg[i].lParam,szKeyName,sizeof(szKeyName)/sizeof(wchar_t));
                TextOut(hdc,0,(cyClient/cyChar-1-i)*cyChar,szBuffer,
                    wsprintf(szBuffer,szFormat[iType],szMessage[pmsg[i].message-WM_KEYFIRST],
                    pmsg[i].wParam,(iType?L" ":szKeyName),(iType?pmsg[i].wParam:' '),
                    LOWORD(pmsg[i].lParam),HIWORD(pmsg[i].lParam) & 0xFF,
                    0x01000000 & pmsg[i].lParam ? szYes:szNo,
                    0x20000000 & pmsg[i].lParam ? szYes:szNo,
                    0x40000000 & pmsg[i].lParam ? szDown:szUp,
                    0x80000000 & pmsg[i].lParam ? szUp:szDown));
            }
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}