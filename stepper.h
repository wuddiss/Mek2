/*
 * stepper.h
 *
 *  Created on: Feb 8, 2024
 *      Author: vidar
 */
#ifndef STEPPER_H_
#define STEPPER_H_

void initStepper();

void steps_wd_fw(int speed, int steps);
void steps_wd_bw(int speed, int steps);
void step_wd_fw(int speed);
void step_wd_bw(int speed);

int steps_fsd_fw(int speed, int steps, int next_step);
void steps_fsd_bw(int speed, int steps);
void step_fsd_fw(int speed);
void step_fsd_bw(int speed);

void step_hsd_fw(int speed);
void step_hsd_bw(int speed);

void wave_drive(int step);
void full_step_drive(int step);
void half_step_drive(int step);

#endif

