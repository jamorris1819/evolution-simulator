#include "plant.h"

Plant::Plant(GLuint shader, glm::vec3 position) : LivingEntity(shader, position) {
}

void Plant::generate() {
	/*((PlantBody*)body)->setAttributes(
		genome->getGeneValue<float>(GeneMarker::GM_SIZE),
		genome->getGeneValue<float>(GeneMarker::GM_LEAF_LENGTH),
		genome->getGeneValue<int>(GeneMarker::GM_LEAF_LAYERS),
		genome->getGeneValue<int>(GeneMarker::GM_LEAF_STEPS),
		genome->getGeneValue<int>(GeneMarker::GM_BUSH_COUNT),
		genome->getGeneValue<int>(GeneMarker::GM_COLOUR_R),
		genome->getGeneValue<int>(GeneMarker::GM_COLOUR_G),
		genome->getGeneValue<int>(GeneMarker::GM_COLOUR_B)
	);
	body->generate();
	body->setPosition(getPosition());
	body->load();
	body->r = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_R);
	body->g = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_G);
	body->b = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_B);*/

	LivingEntity::generate();
}