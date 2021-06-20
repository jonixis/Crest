#pragma once

#include <string>

#include "Renderer.h"

class Texture {

public:
    Texture(const std::string &path);

    ~Texture();

    void bind(unsigned int slot = 0) const;

    void unbind();

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

private:

    unsigned int m_rendererID;
    std::string m_filePath;
    unsigned char *m_localBuffer;
    int m_width, m_height, m_bpp;

};
