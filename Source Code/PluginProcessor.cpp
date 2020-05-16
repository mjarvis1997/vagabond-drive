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
DirtyDistortionAudioProcessor::DirtyDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //init state with value tree
    state = new AudioProcessorValueTreeState(*this, nullptr);

    //attach parameters to value tree
    state->createAndAddParameter("Drive", "Drive", "Drive", NormalisableRange<float>(0.f, 100.f, 0.02), 20, nullptr, nullptr );
    state->createAndAddParameter("Input", "Input", "Input", NormalisableRange<float>(0.f, 100.f, 0.02), 0, nullptr, nullptr);
    state->createAndAddParameter("Blend", "Blend", "Blend", NormalisableRange<float>(0.f, 100.f, 0.02), 50, nullptr, nullptr);
    state->createAndAddParameter("Output", "Output", "Output", NormalisableRange<float>(0.f, 100.f, 0.02), 15, nullptr, nullptr);

    state->state = ValueTree("Drive");
    state->state = ValueTree("Input");
    state->state = ValueTree("Blend");
    state->state = ValueTree("Output");
    
}

DirtyDistortionAudioProcessor::~DirtyDistortionAudioProcessor()
{
}

//==============================================================================
const String DirtyDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DirtyDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DirtyDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DirtyDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DirtyDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DirtyDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DirtyDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DirtyDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String DirtyDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DirtyDistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DirtyDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DirtyDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DirtyDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DirtyDistortionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    //knob parameters
    float drive = *state->getRawParameterValue("Drive");
    float input = *state->getRawParameterValue("Input");
    float blend = *state->getRawParameterValue("Blend");
    float output = *state->getRawParameterValue("Output");

    //adjust parameter values based on relative weights
    drive /= 2;
    blend /= 100;
    input /= 5;
    output /= 33.3;
    

    //iterate through each input channel
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //get write pointers to this channels buffer
        float* channelData = buffer.getWritePointer (channel);

        //iterate through each sample in the buffer
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            //store clean signal
            float cleanSig = *channelData;

            //apply drive multiplier and input
            *channelData *= ((drive) + (drive * input));
            
            //blend clean and dirty signal
            *channelData = ((((2.f / float_Pi) * atan(*channelData)) * (blend)) + (cleanSig * (1.f - blend)));

            //apply output mulitplier
            *channelData *= output;

            //increment to next pointer
            ++channelData;
        }
    }
}

//necessary for attaching parameters to sliders
AudioProcessorValueTreeState& DirtyDistortionAudioProcessor::getState()
{
    return *state;
}

//==============================================================================
bool DirtyDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DirtyDistortionAudioProcessor::createEditor()
{
    return new DirtyDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void DirtyDistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    //store state with parameters in memory block
    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void DirtyDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    //fills value tree with state data
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

    //store tree in state if it is valid
    if (tree.isValid())
    {
        state->state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DirtyDistortionAudioProcessor();
}
