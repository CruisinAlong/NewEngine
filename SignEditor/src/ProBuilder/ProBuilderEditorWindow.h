#pragma once
#include <Sign.h>
#include <vector>

namespace ProBuilder {

class ProBuilderEditorWindow {
public:
    ProBuilderEditorWindow();
    void OnImGuiRender(std::vector<Sign::PrimitiveType>& pending, int& stairsCount);
    void SetVisible(bool v) { m_Open = v; }
    bool IsVisible() const { return m_Open; }
private:
    bool m_Open = true;
};

}
