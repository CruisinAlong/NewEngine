#include "ProBuilderEditorWindow.h"
#include <imgui.h>

namespace ProBuilder {

    ProBuilderEditorWindow::ProBuilderEditorWindow() = default;

    void ProBuilderEditorWindow::OnImGuiRender(std::vector<Sign::PrimitiveType>& pending, int& stairsCount, bool& faceSelectionEnabled)
    {
        if (!m_Open) return;

        ImGui::Begin("ProBuilder", &m_Open);

        ImGui::TextUnformatted("Primitives");
        if (ImGui::Button("Add Cube")) {
            pending.push_back(Sign::PrimitiveType::Cube);
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Plane")) {
            pending.push_back(Sign::PrimitiveType::Plane);
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Cylinder")) {
            pending.push_back(Sign::PrimitiveType::Cylinder);
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Sphere")) {
            pending.push_back(Sign::PrimitiveType::Sphere);
        }

        ImGui::Separator();

        ImGui::TextUnformatted("Stairs");
        ImGui::SliderInt("Steps", &stairsCount, 1, 128);
        if (ImGui::Button("Add Stairs")) {
            pending.push_back(Sign::PrimitiveType::Stairs);
        }

        ImGui::Separator();

        ImGui::TextUnformatted("Selection");
        ImGui::Checkbox("Enable Face Selection (right-click)", &faceSelectionEnabled);
        ImGui::SameLine();
        ImGui::TextDisabled("(toggle on to pick faces)");

        ImGui::End();
    }

} 