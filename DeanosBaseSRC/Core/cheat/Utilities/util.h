#pragma once
#include <atomic>
#include <mutex>
#include <d3d9.h>
#include <dwmapi.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <cstdlib>
#include <random>
#include <direct.h>
#include <fstream>
#include <string>
#include <sstream>
#include <numbers>
#include "../Renderer/ImGui/imgui.h"
#include "settings.h"
#include "../Renderer/ImGui/imgui_impl_dx11.h"
#include "../Renderer/ImGui/imgui_impl_win32.h"
#include "../../driver/driver.hpp"

inline int Width = GetSystemMetrics(SM_CXSCREEN);
inline int Height = GetSystemMetrics(SM_CYSCREEN);

class Vector2 {
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(double _x, double _y) : x(_x), y(_y) {}
	~Vector2() {}

	double x, y;
};

class Vector3 {
public:
	double x, y, z;

	Vector3() : x(0.0), y(0.0), z(0.0) {}
	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	~Vector3() {}

	inline double Dot(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	inline double Distance(const Vector3& v) const {
		return std::sqrt(
			(v.x - x) * (v.x - x) +
			(v.y - y) * (v.y - y) +
			(v.z - z) * (v.z - z)
		);
	}

	inline double Length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator*(double flNum) const {
		return Vector3(x * flNum, y * flNum, z * flNum);
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	inline Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	inline Vector3& operator*=(double flNum) {
		x *= flNum; y *= flNum; z *= flNum;
		return *this;
	}

	inline double DistanceSquared(const Vector3& other) const {
		double dx = x - other.x;
		double dy = y - other.y;
		double dz = z - other.z;
		return dx * dx + dy * dy + dz * dz;
	}

	inline bool operator==(const Vector3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	inline bool operator!=(const Vector3& other) const {
		return !(*this == other);
	}
};

struct FPlane : Vector3 { double W; FPlane() : W(0) {} FPlane(double W) : W(W) {} };

class FMatrix {
public:
	double m[4][4];
	FPlane XPlane, YPlane, ZPlane, WPlane;

	FMatrix() : XPlane(), YPlane(), ZPlane(), WPlane() {}
	FMatrix(FPlane X, FPlane Y, FPlane Z, FPlane W) : XPlane(X), YPlane(Y), ZPlane(Z), WPlane(W) {}

	D3DMATRIX ToD3DMATRIX() const {
		D3DMATRIX r;
		r._11 = XPlane.x; r._12 = XPlane.y; r._13 = XPlane.z; r._14 = XPlane.W;
		r._21 = YPlane.x; r._22 = YPlane.y; r._23 = YPlane.z; r._24 = YPlane.W;
		r._31 = ZPlane.x; r._32 = ZPlane.y; r._33 = ZPlane.z; r._34 = ZPlane.W;
		r._41 = WPlane.x; r._42 = WPlane.y; r._43 = WPlane.z; r._44 = WPlane.W;
		return r;
	}
};
struct frotator
{
	double Pitch;
	double Yaw;
	double Roll;
};
#define M_PI       3.14159265358979323846   // pi

frotator VectorToRotator(Vector3 vector) {
	frotator placeholder;
	double hyp = sqrt(vector.x * vector.x + vector.y * vector.y);

	placeholder.Pitch = atan2(vector.z, hyp) * (180.0 / M_PI);
	placeholder.Yaw = atan2(vector.y, vector.x) * (180.0 / M_PI);
	placeholder.Roll = 0.0;
	return placeholder;
}

struct FQuat { double x, y, z, w; };

struct FTransform final {
	FQuat Rotation;
	Vector3 Translation;
	uint8_t Pad1[0x8];
	Vector3 Scale3D;
	uint8_t Pad2[0x8];

	FMatrix ToMatrixWithScale() const {
		Vector3 S((Scale3D.x == 0.0) ? 1.0 : Scale3D.x, (Scale3D.y == 0.0) ? 1.0 : Scale3D.y, (Scale3D.z == 0.0) ? 1.0 : Scale3D.z);
		double x2 = Rotation.x + Rotation.x;
		double y2 = Rotation.y + Rotation.y;
		double z2 = Rotation.z + Rotation.z;
		double xx2 = Rotation.x * x2;
		double yy2 = Rotation.y * y2;
		double zz2 = Rotation.z * z2;
		double yz2 = Rotation.y * z2;
		double wx2 = Rotation.w * x2;
		double xy2 = Rotation.x * y2;
		double wz2 = Rotation.w * z2;
		double xz2 = Rotation.x * z2;
		double wy2 = Rotation.w * y2;

		FMatrix M;
		M.WPlane.x = Translation.x; M.WPlane.y = Translation.y; M.WPlane.z = Translation.z;
		M.XPlane.x = (1.0 - (yy2 + zz2)) * S.x; M.YPlane.y = (1.0 - (xx2 + zz2)) * S.y; M.ZPlane.z = (1.0 - (xx2 + yy2)) * S.z;
		M.ZPlane.y = (yz2 - wx2) * S.z; M.YPlane.z = (yz2 + wx2) * S.y;
		M.YPlane.x = (xy2 - wz2) * S.y; M.XPlane.y = (xy2 + wz2) * S.x;
		M.ZPlane.x = (xz2 + wy2) * S.z; M.XPlane.z = (xz2 - wy2) * S.x;
		M.XPlane.W = 0; M.YPlane.W = 0; M.ZPlane.W = 0; M.WPlane.W = 1;
		return M;
	}
};

struct Camera { Vector3 Location, Rotation; float FieldOfView; };

template<class T>
class tarray {
public:
	T* data = nullptr;
	std::int32_t count = 0, maxx = 0;
	tarray() {}
	tarray(T* d, std::int32_t c, std::int32_t m) : data(d), count(c), maxx(m) {}

	bool is_valid() const noexcept { return data != nullptr; }
	std::int32_t size() const noexcept { return count; }
	bool is_valid_index(std::int32_t i) const noexcept { return i < size(); }

	T& operator[](std::int32_t i) noexcept { return data[i]; }
	const T& operator[](std::int32_t i) const noexcept { return data[i]; }
};

inline D3DMATRIX MatrixMultiplication(D3DMATRIX m1, D3DMATRIX m2) {
	D3DMATRIX o;
	o._11 = m1._11 * m2._11 + m1._12 * m2._21 + m1._13 * m2._31 + m1._14 * m2._41;
	o._12 = m1._11 * m2._12 + m1._12 * m2._22 + m1._13 * m2._32 + m1._14 * m2._42;
	o._13 = m1._11 * m2._13 + m1._12 * m2._23 + m1._13 * m2._33 + m1._14 * m2._43;
	o._14 = m1._11 * m2._14 + m1._12 * m2._24 + m1._13 * m2._34 + m1._14 * m2._44;
	o._21 = m1._21 * m2._11 + m1._22 * m2._21 + m1._23 * m2._31 + m1._24 * m2._41;
	o._22 = m1._21 * m2._12 + m1._22 * m2._22 + m1._23 * m2._32 + m1._24 * m2._42;
	o._23 = m1._21 * m2._13 + m1._22 * m2._23 + m1._23 * m2._33 + m1._24 * m2._43;
	o._24 = m1._21 * m2._14 + m1._22 * m2._24 + m1._23 * m2._34 + m1._24 * m2._44;
	o._31 = m1._31 * m2._11 + m1._32 * m2._21 + m1._33 * m2._31 + m1._34 * m2._41;
	o._32 = m1._31 * m2._12 + m1._32 * m2._22 + m1._33 * m2._32 + m1._34 * m2._42;
	o._33 = m1._31 * m2._13 + m1._32 * m2._23 + m1._33 * m2._33 + m1._34 * m2._43;
	o._34 = m1._31 * m2._14 + m1._32 * m2._24 + m1._33 * m2._34 + m1._34 * m2._44;
	o._41 = m1._41 * m2._11 + m1._42 * m2._21 + m1._43 * m2._31 + m1._44 * m2._41;
	o._42 = m1._41 * m2._12 + m1._42 * m2._22 + m1._43 * m2._32 + m1._44 * m2._42;
	o._43 = m1._41 * m2._13 + m1._42 * m2._23 + m1._43 * m2._33 + m1._44 * m2._43;
	o._44 = m1._41 * m2._14 + m1._42 * m2._24 + m1._43 * m2._34 + m1._44 * m2._44;
	return o;
}

inline D3DMATRIX Matrix(Vector3 r) {
	float p = r.x * float(std::numbers::pi) / 180.f;
	float y = r.y * float(std::numbers::pi) / 180.f;
	float ro = r.z * float(std::numbers::pi) / 180.f;

	float SP = sinf(p), CP = cosf(p);
	float SY = sinf(y), CY = cosf(y);
	float SR = sinf(ro), CR = cosf(ro);

	D3DMATRIX m;
	m.m[0][0] = CP * CY; m.m[0][1] = CP * SY; m.m[0][2] = SP; m.m[0][3] = 0.f;
	m.m[1][0] = SR * SP * CY - CR * SY; m.m[1][1] = SR * SP * SY + CR * CY; m.m[1][2] = -SR * CP; m.m[1][3] = 0.f;
	m.m[2][0] = -(CR * SP * CY + SR * SY); m.m[2][1] = CY * SR - CR * SP * SY; m.m[2][2] = CR * CP; m.m[2][3] = 0.f;
	m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1.f;
	return m;
}




inline void DrawCornerBox(float x, float y, float w, float h, const ImColor& color, float thickness = 1.0f) {
	const float lw = w * 0.33f;
	const float lh = h * 0.33f;

	ImDrawList* draw = ImGui::GetBackgroundDrawList();

	draw->AddLine(ImVec2(x, y), ImVec2(x + lw, y), color, thickness);
	draw->AddLine(ImVec2(x, y), ImVec2(x, y + lh), color, thickness);

	draw->AddLine(ImVec2(x + w - lw, y), ImVec2(x + w, y), color, thickness);
	draw->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + lh), color, thickness);

	draw->AddLine(ImVec2(x, y + h - lh), ImVec2(x, y + h), color, thickness);
	draw->AddLine(ImVec2(x, y + h), ImVec2(x + lw, y + h), color, thickness);

	draw->AddLine(ImVec2(x + w - lw, y + h), ImVec2(x + w, y + h), color, thickness);
	draw->AddLine(ImVec2(x + w, y + h - lh), ImVec2(x + w, y + h), color, thickness);
}
inline void DrawBox(float x, float y, float w, float h, const ImColor& color, float thickness, BoxType type, bool outlined = false)
{
	ImDrawList* draw = ImGui::GetBackgroundDrawList();

	ImColor outlineColor = IM_COL32(0, 0, 0, 255); 
	float outlineOffset = 1.5f;                    

	switch (type)
	{
	case CORNER:
	{
		const float lw = w * 0.33f;
		const float lh = h * 0.33f;

		if (outlined)
		{
			draw->AddLine(ImVec2(x - outlineOffset, y - outlineOffset), ImVec2(x + lw + outlineOffset, y - outlineOffset), outlineColor, thickness + 1.5f);
			draw->AddLine(ImVec2(x - outlineOffset, y - outlineOffset), ImVec2(x - outlineOffset, y + lh + outlineOffset), outlineColor, thickness + 1.5f);

			draw->AddLine(ImVec2(x + w - lw - outlineOffset, y - outlineOffset), ImVec2(x + w + outlineOffset, y - outlineOffset), outlineColor, thickness + 1.5f);
			draw->AddLine(ImVec2(x + w + outlineOffset, y - outlineOffset), ImVec2(x + w + outlineOffset, y + lh + outlineOffset), outlineColor, thickness + 1.5f);

			draw->AddLine(ImVec2(x - outlineOffset, y + h - lh - outlineOffset), ImVec2(x - outlineOffset, y + h + outlineOffset), outlineColor, thickness + 1.5f);
			draw->AddLine(ImVec2(x - outlineOffset, y + h + outlineOffset), ImVec2(x + lw + outlineOffset, y + h + outlineOffset), outlineColor, thickness + 1.5f);

			draw->AddLine(ImVec2(x + w - lw - outlineOffset, y + h + outlineOffset), ImVec2(x + w + outlineOffset, y + h + outlineOffset), outlineColor, thickness + 1.5f);
			draw->AddLine(ImVec2(x + w + outlineOffset, y + h - lh - outlineOffset), ImVec2(x + w + outlineOffset, y + h + outlineOffset), outlineColor, thickness + 1.5f);
		}

		draw->AddLine(ImVec2(x, y), ImVec2(x + lw, y), color, thickness);
		draw->AddLine(ImVec2(x, y), ImVec2(x, y + lh), color, thickness);

		draw->AddLine(ImVec2(x + w - lw, y), ImVec2(x + w, y), color, thickness);
		draw->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + lh), color, thickness);

		draw->AddLine(ImVec2(x, y + h - lh), ImVec2(x, y + h), color, thickness);
		draw->AddLine(ImVec2(x, y + h), ImVec2(x + lw, y + h), color, thickness);

		draw->AddLine(ImVec2(x + w - lw, y + h), ImVec2(x + w, y + h), color, thickness);
		draw->AddLine(ImVec2(x + w, y + h - lh), ImVec2(x + w, y + h), color, thickness);
		break;
	}

