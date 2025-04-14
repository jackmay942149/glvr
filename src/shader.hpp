#pragma once
#include "string"

class Shader {
  public:
    unsigned int uid;
    Shader(const std::string&, const std::string&);

    void use();

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, float x, float y, float z);
};
