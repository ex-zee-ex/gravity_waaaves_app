
#include "GuiApp.h"

#include "iostream"

#define MIDI_MAGIC 63.50f
#define PARAMETER_THRESHOLD .035f

const int arrayLength=16;
float midiCC[arrayLength];
bool coutMidiSwitch=0;

const int pastFramesSize=120;

float tweakHue=0;
float tweakSat=0;
float tweakBri=0;

float sliderWidth=80;
float yPosAdjust=0;

bool debugOn=true;

int blockSelectHsb=1;


//testing out the node closing thingy
static int nodeToClose=-1;
static int currentNode=-1;

void GuiApp::setup(){
	
	ofBackground(0);

	gui.setup();
	midiSetup();
	allArrayClear();
	
	
}

//--------------------------------------------------------------

void GuiApp::allArrayClear(){
//should we clear all the midiGui switches here too?/ probably...
	for(int i=0;i<PARAMETER_ARRAY_LENGTH;i++){
		//BLOCK1
		
		//input adjust and mix
		ch1Adjust[i]=0.0f;
		ch1AdjustMidiActive[i]=0;
		
		ch2MixAndKey[i]=0.0f;
		ch2MixAndKeyMidiActive[i]=0;
		
		ch2MixAndKeyLfo[i]=0.0f;
		ch2MixAndKeyLfoMidiActive[i]=0;
		
		ch2Adjust[i]=0.0f;
		ch2AdjustMidiActive[i]=0;
		
		//input lfo
		ch1AdjustLfo[i]=0.0f;
		ch1AdjustLfoMidiActive[i]=0;
		
		ch2AdjustLfo[i]=0.0f;
		ch2AdjustLfoMidiActive[i]=0;
		
		//fb1 param
		fb1MixAndKey[i]=0.0f;
		fb1MixAndKeyMidiActive[i]=0;
		
		fb1Geo1[i]=0.0f;
		fb1Geo1MidiActive[i]=0;
		
		fb1Color1[i]=0.0f;
		fb1Color1MidiActive[i]=0;
		
		fb1Filters[i]=0.0f;
		fb1FiltersMidiActive[i]=0;
		
		//fb1 lfo
		fb1MixAndKeyLfo[i]=0.0f;
		fb1MixAndKeyLfoMidiActive[i]=0;
		
		fb1Geo1Lfo1[i]=0.0f;
		fb1Geo1Lfo1MidiActive[i]=0;
		
		fb1Geo1Lfo2[i]=0.0f;
		fb1Geo1Lfo2MidiActive[i]=0;
		
		fb1Color1Lfo1[i]=0.0f;
		fb1Color1Lfo1MidiActive[i]=0;
		
		//BLOCK2
		
		//input adjust
		block2InputAdjust[i]=0.0f;
		block2InputAdjustMidiActive[i]=0;
		
		//input lfo
		block2InputAdjustLfo[i]=0.0f;
		block2InputAdjustLfoMidiActive[i]=0;

		//fb2 param
		fb2MixAndKey[i]=0.0f;
		fb2MixAndKeyMidiActive[i]=0;
		
		fb2Geo1[i]=0.0f;
		fb2Geo1MidiActive[i]=0;
		
		fb2Color1[i]=0.0f;
		fb2Color1MidiActive[i]=0;
		
		fb2Filters[i]=0.0f;
		fb2FiltersMidiActive[i]=0;
		
		//fb2 lfo
		fb2MixAndKeyLfo[i]=0.0f;
		fb2MixAndKeyLfoMidiActive[i]=0;
		
		fb2Geo1Lfo1[i]=0.0f;
		fb2Geo1Lfo1MidiActive[i]=0;
		
		fb2Geo1Lfo2[i]=0.0f;
		fb2Geo1Lfo2MidiActive[i]=0;
		
		fb2Color1Lfo1[i]=0.0f;
		fb2Color1Lfo1MidiActive[i]=0;
		
		//BLOCK3 
		
		//block1 param
		block1Geo[i]=0.0f;
		block1GeoMidiActive[i]=0;
		
		block1Colorize[i]=0.0f;
		block1ColorizeMidiActive[i]=0;
		
		block1Filters[i]=0.0f;
		block1FiltersMidiActive[i]=0;
		
		//block1 lfo
		block1Geo1Lfo1[i]=0.0f;
		block1Geo1Lfo1MidiActive[i]=0;
		
		block1Geo1Lfo2[i]=0.0f;
		block1Geo1Lfo2MidiActive[i]=0;
		
		block1ColorizeLfo1[i]=0.0f;
		block1ColorizeLfo1MidiActive[i]=0;
		
		block1ColorizeLfo2[i]=0.0f;
		block1ColorizeLfo2MidiActive[i]=0;
		
		block1ColorizeLfo3[i]=0.0f;
		block1ColorizeLfo3MidiActive[i]=0;
		
		//block2 params
		block2Geo[i]=0.0f;
		block2GeoMidiActive[i]=0;
		
		block2Colorize[i]=0.0f;
		block2ColorizeMidiActive[i]=0;
		
		block2Filters[i]=0.0f;
		block2FiltersMidiActive[i]=0;
		
		//block2 lfo
		block2Geo1Lfo1[i]=0.0f;
		block2Geo1Lfo1MidiActive[i]=0;
		
		block2Geo1Lfo2[i]=0.0f;
		block2Geo1Lfo2MidiActive[i]=0;
		
		block2ColorizeLfo1[i]=0.0f;
		block2ColorizeLfo1MidiActive[i]=0;
		
		block2ColorizeLfo2[i]=0.0f;
		block2ColorizeLfo2MidiActive[i]=0;
		
		block2ColorizeLfo3[i]=0.0f;
		block2ColorizeLfo3MidiActive[i]=0;
		
		
		//final mix params	
		matrixMix[i]=0.0f;
		matrixMixMidiActive[i]=0;
		
		finalMixAndKey[i]=0.0f;
		finalMixAndKeyMidiActive[i]=0;
		
		//final mix lfo
		matrixMixLfo1[i]=0.0f;
		matrixMixLfo1MidiActive[i]=0;
		
		matrixMixLfo2[i]=0.0f;
		matrixMixLfo2MidiActive[i]=0;
		
		finalMixAndKeyLfo[i]=0.0f;
		finalMixAndKeyLfoMidiActive[i]=0;
		
		
	}

}

//--------------------------------------------------------------
void GuiApp::update(){
	midibiz();
}

//--------------------------------------------------------------
//maps midi messages in to parameters of each gui
//something to think about: do we want to keep all of the paramters at -1 to 1 in here?
//if we want to be able to scale things in and out then we would want to have coefficient arrays
//as well, and bring the coefficient arrays into here to test

//what to do here: inMessage[] maps to midiCC[]
void GuiApp::midi2Gui(bool midiActive[], float params[], bool midiSwitch) {
	//so lets test the midi2gui thing;
	if (midiSwitch == 1) {
		//test for potentiometer latching

		for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
			if (abs(midiCC[i] - params[i]) < PARAMETER_THRESHOLD) {
				midiActive[i] = 1;
			}
		}

		for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
			if (midiActive[i] == 1) {
				params[i] = midiCC[i];
				if( abs(params[i])<.008 ){params[i]=0.0;}//zero shit out
				//might want to 
			}
		}


	}//endifMIDIGUI TRUE
	if (midiSwitch == 0) {
		for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
			midiActive[i] = 0;
		}
	}//endifMIDIGUI FALSE
}

