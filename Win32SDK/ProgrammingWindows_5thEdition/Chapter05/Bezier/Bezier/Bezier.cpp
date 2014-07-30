#include<windows.h>

LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static wchar_t szAppName[] = L"Bezier";
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

    hwnd = CreateWindowW(szAppName,L"Bezier Splines",WS_OVERLAPPEDWINDOW,
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

void DrawBezier(HDC hdc, POINT apt[]){
    PolyBezier(hdc,apt,4);
    MoveToEx(hdc,apt[0].x,apt[0].y,NULL);
    LineTo(hdc,apt[1].x,apt[1].y);

    MoveToEx(hdc,apt[2].x,apt[2].y,NULL);
    LineTo(hdc,apt[3].x,apt[3].y);
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    static POINT apt[4];
    static int cxClient, cyClient;
    HDC hdc;
    PAINTSTRUCT ps;

    switch(message){
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            apt[0].x = cxClient/4;
            apt[0].y = cyClient/2;
            apt[1].x = cxClient/2;
            apt[1].y = cyClient/4;
            apt[2].x = cxClient/2;
            apt[2].y = 3*cyClient/4;
            apt[3].x = 3*cxClient/4;
            apt[3].y = cyClient/2;
            return 0;
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MOUSEMOVE:
            if(wParam & MK_LBUTTON || wParam & MK_RBUTTON){
                hdc = GetDC(hwnd);
                SelectObject(hdc,GetStockObject(WHITE_PEN));
                DrawBezier(hdc,apt);
                if(wParam & MK_LBUTTON){
                    apt[1].x = LOWORD(lParam);
                    apt[1].y = HIWORD(lParam);
                }
                if(wParam & MK_RBUTTON){
                    apt[2].x = LOWORD(lParam);
                    apt[2].y = HIWORD(lParam);
                }
                SelectObject(hdc,GetStockObject(BLACK_PEN));
                DrawBezier(hdc,apt);
                ReleaseDC(hwnd,hdc);
            }
            return 0;

        case WM_PAINT:
            InvalidateRect(hwnd,NULL,TRUE);
            hdc = BeginPaint(hwnd,&ps);
            DrawBezier(hdc,apt);
            EndPaint(hwnd,&ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}