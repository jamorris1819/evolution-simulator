#pragma once

enum class GeneMarker
{
	GM_SIZE,
	GM_COLOUR_R,
	GM_COLOUR_G,
	GM_COLOUR_B,
	GM_SPEED_MOVEMENT,
	GM_SPEED_ROTATION,

	// Leave at end for count.
	GENE_COUNT
};

inline const char* ToString(GeneMarker v)
{
	switch (v)
	{
	case GeneMarker::GM_SIZE:   return "SIZE";
	case GeneMarker::GM_COLOUR_R:   return "COLOUR R";
	case GeneMarker::GM_COLOUR_G: return "COLOUR G";
	case GeneMarker::GM_COLOUR_B: return "COLOUR B";
	case GeneMarker::GM_SPEED_MOVEMENT: return "SPEED MOVEMENT";
	case GeneMarker::GM_SPEED_ROTATION: return "SPEED ROTATION";
	default:      return "UNKNOWN GENE";
	}
}