	case OUTLINE:
		if (outlined)
			draw->AddRect(ImVec2(x - outlineOffset, y - outlineOffset), ImVec2(x + w + outlineOffset, y + h + outlineOffset), outlineColor, 0.f, 0, thickness + 1.5f);

		draw->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.f, 0, thickness);
		break;

	case FILLED:
		if (outlined)
			draw->AddRect(ImVec2(x - outlineOffset, y - outlineOffset), ImVec2(x + w + outlineOffset, y + h + outlineOffset), outlineColor, 0.f, 0, thickness + 1.5f);

		draw->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(color.Value.x, color.Value.y, color.Value.z, 0.25f));
		draw->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.f, 0, thickness);
		break;
	}
}


void circle(const Vector2& pos, float radius, ImU32 color, int segments = 64, float thickness = 1.0f) {
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(pos.x, pos.y), radius, color, segments, thickness);
}

void draw_fov_circle(int fov_size, ImColor color, float thickness = 1.0f, int segments = 64) {
	ImVec2 screen_size = ImGui::GetIO().DisplaySize;

	Vector2 center(screen_size.x / 2.0f, screen_size.y / 2.0f);

	circle(center, (float)fov_size, color, segments, thickness);
}
inline void DrawTextOutlined(const char* text, ImVec2 pos, float size, ImColor color)
{
	ImDrawList* draw = ImGui::GetBackgroundDrawList();
	draw->AddText(ImGui::GetFont(), size, ImVec2(pos.x - 1, pos.y - 1), IM_COL32(0, 0, 0, 255), text);
	draw->AddText(ImGui::GetFont(), size, ImVec2(pos.x + 1, pos.y - 1), IM_COL32(0, 0, 0, 255), text);
	draw->AddText(ImGui::GetFont(), size, ImVec2(pos.x - 1, pos.y + 1), IM_COL32(0, 0, 0, 255), text);
	draw->AddText(ImGui::GetFont(), size, ImVec2(pos.x + 1, pos.y + 1), IM_COL32(0, 0, 0, 255), text);
	draw->AddText(ImGui::GetFont(), size, pos, color, text);
}


