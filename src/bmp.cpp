#include "bmp.hpp"
#include "iostream"
#include <fstream>
#include <sstream>

unsigned char* BMP::load(const std::string& filepath) {
  // Load file uses same method as shader.cpp
  std::string imageData;
  std::ifstream imageFile;

  imageFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    imageFile.open(filepath);
    std::stringstream imageStream;

    imageStream << imageFile.rdbuf();
    imageFile.close();

    imageData = imageStream.str();
  }
  catch(std::ifstream::failure e){
    std::cout <<"Error (TODO:ErrorCode): Texture file not loaded successfully" << std::endl;
  }
  
  unsigned char* texture = new unsigned char ((unsigned char) *imageData.c_str());
  return texture;
}

void BMP::free(unsigned char* a) {
  delete a;
  std::cout << "Freeing Texture From Memory" << std::endl;
  return;
}

