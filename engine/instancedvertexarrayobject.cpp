#include "pch.h"
#include "instancedvertexarrayobject.h"

namespace eng {
	InstancedVertexArrayObject::~InstancedVertexArrayObject() {
	}

	void InstancedVertexArrayObject::setInstanceColours(std::vector<glm::vec3> const& colours) {
		// todo: check amounts provided
		for (int i = 0; i < colours.size(); i++) {
			instances[i].colour = colours[i];
		}
		reload();
	}

	void InstancedVertexArrayObject::render(glm::mat4 matrix) {
		if (!enabled)
			return;

		// Attach model matrix to shader.
		if (model == -1) model = glGetUniformLocation(shaderId, "uModel");
		glUniformMatrix4fv(model, 1, GL_TRUE, &matrix[0][0]);

		// Bind vertex and render polygon.
		glBindVertexArray(vao[0]);
		glDrawElementsInstanced(GL_TRIANGLES, vertexArray.getIndexCount(), GL_UNSIGNED_SHORT, 0, instances.size());
		glBindVertexArray(0);
	}

	void InstancedVertexArrayObject::generateArrays() {
		glGenVertexArrays(1, vao);
		glBindVertexArray(vao[0]);
		glGenBuffers(4, vbo);
	}

	void InstancedVertexArrayObject::load() {
		bindVertexArray();

		generateVertexData();

		allocateVertexMemory(vertexArray.getVertexCount());
		allocateIndexMemory(vertexArray.getIndexCount());
		allocateInstanceMemory(instances.size());

		setVertexData(vertexData);
		setIndexData(vertexArray.getIndices().data());
		setInstanceData(instances);

		assignAttributes();

		unbindVertexArray();
		enabled = true;
	}

	void InstancedVertexArrayObject::reload() {
		setInstanceData(instances);
	}

	void InstancedVertexArrayObject::allocateInstanceMemory(int amount) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InstancedVertexArrayObject::setInstanceData(std::vector<Instance> const& data) {
		std::vector<glm::vec2> positions;
		std::vector<glm::vec3> colours;
		for (Instance const& i : data) {
			positions.push_back(i.position);
			colours.push_back(i.colour);
		}

		int count = instances.size();
		GLint* size = new GLint;

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferSubData(GL_ARRAY_BUFFER, NULL, count * sizeof(glm::vec2), &positions[0]);

		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, size);

		if (count * sizeof(glm::vec2) != *size) {
			std::cout << "Instance position data not loaded onto graphics card correctly" << std::endl;
			terminate();
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferSubData(GL_ARRAY_BUFFER, NULL, count * sizeof(glm::vec3), &colours[0]);

		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, size);

		if (count * sizeof(glm::vec3) != *size) {
			std::cout << "Instance colour data not loaded onto graphics card correctly" << std::endl;
			terminate();
		}

		delete size;
	}

	void InstancedVertexArrayObject::assignAttributes() {
		VertexArrayObject::assignAttributes();

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		int vOffsetLocation = glGetAttribLocation(shaderId, "vOffset");
		glEnableVertexAttribArray(vOffsetLocation);
		glVertexAttribPointer(vOffsetLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glVertexAttribDivisor(vOffsetLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		int vOverrideColourLocation = glGetAttribLocation(shaderId, "vOverrideColour");
		glEnableVertexAttribArray(vOverrideColourLocation);
		glVertexAttribPointer(vOverrideColourLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glVertexAttribDivisor(vOverrideColourLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}