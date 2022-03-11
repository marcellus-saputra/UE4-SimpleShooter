// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* Pawn) 
{
    Super::PawnKilled(Pawn);

    UE_LOG(LogTemp, Warning, TEXT("Pawn %s has been killed."), *Pawn->GetName());

    APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

    if (PlayerController != nullptr) {
        EndGame(false);
    }

    for (AController* Controller : TActorRange<AController>(GetWorld())) {
        AShooterAIController* EnemyController = Cast<AShooterAIController>(Controller);
        if (EnemyController != nullptr && !EnemyController->IsDead()) return;
    }

    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bPlayerWin) 
{
    for (AController* Controller : TActorRange<AController>(GetWorld())) {

        bool bIsWinner = Controller->IsPlayerController() == bPlayerWin;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

        // if (Controller->IsPlayerController()) {
        //     if (bPlayerWin) {
        //         Controller->GameHasEnded(nullptr, true);
        //     } else {
        //         Controller->GameHadEnded(nullptr, false);
        //     }
        // } else {
        //     if (bPlayerWin) {
        //         Controller->GameHasEnded(nullptr, false);
        //     } else {
        //         Controller->GameHasEnded(nullptr, true);
        //     }
        // }
    }
}
