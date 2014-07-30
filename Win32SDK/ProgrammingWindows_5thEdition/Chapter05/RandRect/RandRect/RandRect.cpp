#include<windows.h>
#include<cstdlib>
using namespace std;

LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);
void DrawRectangle(HWND);
int cxClient,cyClient;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static wchar_t szAppName[] = L"RandRect";
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

    hwnd = CreateWindowW(szAppName,L"Random Rectangles",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,0);

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    while(true){
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
            if(msg.message == WM_QUIT)break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
            DrawRectangle(hwnd);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    switch(message){
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}

void DrawRectangle(HWND hwnd){
    HBRUSH hBrush;
    HDC hdc;
    RECT rect;

    if(cxClient == 0 || cyClient == 0)return;

    SetRect(&rect,rand()%cxClient,rand()%cyClient,rand()%cxClient,rand()%cyClient);
    hBrush = CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));
    hdc = GetDC(hwnd);
    FillRect(hdc,&rect,hBrush);
    ReleaseDC(hwnd,hdc);
    DeleteObject(hBrush);
}