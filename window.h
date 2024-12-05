//https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
#pragma once


#include <windows.h>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class window
{
public:
	window(); // default constructor defined in the .cpp file but could be defined here


	//gets rid of copy , and = 
	window(const window&) = delete; // makes it impossible to copy a window onto another
	window& operator =(const window) = delete; // makes it impossible to assign the values of one window to another
	/*
	* window w1;
	* window w2;
	* window w3 = w2; // error!
	* w2 = w1; // error!
	
	*/
	~window(); // destructor



	bool ProcessMessages();

private:
	/*
	HINSTANCE m_hInstance; 
		pointer to a block of info that holds info about the current application 
		used to id the application
		used to interact with the window itself via event handling

	HWND m_hWnd; 
		HWND stands for handle to window
		used for handling events, changing the properties of a window
		window manipulation comes from here
	*/
	HINSTANCE m_hInstance;
	HWND m_hWnd; 

};

