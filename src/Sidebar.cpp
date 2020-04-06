/*
 *  Panorama -  A simple system monitor for Linux, written using dear ImGui.
 *  Copyright (C) 2018 - 2020 Ronen Lapushner
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "Sidebar.h"

panorama::Sidebar::Sidebar(float fWidth)
        : m_fWidth{fWidth},
          m_eCurrentlyVisiblePane{PaneType::PANETYPE_CPU} { }
panorama::Sidebar::~Sidebar() { }

void panorama::Sidebar::renderUI() {
    const int SIDEBAR_BUTTON_PADDING = 30;

    // Determine scaling
    if (panorama::guiutils::getScalingFactor() > 1.0f)
        m_fWidth = ImGui::CalcTextSize("PROCESSES").x + SIDEBAR_BUTTON_PADDING;

    const ImVec2 v2ButtonSize = ImVec2(m_fWidth, m_fWidth / 2);

    ImGui::BeginChild("##sidebar");

    // CPU Pane button
    if (ImGui::Selectable(ICON_FA_MICROCHIP " CPU",
                          (m_eCurrentlyVisiblePane == PaneType::PANETYPE_CPU), 0, v2ButtonSize))
        m_eCurrentlyVisiblePane = PaneType::PANETYPE_CPU;

    // Processes Pane button
    if (ImGui::Selectable(ICON_FA_WINDOW_RESTORE " PROCESSES",
                          (m_eCurrentlyVisiblePane == PaneType::PANETYPE_PROCESSES), 0, v2ButtonSize))
        m_eCurrentlyVisiblePane = PaneType::PANETYPE_PROCESSES;

    // Resources Pane button
    if (ImGui::Selectable(ICON_FA_MEMORY " MEMORY",
                          (m_eCurrentlyVisiblePane == PaneType::PANETYPE_MEMORY), 0, v2ButtonSize))
        m_eCurrentlyVisiblePane = PaneType::PANETYPE_MEMORY;

    ImGui::EndChild();
}
