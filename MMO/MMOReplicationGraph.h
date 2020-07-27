// Copyright 2018 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "ReplicationGraph.h"
#include "MMOPlayerState.h"
#include "MMOReplicationGraph.generated.h"

USTRUCT()
struct FMMOConnectionAlwaysRelevantNodePair
{
	GENERATED_BODY()
		FMMOConnectionAlwaysRelevantNodePair() { }
	FMMOConnectionAlwaysRelevantNodePair(UNetConnection* InConnection, UReplicationGraphNode_AlwaysRelevant_ForConnection* InNode) : NetConnection(InConnection), Node(InNode) { }
	bool operator==(const UNetConnection* InConnection) const { return InConnection == NetConnection; }

	UPROPERTY()
		UNetConnection* NetConnection = nullptr;

	UPROPERTY()
		UReplicationGraphNode_AlwaysRelevant_ForConnection* Node = nullptr;
};

/**
 * 
 */
UCLASS(transient, config = Engine)
class MMO_API UMMOReplicationGraph : public UReplicationGraph
{
	GENERATED_BODY()
	
public:

	UMMOReplicationGraph();

	virtual void InitGlobalActorClassSettings() override;
	virtual void InitGlobalGraphNodes() override;
	virtual void InitConnectionGraphNodes(UNetReplicationGraphConnection* RepGraphConnection) override;
	virtual void RouteAddNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalInfo) override;
	virtual void RouteRemoveNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo) override;

	virtual int32 ServerReplicateActors(float DeltaSeconds) override;

	UMMOReplicationGraphNode_AlwaysRelevantToParty* GetNodeForParty(int32 PartyID);

  UFUNCTION(BlueprintCallable)
 	void AddPlayerToParty(AMMOPlayerState* PS);

	UPROPERTY()
		UReplicationGraphNode_GridSpatialization2D* GridNode;

	UPROPERTY()
		UReplicationGraphNode_ActorList* AlwaysRelevantNode;

	UPROPERTY()
		TArray<FMMOConnectionAlwaysRelevantNodePair> AlwaysRelevantForConnectionList;

	/** Actors that are only supposed to replicate to their owning connection, but that did not have a connection on spawn */
	UPROPERTY()
		TArray<AActor*> ActorsWithoutNetConnection;

	UPROPERTY()
		TMap<int32, UMMOReplicationGraphNode_AlwaysRelevantToParty*> PartyMap;

	UReplicationGraphNode_AlwaysRelevant_ForConnection* GetAlwaysRelevantNodeForConnection(UNetConnection* Connection);
};


/** This is a specialized node for handling PlayerState replication in a frequency limited fashion. It tracks all player states but only returns a subset of them to the replication driver each frame. */
UCLASS()
class UMMOReplicationGraphNode_PlayerStateFrequencyLimiter : public UReplicationGraphNode
{
	GENERATED_BODY()

		UMMOReplicationGraphNode_PlayerStateFrequencyLimiter();

	virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& Actor) override { }
	virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound = true) override { return false; }

	virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;

	virtual void PrepareForReplication() override;

	virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;

	/** How many actors we want to return to the replication driver per frame. Will not suppress ForceNetUpdate. */
	int32 TargetActorsPerFrame = 2;

private:

	TArray<FActorRepListRefView> ReplicationActorLists;
	FActorRepListRefView ForceNetUpdateReplicationActorList;
};


/** Always relevant party ID **/
UCLASS()
class UMMOReplicationGraphNode_AlwaysRelevantToParty : public UReplicationGraphNode
{
	GENERATED_BODY()

public:

	UMMOReplicationGraphNode_AlwaysRelevantToParty();

	int32 PartyID;
	bool UpdatePerConnectionCullDistance;
	TArray<AMMOPlayerState*> PlayerStates;

	virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;
	virtual void PrepareForReplication() override;
	virtual void LogNode(FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName) const override;

	/*virtual void NotifyAddNetworkActor(const FNewReplicatedActorInfo& Actor) override { }
	virtual bool NotifyRemoveNetworkActor(const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound = true) override { return false; }

		
	*/

private:
	
	FActorRepListRefView ReplicationActorList;
};