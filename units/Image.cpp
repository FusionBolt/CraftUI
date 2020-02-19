//
// Created by fusionbolt on 2020-01-28.
//

#include "Image.h"

GWUI::Image::Image(const std::string& path):_imgPath(path)
{

}

void GWUI::Image::Draw(GWUI::Renderer renderer)
{
    if(_imgTexture == nullptr)
    {
        _imgTexture = renderer.LoadIMG(_imgPath);
    }
    renderer.RenderTexture(_imgTexture, _rect);
}

void GWUI::Image::SetRect(GWUI::Rect rect)
{
    _rect = rect;
}

void GWUI::Image::SetPath(const std::string& path)
{
    _imgPath = path;
}