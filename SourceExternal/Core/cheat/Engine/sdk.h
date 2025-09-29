#pragma once
#include "../Utilities/util.h"
#include "../Visuals/esp.h"
#include "offsets.hpp"
#include "sdk.h"
#include <math.h>
#include <numbers>

namespace LocalPtrs {
	inline uintptr_t Player;
	inline uintptr_t Mesh;
	inline uintptr_t PlayerState;
	inline uintptr_t RootComponent;
	inline uintptr_t LocalPlayers;
	inline uintptr_t PlayerController;
	inline uintptr_t Gworld;
}
namespace WorldCache {
	inline uintptr_t AcknowledgedPawn = 0;
	inline uintptr_t Mesh = 0;
	inline uintptr_t PlayerState = 0;
	inline uintptr_t RootComponent = 0;
	inline uintptr_t LocalWeapon = 0;
	inline uintptr_t LocalVehicle = 0;
    inline uintptr_t MovementMode = 0;
	inline char TeamIndex = 0;
}

inline Camera vCamera;
Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id) {
	int32_t ActiveTransforms = read<int32_t>(mesh + (offsets::BoneArray + 0x48)) * 0x10;
	auto bone_array = read<tarray<FTransform>>((uintptr_t)mesh + offsets::BoneArray + ActiveTransforms);
	auto BoneTransform = read<FTransform>((uintptr_t)bone_array.data + (id * 0x60));
	FTransform ComponentToWorld = read<FTransform>((uintptr_t)mesh + offsets::ComponentToWorld);

	D3DMATRIX Matrix = MatrixMultiplication(BoneTransform.ToMatrixWithScale().ToD3DMATRIX(), ComponentToWorld.ToMatrixWithScale().ToD3DMATRIX());

	Vector3 bonePos(Matrix._41, Matrix._42, Matrix._43);

	return bonePos;
}


struct CamewaDescwipsion {
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
};

Camera GetViewAngles() {
	CamewaDescwipsion camera;
	auto locationPointer = read<uintptr_t>(LocalPtrs::Gworld + CameraLocation);
	auto rotationPointer = read<uintptr_t>(LocalPtrs::Gworld + CameraRotation);

	struct Rotation {
		double a;
		char pad_0008[24];
		double b;
		char pad_0028[424];
		double c;
	};
	Rotation rotation;
	rotation = read<Rotation>(rotationPointer);

	camera.Location = read<Vector3>(locationPointer);
	camera.Rotation.x = asin(rotation.c) * (180.0 / std::numbers::pi);
	camera.Rotation.y = ((atan2(rotation.a * -1, rotation.b) * (180.0 / std::numbers::pi)) * -1) * -1;
	camera.FieldOfView = read<float>(LocalPtrs::PlayerController + 0x3AC) * 90.f;

	return { camera.Location, camera.Rotation, camera.FieldOfView };
}
bool is_dead(uintptr_t pawn_private)
{
	return (read<char>(pawn_private + offsets::b_is_dying) >> 5) & 1;
}

Vector2 ProjectWorldToScreen(Vector3 WorldLocation) {
	vCamera = GetViewAngles();

	auto mMatrix = Matrix(vCamera.Rotation);
	auto XAxis = Vector3(mMatrix.m[0][0], mMatrix.m[0][1], mMatrix.m[0][2]);
	auto YAxis = Vector3(mMatrix.m[1][0], mMatrix.m[1][1], mMatrix.m[1][2]);
	auto ZAxis = Vector3(mMatrix.m[2][0], mMatrix.m[2][1], mMatrix.m[2][2]);

	auto vDeltaCoordinates = WorldLocation - vCamera.Location;
	auto tTransform = Vector3(vDeltaCoordinates.Dot(YAxis), vDeltaCoordinates.Dot(ZAxis), vDeltaCoordinates.Dot(XAxis));

	tTransform.z = (tTransform.z < 1.f) ? 1.f : tTransform.z;
	auto fov_radians = tan(vCamera.FieldOfView * std::numbers::pi / 360.f);

	return Vector2(Width / 2 + tTransform.x * ((Width / 2) / fov_radians) / tTransform.z, Height / 2 - tTransform.y * ((Width / 2) / fov_radians) / tTransform.z);
}

bool IsEnemyVisible(uintptr_t Mesh) {
	auto Seconds = read<double>(LocalPtrs::Gworld + 0x198);
	auto LastRenderTime = read<float>(Mesh + 0x1A0);
	return Seconds - LastRenderTime <= 0.06f;
}

