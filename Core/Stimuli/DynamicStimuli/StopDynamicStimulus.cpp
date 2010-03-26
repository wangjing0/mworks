/*
 *  StopDynamicStimulus.cpp
 *  DynamicStimulusPlugins
 *
 *  Created by bkennedy on 8/17/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "StopDynamicStimulus.h"

StopDynamicStimulus::StopDynamicStimulus(shared_ptr<DynamicStimulusDriver> the_dynamic_stimulus) : 
Action() 
{
	setName("StopAction");
	dynamic_stimulus=the_dynamic_stimulus;
}

bool StopDynamicStimulus::execute() {	
	dynamic_stimulus->stop();
    return true;
}
