/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxImGui.h"

#define PARAMETER_ARRAY_LENGTH 16

class GuiApp: public ofBaseApp, public ofxMidiListener {
public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	
	
	/**midi!**/
	void midibiz();
	void midiSetup();
	void newMidiMessage(ofxMidiMessage& eventArgs);
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10;

	/**gui**/
	ofxImGui::Gui gui;

	/*Arrays & midi 2 gui*/
	void allArrayClear();
	void midi2Gui(bool midiActive[], float params[], bool midiSwitch);
	
	//reset
	void resetAll();
	void allButtonsClear();
	
	float sdFixX=0;
	float hdFixY=0;	
	//check and delete all these later	
	float testParameter=0;
	float cribX=0;
	float cribY=0;
	
	//OK LETS FIX ASPECT & POSITIONS FOR REAL THIS TIMEEE
	float input1XFix=0;
	float input1YFix=0;
	float input1ScaleFix=0;
	
	
	//global coefficients
	
	
	
	
	
	
	//i think we trash these?
	float chXDisplace=640.0;
	float chYDisplace=480.0;
	float chZDisplace=1.0;
	//delete?
	float ch1XDisplace=0;
	float ch1YDisplace=0;
	float ch1ZDisplace=0;
	
	
	
	void randomizeControls();
	
	bool secretMenuSwitch=1;
	void block1ResetAll();
	
	
	
	
	
	//ch1 and ch2 input resets
	void block1InputResetAll();
	
	//ch1 parameters
	int ch1InputSelect=0; //0 is input1, 1 is input2
	bool ch1AspectRatioSwitch=0; //0 is 4:3, 1 is 16:9
	
	//ch1 midi syncing & parameter bizness
	bool ch1AdjustMidiGui=0;
	bool ch1AdjustReset=0;
	float ch1Adjust[PARAMETER_ARRAY_LENGTH];
	bool ch1AdjustMidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool ch1HMirror=0;
	bool ch1VMirror=0;
	bool ch1HueInvert=0;
	bool ch1SaturationInvert=0;
	bool ch1BrightInvert=0;
	int ch1GeoOverflow=0;
	bool ch1HFlip=0;
	bool ch1VFlip=0;
	bool ch1RGBInvert=0;
	bool ch1Solarize=0;
	

	
	//ch1 adjust lfo midi syncing & parameter bizness
	bool ch1AdjustLfoMidiGui=0;
	bool ch1AdjustLfoReset=0;
	float ch1AdjustLfo[PARAMETER_ARRAY_LENGTH];
	bool ch1AdjustLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	//ch2 parameters
	int ch2InputSelect=1; //0 is input1, 1 is input2
	bool ch2AspectRatioSwitch=0; //0 is 4:3, 1 is 16:9
	
	//ch2 pmidi syncing & paramater bizness
	bool ch2MixAndKeyMidiGui=0;
	bool ch2MixAndKeyReset=0;
	float ch2MixAndKey[PARAMETER_ARRAY_LENGTH];
	bool ch2MixAndKeyMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int ch2KeyOrder=0;
	int ch2MixType=0;
	int ch2KeyMode=0;
	int ch2MixOverflow=0;
	
	//ch2 pmidi syncing & paramater bizness
	bool ch2MixAndKeyLfoMidiGui=0;
	bool ch2MixAndKeyLfoReset=0;
	float ch2MixAndKeyLfo[PARAMETER_ARRAY_LENGTH];
	bool ch2MixAndKeyLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	//ch2 midi syncing & parameter bizness
	bool ch2AdjustMidiGui=0;
	bool ch2AdjustReset=0;
	float ch2Adjust[PARAMETER_ARRAY_LENGTH];
	bool ch2AdjustMidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool ch2HMirror=0;
	bool ch2VMirror=0;
	bool ch2HueInvert=0;
	bool ch2SaturationInvert=0;
	bool ch2BrightInvert=0;
	int ch2GeoOverflow=0;
	bool ch2HFlip=0;
	bool ch2VFlip=0;
	bool ch2RGBInvert=0;
	bool ch2Solarize=0;
	
	//ch2 adjust lfo midi syncing & parameter bizness
	bool ch2AdjustLfoMidiGui=0;
	bool ch2AdjustLfoReset=0;
	float ch2AdjustLfo[PARAMETER_ARRAY_LENGTH];
	bool ch2AdjustLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb1 reset
	void fb1ResetAll();
	bool fb1FramebufferClearSwitch=0;
	
	
	//fb1 mixnkey pmidi syncing & paramater bizness
	bool fb1MixAndKeyMidiGui=0;
	bool fb1MixAndKeyReset=0;
	float fb1MixAndKey[PARAMETER_ARRAY_LENGTH];
	bool fb1MixAndKeyMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int fb1KeyOrder=0;
	int fb1MixType=0;
	int fb1KeyMode=0;
	int fb1MixOverflow=0;
	
