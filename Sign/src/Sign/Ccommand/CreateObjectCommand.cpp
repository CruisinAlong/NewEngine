#include "signpch.h"
#include "CreateObjectCommand.h"

namespace Sign {
	void CreateObjectCommand::Execute()
	{
		if (m_Entity == nullptr) {
			switch (m_PType) {
			case PrimitiveType::Cube:
				m_Entity = std::make_shared<CubeEntity>();
				m_Entity->SetTranslation({ MathUtils::Random_Float(-10.0f,10.0f),MathUtils::Random_Float(-10.0f,10.0f) ,MathUtils::Random_Float(-10.0f,10.0f) });
				std::println("Cube Added");
				break;
			case PrimitiveType::Plane:
				m_Entity = std::make_shared<PlaneEntity>();
				m_Entity->SetTranslation({ MathUtils::Random_Float(-15.0f,15.0f),MathUtils::Random_Float(-15.0f,15.0f) ,MathUtils::Random_Float(-15.0f,15.0f) });
				break;
			}
		}
		
		m_EntityList.push_back(m_Entity);
	}
	void CreateObjectCommand::Undo()
	{
		auto it = std::find(m_EntityList.begin(), m_EntityList.end(), m_Entity);

		if (it != m_EntityList.end()) {
			m_EntityList.erase(it);
		}
	}
}