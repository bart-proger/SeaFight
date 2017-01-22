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
	void onPress(SDL_Point) override;
	void onRelease(SDL_Point) override;
	void onMove(SDL_Point) override;

private:
	FreeShipsGroup freeShipsGroups_[4];
	FreeShipsGroup * selected_;
	SDL_Point mousePos_;

	static void clearMap_click(Scene &);
	static void goFight_click(Scene &);
};

