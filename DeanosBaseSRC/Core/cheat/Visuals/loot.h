


#pragma once
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <string>


ImFont* ESPFont;
enum class EFortRarity : uint8_t {
	EFortRarity__Common = 0,
	EFortRarity__Uncommon = 1,
	EFortRarity__Rare = 2,
	EFortRarity__Epic = 3,
	EFortRarity__Legendary = 4,
	EFortRarity__Mythic = 5,
	EFortRarity__Transcendent = 6,
	EFortRarity__Unattainable = 7,
	EFortRarity__NumRarityValues = 8,
	EFortRarity__EFortRarity_MAX = 9
};


inline ImColor get_loot_color(EFortRarity tier)
{
	switch (tier)
	{
	case EFortRarity::EFortRarity__Common: return ImColor(123, 123, 123, 255);
	case EFortRarity::EFortRarity__Uncommon: return ImColor(58, 121, 19, 255);
	case EFortRarity::EFortRarity__Rare: return ImColor(18, 88, 162, 255);
	case EFortRarity::EFortRarity__Epic: return ImColor(189, 63, 250, 255);
	case EFortRarity::EFortRarity__Legendary: return ImColor(255, 118, 5, 255);
	case EFortRarity::EFortRarity__Mythic: return ImColor(220, 160, 30, 255);
	default: return ImColor(123, 123, 123, 255);
	}
}

class item {
public:
	uintptr_t
		Actor;

	std::string
		Name,
		isVehicle,
		isChest,
		isLamma,
		isPickup,
		isAmmoBox;
	float
		distance;
};
inline std::vector<item> item_pawns;

uintptr_t RootComponent(uintptr_t actor)
{

	return read<uintptr_t>(actor + offsets::RootComponent);
}
Vector3 GetLocation(uintptr_t actor)
{

	return read<Vector3>(RootComponent(actor) + offsets::RelativeLocation);
}
bool is_in_screen(Vector2 screen_location)
{
	return screen_location.x > 0 && screen_location.x < Width &&
		screen_location.y > 0 && screen_location.y < Height;
}
inline std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

inline void DrawString(ImDrawList* drawlist, float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[128] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		drawlist->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		drawlist->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		drawlist->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		drawlist->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	drawlist->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImColor(color), text.c_str());
}

void draw_text(ImDrawList* drawlist, ImFont* font, float fontSize, ImVec2 position, ImColor color, const char* text)
{
	drawlist->AddText(font, fontSize, ImVec2(position.x - 1, position.y - 1), ImColor(0, 0, 0), text);
	drawlist->AddText(font, fontSize, ImVec2(position.x + 1, position.y - 1), ImColor(0, 0, 0), text);
	drawlist->AddText(font, fontSize, ImVec2(position.x - 1, position.y + 1), ImColor(0, 0, 0), text);
	drawlist->AddText(font, fontSize, ImVec2(position.x + 1, position.y + 1), ImColor(0, 0, 0), text);
	drawlist->AddText(font, fontSize, position, color, text);
}
void draw_item(ImDrawList* drawlist, const char* name, const char* display_name, const ImColor& color, uintptr_t actor) {

	uintptr_t actor_root_component = read<uintptr_t>(actor + offsets::RootComponent);
	Vector3 actor_relative_location = read<Vector3>(actor_root_component + offsets::RelativeLocation);
	Vector2 location = ProjectWorldToScreen(actor_relative_location);

	float item_distance = vCamera.Location.Distance(actor_relative_location) * 0.01f;

	if (!is_in_screen(location)) return;

	char dist[64];
	sprintf_s(dist, "%.fm", item_distance);
	std::string text = std::string(display_name) + " [ " + std::string(dist) + " ]";
	ImVec2 text_size = ImGui::CalcTextSize(text.c_str());

	if (settings::esp.outline) {

		ImColor outlineColor = ImColor(0, 0, 0, 255);
		draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(location.x - text_size.x / 2 - 1, location.y - 18), outlineColor, text.c_str());
		draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(location.x - text_size.x / 2 + 1, location.y - 18), outlineColor, text.c_str());
		draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(location.x - text_size.x / 2, location.y - 18 - 1), outlineColor, text.c_str());
		draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(location.x - text_size.x / 2, location.y - 18 + 1), outlineColor, text.c_str());
	}

	draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(location.x - text_size.x / 2, location.y - 18), color, text.c_str());
}

#define __SPAIR64__(x, y) ((long long)((((uint64_t)(x)) << 32) | ((uint32_t)(y))))

class FName
{
public:
	static std::unordered_map<int32_t, std::string> cache;

