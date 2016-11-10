#include "Thread.h"
#include <iostream>

Thread::Thread(string name):
	name_(name),
	sdlThread_(nullptr)
{
}

Thread::~Thread()
{
	Free();
}

bool Thread::Start()
{
	if (!(sdlThread_ = SDL_CreateThread(_Process, name_.c_str(), reinterpret_cast<void*>(this))))
	{
		std::cerr << "[error] SDL_CreateThread: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Thread::Delay(int ms)
{
	SDL_Delay(ms);
}

void Thread::Free()
{
	if (sdlThread_)
		SDL_WaitThread(sdlThread_, 0);
	sdlThread_ = nullptr;
}

int Thread::_Process(void* self)
{
	Thread* t = reinterpret_cast<Thread*>(self);
	return t->Process();
}
