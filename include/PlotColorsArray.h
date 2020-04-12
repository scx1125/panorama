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

#ifndef PANORAMA_PLOTCOLORSARRAY_H
#define PANORAMA_PLOTCOLORSARRAY_H

#include <random>
#include <vector>

#include "imgui.h"

namespace panorama {
    namespace guiutils {

        class PlotColorsArray {
        public:
            // Cnstr.
            explicit PlotColorsArray(int nColors);

            // Dstr.
            ~PlotColorsArray();

            // Getters
            inline ImU32 getColor(int nIndex) { return m_vColors.at(nIndex); }

        private:
            // Properties
            std::vector<ImU32> m_vColors;

            // Constants
            const float COLOR_DIST_MIN = 0.3f;
            const float COLOR_DIST_MAX = 1.0f;
        };

    }
}
#endif //PANORAMA_PLOTCOLORSARRAY_H
