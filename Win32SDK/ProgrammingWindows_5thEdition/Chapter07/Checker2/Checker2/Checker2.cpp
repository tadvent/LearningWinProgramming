#include<windows.h>

const int DIVISIONS = 5;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    static wchar_t szAppName[] = L"Checker2";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndcls;

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(DC_BRUSH);
    wndcls.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassW(&wndcls)){
        MessageBoxW(NULL,L"This program requires Windows NT!",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"Checker2 Mouse Hit-Test Demo",WS_OVERLAPPEDWINDOW,
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
    static BOOL fState[DIVISIONS][DIVISIONS];
    static int cxBlock,cyBlock;
    HDC hdc;
    int x,y;
    PAINTSTRUCT ps;
    POINT point;
    RECT rect;

    switch(message){
        case WM_SIZE:
            cxBlock = LOWORD(lParam)/DIVISIONS;
            cyBlock = HIWORD(lParam)/DIVISIONS;
            return 0;

        case WM_SETFOCUS:
            ShowCursor(TRUE);
            return 0;
        case WM_KILLFOCUS:
            ShowCursor(FALSE);
            return 0;

        case WM_KEYDOWN:
            GetCursorPos(&point);
            ScreenToClient(hwnd,&point);
            x = max(0,min(DIVISIONS-1,point.x/cxBlock));
            y = max(0,min(DIVISIONS-1,point.y/cyBlock));
            switch(wParam){
                case VK_UP:
                    --y;
                    break;
                case VK_DOWN:
                    ++y;
                    break;
                case VK_LEFT:
                    --x;
                    break;
                case VK_RIGHT:
                    ++x;
                    break;
                case VK_HOME:
                    x = y = 0;
                    break;
                case VK_END:
                    x = y = DIVISIONS - 1;
                    break;
                case VK_RETURN:
                case VK_SPACE:
                    SendMessage(hwnd,WM_LBUTTONDOWN,MK_LBUTTON,MAKELONG(x*cxBlock,y*cyBlock));
                    break;
            }
            x = (x+DIVISIONS)%DIVISIONS;
            y = (y+DIVISIONS)%DIVISIONS;
            point.x = x*cxBlock + cxBlock/2;
            point.y = y*cyBlock + cyBlock/2;
            ClientToScreen(hwnd,&point);
            SetCursorPos(point.x,point.y);
            return 0;

        case WM_LBUTTONDOWN:
            x = LOWORD(lParam)/cxBlock;
            y = HIWORD(lParam)/cyBlock;
            if(x<DIVISIONS && y<DIVISIONS){
                fState[x][y]^=1;
                rect.left = x*cxBlock;
                rect.top = y*cyBlock;
                rect.right = (x+1)*cxBlock;
                rect.bottom = (y+1)*cyBlock;
                InvalidateRect(hwnd,&rect,TRUE);
            }
            else
                MessageBeep(0);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            for(x=0;x<DIVISIONS;++x)for(y=0;y<DIVISIONS;++y){
                Rectangle(hdc,x*cxBlock,y*cyBlock,(x+1)*cxBlock,(y+1)*cyBlock);
                if(fState[x][y]){
                    MoveToEx(hdc,x*cxBlock,y*cyBlock,NULL);
                    LineTo(hdc,(x+1)*cxBlock,(y+1)*cyBlock);
                    MoveToEx(hdc,x*cxBlock,(y+1)*cyBlock,NULL);
                    LineTo(hdc,(x+1)*cxBlock,y*cyBlock);
                }
            }
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd,message,wParam,lParam);
}