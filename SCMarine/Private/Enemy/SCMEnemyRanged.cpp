// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SCMEnemyRanged.h"

void ASCMEnemyRanged::RangedAttack()
{
	// Select a random attack montage to play.
	UAnimMontage* SelectedMontage = ChooseAttackMontage(RangedAttackMontages);
	if (SelectedMontage)
	{
		PlayAnimMontage(SelectedMontage);
	}
	return;
}
