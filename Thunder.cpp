#include "Thunder.h"
#include "Thunderbolt.h"
#include "Common.h"

Thunder::Thunder() 
{

}

//�`��ȊO�̍X�V����������
void Thunder::Update() 
{
	for (Num = 0; Num < 2; Num++) {
		FinThunderboltAnimFlg[Num] = Thunderbolt::FinAnimFlg[Num];

	}
}

//�`��̍X�V����������
void Thunder::Draw() 
{

}