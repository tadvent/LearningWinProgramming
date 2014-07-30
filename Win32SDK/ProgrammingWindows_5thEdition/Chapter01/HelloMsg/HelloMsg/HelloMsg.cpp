#include<windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow){
   switch(MessageBox(NULL,TEXT("Hellow,Windows XP!"),TEXT("HelloMsg"),MB_YESNOCANCEL|MB_ICONQUESTION|MB_DEFBUTTON2)){
       case IDYES:
           MessageBox(NULL,TEXT("YES Pressed."),TEXT("YES"),MB_OK);
           break;
       case IDNO:
           MessageBox(NULL,TEXT("NO Pressed."),TEXT("NO"),MB_OK|MB_ICONINFORMATION);
           break;
       default:
           MessageBox(NULL,TEXT("CANCEL Pressed."),TEXT("OK"),MB_OK|MB_ICONINFORMATION);
   }
   return 0;
}