//
// Created by janos on 27.03.20.
//

#pragma once


#pragma once

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/Shaders/Generic.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/GL/Texture.h>

using namespace Magnum;

class ScreenTriangleShader: public GL::AbstractShaderProgram {
public:
    using Position = Shaders::Generic3D::Position;

    explicit ScreenTriangleShader();

    ScreenTriangleShader& bindTexture(GL::Texture2D& texture);
};


