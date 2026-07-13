// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessActorBeginOverlap);
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyRocket::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OverlappedActor->ActorHasTag(TEXT("Player")))
	{
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("BeginOverlap %s"), *OtherActor->GetName());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionTemplate,
		GetActorLocation());
	UGameplayStatics::SpawnSound2D(GetWorld(), ExplosionSound);

	UGameplayStatics::ApplyDamage(OtherActor,
		10,
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		this,
		nullptr
	);
	
	//Blueprint 함수 호출 하고 싶어요
	CallCPPExecuteBP();

	//Blueprint 함수 호출 하고 싶어요(니가 안하면 내가 기본으로 한다.
	CallCPPExecuteBPDefault();

	Destroy();

}

void AMyRocket::CallCPPExecuteBPDefault_Implementation(void)
{
	UE_LOG(LogTemp, Warning, TEXT("Execute CPP"));
}