	static std::string ToString(int32_t comparison_index)
	{
		if (comparison_index == 0)
			return " Cannot Find Names";

		auto it = cache.find(comparison_index);
		if (it != cache.end())
			return it->second;

		int32_t decryptedIndex = DecryptIndex(comparison_index);

	Resolve:
		if (decryptedIndex <= 0)
			return "";

		uint32_t chunkIndex = decryptedIndex >> 16;
		uint16_t nameEntryIndex = static_cast<uint16_t>(decryptedIndex);

		uint64_t namePoolChunk = read<uint64_t>(
			Base + 0x18169E40 + 8 * chunkIndex + 0x10) + 2 * nameEntryIndex;

		uint16_t pool = read<uint16_t>(namePoolChunk);

		if (((pool ^ 0xAA0) & 0x7FE0) == 0)
		{
			decryptedIndex = DecryptIndex(read<int32_t>(namePoolChunk + 6));
			goto Resolve;
		}

		int32_t nameLength = GetLength(pool);
		if (nameLength <= 0 || nameLength > 2048)
			return "";

		std::vector<char> nameBuffer(nameLength + 1);
		Driver::ReadPhysicalMemory((PVOID)(namePoolChunk + 2), nameBuffer.data(), nameLength);
		nameBuffer[nameLength] = '\0';

		DecryptFName(nameBuffer.data(), nameLength, pool);

		std::string decrypted(nameBuffer.data(), nameLength);
		cache.emplace(comparison_index, decrypted);
		return decrypted;
	}

private:
	static int32_t DecryptIndex(int32_t index)
	{
		if (index)
		{
			int32_t decryptedIndex = -((index - 1) ^ 0x3ACD0705);
			return decryptedIndex ? decryptedIndex : 986515206;
		}
		return 0;
	}

	static void DecryptFName(char* buffer, const int length, uint16_t pool)
	{
		if (length <= 0)
			return;

		char tmp[2048];
		memcpy(tmp, buffer, length);
		int64_t v4 = 0;
		int64_t v12 = static_cast<uint32_t>(0x15F51E5 + 8692 * length);
		int64_t len = length;

		do
		{
			int64_t v14 = length - v4;
			v12 = static_cast<uint32_t>(0x15F51E5 + 8692 * v12);
			char v15 = v12 - tmp[v4];
			buffer[v14 - 1] = v15 + 74;
			++v4;
			--len;
		} while (len);
		buffer[length] = '\0';
	}
	static int32_t GetLength(uint16_t pool)
	{
		return ((pool ^ 0xAA0u) >> 5) & 0x3FF;
	}
};
std::unordered_map<int32_t, std::string> FName::cache;




__forceinline void _DrawText(ImFont* Font, ImVec2 pos, ImU32 color, const char* text, float size = 18.0f, bool outline = false) {
	if (outline) {
		ImVec2 textSize = Font->CalcTextSizeA(size, FLT_MAX, 0.0f, text);
		ImColor outlineCol(1, 1, 1, 255);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2(pos.x + 1, pos.y + textSize.y + 1), ImGui::ColorConvertFloat4ToU32(outlineCol), text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2(pos.x - 1, pos.y + textSize.y - 1), ImGui::ColorConvertFloat4ToU32(outlineCol), text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2(pos.x + 1, pos.y + textSize.y - 1), ImGui::ColorConvertFloat4ToU32(outlineCol), text);
		ImGui::GetBackgroundDrawList()->AddText(Font, size, ImVec2(pos.x - 1, pos.y + textSize.y + 1), ImGui::ColorConvertFloat4ToU32(outlineCol), text);
	}
	ImGui::GetBackgroundDrawList()->AddText(Font, size, pos, color, text);
}

inline std::string GetActorName(uintptr_t actor) {
	int32_t nameIndex = read<int32_t>(actor + 0x8);
	return FName::ToString(nameIndex);
}

