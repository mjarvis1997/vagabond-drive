/*
  ==============================================================================
    Vagabond Drive

    Michael Jarvis

    Ragtag Records 2020
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "resources/pngBinaries.h"
#include "sliders/DirtyLookAndFeel1.h"


//==============================================================================
/**
*/
class DirtyDistortionAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DirtyDistortionAudioProcessorEditor (DirtyDistortionAudioProcessor&);
    ~DirtyDistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    //images
    Image image_drive_background_png;

    //default sizes
    int width, height;
    int sKnobSize, hKnobSize;

    //sliders
    Slider driveKnob;
    Slider blendKnob;
    Slider inputKnob;
    Slider outputKnob;

    //slider attachments
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> inputAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> outputAttachment;
    
    //instance of look and feel with custom png: knob1
    DirtyLookAndFeel1 dirtyLookAndFeel1;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DirtyDistortionAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirtyDistortionAudioProcessorEditor)
};