float GetDistanceToCrosshair(uintptr_t Mesh) {
	Vector3 headBone = GetBoneWithRotation(Mesh, 110);
	Vector3 headTop = headBone;
	headTop.z += 5.0f; // keep consistent offset with DrawSkeleton

	Vector2 head2D = ProjectWorldToScreen(headTop);
	float centerX = Width / 2.0f;
	float centerY = Height / 2.0f;
	return sqrtf((head2D.x - centerX) * (head2D.x - centerX) + (head2D.y - centerY) * (head2D.y - centerY));
}

float GetFOVDistance(uintptr_t Mesh) {
	Vector3 headBone = GetBoneWithRotation(Mesh, 110);
	Vector3 headTop = headBone;
	headTop.z += 5.0f;

	Vector2 head2D = ProjectWorldToScreen(headTop);
	float centerX = Width / 2.0f;
	float centerY = Height / 2.0f;
	return fabsf(head2D.x - centerX) + fabsf(head2D.y - centerY);
}
void DrawPremiumText(ImDrawList* drawList, ImVec2 pos, const char* text,
    ImU32 textColor = IM_COL32(255, 255, 255, 255),
    ImU32 outlineColor = IM_COL32(0, 0, 0, 200),
    ImU32 shadowColor = IM_COL32(0, 0, 0, 100),
    float outlineThickness = 1.5f) {

    drawList->AddText(ImVec2(pos.x + 2, pos.y + 2), shadowColor, text);

    for (float i = -outlineThickness; i <= outlineThickness; i += 0.5f) {
        for (float j = -outlineThickness; j <= outlineThickness; j += 0.5f) {
            if (i == 0 && j == 0) continue;
            float distance = sqrtf(i * i + j * j);
            if (distance <= outlineThickness) {
                ImU32 layerColor = IM_COL32(
                    (outlineColor >> IM_COL32_R_SHIFT) & 0xFF,
                    (outlineColor >> IM_COL32_G_SHIFT) & 0xFF,
                    (outlineColor >> IM_COL32_B_SHIFT) & 0xFF,
                    (int)((float)((outlineColor >> IM_COL32_A_SHIFT) & 0xFF) * (1.0f - distance / outlineThickness))
                );
                drawList->AddText(ImVec2(pos.x + i, pos.y + j), layerColor, text);
            }
        }
    }

    drawList->AddText(pos, textColor, text);

    ImU32 glowColor = IM_COL32(
        (textColor >> IM_COL32_R_SHIFT) & 0xFF,
        (textColor >> IM_COL32_G_SHIFT) & 0xFF,
        (textColor >> IM_COL32_B_SHIFT) & 0xFF,
        80
    );
    drawList->AddText(ImVec2(pos.x + 0.5f, pos.y + 0.5f), glowColor, text);
}

void DrawPremiumBox(ImDrawList* drawList, ImVec2 topLeft, ImVec2 bottomRight,
    ImU32 borderColor = IM_COL32(255, 255, 255, 255),
    ImU32 cornerColor = IM_COL32(255, 255, 255, 180),
    float thickness = 2.0f, float cornerSize = 8.0f) {

    drawList->AddRect(topLeft, bottomRight, borderColor, 2.0f, 0, thickness);

    float cornerLength = cornerSize;
    ImU32 accentColor = IM_COL32(255, 255, 255, 200);

    drawList->AddLine(
        ImVec2(topLeft.x, topLeft.y),
        ImVec2(topLeft.x + cornerLength, topLeft.y),
        accentColor, thickness + 1.0f
    );
    drawList->AddLine(
        ImVec2(topLeft.x, topLeft.y),
        ImVec2(topLeft.x, topLeft.y + cornerLength),
        accentColor, thickness + 1.0f
    );

    drawList->AddLine(
        ImVec2(bottomRight.x, topLeft.y),
        ImVec2(bottomRight.x - cornerLength, topLeft.y),
        accentColor, thickness + 1.0f
    );
    drawList->AddLine(
        ImVec2(bottomRight.x, topLeft.y),
        ImVec2(bottomRight.x, topLeft.y + cornerLength),
        accentColor, thickness + 1.0f
    );

    drawList->AddLine(
        ImVec2(topLeft.x, bottomRight.y),
        ImVec2(topLeft.x + cornerLength, bottomRight.y),
        accentColor, thickness + 1.0f
    );
    drawList->AddLine(
        ImVec2(topLeft.x, bottomRight.y),
        ImVec2(topLeft.x, bottomRight.y - cornerLength),
        accentColor, thickness + 1.0f
    );

    drawList->AddLine(
        ImVec2(bottomRight.x, bottomRight.y),
        ImVec2(bottomRight.x - cornerLength, bottomRight.y),
        accentColor, thickness + 1.0f
    );
    drawList->AddLine(
        ImVec2(bottomRight.x, bottomRight.y),
        ImVec2(bottomRight.x, bottomRight.y - cornerLength),
        accentColor, thickness + 1.0f
    );
}
float CalculateDistanceInMeters(const Vector3& targetPos) {
    Vector3 cameraPos = vCamera.Location;
    float distance = sqrtf(
        powf(targetPos.x - cameraPos.x, 2) +
        powf(targetPos.y - cameraPos.y, 2) +
        powf(targetPos.z - cameraPos.z, 2)
    );
    return distance / 100.0f;
}

