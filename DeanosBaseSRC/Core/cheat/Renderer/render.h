#pragma once
#include "render.h"
#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include "../Utilities/util.h"
#include "../Visuals/esp.h"
#include "ImGui/rank.h"
#include "ImGui/imgui_internal.h"
#define _CRT_SECURE_NO_WARNINGS




namespace resources
{
    struct D3DResources
    {
        HWND hwnd{ nullptr };
        ID3D11Device* device{ nullptr };
        ID3D11DeviceContext* device_context{ nullptr };
        ID3D11RenderTargetView* render_target_view{ nullptr };
        IDXGISwapChain* swap_chain{ nullptr };
    };

    inline D3DResources gfx{};
}

ID3D11ShaderResourceView* LoadTextureFromMemory(const unsigned char* data, size_t data_size)
{
    int width, height, channels;
    unsigned char* image_data = stbi_load_from_memory(data, data_size, &width, &height, &channels, 4);
    if (!image_data)
        return nullptr;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = width * 4;

    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = resources::gfx.device->CreateTexture2D(&desc, &subResource, &texture);
    stbi_image_free(image_data);

    if (FAILED(hr))
        return nullptr;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    ID3D11ShaderResourceView* srv = nullptr;
    hr = resources::gfx.device->CreateShaderResourceView(texture, &srvDesc, &srv);
    texture->Release();

    return SUCCEEDED(hr) ? srv : nullptr;
}


std::unordered_map<std::string, ID3D11ShaderResourceView*> platform_textures;

void InitializePlatformTextures()
{
    static bool initialized = false;
    if (initialized) return;

    platform_textures["xbox"] = LoadTextureFromMemory(xbox_img, sizeof(xbox_img));
    platform_textures["playstation"] = LoadTextureFromMemory(playstation_img, sizeof(playstation_img));
    platform_textures["nintendo"] = LoadTextureFromMemory(switch_img, sizeof(switch_img));
    platform_textures["windows"] = LoadTextureFromMemory(win_img, sizeof(win_img));
    platform_textures["android"] = LoadTextureFromMemory(android, sizeof(android));
    platform_textures["ios"] = LoadTextureFromMemory(_ios, sizeof(_ios));
    platform_textures["bot"] = LoadTextureFromMemory(bot_iocn, sizeof(bot_iocn));

    initialized = true;
}



std::string get_player_platform(uintptr_t player_state, ImColor& resultColor)
{
    std::string result;

    __int64 FString = read<__int64>(player_state + offsets::Platform);
    uintptr_t test_platform = read<uintptr_t>(player_state + offsets::Platform);

    int length = static_cast<int>(read<__int64>(FString + 16));
    if (length == 0) {
        resultColor = ImColor(255, 255, 255);
        return "bot";
    }

    wchar_t platform[64];
    Driver::ReadPhysicalMemory((void*)test_platform, platform, sizeof(platform));

    std::wstring platform_wstr(platform);
    std::string platform_str(platform_wstr.begin(), platform_wstr.end());

    resultColor = ImColor(255, 255, 255);

    if (platform_str == "XBL" || platform_str == "XSX") {
        result = "xbox";
        resultColor = ImColor(0, 255, 0);
    }
    else if (platform_str == "PSN" || platform_str == "PS5") {
        result = "playstation";
        resultColor = ImColor(0, 0, 255);
    }
    else if (platform_str == "SWT") {
        result = "nintendo";
        resultColor = ImColor(255, 0, 0);
    }
    else if (platform_str == "WIN") {
        result = "windows";
        resultColor = ImColor(255, 255, 255);
    }
    else if (platform_str == "MOBIL-A") {
        result = "android";
        resultColor = ImColor(0, 255, 0);
    }
    else if (platform_str == "MOBIL-I") {
        result = "ios";
        resultColor = ImColor(0, 122, 255);
    }
    else {
        result = "bot";
        resultColor = ImColor(255, 255, 255);
    }

    return result;
}
std::string getRank(int tier) {
    switch (tier) {
    case 0:  return "unranked";
    case 1:  return "bronze1";
    case 2:  return "bronze2";
    case 3:  return "silver1";
    case 4:  return "silver2";
    case 5:  return "silver3";
    case 6:  return "gold1";
    case 7:  return "gold2";
    case 8:  return "gold3";
    case 9:  return "platinum1";
    case 10: return "platinum2";
    case 11: return "platinum3";
    case 12: return "diamond1";
    case 13: return "diamond2";
    case 14: return "diamond3";
    case 15: return "elite";
    case 16: return "champion";
    case 17: return "unreal";
    default: return "unranked";
    }
}

