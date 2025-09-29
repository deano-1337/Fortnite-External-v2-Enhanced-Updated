#pragma once
#include <cstdint>
#include <unordered_map>
#include <fstream>


inline namespace FortniteOffsets {
    namespace Globals {
        inline uintptr_t AActors = 0x1A8; // AActors (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CameraLocation = 0x178; // CameraLocation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CameraRotation = 0x188; // CameraRotation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t GEngine = 0x17B93638; // GEngine (Dumped With UDMANS Offset Dumper)
        inline uintptr_t UWorld = 0x17e5c9c8; // UWorld (Dumped With UDMANS Offset Dumper)
    }

    namespace AActor {
        inline uintptr_t CustomTimeDilation = 0x68; // AActor::CustomTimeDilation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RootComponent = 0x1B0; // AActor::RootComponent (Dumped With UDMANS Offset Dumper)
    }

    namespace ABuildingContainer {
        inline uintptr_t HighestRarity = 0xDD0; // ABuildingContainer::HighestRarity (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SpawnSourceOverride = 0xC68; // ABuildingContainer::SpawnSourceOverride (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bAlreadySearched = 0xDD2; // ABuildingContainer::bAlreadySearched ( BitField Index -> 2 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace ABuildingWeakSpot {
        inline uintptr_t HitCount = 0x2DC; // ABuildingWeakSpot::HitCount (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bActive = 0x2D8; // ABuildingWeakSpot::bActive ( BitField Index -> 2 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace ACharacter {
        inline uintptr_t CharacterMovement = 0x330; // ACharacter::CharacterMovement (Dumped With UDMANS Offset Dumper)
        inline uintptr_t Mesh = 0x328; // ACharacter::Mesh (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortAthenaSKPushVehicle {
        inline uintptr_t ForwardForceTractionScale = 0x2224; // AFortAthenaSKPushVehicle::ForwardForceTractionScale (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortAthenaVehicle {
        inline uintptr_t CachedFuelComponent = 0x1378; // AFortAthenaVehicle::CachedFuelComponent (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CachedSpeed = 0xF38; // AFortAthenaVehicle::CachedSpeed (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CustomName = 0x658; // AFortAthenaVehicle::CustomName (Dumped With UDMANS Offset Dumper)
        inline uintptr_t HealthSet = 0x1808; // AFortAthenaVehicle::HealthSet (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PushForceCurrentMultiplier = 0xB5C; // AFortAthenaVehicle::PushForceCurrentMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TopSpeedCurrentMultiplier = 0xB58; // AFortAthenaVehicle::TopSpeedCurrentMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t VehicleAttributes = 0x1350; // AFortAthenaVehicle::VehicleAttributes (Dumped With UDMANS Offset Dumper)
        inline uintptr_t WaterEffectsVehicleMaxSpeedKmh = 0x9E8; // AFortAthenaVehicle::WaterEffectsVehicleMaxSpeedKmh (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPawn {
        inline uintptr_t CurrentWeapon = 0x990; // AFortPawn::CurrentWeapon (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CurrentWeaponList = 0x9C8; // AFortPawn::CurrentWeaponList (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PreviousWeapon = 0x9C0; // AFortPawn::PreviousWeapon (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsDBNO = 0x841; // AFortPawn::bIsDBNO ( BitField Index -> 7 ) (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsDying = 0x728; // AFortPawn::bIsDying ( BitField Index -> 5 ) (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsInvulnerable = 0x72A; // AFortPawn::bIsInvulnerable ( BitField Index -> 2 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPickup {
        inline uintptr_t DefaultFlyTime = 0x5D4; // AFortPickup:efaultFlyTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PrimaryPickupItemEntry = 0x370; // AFortPickup::PrimaryPickupItemEntry (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerController {
        inline uintptr_t AdditionalAimOffset = 0x2D30; // AFortPlayerController::AdditionalAimOffset (Dumped With UDMANS Offset Dumper)
        inline uintptr_t LocationUnderReticle = 0x2BE0; // AFortPlayerController::LocationUnderReticle (Dumped With UDMANS Offset Dumper)
        inline uintptr_t OnSetFirstPersonCamera = 0x10A8; // AFortPlayerController::OnSetFirstPersonCamera (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TargetedFortPawn = 0x18E0; // AFortPlayerController::TargetedFortPawn (Dumped With UDMANS Offset Dumper)
        inline uintptr_t WeaponRecoilOffset = 0x2D60; // AFortPlayerController::WeaponRecoilOffset (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bAutoRunOn = 0x1051; // AFortPlayerController::bAutoRunOn ( BitField Index -> 3 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerControllerGameplay {
        inline uintptr_t bIsCreativeModeratorModeEnabled = 0x3942; // AFortPlayerControllerGameplay::bIsCreativeModeratorModeEnabled ( BitField Index -> 5 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerPawn {
        inline uintptr_t BuildingState = 0x20F8; // AFortPlayerPawn::BuildingState (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CurrentVehicle = 0x2C68; // AFortPlayerPawn::CurrentVehicle (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsParachuteOpen = 0x22C8; // AFortPlayerPawn::bIsParachuteOpen (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsSkydiving = 0x22C7; // AFortPlayerPawn::bIsSkydiving (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerPawnAthena {
        inline uintptr_t LastFiredDirection = 0x5A58; // AFortPlayerPawnAthena::LastFiredDirection (Dumped With UDMANS Offset Dumper)
        inline uintptr_t LastFiredLocation = 0x5A40; // AFortPlayerPawnAthena::LastFiredLocation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t LastFiredTime = 0x5A70; // AFortPlayerPawnAthena::LastFiredTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ReviveFromDBNOTime = 0x4E70; // AFortPlayerPawnAthena::ReviveFromDBNOTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bCanBeMarkedAsTeammate = 0x5F48; // AFortPlayerPawnAthena::bCanBeMarkedAsTeammate (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerState {
        inline uintptr_t Platform = 0x438; // AFortPlayerState::Platform (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerStateAthena {
        inline uintptr_t AlwaysIncludeTeamAsAllies = 0x11C8; // AFortPlayerStateAthena::AlwaysIncludeTeamAsAllies (Dumped With UDMANS Offset Dumper)
        inline uintptr_t KillScore = 0x11E0; // AFortPlayerStateAthena::KillScore (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RebootCounter = 0x18B4; // AFortPlayerStateAthena::RebootCounter (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SeasonLevelUIDisplay = 0x11E4; // AFortPlayerStateAthena::SeasonLevelUIDisplay (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TeamIndex = 0x11C9; // AFortPlayerStateAthena::TeamIndex (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TeamKillScore = 0x1124; // AFortPlayerStateAthena::TeamKillScore (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsDisconnected = 0x16E0; // AFortPlayerStateAthena::bIsDisconnected (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsMuted = 0x13E9; // AFortPlayerStateAthena::bIsMuted (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsTalking = 0x13E8; // AFortPlayerStateAthena::bIsTalking (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bThankedBusDriver = 0x1365; // AFortPlayerStateAthena::bThankedBusDriver ( BitField Index -> 0 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortPlayerStateZone {
        inline uintptr_t CurrentHealth = 0xDC4; // AFortPlayerStateZone::CurrentHealth (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CurrentShield = 0xDCC; // AFortPlayerStateZone::CurrentShield (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MaxHealth = 0xDC8; // AFortPlayerStateZone::MaxHealth (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MaxShield = 0xDD0; // AFortPlayerStateZone::MaxShield (Dumped With UDMANS Offset Dumper)
        inline uintptr_t Spectators = 0xAC0; // AFortPlayerStateZone::Spectators (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortSafeZoneIndicator {
        inline uintptr_t SafeZonePhases = 0x4F0; // AFortSafeZoneIndicator::SafeZonePhases (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortWeapon {
        inline uintptr_t AccumulatedChargeTime = 0x1190; // AFortWeapon::AccumulatedChargeTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t AmmoCount = 0x10B4; // AFortWeapon::AmmoCount (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ChargeTime = 0x118C; // AFortWeapon::ChargeTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CurrentProjectedImpactDistance = 0xFE8; // AFortWeapon::CurrentProjectedImpactDistance (Dumped With UDMANS Offset Dumper)
        inline uintptr_t CurrentReticleColor = 0xFA8; // AFortWeapon::CurrentReticleColor (Dumped With UDMANS Offset Dumper)
        inline uintptr_t LastChargeTime = 0x1194; // AFortWeapon::LastChargeTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TimeToEquip = 0x360; // AFortWeapon::TimeToEquip (Dumped With UDMANS Offset Dumper)
        inline uintptr_t WeaponCoreAnimation = 0x1a38; // AFortWeapon::WeaponCoreAnimation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t WeaponData = 0x578; // AFortWeapon::WeaponData (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bAllowTargeting = 0x100C; // AFortWeapon::bAllowTargeting ( BitField Index -> 4 ) (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIgnoreTryToFireSlotCooldownRestriction = 0x1B81; // AFortWeapon::bIgnoreTryToFireSlotCooldownRestriction (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsChargingWeapon = 0x390; // AFortWeapon::bIsChargingWeapon (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsEquippingWeapon = 0x378; // AFortWeapon::bIsEquippingWeapon (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsReloadingWeapon = 0x391; // AFortWeapon::bIsReloadingWeapon ( BitField Index -> 0 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace AFortWeaponRanged {
        inline uintptr_t AimPitchMax = 0x2118; // AFortWeaponRanged::AimPitchMax (Dumped With UDMANS Offset Dumper)
        inline uintptr_t AimPitchMin = 0x2114; // AFortWeaponRanged::AimPitchMin (Dumped With UDMANS Offset Dumper)
    }

    namespace AGameStateBase {
        inline uintptr_t PlayerArray = 0x2C0; // AGameStateBase::PlayerArray (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ServerWorldTimeSecondsDelta = 0x2E0; // AGameStateBase::ServerWorldTimeSecondsDelta (Dumped With UDMANS Offset Dumper)
    }

    namespace APawn {
        inline uintptr_t PlayerState = 0x2C8; // APawn::PlayerState (Dumped With UDMANS Offset Dumper)
    }

    namespace APlayerCameraManager {
        inline uintptr_t CameraCachePrivate = 0x1530; // APlayerCameraManager::CameraCachePrivate (Dumped With UDMANS Offset Dumper)
        inline uintptr_t DefaultFOV = 0x2BC; // APlayerCameraManager:efaultFOV (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewPitchMax = 0x27B0; // APlayerCameraManager::ViewPitchMax (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewPitchMin = 0x27AC; // APlayerCameraManager::ViewPitchMin (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewRollMax = 0x27C0; // APlayerCameraManager::ViewRollMax (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewRollMin = 0x27BC; // APlayerCameraManager::ViewRollMin (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewTarget = 0x340; // APlayerCameraManager::ViewTarget (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewYawMax = 0x27B8; // APlayerCameraManager::ViewYawMax (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ViewYawMin = 0x27B4; // APlayerCameraManager::ViewYawMin (Dumped With UDMANS Offset Dumper)
    }

    namespace APlayerController {
        inline uintptr_t AcknowledgedPawn = 0x350; // APlayerController::AcknowledgedPawn (Dumped With UDMANS Offset Dumper)
        inline uintptr_t InputPitchScale = 0x544; // APlayerController::InputPitchScale (Dumped With UDMANS Offset Dumper)
        inline uintptr_t InputRollScale = 0x548; // APlayerController::InputRollScale (Dumped With UDMANS Offset Dumper)
        inline uintptr_t InputYawScale = 0x540; // APlayerController::InputYawScale (Dumped With UDMANS Offset Dumper)
        inline uintptr_t NetConnection = 0x520; // APlayerController::NetConnection (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PlayerCameraManager = 0x360; // APlayerController::PlayerCameraManager (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SmoothTargetViewRotationSpeed = 0x3A8; // APlayerController::SmoothTargetViewRotationSpeed (Dumped With UDMANS Offset Dumper)
    }

    namespace APlayerState {
        inline uintptr_t CompressedPing = 0x2B0; // APlayerState::CompressedPing (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PawnPrivate = 0x320; // APlayerState::PawnPrivate (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PlayerId = 0x2AC; // APlayerState::PlayerId (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PlayerNamePrivate = 0x340; // APlayerState::PlayerNamePrivate (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bIsABot = 0x2B2; // APlayerState::bIsABot ( BitField Index -> 3 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace AWorldSettings {
        inline uintptr_t WorldGravityZ = 0x328; // AWorldSettings::WorldGravityZ (Dumped With UDMANS Offset Dumper)
    }

    namespace FCameraCacheEntry {
        inline uintptr_t POV = 0x10; // FCameraCacheEntry::POV (Dumped With UDMANS Offset Dumper)
    }

    namespace FFortBaseWeaponStats {
        inline uintptr_t ReloadTime = 0x174; // FFortBaseWeaponStats::ReloadTime (Dumped With UDMANS Offset Dumper)
    }

    namespace FFortRangedWeaponStats {
        inline uintptr_t AthenaCrouchingSpreadMultiplier = 0x20C; // FFortRangedWeaponStats::AthenaCrouchingSpreadMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t AthenaJumpingFallingSpreadMultiplier = 0x214; // FFortRangedWeaponStats::AthenaJumpingFallingSpreadMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t AthenaSlidingSpreadMultiplier = 0x210; // FFortRangedWeaponStats::AthenaSlidingSpreadMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t AthenaSprintingSpreadMultiplier = 0x218; // FFortRangedWeaponStats::AthenaSprintingSpreadMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t FiringRate = 0x284; // FFortRangedWeaponStats::FiringRate (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MaxSpeedForSpreadMultiplier = 0x220; // FFortRangedWeaponStats::MaxSpeedForSpreadMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MinSpeedForSpreadMultiplier = 0x21C; // FFortRangedWeaponStats::MinSpeedForSpreadMultiplier (Dumped With UDMANS Offset Dumper)
        inline uintptr_t OverrideBaseSpread = 0x1FC; // FFortRangedWeaponStats::OverrideBaseSpread (Dumped With UDMANS Offset Dumper)
        inline uintptr_t OverrideSpreadDownsights = 0x204; // FFortRangedWeaponStats::OverrideSpreadDownsights (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RecoilHoriz = 0x2CC; // FFortRangedWeaponStats::RecoilHoriz (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RecoilVert = 0x2BC; // FFortRangedWeaponStats::RecoilVert (Dumped With UDMANS Offset Dumper)
        inline uintptr_t Spread = 0x1F8; // FFortRangedWeaponStats::Spread (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SpreadDownsights = 0x200; // FFortRangedWeaponStats::SpreadDownsights (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SpreadDownsightsAdditionalCooldownTime = 0x224; // FFortRangedWeaponStats::SpreadDownsightsAdditionalCooldownTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SpreadExponent = 0x228; // FFortRangedWeaponStats::SpreadExponent (Dumped With UDMANS Offset Dumper)
        inline uintptr_t StandingStillSpreadMultiplier = 0x208; // FFortRangedWeaponStats::StandingStillSpreadMultiplier (Dumped With UDMANS Offset Dumper)
    }

    namespace FFortSpectatorZoneArray {
        inline uintptr_t SpectatorArray = 0x108; // FFortSpectatorZoneArray::SpectatorArray (Dumped With UDMANS Offset Dumper)
    }

    namespace FFortSpectatorZoneItem {
        inline uintptr_t PlayerState = 0x10; // FFortSpectatorZoneItem::PlayerState (Dumped With UDMANS Offset Dumper)
    }

    namespace FFortTrapStats {
        inline uintptr_t ArmTime = 0x1F8; // FFortTrapStats::ArmTime (Dumped With UDMANS Offset Dumper)
        inline uintptr_t DamageDelay = 0x200; // FFortTrapStats:amageDelay (Dumped With UDMANS Offset Dumper)
        inline uintptr_t FireDelay = 0x1FC; // FFortTrapStats::FireDelay (Dumped With UDMANS Offset Dumper)
    }

    namespace FItemEntry {
        inline uintptr_t ItemDefinition = 0x10; // FItemEntry::ItemDefinition (Dumped With UDMANS Offset Dumper)
    }

    namespace FMinimalViewInfo {
        inline uintptr_t AspectRatio = 0x5C; // FMinimalViewInfo::AspectRatio (Dumped With UDMANS Offset Dumper)
        inline uintptr_t DesiredFOV = 0x34; // FMinimalViewInfo:esiredFOV (Dumped With UDMANS Offset Dumper)
        inline uintptr_t FOV = 0x30; // FMinimalViewInfo::FOV (Dumped With UDMANS Offset Dumper)
        inline uintptr_t Rotation = 0x18; // FMinimalViewInfo::Rotation (Dumped With UDMANS Offset Dumper)
    }

    namespace UCharacterMovementComponent {
        inline uintptr_t LastUpdateLocation = 0x360; // UCharacterMovementComponent::LastUpdateLocation (Dumped With UDMANS Offset Dumper)
    }

    namespace UEngine {
        inline uintptr_t GameViewport = 0xA90; // UEngine::GameViewport (Dumped With UDMANS Offset Dumper)
        inline uintptr_t LargeFont = 0x90; // UEngine::LargeFont (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SmallFont = 0x50; // UEngine::SmallFont (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TinyFont = 0x30; // UEngine::TinyFont (Dumped With UDMANS Offset Dumper)
    }

    namespace UFortClientSettingsRecord {
        inline uintptr_t FOVMaximum = 0xBE8; // UFortClientSettingsRecord::FOVMaximum (Dumped With UDMANS Offset Dumper)
        inline uintptr_t FOVMinimum = 0xBE4; // UFortClientSettingsRecord::FOVMinimum (Dumped With UDMANS Offset Dumper)
        inline uintptr_t HUDScale = 0x6B0; // UFortClientSettingsRecord::HUDScale (Dumped With UDMANS Offset Dumper)
        inline uintptr_t InitialHUDScale = 0x6B8; // UFortClientSettingsRecord::InitialHUDScale (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MasterVolume = 0xB34; // UFortClientSettingsRecord::MasterVolume (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MouseSensitivity = 0x78C; // UFortClientSettingsRecord::MouseSensitivity (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MouseSensitivityX = 0x790; // UFortClientSettingsRecord::MouseSensitivityX (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MouseSensitivityY = 0x794; // UFortClientSettingsRecord::MouseSensitivityY (Dumped With UDMANS Offset Dumper)
        inline uintptr_t MusicVolume = 0xB38; // UFortClientSettingsRecord::MusicVolume (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ScopedSlow = 0x758; // UFortClientSettingsRecord::ScopedSlow (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TargetingSlow = 0x754; // UFortClientSettingsRecord::TargetingSlow (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bAnonymousMode = 0xB5D; // UFortClientSettingsRecord::bAnonymousMode (Dumped With UDMANS Offset Dumper)
    }

    namespace UFortItemDefinition {
        inline uintptr_t Rarity = 0xA2; // UFortItemDefinition::Rarity (Dumped With UDMANS Offset Dumper)
    }

    namespace UFortLocalPlayer {
        inline uintptr_t ClientSettingsRecord = 0x378; // UFortLocalPlayer::ClientSettingsRecord (Dumped With UDMANS Offset Dumper)
    }

    namespace UFortVehicleFuelComponent {
        inline uintptr_t ServerFuel = 0x130; // UFortVehicleFuelComponent::ServerFuel (Dumped With UDMANS Offset Dumper)
    }

    namespace UFortWeaponItemDefinition {
        inline uintptr_t HitNotifyDuration = 0x29C; // UFortWeaponItemDefinition::HitNotifyDuration (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TriggerType = 0x294; // UFortWeaponItemDefinition::TriggerType (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bAllowTargetingDuringReload = 0x298; // UFortWeaponItemDefinition::bAllowTargetingDuringReload ( BitField Index -> 0 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace UGameInstance {
        inline uintptr_t LocalPlayers = 0x38; // UGameInstance::LocalPlayers (Dumped With UDMANS Offset Dumper)
    }

    namespace UGameViewportClient {
        inline uintptr_t World = 0x78; // UGameViewportClient::World (Dumped With UDMANS Offset Dumper)
    }

    namespace UItemDefinitionBase {
        inline uintptr_t ItemName = 0x40; // UItemDefinitionBase::ItemName (Dumped With UDMANS Offset Dumper)
    }

    namespace ULevel {
        inline uintptr_t OwningWorld = 0xC0; // ULevel::OwningWorld (Dumped With UDMANS Offset Dumper)
        inline uintptr_t WorldSettings = 0x2C0; // ULevel::WorldSettings (Dumped With UDMANS Offset Dumper)
    }

    namespace ULocalPlayer {
        inline uintptr_t ViewportClient = 0x78; // ULocalPlayer::ViewportClient (Dumped With UDMANS Offset Dumper)
    }

    namespace UMaterial {
        inline uintptr_t Wireframe = 0x1D8; // UMaterial::Wireframe ( BitField Index -> 7 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace UMaterialInstance {
        inline uintptr_t Parent = 0x128; // UMaterialInstance::Parent (Dumped With UDMANS Offset Dumper)
        inline uintptr_t ScalarParameterValues = 0x190; // UMaterialInstance::ScalarParameterValues (Dumped With UDMANS Offset Dumper)
        inline uintptr_t TextureParameterValues = 0x1C0; // UMaterialInstance::TextureParameterValues (Dumped With UDMANS Offset Dumper)
        inline uintptr_t VectorParameterValues = 0x1A0; // UMaterialInstance::VectorParameterValues (Dumped With UDMANS Offset Dumper)
    }

    namespace UMovementComponent {
        inline uintptr_t Velocity = 0xD8; // UMovementComponent::Velocity (Dumped With UDMANS Offset Dumper)
    }

    namespace UPlayer {
        inline uintptr_t PlayerController = 0x30; // UPlayer::PlayerController (Dumped With UDMANS Offset Dumper)
    }

    namespace USceneComponent {
        inline uintptr_t ComponentVelocity = 0x188; // USceneComponent::ComponentVelocity (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PhysicsVolume = 0xC8; // USceneComponent::PhysicsVolume (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RelativeLocation = 0x140; // USceneComponent::RelativeLocation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RelativeRotation = 0x158; // USceneComponent::RelativeRotation (Dumped With UDMANS Offset Dumper)
        inline uintptr_t RelativeScale3D = 0x170; // USceneComponent::RelativeScale3D (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bAbsoluteLocation = 0x1A0; // USceneComponent::bAbsoluteLocation ( BitField Index -> 2 ) (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bComponentToWorldUpdated = 0x1E0; // USceneComponent::bComponentToWorldUpdated ( BitField Index -> 0 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace USkeletalMeshComponent {
        inline uintptr_t GlobalAnimRateScale = 0xA58; // USkeletalMeshComponent::GlobalAnimRateScale (Dumped With UDMANS Offset Dumper)
    }

    namespace USkinnedMeshComponent {
        inline uintptr_t MeshDeformerInstances = 0x5B8; // USkinnedMeshComponent::MeshDeformerInstances (Dumped With UDMANS Offset Dumper)
        inline uintptr_t SkeletalMesh = 0x570; // USkinnedMeshComponent::SkeletalMesh (Dumped With UDMANS Offset Dumper)
        inline uintptr_t bForceWireframe = 0x7B7; // USkinnedMeshComponent::bForceWireframe ( BitField Index -> 6 ) (Dumped With UDMANS Offset Dumper)
    }

    namespace UWorld {
        inline uintptr_t GameState = 0x1D8; // UWorld::GameState (Dumped With UDMANS Offset Dumper)
        inline uintptr_t Levels = 0x1F0; // UWorld::Levels (Dumped With UDMANS Offset Dumper)
        inline uintptr_t OwningGameInstance = 0x250; // UWorld::OwningGameInstance (Dumped With UDMANS Offset Dumper)
        inline uintptr_t PersistentLevel = 0x40; // UWorld::PersistentLevel (Dumped With UDMANS Offset Dumper)
    }

    namespace Calculated {
        inline uintptr_t Bounds = 0x108; // USceneComponent::Bounds (Calculated)
        inline uintptr_t LastRenderTime = 0x1A0; // UWorld::LastRenderTime (Calculated)
        inline uintptr_t LastRenderTimeOnScreen = 0x32C; // UPrimitiveComponent::LastRenderTimeOnScreen (Calculated)
        inline uintptr_t LocalPlayerCachedLODDistanceFactor = 0x3AC; // APlayerController::LocalPlayerCachedLODDistanceFactor (Calculated)
    }

    namespace BitfieldIndexs {
        inline int Wireframe = 7;
        inline int bAbsoluteLocation = 2;
        inline int bActive = 2;
        inline int bAllowTargeting = 4;
        inline int bAllowTargetingDuringReload = 0;
        inline int bAlreadySearched = 2;
        inline int bAutoRunOn = 3;
        inline int bComponentToWorldUpdated = 0;
        inline int bForceWireframe = 6;
        inline int bIsABot = 3;
        inline int bIsCreativeModeratorModeEnabled = 5;
        inline int bIsDBNO = 7;
        inline int bIsDying = 5;
        inline int bIsInvulnerable = 2;
        inline int bIsReloadingWeapon = 0;
        inline int bThankedBusDriver = 0;
    }
}
#define CameraLocation      0x178        // Globals -> CameraLocation
#define CameraRotation      0x188 
namespace offsets {

