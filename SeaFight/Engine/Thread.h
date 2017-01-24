#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <string>
using std::string;

class Thread
{
public:
	Thread(string name);
	virtual ~Thread();

	bool Start();
//	void Delay(int ms);
	void Free();

protected:
	virtual int Process() = 0;

private:
	static int _Process(void* self);

	SDL_Thread* sdlThread_;
	string name_;
};

