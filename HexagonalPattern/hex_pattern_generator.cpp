#include "hex_pattern_generator.h"


namespace {

    Point hex_to_pixel(Layout layout, Hex h)
    {
        Orientation M = layout.orientation;
        Point size = layout.size;
        Point origin = layout.origin;
        double x = (M.f0 * h.q + M.f1 * h.r) * size.x;
        double y = (M.f2 * h.q + M.f3 * h.r) * size.y;
        return Point(x + origin.x, y + origin.y);
    }

    Point hex_corner_offset(Layout layout, int corner)
    {
        Orientation M = layout.orientation;
        Point size = layout.size;
        double angle = 2.0 * M_PI * (M.start_angle - corner) / 6.0;
        return Point(size.x * cos(angle), size.y * sin(angle));
    }

    const Orientation layoutPointy = Orientation(sqrt(3.0),
        sqrt(3.0) / 2.0,
        0.0,
        3.0 / 2.0,
        sqrt(3.0) / 3.0,
        -1.0 / 3.0,
        0.0,
        2.0 / 3.0,
        0.5);

    const Orientation layoutFlat = Orientation(3.0 / 2.0,
        0.0,
        sqrt(3.0) / 2.0,
        sqrt(3.0),
        2.0 / 3.0, 0.0,
        -1.0 / 3.0,
        sqrt(3.0) / 3.0,
        0.0);
}//namespace

void hex_pattern_generator::DeleteTexture(GLuint& texture) {
    //use this if the image data is changed or the texture is not needed
    if (texture != 0) {
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

void hex_pattern_generator::LoadTexture()
{
    if (m_textureID != 0) {
        glDeleteTextures(1, &m_textureID);
        m_textureID = 0;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_hexGridData.imageSize.width, m_hexGridData.imageSize.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_hexGridData.pixelData.data());
}

void hex_pattern_generator::SetColor(const int x, const int y, const ImVec4& lineColor) {
    if (x < 0 || x >= m_hexGridData.imageSize.width ||
        y < 0 || y >= m_hexGridData.imageSize.height)
        return;

    int red = static_cast<int>(lineColor.x * 255.0f);
    int green = static_cast<int>(lineColor.y * 255.0f);
    int blue = static_cast<int>(lineColor.z * 255.0f);

    int index = y * m_hexGridData.bitmapRowSize + x * 3;
    m_hexGridData.pixelData[index + 0] = blue;
    m_hexGridData.pixelData[index + 1] = green;
    m_hexGridData.pixelData[index + 2] = red;
}

void hex_pattern_generator::DrawLine(int startX, int startY, int endX, int endY, int lineThickness, ImVec4& lineColor) {
    double deltaX = abs(endX - startX);
    double deltaY = abs(endY - startY);
    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;
    double error = deltaX - deltaY;

    while (true) {
        for (int dx = -lineThickness; dx <= lineThickness; ++dx) {
            for (int dy = -lineThickness; dy <= lineThickness; ++dy) {
                SetColor(startX + dx, startY + dy, lineColor);
            }
        }
        if (startX == endX && startY == endY) break;
        double doubledError = 2 * error;
        if (doubledError > -deltaY) {
            error -= deltaY;
            startX += stepX;
        }
        if (doubledError < deltaX) {
            error += deltaX;
            startY += stepY;
        }
    }
}

std::vector<Point> hex_pattern_generator::PolygonCorners(Layout layout, Hex h)
{
    std::vector<Point> corners = {};
    Point centers = hex_to_pixel(layout, h);
    for (int i = 0; i < 6; i++)
    {
        Point offset = hex_corner_offset(layout, i);
        corners.push_back(Point(centers.x + offset.x, centers.y + offset.y));
    }
    return corners;
}

std::vector<unsigned char> hex_pattern_generator::GenerateHexagonalGridPattern(int hexagonRadius, ImVec4 lineColor, int lineThickness)
{
    Layout shapeOrientation = Layout((m_hexagonOrientation == 1)? layoutFlat : layoutPointy, Point(hexagonRadius, hexagonRadius), Point(m_hexGridData.imageSize.width / 2, m_hexGridData.imageSize.height / 2));
    int cols = (m_hexGridData.imageSize.width / (hexagonRadius * 1.5)) + 1;
    int rows = (m_hexGridData.imageSize.height / (hexagonRadius * sqrt(3))) + 1;
    for (int q = -cols; q <= cols; q++) {
        for (int r = -rows; r <= rows; r++) {
            Hex hex(q, r, -q - r);
            std::vector<Point> corners = PolygonCorners(shapeOrientation, hex);
            for (int i = 0; i < 6; i++) {
                DrawLine(corners[i].x, corners[i].y, corners[(i + 1) % 6].x, corners[(i + 1) % 6].y, lineThickness, lineColor);
            }
        }
    }

    return m_hexGridData.pixelData;
}

void hex_pattern_generator::DisplayImage() {
    if (m_textureID != 0) {
        ImGui::Image((ImTextureID)(intptr_t)m_textureID, ImVec2(float(m_hexGridData.imageSize.width), float(m_hexGridData.imageSize.height)));
    }
}