ImVec4 getRankColor(int tier) {
    static const ImVec4 rank_colors[] = {
        {1.0f, 1.0f, 1.0f, 1.0f}, {0.8f, 0.5f, 0.2f, 1.0f}, {0.8f, 0.5f, 0.2f, 1.0f},
        {0.8f, 0.8f, 0.8f, 1.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {0.8f, 0.8f, 0.8f, 1.0f},
        {1.0f, 0.843f, 0.0f, 1.0f}, {1.0f, 0.843f, 0.0f, 1.0f}, {1.0f, 0.843f, 0.0f, 1.0f},
        {0.4f, 0.6f, 1.0f, 1.0f}, {0.4f, 0.6f, 1.0f, 1.0f}, {0.4f, 0.6f, 1.0f, 1.0f},
        {0.7f, 0.4f, 1.0f, 1.0f}, {0.7f, 0.4f, 1.0f, 1.0f}, {0.7f, 0.4f, 1.0f, 1.0f},
        {0.9f, 0.85f, 0.6f, 1.0f}, {1.0f, 0.6f, 0.0f, 1.0f}, {0.6f, 0.0f, 0.6f, 1.0f}
    };

    return (tier >= 0 && tier < 18) ? rank_colors[tier] : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void draw_player_rank_icon(Vector2 location, int tier)
{
    std::string rank_id = getRank(tier);

    if (platform_textures.find(rank_id) == platform_textures.end())
        return;

    ID3D11ShaderResourceView* texture = platform_textures[rank_id];
    if (!texture)
        return;

    float icon_size = 24.0f;

    ImVec2 icon_pos(location.x - icon_size / 2, location.y);

    ImGui::GetForegroundDrawList()->AddImage(
        (ImTextureID)texture,
        icon_pos,
        ImVec2(icon_pos.x + icon_size, icon_pos.y + icon_size),
        ImVec2(0, 0),
        ImVec2(1, 1),
        IM_COL32_WHITE
    );
}

void draw_player_platform(Vector2 boxTopCenter, std::string platform_id, const ImColor color)
{
    if (platform_textures.find(platform_id) == platform_textures.end())
        return;

    ID3D11ShaderResourceView* texture = platform_textures[platform_id];
    if (!texture)
        return;

    float icon_size = 24.0f;
    ImVec2 icon_pos(boxTopCenter.x - icon_size / 2, boxTopCenter.y - icon_size - 5);

    ImGui::GetForegroundDrawList()->AddImage(
        (ImTextureID)texture,
        icon_pos,
        ImVec2(icon_pos.x + icon_size, icon_pos.y + icon_size),
        ImVec2(0, 0),
        ImVec2(1, 1),
        ImGui::ColorConvertFloat4ToU32(color.Value)
    );
}


void InitializeRankTextures()
{
    // Assuming you have rank icon unsigned char arrays in rankicons.hpp
    platform_textures["unranked"] = LoadTextureFromMemory(unranked, sizeof(unranked));
    platform_textures["bronze1"] = LoadTextureFromMemory(bronze1, sizeof(bronze1));
    platform_textures["bronze2"] = LoadTextureFromMemory(bronze2, sizeof(bronze2));
    platform_textures["bronze3"] = LoadTextureFromMemory(bronze3, sizeof(bronze3));
    platform_textures["silver1"] = LoadTextureFromMemory(silver1, sizeof(silver1));
    platform_textures["silver2"] = LoadTextureFromMemory(silver2, sizeof(silver2));
    platform_textures["silver3"] = LoadTextureFromMemory(silver3, sizeof(silver3));
    platform_textures["gold1"] = LoadTextureFromMemory(gold1, sizeof(gold1));
    platform_textures["gold2"] = LoadTextureFromMemory(gold2, sizeof(gold2));
    platform_textures["gold3"] = LoadTextureFromMemory(gold3, sizeof(gold3));
    platform_textures["platinum1"] = LoadTextureFromMemory(platinum1, sizeof(platinum1));
    platform_textures["platinum2"] = LoadTextureFromMemory(platinum2, sizeof(platinum2));
    platform_textures["platinum3"] = LoadTextureFromMemory(platinum3, sizeof(platinum3));
    platform_textures["diamond1"] = LoadTextureFromMemory(diamond1, sizeof(diamond1));
    platform_textures["diamond2"] = LoadTextureFromMemory(diamond2, sizeof(diamond2));
    platform_textures["diamond3"] = LoadTextureFromMemory(diamond3, sizeof(diamond3));
    platform_textures["elite"] = LoadTextureFromMemory(elite, sizeof(elite));
    platform_textures["champion"] = LoadTextureFromMemory(champion, sizeof(champion));
    platform_textures["unreal"] = LoadTextureFromMemory(unreal, sizeof(unreal));
}

std::string platform(uint64_t PlayerState)
{
    DWORD_PTR test_platform = read<DWORD_PTR>(PlayerState + 0x438); //0x438 FortniteGame.FortPlayerState.Platform -> 0x408
    if (!test_platform) return std::string("AI");

    wchar_t platform[64];
    Driver::ReadPhysicalMemory(reinterpret_cast<PVOID>(test_platform), platform, sizeof(platform));

    std::wstring platform_wstr(platform);
    std::string platform_str(platform_wstr.begin(), platform_wstr.end());
    return platform_str;
};


namespace overlay
{

    auto CreateShittyOverlay() -> bool
    {
        resources::gfx.hwnd = FindWindowA(("Chrome_WidgetWin_1"), ("Discord Overlay"));
        if (!resources::gfx.hwnd)
        {
            MessageBoxA(0, ("Couldn't find overlay."), 0, 0);
            return false;
        }

        int WindowWidth = GetSystemMetrics(SM_CXSCREEN);
        int WindowHeight = GetSystemMetrics(SM_CYSCREEN);

        SetMenu(resources::gfx.hwnd, NULL);

        SetWindowPos(resources::gfx.hwnd, NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);

        ShowWindow(resources::gfx.hwnd, SW_SHOW);
        SetWindowLongA(resources::gfx.hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
        SetWindowLongA(resources::gfx.hwnd, GWL_STYLE, WS_VISIBLE);
        SetWindowLongA(resources::gfx.hwnd,
            -20,
            static_cast<LONG_PTR>(
                static_cast<int>(GetWindowLongA(resources::gfx.hwnd, -20)) | 0x20
                )
        );

        SetWindowPos(resources::gfx.hwnd, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, SWP_SHOWWINDOW);

        MARGINS Margin = { -1, -1, -1, -1 };
        DwmExtendFrameIntoClientArea(resources::gfx.hwnd, &Margin);
        SetLayeredWindowAttributes(resources::gfx.hwnd, NULL, 0xFF, 0x02);

        ShowWindow(resources::gfx.hwnd, SW_SHOW);

        UpdateWindow(resources::gfx.hwnd);

        return true;
    }
}



namespace d3d
{
    inline void ApplyCustomStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.11f, 0.15f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.25f, 0.60f);
        colors[ImGuiCol_Text] = ImVec4(0.90f, 0.92f, 0.95f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.18f, 0.25f, 1.00f);

        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.35f, 0.60f, 0.70f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.45f, 0.80f, 0.90f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.30f, 0.50f, 1.00f);

        colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.35f, 0.60f, 0.70f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.45f, 0.80f, 0.80f);

        colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.55f, 0.90f, 0.80f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.65f, 1.00f, 0.90f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.35f, 0.60f, 0.95f, 1.00f);

        colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.18f, 0.25f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.55f, 0.90f, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.35f, 0.60f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.28f, 0.45f, 1.00f);

        style.WindowPadding = ImVec2(15, 15);
        style.FramePadding = ImVec2(6, 4);
        style.ItemSpacing = ImVec2(10, 6);
        style.WindowRounding = 8.0f;
        style.FrameRounding = 6.0f;
        style.GrabRounding = 6.0f;
        style.ScrollbarRounding = 9.0f;
        style.ChildRounding = 8.0f;
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        ImGuiIO& io = ImGui::GetIO();

        io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/segoeuib.ttf", 18.0f);
        ESPFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 15.0f, nullptr, io.Fonts->GetGlyphRangesDefault());

    }

    inline bool Setup()
    {
        DXGI_SWAP_CHAIN_DESC scd{};
        scd.BufferCount = 2;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferDesc.RefreshRate.Numerator = 60;
        scd.BufferDesc.RefreshRate.Denominator = 1;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = resources::gfx.hwnd;
        scd.SampleDesc.Count = 1;
        scd.SampleDesc.Quality = 0;
        scd.Windowed = TRUE;
        scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
        D3D_FEATURE_LEVEL selected_level;

        if (FAILED(D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            feature_levels,
            _countof(feature_levels),
            D3D11_SDK_VERSION,
            &scd,
            &resources::gfx.swap_chain,
            &resources::gfx.device,
            &selected_level,
            &resources::gfx.device_context)))
        {
            return false;
        }

        ID3D11Texture2D* back_buffer = nullptr;
        if (FAILED(resources::gfx.swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer))) || !back_buffer)
            return false;

        if (FAILED(resources::gfx.device->CreateRenderTargetView(back_buffer, nullptr, &resources::gfx.render_target_view)))
            return false;

        back_buffer->Release();

        ImGui::CreateContext();
        ApplyCustomStyle();

        ImGui_ImplWin32_Init(resources::gfx.hwnd);
        ImGui_ImplDX11_Init(resources::gfx.device, resources::gfx.device_context);

        resources::gfx.device->Release();
        return true;
    }
}

