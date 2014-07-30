#include<windows.h>
#include<cmath>
using namespace std;

const double TWOPI = 2*3.1415926536;

LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lmCmdLine,int nShowCmd){
    static wchar_t szAppName[] = L"Clover";
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

    hwnd = CreateWindowW(szAppName,L"Draw a Clover",WS_OVERLAPPEDWINDOW,
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static HRGN hRgnClip;
    static int cxClient,cyClient;
    double fAngle,fRadius;
    HCURSOR hCursor;
    HDC hdc;
    HRGN hRgnTemp[6];
    int i;
    PAINTSTRUCT ps;

    switch(message){
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            hCursor = SetCursor(LoadCursor(NULL,IDC_WAIT));
            ShowCursor(TRUE);

            if(hRgnClip)DeleteObject(hRgnClip);
            hRgnTemp[0] = CreateEllipticRgn(0,cyClient/3,cxClient/2,2*cyClient/3);
            hRgnTemp[1] = CreateEllipticRgn(cxClient/2,cyClient/3,cxClient,2*cyClient/3);
            hRgnTemp[2] = CreateEllipticRgn(cxClient/3,0,2*cxClient/3,cyClient/2);
            hRgnTemp[3] = CreateEllipticRgn(cxClient/3,cyClient/2,2*cxClient/3,cyClient);
            hRgnTemp[4] = CreateRectRgn(0,0,1,1);
            hRgnTemp[5] = CreateRectRgn(0,0,1,1);
            hRgnClip = CreateRectRgn(0,0,1,1);

            CombineRgn(hRgnTemp[4],hRgnTemp[0],hRgnTemp[1],RGN_OR);
            CombineRgn(hRgnTemp[5],hRgnTemp[2],hRgnTemp[3],RGN_OR);
            CombineRgn(hRgnClip,hRgnTemp[4],hRgnTemp[5],RGN_XOR);

            for(i=0;i<6;++i)
                DeleteObject(hRgnTemp[i]);
            SetCursor(hCursor);
            ShowCursor(FALSE);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            SetWindowOrgEx(hdc,-cxClient/2,-cyClient/2,NULL);
            //SetViewportOrgEx(hdc,cxClient/2,cyClient/2,NULL);
            SelectClipRgn(hdc,hRgnClip);
            fRadius = _hypot(cxClient/2.0,cyClient/2.0);
            for(fAngle = 0.0;fAngle<TWOPI;fAngle += TWOPI/360){
                MoveToEx(hdc,0,0,NULL);
                LineTo(hdc,int(fRadius*cos(fAngle)+0.5),int(-fRadius*sin(fAngle)+0.5));
            }
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            DeleteObject(hRgnClip);
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}