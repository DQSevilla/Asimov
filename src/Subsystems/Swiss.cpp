#include "Subsystems/Swiss.h"
#include "WPILib.h"
#include <cmath>



using Swiss = subsystems::Swiss;

using state_t = subsystems::Swiss::state_t;

double Swiss::tickToDegree = 90; //measure and change later
double Swiss::maxVelocity = 18;

double Swiss::states[] = {
		[retract] = -.032,
		[horizontal] = -.63,
		[cheval_down] = -.7,
		[port_down] = -.768
};


Swiss::Swiss() : Subsystem("Swiss"){
	swisstalon = new CANTalon(7);
	swisstalon->SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogPot);
	swisstalon->ConfigPotentiometerTurns(1);
	swisstalon->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);
	swisstalon->ConfigReverseLimit(states[port_down]);
	swisstalon->ConfigForwardLimit(states[retract]);
	swisstalon->ConfigLimitMode(CANTalon::LimitMode::kLimitMode_SoftPositionLimits);
	swisstalon->SetSensorDirection(true);
	swisstalon->SetClosedLoopOutputDirection(false);
	swisstalon->SetInverted(false);
	SetMode(pos);
};

Swiss::mode_t Swiss::GetMode(){
	return static_cast<mode_t>(swisstalon->GetControlMode());
}
void Swiss::SetMode(mode_t m){
	if(GetMode() == m){
		return;
	}
	else if(m == pos){
		swisstalon->SetControlMode(CANTalon::ControlMode::kPosition);
		swisstalon->SelectProfileSlot(0);
		swisstalon->Set(swisstalon->Get());
		return;
	}
	else if(m == velocity){
		swisstalon->SetControlMode(CANTalon::ControlMode::kSpeed);
		swisstalon->SelectProfileSlot(1);
		SetVelocity(0.0, false);
		return;
	}
	else{
		swisstalon->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		SetVelocity(0.0, false);
		return;
	}
}
state_t Swiss::GetState(){
	return position;
}

void Swiss::SetVelocity(double v, bool changeMode){
	if(changeMode)
		SetMode(velocity);

	if(GetMode() == mode_t::velocity)
		swisstalon->Set(maxVelocity * v);
	else if(GetMode() == mode_t::vbus)
		swisstalon->Set(v);
}
void Swiss::SetVoltage(double v){
	SetMode(vbus);
	swisstalon->Set(v);
}

void Swiss::SetState(state_t s){
	SetMode(pos);
	position = s;
	swisstalon->Set(states[position]);
}
