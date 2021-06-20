//
// Created by fusionbolt on 2020-01-28.
//

#include "Image.h"

Craft::Image::Image(std::string path): _imgPath(std::move(path))
{

}

void Craft::Image::Draw(Renderer &renderer, Rect rect)
{
    if (_imgTexture == nullptr)
    {
        _imgTexture = renderer.LoadIMG(_imgPath);
    }
    renderer.RenderTexture(_imgTexture, rect);
}

void Craft::Image::SetPath(const std::string& path)
{
    _imgPath = path;
}
