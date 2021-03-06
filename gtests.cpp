#include "gtest/gtest.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include "Cst.hpp"
#include "Network.hpp"

using namespace std; 

int main(int argc, char **argv ){
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 
		
}
//Test that the potential of the membran is good calculated with a Iext =1.0
TEST(NeuronTest, MembranPotential) {
	
	Neuron neuron1;
	
	neuron1.pot_calcul(1, 1.0, 0, 0);
	EXPECT_EQ(20.0*(1-exp(-1.0/20.0)), neuron1.getMemb_pot());
  
}
//test that the neuron is really refractory and reinitialize its membrane 
TEST(NeuronTest, refractoryPotClean) {
	
	Neuron neuron1; 
	if(neuron1.getisRefractory() == true){
		
		EXPECT_EQ(0, neuron1.getMemb_pot()); 
	}
	
}
//test that the attribute of the neuron isRefractory turn to true after a neuron spikes (with a Iext very high -> 30 to be sure that a neuron spikes) 
TEST(NeuronTest, RefractoryTime){
	
	Neuron N(E); 

	for(int i(0); i<20; ++i){
	
		N.update_neuron(300, 0);
	
		}EXPECT_EQ(N.getisRefractory(), true);
	
	
}
//to be sure that a Neuron doesn't spikes with a Iext of 1.0 and no Poisson law 
TEST(NeuronTest, numberOfSpikesForIext1){
	
	Neuron N(E); 
	
	for (int i(0); i<1000; ++i){
		
		N.update_neuron(1.0, 0); 
		
		EXPECT_EQ(N.getNumbSpikes(), 0); 		
	}
}
//check that there is suffisantly neurons wich spikes (4 spikes here) with a Iext of 1.01 for 4000 steps
TEST(NeuronTest, numberOfSpikesForIext101){
	Neuron N(E); 
	for (int i(0); i<4000; ++i){
		N.update_neuron(1.01, 0);	
	}
	EXPECT_EQ(N.getNumbSpikes(), 4); 
}

//check that getIsSpiking works great with no Iext
TEST(NeuronTest, getIsSpiking){
	
	Neuron N(E); 
	N.update_neuron(0, 0); 
	int step = 2; 
	EXPECT_EQ(N.getIsSpiking(step), false);	
}
//check that The Je is arriving with a good delay with the help of the buffer 
TEST(NeuronTest, SetBufferDelay){

	Neuron N(E); 
	N.setBuffer(D,Je); 
	for (int i(0); i<16; ++i){
		N.update_neuron(0,0);  
	}
	EXPECT_EQ(N.getMemb_pot(), 0.1); 
}

//test the number of neurons generated in the networks (should be N=12500)
TEST(NertworkTest, NumberOfNeurons){
	
	Network network; 
	network.simulation(); 	
	EXPECT_EQ(N, network.getNumbNeurons());
	
}
