/*
 * SpeedBoost.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: Edward
 */

#include "ForwardBoost.h"

#include "Log/TextLog.h"
#include "Log/MessageData.h"
#include "Log/SystemData.h"

namespace commands
{

using namespace dman;

void ForwardBoost::Initialize()
{
	if(oi_ == nullptr)
	{
		Cancel();
		TextLog::Log(MessageData(MessageData::ERR), SystemData("OI", "ForwardBoost", "Command")) <<
				"Initialization failed";
		return;
	}

	previous_power_ = oi_->get_forward_multiplier();
	oi_->SetForwardMultiplier(power_);
	TextLog::Log(MessageData(MessageData::INFO), SystemData("OI", "ForwardBoost", "Command")) <<
			"Initialized, setting power to: " << power_;
}

void ForwardBoost::End()
{
	if(oi_ == nullptr)
		return;

	oi_->SetForwardMultiplier(previous_power_);
	TextLog::Log(MessageData(MessageData::INFO), SystemData("OI", "ForwardBoost", "Command")) <<
			"Ending, reverting power to: " << previous_power_;
}

void ForwardBoost::Interrupted()
{
	TextLog::Log(MessageData(MessageData::INFO), SystemData("OI", "ForwardBoost", "Command")) <<
			"Interrupted";
	End();
}

}


