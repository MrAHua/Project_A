// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_A/Public/Hala.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHala() {}
// Cross Module References
	PROJECT_A_API UClass* Z_Construct_UClass_AHala_NoRegister();
	PROJECT_A_API UClass* Z_Construct_UClass_AHala();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Project_A();
// End Cross Module References
	void AHala::StaticRegisterNativesAHala()
	{
	}
	UClass* Z_Construct_UClass_AHala_NoRegister()
	{
		return AHala::StaticClass();
	}
	struct Z_Construct_UClass_AHala_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHala_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Project_A,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHala_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Hala.h" },
		{ "ModuleRelativePath", "Public/Hala.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHala_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHala>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AHala_Statics::ClassParams = {
		&AHala::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AHala_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AHala_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHala()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHala_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHala, 2540613829);
	template<> PROJECT_A_API UClass* StaticClass<AHala>()
	{
		return AHala::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHala(Z_Construct_UClass_AHala, &AHala::StaticClass, TEXT("/Script/Project_A"), TEXT("AHala"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHala);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
