#pragma once
#include <string>
inline ImFont* icon;

enum BoxType
{
    CORNER = 0,
    OUTLINE,
    FILLED
};

namespace settings
{

    inline bool use_controller = false;


    struct Colors
    {
        ImColor visible = ImColor(0, 255, 0, 255); // green
        ImColor notVisible = ImColor(255, 0, 0, 255);    // red
    };

    struct ESP
    {
        bool box = true;
        bool snapline = false;
        bool distance = false;
        bool skeletonoutlined = false;
        int skeleton_thickness = 3;
        bool skeletonesp = false;
        bool headesp = true;
        bool rank = false;
        bool outlinetext = false; // outlined text option
        bool username = false;
        bool platform = false;
        bool weaponesp = false;
        bool RankImages = false;
        bool PlatformIcons = false;
        bool outline = false;
        int espdis = 100;
        int textsize = 15;
        BoxType boxType = CORNER; // default box type
        bool boxOutlined = false;   // toggle black outline
    };

    struct World
    {
        bool enableworld = true;
        bool uncommon_loot = true;
        bool common_loot = true;
        bool llamas = true;
        bool rare_loot = true;
        bool foodbox = true;
        bool epic_loot = true;
        bool legendary_loot = true;
        bool mythic_loot = true;
        bool chests = true;
        bool ammobox = true;
        bool vehicle = true;
        bool spirits = true;
        int render_distance_loot = 350;
        int render_distance_ammo = 350;
        int render_distance_vehicle = 350;
        int render_distance_spirits = 350;
        int render_distance_llama = 350;
        int render_distance_chest = 350;
        bool enableOutlinesContainers = true;
        bool enableOutlinesLoot = true;

    };

    struct Aimbot
    {
        bool enabled = true;
        int smoothsize = 95;
        int targetPriority = 0;
        int fovsize = 50;
        int Hitbox = 0;
        bool ignore_team = true; // <<< add this

        int aimkey = VK_RBUTTON;
        bool mouse = true;
        bool prediction = false;
        bool drawfov = true;
        bool vischeck = false;
    };
    struct Exploits
    {
        bool silentaim = false;
        int silentTargetPriority;
        int fovsize = 50;
        bool magic = false;
        bool invisible = false;
        bool flying = false;
        bool Enable = true;
        bool tinyplayers = false;
        bool fovchanger = false;
        int fovchanger_value = 120;
        int Playersize = 1;
        bool norecoil = false;
        bool doublepump = false;
        bool btrack = false;
        bool minigun = false;
        bool tpose = false;
        bool flyy = false;
        bool firstperson = false;
        bool instaReboot = false;
        bool instantrevive = false;
        bool carfly = false;
        bool tpenemy = false;
        bool speedhack = false;
        bool Editdistance = false;
        bool FreeCam = false;
        bool AmmoCountChanger = false;
        bool instaReloadd = false;
        int AmmoCountChangerValue = 1000;

         float flySpeed = 100.0f; // speed multiplier




    };
    struct UI
    {
        bool menu = false;
        bool vsync = true;
    };
    struct TRIGGERBOT
    {
         bool enable_triggerbot = false;
         float delay = 100.0f;
         bool visible_check = true;
         int trigger_key = VK_SHIFT;
         bool team_check = true;
        bool shotgun_only = true;
    };
    inline Colors colors{};
    inline ESP esp{};
    inline TRIGGERBOT triggerbot{};

    inline Aimbot aimbot{};
    inline World world{};
    inline Exploits exploits{};

    inline UI ui{};

    inline void reset()
    {
        colors = Colors{};
        esp = ESP{};
        ui = UI{};
    }

    inline std::string to_string()
    {
        return "[Settings]\n"
            " Box: " + std::string(esp.box ? "On" : "Off") +
            " | Snapline: " + (esp.snapline ? "On" : "Off") +
            " | Distance: " + (esp.distance ? "On" : "Off") +
            " | VSync: " + (ui.vsync ? "On" : "Off");
    }
}