    uintptr_t UWorld = FortniteOffsets::Globals::UWorld;
    uintptr_t AcknowledgedPawn = FortniteOffsets::APlayerController::AcknowledgedPawn;
    uintptr_t PlayerController = FortniteOffsets::UPlayer::PlayerController;
    uintptr_t LocalPlayers = FortniteOffsets::UGameInstance::LocalPlayers;
    uintptr_t PlayerState = FortniteOffsets::APawn::PlayerState;
    uintptr_t OwningGameInstance = FortniteOffsets::UWorld::OwningGameInstance;
    uintptr_t GameState = FortniteOffsets::UWorld::GameState;
    uintptr_t PlayerArray = FortniteOffsets::AGameStateBase::PlayerArray;
    uintptr_t RootComponent = FortniteOffsets::AActor::RootComponent;
    uintptr_t current_vehicle = FortniteOffsets::AFortPlayerPawn::CurrentVehicle;
    uintptr_t RelativeLocation = FortniteOffsets::USceneComponent::RelativeLocation;
    uintptr_t PawnPrivate = FortniteOffsets::APlayerState::PawnPrivate;
    uintptr_t Mesh = FortniteOffsets::ACharacter::Mesh;
    uintptr_t AActor = 0x38;
    uintptr_t TeamIndex = FortniteOffsets::AFortPlayerStateAthena::TeamIndex;
    uintptr_t b_is_dying = FortniteOffsets::AFortPawn::bIsDying;
    uintptr_t BoneArray = 0x5E8; // idk
    uintptr_t ComponentToWorld = FortniteOffsets::USceneComponent::bComponentToWorldUpdated;
    //uintptr_t LastSubmitTimeOnScreen = FortniteOffsets::Calculated::LastRenderTimeOnScreen;
    uintptr_t current_weapon = FortniteOffsets::AFortPawn::CurrentWeapon;
    uintptr_t weapon_data = FortniteOffsets::AFortWeapon::WeaponData;
    uintptr_t AmmoCount = FortniteOffsets::AFortWeapon::AmmoCount;
    uintptr_t ItemName = FortniteOffsets::UItemDefinitionBase::ItemName;
    uintptr_t Tier = FortniteOffsets::UFortItemDefinition::Rarity;
    uintptr_t Color = 0xA2;//idk
    uintptr_t habanero_component = 0x968;//idk
    uintptr_t username_component = 0xA30;///idk
    uintptr_t ranked_progress = 0xd8;///idk
    uintptr_t Levels = 0x1f0;
    uintptr_t PrimaryPickupItemEntry = 0x370;
    uintptr_t bAlreadySearched = 0xDD2;
    uintptr_t Rarity = 0xA2;
    uintptr_t ItemDefinition = 0x10;
    uintptr_t Platform = FortniteOffsets::AFortPlayerState::Platform;
    uintptr_t TargetedFortPawn = FortniteOffsets::AFortPlayerController::TargetedFortPawn;
    uintptr_t KillScore = FortniteOffsets::AFortPlayerStateAthena::KillScore;
    uintptr_t GNames = 0x17A31B80;
};