void draw_line(Vector2 start, Vector2 end, ImU32 color, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), color, thickness);
}

static float powf_(float _X, float _Y)
{
	return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
}

static float sqrtf_(float _X) {
	return (_mm_cvtss_f32(_mm_sqrt_ps(_mm_set_ss(_X))));
}
static double get_cross_distance(double x1, double y1, double x2, double y2) {
	return sqrtf(powf((x2 - x1), 2) + powf_((y2 - y1), 2));
}
Vector3 PredictLocation(Vector3 target, Vector3 targetVelocity, float projectileSpeed, float projectileGravityScale, float distance)
{
	float horizontalTime = distance / projectileSpeed;
	float verticalTime = distance / projectileSpeed;

	target.x += targetVelocity.x * horizontalTime;
	target.y += targetVelocity.y * horizontalTime;
	target.z += targetVelocity.z * verticalTime +
		abs(-980 * projectileGravityScale) * 0.5f * (verticalTime * verticalTime);

	return target;
}
std::string get_rank_name(int tier)
{
	switch (tier)
	{
	case 0: return "Bronze 1";
	case 1: return "Bronze 2";
	case 2: return "Bronze 3";
	case 3: return "Silver 1";
	case 4: return "Silver 2";
	case 5: return "Silver 3";
	case 6: return "Gold 1";
	case 7: return "Gold 2";
	case 8: return "Gold 3";
	case 9: return "Platinum 1";
	case 10: return "Platinum 2";
	case 11: return "Platinum 3";
	case 12: return "Diamond 1";
	case 13: return "Diamond 2";
	case 14: return "Diamond 3";
	case 15: return "Elite";
	case 16: return "Champion";
	case 17: return "Unreal";
	default: return "Unranked";
	}
}

