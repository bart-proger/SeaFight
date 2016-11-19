#pragma once
#include "../Scene.h"
#include "../Ship.h"
#include "../FreeShipsGroup.h"

class PlaceShipScene : public Scene
{
public:
	PlaceShipScene(Game &);
	
	void Init() override;
	void Draw(Graphics &) override;

private:
	static void ClearMap_Click(Scene &);
	static void GoFight_Click(Scene &);

	void onClick(SDL_Point ) override;
// 	void onPress(SDL_Point ) override;
// 	void onRelease(SDL_Point) override;

	FreeShipsGroup freeShipsGroups_[4];
	FreeShipsGroup * selected_;
};

