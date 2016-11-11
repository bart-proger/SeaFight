#pragma once

#include <windows.h>

class WinThread
{
public:
	WinThread();
	virtual ~WinThread();

	void StartThread();
//	void Stop();

protected:
	virtual void Process() = 0;

private:
	static DWORD WINAPI _Process(LPVOID param);

	HANDLE handle;
	DWORD id;

//	bool doStop;
};