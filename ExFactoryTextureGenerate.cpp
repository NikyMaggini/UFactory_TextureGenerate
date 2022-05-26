// Fill out your copyright notice in the Description page of Project Settings.


#include "ExFactoryTextureGenerate.h"
#include "ImageUtils.h"
#include "Misc/FileHelper.h"
#include "Math/Vector.h"

UExFactoryTextureGenerate::UExFactoryTextureGenerate()
{
	bEditorImport = true;
	SupportedClass = UTexture2D::StaticClass();
	Formats.Add(FString("bezier;Bezier file format"));
}

UObject* UExFactoryTextureGenerate::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	int32 H = 512;
	int32 W = 512;
	int32 Index = 0;

	TArray<FString> Lines;
	FFileHelper::LoadFileToStringArray(Lines, *Filename);

	TArray<FString> ContentImportFile;

	TArray<FColor> Pixels;
	Pixels.AddZeroed(W * H);

	FCreateTexture2DParameters Params;

	TArray<FVector> ControlPoints;
	ControlPoints.SetNumZeroed(4);

	for (const FString& Line : Lines)
	{
		Line.ParseIntoArray(ContentImportFile, TEXT(","));
		ControlPoints[Index] = FVector(FCString::Atoi(*(ContentImportFile[0])), FCString::Atoi(*(ContentImportFile[1])), 0);
		Index++;
	}

	TArray<FVector> OutPoints;
	FVector::EvaluateBezier(ControlPoints.GetData(), 1000, OutPoints);

	for (const FVector& Point : OutPoints)
	{
		int X = FMath::RoundToInt(Point.X);
		int Y = FMath::RoundToInt(Point.Y);
		if (X >= 0 && X < W && Y >= 0 && Y < H)
		{
			Pixels[Y * W + X] = FColor(0, 170, 100, 255);
		}
	}

	return FImageUtils::CreateTexture2D(W, H, Pixels, InParent, InName.ToString(), Flags, Params);
}