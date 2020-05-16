/*
  ==============================================================================
    Vagabond Drive

    Michael Jarvis

    Ragtag Records 2020
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DirtyDistortionAudioProcessorEditor::DirtyDistortionAudioProcessorEditor (DirtyDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
   
    ////knob styling
    driveKnob.setLookAndFeel(&dirtyLookAndFeel1);
    driveKnob.setSliderStyle(Slider::Rotary);
    driveKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 16);
    addAndMakeVisible(driveKnob);
    
    blendKnob.setLookAndFeel(&dirtyLookAndFeel1);
    blendKnob.setSliderStyle(Slider::Rotary);
    blendKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 16);
    addAndMakeVisible(blendKnob);
    
    inputKnob.setLookAndFeel(&dirtyLookAndFeel1);
    inputKnob.setSliderStyle(Slider::Rotary);
    inputKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 16);
    addAndMakeVisible(inputKnob);

    outputKnob.setLookAndFeel(&dirtyLookAndFeel1);
    outputKnob.setSliderStyle(Slider::Rotary);
    outputKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 16);
    addAndMakeVisible(outputKnob);

    //attaching processor state to knobs
    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Drive", driveKnob);
    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Blend", blendKnob);
    inputAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Input", inputKnob);
    outputAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Output", outputKnob);
    
    //load image binaries from memory
    image_drive_background_png = ImageCache::getFromMemory(pngBinaries::drive_background_png, pngBinaries::drive_background_pngSize);

    //standard knob size
    sKnobSize = 64;

    //half knob size
    hKnobSize = sKnobSize / 2;
    
    //editor size
    width = 300;
    height = 200;

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (width, height);
}

DirtyDistortionAudioProcessorEditor::~DirtyDistortionAudioProcessorEditor()
{
}

//==============================================================================
void DirtyDistortionAudioProcessorEditor::paint (Graphics& g)
{
    //draw background image
    g.drawImage(image_drive_background_png, 0, 0, 300, 200, 0, 0, 300, 200);

    //set color & font size
    g.setColour (Colours::white);
    g.setFont (15.0f);
    
}


void DirtyDistortionAudioProcessorEditor::resized()
{
    //set location/size of knobs
    driveKnob.setBounds(92 - hKnobSize, 64 - hKnobSize, sKnobSize, sKnobSize);
    inputKnob.setBounds(211 - hKnobSize, 64 - hKnobSize, sKnobSize, sKnobSize);
    blendKnob.setBounds(58 - hKnobSize, 145 - hKnobSize, sKnobSize, sKnobSize);
    outputKnob.setBounds(245 - hKnobSize, 145 - hKnobSize, sKnobSize, sKnobSize);
}


