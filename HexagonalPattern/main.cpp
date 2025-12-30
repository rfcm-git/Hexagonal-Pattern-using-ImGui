#include "Window.h"
#include "hex_pattern_generator.h"
#include "Declarations.h"
#include <vector>

namespace {
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse;
}
void CreateBitmapImage(BitmapImageData& bmpImgData, const ImVec4& backgroundColor);
  
int main() {
    Window window;
    if (!window.Init())
        return -1;

    hex_pattern_generator hexGen;
    int selectMode = 0;
    while (!glfwWindowShouldClose(window.window)) {

        // Start new frame
        window.BeginFrame();

        // Update framebuffer size (for window resizing)
        glfwGetFramebufferSize(window.window, &window.m_windowWidth, &window.m_windowHeight);

        // Fullscreen ImGui window
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)window.m_windowWidth, (float)window.m_windowHeight));
        ImGui::Begin("Hexagonal Pattern", nullptr, flags);

        // -----------------------------
        //  LEFT SIDE: Settings Panel
        // -----------------------------
        float leftPanelWidth = 350.0f;  // You can adjust this width
        ImGui::BeginChild("LeftPanel", ImVec2(leftPanelWidth, 0), true);

            ImGui::Text("Settings");
            ImGui::Separator();
            
			ImGui::Text("Adjust Shape Properties:");
			ImGui::Separator();
            bool boolHexagonOrientation = false;
			boolHexagonOrientation = ImGui::RadioButton("Pointy Top", &hexGen.m_hexagonOrientation, 0);
			ImGui::SameLine();
			boolHexagonOrientation = ImGui::RadioButton("Flat Top", &hexGen.m_hexagonOrientation, 1);
            bool boolLineThickness = ImGui::SliderInt("Shape Thickness: ", &hexGen.m_lineThickness, 1, 10);
			bool boolHexRadius = ImGui::SliderInt("Hexagon Radius: ", &hexGen.m_hexagonRadius, 5, 100);
			bool boolImageWidth = ImGui::SliderInt("Image Width: ", &hexGen.m_hexGridData.imageSize.width, 1, 2000);
			bool boolImageHeight = ImGui::SliderInt("Image Height: ", &hexGen.m_hexGridData.imageSize.height, 1, 2000);
            
			ImGui::Spacing();

			ImGui::Text("Edit Background/Shape Colors:");
            ImGui::Separator();
			ImGui::RadioButton("Background Color", &selectMode, 0);
            ImGui::SameLine();
			ImGui::RadioButton("Shape Color", &selectMode, 1);
			ImGui::Spacing();
            ImGui::SetNextItemWidth(200);
            bool boolColorPicker = ImGui::ColorPicker3(" ", (selectMode == 1)? (float*)&hexGen.m_lineColor : (float*)&hexGen.m_backgroundColor, COLOR_FLAGS);
            ImGui::Spacing();

        ImGui::EndChild();
        ImGui::SameLine();

        // -----------------------------
        //  RIGHT SIDE: Image Display
        // -----------------------------
        ImGui::BeginChild("RightPanel", ImVec2(0, 0), true);
            
        // Run your layout and draw
        if (boolLineThickness || boolHexRadius || boolImageWidth || boolImageHeight || boolColorPicker || boolHexagonOrientation) {
			hexGen.DeleteTexture(hexGen.m_textureID);
            // Update bitmap image
            CreateBitmapImage(hexGen.m_hexGridData, hexGen.m_backgroundColor);
            hexGen.GenerateHexagonalGridPattern(hexGen.m_hexagonRadius, hexGen.m_lineColor, hexGen.m_lineThickness);
            hexGen.LoadTexture();
        }

        hexGen.DisplayImage();

        ImGui::EndChild();
        ImGui::End(); // Main window

        window.EndFrame();
    }
    hexGen.DeleteTexture(hexGen.m_textureID);
    window.Shutdown();
    return 0;
}
