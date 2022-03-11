// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay() {
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); 

    if (AIBehavior != nullptr) {
        RunBehaviorTree(AIBehavior);
        BlackboardComponent = GetBlackboardComponent();
        BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

    // if (LineOfSightTo(PlayerPawn)) {
    //     FVector PlayerLocation = PlayerPawn->GetActorLocation();
    //     BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
    //     BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerLocation);
    // } else {
    //     BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
    // }

    // if (LineOfSightTo(PlayerPawn)) {
    //     SetFocus(PlayerPawn);
    //     MoveToActor(PlayerPawn, 200);
    // } else {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }
}

bool AShooterAIController::IsDead() 
{
    AShooterCharacter* ControlledPawn = Cast<AShooterCharacter>(GetPawn());
    if (ControlledPawn != nullptr) return ControlledPawn->IsDead();

    return true;
}

