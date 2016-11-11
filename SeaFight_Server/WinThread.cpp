#include "WinThread.h"
#include <iostream>

WinThread::WinThread():
	handle(NULL),
	id(0)
//	doStop(false)
{
	handle = CreateThread(NULL, 0, _Process, this, CREATE_SUSPENDED, &id);
}

WinThread::~WinThread()
{
	TerminateThread(handle, NULL);
    CloseHandle(handle);
}


void WinThread::StartThread()
{
	ResumeThread(handle);
}

/*
void Thread::Stop()
{
	EnterCriticalSection(&cs);
	doStop = true;
	LeaveCriticalSection(&cs);
}
*/

DWORD WINAPI WinThread::_Process(LPVOID param)
{
	WinThread* pt = reinterpret_cast<WinThread*>(param);
	pt->Process();
	return 0;
}
