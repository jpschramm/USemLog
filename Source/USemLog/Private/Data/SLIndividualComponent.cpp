// Copyright 2017-2020, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "Data/SLIndividualComponent.h"
#include "Data/SLIndividual.h"
#include "Data/SLSkeletalIndividual.h"
#include "Data/SLVisualIndividual.h"

// Sets default values for this component's properties
USLIndividualComponent::USLIndividualComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsInit = false;
	bIsLoaded = false;

	bOverwriteEditChanges = false;
	bSaveToTagButton = false;
	bLoadFromTagButton = false;
	bToggleVisualMaskMaterial = false;
	bToggleSemanticText = false;
}

// Called before destroying the object.
void USLIndividualComponent::BeginDestroy()
{
	Super::BeginDestroy();
	if (SemanticIndividual)
	{
		SemanticIndividual->ConditionalBeginDestroy();
	}
}

// Called after the C++ constructor and after the properties have been initialized, including those loaded from config.
void USLIndividualComponent::PostInitProperties()
{
	Super::PostInitProperties();

	Init();
	Load();
}

#if WITH_EDITOR
// Called when a property is changed in the editor
void USLIndividualComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Get the changed property name
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ?
		PropertyChangedEvent.Property->GetFName() : NAME_None;

	// Convert datatype
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USLIndividualComponent, ConvertTo))
	{
		FSLIndividualUtils::ConvertIndividualObject(SemanticIndividual, ConvertTo);
	}

	/* Button workaround triggers */
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(USLIndividualComponent, bSaveToTagButton))
	{
		bSaveToTagButton = false;
		ExportToTag(bOverwriteEditChanges);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(USLIndividualComponent, bLoadFromTagButton))
	{
		bLoadFromTagButton = false;
		ImportFromTag(bOverwriteEditChanges);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(USLIndividualComponent, bToggleVisualMaskMaterial))
	{
		bToggleVisualMaskMaterial = false;
		ToggleVisualMaskVisibility();
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(USLIndividualComponent, bToggleSemanticText))
	{
		bToggleSemanticText = false;
		ToggleSemanticTextVisibility();
	}
}
#endif // WITH_EDITOR

//// Called when a component is created(not loaded).This can happen in the editor or during gameplay
//void USLIndividualComponent::OnComponentCreated()
//{
//	Super::OnComponentCreated();
//
//	AActor* Owner = GetOwner();
//
//	if (Owner)
//	{
//		UE_LOG(LogTemp, Log, TEXT("%s::%d"), *FString(__FUNCTION__), __LINE__);
//	}
//
//	// Check if actor already has a semantic data component
//	for (const auto AC : Owner->GetComponentsByClass(USLIndividualComponent::StaticClass()))
//	{
//		if (AC != this)
//		{
//			UE_LOG(LogTemp, Error, TEXT("%s::%d %s already has a semantic data component (%s), self-destruction commenced.."),
//				*FString(__FUNCTION__), __LINE__, *GetOwner()->GetName(), *AC->GetName());
//			//DestroyComponent();
//			ConditionalBeginDestroy();
//			return;
//		}
//	}
//
//	// Set semantic individual type depending on owner
//	if (UClass* IndividualClass = FSLIndividualUtils::CreateIndividualObject(this, Owner, SemanticIndividual))
//	{
//		// Cache the current individual class type
//		ConvertTo = IndividualClass;
//	}
//	else
//	{
//		// Unknown individual type, destroy self
//		ConditionalBeginDestroy();
//		return;
//	}
//}

// Called when the game starts
void USLIndividualComponent::BeginPlay()
{
	Super::BeginPlay();
}

//
bool USLIndividualComponent::Init(bool bForced)
{
	if (bForced)
	{
		bIsInit = false;
	}

	if (IsInit())
	{
		return true;
	}

	bIsInit = InitImpl();
	return bIsInit;
}

//
bool USLIndividualComponent::Load(bool bForced)
{
	if (bForced)
	{
		bIsLoaded = false;
	}

	if (IsLoaded())
	{
		return true;
	}

	if (!IsInit())
	{
		if (!Init(bForced))
		{
			return false;
		}
	}

	bIsLoaded = LoadImpl();
	return bIsLoaded;
}

// Save data to owners tag
void USLIndividualComponent::ExportToTag(bool bOverwrite)
{
	if (SemanticIndividual)
	{
		SemanticIndividual->ExportToTag(bOverwrite);
	}
}

// Load data from owners tag
void USLIndividualComponent::ImportFromTag(bool bOverwrite)
{
	if (SemanticIndividual)
	{
		SemanticIndividual->ImportFromTag(bOverwrite);
	}
}

//// Reload the individual data
//bool USLIndividualComponent::LoadIndividual()
//{
//	if (SemanticIndividual->IsValidLowLevel())
//	{
//		SemanticIndividual->Load();
//	}
//	return false;
//}

// Toggle between original and mask material is possible
bool USLIndividualComponent::ToggleVisualMaskVisibility()
{
	if (USLVisualIndividual* SI = GetCastedIndividualObject<USLVisualIndividual>())
	{
		return SI->ToggleMaterials();
	}
	return false;
}

// Toggle between showing the semantic data in text form
bool USLIndividualComponent::ToggleSemanticTextVisibility()
{
	return false;
}

// Private init implementation
bool USLIndividualComponent::InitImpl()
{
	AActor* Owner = GetOwner();

	if (!Owner)
	{
		return false;
	}

	// Check if actor already has a semantic data component
	for (const auto AC : Owner->GetComponentsByClass(USLIndividualComponent::StaticClass()))
	{
		if (AC != this)
		{
			UE_LOG(LogTemp, Error, TEXT("%s::%d %s already has a semantic data component (%s), self-destruction commenced.."),
				*FString(__FUNCTION__), __LINE__, *GetOwner()->GetName(), *AC->GetName());
			//DestroyComponent();
			ConditionalBeginDestroy();
			return false;
		}
	}

	// Set semantic individual type depending on owner
	if (UClass* IndividualClass = FSLIndividualUtils::CreateIndividualObject(this, Owner, SemanticIndividual))
	{
		// Cache the current individual class type
		ConvertTo = IndividualClass;		
		//SemanticIndividual->Init(); // Is being called automatically on PostInitProperties		
		return true;
	}
	else
	{
		// Unknown individual type, destroy self
		ConditionalBeginDestroy();
		return false;
	}
}

// Private load implementation
bool USLIndividualComponent::LoadImpl()
{
	if (SemanticIndividual)
	{
		return SemanticIndividual->ImportFromTag() && SemanticIndividual->Load();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s::%d This should not happen.."), *FString(__FUNCTION__), __LINE__);
		return false;
	}
}


