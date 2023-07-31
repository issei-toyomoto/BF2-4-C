#include"DxLib.h"
#include"Thunderbolt.h"
#include"Common.h"

#define DEBUG

Thunder::Thunder()
{
	LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, gThunderImg);	//画像読み込み
	LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, gCloudImg);			//画像読み込み

	ThunderX = 100;//雷の座標
	ThunderY = 100;
	CloudX = 100; // 雲の座標
	CloudY = 100;
	VectorX = 3;
	VectorY = 3;
	ThunderAnimCnt = 0;
	CloudAnimCount = 0;
	gWaitTime = 0;
}

void Thunder::Update(int Stage)
{

	NowStage = Stage;
	ThunderAnimCnt++;
	CloudAnimCount++;
	gWaitTime++;
	//StageCollision();
	if (gWaitTime >= 1500) {
		MoveThunderX();
		ThunderX += VectorX;
		MoveThunderY();
		ThunderY += VectorY;
	}
	ThunderAnim();//画像処理

	if (ThunderAnimCnt >= 8) {
		ThunderAnimCnt = 0;
	}	

	CloudAnim();

	if (CloudAnimCount >= 8) {
		CloudAnimCount = 0;
	}
	
}

void Thunder::Draw() const 
{
	if (gWaitTime >= 1500) { 
		DrawGraph(ThunderX, ThunderY, NowImg, TRUE);
	}
	DrawGraph(CloudX, CloudY, CNowImg, TRUE);
#ifdef DEBUG
	if (gWaitTime >= 1500) {
		DrawBox(ThunderX, ThunderY, ThunderX + 32, ThunderY + 32, C_RED, FALSE);
		DrawBox(ThunderX + 4, ThunderY + 4, ThunderX + 28, ThunderY + 28, C_GREEN, FALSE);
	}
	
#endif // DEBUG

}

void Thunder::MoveThunderX()
{
	if (ThunderX <= 0) {
		VectorX *= -1;
	}
	else if (ThunderX >= _SCREEN_WIDHT_) {
		VectorX *= -1;
	}
}

void Thunder::MoveThunderY()
{
	if (ThunderY <= 0) {
		VectorY *= -1;
	}
	else if (ThunderY >= _SCREEN_HEIGHT_) {
		VectorY *= -1;
	}
}

