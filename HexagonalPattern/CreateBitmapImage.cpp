#include "External/imgui/imgui.h"
#include "Declarations.h"
#include <vector>
#include <fstream>

/*void CreateBitmapImage(BitmapImageData& bmpImgData, const ImVec4& backgroundColor)
{
    // Compute row size (padded to 4 bytes)
    bmpImgData.bitmapRowSize = (bmpImgData.imageSize.width * 3 + 3) & ~3;

    const int imageSize = bmpImgData.bitmapRowSize * bmpImgData.imageSize.height;
    bmpImgData.pixelData.resize(imageSize);

    // BMP header (54 bytes)
    unsigned char header[54] = { 0 };
    header[0] = 'B';
    header[1] = 'M';
    *(int*)&header[2] = 54 + imageSize;                 // File size
    *(int*)&header[10] = 54;                             // Offset to pixel data
    *(int*)&header[14] = 40;                             // DIB header size
    *(int*)&header[18] = bmpImgData.imageSize.width;
    *(int*)&header[22] = bmpImgData.imageSize.height;
    *(short*)&header[26] = 1;                            // Planes
    *(short*)&header[28] = 24;                           // Bits per pixel
    *(int*)&header[34] = imageSize;                      // Pixel array size

    // Convert background color (ImVec4 → RGB)
    const unsigned char r = static_cast<unsigned char>(backgroundColor.x * 255.0f);
    const unsigned char g = static_cast<unsigned char>(backgroundColor.y * 255.0f);
    const unsigned char b = static_cast<unsigned char>(backgroundColor.z * 255.0f);

    // Fill pixel data (BMP is bottom-up)
    for (int y = 0; y < bmpImgData.imageSize.height; ++y)
    {
        unsigned char* row = &bmpImgData.pixelData[(bmpImgData.imageSize.height - 1 - y) * bmpImgData.bitmapRowSize];

        // Fill each pixel
        for (int x = 0; x < bmpImgData.imageSize.width; ++x)
        {
            int index = x * 3;
            row[index + 0] = b;
            row[index + 1] = g;
            row[index + 2] = r;
        }

        // Fill padding bytes (if any) with 0
        for (int pad = bmpImgData.imageSize.width * 3; pad < bmpImgData.bitmapRowSize; ++pad)
        {
            row[pad] = 0;
        }
    }

    // Write BMP file
    std::ofstream outFile("hexagonal_pattern_new.bmp", std::ios::binary);
    if (outFile)
    {
        outFile.write(reinterpret_cast<char*>(header), 54);
        outFile.write(reinterpret_cast<char*>(bmpImgData.pixelData.data()), imageSize);
        outFile.close();  // optional but explicit
    }
}*/

/*void  CreateBitmapImage(BitmapImageData& bmpImgData, const ImVec4& backgroundColor)
{
    bmpImgData.bitmapRowSize = (bmpImgData.imageSize.width * 3 + 3) & ~3;
    bmpImgData.pixelData.resize((bmpImgData.bitmapRowSize * bmpImgData.imageSize.height));
    const int imageSize = bmpImgData.bitmapRowSize * bmpImgData.imageSize.height;

    unsigned char m_header[54]; //fileHeaderSize=14 and informationHeaderSize = 40
    m_header[0] = 'B';
    m_header[1] = 'M';
    unsigned char* p = &m_header[2];
    *(int*)(p) = 54 + imageSize; // File size
    p = &m_header[10];
    *(int*)(p) = 54; // Offset to pixel data
    p = &m_header[14];
    *(int*)(p) = 40; // Header size
    p = &m_header[18];
    *(int*)(p) = bmpImgData.imageSize.width;
    p = &m_header[22];
    *(int*)(p) = bmpImgData.imageSize.height;
    p = &m_header[26];
    *(unsigned short*)(p) = 1; // Number of planes
    p = &m_header[28];
    *(unsigned short*)(p) = 24; // Bits per pixel
    p = &m_header[34];
    *(int*)(p) = imageSize; // Image size

    int r = static_cast<int>(backgroundColor.x * 255.0f);
    int g = static_cast<int>(backgroundColor.y * 255.0f);
    int b = static_cast<int>(backgroundColor.z * 255.0f);

    for (int dataHeight = 0; dataHeight < bmpImgData.imageSize.height; dataHeight++) {
        for (int dataWidth = 0; dataWidth < bmpImgData.imageSize.width; dataWidth++) {
            int index = dataHeight * bmpImgData.bitmapRowSize + dataWidth * 3;
            bmpImgData.pixelData[index] = b;        // Blue
            bmpImgData.pixelData[index + 1] = g;    // Green
            bmpImgData.pixelData[index + 2] = r;    // Red
        }
        for (int pad = bmpImgData.imageSize.width * 3; pad < bmpImgData.bitmapRowSize; pad++) {
            int index = dataHeight * bmpImgData.bitmapRowSize + pad;
            bmpImgData.pixelData[index] = 0; // Padding
        }
    }
}*/

void CreateBitmapImage(BitmapImageData& bmpImgData, const ImVec4& backgroundColor)
{
    // Exact row size (no padding)
    bmpImgData.bitmapRowSize = bmpImgData.imageSize.width * 3;

    const int imageSize = bmpImgData.bitmapRowSize * bmpImgData.imageSize.height;
    bmpImgData.pixelData.resize(imageSize);

    // Convert background color
    const unsigned char r = static_cast<unsigned char>(backgroundColor.x * 255.0f);
    const unsigned char g = static_cast<unsigned char>(backgroundColor.y * 255.0f);
    const unsigned char b = static_cast<unsigned char>(backgroundColor.z * 255.0f);

    // Fill pixel data (top-left = (0,0))
    for (int y = 0; y < bmpImgData.imageSize.height; ++y)
    {
        unsigned char* row = &bmpImgData.pixelData[y * bmpImgData.bitmapRowSize];

        for (int x = 0; x < bmpImgData.imageSize.width; ++x)
        {
            int index = x * 3;
            row[index + 0] = b;
            row[index + 1] = g;
            row[index + 2] = r;
        }
    }

    // Optional: Write BMP file (minimal valid BMP)
    unsigned char header[54] = { 0 };
    header[0] = 'B';
    header[1] = 'M';
    *(int*)&header[2] = 54 + imageSize;                 // file size
    *(int*)&header[10] = 54;                             // offset to pixel data
    *(int*)&header[14] = 40;                             // DIB header size
    *(int*)&header[18] = bmpImgData.imageSize.width;
    *(int*)&header[22] = bmpImgData.imageSize.height;
    *(short*)&header[26] = 1;                            // planes
    *(short*)&header[28] = 24;                           // bits per pixel
    *(int*)&header[34] = imageSize;

    std::ofstream outFile("hexagonal_pattern_new.bmp", std::ios::binary);
    if (outFile)
    {
        outFile.write(reinterpret_cast<char*>(header), 54);
        outFile.write(reinterpret_cast<char*>(bmpImgData.pixelData.data()), imageSize);
        outFile.close();
    }
}




