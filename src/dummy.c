// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color {
	unsigned char r;        // Color red value
	unsigned char g;        // Color green value
	unsigned char b;        // Color blue value
	unsigned char a;        // Color alpha value
} Color;

void rl_DrawText(const char *text, int posX, int posY, int fontSize, Color color)
{
	DrawText(text,  posX, posY, fontSize, color);

}

void rl_CloseWindow()
{
	CloseWindow();

}