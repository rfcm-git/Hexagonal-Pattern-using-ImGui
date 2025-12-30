#pragma once
#include <vector>
#include "External/imgui/Backend/imgui_impl_glfw.h"
#include "External/GLFW/glfw3.h"
#include "Declarations.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace {
	constexpr int COLOR_FLAGS = ImGuiColorEditFlags_Float			| 
								ImGuiColorEditFlags_HDR				|
								ImGuiColorEditFlags_NoSidePreview	|
								ImGuiColorEditFlags_PickerHueWheel	| 
								ImGuiColorEditFlags_NoInputs	;
}

class hex_pattern_generator
{
public:
	BitmapImageData m_hexGridData;
	GLuint m_textureID = 0;
	ImVec4 m_backgroundColor = { 179, 44, 25, 0 };
	ImVec4 m_lineColor = { 255, 255, 255, 1 };
	int m_lineThickness = 1.0f;
	int m_hexagonRadius = 20;
	int m_hexagonOrientation = 0; // 0 = pointy, 1 = flat

	void LoadTexture();
	void DisplayImage();
	std::vector<unsigned char> GenerateHexagonalGridPattern(int hexagonRadius, ImVec4 lineColor, int lineThickness);
	void DeleteTexture(GLuint& texture);
private:
	void SetColor(const int x, const int y, const ImVec4& lineColor);
	void DrawLine(int startX, int startY, int endX, int endY, int lineThickness, ImVec4& lineColor);
	std::vector<Point> PolygonCorners(Layout layout, Hex h);

};