	int fb1DelayTime=1;
	
	//fb1 geo1 pmidi syncing & paramater bizness
	bool fb1Geo1MidiGui=0;
	bool fb1Geo1Reset=0;
	float fb1Geo1[PARAMETER_ARRAY_LENGTH];
	bool fb1Geo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool fb1HMirror=0;
	bool fb1VMirror=0;
	bool fb1HFlip=0;
	bool fb1VFlip=0;
	bool fb1RotateMode=0;
	int fb1GeoOverflow=0;
	

	//fb1 color1 pmidi syncing & paramater bizness
	bool fb1Color1MidiGui=0;
	bool fb1Color1Reset=0;
	float fb1Color1[PARAMETER_ARRAY_LENGTH];
	bool fb1Color1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool fb1HueInvert=0;
	bool fb1SaturationInvert=0;
	bool fb1BrightInvert=0;	
	
	//fb1 filters pmidi syncing & paramater bizness
	bool fb1FiltersMidiGui=0;
	bool fb1FiltersReset=0;
	float fb1Filters[PARAMETER_ARRAY_LENGTH];
	bool fb1FiltersMidiActive[PARAMETER_ARRAY_LENGTH];
	
	
	//fb1 LFO
	//fb1 mixnkey pmidi syncing & paramater bizness
	bool fb1MixAndKeyLfoMidiGui=0;
	bool fb1MixAndKeyLfoReset=0;
	float fb1MixAndKeyLfo[PARAMETER_ARRAY_LENGTH];
	bool fb1MixAndKeyLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb1 Geo1Lfo1 pmidi syncing & paramater bizness
	bool fb1Geo1Lfo1MidiGui=0;
	bool fb1Geo1Lfo1Reset=0;
	float fb1Geo1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool fb1Geo1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb1 Geo1Lfo2 pmidi syncing & paramater bizness
	bool fb1Geo1Lfo2MidiGui=0;
	bool fb1Geo1Lfo2Reset=0;
	float fb1Geo1Lfo2[PARAMETER_ARRAY_LENGTH];
	bool fb1Geo1Lfo2MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb1 Color1Lfo1 pmidi syncing & paramater bizness
	bool fb1Color1Lfo1MidiGui=0;
	bool fb1Color1Lfo1Reset=0;
	float fb1Color1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool fb1Color1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//geometrical animations
	//hypercube
	bool block1HypercubeSwitch=0;
	float hypercube_size = 1.0;
    float hypercube_theta_rate=0.01;
    float hypercube_phi_rate=0.01;
	
	//line 
	bool block1LineSwitch=0;
	
	//seven star
	bool block1SevenStar1Switch=0;
	
	//lissaball
	bool block1LissaBallSwitch=0;
	int drawMode=3;
	
	
	//BLOCK2 input
	void block2ResetAll();
	
	void block2InputResetAll();
	
	int block2InputSelect=2;
	bool block2InputAspectRatioSwitch=0;
	
	
	//block2Input midi syncing & parameter bizness
	bool block2InputAdjustMidiGui=0;
	bool block2InputAdjustReset=0;
	float block2InputAdjust[PARAMETER_ARRAY_LENGTH];
	bool block2InputAdjustMidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool block2InputHMirror=0;
	bool block2InputVMirror=0;
	bool block2InputHueInvert=0;
	bool block2InputSaturationInvert=0;
	bool block2InputBrightInvert=0;
	int block2InputGeoOverflow=0;
	bool block2InputHFlip=0;
	bool block2InputVFlip=0;
	bool block2InputRGBInvert=0;
	bool block2InputSolarize=0;
	
	
	//block2Input adjust lfo midi syncing & parameter bizness
	bool block2InputAdjustLfoMidiGui=0;
	bool block2InputAdjustLfoReset=0;
	float block2InputAdjustLfo[PARAMETER_ARRAY_LENGTH];
	bool block2InputAdjustLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	
	
	void fb2ResetAll();
	bool fb2FramebufferClearSwitch=0;
	
	//fb2 mixnkey pmidi syncing & paramater bizness
	bool fb2MixAndKeyMidiGui=0;
	bool fb2MixAndKeyReset=0;
	float fb2MixAndKey[PARAMETER_ARRAY_LENGTH];
	bool fb2MixAndKeyMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int fb2KeyOrder=0;
	int fb2MixType=0;
	int fb2KeyMode=0;
	int fb2MixOverflow=0;
	
	int fb2DelayTime=1;
	