//--------------------------------------------------------------
void GuiApp::draw(){

	int debugAdjust=0;
	
	if(debugOn==true){
		debugAdjust=40;
	}
	float windowWidthThird=320.0;	
	float windowWidthHalf=420;
	

	auto mainSettings = ofxImGui::Settings();
	//change header colors
    ImGui::StyleColorsDark();

	gui.begin();
	
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGuiWindowFlags window_flags=0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	//window_flags |= ImGuiWindowFlags_NoResize;
	
	
	//strangely enough, when i switched to ImGui::Begin from ImGui::BeginWindow, that seemed to really
	//bonk up the fontGlobalScale thing...
	io.FontGlobalScale=2.0f;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	float block2Hue=.52;
	if(blockSelectHsb==1){
		ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor::HSV(.8f,1.0f,.15f));
	}
	if(blockSelectHsb==2){
		ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor::HSV(block2Hue,1.0f,.1f));
	}
	if(blockSelectHsb==3){
		ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor::HSV(.65, 1.0f, .17f));
	}
	bool value=true;
	bool* p_open =&value;
	ImGui::SetNextWindowSize(ImVec2(1280,720-debugAdjust),ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0,0),ImGuiCond_Once);
	//if (ofxImGui::BeginWindow("++--++--++--++--++--++--++--G*R*A*V*I*T*Y**W*A*A*A*V*E*S--++--++--++--++--++--++", mainSettings, false)) {
	if( ImGui::Begin("++--++--++--++--++--++--++--G*R*A*V*I*T*Y**W*A*A*A*V*E*S--++--++--++--++--++--++", p_open ,window_flags)   ) {
	
		ImGui::PushItemWidth(windowWidthHalf);
		//ImGui::SliderFloat("just a test", &testParameter, 0.0f, 1.0f);
		const char* items10[] = { "draw BLOCK1","draw BLOCK2","draw BLOCK3","drawAllBLOCKS" };
		static int item_drawOutput = 2;
		ImGui::Combo("##what gets drawn", &item_drawOutput, items10, IM_ARRAYSIZE(items10));
		drawMode=item_drawOutput;
		ImGui::SameLine();
		ImGui::Text("+++++++++++++++++++++++++++++++++++++++++++++++++");
		ImGui::SameLine();
		if (ImGui::Button("reset all")) {
			resetAll();
		}
		/*
		ImGui::SameLine();
		
		if (ImGui::Button("randomize controls")) {
			randomizeControls();
		}
		*/
		//add float for random seeding
		/*
		ImGui::Text("Hover over me");
		if (ImGui::IsItemHovered())
            ImGui::SetTooltip("I am a tooltip");
		*/
		
		//ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        //if (ImGui::BeginTabBar("GLOBALTAB", tab_bar_flags))
        if (ImGui::BeginTabBar("GLOBALTAB"))
        {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(.8f, 0.5f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(.8f, 0.6f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(.8f, 0.7f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(.8f, 0.9f, 0.9f));
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(.8f, 0.5f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(.8f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(.8f, 0.9f, 0.9f));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, (ImVec4)ImColor::HSV(.8f, 0.3f, 0.2f));
			ImGui::PushStyleColor(ImGuiCol_Text,(ImVec4)ImColor::HSV(.2f,.25f,1.0f));
			//if (ImGui::CollapsingHeader("--++--<<--**--<<--++--!!--**--++--**--BLOCK_1--**--++--**--!!--++-->>--**-->>--++--")){
			
			ImGui::PushStyleColor(ImGuiCol_Tab, (ImVec4)ImColor::HSV(.8f,.5f,.5f));
			ImGui::PushStyleColor(ImGuiCol_TabActive, (ImVec4)ImColor::HSV(.8f,.9f,.9f));
			ImGui::PushStyleColor(ImGuiCol_TabHovered, (ImVec4)ImColor::HSV(.8f,.7f,.7f));
				
			
			if (ImGui::BeginTabItem("BLOCK_1")){
				blockSelectHsb=1;
				if (ImGui::Button("reset BLOCK_1")) {
					block1ResetAll();
				}
				ImGui::SameLine();
				if (ImGui::Button("reset inputs")) {
					block1InputResetAll();
				}
				ImGui::SameLine();
				if (ImGui::Button("reset fb1")) {
					fb1ResetAll();
				}	
				if (ImGui::BeginTabBar("BLOCK1_subfolders"))
				{
					
					if (ImGui::BeginTabItem("ch1 adjust")){
						const char* items0[] = { "input1","input2" };
						static int item_ch1InputSelect = 0;
						ImGui::Combo("input   ##ch1", &item_ch1InputSelect, items0, IM_ARRAYSIZE(items0));
						ch1InputSelect=item_ch1InputSelect;
						
						ImGui::SameLine();
						//might want to change default to hd and check for SD if that seems more relevant
						ImGui::Checkbox("hd aspect ratio     ##ch1Adjust", &ch1AspectRatioSwitch);
						ImGui::SameLine();
						ImGui::Checkbox("midi/gui      ##ch1Adjust", &ch1AdjustMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset   ##ch1Adjust",&ch1AdjustReset);
						if (ch1AdjustReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								ch1Adjust[i] = 0.0f;
								ch1AdjustMidiActive[i] = 0;
							}
							ch1AdjustReset = 0;
							ch1VMirror=ch1HMirror=ch1VFlip=ch1HFlip=ch1HueInvert=ch1SaturationInvert=ch1BrightInvert=ch1RGBInvert=ch1Solarize=0;
						}
						midi2Gui(ch1AdjustMidiActive, ch1Adjust, ch1AdjustMidiGui);
						ImGui::Separator();
						ImGui::SliderFloat("x <->   ##ch1", &ch1Adjust[0], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("y <->   ##ch1", &ch1Adjust[1], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("z <->   ##ch1", &ch1Adjust[2], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("rotate <-> ##ch1", &ch1Adjust[3], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("hue ^^  ##ch1", &ch1Adjust[4], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sat ^^  ##ch1", &ch1Adjust[5], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("bri ^^  ##ch1", &ch1Adjust[6], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("posterize  ##ch1", &ch1Adjust[7], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("kaleido ##ch1 ", &ch1Adjust[8], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("kaleido slice ##ch1 ", &ch1Adjust[9], -1.0f, 1.0f);
						
						ImGui::Separator();
						ImGui::SliderFloat("blur    ##ch1 ", &ch1Adjust[10], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("blur rad  ##ch1 ", &ch1Adjust[11], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("sharp   ##ch1 ", &ch1Adjust[12], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sharp rad ##ch1 ", &ch1Adjust[13], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("filters boost ##ch1 ", &ch1Adjust[14], -1.0f, 1.0f);
						ImGui::Separator();
						
						static int item_current0 = 0;
						const char* items1[] = { "geo overflow clamp","geo overflow toroid","geo overflow mirror" };
						ImGui::Combo("##ch1 geo overflow", &item_current0, items1, IM_ARRAYSIZE(items1));
						ch1GeoOverflow = item_current0;
						ImGui::Separator();
						ImGui::Checkbox("h mirror        ##ch1",&ch1HMirror);
						ImGui::SameLine();
						ImGui::Checkbox("v mirror        ##ch1",&ch1VMirror);
						ImGui::SameLine();
						ImGui::Checkbox("h flip          ##ch1",&ch1HFlip);
						ImGui::SameLine();
						ImGui::Checkbox("v flip          ##ch1",&ch1VFlip);
						
						ImGui::Separator();
						ImGui::Checkbox("hue invert      ##ch1",&ch1HueInvert);
						ImGui::SameLine();
						ImGui::Checkbox("sat invert      ##ch1",&ch1SaturationInvert);
						ImGui::SameLine();
						ImGui::Checkbox("bri invert      ##ch1",&ch1BrightInvert);
						ImGui::SameLine();
						ImGui::Checkbox("rgb invert      ##ch1",&ch1RGBInvert);
						ImGui::SameLine();
						ImGui::Checkbox("solarize        ##ch1",&ch1Solarize);				
						
						ImGui::EndTabItem();
					}
					
					if (ImGui::BeginTabItem("ch2 mix and key")){
						
						static int item_current0 = 0;
						static int item_current1 = 0;
						static int item_current2 = 0;
						static int item_current3 = 0;
						
						const char* items00[] = { "input1","input2" };
						static int item_ch2InputSelect = 1;
						ImGui::Combo("input          ##ch2", &item_ch2InputSelect, items00, IM_ARRAYSIZE(items00));
						ch2InputSelect=item_ch2InputSelect;
						ImGui::SameLine();
						ImGui::Checkbox("hd aspect ratio ##ch2", &ch2AspectRatioSwitch);
						ImGui::Separator();
						  
						ImGui::Checkbox("midi/gui                 ##ch2", &ch2MixAndKeyMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset          ##ch2",&ch2MixAndKeyReset);
						ImGui::SameLine();
						if (ch2MixAndKeyReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								ch2MixAndKey[i] = 0.0f;
								ch2MixAndKeyMidiActive[i] = 0;
							}
							ch2MixAndKeyReset = 0;
						}
						
						midi2Gui(ch2MixAndKeyMidiActive, ch2MixAndKey, ch2MixAndKeyMidiGui);

						const char* items0[] = { "key order ch1->ch2","key order ch2->ch1" };
						ImGui::Combo("key order ##ch2 ", &item_current0, items0, IM_ARRAYSIZE(items0));
						ch2KeyOrder = item_current0;
						
						ImGui::Separator();
						const char* items1[] = { "linear fade", "additive","difference","multiplicitive","dodge" };
						ImGui::Combo("mix type       ##ch2 ", &item_current1, items1, IM_ARRAYSIZE(items1));
						ch2MixType = item_current1;
						ImGui::SameLine();
						ImGui::SliderFloat("mix ##ch2",&ch2MixAndKey[0],-1.0,1.0);
						ImGui::Separator();
						
						const char* items2[] = { "wrap", "clamp","foldover" };
						ImGui::Combo("overflow       ##ch2Mix", &item_current2, items2, IM_ARRAYSIZE(items2));
						ch2MixOverflow = item_current2;
						ImGui::SameLine();
						const char* items3[] = { "lumakey","chromakey" };
						ImGui::Combo("key mode ##ch2", &item_current3, items3, IM_ARRAYSIZE(items3));
						ch2KeyMode = item_current3;
						ImGui::Separator();
					
						if(ch2KeyMode==0){
						ImGui::SliderFloat("key red        ##ch2",&ch2MixAndKey[1],-1.0,1.0);
						ImGui::SameLine();
						ImGui::SliderFloat("key green      ##ch2",&ch2MixAndKey[1],-1.0,1.0);
						ImGui::Separator();
						ImGui::SliderFloat("key blue       ##ch2",&ch2MixAndKey[1],-1.0,1.0);
						ImGui::SameLine();
						ch2MixAndKey[2]=ch2MixAndKey[3]=ch2MixAndKey[1];
						}
						
						if(ch2KeyMode==1){
						ImGui::SliderFloat("key red        ##ch2",&ch2MixAndKey[1],-1.0,1.0);
						ImGui::SameLine();
						ImGui::SliderFloat("key green      ##ch2",&ch2MixAndKey[2],-1.0,1.0);
						ImGui::Separator();
						ImGui::SliderFloat("key blue       ##ch2",&ch2MixAndKey[3],-1.0,1.0);
						ImGui::SameLine();
						}
						ImGui::ColorButton("testingColorButton 1", ImVec4(ch2MixAndKey[1], ch2MixAndKey[2], ch2MixAndKey[3], 1.0), 0, ImVec2(20, 20));
						ImGui::SameLine();
						ImGui::Text("key value color");
						
						ImGui::Separator();
						ImGui::SliderFloat("key threshold  ##ch2",&ch2MixAndKey[4],-1.0,1.0);
						ImGui::SameLine();
						ImGui::SliderFloat("key soft ##ch2",&ch2MixAndKey[5],-1.0,1.0);
						
						ImGui::EndTabItem();
					}
					
					if (ImGui::BeginTabItem("ch2 adjust")){
						ImGui::Checkbox("midi/gui                            ##ch2Adjust", &ch2AdjustMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset ##ch2Adjust",&ch2AdjustReset);
						if (ch2AdjustReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								ch2Adjust[i] = 0.0f;
								ch2AdjustMidiActive[i] = 0;
							}
							ch2AdjustReset = 0;
							ch2VMirror=ch2HMirror=ch2VFlip=ch2HFlip=ch2HueInvert=ch2SaturationInvert=ch2BrightInvert=ch2RGBInvert=ch2Solarize=0;
						}
						
						midi2Gui(ch2AdjustMidiActive, ch2Adjust, ch2AdjustMidiGui);
						ImGui::Separator();
						ImGui::SliderFloat("x <->   ##ch2", &ch2Adjust[0], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("y <->   ##ch2", &ch2Adjust[1], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("z <->   ##ch2", &ch2Adjust[2], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("rotate <-> ##ch2", &ch2Adjust[3], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("hue ^^  ##ch2", &ch2Adjust[4], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sat ^^  ##ch2", &ch2Adjust[5], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("bri ^^  ##ch2", &ch2Adjust[6], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("posterize  ##ch2", &ch2Adjust[7], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("kaleido ##ch2 ", &ch2Adjust[8], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("kaleido slice ##ch2 ", &ch2Adjust[9], -1.0f, 1.0f);
						
						ImGui::Separator();
						ImGui::SliderFloat("blur    ##ch2 ", &ch2Adjust[10], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("blur rad  ##ch2 ", &ch2Adjust[11], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("sharp   ##ch2 ", &ch2Adjust[12], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sharp rad ##ch2 ", &ch2Adjust[13], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("filters boost ##ch2 ", &ch2Adjust[14], -1.0f, 1.0f);
						ImGui::Separator();
						
						
						static int item_current0 = 0;
						const char* items1[] = { "geo overflow clamp","geo overflow toroid","geo overflow mirror" };
						ImGui::Combo("##ch2 geo overflow", &item_current0, items1, IM_ARRAYSIZE(items1));
						ch2GeoOverflow = item_current0;
						ImGui::Separator();
						ImGui::Checkbox("h mirror        ##ch2",&ch2HMirror);
						ImGui::SameLine();
						ImGui::Checkbox("v mirror        ##ch2",&ch2VMirror);
						ImGui::SameLine();
						ImGui::Checkbox("h flip          ##ch2",&ch2HFlip);
						ImGui::SameLine();
						ImGui::Checkbox("v flip          ##ch2",&ch2VFlip);
						
						ImGui::Separator();
						ImGui::Checkbox("hue invert      ##ch2",&ch2HueInvert);
						ImGui::SameLine();
						ImGui::Checkbox("sat invert      ##ch2",&ch2SaturationInvert);
						ImGui::SameLine();
						ImGui::Checkbox("bri invert      ##ch2",&ch2BrightInvert);
						ImGui::SameLine();
						ImGui::Checkbox("rgb invert      ##ch2",&ch2RGBInvert);
						ImGui::SameLine();
						ImGui::Checkbox("solarize        ##ch2",&ch2Solarize);				
						
						ImGui::EndTabItem();
					}
					
					if (ImGui::BeginTabItem("ch1 and ch2 lfo")){		
						if(nodeToClose==0)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("ch1 adjust lfo"))
						{
							if(currentNode==0)
							{
								ImGui::Checkbox("midi/gui                 ##ch1AdjustLfo", &ch1AdjustLfoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##ch1AdjustLfo",&ch1AdjustLfoReset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (ch1AdjustLfoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										ch1AdjustLfo[i] = 0.0f;
										ch1AdjustLfoMidiActive[i] = 0;
									}
									ch1AdjustLfoReset = 0;
								}
								
								midi2Gui(ch1AdjustLfoMidiActive, ch1AdjustLfo, ch1AdjustLfoMidiGui);
								ImGui::Separator();
								
								ImGui::SliderFloat("x <-> a      ##ch1", &ch1AdjustLfo[0], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("x <-> r      ##ch1", &ch1AdjustLfo[1], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("y <-> a      ##ch1", &ch1AdjustLfo[2], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("y <-> r      ##ch1", &ch1AdjustLfo[3], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("z <-> a      ##ch1", &ch1AdjustLfo[4], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("z <-> r      ##ch1", &ch1AdjustLfo[5], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("rotate <-> a ##ch1", &ch1AdjustLfo[6], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> r ##ch1", &ch1AdjustLfo[7], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("hue ^^ a     ##ch1", &ch1AdjustLfo[8], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("hue ^^ r     ##ch1", &ch1AdjustLfo[9], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("sat ^^ a     ##ch1", &ch1AdjustLfo[10], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("sat ^^ r     ##ch1", &ch1AdjustLfo[11], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("bri ^^ a     ##ch1", &ch1AdjustLfo[12], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("bri ^^ r     ##ch1", &ch1AdjustLfo[13], -1.0f, 1.0f);
								
								ImGui::Separator();
								
								ImGui::SliderFloat("kaleid sli a ##ch1", &ch1AdjustLfo[14], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid sli r ##ch1", &ch1AdjustLfo[15], -1.0f, 1.0f);		
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=0;
							}
							ImGui::TreePop();
						}
						ImGui::Separator();
						if(nodeToClose==1)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("ch2 mix and key lfo"))
						{
							if(currentNode==1)
							{
								ImGui::Checkbox("midi/gui                 ##ch2MixAndKeyLfo", &ch2MixAndKeyLfoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##ch2MixAndKeyLfo",&ch2MixAndKeyLfoReset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (ch2MixAndKeyLfoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										ch2MixAndKeyLfo[i] = 0.0f;
										ch2MixAndKeyLfoMidiActive[i] = 0;
									}
									ch2MixAndKeyLfoReset = 0;
								}
								
								midi2Gui(ch2MixAndKeyLfoMidiActive, ch2MixAndKeyLfo, ch2MixAndKeyLfoMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("mix a       ##ch2",&ch2MixAndKeyLfo[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("mix r       ##ch2",&ch2MixAndKeyLfo[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky thresh a ##ch2",&ch2MixAndKeyLfo[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky thresh r ##ch2",&ch2MixAndKeyLfo[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky soft a   ##ch2",&ch2MixAndKeyLfo[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky soft r   ##ch2",&ch2MixAndKeyLfo[5],-1.0,1.0);
								
								//looks like we could just add AND wipe mode too here without too much issue, so we could simultaneously
								//wipe and mix and key without having alternate modes
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=1;
							}
							ImGui::TreePop();
						}
						ImGui::Separator();
						if(nodeToClose==2)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("ch2 adjust lfo"))
						{
							if(currentNode==2)
							{
								ImGui::Checkbox("midi/gui                 ##ch2AdjustLfo", &ch2AdjustLfoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##ch2AdjustLfo",&ch2AdjustLfoReset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (ch2AdjustLfoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										ch2AdjustLfo[i] = 0.0f;
										ch2AdjustLfoMidiActive[i] = 0;
									}
									ch2AdjustLfoReset = 0;
								}
								
								midi2Gui(ch2AdjustLfoMidiActive, ch2AdjustLfo, ch2AdjustLfoMidiGui);
								ImGui::Separator();
								
								ImGui::SliderFloat("x <-> a      ##ch2", &ch2AdjustLfo[0], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("x <-> r      ##ch2", &ch2AdjustLfo[1], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("y <-> a      ##ch2", &ch2AdjustLfo[2], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("y <-> r      ##ch2", &ch2AdjustLfo[3], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("z <-> a      ##ch2", &ch2AdjustLfo[4], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("z <-> r      ##ch2", &ch2AdjustLfo[5], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("rotate <-> a ##ch2", &ch2AdjustLfo[6], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> r ##ch2", &ch2AdjustLfo[7], -1.0f, 1.0f);
								ImGui::Separator();
								ImGui::SliderFloat("hue ^^ a     ##ch2", &ch2AdjustLfo[8], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("hue ^^ r     ##ch2", &ch2AdjustLfo[9], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("sat ^^ a     ##ch2", &ch2AdjustLfo[10], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("sat ^^ r     ##ch2", &ch2AdjustLfo[11], -1.0f, 1.0f);
								ImGui::Separator();
								
								ImGui::SliderFloat("bri ^^ a     ##ch2", &ch2AdjustLfo[12], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("bri ^^ r     ##ch2", &ch2AdjustLfo[13], -1.0f, 1.0f);
								
								
								ImGui::Separator();
								
								ImGui::SliderFloat("kaleid sli a ##ch2", &ch2AdjustLfo[14], -1.0f, 1.0f);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid sli r ##ch2", &ch2AdjustLfo[15], -1.0f, 1.0f);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=2;
							}
							ImGui::TreePop();
						}			
						ImGui::EndTabItem();
					}
					if(ImGui::BeginTabItem("fb1 parameters")){
						//reset all fb1 parameters
						
						ImGui::SliderInt("fb1 delay time         ",&fb1DelayTime,1,pastFramesSize);
						ImGui::SameLine();
						fb1FramebufferClearSwitch=0;
						if (ImGui::Button("fb1 framebuffer clear")) {
							fb1FramebufferClearSwitch=1;
						}
						if(nodeToClose==3)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 mix and key"))
						{	
							if(currentNode==3)
							{
								static int item_current0 = 0;
								static int item_current1 = 0;
								static int item_current2 = 0;
								static int item_current3 = 0;
								ImGui::Checkbox("midi/gui                 ##fb1", &fb1MixAndKeyMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset          ##fb1",&fb1MixAndKeyReset);
								ImGui::SameLine();
								if (fb1MixAndKeyReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1MixAndKey[i] = 0.0f;
										fb1MixAndKeyMidiActive[i] = 0;
									}
									fb1MixAndKeyReset = 0;
								}
								
								midi2Gui(fb1MixAndKeyMidiActive, fb1MixAndKey, fb1MixAndKeyMidiGui);

								const char* items0[] = { "key order inputs->fb1","key order fb1->inputs" };
								ImGui::Combo("key order ##fb1 ", &item_current0, items0, IM_ARRAYSIZE(items0));
								fb1KeyOrder = item_current0;
								
								ImGui::Separator();
								const char* items1[] = { "linear fade", "additive","difference","multiplicitive","dodge" };
								ImGui::Combo("mix type       ##fb1 ", &item_current1, items1, IM_ARRAYSIZE(items1));
								fb1MixType = item_current1;
								ImGui::SameLine();
								ImGui::SliderFloat("mix ##fb1",&fb1MixAndKey[0],-1.0,1.0);
								ImGui::Separator();
								
								const char* items2[] = { "wrap", "clamp","foldover" };
								ImGui::Combo("overflow       ##fb1Mix", &item_current2, items2, IM_ARRAYSIZE(items2));
								fb1MixOverflow = item_current2;
								ImGui::SameLine();
								const char* items3[] = { "lumakey","chromakey" };
								ImGui::Combo("key mode ##fb1", &item_current3, items3, IM_ARRAYSIZE(items3));
								fb1KeyMode = item_current3;
								ImGui::Separator();
							
								if(fb1KeyMode==0){
								ImGui::SliderFloat("key red        ##fb1",&fb1MixAndKey[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("key green      ##fb1",&fb1MixAndKey[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("key blue       ##fb1",&fb1MixAndKey[1],-1.0,1.0);
								ImGui::SameLine();
								fb1MixAndKey[2]=fb1MixAndKey[3]=fb1MixAndKey[1];
								}
								
								if(fb1KeyMode==1){
								ImGui::SliderFloat("key red        ##fb1",&fb1MixAndKey[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("key green      ##fb1",&fb1MixAndKey[2],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("key blue       ##fb1",&fb1MixAndKey[3],-1.0,1.0);
								ImGui::SameLine();
								}
								ImGui::ColorButton("testingColorButton 1", ImVec4(fb1MixAndKey[1], fb1MixAndKey[2], fb1MixAndKey[3], 1.0), 0, ImVec2(20, 20));
								ImGui::SameLine();
								ImGui::Text("key value color");
								
								ImGui::Separator();
								ImGui::SliderFloat("key threshold  ##fb1",&fb1MixAndKey[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("key soft ##fb1",&fb1MixAndKey[5],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=3;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==4)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 geo")){
							if(currentNode==4)
							{
								ImGui::Checkbox("midi/gui                               ##fb1", &fb1Geo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset  ##fb1",&fb1Geo1Reset);
								if (fb1Geo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1Geo1[i] = 0.0f;
										fb1Geo1MidiActive[i] = 0;
									}
									fb1GeoOverflow=0;
									fb1HMirror=fb1VMirror=fb1RotateMode=0;
									//ADD ALL CHECKBOXES ETC HERE
									fb1Geo1Reset = 0;
								}
								
								midi2Gui(fb1Geo1MidiActive, fb1Geo1, fb1Geo1MidiGui);
								
								//x, y, z, rotate, matrix, kaleido
								ImGui::SliderFloat("x <->      ##fb1",&fb1Geo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <->      ##fb1",&fb1Geo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <->      ##fb1",&fb1Geo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> ##fb1",&fb1Geo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x stretch  ##fb1",&fb1Geo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch  ##fb1",&fb1Geo1[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear    ##fb1",&fb1Geo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear    ##fb1",&fb1Geo1[7],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("kaleid amt ##fb1",&fb1Geo1[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid slice ##fb1",&fb1Geo1[9],-1.0,1.0);
								ImGui::Separator();
								static int item_current0 = 0;
								const char* items0[] = { "clamp","toroid","mirror" };
								ImGui::Combo("fb1 geo overflow", &item_current0, items0, IM_ARRAYSIZE(items0));
								fb1GeoOverflow = item_current0;
								ImGui::Separator();
								ImGui::Checkbox("h mirror      ##fb1", &fb1HMirror);
								ImGui::SameLine();
								ImGui::Checkbox("v mirror      ##fb1", &fb1VMirror);
								ImGui::SameLine();
								ImGui::Checkbox("h flip        ##fb1",&fb1HFlip);
								ImGui::SameLine();
								ImGui::Checkbox("v flip        ##fb1",&fb1VFlip);
								ImGui::SameLine();
								ImGui::Checkbox("rotate mode      ##fb1", &fb1RotateMode);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=4;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						
						if(nodeToClose==5)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 color"))
						{
							if(currentNode==5)
							{
								ImGui::Checkbox("midi/gui                                ##fb1color1", &fb1Color1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##fb1color1",&fb1Color1Reset);
								if (fb1Color1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1Color1[i] = 0.0f;
										fb1Color1MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb1HueInvert=fb1SaturationInvert=fb1BrightInvert=0;
									fb1Color1Reset = 0;
								}
								
								midi2Gui(fb1Color1MidiActive, fb1Color1, fb1Color1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("hue ++      ##fb1",&fb1Color1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sat ++      ##fb1",&fb1Color1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("bri ++      ##fb1",&fb1Color1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("hue **      ##fb1",&fb1Color1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sat **      ##fb1",&fb1Color1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("bri **      ##fb1",&fb1Color1[5],-1.0,1.0);
								ImGui::Separator();			
								ImGui::SliderFloat("hue ^^      ##fb1",&fb1Color1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sat ^^      ##fb1",&fb1Color1[7],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("bri ^^      ##fb1",&fb1Color1[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("hue shaper  ##fb1",&fb1Color1[9],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("posterize   ##fb1",&fb1Color1[10],0.0,1.0);
								ImGui::Separator();
								
								ImGui::Checkbox("fb1 hue invert  ", &fb1HueInvert);
								ImGui::SameLine();
								ImGui::Checkbox("fb1 sat invert  ", &fb1SaturationInvert);
								ImGui::SameLine();
								ImGui::Checkbox("fb1 bri invert  ", &fb1BrightInvert);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=5;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==6)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 filters"))
						{
							if(currentNode==6)
							{
								ImGui::Checkbox("midi/gui                               ##fb1filters ", &fb1FiltersMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##fb1filters ",&fb1FiltersReset);
								if (fb1FiltersReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1Filters[i] = 0.0f;
										fb1FiltersMidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb1FiltersReset = 0;
								}
								
								midi2Gui(fb1FiltersMidiActive, fb1Filters, fb1FiltersMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("blur amt   ##fb1",&fb1Filters[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("blur rad   ##fb1",&fb1Filters[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sharp amt  ##fb1",&fb1Filters[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sharp rad  ##fb1",&fb1Filters[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("temp 1 amt ##fb1",&fb1Filters[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("temp 1 q   ##fb1",&fb1Filters[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("temp 2 amt ##fb1",&fb1Filters[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("temp 2 q   ##fb1",&fb1Filters[7],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("filters boost ##fb1",&fb1Filters[8],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=6;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(secretMenuSwitch==1){
							if(nodeToClose==7)
							{
								ImGui::SetNextItemOpen(false, ImGuiCond_Always);
								nodeToClose=-1;	
							}
							if (ImGui::TreeNode("Geometrical Animations"))
							{
								if(currentNode==7)
								{
									ImGui::Checkbox("hypercube ##fb1",&block1HypercubeSwitch);
									/*
									ImGui::SameLine();
									ImGui::SliderFloat("hc size",&hypercube_size,.0,2.0);
									ImGui::Separator();
									ImGui::SliderFloat("hc rate 1", &hypercube_theta_rate, -.1,.1);
									ImGui::SameLine();
									ImGui::SliderFloat("hc rate 2", &hypercube_phi_rate, -.1,.1);
									*/
									ImGui::Checkbox("dancing line ##fb1",&block1LineSwitch);
									ImGui::Checkbox("septagram ##fb1",&block1SevenStar1Switch);
									ImGui::Checkbox("lissajous ball ##fb1",&block1LissaBallSwitch);
								}
								else
								{
									nodeToClose=currentNode;
									currentNode=7;
								}
								ImGui::TreePop();
							}
						}
						ImGui::EndTabItem();
						//ImGui::TreePop();
					}//end fb1 parameters
					
					if(ImGui::BeginTabItem("fb1 lfo"))
					{
						if(nodeToClose==8)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 mix and key lfo"))
						{
							if(currentNode==8)
							{
								ImGui::Checkbox("midi/gui                 ##fb1mixandkeylfo", &fb1MixAndKeyLfoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb1mixandkeylfo",&fb1MixAndKeyLfoReset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb1MixAndKeyLfoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1MixAndKeyLfo[i] = 0.0f;
										fb1MixAndKeyLfoMidiActive[i] = 0;
									}
									fb1MixAndKeyLfoReset = 0;
								}
								
								midi2Gui(fb1MixAndKeyLfoMidiActive, fb1MixAndKeyLfo, fb1MixAndKeyLfoMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("mix a       ##fb1",&fb1MixAndKeyLfo[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("mix r       ##fb1",&fb1MixAndKeyLfo[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky thresh a ##fb1",&fb1MixAndKeyLfo[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky thresh r ##fb1",&fb1MixAndKeyLfo[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky soft a   ##fb1",&fb1MixAndKeyLfo[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky soft r   ##fb1",&fb1MixAndKeyLfo[5],-1.0,1.0);

							}
							else
							{
								nodeToClose=currentNode;
								currentNode=8;
							}
							ImGui::TreePop();
						}
						ImGui::Separator();
						if(nodeToClose==9)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 geo lfo 1"))
						{
							if(currentNode==9)
							{
								ImGui::Checkbox("midi/gui                 ##fb1Geo1Lfo1", &fb1Geo1Lfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb1Geo1Lfo1",&fb1Geo1Lfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb1Geo1Lfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1Geo1Lfo1[i] = 0.0f;
										fb1Geo1Lfo1MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb1Geo1Lfo1Reset = 0;
								}
								
								midi2Gui(fb1Geo1Lfo1MidiActive, fb1Geo1Lfo1, fb1Geo1Lfo1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x <-> a      ##fb1Lfo",&fb1Geo1Lfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x <-> r      ##fb1Lfo",&fb1Geo1Lfo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y <-> a      ##fb1Lfo",&fb1Geo1Lfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <-> r      ##fb1Lfo",&fb1Geo1Lfo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <-> a      ##fb1Lfo",&fb1Geo1Lfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("z <-> r      ##fb1Lfo",&fb1Geo1Lfo1[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("rotate <-> a ##fb1Lfo",&fb1Geo1Lfo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> r ##fb1Lfo",&fb1Geo1Lfo1[7],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=9;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==10)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 geo lfo 2"))
						{
							if(currentNode==10)
							{	
								ImGui::Checkbox("midi/gui                 ##fb1Geo1Lfo2", &fb1Geo1Lfo2MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb1Geo1Lfo2",&fb1Geo1Lfo2Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb1Geo1Lfo2Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1Geo1Lfo2[i] = 0.0f;
										fb1Geo1Lfo2MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb1Geo1Lfo2Reset = 0;
								}
								
								midi2Gui(fb1Geo1Lfo2MidiActive, fb1Geo1Lfo2, fb1Geo1Lfo2MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x stretch a  ##fb1lfo",&fb1Geo1Lfo2[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x stretch r  ##fb1lfo",&fb1Geo1Lfo2[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y stretch a  ##fb1lfo",&fb1Geo1Lfo2[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch r  ##fb1lfo",&fb1Geo1Lfo2[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear a    ##fb1lfo",&fb1Geo1Lfo2[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x shear r    ##fb1lfo",&fb1Geo1Lfo2[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y shear a    ##fb1lfo",&fb1Geo1Lfo2[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear r    ##fb1lfo",&fb1Geo1Lfo2[7],-1.0,1.0);
								
								ImGui::Separator();
								ImGui::SliderFloat("kaleid sl a  ##fb1lfo",&fb1Geo1Lfo2[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid sl r  ##fb1lfo",&fb1Geo1Lfo2[9],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=10;
							}
							ImGui::TreePop();		
						}
						ImGui::Separator();
						if(nodeToClose==11)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb1 color Lfo"))
						{
							if(currentNode==11)
							{
								ImGui::Checkbox("midi/gui                 ##fb1Color1Lfo1", &fb1Color1Lfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb1Color1Lfo1",&fb1Color1Lfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb1Color1Lfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb1Color1Lfo1[i] = 0.0f;
										fb1Color1Lfo1MidiActive[i] = 0;
									}
									fb1Color1Lfo1Reset = 0;
								}
								
								midi2Gui(fb1Color1Lfo1MidiActive, fb1Color1Lfo1, fb1Color1Lfo1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("hue x a      ##fb1lfo",&fb1Color1Lfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("hue x r      ##fb1lfo",&fb1Color1Lfo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sat x a      ##fb1lfo",&fb1Color1Lfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sat x r      ##fb1lfo",&fb1Color1Lfo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("bright x a   ##fb1lfo",&fb1Color1Lfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("bright x r   ##fb1lfo",&fb1Color1Lfo1[5],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=11;
							}
							ImGui::TreePop();	
						}
						ImGui::EndTabItem();
						//ImGui::TreePop();
					}
				
						
					ImGui::EndTabBar();
				}
				
				ImGui::EndTabItem();
			}//end block1tabItem
		    ImGui::PopStyleColor(12);
		        	
        
        
        
        
        	//BLOCK2 color style
			ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(block2Hue, 0.6f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(block2Hue, 0.7f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(block2Hue, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(block2Hue, 0.8f, 0.8f));
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(block2Hue, 0.5f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(block2Hue, 0.6f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(block2Hue, 0.7f, 0.8f));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, (ImVec4)ImColor::HSV(block2Hue, 0.2f, 0.1f));
			
			ImGui::PushStyleColor(ImGuiCol_Text,(ImVec4)ImColor::HSV(.83f,.2f,1.0f));
        
			ImGui::PushStyleColor(ImGuiCol_Tab, (ImVec4)ImColor::HSV(block2Hue,.65f,.65f));
			ImGui::PushStyleColor(ImGuiCol_TabActive, (ImVec4)ImColor::HSV(block2Hue,.7f,.7f));
			ImGui::PushStyleColor(ImGuiCol_TabHovered, (ImVec4)ImColor::HSV(block2Hue,.8f,.8f));
			        
        
		    if (ImGui::BeginTabItem("BLOCK_2"))
		    {
		    	blockSelectHsb=2;
		    	//if (ImGui::CollapsingHeader("--**--**--**--**--**--**--**--**--**--BLOCK_2--**--**--**--**--**--**--**--**--**--")){	
				//add block2 input select & process
				if (ImGui::Button("reset BLOCK_2")) {
						block2ResetAll();
				}
				ImGui::SameLine();
				if (ImGui::Button("reset input")) {
						block2InputResetAll();
				}
				ImGui::SameLine();
				if (ImGui::Button("reset fb2")) {
						fb2ResetAll();
				}
				
				ImGui::Separator();
				
				
				if(ImGui::BeginTabBar("BLOCK_2 subfolders")){
					
					if(ImGui::BeginTabItem("BLOCK_2 input adjust"))
					{
						const char* items0[] = { "BLOCK_1","input1","input2" };
						static int item_block2InputSelect = 2;
						ImGui::Combo("input   ##block2Input", &item_block2InputSelect, items0, IM_ARRAYSIZE(items0));
						block2InputSelect=item_block2InputSelect;
						ImGui::SameLine();
						//might want to change default to hd and check for SD if that seems more relevant
						ImGui::Checkbox("hd aspect ratio     ##block2InputAdjust", &block2InputAspectRatioSwitch);
						ImGui::SameLine();
						ImGui::Checkbox("midi/gui      ##block2InputAdjust", &block2InputAdjustMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset ##block2InputAdjust",&block2InputAdjustReset);
						if (block2InputAdjustReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								block2InputAdjust[i] = 0.0f;
								block2InputAdjustMidiActive[i] = 0;
							}
							block2InputAdjustReset = 0;
							block2InputVMirror=block2InputHMirror=block2InputVFlip=block2InputHFlip=block2InputHueInvert=0;
							block2InputSaturationInvert=block2InputBrightInvert=block2InputRGBInvert=block2InputSolarize=0;
						}
						
						midi2Gui(block2InputAdjustMidiActive, block2InputAdjust, block2InputAdjustMidiGui);
						ImGui::Separator();
						ImGui::SliderFloat("x <->   ##block2Input", &block2InputAdjust[0], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("y <->   ##block2Input", &block2InputAdjust[1], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("z <->   ##block2Input", &block2InputAdjust[2], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("rotate <-> ##block2Input", &block2InputAdjust[3], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("hue ^^  ##block2Input", &block2InputAdjust[4], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sat ^^  ##block2Input", &block2InputAdjust[5], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("bri ^^  ##block2Input", &block2InputAdjust[6], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("posterize  ##block2Input", &block2InputAdjust[7], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("kaleido ##block2Input ", &block2InputAdjust[8], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("kaleido slice ##block2Input ", &block2InputAdjust[9], -1.0f, 1.0f);
						
						ImGui::Separator();
						ImGui::SliderFloat("blur    ##block2Input ", &block2InputAdjust[10], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("blur rad  ##block2Input ", &block2InputAdjust[11], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("sharp   ##block2Input ", &block2InputAdjust[12], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sharp rad ##block2Input ", &block2InputAdjust[13], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("filters boost ##block2Input ", &block2InputAdjust[14], -1.0f, 1.0f);
						ImGui::Separator();
						
						
						
						
						static int item_current0 = 0;
						const char* items1[] = { "geo overflow clamp","geo overflow toroid","geo overflow mirror" };
						ImGui::Combo("##block2Input geo overflow", &item_current0, items1, IM_ARRAYSIZE(items1));
						block2InputGeoOverflow = item_current0;
						ImGui::Separator();
						ImGui::Checkbox("h mirror ##block2Input",&block2InputHMirror);
						ImGui::SameLine();
						ImGui::Checkbox("v mirror ##block2Input",&block2InputVMirror);
						ImGui::SameLine();
						ImGui::Checkbox("h flip ##block2Input",&block2InputHFlip);
						ImGui::SameLine();
						ImGui::Checkbox("v flip ##block2Input",&block2InputVFlip);
						ImGui::Separator();
						ImGui::Checkbox("hue invert ##block2Input",&block2InputHueInvert);
						ImGui::SameLine();
						ImGui::Checkbox("sat invert ##block2Input",&block2InputSaturationInvert);
						ImGui::SameLine();
						ImGui::Checkbox("bri invert ##block2Input",&block2InputBrightInvert);
						ImGui::SameLine();
						ImGui::Checkbox("rgb invert ##block2Input",&block2InputRGBInvert);
						ImGui::SameLine();
						ImGui::Checkbox("solarize ##block2Input",&block2InputSolarize);
					
						ImGui::EndTabItem();
					}
				
					if (ImGui::BeginTabItem("BLOCK_2 input adjust lfo")){
						
						ImGui::Checkbox("midi/gui                 ##block2InputAdjustLfo", &block2InputAdjustLfoMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset        ##block2InputAdjustLfo",&block2InputAdjustLfoReset);
						ImGui::SameLine();
						ImGui::Text("a := lfo amplitude     r := lfo rate");
						if (block2InputAdjustLfoReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								block2InputAdjustLfo[i] = 0.0f;
								block2InputAdjustLfoMidiActive[i] = 0;
							}
							block2InputAdjustLfoReset = 0;
						}
						
						midi2Gui(block2InputAdjustLfoMidiActive, block2InputAdjustLfo, block2InputAdjustLfoMidiGui);
						ImGui::Separator();
						
						ImGui::SliderFloat("x <-> a      ##block2Input", &block2InputAdjustLfo[0], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("x <-> r      ##block2Input", &block2InputAdjustLfo[1], -1.0f, 1.0f);
						ImGui::Separator();
						
						ImGui::SliderFloat("y <-> a      ##block2Input", &block2InputAdjustLfo[2], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("y <-> r      ##block2Input", &block2InputAdjustLfo[3], -1.0f, 1.0f);
						ImGui::Separator();
						
						ImGui::SliderFloat("z <-> a      ##block2Input", &block2InputAdjustLfo[4], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("z <-> r      ##block2Input", &block2InputAdjustLfo[5], -1.0f, 1.0f);
						ImGui::Separator();
						
						ImGui::SliderFloat("rotate <-> a ##block2Input", &block2InputAdjustLfo[6], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("rotate <-> r ##block2Input", &block2InputAdjustLfo[7], -1.0f, 1.0f);
						ImGui::Separator();
						ImGui::SliderFloat("hue ^^ a     ##block2Input", &block2InputAdjustLfo[8], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("hue ^^ r     ##block2Input", &block2InputAdjustLfo[9], -1.0f, 1.0f);
						ImGui::Separator();
						
						ImGui::SliderFloat("sat ^^ a     ##block2Input", &block2InputAdjustLfo[10], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("sat ^^ r     ##block2Input", &block2InputAdjustLfo[11], -1.0f, 1.0f);
						ImGui::Separator();
						
						ImGui::SliderFloat("bri ^^ a     ##block2Input", &block2InputAdjustLfo[12], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("bri ^^ r     ##block2Input", &block2InputAdjustLfo[13], -1.0f, 1.0f);
						
						
						ImGui::Separator();
						
						ImGui::SliderFloat("kaleid sli a ##block2Input", &block2InputAdjustLfo[14], -1.0f, 1.0f);
						ImGui::SameLine();
						ImGui::SliderFloat("kaleid sli r ##block2Input", &block2InputAdjustLfo[15], -1.0f, 1.0f);
						
						ImGui::EndTabItem();
					}
				
				
				
					if(ImGui::BeginTabItem("fb2 parameters"))
					{
						//reset all fb2 parameters
						ImGui::SliderInt("fb2 delay time     ",&fb2DelayTime,1,pastFramesSize);
						ImGui::SameLine();
						fb2FramebufferClearSwitch=0;
						if (ImGui::Button("fb2 framebuffer clear")) {
							fb2FramebufferClearSwitch=1;
						}
						if(nodeToClose==12)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 mix and key"))
						{
							if(currentNode==12)
							{	
								static int item_current0 = 0;
								static int item_current1 = 0;
								static int item_current2 = 0;
								static int item_current3 = 0;  
								ImGui::Checkbox("midi/gui                 ##fb2", &fb2MixAndKeyMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset          ##fb2",&fb2MixAndKeyReset);
								ImGui::SameLine();
								if (fb2MixAndKeyReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2MixAndKey[i] = 0.0f;
										fb2MixAndKeyMidiActive[i] = 0;
									}
									fb2MixAndKeyReset = 0;
								}
								
								midi2Gui(fb2MixAndKeyMidiActive, fb2MixAndKey, fb2MixAndKeyMidiGui);

								const char* items0[] = { "key order inputs->fb2","key order fb2->inputs" };
								ImGui::Combo("key order ##fb2 ", &item_current0, items0, IM_ARRAYSIZE(items0));
								fb2KeyOrder = item_current0;
								
								ImGui::Separator();
								const char* items1[] = { "linear fade", "additive","difference","multiplicitive","dodge" };
								ImGui::Combo("mix type       ##fb2 ", &item_current1, items1, IM_ARRAYSIZE(items1));
								fb2MixType = item_current1;
								ImGui::SameLine();
								ImGui::SliderFloat("mix ##fb2",&fb2MixAndKey[0],-1.0,1.0);
								ImGui::Separator();
								
								const char* items2[] = { "wrap", "clamp","foldover" };
								ImGui::Combo("overflow       ##fb2Mix", &item_current2, items2, IM_ARRAYSIZE(items2));
								fb2MixOverflow = item_current2;
								ImGui::SameLine();
								const char* items3[] = { "lumakey","chromakey" };
								ImGui::Combo("key mode ##fb2", &item_current3, items3, IM_ARRAYSIZE(items3));
								fb2KeyMode = item_current3;
								ImGui::Separator();
							
								if(fb2KeyMode==0)
								{
									ImGui::SliderFloat("key red        ##fb2",&fb2MixAndKey[1],-1.0,1.0);
									ImGui::SameLine();
									ImGui::SliderFloat("key green      ##fb2",&fb2MixAndKey[1],-1.0,1.0);
									ImGui::Separator();
									ImGui::SliderFloat("key blue       ##fb2",&fb2MixAndKey[1],-1.0,1.0);
									ImGui::SameLine();
									fb2MixAndKey[2]=fb2MixAndKey[3]=fb2MixAndKey[1];
								}
								
								if(fb2KeyMode==1)
								{
									ImGui::SliderFloat("key red        ##fb2",&fb2MixAndKey[1],-1.0,1.0);
									ImGui::SameLine();
									ImGui::SliderFloat("key green      ##fb2",&fb2MixAndKey[2],-1.0,1.0);
									ImGui::Separator();
									ImGui::SliderFloat("key blue       ##fb2",&fb2MixAndKey[3],-1.0,1.0);
									ImGui::SameLine();
								}
								ImGui::ColorButton("testingColorButton 1", ImVec4(fb2MixAndKey[1], fb2MixAndKey[2], fb2MixAndKey[3], 1.0), 0, ImVec2(20, 20));
								ImGui::SameLine();
								ImGui::Text("key value color");
								
								ImGui::Separator();
								ImGui::SliderFloat("key threshold  ##fb2",&fb2MixAndKey[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("key soft ##fb2",&fb2MixAndKey[5],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=12;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==13)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 geo")){
							if(currentNode==13)
							{
								ImGui::Checkbox("midi/gui                               ##fb2", &fb2Geo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset  ##fb2",&fb2Geo1Reset);
								if (fb2Geo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2Geo1[i] = 0.0f;
										fb2Geo1MidiActive[i] = 0;
									}
									fb2GeoOverflow=0;
									fb2HMirror=fb2VMirror=fb2RotateMode=0;
									fb2Geo1Reset = 0;
								}
								
								midi2Gui(fb2Geo1MidiActive, fb2Geo1, fb2Geo1MidiGui);
								
								//x, y, z, rotate, matrix, kaleido
								ImGui::SliderFloat("x <->      ##fb2",&fb2Geo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <->      ##fb2",&fb2Geo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <->      ##fb2",&fb2Geo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> ##fb2",&fb2Geo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x stretch  ##fb2",&fb2Geo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch  ##fb2",&fb2Geo1[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear    ##fb2",&fb2Geo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear    ##fb2",&fb2Geo1[7],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("kaleid amt ##fb2",&fb2Geo1[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid slice ##fb2",&fb2Geo1[9],-1.0,1.0);
								ImGui::Separator();
								static int item_current0 = 0;
								const char* items0[] = { "clamp","toroid","mirror" };
								ImGui::Combo("fb2 geo overflow", &item_current0, items0, IM_ARRAYSIZE(items0));
								fb2GeoOverflow = item_current0;
								ImGui::Separator();
								ImGui::Checkbox("h mirror      ##fb2", &fb2HMirror);
								ImGui::SameLine();
								ImGui::Checkbox("v mirror      ##fb2", &fb2VMirror);
								ImGui::SameLine();
								ImGui::Checkbox("h flip        ##fb2",&fb2HFlip);
								ImGui::SameLine();
								ImGui::Checkbox("v flip        ##fb2",&fb2VFlip);
								ImGui::SameLine();					
								ImGui::SameLine();
								ImGui::Checkbox("rotate mode      ##fb2", &fb2RotateMode);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=13;
							}
							ImGui::TreePop();
						}
						ImGui::Separator();
						if(nodeToClose==14)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 color"))
						{
							if(currentNode==14)
							{
								ImGui::Checkbox("midi/gui                                ##fb2color1", &fb2Color1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##fb2color1",&fb2Color1Reset);
								if (fb2Color1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2Color1[i] = 0.0f;
										fb2Color1MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb2HueInvert=fb2SaturationInvert=fb2BrightInvert=0;
									fb2Color1Reset = 0;
								}
								
								midi2Gui(fb2Color1MidiActive, fb2Color1, fb2Color1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("hue ++      ##fb2",&fb2Color1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sat ++      ##fb2",&fb2Color1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("bri ++      ##fb2",&fb2Color1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("hue **      ##fb2",&fb2Color1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sat **      ##fb2",&fb2Color1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("bri **      ##fb2",&fb2Color1[5],-1.0,1.0);
								ImGui::Separator();			
								ImGui::SliderFloat("hue ^^      ##fb2",&fb2Color1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sat ^^      ##fb2",&fb2Color1[7],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("bri ^^      ##fb2",&fb2Color1[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("hue shaper  ##fb2",&fb2Color1[9],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("posterize   ##fb2",&fb2Color1[10],0.0,1.0);
								ImGui::Separator();
								
								ImGui::Checkbox("fb2 hue invert  ", &fb2HueInvert);
								ImGui::SameLine();
								ImGui::Checkbox("fb2 sat invert  ", &fb2SaturationInvert);
								ImGui::SameLine();
								ImGui::Checkbox("fb2 bri invert  ", &fb2BrightInvert);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=14;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==15)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 filters"))
						{
							if(currentNode==15)
							{
								ImGui::Checkbox("midi/gui                               ##fb2filters ", &fb2FiltersMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##fb2filters ",&fb2FiltersReset);
								if (fb2FiltersReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2Filters[i] = 0.0f;
										fb2FiltersMidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb2FiltersReset = 0;
								}
								
								midi2Gui(fb2FiltersMidiActive, fb2Filters, fb2FiltersMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("blur amt   ##fb2",&fb2Filters[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("blur rad   ##fb2",&fb2Filters[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sharp amt  ##fb2",&fb2Filters[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sharp rad  ##fb2",&fb2Filters[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("temp 1 amt ##fb2",&fb2Filters[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("temp 1 q   ##fb2",&fb2Filters[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("temp 2 amt ##fb2",&fb2Filters[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("temp 2 q   ##fb2",&fb2Filters[7],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("filters boost ##fb2",&fb2Filters[8],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=15;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(secretMenuSwitch==1){
							if(nodeToClose==16)
							{
								ImGui::SetNextItemOpen(false, ImGuiCond_Always);
								nodeToClose=-1;	
							}
							if (ImGui::TreeNode("geometrical animations ##fb2"))
							{
								if(currentNode==16)
								{	
									ImGui::Checkbox("hypercube ##fb2",&block2HypercubeSwitch);
									ImGui::Checkbox("dancing line ##fb2",&block2LineSwitch);
									ImGui::Checkbox("septagram ##fb2",&block2SevenStar1Switch);	
									ImGui::Checkbox("lissajous ball ##fb2",&block2LissaBallSwitch);
								}
								else
								{
									nodeToClose=currentNode;
									currentNode=16;
								}
								ImGui::TreePop();	
							}
						}
						ImGui::EndTabItem();
						//ImGui::TreePop();
					}//end fb2 parameters
					
					
									
					if(ImGui::BeginTabItem("fb2 lfo")){
						if(nodeToClose==17)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 mix and key lfo"))
						{
							if(currentNode==17)
							{
								ImGui::Checkbox("midi/gui                 ##fb2mixandkeylfo", &fb2MixAndKeyLfoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb2mixandkeylfo",&fb2MixAndKeyLfoReset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb2MixAndKeyLfoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2MixAndKeyLfo[i] = 0.0f;
										fb2MixAndKeyLfoMidiActive[i] = 0;
									}
									fb2MixAndKeyLfoReset = 0;
								}
								
								midi2Gui(fb2MixAndKeyLfoMidiActive, fb2MixAndKeyLfo, fb2MixAndKeyLfoMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("mix a       ##fb2",&fb2MixAndKeyLfo[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("mix r       ##fb2",&fb2MixAndKeyLfo[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky thresh a ##fb2",&fb2MixAndKeyLfo[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky thresh r ##fb2",&fb2MixAndKeyLfo[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky soft a   ##fb2",&fb2MixAndKeyLfo[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky soft r   ##fb2",&fb2MixAndKeyLfo[5],-1.0,1.0);											
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=17;
							}
							ImGui::TreePop();							
						}
						ImGui::Separator();
						if(nodeToClose==18)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 geo lfo 1"))
						{
							if(currentNode==18)
							{
								ImGui::Checkbox("midi/gui                 ##fb2Geo1Lfo1", &fb2Geo1Lfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb2Geo1Lfo1",&fb2Geo1Lfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb2Geo1Lfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2Geo1Lfo1[i] = 0.0f;
										fb2Geo1Lfo1MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb2Geo1Lfo1Reset = 0;
								}
								
								midi2Gui(fb2Geo1Lfo1MidiActive, fb2Geo1Lfo1, fb2Geo1Lfo1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x <-> a      ##fb2Lfo",&fb2Geo1Lfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x <-> r      ##fb2Lfo",&fb2Geo1Lfo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y <-> a      ##fb2Lfo",&fb2Geo1Lfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <-> r      ##fb2Lfo",&fb2Geo1Lfo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <-> a      ##fb2Lfo",&fb2Geo1Lfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("z <-> r      ##fb2Lfo",&fb2Geo1Lfo1[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("rotate <-> a ##fb2Lfo",&fb2Geo1Lfo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> r ##fb2Lfo",&fb2Geo1Lfo1[7],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=18;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==19)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 geo lfo 2"))
						{
							if(currentNode==19)
							{
								ImGui::Checkbox("midi/gui                 ##fb2Geo1Lfo2", &fb2Geo1Lfo2MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb2Geo1Lfo2",&fb2Geo1Lfo2Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb2Geo1Lfo2Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2Geo1Lfo2[i] = 0.0f;
										fb2Geo1Lfo2MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									fb2Geo1Lfo2Reset = 0;
								}
								
								midi2Gui(fb2Geo1Lfo2MidiActive, fb2Geo1Lfo2, fb2Geo1Lfo2MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x stretch a  ##fb2lfo",&fb2Geo1Lfo2[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x stretch r  ##fb2lfo",&fb2Geo1Lfo2[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y stretch a  ##fb2lfo",&fb2Geo1Lfo2[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch r  ##fb2lfo",&fb2Geo1Lfo2[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear a    ##fb2lfo",&fb2Geo1Lfo2[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x shear r    ##fb2lfo",&fb2Geo1Lfo2[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y shear a    ##fb2lfo",&fb2Geo1Lfo2[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear r    ##fb2lfo",&fb2Geo1Lfo2[7],-1.0,1.0);
								
								ImGui::Separator();
								ImGui::SliderFloat("kaleid sl a  ##fb2lfo",&fb2Geo1Lfo2[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid sl r  ##fb2lfo",&fb2Geo1Lfo2[9],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=19;
							}
							ImGui::TreePop();		
						}
						ImGui::Separator();
						if(nodeToClose==20)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("fb2 color lfo"))
						{
							if(currentNode==20)
							{
								ImGui::Checkbox("midi/gui                 ##fb2Color1Lfo1", &fb2Color1Lfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##fb2Color1Lfo1",&fb2Color1Lfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (fb2Color1Lfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										fb2Color1Lfo1[i] = 0.0f;
										fb2Color1Lfo1MidiActive[i] = 0;
									}
									fb2Color1Lfo1Reset = 0;
								}
								
								midi2Gui(fb2Color1Lfo1MidiActive, fb2Color1Lfo1, fb2Color1Lfo1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("hue x a      ##fb2lfo",&fb2Color1Lfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("hue x r      ##fb2lfo",&fb2Color1Lfo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sat x a      ##fb2lfo",&fb2Color1Lfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sat x r      ##fb2lfo",&fb2Color1Lfo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("bright x a   ##fb2lfo",&fb2Color1Lfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("bright x r   ##fb2lfo",&fb2Color1Lfo1[5],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=20;
							}
							ImGui::TreePop();	
						}
						ImGui::EndTabItem();
						//ImGui::TreePop();
					}
					ImGui::EndTabBar();
				}//end block 2 tab bar
				ImGui::EndTabItem();
			}//end block2tab
		
        	ImGui::PopStyleColor(12);
        
        	
        	
     		   	
        	
        	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(.65f, 0.5f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(.65f, 0.6f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(.65f, 0.7f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(.65f, 0.9f, 0.9f));
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(.65f, 0.5f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(.65f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(.65f, 0.9f, 0.9f));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, (ImVec4)ImColor::HSV(.65f, 0.3f, 0.2f));

			ImGui::PushStyleColor(ImGuiCol_Text,(ImVec4)ImColor::HSV(.5f,.3f,1.0f));
        	
        	ImGui::PushStyleColor(ImGuiCol_Tab, (ImVec4)ImColor::HSV(.65f,.5f,.5f));
			ImGui::PushStyleColor(ImGuiCol_TabActive, (ImVec4)ImColor::HSV(.65f,.9f,.9f));
			ImGui::PushStyleColor(ImGuiCol_TabHovered, (ImVec4)ImColor::HSV(.65f,.7f,.7f));
			
        
        	if(ImGui::BeginTabItem("BLOCK_3"))
       		{
 				blockSelectHsb=3;       
        		//if (ImGui::CollapsingHeader("--**--**--**--**--**--**--**--**--**--BLOCK_3--**--**--**--**--**--**--**--**--**--")){
				static int item_current0 = 0;
				const char* items0[] = { "BLOCK_1->BLOCK_2","BLOCK_2->BLOCK_1" };
				ImGui::Combo(" final mix order", &item_current0, items0, IM_ARRAYSIZE(items0));
				finalKeyOrder = item_current0;
				ImGui::SameLine();
				ImGui::Text("                   ");
				ImGui::SameLine();
				if (ImGui::Button("reset BLOCK_3")) {
					block3ResetAll();
				}
				//add random fill 
				
				
				
				//**SO HERE IS WHERE WE TEST OUT TABBAR FLAGS
				ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyScroll;
				//tab_bar_flags |=ImGuiTabBarFlags_AutoSelectNewTabs;
				
				//try out adding tab_bar_flags in here to the tab bar
				if(ImGui::BeginTabBar("BLOCK_3 subfolders",tab_bar_flags))
				{
					if (ImGui::BeginTabItem("B_1 parameters"))
					{
						if(nodeToClose==21)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if(ImGui::TreeNode("B_1 geometry"))
						{
							if(currentNode==21)
							{
								ImGui::Checkbox("midi/gui                               ##block1Geo ", &block1GeoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##block1Geo ",&block1GeoReset);
								if (block1GeoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1Geo[i] = 0.0f;
										block1GeoMidiActive[i] = 0;
									}
									block1GeoReset = 0;
									block1HMirror=block1VMirror=block1HFlip=block1VFlip=block1RotateMode=0;
								}
								
								midi2Gui(block1GeoMidiActive, block1Geo, block1GeoMidiGui);	
								ImGui::Separator();
								ImGui::SliderFloat("x <->      ##block1",&block1Geo[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <->      ##block1",&block1Geo[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <->      ##block1",&block1Geo[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> ##block1",&block1Geo[3],-1.0,1.0);
							
								ImGui::Separator();
								ImGui::SliderFloat("x stretch  ##block1",&block1Geo[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch  ##block1",&block1Geo[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear    ##block1",&block1Geo[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear    ##block1",&block1Geo[7],-1.0,1.0);
								ImGui::Separator();
								
								ImGui::SliderFloat("kaleid amt ##block1",&block1Geo[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid slice ##block1",&block1Geo[9],-1.0,1.0);
								ImGui::Separator();
								
								static int item_current0 = 0;
								const char* items0[] = { "clamp","toroid","mirror" };
								ImGui::Combo("block1 geo overflow", &item_current0, items0, IM_ARRAYSIZE(items0));
								block1GeoOverflow = item_current0;
								ImGui::Separator();
								ImGui::Checkbox("h mirror     ##block1", &block1HMirror);
								ImGui::SameLine();
								ImGui::Checkbox("v mirror     ##block1", &block1VMirror);
								ImGui::SameLine();
								ImGui::Checkbox("h flip       ##block1", &block1HFlip);
								ImGui::SameLine();
								ImGui::Checkbox("v flip       ##block1", &block1VFlip);
								ImGui::SameLine();
								ImGui::Checkbox("rotate mode  ##block1", &block1RotateMode);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=21;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==22)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_1 color eq"))
						{
							if(currentNode==22)
							{
								ImGui::Checkbox("midi/gui            ##block1Colorize", &block1ColorizeMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset                ##block1Colorize",&block1ColorizeReset);
								ImGui::SameLine();
								ImGui::Checkbox("on/off              ##block1Colorize",&block1ColorizeSwitch);
								ImGui::SameLine();
								ImGui::Checkbox("hsb/rgb             ##block1Colorize",&block1ColorizeHSB_RGB);
								
								if (block1ColorizeReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1Colorize[i] = 0.0f;
										block1ColorizeMidiActive[i] = 0;
									}
									block1ColorizeReset = 0;
									block1ColorizeSwitch=block1ColorizeHSB_RGB=0;
								}
								
								midi2Gui(block1ColorizeMidiActive, block1Colorize, block1ColorizeMidiGui);
								
								if(block1ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block1ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block1Colorize[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block1Colorize[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block1Colorize[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 1");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block1Colorize[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block1Colorize[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block1Colorize[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 2");
								ImGui::Separator();
								
								ImGui::SliderFloat("##7",&block1Colorize[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##8",&block1Colorize[7],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##9",&block1Colorize[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 3");
								ImGui::Separator();
								
								ImGui::SliderFloat("##10",&block1Colorize[9],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##11",&block1Colorize[10],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##12",&block1Colorize[11],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 4");
								ImGui::Separator();
								
								ImGui::SliderFloat("##13",&block1Colorize[12],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##14",&block1Colorize[13],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##15",&block1Colorize[14],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 5");
								ImGui::Separator();
								
								ImGui::PopItemWidth();
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=22;
							}
							ImGui::TreePop();	
						}	
						ImGui::Separator();
						if(nodeToClose==23)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_1 filters"))
						{
							if(currentNode==23)
							{
								ImGui::Checkbox("midi/gui                               ##block1filters ", &block1FiltersMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##block1filters ",&block1FiltersReset);
								if (block1FiltersReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1Filters[i] = 0.0f;
										block1FiltersMidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block1FiltersReset = 0;
								}
								
								midi2Gui(block1FiltersMidiActive, block1Filters, block1FiltersMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("blur amt   ##block1",&block1Filters[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("blur rad   ##block1",&block1Filters[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sharp amt  ##block1",&block1Filters[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sharp rad  ##block1",&block1Filters[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("filt boost ##block1",&block1Filters[4],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=23;
							}
							ImGui::TreePop();	
						}
						//END BLOCK 1 TAB	
						ImGui::EndTabItem();	
					}
					if (ImGui::BeginTabItem("B_1 lfo")){
						if(nodeToClose==24)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_1 geo lfo 1"))
						{
							if(currentNode==24)
							{
								ImGui::Checkbox("midi/gui                 ##block1Geo1Lfo1", &block1Geo1Lfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##block1Geo1Lfo1",&block1Geo1Lfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block1Geo1Lfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1Geo1Lfo1[i] = 0.0f;
										block1Geo1Lfo1MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block1Geo1Lfo1Reset = 0;
								}
								
								midi2Gui(block1Geo1Lfo1MidiActive, block1Geo1Lfo1, block1Geo1Lfo1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x <-> a      ##block1Lfo",&block1Geo1Lfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x <-> r      ##block1Lfo",&block1Geo1Lfo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y <-> a      ##block1Lfo",&block1Geo1Lfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <-> r      ##block1Lfo",&block1Geo1Lfo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <-> a      ##block1Lfo",&block1Geo1Lfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("z <-> r      ##block1Lfo",&block1Geo1Lfo1[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("rotate <-> a ##block1Lfo",&block1Geo1Lfo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> r ##block1Lfo",&block1Geo1Lfo1[7],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=24;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==25)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_1 geo lfo 2"))
						{
							if(currentNode==25)
							{
								ImGui::Checkbox("midi/gui                 ##block1Geo1Lfo2", &block1Geo1Lfo2MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##block1Geo1Lfo2",&block1Geo1Lfo2Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block1Geo1Lfo2Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1Geo1Lfo2[i] = 0.0f;
										block1Geo1Lfo2MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block1Geo1Lfo2Reset = 0;
								}
								
								midi2Gui(block1Geo1Lfo2MidiActive, block1Geo1Lfo2, block1Geo1Lfo2MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x stretch a  ##block1lfo",&block1Geo1Lfo2[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x stretch r  ##block1lfo",&block1Geo1Lfo2[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y stretch a  ##block1lfo",&block1Geo1Lfo2[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch r  ##block1lfo",&block1Geo1Lfo2[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear a    ##block1lfo",&block1Geo1Lfo2[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x shear r    ##block1lfo",&block1Geo1Lfo2[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y shear a    ##block1lfo",&block1Geo1Lfo2[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear r    ##block1lfo",&block1Geo1Lfo2[7],-1.0,1.0);	
								ImGui::Separator();
								ImGui::SliderFloat("kaleid sl a  ##block1lfo",&block1Geo1Lfo2[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid sl r  ##block1lfo",&block1Geo1Lfo2[9],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=25;
							}
							ImGui::TreePop();		
						}
						ImGui::Separator();
						if(nodeToClose==26)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_1 color eq lfo 1"))
						{	
							if(currentNode==26)
							{	
								ImGui::Checkbox("midi/gui             ##block1ColorizeLfo1", &block1ColorizeLfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset               ##block1ColorizeLfo1",&block1ColorizeLfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block1ColorizeLfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1ColorizeLfo1[i] = 0.0f;
										block1ColorizeLfo1MidiActive[i] = 0;
									}
									block1ColorizeLfo1Reset = 0;
								}
								
								midi2Gui(block1ColorizeLfo1MidiActive, block1ColorizeLfo1, block1ColorizeLfo1MidiGui);
								
								if(block1ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								if(block1ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block1ColorizeLfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block1ColorizeLfo1[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block1ColorizeLfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 1 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block1ColorizeLfo1[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block1ColorizeLfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block1ColorizeLfo1[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 1 r");
								ImGui::Separator();
								
								ImGui::SliderFloat("##7",&block1ColorizeLfo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##8",&block1ColorizeLfo1[7],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##9",&block1ColorizeLfo1[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 2 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##10",&block1ColorizeLfo1[9],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##11",&block1ColorizeLfo1[10],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##12",&block1ColorizeLfo1[11],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 2 r");
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=26;
							}
							ImGui::TreePop();	
						}	
						ImGui::Separator();						
						if(nodeToClose==27)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}				
						if (ImGui::TreeNode("B_1 color eq lfo 2"))
						{
							if(currentNode==27)
							{	
								ImGui::Checkbox("midi/gui             ##block1ColorizeLfo2", &block1ColorizeLfo2MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset               ##block1ColorizeLfo2",&block1ColorizeLfo2Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block1ColorizeLfo2Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1ColorizeLfo2[i] = 0.0f;
										block1ColorizeLfo2MidiActive[i] = 0;
									}
									block1ColorizeLfo2Reset = 0;
								}
								
								midi2Gui(block1ColorizeLfo2MidiActive, block1ColorizeLfo2, block1ColorizeLfo2MidiGui);
								
								if(block1ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block1ColorizeHSB_RGB==1){
									ImGui::Text("red                     ");
									ImGui::SameLine();
									ImGui::Text("green                   ");
									ImGui::SameLine();
									ImGui::Text("blue                    ");
								} 
								ImGui::Separator();
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block1ColorizeLfo2[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block1ColorizeLfo2[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block1ColorizeLfo2[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 3 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block1ColorizeLfo2[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block1ColorizeLfo2[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block1ColorizeLfo2[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 3 r");
								ImGui::Separator();
								
								ImGui::SliderFloat("##7",&block1ColorizeLfo2[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##8",&block1ColorizeLfo2[7],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##9",&block1ColorizeLfo2[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 4 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##10",&block1ColorizeLfo2[9],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##11",&block1ColorizeLfo2[10],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##12",&block1ColorizeLfo2[11],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 4 r");
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=27;
							}
							ImGui::TreePop();
						}	
						ImGui::Separator();	
						if(nodeToClose==28)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}	
						if (ImGui::TreeNode("B_1 color eq lfo 3"))
						{
							if(currentNode==28)
							{	
								ImGui::Checkbox("midi/gui             ##block1ColorizeLfo3", &block1ColorizeLfo3MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset               ##block1ColorizeLfo3",&block1ColorizeLfo3Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block1ColorizeLfo3Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block1ColorizeLfo3[i] = 0.0f;
										block1ColorizeLfo3MidiActive[i] = 0;
									}
									block1ColorizeLfo3Reset = 0;
								}
								
								midi2Gui(block1ColorizeLfo3MidiActive, block1ColorizeLfo3, block1ColorizeLfo3MidiGui);
								
								if(block1ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block1ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block1ColorizeLfo3[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block1ColorizeLfo3[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block1ColorizeLfo3[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 5 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block1ColorizeLfo3[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block1ColorizeLfo3[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block1ColorizeLfo3[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 5 r");
								ImGui::Separator();
							
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=28;
							}
							ImGui::TreePop();						
						}		
						//endBlock1LfoTab			
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("B_2 parameters")){
						if(nodeToClose==29)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if(ImGui::TreeNode("B_2 geo"))
						{
							if(currentNode==29)
							{
								ImGui::Checkbox("midi/gui                               ##block2Geo ", &block2GeoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##block2Geo ",&block2GeoReset);
								if (block2GeoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2Geo[i] = 0.0f;
										block2GeoMidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block2GeoReset = 0;
									block2HMirror=block2VMirror=block2HFlip=block2VFlip=block2RotateMode=0;
								}
								
								midi2Gui(block2GeoMidiActive, block2Geo, block2GeoMidiGui);	
								ImGui::Separator();
								ImGui::SliderFloat("x <->      ##block2",&block2Geo[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <->      ##block2",&block2Geo[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <->      ##block2",&block2Geo[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> ##block2",&block2Geo[3],-1.0,1.0);
							
								ImGui::Separator();
								ImGui::SliderFloat("x stretch  ##block2",&block2Geo[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch  ##block2",&block2Geo[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear    ##block2",&block2Geo[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear    ##block2",&block2Geo[7],-1.0,1.0);
								ImGui::Separator();
								
								ImGui::SliderFloat("kaleid amt ##block2",&block2Geo[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid slice ##block2",&block2Geo[9],-1.0,1.0);
								ImGui::Separator();
								
								static int item_current0 = 0;
								const char* items0[] = { "clamp","toroid","mirror" };
								ImGui::Combo("block2 geo overflow", &item_current0, items0, IM_ARRAYSIZE(items0));
								block2GeoOverflow = item_current0;
								ImGui::Separator();
								ImGui::Checkbox("h mirror     ##block2", &block2HMirror);
								ImGui::SameLine();
								ImGui::Checkbox("v mirror     ##block2", &block2VMirror);
								ImGui::SameLine();
								ImGui::Checkbox("h flip       ##block2", &block2HFlip);
								ImGui::SameLine();
								ImGui::Checkbox("v flip       ##block2", &block2VFlip);
								ImGui::SameLine();
								ImGui::Checkbox("rotate mode  ##block2", &block2RotateMode);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=29;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==30)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 color eq"))
						{
							if(currentNode==30)
							{
								ImGui::Checkbox("midi/gui            ##block2Colorize", &block2ColorizeMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset                ##block2Colorize",&block2ColorizeReset);
								ImGui::SameLine();
								ImGui::Checkbox("on/off              ##block2Colorize",&block2ColorizeSwitch);
								ImGui::SameLine();
								ImGui::Checkbox("HSB/RGB             ##block2Colorize",&block2ColorizeHSB_RGB);
								if (block2ColorizeReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2Colorize[i] = 0.0f;
										block2ColorizeMidiActive[i] = 0;
									}
									block2ColorizeReset = 0;
									block1ColorizeSwitch=block1ColorizeHSB_RGB=0;
								}
								
								midi2Gui(block2ColorizeMidiActive, block2Colorize, block2ColorizeMidiGui);
								
									
								
								if(block2ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block2ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block2Colorize[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block2Colorize[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block2Colorize[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 1");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block2Colorize[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block2Colorize[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block2Colorize[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 2");
								ImGui::Separator();
								
								ImGui::SliderFloat("##7",&block2Colorize[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##8",&block2Colorize[7],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##9",&block2Colorize[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 3");
								ImGui::Separator();
								
								ImGui::SliderFloat("##10",&block2Colorize[9],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##11",&block2Colorize[10],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##12",&block2Colorize[11],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 4");
								ImGui::Separator();
								
								ImGui::SliderFloat("##13",&block2Colorize[12],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##14",&block2Colorize[13],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##15",&block2Colorize[14],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 5");
								ImGui::Separator();
								
								ImGui::PopItemWidth();
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=30;
							}
							ImGui::TreePop();	
						}	
						ImGui::Separator();
						if(nodeToClose==31)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 filters"))
						{
							if(currentNode==31)
							{
								ImGui::Checkbox("midi/gui                               ##block2filters ", &block2FiltersMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset ##block2filters ",&block2FiltersReset);
								if (block2FiltersReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2Filters[i] = 0.0f;
										block2FiltersMidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block2FiltersReset = 0;
								}
								
								midi2Gui(block2FiltersMidiActive, block2Filters, block2FiltersMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("blur amt   ##block2",&block2Filters[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("blur rad   ##block2",&block2Filters[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("sharp amt  ##block2",&block2Filters[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("sharp rad  ##block2",&block2Filters[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("filt boost ##block2",&block2Filters[4],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=31;
							}
							ImGui::TreePop();
						}	
						//endBLOCK2parameters
						ImGui::EndTabItem();	
					}
					if (ImGui::BeginTabItem("B_2 lfo")){
						if(nodeToClose==32)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 geo lfo 1"))
						{
							if(currentNode==32)
							{
								ImGui::Checkbox("midi/gui                 ##block2Geo1Lfo1", &block2Geo1Lfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##block2Geo1Lfo1",&block2Geo1Lfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block2Geo1Lfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2Geo1Lfo1[i] = 0.0f;
										block2Geo1Lfo1MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block2Geo1Lfo1Reset = 0;
								}
								
								midi2Gui(block2Geo1Lfo1MidiActive, block2Geo1Lfo1, block2Geo1Lfo1MidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("x <-> a      ##block2Lfo",&block2Geo1Lfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x <-> r      ##block2Lfo",&block2Geo1Lfo1[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y <-> a      ##block2Lfo",&block2Geo1Lfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y <-> r      ##block2Lfo",&block2Geo1Lfo1[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("z <-> a      ##block2Lfo",&block2Geo1Lfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("z <-> r      ##block2Lfo",&block2Geo1Lfo1[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("rotate <-> a ##block2Lfo",&block2Geo1Lfo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("rotate <-> r ##block2Lfo",&block2Geo1Lfo1[7],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=32;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==33)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 geo lfo 2"))
						{
							if(currentNode==33)
							{
								ImGui::Checkbox("midi/gui                 ##block2Geo1Lfo2", &block2Geo1Lfo2MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##block2Geo1Lfo2",&block2Geo1Lfo2Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block2Geo1Lfo2Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2Geo1Lfo2[i] = 0.0f;
										block2Geo1Lfo2MidiActive[i] = 0;
									}
									//ADD ALL CHECKBOXES ETC HERE
									block2Geo1Lfo2Reset = 0;
								}
								
								midi2Gui(block2Geo1Lfo2MidiActive, block2Geo1Lfo2, block2Geo1Lfo2MidiGui);
								
								
								ImGui::Separator();
								ImGui::SliderFloat("x stretch a  ##block2lfo",&block2Geo1Lfo2[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x stretch r  ##block2lfo",&block2Geo1Lfo2[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y stretch a  ##block2lfo",&block2Geo1Lfo2[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y stretch r  ##block2lfo",&block2Geo1Lfo2[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("x shear a    ##block2lfo",&block2Geo1Lfo2[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("x shear r    ##block2lfo",&block2Geo1Lfo2[5],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("y shear a    ##block2lfo",&block2Geo1Lfo2[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("y shear r    ##block2lfo",&block2Geo1Lfo2[7],-1.0,1.0);
								
								
								ImGui::Separator();
								ImGui::SliderFloat("kaleid sl a  ##block2lfo",&block2Geo1Lfo2[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("kaleid sl r  ##block2lfo",&block2Geo1Lfo2[9],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=33;
							}
							ImGui::TreePop();		
						}
						ImGui::Separator();
						if(nodeToClose==34)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 color eq lfo 1"))
						{
							if(currentNode==34)
							{
								ImGui::Checkbox("midi/gui             ##block2ColorizeLfo1", &block2ColorizeLfo1MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset               ##block2ColorizeLfo1",&block2ColorizeLfo1Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block2ColorizeLfo1Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2ColorizeLfo1[i] = 0.0f;
										block2ColorizeLfo1MidiActive[i] = 0;
									}
									block2ColorizeLfo1Reset = 0;
								}
								
								midi2Gui(block2ColorizeLfo1MidiActive, block2ColorizeLfo1, block2ColorizeLfo1MidiGui);
								
								if(block2ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block2ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block2ColorizeLfo1[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block2ColorizeLfo1[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block2ColorizeLfo1[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 1 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block2ColorizeLfo1[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block2ColorizeLfo1[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block2ColorizeLfo1[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 1 r");
								ImGui::Separator();
								
								ImGui::SliderFloat("##7",&block2ColorizeLfo1[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##8",&block2ColorizeLfo1[7],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##9",&block2ColorizeLfo1[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 2 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##10",&block2ColorizeLfo1[9],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##11",&block2ColorizeLfo1[10],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##12",&block2ColorizeLfo1[11],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 2 r");
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=34;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==35)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 color eq lfo 2"))
						{
							if(currentNode==35)
							{	
								ImGui::Checkbox("midi/gui             ##block2ColorizeLfo2", &block2ColorizeLfo2MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset               ##block2ColorizeLfo2",&block2ColorizeLfo2Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block2ColorizeLfo2Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2ColorizeLfo2[i] = 0.0f;
										block2ColorizeLfo2MidiActive[i] = 0;
									}
									block2ColorizeLfo2Reset = 0;
								}
								
								midi2Gui(block2ColorizeLfo2MidiActive, block2ColorizeLfo2, block2ColorizeLfo2MidiGui);
								
								if(block2ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block2ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block2ColorizeLfo2[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block2ColorizeLfo2[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block2ColorizeLfo2[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 3 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block2ColorizeLfo2[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block2ColorizeLfo2[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block2ColorizeLfo2[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 3 r");
								ImGui::Separator();
								
								ImGui::SliderFloat("##7",&block2ColorizeLfo2[6],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##8",&block2ColorizeLfo2[7],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##9",&block2ColorizeLfo2[8],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 4 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##10",&block2ColorizeLfo2[9],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##11",&block2ColorizeLfo2[10],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##12",&block2ColorizeLfo2[11],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 4 r");
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=35;
							}
							ImGui::TreePop();	
						}
						ImGui::Separator();
						if(nodeToClose==36)
						{
							ImGui::SetNextItemOpen(false, ImGuiCond_Always);
							nodeToClose=-1;	
						}
						if (ImGui::TreeNode("B_2 color eq lfo 3"))
						{
							if(currentNode==36)
							{	
								ImGui::Checkbox("midi/gui             ##block2ColorizeLfo3", &block2ColorizeLfo3MidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset               ##block2ColorizeLfo3",&block2ColorizeLfo3Reset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (block2ColorizeLfo3Reset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										block2ColorizeLfo3[i] = 0.0f;
										block2ColorizeLfo3MidiActive[i] = 0;
									}
									block2ColorizeLfo3Reset = 0;
								}
								
								midi2Gui(block2ColorizeLfo3MidiActive, block2ColorizeLfo3, block2ColorizeLfo3MidiGui);
								
								if(block2ColorizeHSB_RGB==0){
									ImGui::Text("hue                    ");
									ImGui::SameLine();
									ImGui::Text("sat                    ");
									ImGui::SameLine();
									ImGui::Text("bri                    ");
								}
								 
								if(block2ColorizeHSB_RGB==1){
									ImGui::Text("red                    ");
									ImGui::SameLine();
									ImGui::Text("green                  ");
									ImGui::SameLine();
									ImGui::Text("blue                   ");
								} 
								ImGui::Separator();
								ImGui::PushItemWidth(windowWidthThird);
								
								ImGui::SliderFloat("##1",&block2ColorizeLfo3[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##2",&block2ColorizeLfo3[1],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##3",&block2ColorizeLfo3[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 5 a");
								ImGui::Separator();
								
								ImGui::SliderFloat("##4",&block2ColorizeLfo3[3],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##5",&block2ColorizeLfo3[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("##6",&block2ColorizeLfo3[5],-1.0,1.0);
								ImGui::SameLine();
								ImGui::Text("band 5 r");
								ImGui::Separator();
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=36;
							}
							ImGui::TreePop();
						}//end block1ColorizeLfo2
						ImGui::EndTabItem();			
						//ImGui::TreePop();
					}//end BLOCK2 lfos tab item	
						
					if (ImGui::BeginTabItem("matrix mixer")){
						//static int item_current0 = 0;
						static int item_current1 = 0;
						static int item_current2 = 0;
						
						ImGui::PushItemWidth(windowWidthThird);
						
						ImGui::Checkbox("midi/gui                              ##matrixMix", &matrixMixMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset        ##matrixMix",&matrixMixReset);
						if (matrixMixReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								matrixMix[i] = 0.0f;
								matrixMixMidiActive[i] = 0;
							}
							matrixMixReset = 0;
						}
						
						const char* items1[] = {  "linear fade", "additive","difference","multiplicitive","dodge" };
						ImGui::Combo("type             ", &item_current1, items1, IM_ARRAYSIZE(items1));
						matrixMixType = item_current1;
						ImGui::SameLine();
						const char* items2[] = { "clamp", "wrap","foldover" };
						ImGui::Combo("overflow", &item_current2, items2, IM_ARRAYSIZE(items2));
						matrixMixOverflow = item_current2;
						
						ImGui::Text(" ");
						
						midi2Gui(matrixMixMidiActive, matrixMix, matrixMixMidiGui);
						if( finalKeyOrder==0){
							ImGui::Text("B_2     ->   ");
						}
						if( finalKeyOrder==1){
							ImGui::Text("B_1     ->   ");
						}
						ImGui::SameLine();
						ImGui::Text("red                       ");
						ImGui::SameLine();
						ImGui::Text("green                      ");
						ImGui::SameLine();
						ImGui::Text("blue                  ");
						ImGui::Separator();
						
						if( finalKeyOrder==0){
							ImGui::Text("B_1       red");	
						}
						if( finalKeyOrder==1){
							ImGui::Text("B_2       red");	
						}
						ImGui::SameLine();
						ImGui::SliderFloat("##1",&matrixMix[0],-1.0,1.0);
						ImGui::SameLine();
						ImGui::Text("   ");
						ImGui::SameLine();
						ImGui::SliderFloat("##2",&matrixMix[1],-1.0,1.0);
						ImGui::SameLine();
						ImGui::Text("   ");
						ImGui::SameLine();
						ImGui::SliderFloat("##3",&matrixMix[2],-1.0,1.0);
						
						ImGui::Separator();
						
						if( finalKeyOrder==0){
							ImGui::Text("B_1     green");	
						}
						if( finalKeyOrder==1){
							ImGui::Text("B_2     green");	
						}
						ImGui::SameLine();
						ImGui::SliderFloat("##4",&matrixMix[3],-1.0,1.0);
						ImGui::SameLine();
						ImGui::Text("   ");
						ImGui::SameLine();
						ImGui::SliderFloat("##5",&matrixMix[4],-1.0,1.0);
						ImGui::SameLine();
						ImGui::Text("   ");
						ImGui::SameLine();
						ImGui::SliderFloat("##6",&matrixMix[5],-1.0,1.0);
						
						ImGui::Separator();
						
						if( finalKeyOrder==0){
							ImGui::Text("B_1      blue");	
						}
						if( finalKeyOrder==1){
							ImGui::Text("B_2      blue");	
						}
						ImGui::SameLine();
						ImGui::SliderFloat("##7",&matrixMix[6],-1.0,1.0);
						ImGui::SameLine();
						ImGui::Text("   ");
						ImGui::SameLine();
						ImGui::SliderFloat("##8",&matrixMix[7],-1.0,1.0);
						ImGui::SameLine();
						ImGui::Text("   ");
						ImGui::SameLine();
						ImGui::SliderFloat("##9",&matrixMix[8],-1.0,1.0);
						
						ImGui::Separator();

						ImGui::PopItemWidth();
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("final mix and key")){
						
						static int item_current0 = 0;
						static int item_current1 = 0;
						static int item_current2 = 0;
						static int item_current3 = 0;
						
						  
						ImGui::Checkbox("midi/gui                 ##final", &finalMixAndKeyMidiGui);
						ImGui::SameLine();
						ImGui::Checkbox("reset          ##final",&finalMixAndKeyReset);
						ImGui::SameLine();
						if (finalMixAndKeyReset == 1) {
							for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
								finalMixAndKey[i] = 0.0f;
								finalMixAndKeyMidiActive[i] = 0;
							}
							finalMixAndKeyReset = 0;
						}
						
						midi2Gui(finalMixAndKeyMidiActive, finalMixAndKey, finalMixAndKeyMidiGui);
		                
						ImGui::Separator();
						const char* items1[] = { "linear fade", "additive","difference","multiplicitive","dodge" };
						ImGui::Combo("mix type       ##final ", &item_current1, items1, IM_ARRAYSIZE(items1));
						finalMixType = item_current1;
						ImGui::SameLine();
						ImGui::SliderFloat("mix ##final",&finalMixAndKey[0],-1.0,1.0);
						ImGui::Separator();
						
						const char* items2[] = {"clamp", "wrap","foldover" };
						ImGui::Combo("overflow       ##finalMix", &item_current2, items2, IM_ARRAYSIZE(items2));
						finalMixOverflow = item_current2;
						ImGui::SameLine();
						const char* items3[] = { "lumakey","chromakey" };
						ImGui::Combo("key mode ##final", &item_current3, items3, IM_ARRAYSIZE(items3));
						finalKeyMode = item_current3;
						ImGui::Separator();
					
						if(finalKeyMode==0){
							ImGui::SliderFloat("key red        ##final",&finalMixAndKey[1],-1.0,1.0);
							ImGui::SameLine();
							ImGui::SliderFloat("key green      ##final",&finalMixAndKey[1],-1.0,1.0);
							ImGui::Separator();
							ImGui::SliderFloat("key blue       ##final",&finalMixAndKey[1],-1.0,1.0);
							ImGui::SameLine();
							finalMixAndKey[2]=finalMixAndKey[3]=finalMixAndKey[1];
							
						}
						
						if(finalKeyMode==1){
							ImGui::SliderFloat("key red        ##final",&finalMixAndKey[1],-1.0,1.0);
							ImGui::SameLine();
							ImGui::SliderFloat("key green      ##final",&finalMixAndKey[2],-1.0,1.0);
							ImGui::Separator();
							ImGui::SliderFloat("key blue       ##final",&finalMixAndKey[3],-1.0,1.0);
							ImGui::SameLine();
						}
						
						ImGui::ColorButton("testingColorButton 1", ImVec4(finalMixAndKey[1], finalMixAndKey[2], finalMixAndKey[3], 1.0), 0, ImVec2(20, 20));
						ImGui::SameLine();
						ImGui::Text("key value color");
						
						ImGui::Separator();
						ImGui::SliderFloat("key threshold  ##final",&finalMixAndKey[4],-1.0,1.0);
						ImGui::SameLine();
						ImGui::SliderFloat("key soft ##final",&finalMixAndKey[5],-1.0,1.0);
						
						ImGui::EndTabItem();	
					}
					if (ImGui::BeginTabItem("mix lfo")){
					
						if(secretMenuSwitch==1){
							if(nodeToClose==37)
							{
								ImGui::SetNextItemOpen(false, ImGuiCond_Always);
								nodeToClose=-1;	
							}
							if (ImGui::TreeNode("matrix mixer lfo 1"))
							{
								if(currentNode==37)
								{
									ImGui::Checkbox("midi/gui             ##matrixMixLfo1", &matrixMixLfo1MidiGui);
									ImGui::SameLine();
									ImGui::Checkbox("reset        ##matrixMixLfo1",&matrixMixLfo1Reset);
									ImGui::SameLine();
								    ImGui::Text("a := lfo amplitude     r := lfo rate");
									if (matrixMixLfo1Reset == 1) {
										for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
											matrixMixLfo1[i] = 0.0f;
											matrixMixLfo1MidiActive[i] = 0;
										}
										matrixMixLfo1Reset = 0;
									}
									
									ImGui::Separator();
									
									midi2Gui(matrixMixLfo1MidiActive, matrixMixLfo1, matrixMixLfo1MidiGui);
									
									if( finalKeyOrder==0){
										ImGui::Text("B_2   ->    ");
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_1   ->    ");
									}
									ImGui::SameLine();
									ImGui::Text("red                       ");
									ImGui::SameLine();
									ImGui::Text("green                      ");
									ImGui::SameLine();
									ImGui::Text("blue                  ");
									ImGui::Separator();
									
									ImGui::PushItemWidth(windowWidthThird);
									
									if( finalKeyOrder==0){
										ImGui::Text("B_1  red   a");	
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_2  red   a");	
									}
									ImGui::SameLine();
									ImGui::SliderFloat("##1",&matrixMixLfo1[0],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##2",&matrixMixLfo1[1],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##3",&matrixMixLfo1[2],-1.0,1.0);
									
									ImGui::Separator();
									
									if( finalKeyOrder==0){
										ImGui::Text("B_1  red   r");	
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_2  red   r");	
									}
									ImGui::SameLine();
									ImGui::SliderFloat("##4",&matrixMixLfo1[3],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##5",&matrixMixLfo1[4],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##6",&matrixMixLfo1[5],-1.0,1.0);
									
									ImGui::Separator();
									
									if( finalKeyOrder==0){
										ImGui::Text("B_1 green  a");	
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_2 green  a");	
									}
									ImGui::SameLine();
									ImGui::SliderFloat("##7",&matrixMixLfo1[6],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##8",&matrixMixLfo1[7],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##9",&matrixMixLfo1[8],-1.0,1.0);
									
									ImGui::Separator();
									
									if( finalKeyOrder==0){
										ImGui::Text("B_1 green  r");	
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_2 green  r");	
									}
									ImGui::SameLine();
									ImGui::SliderFloat("##10",&matrixMixLfo1[9],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##11",&matrixMixLfo1[10],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##12",&matrixMixLfo1[11],-1.0,1.0);
									
									ImGui::PopItemWidth();
								}
								else
								{
									nodeToClose=currentNode;
									currentNode=37;
								}
								ImGui::TreePop();		
							}
							ImGui::Separator();
							if(nodeToClose==38)
							{
								ImGui::SetNextItemOpen(false, ImGuiCond_Always);
								nodeToClose=-1;	
							}
							if (ImGui::TreeNode("matrix mixer lfo 2")){
								if(currentNode==38)
								{
									ImGui::Checkbox("midi/gui             ##matrixMixLfo2", &matrixMixLfo2MidiGui);
									ImGui::SameLine();
									ImGui::Checkbox("reset        ##matrixMixLfo2",&matrixMixLfo2Reset);
									ImGui::SameLine();
								    ImGui::Text("a := lfo amplitude     r := lfo rate");
									if (matrixMixLfo2Reset == 1) {
										for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
											matrixMixLfo2[i] = 0.0f;
											matrixMixLfo2MidiActive[i] = 0;
										}
										matrixMixLfo2Reset = 0;
									}
									
									ImGui::Separator();
									
									midi2Gui(matrixMixLfo2MidiActive, matrixMixLfo2, matrixMixLfo2MidiGui);
									
									if( finalKeyOrder==0){
										ImGui::Text("B_2   ->    ");
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_1   ->    ");
									}
									ImGui::SameLine();
									ImGui::Text("red                       ");
									ImGui::SameLine();
									ImGui::Text("green                      ");
									ImGui::SameLine();
									ImGui::Text("blue                  ");
									ImGui::Separator();
									
									ImGui::PushItemWidth(windowWidthThird);
									
									if( finalKeyOrder==0){
										ImGui::Text("B_1  blue  a");	
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_2  blue  a");	
									}
									ImGui::SameLine();
									ImGui::SliderFloat("##1",&matrixMixLfo2[0],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##2",&matrixMixLfo2[1],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##3",&matrixMixLfo2[2],-1.0,1.0);
									
									ImGui::Separator();
									
									if( finalKeyOrder==0){
										ImGui::Text("B_1  blue  r");	
									}
									if( finalKeyOrder==1){
										ImGui::Text("B_2  blue  r");	
									}
									ImGui::SameLine();
									ImGui::SliderFloat("##4",&matrixMixLfo2[3],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##5",&matrixMixLfo2[4],-1.0,1.0);
									ImGui::SameLine();
									ImGui::Text("   ");
									ImGui::SameLine();
									ImGui::SliderFloat("##6",&matrixMixLfo2[5],-1.0,1.0);
									ImGui::Separator();
									ImGui::PopItemWidth();
								}
								else
								{
									nodeToClose=currentNode;
									currentNode=38;
								}
								ImGui::TreePop();
							}

						}//end secret menu
						ImGui::Separator();
							if(nodeToClose==39)
							{
								ImGui::SetNextItemOpen(false, ImGuiCond_Always);
								nodeToClose=-1;	
							}
						if (ImGui::TreeNode("final mix and key lfo"))
						{
							if(currentNode==39)
							{
								ImGui::Checkbox("midi/gui                 ##finalmixandkey", &finalMixAndKeyLfoMidiGui);
								ImGui::SameLine();
								ImGui::Checkbox("reset        ##finalmixandkey",&finalMixAndKeyLfoReset);
								ImGui::SameLine();
								ImGui::Text("a := lfo amplitude     r := lfo rate");
								if (finalMixAndKeyLfoReset == 1) {
									for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
										finalMixAndKeyLfo[i] = 0.0f;
										finalMixAndKeyLfoMidiActive[i] = 0;
									}
									finalMixAndKeyLfoReset = 0;
								}
								
								midi2Gui(finalMixAndKeyLfoMidiActive, finalMixAndKeyLfo, finalMixAndKeyLfoMidiGui);
								
								ImGui::Separator();
								ImGui::SliderFloat("mix a       ##final",&finalMixAndKeyLfo[0],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("mix r       ##final",&finalMixAndKeyLfo[1],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky thresh a ##final",&finalMixAndKeyLfo[2],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky thresh r ##final",&finalMixAndKeyLfo[3],-1.0,1.0);
								ImGui::Separator();
								ImGui::SliderFloat("ky soft a   ##final",&finalMixAndKeyLfo[4],-1.0,1.0);
								ImGui::SameLine();
								ImGui::SliderFloat("ky soft r   ##final",&finalMixAndKeyLfo[5],-1.0,1.0);
							}
							else
							{
								nodeToClose=currentNode;
								currentNode=39;
							}
							ImGui::TreePop();
						}	
						
						ImGui::EndTabItem();	
					}//end finalmix lfo
					ImGui::EndTabBar();
				}
				ImGui::EndTabItem();		
			}//end block3
       		ImGui::PopStyleColor(12);	
        	ImGui::EndTabBar();
        }//end global tab
		
		
		ImGui::Checkbox("click to order from the secret menu",&secretMenuSwitch);
	}
	ImGui::PopStyleColor(1);
	ImGui::PopItemWidth();
	
	ImGui::End();
	//ofxImGui::EndWindow(mainSettings);


	gui.end();
}

//--------------------------------------------------------------
void GuiApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void GuiApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void GuiApp::keyPressed(int key) {
	/*
    if (key == 'a') {tweakHue += .01; cout<<"hue = "<<tweakHue<<endl;}
    if (key == 'z') {tweakHue -= .01; cout<<"hue = "<<tweakHue<<endl;}
    
    if (key == 's') {tweakSat += .01; cout<<"sat = "<<tweakSat<<endl;}
    if (key == 'x') {tweakSat -= .01; cout<<"sat = "<<tweakSat<<endl;}
    */
    if (key == 'a') {sliderWidth += .1; cout<<"xpos = "<<sliderWidth<<endl;}
    if (key == 'z') {sliderWidth -= .1; cout<<"xpos = "<<sliderWidth<<endl;}
    
    if (key == 's') {tweakSat += .01; cout<<"tweakSat = "<<tweakSat<<endl;}
    if (key == 'x') {tweakSat -= .01; cout<<"tweakSat = "<<tweakSat<<endl;}
    
    if (key == 'd') {tweakBri += .01; cout<<"bri = "<<tweakBri<<endl;}
    if (key == 'c') {tweakBri -= .01; cout<<"bri = "<<tweakBri<<endl;}
    //if(key=='0'){coutMidiSwitch=!coutMidiSwitch;}
    
}

//--------------------------------------------------------------
void GuiApp::keyReleased(int key) {
}
//--------------------------------------------------------------
void GuiApp::midiSetup(){
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual 		port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
	
}
//--------------------------------------------------------------
void GuiApp::midibiz(){
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
	
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                
                //How to Midi Map
                //uncomment the line that says cout<<message control etc
                //run the code and look down in the console
                //when u move a knob on yr controller keep track of the number that shows up
                //that is the cc value of the knob
                //then go down to the part labled 'MIDIMAPZONE'
                //and change the numbers for each if message.control== statement to the values
                //on yr controller
                
                if(coutMidiSwitch==1){
               		//cout << "message.control"<< message.control<< endl;
                	//cout << "message.value"<< message.value<< endl;
                }
				
				if(message.control>15 && message.control<24){
                    midiCC[message.control-16]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    if(coutMidiSwitch==1){
                    cout << "midiCC[message.control-16] "<<midiCC[message.control-16]<< endl;
                    cout << "message.value"<< message.value<< endl;
                    }
                }
                
                if(message.control>119 && message.control<128){
                    midiCC[message.control-120+8]=(message.value-MIDI_MAGIC)/MIDI_MAGIC;
                    if(coutMidiSwitch==1){
                    cout << "midiCC[message.control-120+8] "<<midiCC[message.control-120+8]<< endl;
                    cout << "message.value"<< message.value<< endl;
                    }
                }
				
                /* the nanostudio kontrols
                //c1 maps to fb0 hue attenuation
                if(message.control==20){
                    c1=(message.value-63.0)/63.0;
                   //  c1=(message.value)/127.00;
                    
                }
                
   				}
                */
             
			}//endifmessagestatus==
		}//endifmessagestatus<
	}//endfori	
}//endmidibiz
//-----------------------------------------------------------------------------------
void GuiApp::resetAll(){
	allArrayClear();
	allButtonsClear();
	
	fb1DelayTime=1;
	fb2DelayTime=1;
}

//-----------------------------------------------------------------------------------
void GuiApp::allButtonsClear(){
	ch1VMirror=ch1HMirror=ch1VFlip=ch1HFlip=ch1HueInvert=ch1SaturationInvert=ch1BrightInvert=ch1RGBInvert=ch1Solarize=0;
	ch2VMirror=ch2HMirror=ch2VFlip=ch2HFlip=ch2HueInvert=ch2SaturationInvert=ch2BrightInvert=ch2RGBInvert=ch2Solarize=0;
	
	fb1HueInvert=fb1SaturationInvert=fb1BrightInvert=0;
	fb1HMirror=fb1VMirror=fb1RotateMode=0;
	
	block2InputVMirror=block2InputHMirror=block2InputVFlip=block2InputHFlip=block2InputHueInvert=0;
	block2InputSaturationInvert=block2InputBrightInvert=block2InputRGBInvert=block2InputSolarize=0;
	
	fb2HueInvert=fb2SaturationInvert=fb2BrightInvert=0;
	fb2HMirror=fb2VMirror=fb2RotateMode=0;
	
	block1HMirror=block1VMirror=block1HFlip=block1VFlip=block1RotateMode=0;
	block2HMirror=block2VMirror=block2HFlip=block2VFlip=block2RotateMode=0;
	block1ColorizeSwitch=block1ColorizeHSB_RGB=0;
	block1ColorizeSwitch=block1ColorizeHSB_RGB=0;
	
}



//-----------------------------------------------------------------------------------
void GuiApp::block1ResetAll(){
	fb1ResetAll();
	block1InputResetAll();
}

//-----------------------------------------------------------------------------------
void GuiApp::block1InputResetAll(){
	for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
		ch1Adjust[i]=0.0f;
		ch1AdjustMidiActive[i]=0;
		
		ch2MixAndKey[i]=0.0f;
		ch2MixAndKeyMidiActive[i]=0;
		
		ch2MixAndKeyLfo[i]=0.0f;
		ch2MixAndKeyLfoMidiActive[i]=0;
		
		ch2Adjust[i]=0.0f;
		ch2AdjustMidiActive[i]=0;
		
		//input lfo
		ch1AdjustLfo[i]=0.0f;
		ch1AdjustLfoMidiActive[i]=0;
		
		ch2AdjustLfo[i]=0.0f;
		ch2AdjustLfoMidiActive[i]=0;
	}	
	
	ch1VMirror=ch1HMirror=ch1VFlip=ch1HFlip=ch1HueInvert=ch1SaturationInvert=ch1BrightInvert=ch1RGBInvert=ch1Solarize=0;
	
	ch2VMirror=ch2HMirror=ch2VFlip=ch2HFlip=ch2HueInvert=ch2SaturationInvert=ch2BrightInvert=ch2RGBInvert=ch2Solarize=0;
}

//-----------------------------------------------------------------------------------
void GuiApp::fb1ResetAll(){
	for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
		fb1MixAndKey[i]=0.0f;
		fb1MixAndKeyMidiActive[i]=0;
		
		fb1Geo1[i]=0.0f;
		fb1Geo1MidiActive[i]=0;
		
		fb1Color1[i]=0.0f;
		fb1Color1MidiActive[i]=0;
		
		fb1Filters[i]=0.0f;
		fb1FiltersMidiActive[i]=0;
		
		fb1MixAndKeyLfo[i]=0.0f;
		fb1MixAndKeyLfoMidiActive[i]=0;
		
		fb1Geo1Lfo1[i]=0.0f;
		fb1Geo1Lfo1MidiActive[i]=0;
		
		fb1Geo1Lfo2[i]=0.0f;
		fb1Geo1Lfo2MidiActive[i]=0;
		
		fb1Color1Lfo1[i]=0.0f;
		fb1Color1Lfo1MidiActive[i]=0;
	}
	fb1DelayTime=1;
	fb1HueInvert=fb1SaturationInvert=fb1BrightInvert=0;

	fb1HMirror=fb1VMirror=fb1RotateMode=0;
}

//-----------------------------------------------------------------------------------
void GuiApp::block2ResetAll(){
	fb2ResetAll();
	block2InputResetAll();
}


//-----------------------------------------------------------------------------------
void GuiApp::block2InputResetAll(){
	for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
		block2InputAdjust[i]=0.0f;
		block2InputAdjustMidiActive[i]=0;
		
		//input lfo
		block2InputAdjustLfo[i]=0.0f;
		block2InputAdjustLfoMidiActive[i]=0;
		
		}	
	
	block2InputVMirror=block2InputHMirror=block2InputVFlip=block2InputHFlip=block2InputHueInvert=0;
	block2InputSaturationInvert=block2InputBrightInvert=block2InputRGBInvert=block2InputSolarize=0;
		
}


//-----------------------------------------------------------------------------------
void GuiApp::fb2ResetAll(){
	for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
		fb2MixAndKey[i]=0.0f;
		fb2MixAndKeyMidiActive[i]=0;
		
		fb2Geo1[i]=0.0f;
		fb2Geo1MidiActive[i]=0;
		
		fb2Color1[i]=0.0f;
		fb2Color1MidiActive[i]=0;
		
		fb2Filters[i]=0.0f;
		fb2FiltersMidiActive[i]=0;
		
		fb2MixAndKeyLfo[i]=0.0f;
		fb2MixAndKeyLfoMidiActive[i]=0;
		
		fb2Geo1Lfo1[i]=0.0f;
		fb2Geo1Lfo1MidiActive[i]=0;
		
		fb2Geo1Lfo2[i]=0.0f;
		fb2Geo1Lfo2MidiActive[i]=0;
		
		fb2Color1Lfo1[i]=0.0f;
		fb2Color1Lfo1MidiActive[i]=0;
	}
	fb2DelayTime=1;
	fb2HueInvert=fb2SaturationInvert=fb2BrightInvert=0;

	fb2HMirror=fb2VMirror=fb2RotateMode=0;
}
//---------------------------------------------------------------------------------------
void GuiApp::block3ResetAll(){
	for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
		//block1 param
		block1Geo[i]=0.0f;
		block1GeoMidiActive[i]=0;
		
		block1Colorize[i]=0.0f;
		block1ColorizeMidiActive[i]=0;
		
		block1Filters[i]=0.0f;
		block1FiltersMidiActive[i]=0;
		
		//block1 lfo
		block1Geo1Lfo1[i]=0.0f;
		block1Geo1Lfo1MidiActive[i]=0;
		
		block1Geo1Lfo2[i]=0.0f;
		block1Geo1Lfo2MidiActive[i]=0;
		
		block1ColorizeLfo1[i]=0.0f;
		block1ColorizeLfo1MidiActive[i]=0;
		
		block1ColorizeLfo2[i]=0.0f;
		block1ColorizeLfo2MidiActive[i]=0;
		
		block1ColorizeLfo3[i]=0.0f;
		block1ColorizeLfo3MidiActive[i]=0;
		
		//block2 params
		block2Geo[i]=0.0f;
		block2GeoMidiActive[i]=0;
		
		block2Colorize[i]=0.0f;
		block2ColorizeMidiActive[i]=0;
		
		block2Filters[i]=0.0f;
		block2FiltersMidiActive[i]=0;
		
		//block2 lfo
		block2Geo1Lfo1[i]=0.0f;
		block2Geo1Lfo1MidiActive[i]=0;
		
		block2Geo1Lfo2[i]=0.0f;
		block2Geo1Lfo2MidiActive[i]=0;
		
		block2ColorizeLfo1[i]=0.0f;
		block2ColorizeLfo1MidiActive[i]=0;
		
		block2ColorizeLfo2[i]=0.0f;
		block2ColorizeLfo2MidiActive[i]=0;
		
		block2ColorizeLfo3[i]=0.0f;
		block2ColorizeLfo3MidiActive[i]=0;
		
		
		//final mix params	
		matrixMix[i]=0.0f;
		matrixMixMidiActive[i]=0;
		
		finalMixAndKey[i]=0.0f;
		finalMixAndKeyMidiActive[i]=0;
		
		//final mix lfo
		matrixMixLfo1[i]=0.0f;
		matrixMixLfo1MidiActive[i]=0;
		
		matrixMixLfo2[i]=0.0f;
		matrixMixLfo2MidiActive[i]=0;
		
		finalMixAndKeyLfo[i]=0.0f;
		finalMixAndKeyLfoMidiActive[i]=0;
			
	
	}
	block1HMirror=block1VMirror=block1HFlip=block1VFlip=block1RotateMode=0;
	block2HMirror=block2VMirror=block2HFlip=block2VFlip=block2RotateMode=0;
	block1ColorizeSwitch=block1ColorizeHSB_RGB=0;
	block1ColorizeSwitch=block1ColorizeHSB_RGB=0;	

}

//------------------------------------------------------------------------
void GuiApp::randomizeControls(){
	for (int i = 0; i < PARAMETER_ARRAY_LENGTH; i++) {
		//block1 param
		block1Geo[i]+=.5*ofRandomf()*ofRandomf();
		
		block1Colorize[i]+=.5*ofRandomf()*ofRandomf();
				
		block1Filters[i]+=.5*ofRandomf()*ofRandomf();
				
		//block1 lfo
		block1Geo1Lfo1[i]+=.5*ofRandomf()*ofRandomf();
				
		block1Geo1Lfo2[i]+=.5*ofRandomf()*ofRandomf();
				
		block1ColorizeLfo1[i]+=.5*ofRandomf()*ofRandomf();
				
		block1ColorizeLfo2[i]+=.5*ofRandomf()*ofRandomf();
			
		block1ColorizeLfo3[i]+=.5*ofRandomf()*ofRandomf();
				
		//block2 params
		block2Geo[i]+=.5*ofRandomf()*ofRandomf();
				
		block2Colorize[i]+=.5*ofRandomf()*ofRandomf();
		
		block2Filters[i]+=.5*ofRandomf()*ofRandomf();
			
		//block2 lfo
		block2Geo1Lfo1[i]+=.5*ofRandomf()*ofRandomf();
				
		block2Geo1Lfo2[i]+=.5*ofRandomf()*ofRandomf();
				
		block2ColorizeLfo1[i]+=.5*ofRandomf()*ofRandomf();
			
		block2ColorizeLfo2[i]+=.5*ofRandomf()*ofRandomf();
			
		block2ColorizeLfo3[i]+=.5*ofRandomf()*ofRandomf();
		
		//final mix params	
		matrixMix[i]+=.5*ofRandomf()*ofRandomf();
			
		finalMixAndKey[i]+=.5*ofRandomf()*ofRandomf();
		
		//final mix lfo
		matrixMixLfo1[i]+=.5*ofRandomf()*ofRandomf();
				
		matrixMixLfo2[i]+=.5*ofRandomf()*ofRandomf();
				
		finalMixAndKeyLfo[i]+=.5*ofRandomf()*ofRandomf();
		
		
	}


}
