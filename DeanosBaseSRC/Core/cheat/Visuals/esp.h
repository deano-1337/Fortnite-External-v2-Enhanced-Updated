#pragma once
#include "../Utilities/util.h"
#include "../Engine/sdk.h"
#include "../Engine/offsets.hpp"
#include "../Utilities/settings.h"
#include "../aimbot/aimbot.h"
#include "loot.h"
#define STB_IMAGE_IMPLEMENTATION

#include "../Renderer/ImGui/stb_image.h"
#include "../Renderer/rank_Icons.h"
#include "../Renderer/platform_icons.h"

#include "../Renderer/render.h"
#include "../Utilities/hexray.hpp"
#define M_PI 3.14159265358979323846

void draw_player_rank_icon(Vector2 location, int tier);
void InitializeRankTextures();

// Platform
void draw_player_platform(Vector2 location, std::string platform_id, const ImColor color);
void InitializePlatformTextures();
std::string get_player_platform(uintptr_t player_state, ImColor& resultColor);
std::string platform(uint64_t PlayerState);
enum EMovementMode : uint8
{
    MOVE_None = 0,
    MOVE_Walking = 1,
    MOVE_NavWalking = 2,
    MOVE_Falling = 3,
    MOVE_Swimming = 4,
    MOVE_Flying = 5,
    MOVE_Custom = 6,
    MOVE_MAX = 7,
};

struct PlayerBounds {
    float left, right, top, bottom;
    uintptr_t pawn_priv;
};

struct PawnData {
    uintptr_t pawn;
    uintptr_t mesh;
    uintptr_t playerState;
    Vector3 head3D;
    Vector3 bottom3D;
    Vector2 head2D;
    Vector2 bottom2D;
    bool isDead;
    bool isVisible;
    std::string username;
    std::string platformStr;
    std::string weaponName;
    int teamIndex;
    int rankProgress;
    ImColor boxColor;
};

enum class TargetZone {
    Head,
    Chest,
    Stomach,
    LeftArm,
    RightArm,
    LeftLeg,
    RightLeg
};

int GetBoneID(TargetZone zone) {
    switch (zone) {
    case TargetZone::Head: return 110;
    case TargetZone::Chest: return 8;
    case TargetZone::Stomach: return 3;
    case TargetZone::LeftArm: return 35;
    case TargetZone::RightArm: return 62;
    case TargetZone::LeftLeg: return 65;
    case TargetZone::RightLeg: return 67;
    default: return 0;
    }
}

uintptr_t SelectedTargetEntityForSilentAim = 0;
TargetZone selectedZone = TargetZone::Head;


inline void DrawSkeleton(uint64_t mesh, const ImColor& color, float thickness, bool outlined, bool headesp, const Vector3& /*headLocation*/)
{
    ImDrawList* draw = ImGui::GetBackgroundDrawList();

    // Skeleton bone pairs
    static const std::pair<int, int> bonePairs[] = {
        {67, 9}, {9, 10}, {10, 11},           // Spine
        {67, 38}, {38, 39}, {39, 40},         // Left arm
        {67, 2}, {2, 71}, {71, 72}, {72, 75}, // Left leg
        {2, 78}, {78, 79}, {79, 82}           // Right leg
    };

    // Draw skeleton lines
    for (const auto& [a, b] : bonePairs)
    {
        Vector2 p1 = ProjectWorldToScreen(GetBoneWithRotation(mesh, a));
        Vector2 p2 = ProjectWorldToScreen(GetBoneWithRotation(mesh, b));

        if (outlined)
            draw->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y),
                ImColor(0, 0, 0, 255), thickness + 1.5f);

        draw->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y),
            color, thickness);
    }

    // Head circle — use actual head bone (110) and small top-of-skull offset
    if (headesp)
    {
        Vector3 headBone = GetBoneWithRotation(mesh, 110); // real head
        Vector3 headTop = headBone;
        headTop.z += 0.0f;   // exactly at bone 110

        Vector2 head2D = ProjectWorldToScreen(headTop);

        Vector3 delta = headTop - vCamera.Location;
        float distance = delta.Length();

        // Circle radius based on distance and FOV
        const float baseSize = 8.0f; // tweak if too big/small
        float circleRadius = baseSize * (Height / (2.0f * distance * tanf(vCamera.FieldOfView * (float)M_PI / 360.f)));

        int segments = 50;

        if (outlined)
            draw->AddCircle(ImVec2(head2D.x, head2D.y), circleRadius,
                ImColor(0, 0, 0, 255), segments, thickness + 1.5f);

        draw->AddCircle(ImVec2(head2D.x, head2D.y), circleRadius,
            color, segments, thickness);
    }
}


