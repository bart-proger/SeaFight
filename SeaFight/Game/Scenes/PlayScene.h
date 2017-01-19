#pragma once
#include "../Scene.h"
#include "../../Engine/Font.h"

class PlayScene : public Scene
{
public:
	PlayScene(Game &);

	void init() override;
	void update(float dt) override;
	void draw(Graphics &) override;
	
// 	static void ClearMapClick(Scene &);
// 	static void GoFightClick(Scene &);
// 
 	void onRelease(SDL_Point );
private:
	Font font_;
};

