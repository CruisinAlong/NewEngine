#include "ProBuilderEditorWindow.h"
#include <imgui.h>

namespace ProBuilder {

ProBuilderEditorWindow::ProBuilderEditorWindow()
{
}

void ProBuilderEditorWindow::OnImGuiRender(std::vector<Sign::PrimitiveType>& pending)
{
    if (!m_Open)
        return;

    ImGui::Begin("ProBuilder", &m_Open);

    if (ImGui::Button("Create Cube"))
        pending.push_back(Sign::PrimitiveType::Cube);
    ImGui::SameLine();
    if (ImGui::Button("Create Plane"))
        pending.push_back(Sign::PrimitiveType::Plane);
    ImGui::SameLine();
    if (ImGui::Button("Create Cylinder"))
        pending.push_back(Sign::PrimitiveType::Cylinder);
    if (ImGui::Button("Create Sphere"))
        pending.push_back(Sign::PrimitiveType::Sphere);
    if (ImGui::Button("Create Stairs"))
		pending.push_back(Sign::PrimitiveType::Stairs);

    ImGui::End();
}

}