void UpdateWorldCache() {
    WorldCache::AcknowledgedPawn = LocalPtrs::Player;
    if (WorldCache::AcknowledgedPawn) {
        WorldCache::Mesh = read_cached<uint64_t>(WorldCache::AcknowledgedPawn + offsets::Mesh);
        WorldCache::PlayerState = read_cached<uint64_t>(WorldCache::AcknowledgedPawn + offsets::PlayerState);
        WorldCache::RootComponent = read_cached<uint64_t>(WorldCache::AcknowledgedPawn + offsets::RootComponent);
        WorldCache::LocalWeapon = read_cached<uint64_t>(WorldCache::AcknowledgedPawn + offsets::current_weapon);
        WorldCache::LocalVehicle = read_cached<uint64_t>(WorldCache::AcknowledgedPawn + offsets::current_vehicle);

        uintptr_t UCharacterMovementComponent = read_cached<uintptr_t>(WorldCache::AcknowledgedPawn + 0x330);
        WorldCache::MovementMode = static_cast<EMovementMode>(read_cached<int>(UCharacterMovementComponent + 0x231));

        if (WorldCache::PlayerState)
            WorldCache::TeamIndex = read_cached<char>(WorldCache::PlayerState + offsets::TeamIndex);
    }
    else {
        WorldCache::Mesh = 0;
        WorldCache::PlayerState = 0;
        WorldCache::RootComponent = 0;
        WorldCache::LocalWeapon = 0;
        WorldCache::LocalVehicle = 0;
        WorldCache::TeamIndex = 0;
    }
}


PawnData GetPawnData(uintptr_t pawn) {
    PawnData data{};
    data.pawn = pawn;
    data.mesh        = read_cached<uint64_t>(pawn + offsets::Mesh);
    data.playerState = read_cached<uint64_t>(pawn + offsets::PlayerState);
    data.isDead      = is_dead(pawn);
    data.isVisible   = data.mesh ? IsEnemyVisible(data.mesh) : false;
    data.teamIndex   = data.playerState ? read_cached<char>(data.playerState + offsets::TeamIndex) : 0;
    data.head3D      = GetBoneWithRotation(data.mesh ? data.mesh : pawn, 110);
    data.bottom3D    = GetBoneWithRotation(data.mesh ? data.mesh : pawn, 0);
    data.head2D      = ProjectWorldToScreen(data.head3D);
    data.bottom2D    = ProjectWorldToScreen(data.bottom3D);
    data.username    = data.playerState ? GetPlayerName(data.playerState) : "";
    data.platformStr = data.playerState ? platform(data.playerState) : "";
    data.weaponName  = GetWeaponName(pawn);
    data.boxColor    = data.mesh ? (data.isVisible ? settings::colors.visible : settings::colors.notVisible) : ImColor(255, 255, 255, 100);
    return data;
}

