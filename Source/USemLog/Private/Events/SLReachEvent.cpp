// Copyright 2017-present, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "Events/SLReachEvent.h"
#include "Individuals/Type/SLBaseIndividual.h"
#include "Owl/SLOwlExperimentStatics.h"

// Constructor with initialization
FSLReachEvent::FSLReachEvent(const FString& InId, const float InStart, const float InEnd, const uint64 InPairId,
	USLBaseIndividual* InManipulator, USLBaseIndividual* InIndividual) :
	ISLEvent(InId, InStart, InEnd), PairId(InPairId), Manipulator(InManipulator), Individual(InIndividual)
{
}

// Constructor initialization without end time
FSLReachEvent::FSLReachEvent(const FString& InId, const float InStart, const uint64 InPairId,
	USLBaseIndividual* InIndividual, USLBaseIndividual* InManipulator) :
	ISLEvent(InId, InStart), PairId(InPairId), Manipulator(InManipulator), Individual(InIndividual)
{
}

/* Begin ISLEvent interface */
// Get an owl representation of the event
FSLOwlNode FSLReachEvent::ToOwlNode() const
{
	// Create the Reach event node
	FSLOwlNode EventIndividual = FSLOwlExperimentStatics::CreateEventIndividual(
		"log", Id, "ReachingForSomething");
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateStartTimeProperty("log", StartTime));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateEndTimeProperty("log", EndTime));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreatePerformedByProperty("log", Manipulator->GetIdValue()));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateObjectActedOnProperty("log", Individual->GetIdValue()));
	EventIndividual.AddChildNode(FSLOwlExperimentStatics::CreateInEpisodeProperty("log", EpisodeId));
	return EventIndividual;
}

// Add the owl representation of the event to the owl document
void FSLReachEvent::AddToOwlDoc(FSLOwlDoc* OutDoc)
{
	// Add timepoint individuals
	// We know that the document is of type FOwlExperiment,
	// we cannot use the safer dynamic_cast because RTTI is not enabled by default
	// if (FOwlEvents* EventsDoc = dynamic_cast<FOwlEvents*>(OutDoc))
	FSLOwlExperiment* EventsDoc = static_cast<FSLOwlExperiment*>(OutDoc);
	EventsDoc->RegisterTimepoint(StartTime);
	EventsDoc->RegisterTimepoint(EndTime);
	EventsDoc->RegisterObject(Manipulator);
	EventsDoc->RegisterObject(Individual);
	OutDoc->AddIndividual(ToOwlNode());
}

// Get event context data as string (ToString equivalent)
FString FSLReachEvent::Context() const
{
	return FString::Printf(TEXT("Reach - %lld"), PairId);
}

// Get the tooltip data
FString FSLReachEvent::Tooltip() const
{
	return FString::Printf(TEXT("\'O1\',\'%s\',\'Id\',\'%s\',\'O2\',\'%s\',\'Id\',\'%s\',\'Id\',\'%s\'"),
		*Manipulator->GetClassValue(), *Manipulator->GetIdValue(), *Individual->GetClassValue(), *Individual->GetIdValue(), *Id);
}

// Get the data as string
FString FSLReachEvent::ToString() const
{
	return FString::Printf(TEXT("Individual:[%s] Manipulator:[%s] PairId:%lld"),
		*Manipulator->GetInfo(), *Individual->GetInfo(), PairId);
}

FString FSLReachEvent::RESTCallToKnowRob(FSLKRRestClient* InFSLKRRestClient) const
{
	// Call REST method to create sub actions on KnowRob side.
	// somaClassName:somaIndividualName is sent at the moment for objects participated
	FString ObjectsPartcipated = TEXT("[") 
		+ Individual->GetClassValue() + TEXT(":") + Individual->GetParentActor()->GetActorLabel() 
		+ TEXT(",") 
		+ Manipulator->GetClassValue() + TEXT(":") + Manipulator->GetParentActor()->GetActorLabel() 
		+ TEXT("]");


	FString SubActionType = TEXT("soma:'Reach'");
	FString TaskType = TEXT("soma:'Reaching'");

	FString AdditionalEventInfo = TEXT("");
	InFSLKRRestClient->SendCreateSubActionRequest(SubActionType, TaskType,
		ObjectsPartcipated, AdditionalEventInfo, double(StartTime), double(EndTime));

	return TEXT("Succeed!");
}
/* End ISLEvent interface */