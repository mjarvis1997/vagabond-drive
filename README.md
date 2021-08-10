# vagabond-drive
Audio plugin in .vst3 format

Built in C++ with JUCE

Custom GUI created with Adobe Illustrator

![alt text](https://i.imgur.com/6HLx8G7.png)

## What does it do?
Distorts sound based on sinusoidal interpolation

Works well with guitars and synthesizers

## How do I use it?
Load the vst3 plugin into the Digital Audio Workshop or software of your choice. For most cases you simply need to add this to your plugin directory, and refresh the plugin cache

## What do the knobs do?
The knobs can be used with mouse input, or direct keyboard entry.
There are four knobs which allow you to tweak the sound to your liking: 

### Output 
Controls the overall volume (whether dirty or clean)

### Blend 
Controls the ratio of clean input and distorted audio (it is common to use a mixture of the two)

### Drive 
Controls the intensity of the drive effect

Low values add subtle grit and texture, higher values create more harsh changes in tone

### Dirty 
Controls the intensity, but has more impact than the Drive knob

Use when you want extreme distortion, can be dissonant in some cases

## How do I make changes or build the source code myself?
The source code is compiled with the help of Projucer. Create an "audio plugin" via their interface and replace the existing source code with mine.

