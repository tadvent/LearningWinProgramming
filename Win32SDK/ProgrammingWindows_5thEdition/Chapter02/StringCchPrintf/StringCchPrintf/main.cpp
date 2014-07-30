#include<windows.h>
#include<strsafe.h>
#include<cstdlib>
#include<ctime>

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR lpCmdLine, int nShowCmd){
    const int textsize = 30;
    wchar_t buffer[textsize];

    srand((unsigned)time(NULL));
    int a = rand();
    int b = rand();
    StringCchPrintf(buffer, textsize, L"%d + %d = %d", a, b, a+b);
    MessageBoxW(NULL, buffer, L"RandomAdd", MB_OK);
    return 0;
}
