#pragma once
#include "textureFormat.hpp"
#include <string>

class BMP : public Texture {
public:
  BMP(int width, int height, int colorChannels){
    m_width = width;
    m_height = height;
    m_colorChannels = colorChannels;
  }

  
  unsigned char* load(const std::string& filepath) override;
  void free(unsigned char* a) override; 
};