	//fb2 geo1 pmidi syncing & paramater bizness
	bool fb2Geo1MidiGui=0;
	bool fb2Geo1Reset=0;
	float fb2Geo1[PARAMETER_ARRAY_LENGTH];
	bool fb2Geo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool fb2HMirror=0;
	bool fb2VMirror=0;
	bool fb2HFlip=0;
	bool fb2VFlip=0;
	bool fb2RotateMode=0;
	int fb2GeoOverflow=0;

	//fb2 color1 pmidi syncing & paramater bizness
	bool fb2Color1MidiGui=0;
	bool fb2Color1Reset=0;
	float fb2Color1[PARAMETER_ARRAY_LENGTH];
	bool fb2Color1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool fb2HueInvert=0;
	bool fb2SaturationInvert=0;
	bool fb2BrightInvert=0;	
	
	//fb2 filters pmidi syncing & paramater bizness
	bool fb2FiltersMidiGui=0;
	bool fb2FiltersReset=0;
	float fb2Filters[PARAMETER_ARRAY_LENGTH];
	bool fb2FiltersMidiActive[PARAMETER_ARRAY_LENGTH];
	
	
	//fb2 LFO
	//fb2 mixnkey pmidi syncing & paramater bizness
	bool fb2MixAndKeyLfoMidiGui=0;
	bool fb2MixAndKeyLfoReset=0;
	float fb2MixAndKeyLfo[PARAMETER_ARRAY_LENGTH];
	bool fb2MixAndKeyLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb2 Geo1Lfo1 pmidi syncing & paramater bizness
	bool fb2Geo1Lfo1MidiGui=0;
	bool fb2Geo1Lfo1Reset=0;
	float fb2Geo1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool fb2Geo1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb2 Geo1Lfo2 pmidi syncing & paramater bizness
	bool fb2Geo1Lfo2MidiGui=0;
	bool fb2Geo1Lfo2Reset=0;
	float fb2Geo1Lfo2[PARAMETER_ARRAY_LENGTH];
	bool fb2Geo1Lfo2MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//fb2 Color1Lfo1 pmidi syncing & paramater bizness
	bool fb2Color1Lfo1MidiGui=0;
	bool fb2Color1Lfo1Reset=0;
	float fb2Color1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool fb2Color1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block2 geometrical animations
	//hypercube
	bool block2HypercubeSwitch=0;
	
	//line 
	bool block2LineSwitch=0;
	
	//seven star
	bool block2SevenStar1Switch=0;
	
	//lissaball
	bool block2LissaBallSwitch=0;
	
	//BLOCK3
	
	
	void block3ResetAll();
	
	
	
	
	//block1 Geo pmidi syncing & paramater bizness
	bool block1GeoMidiGui=0;
	bool block1GeoReset=0;
	float block1Geo[PARAMETER_ARRAY_LENGTH];
	bool block1GeoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int block1GeoOverflow=0;
	bool block1HMirror=0;
	bool block1VMirror=0;
	bool block1HFlip=0;
	bool block1VFlip=0;
	bool block1RotateMode=0;
	
	//block1 Colorize
	bool block1ColorizeMidiGui=0;
	bool block1ColorizeReset=0;
	float block1Colorize[PARAMETER_ARRAY_LENGTH];
	bool block1ColorizeMidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool block1ColorizeSwitch=0;
	bool block1ColorizeHSB_RGB=0;//0 is hsb, 1 is rgb
	
	//block1 filters pmidi syncing & paramater bizness
	bool block1FiltersMidiGui=0;
	bool block1FiltersReset=0;
	float block1Filters[PARAMETER_ARRAY_LENGTH];
	bool block1FiltersMidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block1 Geo1Lfo1 pmidi syncing & paramater bizness
	bool block1Geo1Lfo1MidiGui=0;
	bool block1Geo1Lfo1Reset=0;
	float block1Geo1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool block1Geo1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block1 Geo1Lfo2 pmidi syncing & paramater bizness
	bool block1Geo1Lfo2MidiGui=0;
	bool block1Geo1Lfo2Reset=0;
	float block1Geo1Lfo2[PARAMETER_ARRAY_LENGTH];
	bool block1Geo1Lfo2MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block1 ColorizeLfo1
	bool block1ColorizeLfo1MidiGui=0;
	bool block1ColorizeLfo1Reset=0;
	float block1ColorizeLfo1[PARAMETER_ARRAY_LENGTH];
	bool block1ColorizeLfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block1 ColorizeLfo2
	bool block1ColorizeLfo2MidiGui=0;
	bool block1ColorizeLfo2Reset=0;
	float block1ColorizeLfo2[PARAMETER_ARRAY_LENGTH];
	bool block1ColorizeLfo2MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block1 ColorizeLfo3
	bool block1ColorizeLfo3MidiGui=0;
	bool block1ColorizeLfo3Reset=0;
	float block1ColorizeLfo3[PARAMETER_ARRAY_LENGTH];
	bool block1ColorizeLfo3MidiActive[PARAMETER_ARRAY_LENGTH];
	






