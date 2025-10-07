#pragma once
#include <cstdint>
#include <unordered_map>
#include <fstream>

#define CameraLocation      0x178        // Globals -> CameraLocation
#define CameraRotation      0x188 
namespace offsets {

    uintptr_t UWorld = 0x16EAC598;
    uintptr_t AcknowledgedPawn = 0x350;
    uintptr_t PlayerController = 0x30;
    uintptr_t LocalPlayers = 0x38;
    uintptr_t PlayerState = 0x2C8;
    uintptr_t OwningGameInstance = 0x240;
    uintptr_t GameState = 0x1C8;
    uintptr_t PlayerArray = 0x2C0; //idk
    uintptr_t RootComponent = 0x1B0;
    uintptr_t current_vehicle = 0x2B78;
    uintptr_t RelativeLocation = 0x140;
    uintptr_t PawnPrivate = 0x320; //idk
    uintptr_t Mesh = 0x328;
    uintptr_t AActor = 0x168;
    uintptr_t TeamIndex = 0x1191;
    uintptr_t b_is_dying = 0x728;
    uintptr_t BoneArray = 0x5E8; // idk
    uintptr_t ComponentToWorld = 0x1E0;
    //uintptr_t LastSubmitTimeOnScreen = FortniteOffsets::Calculated::LastRenderTimeOnScreen;
    uintptr_t current_weapon = 0x990;
    uintptr_t weapon_data = 0x5A8;
    uintptr_t AmmoCount = 0x1184;
    uintptr_t ItemName = 0x40;
    uintptr_t Tier = 0xa2;
    // uintptr_t Color = 0xA2;//idk
    uintptr_t HabaneroComponent = 0x938;//idk
    uintptr_t PlayerName = 0x9f8;///idk
    uintptr_t ranked_progress = 0xd8;///idk
    uintptr_t Levels = 0x1E0;
    uintptr_t PrimaryPickupItemEntry = 0x3a0;
    uintptr_t bAlreadySearched = 0xDD2;
    uintptr_t Rarity = 0xa2;
    uintptr_t ItemDefinition = 0x10;
    uintptr_t ItemRarity = 0xaa;
    uintptr_t Platform = 0x438;
    uintptr_t TargetedFortPawn = 0x1900;
    uintptr_t KillScore = 0x11A8;
    uintptr_t GNames = 0x171BAF00;
};