struct ItemBase { uintptr_t level; DWORD actors; };
std::vector<ItemBase> ItemBaseList;
std::mutex itembaseMutex;
void CacheLevels()
{
	for (;;)
	{
		if (!is_valid(LocalPtrs::Gworld)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		uintptr_t ItemLevels = read<uintptr_t>(LocalPtrs::Gworld + offsets::Levels);
		if (!is_valid(ItemLevels)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		std::vector<item> mrxd;

		DWORD levelCount = read<DWORD>(LocalPtrs::Gworld + (offsets::Levels + sizeof(PVOID)));
		for (DWORD i = 0; i < levelCount; ++i)
		{
			uintptr_t ItemLevel = read<uintptr_t>(ItemLevels + (i * sizeof(uintptr_t)));
			if (!is_valid(ItemLevel)) continue;

			DWORD actorCount = read<DWORD>(ItemLevel + (offsets::AActor + sizeof(PVOID)));
			uintptr_t ItemsPawns = read<uintptr_t>(ItemLevel + offsets::AActor);

			if (!is_valid(ItemsPawns) || actorCount == 0) continue;

			for (DWORD j = 0; j < actorCount; ++j)
			{
				uintptr_t CurrentItemPawn = read<uintptr_t>(ItemsPawns + (j * sizeof(uintptr_t)));
				if (!is_valid(CurrentItemPawn)) continue;

				Vector3 ItemPosition = GetLocation(CurrentItemPawn);
				float ItemDist = vCamera.Location.Distance(ItemPosition) / 100;
				int ItemIndex = read<int>(CurrentItemPawn + 0x8);

				auto CurrentItemPawnName = FName::ToString(ItemIndex);

				bool shouldUpdate = false;
				bool bIsPickup = false;

				if (settings::world.uncommon_loot || settings::world.chests) {
					bIsPickup = true;
					shouldUpdate = true;
				}

				if (shouldUpdate) {
					item Item{};
					Item.Actor = CurrentItemPawn;
					Item.Name = CurrentItemPawnName;
					Item.isPickup = bIsPickup;
					Item.distance = ItemDist;

					mrxd.push_back(Item);
				}
			}
		}

		{
			std::scoped_lock lock(itembaseMutex);
			item_pawns = mrxd;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
void WorldLoop(ImDrawList* drawlist)
{
	auto levelListCopy = item_pawns;

	for (auto entity : levelListCopy)
	{
		if (!entity.Actor) continue;

		if ((settings::world.uncommon_loot || settings::world.common_loot ||
			settings::world.rare_loot || settings::world.epic_loot ||
			settings::world.legendary_loot || settings::world.mythic_loot) &&
			(entity.Name.find("FortPickupAthena") != std::string::npos ||
				entity.Name.find("Fort_Pickup_Creative_C") != std::string::npos ||
				entity.Name.find("FortPickup") != std::string::npos))
		{
			if (entity.distance > settings::world.render_distance_loot) continue;

			uintptr_t actor_root_component = read<uintptr_t>(entity.Actor + offsets::RootComponent);
			if (!actor_root_component) continue;

			Vector3 actor_relative_location = read<Vector3>(actor_root_component + offsets::RelativeLocation);
			Vector2 location = ProjectWorldToScreen(actor_relative_location);
			float item_distance = vCamera.Location.Distance(actor_relative_location) * 0.01f;
			if (!is_in_screen(location)) continue;

			uintptr_t definition = read<uintptr_t>(entity.Actor + offsets::PrimaryPickupItemEntry + offsets::ItemDefinition);
			if (!definition) continue;

			EFortRarity tier = read<EFortRarity>(definition + offsets::Rarity);
			uint64_t ItemName = read<uint64_t>(definition + offsets::ItemName);
			uint64_t FData = read<uint64_t>(ItemName + 0x20); //idk
			int FLength = read<int>(ItemName + 0x28); //idk

			if (FLength > 0 && FLength < 50)
			{
				std::unique_ptr<wchar_t[]> WeaponBuffer(new wchar_t[FLength]);
				Driver::ReadPhysicalMemory(PVOID(FData), (PVOID)WeaponBuffer.get(), FLength * sizeof(wchar_t));

				std::wstring wstr_buf(WeaponBuffer.get());
				std::string weapon_name(wstr_buf.begin(), wstr_buf.end());

				std::unordered_map<EFortRarity, bool> loot_settings = {
					{EFortRarity::EFortRarity__Common, settings::world.common_loot},
					{EFortRarity::EFortRarity__Uncommon, settings::world.uncommon_loot},
					{EFortRarity::EFortRarity__Rare, settings::world.rare_loot},
					{EFortRarity::EFortRarity__Epic, settings::world.epic_loot},
					{EFortRarity::EFortRarity__Legendary, settings::world.legendary_loot},
					{EFortRarity::EFortRarity__Mythic, settings::world.mythic_loot},
				};

				if (loot_settings[tier]) {
					char dist[64];
					sprintf_s(dist, "%.fm", item_distance);
					std::string text = weapon_name + " (" + std::string(dist) + ")";
					ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
					ImVec2 text_pos = ImVec2(location.x - text_size.x / 2, location.y - 18);

					ImColor textColor = get_loot_color(tier);
					ImColor outlineColor = ImColor(0, 0, 0, 255);

					if (settings::world.enableOutlinesLoot) {

						draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(text_pos.x - 1, text_pos.y), outlineColor, text.c_str());
						draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(text_pos.x + 1, text_pos.y), outlineColor, text.c_str());
						draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(text_pos.x, text_pos.y - 1), outlineColor, text.c_str());
						draw_text(drawlist, ImGui::GetFont(), 16, ImVec2(text_pos.x, text_pos.y + 1), outlineColor, text.c_str());
					}
					draw_text(drawlist, ImGui::GetFont(), 16, text_pos, textColor, text.c_str());
				}
			}
		}

		if (settings::world.chests && strstr(entity.Name.c_str(), "Tiered_Chest") && entity.distance <= settings::world.render_distance_chest)
		{
			if (!(read<BYTE>(entity.Actor + offsets::bAlreadySearched) >> 2 & 1))
			{
				draw_item(drawlist, "Tiered_Chest", "Chest", ImColor(255, 255, 0, 255), entity.Actor);
			}
		}

		if (settings::world.llamas && strstr(entity.Name.c_str(), "AthenaSupplyDrop_Llama_C") && entity.distance <= settings::world.render_distance_llama)
		{
			if (!(read<BYTE>(entity.Actor + offsets::bAlreadySearched) >> 2 & 1))
			{
				draw_item(drawlist, "AthenaSupplyDrop_Llama_C", "Llama", ImColor(204, 0, 255, 255), entity.Actor);
			}
		}

		if (settings::world.foodbox && strstr(entity.Name.c_str(), "FoodBox_Produce_Athena_C") && entity.distance <= settings::world.render_distance_ammo)
		{
			if (!(read<BYTE>(entity.Actor + offsets::bAlreadySearched) >> 2 & 1))
			{
				draw_item(drawlist, "FoodBox_Produce_Athena_C", "Food Box", ImColor(0, 255, 21, 255), entity.Actor);
			}
		}

		if (settings::world.ammobox && strstr(entity.Name.c_str(), "Tiered_Ammo_Athena_C") && entity.distance <= settings::world.render_distance_ammo)
		{
			if (!(read<BYTE>(entity.Actor + offsets::bAlreadySearched) >> 2 & 1))
			{
				draw_item(drawlist, "Tiered_Ammo_Athena_C", "Ammo Box", ImColor(0, 100, 0, 255), entity.Actor);
			}
		}

		if ((strstr(entity.Name.c_str(), "Valet_BasicSUV_Vehicle_C") ||
			strstr(entity.Name.c_str(), "Valet_SportsCar_Vehicle_C") ||
			strstr(entity.Name.c_str(), "Motorcycle_Sport_Vehicle_C"))
			&& settings::world.vehicle
			&& entity.distance <= settings::world.render_distance_vehicle)
		{
			draw_item(drawlist, entity.Name.c_str(), "Vehicle", ImColor(255, 0, 0, 255), entity.Actor);
		}

		if (((settings::world.spirits && strstr(entity.Name.c_str(), "NPC_Pawn_Irwin_Simple_Sprite_Air_C")) ||
			(settings::world.spirits && strstr(entity.Name.c_str(), "NPC_Pawn_Irwin_Simple_Sprite_Water_C")))
			&& entity.distance <= settings::world.render_distance_spirits)
		{
			const char* itemName = strstr(entity.Name.c_str(), "Air_C") ? "Air Spirit" : "Water Spirit";
			ImColor itemColor = strstr(entity.Name.c_str(), "Air_C") ? ImColor(255, 255, 255, 255) : ImColor(0, 153, 255, 255);

			draw_item(drawlist, entity.Name.c_str(), itemName, itemColor, entity.Actor);
		}
		//ImGui::PopFont();
	}
}
void leveldrawing(ImDrawList* drawlist)
{
	auto levelListCopy = item_pawns;

	for (auto entity : levelListCopy)
	{
		if (entity.Actor)
		{
			if (settings::world.uncommon_loot && strstr(entity.Name.c_str(), ("FortPickupAthena")) or strstr(entity.Name.c_str(), ("Fort_Pickup_Creative_C")) or strstr(entity.Name.c_str(), ("FortPickup")))
			{
				Vector3 Location = GetLocation(entity.Actor);

				Vector2 ChestPosition = ProjectWorldToScreen(Location);

				if (is_in_screen(ChestPosition))
				{
					std::string wtf2 = " [" + std::to_string((int)entity.distance) + ("m]");
					ImVec2 text_size = ImGui::CalcTextSize(wtf2.c_str());
					DrawString(drawlist, 13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, ImVec4(0.0f, 1.0f, 1.0f, 1.0f), false, false, wtf2.c_str());
				}
			}

			if (settings::world.chests && strstr(entity.Name.c_str(), ("Tiered_Chest")))
			{
				Vector3 Location = GetLocation(entity.Actor);
				Vector2 Screen = ProjectWorldToScreen(Location);

				if (is_in_screen(Screen))
				{
					std::string BuiltString = "Chest [" + std::to_string((int)entity.distance) + "]";
					ImVec2 text_size = ImGui::CalcTextSize(BuiltString.c_str());

					DrawString(drawlist, 13, Screen.x - (text_size.x / 2), Screen.y - 18, ImColor(255, 255, 0), false, false, BuiltString.c_str());
				}
			}
		}
	}
}