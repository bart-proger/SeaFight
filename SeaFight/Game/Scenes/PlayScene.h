#pragma once
#include "../Scene.h"

class PlayScene : public Scene
{
public:
	PlayScene(Game &);

	void Init() override;
	void Update(float dt) override;
	void Draw(Graphics &) override;
	
// 	static void ClearMapClick(Scene &);
// 	static void GoFightClick(Scene &);
// 
 	void OnClick(SDL_Point );
};

