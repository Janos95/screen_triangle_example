
#include "screen_triangle_shader.hpp"

#include <Corrade/Containers/StridedArrayView.h>

#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/Image.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/ImageView.h>

#include <random>
#include <iostream>

using namespace Magnum;
using namespace Corrade;

class ScreenTriangleExample: public Platform::Application {
public:
    explicit ScreenTriangleExample(const Arguments& arguments);

private:
    void drawEvent() override;
    void tickEvent() override;

    GL::Mesh _mesh;
    ScreenTriangleShader _shader;
    GL::Texture2D _texture;

    std::default_random_engine _eng;
    std::uniform_real_distribution<float> _distr;
};

ScreenTriangleExample::ScreenTriangleExample(const Arguments& arguments):
        Platform::Application{arguments, Configuration{}.setTitle("Screen Triangle Example")},
        _eng(0),
        _distr(0,1)
{
}

void ScreenTriangleExample::tickEvent() {
    redraw();
}

void ScreenTriangleExample::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    auto s = GL::defaultFramebuffer.viewport().size();
    Containers::Array<char> data(Containers::NoInit, s.x() * s.y() * sizeof(Color4));
    Image2D image{PixelFormat::RGBA32F, s, std::move(data)};
    for(auto row: image.pixels<Color4>()) {
        for(Color4& p: row){
            p = Color4(_distr(_eng),_distr(_eng),_distr(_eng),1);
        }
    }

    _texture.setStorage(1, GL::TextureFormat::RGBA32F, s)
            .setSubImage(0, {}, image)
            .generateMipmap();

    _shader.bindTexture(_texture).draw(GL::Mesh{}.setCount(3));

    swapBuffers();
}


MAGNUM_APPLICATION_MAIN(ScreenTriangleExample)