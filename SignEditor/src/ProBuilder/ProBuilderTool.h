#pragma once
#include <Sign.h>

namespace ProBuilder {

class ProBuilderTool {
public:
    enum class Mode { Object, Vertex, Edge, Face };
    ProBuilderTool();
    void SetMode(Mode m) { m_Mode = m; }
    Mode GetMode() const { return m_Mode; }
private:
    Mode m_Mode = Mode::Object;
};

}
