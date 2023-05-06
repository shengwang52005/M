#pragma once

#include <Windows.h>

#include "../ImGui/ImGui/imgui_impl_dx11.h"
#include "../ImGui/ImGui/imgui.h"
#include "../ImGui/ImGui/imgui_impl_win32.h"
#include "GuiDefinitions.h"
#include "MainGUI.h"

#include "../ImGui/ImGuiNotify/tahoma.h"
#include "../ImGui/ImGuiNotify/fa_solid_900.h"
#include "../ImGui/ImGuiNotify/font_awesome_5.h"
bool g_ShowMenu = true;
void MergeIconsWithLatestFont(float font_size, bool FontDataOwnedByAtlas = false) {
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.FontDataOwnedByAtlas = FontDataOwnedByAtlas;

	ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)fa_solid_900, sizeof(fa_solid_900), font_size, &icons_config, icons_ranges);
}

namespace gui {
    void InitImGui(HWND window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(pDevice, pContext);
        ImGui::GetIO().ImeWindowHandle = window;

        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);
        //init notify
        MergeIconsWithLatestFont(16.f, false);
    }

    void Render() {
        ImGui_ImplWin32_NewFrame();
        ImGui_ImplDX11_NewFrame();

        ImGui::NewFrame();

        if (g_ShowMenu) {
            bool bShow = true;
            gui::FrameLoadGui();
        }

        //ImGuiIO& io = ImGui::GetIO();
        if(ImGui::IsKeyPressed(ImGuiKey_F12, false))
            g_ShowMenu = !g_ShowMenu;
        
        ImGui::Render();
    }
}