uintptr_t TagetedFortPAwn = 0x18D0;


enum boneID : int {
    Head = 110,
    Neck = 67,
    LHand = 11,
    RHand = 40,
    RElbow = 39,
    LElbow = 10,
    LShoulder = 9,
    RShoulder = 38,
    Chest = 66,
    Pelvis = 2,
    LHip = 71,
    RHip = 78,
    LKnee = 72,
    RKnee = 79,
    LFeet = 75,
    RFeet = 82,
    Root = 0
};



struct b
{
    int humanbase = 0;
    int	humanpelvis = 2;
    int	humanlthigh1 = 71;
    int	humanlthigh2 = 77;
    int	humanlthigh3 = 72;
    int	humanlcalf = 74;
    int	humanlfoot = 86;
    int humanlfoot2 = 86;
    int	humanltoe = 76;
    int	humanrthigh1 = 78;
    int	humanrthigh2 = 84;
    int	humanrthigh3 = 79;
    int humanrfoot2 = 82;
    int	humanrcalf = 81;
    int	humanrfoot = 87;
    int	humanrtoe = 83;
    int	humanspine1 = 7;
    int	humanspine2 = 5;
    int	humanspine3 = 2;
    int	humanlcollarbone = 9;
    int	humanlupperarm = 35;
    int	humanlforearm1 = 36;
    int humanchestright = 37;
    int humanchestleft = 8;
    int	humanlforearm23 = 10;
    int	humanlforearm2 = 34;
    int	humanlforearm3 = 33;
    int	humanlpalm = 32;
    int humanlhand = 11;
    int	humanrcollarbone = 98;
    int	humanrupperarm = 64;
    int	humanrforearm1 = 65;
    int	humanrforearm23 = 39;
    int humanrhand = 40;
    int	humanrforearm2 = 63;
    int	humanrforearm3 = 62;
    int	humanrpalm = 58;
    int	humanneck = 67;
    int	humanhead = 68;
    int	humanchest = 66;
};