	//i think this is trash
	//block1 Color1Lfo1 pmidi syncing & paramater bizness
	bool block1Color1Lfo1MidiGui=0;
	bool block1Color1Lfo1Reset=0;
	float block1Color1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool block1Color1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];


	
	
	
	
	//block2 Geo pmidi syncing & paramater bizness
	bool block2GeoMidiGui=0;
	bool block2GeoReset=0;
	float block2Geo[PARAMETER_ARRAY_LENGTH];
	bool block2GeoMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int block2GeoOverflow=0;
	bool block2HMirror=0;
	bool block2VMirror=0;
	bool block2HFlip=0;
	bool block2VFlip=0;
	bool block2RotateMode=0;
	
	//block2 Colorize
	bool block2ColorizeMidiGui=0;
	bool block2ColorizeReset=0;
	float block2Colorize[PARAMETER_ARRAY_LENGTH];
	bool block2ColorizeMidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool block2ColorizeSwitch=0;
	bool block2ColorizeHSB_RGB=0;
	
	//block2 filters pmidi syncing & paramater bizness
	bool block2FiltersMidiGui=0;
	bool block2FiltersReset=0;
	float block2Filters[PARAMETER_ARRAY_LENGTH];
	bool block2FiltersMidiActive[PARAMETER_ARRAY_LENGTH];
		
	//block2 Geo1Lfo1 pmidi syncing & paramater bizness
	bool block2Geo1Lfo1MidiGui=0;
	bool block2Geo1Lfo1Reset=0;
	float block2Geo1Lfo1[PARAMETER_ARRAY_LENGTH];
	bool block2Geo1Lfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block2 Geo1Lfo2 pmidi syncing & paramater bizness
	bool block2Geo1Lfo2MidiGui=0;
	bool block2Geo1Lfo2Reset=0;
	float block2Geo1Lfo2[PARAMETER_ARRAY_LENGTH];
	bool block2Geo1Lfo2MidiActive[PARAMETER_ARRAY_LENGTH];

	//block2 ColorizeLfo1
	bool block2ColorizeLfo1MidiGui=0;
	bool block2ColorizeLfo1Reset=0;
	float block2ColorizeLfo1[PARAMETER_ARRAY_LENGTH];
	bool block2ColorizeLfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block2 ColorizeLfo2
	bool block2ColorizeLfo2MidiGui=0;
	bool block2ColorizeLfo2Reset=0;
	float block2ColorizeLfo2[PARAMETER_ARRAY_LENGTH];
	bool block2ColorizeLfo2MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//block2 ColorizeLfo3
	bool block2ColorizeLfo3MidiGui=0;
	bool block2ColorizeLfo3Reset=0;
	float block2ColorizeLfo3[PARAMETER_ARRAY_LENGTH];
	bool block2ColorizeLfo3MidiActive[PARAMETER_ARRAY_LENGTH];
	

	
	//matrix mixer
	bool matrixMixMidiGui=0;
	bool matrixMixReset=0;
	float matrixMix[PARAMETER_ARRAY_LENGTH];
	bool matrixMixMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int matrixMixType=0;
	int matrixMixOverflow=0;
		
	//final mix pmidi syncing & paramater bizness
	bool finalMixAndKeyMidiGui=0;
	bool finalMixAndKeyReset=0;
	float finalMixAndKey[PARAMETER_ARRAY_LENGTH];
	bool finalMixAndKeyMidiActive[PARAMETER_ARRAY_LENGTH];
	
	int finalKeyOrder=0;
	int finalMixType=0;
	int finalKeyMode=0;
	int finalMixOverflow=0;
	
	//matrix mixer lfo
	bool matrixMixLfo1MidiGui=0;
	bool matrixMixLfo1Reset=0;
	float matrixMixLfo1[PARAMETER_ARRAY_LENGTH];
	bool matrixMixLfo1MidiActive[PARAMETER_ARRAY_LENGTH];
	
	bool matrixMixLfo2MidiGui=0;
	bool matrixMixLfo2Reset=0;
	float matrixMixLfo2[PARAMETER_ARRAY_LENGTH];
	bool matrixMixLfo2MidiActive[PARAMETER_ARRAY_LENGTH];
	
	//final mixnkey pmidi syncing & paramater bizness
	bool finalMixAndKeyLfoMidiGui=0;
	bool finalMixAndKeyLfoReset=0;
	float finalMixAndKeyLfo[PARAMETER_ARRAY_LENGTH];
	bool finalMixAndKeyLfoMidiActive[PARAMETER_ARRAY_LENGTH];
	


};

