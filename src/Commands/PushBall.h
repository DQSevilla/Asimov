/*
 * PushBall.h
 *
 *  Created on: Feb 6, 2016
 *      Author: David
 */

#ifndef SRC_COMMANDS_PUSHBALL_H_
#define SRC_COMMANDS_PUSHBALL_H_
#include "Subsystems/Intake.h"

/**
 * Commands namespace with declaration
 * of PushBall command group, and nested
 * Push and Stopper command classes.
 */
namespace commands
{

using Intake = subsystems::Intake;


class PushBall: public CommandGroup
{
using State_t = Intake::State_t;
// Constructor & destructors:
public:
	PushBall(Intake* intake);
	virtual ~PushBall() = default;

// Main functions:
public:
	/**
	 * TODO : Documentation
	 * So far does nothing
	 */
	void Initialize() override;

protected:

// Nested command classes:
private:
	/**
	 * Push command controls the Outake Function of the Intake Subsystem,
	 * responsable for moving the boulder from its storage.
	 */
	class Push: public Command
	{
	// Constructor & destructor:
	public:
		Push(Intake *intake, double time = 0.5);
		virtual ~Push() = default;

	// Main functions:
	public:
		/**
		 * If the current state of Intake is not HOLDING, an error message
		 * is printed. Otherwise the state is changed to PUSHING and the
		 * Outake function of the Intake subsystem is called.
		 */
		void Initialize() override;

		/**
		 * Returns true if the command should no longet execute, false if
		 * otherwise. If the mechanical switch (detector_) on the Intake
		 * system is not pressed on and the position of the roller is at or
		 * equal to a target position, or if the command times out.
		 */
		bool IsFinished() override;

		/**
		 * Not implemented.
		 */
		void Execute() override {};

		/**
		 * Not implemented.
		 */
		void End() override;

		/**
		 * Not implemented. (Push is not interruptible)
		 */
		void Interrupted() override {};

		/**
		 * Sets the target position to target_position
		 */
		void SetTargetPosition(double target_position);

		/**
		 * @return target_position_ the target position of roller
		 */
		double GetTargetPosition() const;


		double GetTimeout() const;

	private:
		Intake *intake_;
		double target_position_;
		double timeout_;
	};

	/**
	 * Stopper is responsable for halting the movement of the rollers
	 */
	class Stopper: public Command
	{
	// Constructor & destructor:
	public:
		Stopper(Intake *intake);
		virtual ~Stopper() = default;

	// Main functions:
	public:
		/**
		 * Not implemented.
		 */
		void Initialize() override {};

		/**
		 * Function only returns true because the purpose is to stop the
		 * rollers.
		 */
		bool IsFinished() override;
		/**
		 * Not implemented.
		 */
		void Execute() override {};

		/**
		 * Calls the Stop function of Intake to stop moving the rollers,
		 * and sets the state to OFF.
		 */
		void End() override;

		/**
		 * Not implemented (Stopper is not interruptible).
		 */
		void Interrupted() override {};

	private:
		Intake *intake_;
	};

private:
	Intake *intake_;
	Push *push_;
	Stopper *stop_;
//	WaitCommand *wait_;
};

}// end namespace commands

#endif /* SRC_COMMANDS_PUSHBALL_H_ */
