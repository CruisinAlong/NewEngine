#pragma once
#include <cstdint>
#include <bitset>
#include <limits>
namespace Sign {

	using EntityID = uint32_t;
	constexpr EntityID INVALID_ENTITY_ID = (std::numeric_limits<EntityID>().max)();
	using ComponentType = uint8_t;

	constexpr EntityID MAX_ENTITIES = 5000;
	constexpr ComponentType MAX_COMPONENTS = 32;


	using Signature = std::bitset<MAX_COMPONENTS>;
}