void ActorLoop() {
    static bool textures_initialized = false;
    if (!textures_initialized) {
        InitializePlatformTextures();
        InitializeRankTextures();
        textures_initialized = true;
    }

    static float deltaTime = 0.0f;
    static auto lastTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;
    int fps = (int)(1.0f / deltaTime);

    LocalPtrs::Gworld = read<uint64_t>(Base + offsets::UWorld);
    if (!LocalPtrs::Gworld) return;

    uintptr_t GameInstance = read<uint64_t>(LocalPtrs::Gworld + offsets::OwningGameInstance);
    if (!GameInstance) return;

    uintptr_t LocalPlayerArray = read<uint64_t>(GameInstance + offsets::LocalPlayers);
    if (!LocalPlayerArray) return;

    LocalPtrs::LocalPlayers = read<uint64_t>(LocalPlayerArray);
    if (!LocalPtrs::LocalPlayers) return;

    LocalPtrs::PlayerController = read<uint64_t>(LocalPtrs::LocalPlayers + offsets::PlayerController);
    LocalPtrs::Player = read<uint64_t>(LocalPtrs::PlayerController + offsets::AcknowledgedPawn);
    LocalPtrs::RootComponent = LocalPtrs::Player ? read<uint64_t>(LocalPtrs::Player + offsets::RootComponent) : 0;

    UpdateWorldCache();

    ImDrawList* draw = ImGui::GetBackgroundDrawList();

    // --- HEADER TEXT (White) ---
    draw->AddText(ImVec2(10, 10), IM_COL32(255, 255, 255, 255), "PUCHMADE v1.0");
    draw->AddText(ImVec2(10, 30), IM_COL32(255, 255, 255, 255), ("FPS: " + std::to_string(fps)).c_str());

    if (settings::aimbot.drawfov)
        draw_fov_circle(settings::aimbot.fovsize, ImColor(255, 255, 255, 255), 1.5f, 100); // White FOV circle

    uintptr_t GameState = read<uint64_t>(LocalPtrs::Gworld + offsets::GameState);
    if (!GameState) return;

    uintptr_t PlayerArray = read<uint64_t>(GameState + offsets::PlayerArray);
    if (!PlayerArray) return;

    int PlayerCount = read<int>(GameState + offsets::PlayerArray + sizeof(uintptr_t));
    if (PlayerCount <= 0) return;

    std::vector<PawnData> pawns;
    pawns.reserve(PlayerCount);

    for (int i = 0; i < PlayerCount; i++) {
        uintptr_t PlayerState = read<uint64_t>(PlayerArray + i * sizeof(uintptr_t));
        if (!PlayerState) continue;

        uintptr_t pawn_private = read<uint64_t>(PlayerState + offsets::PawnPrivate);
        if (!pawn_private || pawn_private == LocalPtrs::Player) continue;

        PawnData data = GetPawnData(pawn_private);
        if (!data.mesh || data.isDead) continue;

        pawns.push_back(data);
    }

    PawnData* FinalTargetData = nullptr;
    float closestCrossDist = FLT_MAX;
    for (auto& data : pawns) {
        Vector2 screenPos = data.head2D;
        if (screenPos.x == 0 && screenPos.y == 0) continue;

        float crossDist = get_cross_distance(screenPos.x, screenPos.y, Width / 2, Height / 2);
        if (crossDist < closestCrossDist && crossDist <= settings::aimbot.fovsize) {
            FinalTargetData = &data;
            closestCrossDist = crossDist;
        }
    }

    for (auto& data : pawns) {
        float distance = vCamera.Location.Distance(data.head3D) / 100.0f;
        if (distance > settings::esp.espdis) continue;

        float height = fabsf(data.head2D.y - data.bottom2D.y) * 1.1f;
        float width = height * 0.35f;
        float topOffset = height * 0.1f;

        float boxTop = data.head2D.y - topOffset;
        float boxBottom = data.bottom2D.y;
        float boxLeft = data.head2D.x - width / 2.f;
        float boxRight = data.head2D.x + width / 2.f;
        float boxCenterX = (boxLeft + boxRight) / 2.0f;
        if (settings::esp.box)
            DrawBox(boxLeft, boxTop, width, height, data.boxColor, 2.5f, settings::esp.boxType, settings::esp.boxOutlined);

        if (settings::esp.snapline)
            draw->AddLine(ImVec2(Width * 0.5f, Height), ImVec2(boxCenterX, boxBottom), ImColor(255, 255, 255, 255), 2.5f);

        if (settings::esp.skeletonesp)
            DrawSkeleton(data.mesh, ImColor(255, 255, 255, 255), settings::esp.skeleton_thickness, settings::esp.skeletonoutlined, settings::esp.headesp, data.head3D);

        if (settings::esp.username) {
            ImVec2 usernameSize = ImGui::CalcTextSize(data.username.c_str());
            ImVec2 usernamePos(boxLeft, boxTop - usernameSize.y - 2.f);
            DrawTextOutlined(data.username.c_str(), usernamePos, (float)settings::esp.textsize, ImColor(255, 255, 255, 255));
        }

        if (settings::esp.platform) {
            ImColor platformColor;
            std::string platformText = get_player_platform(data.playerState, platformColor);
            draw_player_platform(Vector2(boxCenterX, boxTop - 20.f), platformText, platformColor);
        }



        if (settings::esp.rank) {
            const int32_t rank_progress = read<int32_t>(
                read<uint64_t>(data.playerState + offsets::HabaneroComponent) + offsets::ranked_progress + 0x10
            );
            draw_player_rank_icon(Vector2(boxCenterX, boxBottom + 5), rank_progress);
        }

        if (settings::esp.distance) {
            std::string distanceStr = std::to_string((int)distance) + "m";
            ImVec2 distPos(boxLeft, boxBottom + 5.f);
            DrawTextOutlined(distanceStr.c_str(), distPos, (float)settings::esp.textsize, ImColor(255, 255, 255, 255));
        }

        if (settings::esp.weaponesp) {
            std::string weaponName = data.weaponName.empty() ? "No Item" : data.weaponName;
            ImVec2 weaponPos(boxRight - ImGui::CalcTextSize(weaponName.c_str()).x, boxBottom + 5.f);
            DrawTextOutlined(weaponName.c_str(), weaponPos, (float)settings::esp.textsize, ImColor(255, 255, 255, 255));
        }
        if (settings::aimbot.enabled && FinalTargetData && FinalTargetData->mesh) {
            Vector3 hitbox;
            switch (settings::aimbot.Hitbox) {
            case 0: hitbox = GetBoneWithRotation(FinalTargetData->mesh, 110); break;
            case 1: hitbox = GetBoneWithRotation(FinalTargetData->mesh, 66); break;
            case 2: hitbox = GetBoneWithRotation(FinalTargetData->mesh, 36); break;
            case 3: hitbox = GetBoneWithRotation(FinalTargetData->mesh, 2); break;
            case 4: {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, 3);
                int randomHitbox = dis(gen);
                hitbox = GetBoneWithRotation(FinalTargetData->mesh,
                    randomHitbox == 0 ? 110 :
                    randomHitbox == 1 ? 66 :
                    randomHitbox == 2 ? 36 : 2);
                break;
            }
            }

            if (settings::aimbot.prediction) {
                auto root = read<uint64_t>(FinalTargetData->pawn + offsets::RootComponent);
                if (root) {
                    Vector3 velocity = read<Vector3>(root + 0x188);
                    float distance = vCamera.Location.Distance(hitbox);

                    float projectileSpeed = read<float>(WorldCache::LocalWeapon + 0x212C);
                    float projectileGravityScale = read<float>(WorldCache::LocalWeapon + 0x2130);

                    if (projectileSpeed > 0)
                        hitbox = PredictLocation(hitbox, velocity, projectileSpeed, projectileGravityScale, distance);
                }
            }

            Vector2 hitboxScreen = ProjectWorldToScreen(hitbox);
            if (hitboxScreen.x != 0 && hitboxScreen.y != 0) {
                if (!settings::aimbot.vischeck || FinalTargetData->isVisible) {
                    if (GetAsyncKeyState(settings::aimbot.aimkey) && settings::aimbot.mouse)
                        aim(FinalTargetData->mesh, hitboxScreen);
                }
            }
        }
    }
}
