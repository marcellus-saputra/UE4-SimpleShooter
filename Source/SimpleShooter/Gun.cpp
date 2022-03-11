// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger() 
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	AController* OwnerController = GetOwnerController();

	FRotator PlayerViewPointRotation;
	FHitResult HitResult;
	bool bObjectHit = GunRayTrace(HitResult, PlayerViewPointRotation, OwnerController);

	if (bObjectHit) {
		FVector HitLocation = HitResult.Location;
		FVector ImpactDirection = PlayerViewPointRotation.Vector();

		// DrawDebugPoint(GetWorld(), HitLocation, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitLocation, ImpactDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitLocation, 0.1f);

		FPointDamageEvent DamageEvent(Damage, HitResult, ImpactDirection, nullptr);
		AActor* DamagedActor = HitResult.GetActor();
		if (DamagedActor != nullptr) {
			DamagedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			//UE_LOG(LogTemp, Warning, TEXT("%s took damage."), *DamagedActor->GetName());
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Need to output ShotDirection to call the PointDamageEvent in TriggerPull
bool AGun::GunRayTrace(FHitResult &HitResult, FRotator &ShotDirection, AController* OwnerController) 
{
	if (OwnerController == nullptr) return false;

	FVector PlayerViewPointLocation;
	OwnerController->GetPlayerViewPoint(PlayerViewPointLocation, ShotDirection);

	FVector TraceEnd = PlayerViewPointLocation + ShotDirection.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewPointLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}
