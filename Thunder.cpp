#include "Thunder.h"
#include "Thunderbolt.h"
#include "Common.h"

Thunder::Thunder() 
{

}

//描画以外の更新を実装する
void Thunder::Update() 
{
	for (Num = 0; Num < 2; Num++) {
		FinThunderboltAnimFlg[Num] = Thunderbolt::FinAnimFlg[Num];

	}
}

//描画の更新を実装する
void Thunder::Draw() 
{

}