ImVec4 get_rank_color(int tier)
{
	switch (tier)
	{
	case 0: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	case 1:
	case 2: return ImVec4(0.902f, 0.580f, 0.227f, 1.0f);
	case 3:
	case 4:
	case 5: return ImVec4(0.843f, 0.843f, 0.843f, 1.0f);
	case 6:
	case 7:
	case 8: return ImVec4(1.0f, 0.871f, 0.0f, 1.0f);
	case 9:
	case 10:
	case 11: return ImVec4(0.0f, 0.7f, 0.7f, 1.0f);
	case 12:
	case 13:
	case 14: return ImVec4(0.1686f, 0.3294f, 0.8235f, 1.0f);
	case 15: return ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	case 16: return ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
	case 17: return ImVec4(0.6f, 0.0f, 0.6f, 1.0f);
	default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}
ImFont* MenuFont;

void text(const std::string& text, const ImVec2& pos, float size, ImColor color, bool center) {
	constexpr float StrokeValue = 0.9f;
	uint32_t EdgeColor = 0xFF000000;

	float EdgeA = (EdgeColor >> 24) & 0xff;
	float EdgeR = (EdgeColor >> 16) & 0xff;
	float EdgeG = (EdgeColor >> 8) & 0xff;
	float EdgeB = (EdgeColor) & 0xff;

	std::stringstream StringStream(text);
	std::string Line;
	float Y = 0.0f;
	int I = 0;
	ImGui::PushFont(MenuFont);
	while (getline(StringStream, Line)) {
		ImVec2 TextSize = ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, 0.0f, Line.c_str());

		if (center) {
			if (settings::esp.outlinetext) {
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - TextSize.x / 2.0f) - StrokeValue, pos.y + TextSize.y * I), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - TextSize.x / 2.0f) + StrokeValue, pos.y + TextSize.y * I), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - TextSize.x / 2.0f), (pos.y + TextSize.y * I) - StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - TextSize.x / 2.0f), (pos.y + TextSize.y * I) + StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
			}
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(pos.x - TextSize.x / 2.0f, pos.y + TextSize.y * I), color, Line.c_str());
		}
		else {
			if (settings::esp.outlinetext) {
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x) - StrokeValue, (pos.y + TextSize.y * I)), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x) + StrokeValue, (pos.y + TextSize.y * I)), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x), (pos.y + TextSize.y * I) - StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x), (pos.y + TextSize.y * I) + StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
			}
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(pos.x, pos.y + TextSize.y * I), color, Line.c_str());
		}

		Y = pos.y + TextSize.y * (I + 1);
		I++;
	}
	ImGui::PopFont();
}
enum bone : int
{
	HumanBase = 0,
	HumanPelvis = 2,
	HumanLThigh1 = 71,
	HumanLThigh2 = 77,
	HumanLThigh3 = 72,
	HumanLCalf = 74,
	HumanLFoot2 = 122,
	HumanLFoot = 122,
	HumanLToe = 76,
	HumanRThigh1 = 78,
	HumanRThigh2 = 84,
	HumanRThigh3 = 79,
	HumanRCalf = 81,
	HumanRFoot2 = 82,
	HumanRFoot = 87,
	HumanRToe = 83,
	HumanSpine1 = 7,
	HumanSpine2 = 5,
	HumanSpine3 = 2,
	HumanLCollarbone = 9,
	HumanLUpperarm = 35,
	HumanLForearm1 = 36,
	HumanLForearm23 = 10,
	HumanLForearm2 = 34,
	HumanLForearm3 = 33,
	HumanLPalm = 32,
	HumanLHand = 11,
	HumanRCollarbone = 98,
	HumanRUpperarm = 64,
	HumanRForearm1 = 65,
	HumanRForearm23 = 39,
	HumanRForearm2 = 63,
	HumanRForearm3 = 62,
	HumanRHand = 40,
	HumanRPalm = 58,
	HumanNeck = 66,
	HumanHead = 110,
	HumanLowerHead = 106,

	HumanChest = 65
};

Vector3 CalculateNewRotation(Vector3& zaz, Vector3& daz) {
	Vector3 dalte = zaz - daz;
	Vector3 ongle;
	float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
	ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
	ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;
	if (dalte.x >= 0.f) ongle.y += 180.f;
	return ongle;
}


