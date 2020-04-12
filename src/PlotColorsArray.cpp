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

#include "PlotColorsArray.h"

using panorama::guiutils::PlotColorsArray;

PlotColorsArray::PlotColorsArray(int nColors) {
    // Initialize random engine
    std::mt19937 engine{std::random_device{}()};
    std::uniform_real_distribution<float> dist(COLOR_DIST_MIN, COLOR_DIST_MAX);

    // Initialize colors
    for (int i = 0; i < nColors; i++) {
        ImVec4 colorVec = ImVec4(dist(engine), dist(engine), dist(engine), 1.0f);
        m_vColors.push_back(ImGui::ColorConvertFloat4ToU32(colorVec));
    }
}

PlotColorsArray::~PlotColorsArray() { }

