#pragma once
#include <vector>
#include "Sign/Scene/ECS/ECSTypes.h"
namespace Sign {

	class ISparseSet {
	public:
		virtual ~ISparseSet() = default;

		virtual void Remove(EntityID entity) = 0;

	};
	template<typename T>
	class SparseSet : public ISparseSet
	{
	public:

		SparseSet(uint32_t maxEntities = MAX_ENTITIES, uint32_t maxComponents = MAX_ENTITIES);
		~SparseSet();

		T* Get(EntityID entity);
		T& Add(EntityID entity, T component);
		void Delete(EntityID entity);
		void Clear();
		// Inherited via ISparseSet
		void Remove(EntityID entity) override
		{
			Delete(entity);
		}

		size_t Size() { return dense.size(); }

		auto begin() { return dense.begin(); }
		auto end()   { return dense.end(); }

		auto begin() const { return dense.begin(); }
		auto end() const   { return dense.end(); }

	private:
		std::vector<uint32_t> sparse;
		std::vector<T> dense;
	};

	template<typename T>
	inline SparseSet<T>::SparseSet(uint32_t maxEntities, uint32_t maxComponents)
	{

		sparse.resize(maxEntities);

		dense.reserve(maxComponents);
	}
	template<typename T>
	inline SparseSet<T>::~SparseSet()
	{
	}
	template<typename T>
	inline T* SparseSet<T>::Get(EntityID entity)
	{
		// TODO: insert return statement here
		if (entity >= sparse.size()) {
			return nullptr;
		}
		auto idx = sparse[entity];
		if (idx < dense.size() && dense[idx].m_entity == entity)
			return &dense[idx];

		return nullptr;
	}
	template<typename T>
	inline T& SparseSet<T>::Add(EntityID entity, T component)
	{
		// TODO: insert return statement here
		if (entity >= sparse.size())
			sparse.resize(entity + 1);
		auto idx = sparse[entity];
		
		if (idx < dense.size() && dense[idx].m_entity == entity)
			return dense[idx];

		component.m_entity = entity;
		sparse[entity] = dense.size();
		dense.push_back(std::move(component));


		return dense.back();
	}
	template<typename T>
	inline void SparseSet<T>::Delete(EntityID entity)
	{
		if (entity >= sparse.size()) {
			return;
		}

		auto idx = sparse[entity];

		if (idx >= dense.size() || dense[idx].m_entity != entity)
			return;
		auto lastIdx = dense.size() - 1;
		if (idx != lastIdx)
		{
			dense[idx] = std::move(dense[lastIdx]);
			sparse[dense[idx].m_entity] = idx;
		}
		dense.pop_back();
	}
	template<typename T>
	inline void SparseSet<T>::Clear()
	{
		sparse.clear();
		dense.clear();
	}
}

