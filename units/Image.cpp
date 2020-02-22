//
// Created by fusionbolt on 2020-01-28.
//

#include "Image.h"

GWUI::Image::Image(std::string path):_imgPath(std::move(path))
{

}

void GWUI::Image::Draw(Renderer &renderer, Rect rect)
{
    if(_imgTexture == nullptr)
    {
        _imgTexture = renderer.LoadIMG(_imgPath);
    }
    renderer.RenderTexture(_imgTexture, rect);
}

void GWUI::Image::SetPath(const std::string& path)
{
    _imgPath = path;
}
