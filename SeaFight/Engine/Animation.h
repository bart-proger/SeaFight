#pragma once

class Graphics;

class Animation
{
public:
	enum PlayType { SEQUENCE, LOOP };
	void play();
	void draw(Graphics &);
private:
	PlayType type_;
	int frame_;
	int frameRate_; //ms
};

