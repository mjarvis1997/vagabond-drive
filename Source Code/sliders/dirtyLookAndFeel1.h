/*
  ==============================================================================
    Vagabond Drive

    Michael Jarvis

    Ragtag Records 2020
  ==============================================================================
*/
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../resources/pngBinaries.h"

class DirtyLookAndFeel1 : public LookAndFeel_V4
{
    public:
        DirtyLookAndFeel1();
        
        void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
        
    private:
        Image image_knob_strip_png;
      
};



