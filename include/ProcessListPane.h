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

#ifndef PANORAMA_PROCESSLISTPANE_H
#define PANORAMA_PROCESSLISTPANE_H

#include <array>

#include "imgui.h"

#include "MemoryUnits.h"
#include "ProcessList.h"
#include "ProcessUtils.h"

#define PANORAMA_FILTER_BUFF_LEN 512

namespace panorama {

    class ProcessListPane {
    public:
        // Cnstr.
        ProcessListPane();

        // Dstr.
        ~ProcessListPane();

        // Methods
        void renderUI();

        // Getters
        inline ProcessList &processList() { return m_oProcessList; }

    private:
        // Properties
        ProcessList m_oProcessList;
        MeasurementUnit m_eUnit;
        MeasurementScale m_eUnitScale;
        std::array<char, PANORAMA_FILTER_BUFF_LEN> m_arrFilterBuffer;
        struct ImGuiTextFilter m_stTextFilter;
        PANORAMA_PROCESSID_TYPE m_nCurrentlySelectedProcess;
        int m_nCurrentlySelectedProcessPrio;
        int m_nCurrentlyVisibleProcesses;
    };

}

#endif //PANORAMA_PROCESSLISTPANE_H
