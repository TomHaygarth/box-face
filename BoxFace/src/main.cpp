/*
	File: Main.cpp
	Author: Tom Haygarth
	Version: 0.1
	Updated: 20/03/2013

	The application is designed to use input gained from the XInput interface to emulate keyboard and mouse functionality.
	By mapping various keys and mouse directions onto the keys and analogue sticks.

*/

// include files
#include <Windows.h>
#include <XInput.h>

#include "BoxFaceApp.h"

using namespace std;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
HWND	hwnd;

HBITMAP		theOldFrontBitMap, theOldBackBitMap;
RECT		screenRect;
HDC			backHDC, frontHDC, bitmapHDC;



void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX  wcex;									

    wcex.cbSize        = sizeof (wcex);				
    wcex.style         = CS_HREDRAW | CS_VREDRAW;		
    wcex.lpfnWndProc   = WndProc;						
    wcex.cbClsExtra    = 0;								
    wcex.cbWndExtra    = 0;								
    wcex.hInstance     = hInstance;						
    wcex.hIcon         = 0; 
    wcex.hCursor       = LoadCursor (NULL, IDC_ARROW);	
															
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wcex.lpszMenuName  = NULL;							
    wcex.lpszClassName = "WindowClass";				
    wcex.hIconSm       = 0; 

	RegisterClassEx (&wcex);							

}

BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow)
{

   hwnd = CreateWindow ("WindowClass",					
						 "BoxFace-360 to pc control",		  			
						 WS_OVERLAPPEDWINDOW,				
						 100,						
						 100,						
						 800,						
						 800,
						 NULL,								
						 NULL,								
						 hInstance,						    
						 NULL);								
	if (!hwnd)
	{
		return FALSE;
	}
    ShowWindow (hwnd, nCmdShow);							
    UpdateWindow (hwnd);									
	return TRUE;

}


void setBuffers()
{
	GetClientRect(hwnd, &screenRect);	//creates rect based on window client area
	frontHDC = GetDC(hwnd);			// Initialises front buffer device context (window)
	backHDC = CreateCompatibleDC(frontHDC);// sets up Back DC to be compatible with the front
	bitmapHDC=CreateCompatibleDC(backHDC);
	theOldFrontBitMap = CreateCompatibleBitmap(frontHDC, screenRect.right, 
		screenRect.bottom);		//creates bitmap compatible with the front buffer
    theOldBackBitMap = (HBITMAP)SelectObject(backHDC, theOldFrontBitMap);
								//creates bitmap compatible with the back buffer
	FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void displayFrame()
{
		BitBlt(frontHDC, screenRect.left,screenRect.top, screenRect.right, 
		screenRect.bottom, backHDC, 0, 0, SRCCOPY);
		FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void releaseResources()
{
	SelectObject(backHDC,theOldBackBitMap);
	DeleteDC(backHDC);
	DeleteDC(bitmapHDC);
	ReleaseDC(hwnd,frontHDC);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)			
{														
										
    MSG         msg;

	BoxFaceApp boxApp;


	if(!boxApp.Initialise())
	{
		return FALSE;
	}



	RegisterMyWindow(hInstance);

    if (!InitialiseMyWindow(hInstance, nCmdShow))
		return FALSE;

#ifndef NDEBUG
	
#else
	if(strstr(szCmdLine, "-d"))
	{
		
	}
#endif


	setBuffers();

	while (TRUE)					
    {										
		// only peek in the message que to see if we have something
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		}
		else
		{
			boxApp.Update();
			boxApp.Render(backHDC,bitmapHDC);

			displayFrame();
		}
    }

	boxApp.Unload();
	    
	// release our device contexts and other resources
	releaseResources();

	return msg.wParam ;	

}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

    switch (message)											
    {														
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			RECT rt;
			GetClientRect(hWnd, &rt);
			EndPaint(hWnd, &ps);
		    break;		

		case WM_DESTROY:	
			PostQuitMessage(0);		
			break;	

	}
	return DefWindowProc (hWnd, message, wParam, lParam);																	

}