void DrawPremiumHealthBar(ImDrawList* drawList, ImVec2 pos, float width, float height,
    float healthPercent, bool isVisible) {

    ImU32 bgColor = IM_COL32(0, 0, 0, 160);
    ImU32 borderColor = IM_COL32(255, 255, 255, 200);

    drawList->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), bgColor, 2.0f);
    drawList->AddRect(pos, ImVec2(pos.x + width, pos.y + height), borderColor, 2.0f, 0, 1.0f);

    float healthWidth = (width - 2) * healthPercent;

    if (healthWidth > 1.0f) {
        ImU32 healthColorStart, healthColorEnd;

        if (healthPercent > 0.75f) {
            healthColorStart = IM_COL32(100, 255, 100, 255);
            healthColorEnd = IM_COL32(80, 200, 80, 255);
        }
        else if (healthPercent > 0.5f) {
            healthColorStart = IM_COL32(255, 255, 100, 255);
            healthColorEnd = IM_COL32(200, 200, 80, 255);
        }
        else if (healthPercent > 0.25f) {
            healthColorStart = IM_COL32(255, 180, 100, 255);
            healthColorEnd = IM_COL32(200, 140, 80, 255);
        }
        else {
            healthColorStart = IM_COL32(255, 100, 100, 255);
            healthColorEnd = IM_COL32(200, 80, 80, 255);
        }

        drawList->AddRectFilledMultiColor(
            ImVec2(pos.x + 1, pos.y + 1),
            ImVec2(pos.x + healthWidth + 1, pos.y + height - 1),
            healthColorStart, healthColorEnd,
            healthColorEnd, healthColorStart
        );

        ImU32 glowColor = IM_COL32(
            (healthColorStart >> IM_COL32_R_SHIFT) & 0xFF,
            (healthColorStart >> IM_COL32_G_SHIFT) & 0xFF,
            (healthColorStart >> IM_COL32_B_SHIFT) & 0xFF,
            60
        );
        drawList->AddRectFilled(
            ImVec2(pos.x, pos.y - 1),
            ImVec2(pos.x + healthWidth + 2, pos.y + height + 1),
            glowColor, 3.0f
        );
    }
}

static std::string GetPlayerName(uintptr_t playerState) {
	auto Name = read<uintptr_t>(playerState + offsets::username_component);
	auto length = read<int>(Name + 0x10);
	auto v6 = (__int64)length;
	auto displayname = read<char>(playerState + 0x268);

	if (!v6) return std::string("NaN");

	auto FText = (uintptr_t)read<__int64>(Name + 0x8);

	wchar_t* Buffer = new wchar_t[length];
	Driver::ReadPhysicalMemory(reinterpret_cast<PVOID>(FText), Buffer, length * sizeof(wchar_t));



	char v21;
	int v22;
	int i;

	int v25;
	UINT16* v23;

	v21 = v6 - 1;
	if (!(UINT32)v6)
		v21 = 0;
	v22 = 0;
	v23 = (UINT16*)Buffer;
	for (i = (v21) & 3; ; *v23++ += i & 7)
	{
		v25 = v6 - 1;
		if (!(UINT32)v6)
			v25 = 0;
		if (v22 >= v25)
			break;
		i += 3;
		++v22;
	}

	std::wstring PlayerName{ Buffer };
	delete[] Buffer;
	return std::string(PlayerName.begin(), PlayerName.end());
};

std::string GetWeaponName(uintptr_t Player) {
	std::string weapon_name;

	uint64_t current_weapon = read<uint64_t>(Player + offsets::current_weapon);
	uint64_t weapon_data = read<uint64_t>(current_weapon + offsets::weapon_data);
	uint64_t item_name = read<uint64_t>(weapon_data + 0x40);

	uint64_t FData = read<uint64_t>(item_name + 0x20);
	int FLength = read<int>(item_name + 0x28);

	if (FLength > 0 && FLength < 50)
	{
		wchar_t* WeaponBuffer = new wchar_t[FLength];
		Driver::ReadPhysicalMemory(reinterpret_cast<PVOID>(FData), WeaponBuffer, FLength * sizeof(wchar_t));

		std::wstring wstr_buf(WeaponBuffer);
		weapon_name.append(std::string(wstr_buf.begin(), wstr_buf.end()));

		delete[] WeaponBuffer;
	}

	return weapon_name;
};
