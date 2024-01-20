#ifndef FMOD_DEBUG_MONITOR_H
#define FMOD_DEBUG_MONITOR_H

#include "../fmod_studio_module.h"
class FMODDebugMonitor : public Node
{
	GDCLASS(FMODDebugMonitor, Node);

protected:
	static void _bind_methods();

	void _notification(int p_what);

private:
	uint64_t last_debug_update = 0;
	float dsp_cpu_info = 0.0f;
	float studio_cpu_info = 0.0f;
	int current_alloc_info = 0;
	int max_alloc_info = 0;
	int channels_info = 0;
	int real_channels_info = 0;
	bool leaving_tree = false;
	FMOD::Studio::System* studio_system = nullptr;
	FMOD::System* core_system = nullptr;

public:
	void do_enter_tree();
	void do_exit_tree();
	void do_process(double delta);

	void process_debug_info();
	float get_cpu_dsp_usage();
	float get_cpu_studio_update();
	int get_current_memory_alloc();
	int get_max_memory_alloc();
	int get_channels();
	int get_real_channels();
};

#endif // FMOD_DEBUG_MONITOR_H