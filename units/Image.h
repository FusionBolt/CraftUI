//
// Created by fusionbolt on 2020-01-28.
//

#ifndef GWUI_IMAGE_H
#define GWUI_IMAGE_H

#include <string>

#include "../units/Renderer.h"

namespace Craft
{
    class Image
    {
    public:
        Image() = default;

        explicit Image(std::string path);

        void Draw(Renderer &renderer, Rect rect);

        void SetPath(const std::string& path);

    private:
        std::string _imgPath;

        std::shared_ptr<SDL_Texture> _imgTexture;

    };
}

#endif //GWUI_IMAGE_H
