#include<windows.h>

const int MAXPOINTS = 1000;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static wchar_t szAppName[] = L"Connect";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndcls;

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(DC_BRUSH);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

    if(!RegisterClassW(&wndcls)){
        MessageBoxW(NULL, L"This program requires Windows NT!", szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName, L"Connect-the-Points Mouse Demo", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static POINT pt[MAXPOINTS];
    static int iCount;
    HDC hdc;
    int i, j;
    PAINTSTRUCT ps;
    switch(message){
        case WM_LBUTTONDBLCLK:
            MessageBox(hwnd, L"Double clicked!", L"Connect Program", MB_OK | MB_ICONINFORMATION);
            return 0;
        case WM_LBUTTONDOWN:
            iCount = 0;
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_MOUSEMOVE:
            if(wParam & MK_LBUTTON &&iCount<1000){
                pt[iCount].x = LOWORD(lParam);
                pt[iCount++].y = HIWORD(lParam);
                hdc = GetDC(hwnd);
                SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), 0);
                ReleaseDC(hwnd, hdc);
            }
            return 0;
        case WM_LBUTTONUP:
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            SetCursor(LoadCursor(NULL, IDC_WAIT));
            ShowCursor(TRUE);
            for(i=0; i<iCount-1; ++i)for(j=i+1; j<iCount; ++j){
                MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
                LineTo(hdc, pt[j].x, pt[j].y);
            }
            ShowCursor(FALSE);
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