namespace menu
{
    inline void Render()
    {



        const DWORD color_picker_flags = ImGuiColorEditFlags_NoSidePreview
            | ImGuiColorEditFlags_AlphaBar
            | ImGuiColorEditFlags_NoInputs
            | ImGuiColorEditFlags_AlphaPreview;

        ImGui::SetNextWindowSize({ 700.f, 500.f }, ImGuiCond_FirstUseEver);
        ImGui::Begin("Deano Overlay Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

        if (ImGui::BeginTabBar("##tabs"))
        {
            // Aimbot Tab
            if (ImGui::BeginTabItem("Aimbot"))
            {
                ImGui::Checkbox("Enable Aimbot", &settings::aimbot.enabled);
                ImGui::SliderInt("Smoothness", &settings::aimbot.smoothsize, 1, 100);
                ImGui::Checkbox("Draw Fov", &settings::aimbot.drawfov);
                ImGui::SliderInt("FOV Size", &settings::aimbot.fovsize, 1, 500);
                ImGui::Combo("Target Priority", &settings::aimbot.targetPriority, "Closest Distance\0Closest Crosshair\0\0");
                ImGui::Combo("Hitbox", &settings::aimbot.Hitbox, "Head\0Chest\0Body\0Legs\0Random\0\0");
                ImGui::Checkbox("Prediction", &settings::aimbot.prediction);
                ImGui::Checkbox("Visibility Check", &settings::aimbot.vischeck);
                ImGui::EndTabItem();
            }

            // ESP Tab
            if (ImGui::BeginTabItem("ESP"))
            {
                ImGui::Checkbox("Box", &settings::esp.box);
                ImGui::Checkbox("Skeleton ESP", &settings::esp.skeletonesp);
                ImGui::Checkbox("Snapline", &settings::esp.snapline);
                ImGui::Checkbox("Distance ESP", &settings::esp.distance);
                ImGui::Checkbox("Rank ESP", &settings::esp.rank);
                ImGui::Checkbox("Username ESP", &settings::esp.username);
                ImGui::Checkbox("Platform ESP", &settings::esp.platform);
                ImGui::Checkbox("Weapon ESP", &settings::esp.weaponesp);

                ImGui::Separator();
                const char* boxOptions[] = { "Corner Box", "Full Box", "Filled Box" };
                int currentBoxType = static_cast<int>(settings::esp.boxType);
                ImGui::Combo("Box Type", &currentBoxType, boxOptions, IM_ARRAYSIZE(boxOptions));
                settings::esp.boxType = static_cast<BoxType>(currentBoxType);

                ImGui::Separator();
                ImGui::Text("ESP Colors");
                ImGui::ColorEdit4("Visible", reinterpret_cast<float*>(&settings::colors.visible), color_picker_flags);
                ImGui::ColorEdit4("Not Visible", reinterpret_cast<float*>(&settings::colors.notVisible), color_picker_flags);
                ImGui::SliderInt("Distance##ESP", &settings::esp.espdis, 50, 500);
                ImGui::EndTabItem();
            }


            if (ImGui::BeginTabItem("World"))
            {

                ImGui::Checkbox("Enable WorldEsp", &settings::world.enableworld);
                if (settings::world.enableworld)
                {
                    //ImGui::SliderInt("World Distance", &settings::world.maxRenderDistance, 50, 200);

                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Misc"))
            {
                ImGui::Checkbox("VSync", &settings::ui.vsync);
                ImGui::Checkbox("Text Outlined", &settings::esp.outlinetext);
                ImGui::Checkbox("Outlined Skeleton", &settings::esp.skeletonoutlined);
                ImGui::SliderInt("Skeleton Thickness", &settings::esp.skeleton_thickness, 1, 5);
                ImGui::Checkbox("Outlined Box", &settings::esp.boxOutlined);


                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}


namespace core
{
    inline void Run()
    {
        constexpr float clear_color[4] = { 0.f, 0.f, 0.f, 0.f };
        MSG msg{};

        static bool threads_started = false;
        if (!threads_started) {
            std::thread([]() { CacheLevels(); }).detach();
            threads_started = true;
        }

        while (msg.message != WM_QUIT)
        {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            auto& io = ImGui::GetIO();
            io.DeltaTime = 1.0f / 60.0f;

            if (GetAsyncKeyState(VK_INSERT) & 1)
                settings::ui.menu = !settings::ui.menu;

            if (settings::ui.menu)
            {
                POINT cursor{};
                GetCursorPos(&cursor);
                io.MousePos = ImVec2(static_cast<float>(cursor.x), static_cast<float>(cursor.y));
                io.MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
            }

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ActorLoop();
            WorldLoop(ImGui::GetBackgroundDrawList());

            if (settings::ui.menu)
                menu::Render();

            ImGui::Render();

            resources::gfx.device_context->OMSetRenderTargets(1, &resources::gfx.render_target_view, nullptr);
            resources::gfx.device_context->ClearRenderTargetView(resources::gfx.render_target_view, clear_color);

            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            resources::gfx.swap_chain->Present(settings::ui.vsync, 0);
        }

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
}


inline void setup()
{
    overlay::CreateShittyOverlay();
    d3d::Setup();
    core::Run();


}