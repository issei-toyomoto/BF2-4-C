#include"bubble.h"
#include"Dxlib.h"
void bubble::GenerationBubble() const{

	DrawBox(bubbleX, bubbleY, bubbleX+10, bubbleY +10, GetColor(255, 0, 0), TRUE);
}
void bubble::UpdateBubble()
{
	FPSCount++;

	if (FPSCount % 60 == 0) {
		bubbleY -= 10;
		bubbleX -= 10;
		
	}
}
