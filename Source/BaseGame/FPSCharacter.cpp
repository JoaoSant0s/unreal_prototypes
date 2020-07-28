// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DamageableActor.h"

#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FHitResult AFPSCharacter::InstantShot() {
	FVector rayLocation;
	FRotator rayRotation;
	FVector endTrace = FVector::ZeroVector;

	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
		
	if (playerController) {	
		UE_LOG(LogTemp, Warning, TEXT("PlayerController!"));

		playerController->GetPlayerViewPoint(rayLocation, rayRotation);
		endTrace = rayLocation + (rayRotation.Vector() * weaponRange);
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(InstantShot), true, Instigator);
	FHitResult outHit(ForceInit);	

	GetWorld()->LineTraceSingleByChannel(outHit, rayLocation, endTrace, ECC_Visibility, traceParams);

	return outHit;
}

void AFPSCharacter::FireWeapon() 
{
	FHitResult hit = InstantShot();
	ADamageableActor * actor = Cast<ADamageableActor>(hit.Actor);
				
	if (actor && actor->isAttackable) {		
		actor->TakeAttack(weaponDamage);
	}	
}
