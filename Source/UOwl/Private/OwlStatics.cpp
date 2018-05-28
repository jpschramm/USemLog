// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "OwlStatics.h"

/* Owl individuals creation */
// Create an object entry
FOwlNode FOwlStatics::CreateObjectIndividual(const FString& Id, const FString& Class)
{
	// Prefix name constants
	const FOwlPrefixName RdfAbout("rdf", "about");
	const FOwlPrefixName OwlNI("owl", "NamedIndividual");

	FOwlNode ObjectIndividual(OwlNI, FOwlAttribute(RdfAbout, FOwlAttributeValue("log", Id)));
	ObjectIndividual.Comment = TEXT("Object " + Class + " " + Id);
	ObjectIndividual.ChildNodes.Add(FOwlStatics::CreateClassProperty(Class));
	return ObjectIndividual;
}

// Create a pose entry
FOwlNode FOwlStatics::CreatePoseIndividual(const FString& InId, const FVector& InLoc, const FQuat& InQuat)
{
	// Prefix name constants
	const FOwlPrefixName RdfAbout("rdf", "about");
	const FOwlPrefixName RdfType("rdf", "type");
	const FOwlPrefixName RdfResource("rdf", "resource");
	const FOwlPrefixName OwlNI("owl", "NamedIndividual");

	// Attribute values constants
	const FOwlAttributeValue AttrValPose("knowrob", "Pose");
	const FOwlAttributeValue AttrValString("xsd", "string");

	// Pose individual
	FOwlNode PoseIndividual(OwlNI, FOwlAttribute(RdfAbout, FOwlAttributeValue("log", InId)));
	FOwlNode PoseProperty(RdfType, FOwlAttribute(RdfResource, AttrValPose));
	PoseIndividual.ChildNodes.Add(PoseProperty);
	PoseIndividual.ChildNodes.Add(FOwlStatics::CreateQuaternionProperty(InQuat));
	PoseIndividual.ChildNodes.Add(FOwlStatics::CreateLocationProperty(InLoc));
	return PoseIndividual;
}

// Create a constraint individual
FOwlNode FOwlStatics::CreateConstraintIndividual()
{
	return FOwlNode();
}

// Create a class individual
FOwlNode FOwlStatics::CreateClassDefinition(const FString& InClass)
{
	// Prefix name constants
	const FOwlPrefixName RdfAbout("rdf", "about");
	const FOwlPrefixName OwlClass("owl", "Class");

	return FOwlNode(OwlClass, FOwlAttribute(RdfAbout, FOwlAttributeValue("knowrob", InClass)));
}

/* Owl properties creation */
// Create class property
FOwlNode FOwlStatics::CreateClassProperty(const FString& InClass)
{
	const FOwlPrefixName RdfResource("rdf", "resource");
	const FOwlPrefixName RdfType("rdf", "type");

	return FOwlNode(RdfType, FOwlAttribute(RdfResource, FOwlAttributeValue("knowrob", InClass)));
}

// Create subclass property
FOwlNode FOwlStatics::CreateSubClassProperty(const FString& InSubClass)
{
	const FOwlPrefixName RdfResource("rdf", "resource");
	const FOwlPrefixName RdfsSubClass("rdfs", "subClassOf");

	return FOwlNode(RdfsSubClass, FOwlAttribute(RdfResource, FOwlAttributeValue("knowrob", InSubClass)));
}

// Create subclass - depth property
FOwlNode FOwlStatics::CreateDepthProperty(float Value) 
{
	const FOwlPrefixName RdfsSubClass("rdfs", "subClassOf");
	const FOwlPrefixName OwlRestriction("owl", "Restriction");

	FOwlNode SubClass(RdfsSubClass);
	FOwlNode Restriction(OwlRestriction);
	Restriction.ChildNodes.Add(CreateOnProperty("depthOfObject"));
	Restriction.ChildNodes.Add(CreateHasValueFloat(Value));
	SubClass.ChildNodes.Add(Restriction);
	return SubClass;
}

// Create subclass - height property
FOwlNode FOwlStatics::CreateHeightProperty(float Value) 
{
	const FOwlPrefixName RdfsSubClass("rdfs", "subClassOf");
	const FOwlPrefixName OwlRestriction("owl", "Restriction");

	FOwlNode SubClass(RdfsSubClass);
	FOwlNode Restriction(OwlRestriction);
	Restriction.ChildNodes.Add(CreateOnProperty("heightOfObject"));
	Restriction.ChildNodes.Add(CreateHasValueFloat(Value));
	SubClass.ChildNodes.Add(Restriction);
	return SubClass;
}

