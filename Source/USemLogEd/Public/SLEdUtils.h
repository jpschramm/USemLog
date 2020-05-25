// Copyright 2017-2020, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"

/**
 * Static helpers functions for the semantic logger editor module tookit
 */
class USEMLOGED_API FSLEdUtils
{
public:
	// Write the semantic map
	static void WriteSemanticMap(UWorld* World, bool bOverwrite = false);

	/* Individual actor components */
	static void CreateSemanticDataComponents(UWorld* World, bool bOverwrite = false);
	static void CreateSemanticDataComponents(const TArray<AActor*>& Actors, bool bOverwrite = false);
	static void ReLoadSemanticDataComponents(UWorld* World);
	static void ReLoadSemanticDataComponents(const TArray<AActor*>& Actors);
	static void RemoveSemanticDataComponents(UWorld* World);
	static void RemoveSemanticDataComponents(const TArray<AActor*>& Actors);

	/* Semantic data components functionalities*/
	static void ToggleMasks(UWorld* World);
	static void ToggleMasks(const TArray<AActor*>& Actors);

	/* Individual actor visual info */
	static void CreateVisualInfoComponents(UWorld* World, bool bOverwrite = false);
	static void CreateVisualInfoComponents(const TArray<AActor*>& Actors, bool bOverwrite = false);
	static void RefreshVisualInfoComponents(UWorld* World);
	static void RefreshVisualInfoComponents(const TArray<AActor*>& Actors);
	static void RemoveVisualInfoComponents(UWorld* World);
	static void RemoveVisualInfoComponents(const TArray<AActor*>& Actors);
	static void ToggleVisualInfoComponents(UWorld* World);
	static void ToggleVisualInfoComponents(const TArray<AActor*>& Actors);

	// Save components data to tags
	static void ExportToTag(UWorld* World, bool bOverwrite = false);
	static void ExportToTag(const TArray<AActor*>& Actors, bool bOverwrite = false);

	// Loads components data from tags
	static void ImportFromTag(UWorld* World, bool bOverwrite = false);
	static void ImportFromTag(const TArray<AActor*>& Actors, bool bOverwrite = false);

	/* Ids */
	static void WriteUniqueIds(UWorld* World, bool bOverwrite = false);
	static void WriteUniqueIds(const TArray<AActor*>& Actors, bool bOverwrite = false);
	static void RemoveUniqueIds(UWorld* World);
	static void RemoveUniqueIds(const TArray<AActor*>& Actors);

	/* Class names */
	static void WriteClassNames(UWorld* World, bool bOverwrite = false);
	static void WriteClassNames(const TArray<AActor*>& Actors, bool bOverwrite = false);
	static void RemoveClassNames(UWorld* World);
	static void RemoveClassNames(const TArray<AActor*>& Actors);

	/* Visual masks */
	static void WriteVisualMasks(UWorld* World, bool bOverwrite = false);
	static void WriteVisualMasks(const TArray<AActor*>& Actors, UWorld* World, bool bOverwrite = false);
	static void RemoveVisualMasks(UWorld* World);
	static void RemoveVisualMasks(const TArray<AActor*>& Actors);

	// Remove all tag keys
	static void RemoveTagKey(UWorld* World, const FString& TagType, const FString& TagKey);
	static void RemoveTagKey(const TArray<AActor*>& Actors, const FString& TagType, const FString& TagKey);

	// Remove all types
	static void RemoveTagType(UWorld* World, const FString& TagType);
	static void RemoveTagType(const TArray<AActor*>& Actors, const FString& TagType);

	// Add the semantic monitor components registered to tags to the actors
	static void AddSemanticMonitorComponents(UWorld* World, bool bOverwrite = false);
	static void AddSemanticMonitorComponents(const TArray<AActor*>& Actors, bool bOverwrite = false);

	// Enable overlaps on actors
	static void EnableOverlaps(UWorld* World);
	static void EnableOverlaps(const TArray<AActor*>& Actors);
	
	// Toggle between showing the semantic data of the entities in the world
	static void ShowSemanticData(UWorld* World);
	static void ShowSemanticData(const TArray<AActor*>& Actors);

	// Enable all materials for instanced static mesh rendering
	static void EnableAllMaterialsForInstancedStaticMesh();

private:

	/* Semantic data components */
	// Reset semantic individual component
	static void LoadSemanticIndividualComponent(AActor* Actor);

	// Remove semantic individual component
	static void RemoveSemanticIndividualComponent(AActor* Actor);

	// Show hide the visual mask 
	static void ToggleVisualMaskVisibility(AActor* Actor);

	// Save semantic individual data to tag
	static void ExportIndividualDataToTag(AActor* Actor, bool bOverwrite = false);

	// Save semantic individual data to tag
	static void ImportIndividualDataFromTag(AActor* Actor, bool bOverwrite = false);


	/* Visual info components */
	// Refresh the visual info component
	static void RefreshVisualInfoComponent(AActor* Actor);

	// Remove the visual info component
	static void RemoveVisualInfoComponent(AActor* Actor);

	// Show hide semantic text information
	static void ToggleVisualInfo(AActor* Actor);


	/* Helpers */
	// Get the individual component of the actor (nullptr if none found)
	FORCEINLINE static class USLIndividualComponent* GetIndividualComponent(AActor* Actor);

	// Get the visual info component of the actor (nullptr if none found)
	FORCEINLINE static class USLIndividualVisualInfo* GetVisualInfoComponent(AActor* Actor);



	//// Generate unique visual masks using incremental heuristic
	//static void WriteIncrementallyGeneratedVisualMasks(UWorld* World, bool bOverwrite = false);

	//// Get already used visual mask colors
	//static TArray<FColor> GetConsumedVisualMaskColors(UWorld* World);

	//// Add unique mask color
	//static bool AddUniqueVisualMask(AActor* Actor, TArray<FColor>& ConsumedColors, bool bOverwrite = false);

	//// Generate a new unique color in hex, avoiding any from the used up array
	//static FColor NewRandomlyGeneratedUniqueColor(TArray<FColor>& ConsumedColors, int32 NumberOfTrials = 100, int32 MinManhattanDistance = 29);

	///* Color helpers */
	//// Get the manhattan distance between the colors
	//FORCEINLINE static int32 ColorManhattanDistance(const FColor& C1, const FColor& C2)
	//{
	//	return FMath::Abs(C1.R - C2.R) + FMath::Abs(C1.G - C2.G) + FMath::Abs(C1.B - C2.B);
	//}

	//// Check if the two colors are equal with a tolerance
	//FORCEINLINE static bool ColorEqual(const FColor& C1, const FColor& C2, uint8 Tolerance = 0)
	//{
	//	if (Tolerance < 1) { return C1 == C2; }
	//	return ColorManhattanDistance(C1, C2) <= Tolerance;
	//}

	//// Generate a random color
	//FORCEINLINE static FColor ColorRandomRGB()
	//{
	//	return FColor((uint8)(FMath::FRand() * 255.f), (uint8)(FMath::FRand() * 255.f), (uint8)(FMath::FRand() * 255.f));
	//}

	//// Backlog
	//// Add unique id to the tag of the actor if the actor is a known type
	//static bool AddUniqueIdToTag(AActor* Actor, bool bOverwrite = false);

	//// Get class name of actor (if not known use label name if bDefaultToLabelName is true)
	//static FString GetClassName(AActor* Actor, bool bDefaultToLabelName = false);
};