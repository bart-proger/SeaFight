#pragma once
#include "../Scene.h"
#include "../../Engine/Font.h"

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
 	void onClick(SDL_Point );
private:
	Font font_;
};

