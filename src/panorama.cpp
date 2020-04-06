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

#include "Globals.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include <iostream>
#include <string>

#include <unistd.h>
#include <wordexp.h>

#include "MainWindow.h"
#include "IconsFontAwesome5.h"

#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720

// Global variables
GLFWwindow *g_pGlfwWindow;
float g_fFontScaling = 1.0f;

// TODO: Change this callback for something a bit more meaningful
static void glfw_error_callback(int error, const char* description) {
    std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void loadFonts(ImGuiIO &io) {
    // Load default font
    io.Fonts->AddFontDefault();

    // Check if the regular font fonts exists.
    std::string sFontPath = panorama::utils::getCurrentProcessDir() + "/DroidSans.ttf";
    if (access(sFontPath.c_str(), F_OK) == 0) {
        io.Fonts->AddFontFromFileTTF(sFontPath.c_str(), PANORAMA_FONT_SIZE_REGULAR * g_fFontScaling);

        // Load fontawesome into the regular font
        {
            std::string sFontAwesomePath = panorama::utils::getCurrentProcessDir() + "/fa-solid-900.ttf";
            if (access(sFontAwesomePath.c_str(), F_OK) == 0) {
                static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
                ImFontConfig icons_config;
                icons_config.MergeMode = true;
                icons_config.PixelSnapH = true;

                io.Fonts->AddFontFromFileTTF(sFontAwesomePath.c_str(),
                                             (PANORAMA_FONT_SIZE_REGULAR - 2) * g_fFontScaling,
                                             &icons_config, icons_ranges);
            }
            else
                std::cerr << "Error: Could not find font " << sFontAwesomePath <<
                          ", no icons will be displayed!" << std::endl;
        }

        io.Fonts->AddFontFromFileTTF(sFontPath.c_str(), PANORAMA_FONT_SIZE_TITLE * g_fFontScaling);
        io.Fonts->AddFontFromFileTTF(sFontPath.c_str(), PANORAMA_FONT_SIZE_EXTRALARGE * g_fFontScaling);
    }
    else {
        std::cerr << "Error: Could not find font " << sFontPath << ", using fallback!" << std::endl;

        // Fallback to default font
        // TODO: Add this font but with different sizes. Should still look decent if font is missing.
        const int FONT_COUNT = 3;
        for (int i = 0; i < FONT_COUNT; i++)
            io.Fonts->AddFontDefault();
    }
}

int initApplication() {
    // Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        // Error callback handles error output
        return -1;
    }

    // If we have the PANORAMA_SCALING environment variable, we're gonna scale all fonts by it.
    // A bit of a double check here, but we need this to verify the scaling, since the utility
    // function does not check for errors.
    const char *cstrScalingModifier;
    if ((cstrScalingModifier = std::getenv("PANORAMA_SCALING")) != nullptr) {
        try {
            g_fFontScaling = panorama::guiutils::getScalingFactor();
        }
        catch (const std::invalid_argument &ex) {
            std::cerr << "Error getting scale from PANORAMA_SCALING, using 1 as default." << std::endl;
        }
    }

    // Create title for the window
    std::string sTitle = "Panorama v." PANORAMA_VERSION;
    if (panorama::utils::isRunningInPrivilagedMode())
        sTitle += " (Privileged)";

    // Setup a low-level window
    g_pGlfwWindow = glfwCreateWindow(
            MAIN_WINDOW_WIDTH * g_fFontScaling,
            MAIN_WINDOW_HEIGHT * g_fFontScaling,
            sTitle.c_str(),
            NULL, NULL);
    if (g_pGlfwWindow == nullptr) {
        // Error callback handles error output
        return -1;
    }

    glfwMakeContextCurrent(g_pGlfwWindow);
    glfwSwapInterval(1); // Enable vsync


    // Setup ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup style
    ImGui::StyleColorsLight();

    // Initialize ImGui
    ImGui_ImplGlfw_InitForOpenGL(g_pGlfwWindow, true);
    ImGui_ImplOpenGL2_Init();

    // Enable keyboard navigation
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Load fonts
    loadFonts(io);

    return 0;
}

void destroyApplication() {
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(g_pGlfwWindow);
    glfwTerminate();
}

int main(int argc, char **argv) {
    // Init application
    int iInitResult = initApplication();
    if (iInitResult != 0)
        return iInitResult;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Init main window
    panorama::MainWindow wndMain(g_pGlfwWindow, "", MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    wndMain.setWindowFlags(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
    wndMain.setMaximized(true);

    // Main loop
    bool done = false;
    while (!done && !glfwWindowShouldClose(g_pGlfwWindow)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render main window
        wndMain.render();

        // Rendering
        ImGui::Render();
        int display_w, display_h;

        glfwGetFramebufferSize(g_pGlfwWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int) ImGui::GetIO().DisplaySize.x, (int) ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Legacy OpenGL 2 fixes
        /*
        GLint last_program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        glUseProgram(0);
         */
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        //glUseProgram(last_program);

        glfwMakeContextCurrent(g_pGlfwWindow);
        glfwSwapBuffers(g_pGlfwWindow);
    }

    destroyApplication();

    return 0;
}
