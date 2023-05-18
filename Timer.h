#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	int GetTick();

	bool is_started();
	bool is_paused();

private:
	int start_tick_;
	int pause_tick_;

	bool is_paused_;
	bool is_started_;
};

#endif // !TIMER_H
