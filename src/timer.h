/*
 * timer.h
 *
 *  Created on: 19 Dec 2018
 *      Author: davca
 */

#ifndef ENGINE_CORE_TIMER_H_
#define ENGINE_CORE_TIMER_H_

#include <chrono>

class Timer {
public:
	Timer() {
		m_applicationStart = std::chrono::system_clock::now();
		m_lastDtTime = m_applicationStart;
	}
	// this function returns the amount of milis between the last and current call to this function
	double GetDt() {
		auto currentDtTime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = m_lastDtTime - currentDtTime;
		m_lastDtTime = currentDtTime;
		return (double)-elapsed_time.count()*1000.0;
	}
private:
	std::chrono::time_point<std::chrono::system_clock> m_applicationStart;
	std::chrono::time_point<std::chrono::system_clock> m_lastDtTime;
};



#endif /* ENGINE_CORE_TIMER_H_ */