void Thunder::StageCollision() 
{
	//雷の矩形
	int TXU_Left, TYU_Left;//左上
	int TXL_Right, TYL_Right;//右下
	TXU_Left = ThunderX;//左上X
	TYU_Left = ThunderX;//左上Y
	TXL_Right = ThunderX;//右下X
	TYL_Right = ThunderX;//右下Y

	if (NowStage == 1) {//***************　１ステージ　***************//
		/*******************************************************************************************************************************/
				//側面の当たり判定//
		/*******************************************************************************************************************************/
		
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
			VectorX *= -COR;
		}

		if (TYL_Right >= S_Sky_Ground_0_YU + PlusPx && TYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//上の台（側面）
			if (TXU_Left <= S_Sky_Ground_0_XL + PlusPx && TXL_Right >= S_Sky_Ground_0_XL) {//上の台の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S_Sky_Ground_0_XU - PlusPx && TXL_Right <= S_Sky_Ground_0_XU) {//上の台の左
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S_Sky_Ground_0_YL - PlusPx && TYL_Right >= S_Sky_Ground_0_YL) {//上の台（下辺）
			if (TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
		}
		

		if (TYU_Left > Sea_Level) {//海面

		}
		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/
		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Sky_Ground_0_YU && TYL_Right <= S_Sky_Ground_0_YU + PlusPx && TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {//浮いている中央の台（上辺）
			VectorY *= -COR;
		}
	}
	else if (NowStage == 2) {//***************　２ステージ　***************//
		/*******************************************************************************************************************************/
				//側面の当たり判定//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
			VectorX *= -COR;
		}

		if (TYL_Right >= S_Sky_Ground_0_YU + PlusPx && TYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//上の台（側面）
			if (TXU_Left <= S_Sky_Ground_0_XL + PlusPx && TXL_Right >= S_Sky_Ground_0_XL) {//上の台の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S_Sky_Ground_0_XU - PlusPx && TXL_Right <= S_Sky_Ground_0_XU) {//上の台の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S2_Sky_Ground_0_YU + PlusPx && TYU_Left <= S2_Sky_Ground_0_YL - PlusPx) {//左上の台（側面）
			if (TXU_Left <= S2_Sky_Ground_0_XL + PlusPx && TXL_Right >= S2_Sky_Ground_0_XL) {//左上の台の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S2_Sky_Ground_0_XU - PlusPx && TXL_Right <= S2_Sky_Ground_0_XU) {//左上の台の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S2_Sky_Ground_1_YU + PlusPx && TYU_Left <= S2_Sky_Ground_1_YL - PlusPx) {//右上の台（側面）
			if (TXU_Left <= S2_Sky_Ground_1_XL + PlusPx && TXL_Right >= S2_Sky_Ground_1_XL) {//右上の台の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S2_Sky_Ground_1_XU - PlusPx && TXL_Right <= S2_Sky_Ground_1_XU) {//右上の台の左
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S_Sky_Ground_0_YL - PlusPx && TYL_Right >= S_Sky_Ground_0_YL) {//上の台（下辺）
			if (TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S2_Sky_Ground_0_YL - PlusPx && TYL_Right >= S2_Sky_Ground_0_YL) {//左上の台（下辺）
			if (TXU_Left <= S2_Sky_Ground_0_XL && TXL_Right >= S2_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S2_Sky_Ground_1_YL - PlusPx && TYL_Right >= S2_Sky_Ground_1_YL) {//右上の台（下辺）
			if (TXU_Left <= S2_Sky_Ground_1_XL && TXL_Right >= S2_Sky_Ground_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
		}

		if (TYU_Left > Sea_Level) {//海面

		}
		
		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/
		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Sky_Ground_0_YU && TYL_Right <= S_Sky_Ground_0_YU + PlusPx && TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {//浮いている中央の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S2_Sky_Ground_0_YU && TYL_Right <= S2_Sky_Ground_0_YU + PlusPx && TXU_Left <= S2_Sky_Ground_0_XL && TXL_Right >= S2_Sky_Ground_0_XU) {//浮いている左上の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S2_Sky_Ground_1_YU && TYL_Right <= S2_Sky_Ground_1_YU + PlusPx && TXU_Left <= S2_Sky_Ground_1_XL && TXL_Right >= S2_Sky_Ground_1_XU) {//浮いている左上の台（上辺）
			VectorY *= -COR;
		}
	}
	else if (NowStage == 3) {//***************　３ステージ　***************//
		/*******************************************************************************************************************************/
				//側面の当たり判定//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
			VectorX *= -COR;
		}

		if (TYL_Right >= S3_Sky_SGround_0_YU + PlusPx && TYU_Left <= S3_Sky_SGround_0_YL - PlusPx) {//左鍾乳石（地面）
			if (TXU_Left <= S3_Sky_SGround_0_XL + PlusPx && TXL_Right >= S3_Sky_SGround_0_XL) {//左鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SGround_0_XU - PlusPx && TXL_Right <= S3_Sky_SGround_0_XU) {//左鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SStone_0_YU + PlusPx && TYU_Left <= S3_Sky_SStone_0_YL - PlusPx) {//左鍾乳石（石）
			if (TXU_Left <= S3_Sky_SStone_0_XL + PlusPx && TXL_Right >= S3_Sky_SStone_0_XL) {//左鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SStone_0_XU - PlusPx && TXL_Right <= S3_Sky_SStone_0_XU) {//左鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SGround_1_YU + PlusPx && TYU_Left <= S3_Sky_SGround_1_YL - PlusPx) {//中央鍾乳石（地面）
			if (TXU_Left <= S3_Sky_SGround_1_XL + PlusPx && TXL_Right >= S3_Sky_SGround_1_XL) {//中央鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SGround_1_XU - PlusPx && TXL_Right <= S3_Sky_SGround_1_XU) {//中央鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SStone_1_YU + PlusPx && TYU_Left <= S3_Sky_SStone_1_YL - PlusPx) {//中央鍾乳石（石）
			if (TXU_Left <= S3_Sky_SStone_1_XL + PlusPx && TXL_Right >= S3_Sky_SStone_1_XL) {//中央鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SStone_1_XU - PlusPx && TXL_Right <= S3_Sky_SStone_1_XU) {//中央鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SGround_2_YU + PlusPx && TYU_Left <= S3_Sky_SGround_2_YL - PlusPx) {//右鍾乳石（地面）
			if (TXU_Left <= S3_Sky_SGround_2_XL + PlusPx && TXL_Right >= S3_Sky_SGround_2_XL) {//右鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SGround_2_XU - PlusPx && TXL_Right <= S3_Sky_SGround_2_XU) {//右鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SStone_2_YU + PlusPx && TYU_Left <= S3_Sky_SStone_2_YL - PlusPx) {//右鍾乳石（石）
			if (TXU_Left <= S3_Sky_SStone_2_XL + PlusPx && TXL_Right >= S3_Sky_SStone_2_XL) {//右鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SStone_2_XU - PlusPx && TXL_Right <= S3_Sky_SStone_2_XU) {//右鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_Ground_0_YU + PlusPx && TYU_Left <= S3_Sky_Ground_0_YL - PlusPx) {//上空中床
			if (TXU_Left <= S3_Sky_Ground_0_XL + PlusPx && TXL_Right >= S3_Sky_Ground_0_XL) {//上空中床の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_Ground_0_XU - PlusPx && TXL_Right <= S3_Sky_Ground_0_XU) {//上空中床の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_Ground_1_YU + PlusPx && TYU_Left <= S3_Sky_Ground_1_YL - PlusPx) {//下空中床
			if (TXU_Left <= S3_Sky_Ground_1_XL + PlusPx && TXL_Right >= S3_Sky_Ground_1_XL) {//下空中床の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_Ground_1_XU - PlusPx && TXL_Right <= S3_Sky_Ground_1_XU) {//下空中床の左
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S3_Sky_SGround_0_YL - PlusPx && TYL_Right >= S3_Sky_SGround_0_YL) {//左鍾乳石（地面）（下辺）
			if (TXU_Left <= S3_Sky_SGround_0_XL && TXL_Right >= S3_Sky_SGround_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SStone_0_YL - PlusPx && TYL_Right >= S3_Sky_SStone_0_YL) {//左鍾乳石（石）（下辺）
			if (TXU_Left <= S3_Sky_SStone_0_XL && TXL_Right >= S3_Sky_SStone_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SGround_1_YL - PlusPx && TYL_Right >= S3_Sky_SGround_1_YL) {//中央鍾乳石（地面）（下辺）
			if (TXU_Left <= S3_Sky_SGround_1_XL && TXL_Right >= S3_Sky_SGround_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SStone_1_YL - PlusPx && TYL_Right >= S3_Sky_SStone_1_YL) {//中央鍾乳石（石）（下辺）
			if (TXU_Left <= S3_Sky_SStone_1_XL && TXL_Right >= S3_Sky_SStone_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SGround_2_YL - PlusPx && TYL_Right >= S3_Sky_SGround_2_YL) {//左鍾乳石（地面）（下辺）
			if (TXU_Left <= S3_Sky_SGround_2_XL && TXL_Right >= S3_Sky_SGround_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SStone_2_YL - PlusPx && TYL_Right >= S3_Sky_SStone_2_YL) {//左鍾乳石（石）（下辺）
			if (TXU_Left <= S3_Sky_SStone_2_XL && TXL_Right >= S3_Sky_SStone_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_Ground_0_YL - PlusPx && TYL_Right >= S3_Sky_Ground_0_YL) {//上空中床（下辺）
			if (TXU_Left <= S3_Sky_Ground_0_XL && TXL_Right >= S3_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_Ground_1_YL - PlusPx && TYL_Right >= S3_Sky_Ground_1_YL) {//下空中床（下辺）
			if (TXU_Left <= S3_Sky_Ground_1_XL && TXL_Right >= S3_Sky_Ground_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
		}

		if (TYU_Left > Sea_Level) {//海面

		}
		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/

		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_SGround_0_YU && TYL_Right <= S3_Sky_SGround_0_YU + PlusPx && TXU_Left <= S3_Sky_SGround_0_XL && TXL_Right >= S3_Sky_SGround_0_XU) {//左鍾乳石（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_SGround_1_YU && TYL_Right <= S3_Sky_SGround_1_YU + PlusPx && TXU_Left <= S3_Sky_SGround_1_XL && TXL_Right >= S3_Sky_SGround_1_XU) {//中央鍾乳石（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_SGround_2_YU && TYL_Right <= S3_Sky_SGround_2_YU + PlusPx && TXU_Left <= S3_Sky_SGround_2_XL && TXL_Right >= S3_Sky_SGround_2_XU) {//右鍾乳石（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_Ground_0_YU && TYL_Right <= S3_Sky_Ground_0_YU + PlusPx && TXU_Left <= S3_Sky_Ground_0_XL && TXL_Right >= S3_Sky_Ground_0_XU) {//上空中床（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_Ground_1_YU && TYL_Right <= S3_Sky_Ground_1_YU + PlusPx && TXU_Left <= S3_Sky_Ground_1_XL && TXL_Right >= S3_Sky_Ground_1_XU) {//下空中床（上辺）
			VectorY *= -COR;
		}

	}
	else if (NowStage == 4) {//***************　４ステージ　***************//
		/*******************************************************************************************************************************/
				//側面の当たり判定//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_0_YU + PlusPx && TYU_Left <= S4_Sky_Ground_0_YL - PlusPx) {//１番左
		if (TXU_Left <= S4_Sky_Ground_0_XL + PlusPx && TXL_Right >= S4_Sky_Ground_0_XL) {//１番左の右
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_0_XU - PlusPx && TXL_Right <= S4_Sky_Ground_0_XU) {//１番左の左
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_1_YU + PlusPx && TYU_Left <= S4_Sky_Ground_1_YL - PlusPx) {//左から２番目
		if (TXU_Left <= S4_Sky_Ground_1_XL + PlusPx && TXL_Right >= S4_Sky_Ground_1_XL) {//左から２番目の右
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_1_XU - PlusPx && TXL_Right <= S4_Sky_Ground_1_XU) {//左から２番目の左
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_2_YU + PlusPx && TYU_Left <= S4_Sky_Ground_2_YL - PlusPx) {//１番上
		if (TXU_Left <= S4_Sky_Ground_2_XL + PlusPx && TXL_Right >= S4_Sky_Ground_2_XL) {//１番上の右
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_2_XU - PlusPx && TXL_Right <= S4_Sky_Ground_2_XU) {//１番上の左
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_3_YU + PlusPx && TYU_Left <= S4_Sky_Ground_3_YL - PlusPx) {//１番下
		if (TXU_Left <= S4_Sky_Ground_3_XL + PlusPx && TXL_Right >= S4_Sky_Ground_3_XL) {//１番下の右
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_3_XU - PlusPx && TXL_Right <= S4_Sky_Ground_3_XU) {//１番下の左
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_4_YU + PlusPx && TYU_Left <= S4_Sky_Ground_4_YL - PlusPx) {//１番右
		if (TXU_Left <= S4_Sky_Ground_4_XL + PlusPx && TXL_Right >= S4_Sky_Ground_4_XL) {//１番右の右
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_4_XU - PlusPx && TXL_Right <= S4_Sky_Ground_4_XU) {//１番右の左
			VectorX *= -COR;
		}
	}
	/*******************************************************************************************************************************/
			//下辺の当たり判定//
	/*******************************************************************************************************************************/
	if (TYU_Left <= S4_Sky_Ground_0_YL - PlusPx && TYL_Right >= S4_Sky_Ground_0_YL) {//１番左
		if (TXU_Left <= S4_Sky_Ground_0_XL && TXL_Right >= S4_Sky_Ground_0_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_1_YL - PlusPx && TYL_Right >= S4_Sky_Ground_1_YL) {//左から２番目
		if (TXU_Left <= S4_Sky_Ground_1_XL && TXL_Right >= S4_Sky_Ground_1_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_2_YL - PlusPx && TYL_Right >= S4_Sky_Ground_2_YL) {//１番上
		if (TXU_Left <= S4_Sky_Ground_2_XL && TXL_Right >= S4_Sky_Ground_2_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_3_YL - PlusPx && TYL_Right >= S4_Sky_Ground_3_YL) {//１番下
		if (TXU_Left <= S4_Sky_Ground_3_XL && TXL_Right >= S4_Sky_Ground_3_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_4_YL - PlusPx && TYL_Right >= S4_Sky_Ground_4_YL) {//１番右
		if (TXU_Left <= S4_Sky_Ground_4_XL && TXL_Right >= S4_Sky_Ground_4_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= 0) {//画面上の当たり判定
		VectorY *= -COR;
	}

	if (TYU_Left > Sea_Level) {//海面

	}
	/*******************************************************************************************************************************/
			//上辺の当たり判定//
	/*******************************************************************************************************************************/

	if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
		VectorY *= -COR;
	}
	else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_0_YU && TYL_Right <= S4_Sky_Ground_0_YU + PlusPx && TXU_Left <= S4_Sky_Ground_0_XL && TXL_Right >= S4_Sky_Ground_0_XU) {//１番左の台
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_1_YU && TYL_Right <= S4_Sky_Ground_1_YU + PlusPx && TXU_Left <= S4_Sky_Ground_1_XL && TXL_Right >= S4_Sky_Ground_1_XU) {//左から２番目の台
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_2_YU && TYL_Right <= S4_Sky_Ground_2_YU + PlusPx && TXU_Left <= S4_Sky_Ground_2_XL && TXL_Right >= S4_Sky_Ground_2_XU) {//１番上の台
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_3_YU && TYL_Right <= S4_Sky_Ground_3_YU + PlusPx && TXU_Left <= S4_Sky_Ground_3_XL && TXL_Right >= S4_Sky_Ground_3_XU) {//１番下の台
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_4_YU && TYL_Right <= S4_Sky_Ground_4_YU + PlusPx && TXU_Left <= S4_Sky_Ground_4_XL && TXL_Right >= S4_Sky_Ground_4_XU) {//１番右の台
		VectorY *= -COR;
	}
	else if (NowStage == 5) {//***************　５ステージ　***************//
		/*******************************************************************************************************************************/
				//側面の当たり判定//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
			VectorX *= -COR;
		}	

		if (TYL_Right >= S5_Sky_SGround_0_YU + PlusPx && TYU_Left <= S5_Sky_SGround_0_YL - PlusPx) {//左鍾乳石
			if (TXU_Left <= S5_Sky_SGround_0_XL + PlusPx && TXL_Right >= S5_Sky_SGround_0_XL) {//左鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_SGround_0_XU - PlusPx && TXL_Right <= S5_Sky_SGround_0_XU) {//左鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_SGround_1_YU + PlusPx && TYU_Left <= S5_Sky_SGround_1_YL - PlusPx) {//中央鍾乳石
			if (TXU_Left <= S5_Sky_SGround_1_XL + PlusPx && TXL_Right >= S5_Sky_SGround_1_XL) {//中央鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_SGround_1_XU - PlusPx && TXL_Right <= S5_Sky_SGround_1_XU) {//中央鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_SGround_2_YU + PlusPx && TYU_Left <= S5_Sky_SGround_2_YL - PlusPx) {//右鍾乳石
			if (TXU_Left <= S5_Sky_SGround_2_XL + PlusPx && TXL_Right >= S5_Sky_SGround_2_XL) {//右鍾乳石の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_SGround_2_XU - PlusPx && TXL_Right <= S5_Sky_SGround_2_XU) {//右鍾乳石の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_Ground_0_YU + PlusPx && TYU_Left <= S5_Sky_Ground_0_YL - PlusPx) {//１番上
			if (TXU_Left <= S5_Sky_Ground_0_XL + PlusPx && TXL_Right >= S5_Sky_Ground_0_XL) {//１番上の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_Ground_0_XU - PlusPx && TXL_Right <= S5_Sky_Ground_0_XU) {//１番上の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_Ground_1_YU + PlusPx && TYU_Left <= S5_Sky_Ground_1_YL - PlusPx) {//下の右
			if (TXU_Left <= S5_Sky_Ground_1_XL + PlusPx && TXL_Right >= S5_Sky_Ground_1_XL) {//下の右の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_Ground_1_XU - PlusPx && TXL_Right <= S5_Sky_Ground_1_XU) {//下の右の左
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_Ground_2_YU + PlusPx && TYU_Left <= S5_Sky_Ground_2_YL - PlusPx) {//下の左
			if (TXU_Left <= S5_Sky_Ground_2_XL + PlusPx && TXL_Right >= S5_Sky_Ground_2_XL) {//下の左の右
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_Ground_2_XU - PlusPx && TXL_Right <= S5_Sky_Ground_2_XU) {//下の左の左
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S5_Sky_SGround_0_YL - PlusPx && TYL_Right >= S5_Sky_SGround_0_YL) {//右鍾乳石
			if (TXU_Left <= S5_Sky_SGround_0_XL && TXL_Right >= S5_Sky_SGround_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_SGround_1_YL - PlusPx && TYL_Right >= S5_Sky_SGround_1_YL) {//中央鍾乳石
			if (TXU_Left <= S5_Sky_SGround_1_XL && TXL_Right >= S5_Sky_SGround_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_SGround_2_YL - PlusPx && TYL_Right >= S5_Sky_SGround_2_YL) {//右鍾乳石
			if (TXU_Left <= S5_Sky_SGround_2_XL && TXL_Right >= S5_Sky_SGround_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_Ground_0_YL - PlusPx && TYL_Right >= S5_Sky_Ground_0_YL) {//１番上
			if (TXU_Left <= S5_Sky_Ground_0_XL && TXL_Right >= S5_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_Ground_1_YL - PlusPx && TYL_Right >= S5_Sky_Ground_1_YL) {//下の右
			if (TXU_Left <= S5_Sky_Ground_1_XL && TXL_Right >= S5_Sky_Ground_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_Ground_2_YL - PlusPx && TYL_Right >= S5_Sky_Ground_2_YL) {//下の左
			if (TXU_Left <= S5_Sky_Ground_2_XL && TXL_Right >= S5_Sky_Ground_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
		}

		if (TYU_Left > Sea_Level) {//海面\

		}
		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/

		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_SGround_0_YU && TYL_Right <= S5_Sky_SGround_0_YU + PlusPx && TXU_Left <= S5_Sky_SGround_0_XL && TXL_Right >= S5_Sky_SGround_0_XU) {//左鍾乳石
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_SGround_1_YU && TYL_Right <= S5_Sky_SGround_1_YU + PlusPx && TXU_Left <= S5_Sky_SGround_1_XL && TXL_Right >= S5_Sky_SGround_1_XU) {//中央鍾乳石
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_SGround_2_YU && TYL_Right <= S5_Sky_SGround_2_YU + PlusPx && TXU_Left <= S5_Sky_SGround_2_XL && TXL_Right >= S5_Sky_SGround_2_XU) {//右鍾乳石
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_Ground_0_YU && TYL_Right <= S5_Sky_Ground_0_YU + PlusPx && TXU_Left <= S5_Sky_Ground_0_XL && TXL_Right >= S5_Sky_Ground_0_XU) {//一番上
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_Ground_1_YU && TYL_Right <= S5_Sky_Ground_1_YU + PlusPx && TXU_Left <= S5_Sky_Ground_1_XL && TXL_Right >= S5_Sky_Ground_1_XU) {//下の左
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_Ground_2_YU && TYL_Right <= S5_Sky_Ground_2_YU + PlusPx && TXU_Left <= S5_Sky_Ground_2_XL && TXL_Right >= S5_Sky_Ground_2_XU) {//下の右
			VectorY *= -COR;
		}
	}
	
}

void Thunder::ThunderAnim()
{
	if (ThunderAnimCnt >= 0 && ThunderAnimCnt <= 2) {
		NowImg = gThunderImg[0];
	}
	else if (ThunderAnimCnt >= 3 && ThunderAnimCnt <= 5) {
		NowImg = gThunderImg[1];
	}
	else if (ThunderAnimCnt <= 6 && ThunderAnimCnt <= 8) {
		NowImg = gThunderImg[2];
	}
}

void Thunder::CloudAnim()
{

	if (CloudAnimCount >= 0 && CloudAnimCount <= 2) {
		CNowImg = gCloudImg[0];
	}
	else if (gWaitTime >= 1500) {

		if (CloudAnimCount >= 3 && CloudAnimCount <= 5) {
			CNowImg = gCloudImg[1];
		}
		else if (CloudAnimCount <= 6 && CloudAnimCount <= 8) {
			CNowImg = gCloudImg[2];
		}
	}
}
