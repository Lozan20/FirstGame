#pragma once
#include <raylib.h>
class Lives
{
public:
	static int numberOfLives;
private:
	static int beginDrawX;
	static int beginDrawY;
	static Texture2D texture;
public:
	static void Lives::drawLives()
	{
		//texture = Lives::loadTexture();
		for (int i = 0; i < numberOfLives; i++)
		{
			DrawTexture(texture, 1036+ i*110 , 20, WHITE);
		}
	}
	inline static Texture2D Lives::loadTexture();
};
Texture2D Lives::loadTexture()
{
	Texture2D* temp = new Texture2D();
	Image heart = LoadImage("resources/heartW2.png");
	ImageColorReplace(&heart, WHITE, Color{ 130,130,130,0 });
	ImageResize(&heart, 100, 100);
	*temp = LoadTextureFromImage(heart);
	UnloadImage(heart);
	texture = *temp;
	return *temp;
}

