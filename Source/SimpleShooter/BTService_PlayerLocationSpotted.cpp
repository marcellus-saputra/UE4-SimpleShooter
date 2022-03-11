// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationSpotted.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_PlayerLocationSpotted::UBTService_PlayerLocationSpotted() 
{
    NodeName = TEXT("Update PlayerLocation if spotted");
}

void UBTService_PlayerLocationSpotted::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerPawn == nullptr) return;

    AAIController* AIController = OwnerComp.GetAIOwner();

    if (AIController == nullptr) return;

    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    } else {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
