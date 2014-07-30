#include<windows.h>
const int DIVISIONS = 5;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildWndProc(HWND,UINT,WPARAM,LPARAM);

wchar_t szChildClass[] = L"Checker3_Child";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static wchar_t szAppName[] = L"Checker3";
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
    wndclass.style = CS_VREDRAW | CS_HREDRAW;

    if(!RegisterClassW(&wndclass)){
        MessageBox(NULL,L"This program requires Windows NT !",szAppName,MB_ICONERROR);
        return 0;
    }

    wndclass.lpfnWndProc = ChildWndProc;
    wndclass.cbWndExtra = sizeof(long);
    wndclass.hIcon = NULL;
    wndclass.lpszClassName = szChildClass;

    RegisterClass(&wndclass);

    hwnd = CreateWindowW(szAppName,L"Checker3 Mouse Hit-Test Demo",WS_OVERLAPPEDWINDOW,
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
    static HWND hwndChild[DIVISIONS][DIVISIONS];
    int cxBlock,cyBlock,x,y;

    switch(message){
        case WM_CREATE:
            for(x=0;x<DIVISIONS;++x)
                for(y=0;y<DIVISIONS;++y)
                    hwndChild[x][y] = CreateWindowW(szChildClass,NULL,WS_CHILDWINDOW|WS_VISIBLE,
                    0,0,0,0,hwnd,(HMENU)(y<<8|x),(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
            return 0;

        case WM_SIZE:
            cxBlock = LOWORD(lParam)/DIVISIONS;
            cyBlock = HIWORD(lParam)/DIVISIONS;
            for(x=0;x<DIVISIONS;++x)for(y=0;y<DIVISIONS;++y)
                MoveWindow(hwndChild[x][y],x*cxBlock,y*cyBlock,cxBlock,cyBlock,TRUE);
            return 0;

        case WM_LBUTTONDOWN:
            MessageBeep(0);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,message,wParam,lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch(message){
        case WM_CREATE:
            SetWindowLong(hwnd,0,0);    //on/off flag
            return 0;

        case WM_LBUTTONDOWN:
            SetWindowLong(hwnd,0,1^GetWindowLong(hwnd,0));
            InvalidateRect(hwnd,NULL,FALSE);
            //SendMessage(GetParent(hwnd),WM_LBUTTONDOWN,wParam,lParam);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);
            Rectangle(hdc,0,0,rect.right,rect.bottom);

            if(GetWindowLong(hwnd,0)){
                MoveToEx(hdc,0,0,NULL);
                LineTo(hdc,rect.right,rect.bottom);
                MoveToEx(hdc,0,rect.bottom,NULL);
                LineTo(hdc,rect.right,0);
            }

            EndPaint(hwnd,&ps);
            return 0;
    }
    return DefWindowProc(hwnd,message,wParam,lParam);
}