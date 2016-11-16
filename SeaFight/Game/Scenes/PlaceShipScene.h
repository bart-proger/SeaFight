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

	void OnClick(SDL_Point ) override;

	FreeShipsGroup freeShipsGroups_[4];
};

