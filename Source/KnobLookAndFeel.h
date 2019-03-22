/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 21 Mar 2019 5:47:22pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once

class KnobLookAndFeel : public LookAndFeel_V4
{
public:
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		// Radius of knob
		auto radius = jmin(width / 2, height / 2) - 10.0f;
		radius *= 0.8f;
		// Centre point (centreX, centreY) of knob
		auto centreX = x + width * 0.5f;
		auto centreY = y + height * 0.5f;

		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		// current angle of the slider
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// Draw path of the slider backgound (in darker background colour)
		Path backgroundArc;
		backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
		Colour myColour = findColour(0x1005700);
		myColour = myColour.darker(.8f);
		g.setColour(myColour);
		g.strokePath(backgroundArc, PathStrokeType(3.f, PathStrokeType::curved, PathStrokeType::rounded));
		// Draw path of slider foreground (in white)
		Path foregroundArc;
		foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
		g.setColour(Colours::white);
		g.strokePath(foregroundArc, PathStrokeType(3.f, PathStrokeType::curved, PathStrokeType::rounded));

		// Pointer
		Path p;
		auto pointerLength = radius * 1.f;
		auto pointerThickness = 3.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
		g.setColour(Colours::white);
		g.fillPath(p);

		// Draw slider value
		g.setFont(12);
		String value = "";
		if (slider.getValue() > 1000)
			value = static_cast<String> (round(slider.getValue() / 10.f) / 100.f) + " s";
		else
			value = static_cast<String> (round(slider.getValue() * 100.f) / 100.f);
		g.drawFittedText(value + (slider.getValue() < 1000 ? slider.getTextValueSuffix() : ""), centreX - 30.f, height - 10.f, 60.f, 10.f, Justification::centred, 1);
	}
};