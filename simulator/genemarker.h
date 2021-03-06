#pragma once
#include <tuple>

enum class GeneMarker
{
	GM_SIZE,
	GM_COLOUR_R,
	GM_COLOUR_G,
	GM_COLOUR_B,
	GM_SPEED_MOVEMENT,
	GM_SPEED_ROTATION,

	// Body genes
	GM_BODY_STEPS,
	GM_BODY_MUTATION_RATE,
	GM_BODY_OFFSETX,
	GM_BODY_OFFSETY,

	// Plant genes
	GM_LEAF_STEPS,
	GM_LEAF_LENGTH,
	GM_LEAF_LAYERS,
	GM_BUSH_COUNT,

	// Leave at end for count.
	GENE_COUNT
};

inline const char* geneMarkerToString(GeneMarker v)
{
	switch (v)
	{
	case GeneMarker::GM_SIZE:   return "SIZE";
	case GeneMarker::GM_COLOUR_R:   return "COLOUR R";
	case GeneMarker::GM_COLOUR_G: return "COLOUR G";
	case GeneMarker::GM_COLOUR_B: return "COLOUR B";
	case GeneMarker::GM_SPEED_MOVEMENT: return "SPEED MOVEMENT";
	case GeneMarker::GM_SPEED_ROTATION: return "SPEED ROTATION";
	case GeneMarker::GM_BODY_STEPS: return "BODY STEPS";
	case GeneMarker::GM_BODY_MUTATION_RATE: return "BODY MUTATION RATE";
	case GeneMarker::GM_BODY_OFFSETX: return "BODY OFFSET X";
	case GeneMarker::GM_BODY_OFFSETY: return "BODY OFFSET Y";
	default:      return "UNKNOWN GENE";
	}
}

inline std::tuple<int, int> geneMarkerLimits(GeneMarker v)
{
	switch (v)
	{
	case GeneMarker::GM_SIZE:   return std::tuple<int, int>(0, 75);
	case GeneMarker::GM_COLOUR_R:
	case GeneMarker::GM_COLOUR_G:
	case GeneMarker::GM_COLOUR_B: return std::tuple<int, int>(0, 255);
	case GeneMarker::GM_SPEED_MOVEMENT: return std::tuple<int, int>(5, 50);
	case GeneMarker::GM_SPEED_ROTATION: return std::tuple<int, int>(5, 50);
	case GeneMarker::GM_BODY_STEPS: return std::tuple<int, int>(6, 20);
	case GeneMarker::GM_LEAF_STEPS: return std::tuple<int, int>(8, 40);
	case GeneMarker::GM_LEAF_LAYERS: return std::tuple<int, int>(1, 8);
	case GeneMarker::GM_BUSH_COUNT: return std::tuple<int, int>(5, 12);
	default:      return std::tuple<int, int>(0, 0); // no limits
	}
}