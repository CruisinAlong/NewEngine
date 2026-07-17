#pragma once
#include "Sign/Renderer/Mesh.h"
namespace Sign {
	class ResourceCache
	{
	public:
		template <std::derived_from<Mesh> T>
		static std::shared_ptr<T> GetOrCreate(std::string_view key, std::function<std::shared_ptr<T>()> factory) {
			std::string keyStr(key);

			auto it = s_StaticCache.find(keyStr);

			if (it != s_StaticCache.end()) {
				return std::static_pointer_cast<T>(it->second);
			}

			std::shared_ptr<T> resource = factory();
			s_StaticCache[keyStr] = resource;
			return resource;
		}

		static void Clear() { s_StaticCache.clear(); }
	private:
		inline static std::unordered_map<std::string, std::shared_ptr<Mesh>> s_StaticCache;

	};
}

