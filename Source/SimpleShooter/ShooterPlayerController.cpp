// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    
    HUD->RemoveFromViewport();
    if (!bIsWinner) {
        UE_LOG(LogTemp, Warning, TEXT("You have lost."));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("You have won!"));
    }
    
    if (bIsWinner) {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenWidget);
        if (WinScreen != nullptr) {
            WinScreen->AddToViewport();
        }
    } else {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenWidget);
        if (LoseScreen != nullptr) {
            LoseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDWidget);
    if (HUD != nullptr) {
        HUD->AddToViewport();
    }
}
