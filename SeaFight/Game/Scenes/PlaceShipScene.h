#pragma once
#include "../Scene.h"
#include "../Ship.h"
#include "../FreeShipsGroup.h"

class PlaceShipScene : public Scene
{
public:
	PlaceShipScene(Game &);
	
	void init() override;
	void draw(Graphics &) override;
	void onShow() override;

private:
	static void ClearMap_Click(Scene &);
	static void GoFight_Click(Scene &);
	 
	void onPress(SDL_Point) override;
	void onRelease(SDL_Point ) override;
	void onMouseMove(SDL_Point p) override;

	FreeShipsGroup freeShipsGroups_[4];
	FreeShipsGroup * selected_;
	SDL_Point mousePos_;
};

