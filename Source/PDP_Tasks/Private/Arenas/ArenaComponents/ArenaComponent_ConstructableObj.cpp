#include "Arenas/ArenaComponents/ArenaComponent_ConstructableObj.h"

AArenaComponent_ConstructableObj::AArenaComponent_ConstructableObj()
{
	// FixConnections();
}

void AArenaComponent_ConstructableObj::FixAllConnections()
{
	FixConnection(Up, ComponentConnection.UpConnection);
	FixConnection(Down, ComponentConnection.DownConnection);
	FixConnection(Left, ComponentConnection.LeftConnection);
	FixConnection(Right, ComponentConnection.RightConnection);
}

void AArenaComponent_ConstructableObj::FixConnection(const EConnectionDirection Direction,
                                                     FConstructableComponent Connection)
{
	if (Connection.ConstructableObj /*&& !Connection.bIsCatched*/)
	{
		Connection.bIsCatched = true;

		AArenaComponent_ConstructableObj* ConstructableObj =
			Cast<AArenaComponent_ConstructableObj>(Connection.ConstructableObj);
		if (!ConstructableObj)
		{
			ConstructableObj->Destroy();
			return;
		}

		ConstructableObj->SetActorLocation(FixLocation(Direction));
		CheckConnections(Direction, ConstructableObj);

		Connection.bIsCatched = false;

		ConstructableObj->FixAllConnections();
	}
}

FVector AArenaComponent_ConstructableObj::FixLocation(const EConnectionDirection Direction) const
{
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;

	switch (Direction)
	{
	case Up:
		X = GetActorLocation().X + (Width * 100.f);
		Y = GetActorLocation().Y;
		Z = GetActorLocation().Z;
		break;

	case Down:
		X = GetActorLocation().X - (Width * 100.f);
		Y = GetActorLocation().Y;
		Z = GetActorLocation().Z;
		break;

	case Left:
		X = GetActorLocation().X;
		Y = GetActorLocation().Y - (Length * 100.f);
		Z = GetActorLocation().Z;
		break;

	case Right:
		X = GetActorLocation().X;
		Y = GetActorLocation().Y + (Length * 100.f);
		Z = GetActorLocation().Z;
		break;

	default: break;
	}

	return FVector(X, Y, Z);
}

void AArenaComponent_ConstructableObj::CheckConnections(EConnectionDirection Direction,
                                                        AArenaComponent_ConstructableObj* ConstructableObj)
{
	switch (Direction)
	{
	case Up:
		if (!ConstructableObj->ComponentConnection.DownConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.DownConnection.ConstructableObj = this;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	case Down:
		if (!ConstructableObj->ComponentConnection.UpConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.UpConnection.ConstructableObj = this;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	case Left:
		if (!ConstructableObj->ComponentConnection.RightConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.RightConnection.ConstructableObj = this;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	case Right:
		if (!ConstructableObj->ComponentConnection.LeftConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.LeftConnection.ConstructableObj = this;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	default: break;
	}
}
