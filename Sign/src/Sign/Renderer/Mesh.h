#pragma once
#include <cstdint>
#include "Sign/Buffers/VertexArray.h"
#include "Sign/Math/SignMath.h"

namespace Sign {
	class Mesh
	{
	public:
		Mesh(const void* vertices, uint32_t vertexCount, const WORD* indices, uint32_t indexCount);
		~Mesh() = default;
		const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }


	private:
		std::shared_ptr<VertexArray> m_VertexArray;
	};
}

