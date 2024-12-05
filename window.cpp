#include "window.h"
#include <iostream>
using namespace std;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {


	case WM_CLOSE: //close button
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT: // Paint message (needed to draw stuff)
		{
			// Begin painting
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			// Set the rectangle's drawing color (red in this case)
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Red brush

			// Define the rectangle's coordinates
			RECT rect = { 50, 50, 300, 200 }; // (left, top, right, bottom)

			// Draw the rectangle on the window
			FillRect(hdc, &rect, hBrush);

			// Clean up
			DeleteObject(hBrush);  // Free the brush resource

			// End painting
			EndPaint(hWnd, &ps);
		}
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}





window::window() // this whole part could be insdie the .h file
	: m_hInstance(GetModuleHandle(nullptr)) // Initializer list
{
	const wchar_t* CLASS_NAME = L"Huds First Window"; // local to the constructor function and holds then name of the class

	WNDCLASS wndClass = {}; //wndclass is a windows api thing, this declares a blank one with all values set to zero
	
	//filling in the values of the wndclass struct
	wndClass.hInstance = m_hInstance; // even though is private you still have access to it due to it being in the class
	wndClass.lpszClassName = CLASS_NAME; // seting window name 
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // null here tells the system that you are laoding from the systems list of logos
	wndClass.hCursor = LoadCursor(NULL, IDC_CROSS);// null here tells the system that you are laoding from the systems list of cursors
	wndClass.lpfnWndProc = WindowProc; // window procedure check notes , points to function above


	RegisterClass(&wndClass);
	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU; // defines the window style WS_CAPTION (title on window)| WS_MINIMIZEBOX (minimize box) |  WS_SYSMENU (dispalys minimize box and close button);

	int WIDTH = 650;
	int HEIGHT = 480;
	RECT windowsDimensions;
	windowsDimensions.left = 250;
	windowsDimensions.top = 250;
	windowsDimensions.right = windowsDimensions.left + WIDTH; // sets the right corner to be WIDTH far away from the left side
	windowsDimensions.bottom = windowsDimensions.top + HEIGHT; // same but for height

	AdjustWindowRect(&windowsDimensions, style, false); // false if not using menus. corrects some stuff idk


	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Title",
		style,
		windowsDimensions.left,
		windowsDimensions.top,
		windowsDimensions.right - windowsDimensions.left,
		windowsDimensions.bottom - windowsDimensions.top,
		NULL,
		NULL, // menus
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);

	cout << "window deconstructor has been called" << endl;
}

window::~window()
{
	const wchar_t* CLASS_NAME = L"Huds First Window"; 

	UnregisterClass(CLASS_NAME, m_hInstance);
	cout << "window deconstructor has been called" << endl;
}





bool window::ProcessMessages()
/*any time a message comes into the process messages function, 
its translated then sent to the windows proc fucntion to be handled by
sending it through the dispatch message functon*/
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{ // keeps running as long as there are more messages in the qeuee
	
		if (msg.message == WM_QUIT) { // 
			return false;
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg); // calls WindowProc to handle the message / event
	}

	return true;
}