std::unique_ptr<b> bones = std::make_unique<b>();
namespace world_offsets
{
    uintptr_t Levels = 0x1E8;
    uintptr_t Actors = 0x48;
}
template< typename t >

class TArray
{
public:
    TArray() : tData(), iCount(), iMaxCount() {}
    TArray(t* data, int count, int max_count) :
        tData(tData), iCount(iCount), iMaxCount(iMaxCount) {
    }

public:
    auto Get(int idx) -> t
    {
        return read< t >(reinterpret_cast<__int64>(this->tData) + (idx * sizeof(t)));
    }

    auto Size() -> std::uint32_t
    {
        return this->iCount;
    }

    bool IsValid()
    {
        return this->iCount != 0;
    }

    t* tData;
    int iCount;
    int iMaxCount;
    std::uintptr_t Array;
    std::uint32_t Count;
    std::uint32_t MaxCount;

    t Get(std::uint32_t Index) const {
        if (Index >= Count) {
            return t();
        }
        return read<t>(Array + (Index * sizeof(t)));
    }

    t operator[](std::uint32_t Index) const {
        return Get(Index);
    }

    std::uint32_t size() const {
        return Count;
    }

    bool isValid() const {
        return Array && Count <= MaxCount && MaxCount <= 1000000;
    }

