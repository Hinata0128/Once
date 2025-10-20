#pragma once
#include <memory>
// #include "Renderer.h" (Rendererクラスを使うのは実装側なので、ここでは不要な場合が多い)

class IDrawable {
public:
    // 仮想デストラクタは必須
    virtual ~IDrawable() = default;

    // 変更後のDraw関数（引数なし）
    virtual void Draw() = 0;
};