/*
window creation comes in two parts, first the creation of the window with certan proprties
* then you have to make a place to handle it
*/


#include <iostream>
#include "window.h"

using namespace std;

int main() {
	cout << "program started" << endl;

	window* myWindow = new window();

	bool running = true;

	while (running) {
		if (!myWindow->ProcessMessages()) {
			cout << "closing window";
			running = false;
		}
		//render


		Sleep(10);
	}



	delete myWindow;
	myWindow = nullptr;
	cout << "program ended" << endl;
	return 0;
}