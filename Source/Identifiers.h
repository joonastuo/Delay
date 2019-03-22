/*
  ==============================================================================

    Identifiers.h
    Created: 14 Mar 2019 7:37:42am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

namespace IDs {
	// JUCE Strings
	#define DECLARE_ID(name) const juce::String name (#name);

	DECLARE_ID(time)		// Delay time (0s - 2s)
	DECLARE_ID(wetness)		// Dry / wet -ratio (0% - 100%)
	DECLARE_ID(feedback)	// Feedback gain (-100% - 100%)

	#undef DECLARE_ID
}