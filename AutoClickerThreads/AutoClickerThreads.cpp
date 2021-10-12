#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>


static void startclicker(int_least64_t periodForAutoclicker)
{
	INPUT inp[2] = {};
	bool exit = false;
	bool clicking = false;

	inp[0].type = INPUT_MOUSE;
	inp[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	inp[1].type = INPUT_MOUSE;
	inp[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	// if we would like a transmit a keyboard input
	/*
	inp[0].type = INPUT_KEYBOARD;
	inp[0].ki.wVk = VK_SPACE;
	inp[1].type = INPUT_KEYBOARD;
	inp[1].ki.wVk = VK_SPACE;
	inp[1].ki.dwFlags = KEYEVENTF_KEYUP;
	*/
	UINT uSent = SendInput(ARRAYSIZE(inp), inp, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inp)) {
		std::cerr << "SendInput failed: 0x%x\n";
	}
	else {
		std::cout << "Initialized" << std::endl;
	}

	while (!exit)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			std::cout << "Bye Bye <3 " << std::endl;
			clicking = false;
			exit = true;
			return;
		}
		if (GetAsyncKeyState(VK_NUMPAD2))
		{
			std::cout << "Clicking !" << std::endl;
			clicking = true;


			while (clicking)
			{

				std::this_thread::sleep_for(std::chrono::milliseconds(periodForAutoclicker));

				UINT uSent = SendInput(ARRAYSIZE(inp), inp, sizeof(INPUT));
				if (uSent != ARRAYSIZE(inp)) {
					std::cerr << "SendInput failed: 0x%x\n";
				}


				if (GetAsyncKeyState(VK_NUMPAD3))
				{
					clicking = false;
					std::cout << "Stopping the clicker.." << std::endl;
				}

			}
		}

	}
}

int_least64_t setWindowTitleAndFAQOutputAndStartInput()
{
	int_least64_t period;
	system("TITLE Mouse Clicker by sandaasu edited by Gerodote");
	using std::cout;
	using std::endl;
	std::cout << "Please, write period, for which autoclick will execute in ms (milliseconds):" << std::endl;
	std::cin >> period;
	std::cout << "Thank You, program starts." << std::endl << std::endl;
	cout << "======================================================" << endl;
	cout << "[ HOTKEYS ]" << endl << endl;
	cout << "NumPad2 = activate autoclicker left_button (once in " << period << "ms)" << endl;
	cout << "NumPad3 = STOP" << endl;
	cout << "Escape  = Close" << endl;
	cout << "======================================================" << endl
		<< endl;
	cout << "[ LOG ] " << endl << endl;

	return period; // RVO, we don't care about std::move.
}


int main()
{
	int_least64_t period = setWindowTitleAndFAQOutputAndStartInput();
	std::thread first(startclicker, period);
	first.join();
	std::cout << "Exited." << std::endl;

	return 0;
}