    std::uintptr_t getAddress() const {
        return Array;
    }
};
template<class T>
class FArray
{
public:
    int getLength() const
    {
        return count;
    }

    int getIdentifier()
    {
        return data * count * max;
    }

    bool isValid() const
    {
        if (count > max)
            return false;
        if (!data)
            return false;
        return true;
    }

    uint64_t getAddress() const
    {
        return data;
    }

    T operator [](size_t idx) const
    {
        return read<T>(data + sizeof(T) * idx);
    }

protected:
    uint64_t data;
    uint64_t count;
    uint64_t max;
};

struct Fortnite
{
    uint64_t getVAStart(uintptr_t gworldOffset);

    enum ActorType
    {
        NOT_IN_USE = 0,
        CHEST = 1,
        AMMO_BOX = 2
    };

    struct ActorDefinitions
    {
        int actorID;
        std::string fname;
        ActorType actorType;
    };

    const std::unordered_map<std::string, ActorType>& getActorByName()
    {
        const std::unordered_map<std::string, ActorType> actorTypeByName =
        {
            {"Tiered_Chest", ActorType::CHEST},
            {"Tiered_Ammo", ActorType::AMMO_BOX}
        };
        return actorTypeByName;
    }

    ActorDefinitions getActorDefinitions(int actorID);
};