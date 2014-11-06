// VCTest.cpp

// インクルード
#include <Windows.h>

// 定数宣言
const int kScreenWidth =800;
const int kScreenHeight=600;

// プロトタイプ宣言（staticをつけることで、このファイルからのみで使うことを保証する）
static LRESULT CALLBACK wndProc(HWND inHWnd, UINT inUMsg, WPARAM inWParam, LPARAM inLParam);

static bool registerWindowClass(HINSTANCE inHInstance,LPCTSTR inWndClassName);
static HWND createWindow(LPCTSTR inWndClassNme,int inWidth,int inHeight,HINSTANCE inHInstance);

// WinMain
int WINAPI WinMain(HINSTANCE inHInstance,
    HINSTANCE inHPrevInstance,
    LPSTR inCmdLine,
    int inNCmdShow) {

        // TEXTでくくることで文字列を統一化 
        LPCTSTR windowClassName=TEXT("AnimationAndGame2-01");

        if(registerWindowClass(inHInstance,windowClassName)==false) {
            MessageBox(NULL,TEXT("Can not register WNDCLASS."),TEXT("ERROR"),MB_OK);
            return 0;
        }

        HWND hWnd=createWindow(windowClassName,kScreenWidth,kScreenHeight,inHInstance);
        if(hWnd==NULL) {
            MessageBox(NULL,TEXT("Can not create window."),TEXT("ERROR"),MB_OK);
            return 0;
        }

        // message loop
        int returnCode=0;
        bool isError=false;
        while(TRUE) {
            MSG msg;
            int getMessageResult=GetMessage(&msg,NULL,0,0);
            if(getMessageResult>0) {
                DispatchMessage(&msg);
            } else if(getMessageResult==-1) {
                isError=true;
                break;
            } else { // getMessageResult==0 (WM_QUIT)
                returnCode = msg.wParam;
                break;
            }
        }
        if( isError ) {
            MessageBox(NULL,TEXT("Can not get message."),TEXT("ERROR"),MB_OK);
        }
        return returnCode;
}

// WindowClass 
static bool registerWindowClass(HINSTANCE inHInstance,LPCWSTR inWndClassName) {
    WNDCLASSEX windowClass;
    ZeroMemory(&windowClass,sizeof(windowClass));

    windowClass.cbSize=sizeof(WNDCLASSEX);
    windowClass.style=CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc=wndProc;
    windowClass.hInstance=inHInstance;
    windowClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    windowClass.hCursor=LoadCursor(NULL , IDC_ARROW);
    windowClass.hbrBackground=(HBRUSH)(COLOR_WINDOW);
    windowClass.lpszMenuName= NULL;
    windowClass.lpszClassName=inWndClassName;
    windowClass.hIconSm = NULL;

    return RegisterClassEx(&windowClass)!=0;
}

// 実際にWindowをつくる関数
static HWND createWindow(LPCWSTR inWndClassNme,
    int inWidth,int inHeight,
    HINSTANCE inHInstance) {
        HWND ret=CreateWindowEx(WS_EX_LEFT,inWndClassNme,
            TEXT("Lesson1"),
            WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX | WS_VISIBLE,
            CW_USEDEFAULT,CW_USEDEFAULT,
            inWidth,inHeight,
            NULL,NULL,inHInstance,NULL
            );
        return ret;
}

// wndProc
static LRESULT CALLBACK wndProc(HWND inHWnd, UINT inUMsg, WPARAM inWParam, LPARAM inLParam) {
    switch(inUMsg) {
    case WM_CREATE:
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        ValidateRect(inHWnd,NULL);
        return 0;
    default:
        return DefWindowProc(inHWnd,inUMsg,inWParam,inLParam);
    }
}