#pragma once
#include <memory>
// #include "Renderer.h" (Renderer�N���X���g���͎̂������Ȃ̂ŁA�����ł͕s�v�ȏꍇ������)

class IDrawable {
public:
    // ���z�f�X�g���N�^�͕K�{
    virtual ~IDrawable() = default;

    // �ύX���Draw�֐��i�����Ȃ��j
    virtual void Draw() = 0;
};