#pragma once
#include "vertexarrayobject.h"
#include "glm/vec2.hpp"
#include "instance.h"

namespace eng {
	class InstancedVertexArrayObject : public VertexArrayObject {
	public:
		InstancedVertexArrayObject() : VertexArrayObject() {}
		~InstancedVertexArrayObject();
		void setInstanceColours(std::vector<glm::vec3> const&);
		void setInstances(std::vector<Instance> const& positions) { instances = positions; }
		std::vector<Instance> const& getInstances() const { return instances; }
		int getInstanceCount() const { return instances.size(); }
		virtual void render(glm::mat4 matrix) override;
		virtual void load() override;
		void reload();

	protected:
		void allocateInstanceMemory(int amount);
		void setInstanceData(std::vector<Instance> const&);
		virtual void assignAttributes() override;
		virtual void generateArrays() override;
		std::vector<Instance> instances;
	};
}