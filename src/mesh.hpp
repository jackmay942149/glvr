#pragma once
#include "vector"

class Mesh{
  public:
    const std::vector<float> m_Vertices;
    const std::vector<int> m_Indices;

    Mesh(const std::vector<float>& Vertices, const std::vector<int>& Indices):
      m_Vertices{Vertices},
      m_Indices{Indices}{}
};
