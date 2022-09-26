// COPYRIGHT 1995-2022 ESRI
// TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
// Unpublished material - all rights reserved under the
// Copyright Laws of the United States and applicable international
// laws, treaties, and conventions.
//
// For additional information, contact:
// Attn: Contracts and Legal Department
// Environmental Systems Research Institute, Inc.
// 380 New York Street
// Redlands, California 92373
// USA
//
// email: legal@esri.com

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/SplineMeshComponent.h"
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialExpressionConstant3Vector.h"

#include "ArcGISMapsSDK/Actors/ArcGISMapActor.h"
#include "ArcGISMapsSDK/API/GameEngine/Geometry/ArcGISGeometry.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISAngularUnit.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISAngularUnitId.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISGeodeticCurveType.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISGeodeticDistanceResult.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISGeometryEngine.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISLinearUnit.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISLinearUnitId.h"
#include "ArcGISMapsSDK/BlueprintNodes/GameEngine/Geometry/ArcGISSpatialReference.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "sample_project/Routing/Breadcrumb.h"
#include "sample_project/Routing/RouteMarker.h"

#include "Measure.generated.h"

UCLASS()
class AMeasure : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeasure();

	UFUNCTION(BlueprintCallable)
	void RenderLine();

	UFUNCTION(BlueprintCallable)
	void ClearLine();

	UFUNCTION(BlueprintCallable)
	void UnitChanged();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<AActor*> FeaturePoints;
	double GeodeticDistance;
	FString GeodeticDistanceText;
	TObjectPtr<UArcGISMapComponent> MapComponent;
	FVector2D RouteCueScale = FVector2D(5);
	TObjectPtr<UStaticMesh> RouteMesh;
	TDoubleLinkedList<USplineMeshComponent*> SplineMeshComponents;
	TArray<ARouteMarker*> Stops;
	TObjectPtr<UUserWidget> UIWidget;
	TSubclassOf<UUserWidget> UIWidgetClass;
	TObjectPtr<UArcGISLinearUnit> Unit;
	TObjectPtr<UComboBoxString> UnitDropdown;
	FString UnitText;
	UFunction* WidgetFunction;
	double SegmentDistance;
	FActorSpawnParameters SpawnParam = FActorSpawnParameters();

	void AddStop();
	void Interpolate(AActor* start, AActor* end);
	void SetElevation(AActor* stop);
	void SetupInput();
};
