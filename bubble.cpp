#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
void bubble::GenerationBubble() const{

	DrawBox(bubbleX, bubbleY, bubbleX+10, bubbleY +10, GetColor(255, 0, 0), TRUE);
	//DrawFormatString(10, 100, C_WHITE, "%d", bubbleX);
}	
void bubble::UpdateBubble()
{
	
	FPSCount++;
	
	bubbleY-=1;

	

	
	
	if (FPSCount > 30) {
			bubbleX -= 10;
	}
	else {
			bubbleX += 5;
	}
	if (FPSCount > 50) {
				bubbleX += 15;
	}

	

	

	/*if (FPSCount % 60 == 0) {
		bubbleY -= 10;
		if (FPSCount % 30 == 0) {
			bubbleX -= 10;
		}
		else {
			bubbleX +=10;
		}
	}*/
}
