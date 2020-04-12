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

#include "Window.h"

using std::string;
using panorama::Window;

Window::Window(GLFWwindow *pGlfwWindow, std::string sTitle, int w, int h) :
        m_pRawWindow{pGlfwWindow}, m_sTitle{sTitle}, m_iWidth{w}, m_iHeight{h},
        m_bMaximized{false},
        m_eWindowFlags{ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse } {
    // If the title is empty, set it to something to avoid an assertion.
    if (m_sTitle.empty())
        m_sTitle = " ";
}

Window::~Window() { }

void Window::setMaximized(bool bMaximized) {
    m_bMaximized = bMaximized;
}

void Window::setWindowFlags(ImGuiWindowFlags eWinFlags) {
    m_eWindowFlags = eWinFlags;
}

int Window::width() const {
    return m_iWidth;
}

int Window::height() const {
    return m_iHeight;
}

std::string Window::title() const {
    return m_sTitle;
}

void panorama::Window::render() {
    bool bOpen = false;

    // Setup window before it's drawn
    if (m_bMaximized) {
        // Get main window size
        glfwGetFramebufferSize(m_pRawWindow, &m_iWidth, &m_iHeight);

        // We need to reserve space for the main menu. So we draw an empty one,
        // and get the size. The MainWindow event loop will draw the actual menu.
        float fMenuHeight;

        if (ImGui::BeginMainMenuBar()) {
            fMenuHeight = ImGui::GetWindowSize().y;
            ImGui::EndMainMenuBar();
        }
        ImGui::SetNextWindowSize(ImVec2(m_iWidth, m_iHeight - fMenuHeight), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, fMenuHeight), ImGuiCond_Always);

        m_eWindowFlags |= ImGuiWindowFlags_NoResize;
    }

    // Begin drawing the window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin(m_sTitle.c_str(), &bOpen, m_eWindowFlags);

    // Overridable UI render function
    renderUI();

    ImGui::End();
    ImGui::PopStyleVar();
}

void Window::close() {
    glfwSetWindowShouldClose(m_pRawWindow, static_cast<int>(true));
}
