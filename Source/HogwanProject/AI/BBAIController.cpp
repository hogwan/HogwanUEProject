// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABBAIController::ABBAIController()
{
	
}

void ABBAIController::ChangeAIState(uint8 _StateType)
{
	UBlackboardComponent* BB = GetBlackboardComponent();
	BB->SetValueAsEnum(TEXT("StateValue"), _StateType);
}
