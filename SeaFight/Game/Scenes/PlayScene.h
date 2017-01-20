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
 	void onRelease(SDL_Point) override;
	void onMouseMove(SDL_Point) override;
	void onChangeGameState(/*Game::PlayState*/) override;
private:
	Font font_;
	SDL_Point * aimPos_;
	string status_;

	static void surrender_click(Scene &);
	static void continue_click(Scene &);
	static void fire_click(Scene &);
};

