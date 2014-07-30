#include<windows.h>

#define BUFFER(x,y) *(pBuffer+y*cxBuffer+x)

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    static wchar_t szAppName[] = L"Typer";
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

    hwnd = CreateWindowW(szAppName,L"Typing Program",WS_OVERLAPPEDWINDOW,
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
    static DWORD dwCharSet = DEFAULT_CHARSET;
    static int cxChar,cyChar,cxClient,cyClient,cxBuffer,cyBuffer,xCaret,yCaret;
    static wchar_t *pBuffer = NULL;
    HDC hdc;
    int x,y,i;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(message){
        case WM_INPUTLANGCHANGE:
            dwCharSet = wParam;
            //fall through
        case WM_CREATE:
            hdc = GetDC(hwnd);
            SelectObject(hdc,CreateFont(0,0,0,0,0,0,0,0,dwCharSet,0,0,0,FIXED_PITCH,NULL));
            GetTextMetrics(hdc,&tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight;
            DeleteObject(SelectObject(hdc,GetStockObject(SYSTEM_FONT)));
            ReleaseDC(hwnd,hdc);
            //fall through
        case WM_SIZE:
            //obtain window size in pixels
            if(message == WM_SIZE){
                cxClient = LOWORD(lParam);
                cyClient = HIWORD(lParam);
            }
            //calculate window size in characters
            cxBuffer = max(1,cxClient/cxChar);
            cyBuffer = max(1,cyClient/cyChar);
            //allocate memory for buffer and clear it
            if(pBuffer != NULL)free(pBuffer);
            pBuffer = (wchar_t *)malloc(cxBuffer * cyBuffer * sizeof(wchar_t));

            for(y=0;y<cyBuffer;++y)for(x=0;x<cxBuffer;++x)BUFFER(x,y) = L' ';
            //set caret to upper left corner
            xCaret = 0;
            yCaret = 0;
            if(hwnd == GetFocus())
                SetCaretPos(xCaret*cxChar,yCaret*cyChar);
            InvalidateRect(hwnd,NULL,TRUE);
            return 0;

        case WM_SETFOCUS:
            //create and show the caret
            CreateCaret(hwnd,NULL,cxChar,cyChar);
            SetCaretPos(xCaret*cxChar,yCaret*cyChar);
            ShowCaret(hwnd);
            return 0;

        case WM_KILLFOCUS:
            //hide and destroy the caret
            HideCaret(hwnd);
            DestroyCaret();
            return 0;

        case WM_KEYDOWN:
            switch(wParam){
                case VK_HOME:
                    xCaret = 0;
                    break;
                case VK_END:
                    xCaret = cxBuffer - 1;
                    break;
                case VK_PRIOR:
                    yCaret = 0;
                    break;
                case VK_NEXT:
                    yCaret = cyBuffer - 1;
                    break;
                case VK_LEFT:
                    xCaret = max(xCaret-1,0);
                    break;
                case VK_RIGHT:
                    xCaret = min(xCaret+1,cxBuffer-1);
                    break;
                case VK_UP:
                    yCaret = max(yCaret-1,0);
                    break;
                case VK_DOWN:
                    yCaret = min(yCaret+1,cyBuffer-1);
                    break;
                case VK_DELETE:
                    for(x=xCaret;x<cxBuffer-1;++x)BUFFER(x,yCaret)=BUFFER(x+1,yCaret);
                    BUFFER(cxBuffer-1,yCaret)=L' ';
                    HideCaret(hwnd);
                    hdc = GetDC(hwnd);

                    SelectObject(hdc,CreateFont(0,0,0,0,0,0,0,0,dwCharSet,0,0,0,FIXED_PITCH,NULL));
                    TextOut(hdc,xCaret*cxChar,yCaret*cyChar, & BUFFER(xCaret,yCaret),cxBuffer-xCaret);
                    DeleteObject(SelectObject(hdc,GetStockObject(SYSTEM_FONT)));
                    ReleaseDC(hwnd,hdc);
                    ShowCaret(hwnd);
                    break;
            }
            SetCaretPos(xCaret*cxChar,yCaret*cyChar);
            return 0;

        case WM_CHAR:
            for(i=0;i<(int)LOWORD(lParam);++i){
                switch(wParam){
                    case L'\b':  //backspace
                        if(xCaret>0){
                            xCaret--;
                            SendMessage(hwnd,WM_KEYDOWN,VK_DELETE,1);
                        }
                        break;
                    case L'\t':  //tab
                        do {
                            SendMessage(hwnd,WM_CHAR,L' ',1);
                        }while(xCaret%8 !=0);
                        break;
                    case L'\n': //line feed
                        if(++yCaret == cyBuffer)yCaret=0;
                        break;
                    case L'\r':
                        xCaret = 0;
                        if(++yCaret == cyBuffer)yCaret=0;
                        break;
                    case L'\x1B':   //escape
                        for(y=0;y<cyBuffer;++y)for(x=0;x<cxBuffer;++x)
                            BUFFER(x,y)=L' ';
                        xCaret = 0;
                        yCaret = 0;

                        InvalidateRect(hwnd,NULL,FALSE);
                        break;
                    default:    //character codes
                        BUFFER(xCaret,yCaret)=(wchar_t)wParam;
                        HideCaret(hwnd);
                        hdc = GetDC(hwnd);
                        SelectObject(hdc,CreateFont(0,0,0,0,0,0,0,0,dwCharSet,0,0,0,FIXED_PITCH,NULL));
                        TextOut(hdc,xCaret*cxChar,yCaret*cyChar, & BUFFER(xCaret,yCaret),1);
                        DeleteObject(SelectObject(hdc,GetStockObject(SYSTEM_FONT)));
                        ReleaseDC(hwnd,hdc);
                        ShowCaret(hwnd);
                        if(++xCaret == cxBuffer){
                            xCaret = 0;
                            if(++yCaret == cyBuffer)yCaret = 0;
                        }
                        break;
                }
            }
            SetCaretPos(xCaret*cxChar,yCaret*cyChar);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
            SelectObject(hdc,CreateFont(0,0,0,0,0,0,0,0,dwCharSet,0,0,0,FIXED_PITCH,NULL));
            for(y=0;y<cyBuffer;++y)
                TextOut(hdc,0,y*cyChar, & BUFFER(0,y),cxBuffer);
            DeleteObject(SelectObject(hdc,GetStockObject(SYSTEM_FONT)));
            EndPaint(hwnd,&ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd,message,wParam,lParam);
}