// Create subclass - width property
FOwlNode FOwlStatics::CreateWidthProperty(float Value) 
{
	const FOwlPrefixName RdfsSubClass("rdfs", "subClassOf");
	const FOwlPrefixName OwlRestriction("owl", "Restriction");

	FOwlNode SubClass(RdfsSubClass);
	FOwlNode Restriction(OwlRestriction);
	Restriction.ChildNodes.Add(CreateOnProperty("widthOfObject"));
	Restriction.ChildNodes.Add(CreateHasValueFloat(Value));
	SubClass.ChildNodes.Add(Restriction);
	return SubClass;
}

// Create owl:onProperty meta property
FOwlNode FOwlStatics::CreateOnProperty(const FString& InProperty)
{
	const FOwlPrefixName OwlOnProp("owl", "onProperty");
	const FOwlPrefixName RdfResource("rdf", "resource");

	return FOwlNode(OwlOnProp, FOwlAttribute(RdfResource,FOwlAttributeValue("knowrob", InProperty)));
}

// Create owl:hasValue float property
FOwlNode FOwlStatics::CreateHasValueFloat(float Value)
{
	const FOwlPrefixName OwlHasVal("owl", "hasValue");
	const FOwlPrefixName RdfDatatype("rdf", "datatype");

	return FOwlNode(OwlHasVal, FOwlAttribute(RdfDatatype, FOwlAttributeValue("xsd", "float")),
		FString::SanitizeFloat(Value));
}

// Create owl:hasValue string property
FOwlNode FOwlStatics::CreateHasValueString(const FString& InValue)
{
	const FOwlPrefixName OwlHasVal("owl", "hasValue");
	const FOwlPrefixName RdfDatatype("rdf", "datatype");

	return FOwlNode(OwlHasVal, FOwlAttribute(RdfDatatype, FOwlAttributeValue("xsd", "string")),
		InValue);
}

// Create pose property
FOwlNode FOwlStatics::CreatePoseProperty(const FString& InId)
{
	const FOwlPrefixName KbPose("knowrob", "pose");
	const FOwlPrefixName RdfResource("rdf", "resource");

	return FOwlNode(KbPose, FOwlAttribute(RdfResource, FOwlAttributeValue("log", InId)));
}

// Create child property
FOwlNode FOwlStatics::CreateChildProperty(const FString& InId)
{
	const FOwlPrefixName KbChild("knowrob", "child");
	const FOwlPrefixName RdfResource("rdf", "resource");

	return FOwlNode(KbChild, FOwlAttribute(RdfResource, FOwlAttributeValue("log", InId)));
}

// Create parent property
FOwlNode FOwlStatics::CreateParentProperty(const FString& InId)
{
	const FOwlPrefixName KbParent("knowrob", "parent");
	const FOwlPrefixName RdfResource("rdf", "resource");

	return FOwlNode(KbParent, FOwlAttribute(RdfResource, FOwlAttributeValue("log", InId)));
}

// Create a location node
FOwlNode FOwlStatics::CreateLocationProperty(const FVector& InLoc)
{
	const FOwlPrefixName RdfDatatype("rdf", "datatype");
	const FOwlPrefixName KbTransl("knowrob", "translation");
	const FOwlAttributeValue AttrValString("xsd", "string");

	const FString LocStr = FString::Printf(TEXT("%f %f %f"),
		InLoc.X, InLoc.Y, InLoc.Z);
	return FOwlNode(KbTransl, FOwlAttribute(RdfDatatype, AttrValString), LocStr);
}

// Create a quaternion node
FOwlNode FOwlStatics::CreateQuaternionProperty(const FQuat& InQuat)
{
	const FOwlPrefixName RdfDatatype("rdf", "datatype");
	const FOwlPrefixName KbQuat("knowrob", "quaternion");
	const FOwlAttributeValue AttrValString("xsd", "string");
	
	const FString QuatStr = FString::Printf(TEXT("%f %f %f %f"),
		InQuat.W, InQuat.X, InQuat.Y, InQuat.Z);
	return FOwlNode(KbQuat, FOwlAttribute(RdfDatatype, AttrValString), QuatStr);
}
