#include "Arenas/ArenaComponents/ArenaComponent_ConstructableObj.h"


void AArenaComponent_ConstructableObj::FixAllConnections()
{
	// Set flag to prevent fixing current component
	bIsFixed = true;
	
	FixConnection(Up, ComponentConnection.UpConnection);
	FixConnection(Down, ComponentConnection.DownConnection);
	FixConnection(Left, ComponentConnection.LeftConnection);
	FixConnection(Right, ComponentConnection.RightConnection);
}


void AArenaComponent_ConstructableObj::FixConnection(const EConnectionDirection Direction,
                                                     FComponentInfo Connection)
{
	// Cast to AArenaComponent_ConstructableObj
	AArenaComponent_ConstructableObj* ConstructableObj =
		Cast<AArenaComponent_ConstructableObj>(Connection.ConstructableObj);

	// If cast successful and component was not fixed
	if (ConstructableObj && !(ConstructableObj->bIsFixed))
	{
		FixLocation(Direction, ConstructableObj);
		CheckConnections(Direction, ConstructableObj);

		ConstructableObj->FixAllConnections();
	}
}

void AArenaComponent_ConstructableObj::FixLocation(const EConnectionDirection Direction,
                                                   AArenaComponent_ConstructableObj* ConstructableObj) const
{
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;

	switch (Direction)
	{
	case Up:
		// Calculate distance by using scalable params
		X = GetActorLocation().X + (Width * 50.f) + (ConstructableObj->Width * 50.f);
		Y = GetActorLocation().Y;
		Z = GetActorLocation().Z;
		break;

	case Down:
		X = GetActorLocation().X - (Width * 50.f) - (ConstructableObj->Width * 50.f);
		Y = GetActorLocation().Y;
		Z = GetActorLocation().Z;
		break;

	case Left:
		X = GetActorLocation().X;
		Y = GetActorLocation().Y - (Length * 50.f) - (ConstructableObj->Length * 50.f);
		Z = GetActorLocation().Z;
		break;

	case Right:
		X = GetActorLocation().X;
		Y = GetActorLocation().Y + (Length * 50.f) + (ConstructableObj->Length * 50.f);
		Z = GetActorLocation().Z;
		break;

	default: break;
	}

	ConstructableObj->SetActorLocation(FVector(X, Y, Z));
}

void AArenaComponent_ConstructableObj::CheckConnections(const EConnectionDirection Direction,
                                                        AArenaComponent_ConstructableObj* ConstructableObj)
{
	switch (Direction)
	{
	case Up:
		// If other component does not have connection
		if (!ConstructableObj->ComponentConnection.DownConnection.ConstructableObj)
		{
			// Add this component to other component
			ConstructableObj->ComponentConnection.DownConnection.ConstructableObj = this;
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	case Down:
		if (!ConstructableObj->ComponentConnection.UpConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.UpConnection.ConstructableObj = this;
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	case Left:
		if (!ConstructableObj->ComponentConnection.RightConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.RightConnection.ConstructableObj = this;
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	case Right:
		if (!ConstructableObj->ComponentConnection.LeftConnection.ConstructableObj)
		{
			ConstructableObj->ComponentConnection.LeftConnection.ConstructableObj = this;
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Changed"));
		}
		break;

	default: break;
	}
}
