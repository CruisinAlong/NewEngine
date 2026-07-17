#include "ProBuilderEditorWindow.h"
#include <imgui.h>

namespace ProBuilder {

ProBuilderEditorWindow::ProBuilderEditorWindow()
{
}

void ProBuilderEditorWindow::OnImGuiRender(std::vector<Sign::PrimitiveType>& pending, int& stairsCount)
{
    if (!m_Open)
        return;

    ImGui::Begin("ProBuilder", &m_Open);

    if (ImGui::Button("Create Cube")) {
        pending.push_back(Sign::PrimitiveType::Cube);
        std::println("[ProBuilder] Create Cube clicked");
    }
    ImGui::SameLine();
    if (ImGui::Button("Create Plane")) {
        pending.push_back(Sign::PrimitiveType::Plane);
        std::println("[ProBuilder] Create Plane clicked");
    }
    ImGui::SameLine();
    if (ImGui::Button("Create Cylinder")) {
        pending.push_back(Sign::PrimitiveType::Cylinder);
        std::println("[ProBuilder] Create Cylinder clicked");
    }
    if (ImGui::Button("Create Sphere")) {
        pending.push_back(Sign::PrimitiveType::Sphere);
        std::println("[ProBuilder] Create Sphere clicked");
    }
    ImGui::TextUnformatted("Stairs");
    ImGui::SliderInt("Steps", &stairsCount, 1, 128); // adjust max if needed
    if (ImGui::Button("Add Stairs")) {
        // When EditorLayer processes the queue it will use the editor's current stairsCount
        pending.push_back(Sign::PrimitiveType::Stairs);
    }

    ImGui::End();
}

}
