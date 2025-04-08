/**
 * This class implements timer that can be
 * used to compute time between two function calls.
 */

#pragma once

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class CTimer
{
public:
	CTimer(void);
	virtual ~CTimer(void);

	/**
	 * Create
	 * initialise the timer
	 */
	void Create(void);

	/**
	 * Release
	 */
	void Release(void);

	/**
	 * BeginTimer
	 * get the start value of the timer
	 */
	void BeginTimer(void);

	/**
	 * EndTimer
	 * compute time elapsed from BeginTimer call
	 */
	void EndTimer(void);

	/**
	 * GetElapsedSeconds
	 * @return seconds elapsed in between last calls to
	 * BeginTimer and EndTimer functions
	 */
	inline float GetElapsedSeconds() const { return m_fElapsedSeconds; }

private:
	// timer values
	INT64			m_ddwStartTicks;
	INT64			m_ddwTickFrequency;

	// seconds elapsed in between BeginTimer and
	// EndTimer function calls
	float			m_fElapsedSeconds;
};