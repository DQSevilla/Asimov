#include "Shoot.h"

/**
 * Commands namespace with implementation
 * of Shoot command.
 */
namespace commands
{

//Constructor:
Shoot::Shoot(Intake* intake, Shooter* shooter, double shoot_time)
{
	intake_ = intake;
	shooter_ = shooter;
	shoot_time_ = shoot_time;
	timer_ = new Timer;
}

void Shoot::Initialize()
{
	if (shooter_->GetState() == State_t::SPUNUP)
	{
		if (timer_->Get() == 0.0)
			timer_->Start();
		shooter_->SetState(Shooter::State_t::SHOOTING);
		intake_->SetState(Intake::State_t::SHOOTING);
		intake_->ShootBall();
	}
	else
	{
		std::cout << "ERROR: Invalid starting state (should be \"SPUNUP\")";
	}
}

void Shoot::End()
{
	shooter_->SetState(Shooter::State_t::SPUNUP);
	intake_->SetState(Intake::State_t::OFF);
	intake_->Stop();
}

bool Shoot::IsFinished()
{
	return (timer_->Get() >= shoot_time_);
}

void Shoot::Interrupted()
{
	End();
}

void Shoot::SetShootTime(double shoot_time)
{
	shoot_time_ = shoot_time;
}

double Shoot::GetShootTime() const
{
	return shoot_time_;
}

} // end namespace commands
