#include<windows.h>

const int ID_TIMER = 1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND,UINT,UINT,DWORD);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    wchar_t szAppName[] = L"Beeper2";
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

    hwnd = CreateWindowW(szAppName,L"Beeper2 Timer Demo",
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                         NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg,NULL,0,0)) != 0){
        if(bRet == -1){
            MessageBox(NULL,L"System error occurred...", szAppName, MB_ICONERROR);
            return -1;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    //static BOOL fFlipFlop = FALSE;
    //HBRUSH hBrush;
    //HDC hdc;
    //PAINTSTRUCT ps;
    //RECT rc;

    switch(message){
        case WM_CREATE:
            SetTimer(hwnd,ID_TIMER,1000,TimerProc);
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd,ID_TIMER);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,message,wParam,lParam);
}

void CALLBACK TimerProc(HWND hwnd,UINT message, UINT iTimerID, DWORD dwTime){
    static BOOL fFlipFlop = FALSE;
    HBRUSH hBrush;
    HDC hdc;
    RECT rc;

    MessageBeep(-1);
    fFlipFlop = !fFlipFlop;
    GetClientRect(hwnd,&rc);
    hdc = GetDC(hwnd);
    hBrush = CreateSolidBrush(fFlipFlop? RGB(255,0,0):RGB(0,0,255));
    FillRect(hdc,&rc,hBrush);
    ReleaseDC(hwnd,hdc);
    DeleteObject(hBrush);
}