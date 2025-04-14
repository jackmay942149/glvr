#pragma once
#include <string>

class Texture {
public:
  int m_width;
  int m_height;
  int m_colorChannels;
  virtual unsigned char* load(const std::string& filepath) = 0;
  virtual void free(unsigned char* a) = 0;
};
