#include "debug_monitors.h"

#include "core/os/time.h"
#include "main/performance.h"

using namespace godot;

void FMODDebugMonitor::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_cpu_dsp_usage"), &FMODDebugMonitor::get_cpu_dsp_usage);
	ClassDB::bind_method(D_METHOD("get_cpu_studio_update"), &FMODDebugMonitor::get_cpu_studio_update);
	ClassDB::bind_method(D_METHOD("get_current_memory_alloc"), &FMODDebugMonitor::get_current_memory_alloc);
	ClassDB::bind_method(D_METHOD("get_max_memory_alloc"), &FMODDebugMonitor::get_max_memory_alloc);
	ClassDB::bind_method(D_METHOD("get_channels"), &FMODDebugMonitor::get_channels);
	ClassDB::bind_method(D_METHOD("get_real_channels"), &FMODDebugMonitor::get_real_channels);
}

void FMODDebugMonitor::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			do_enter_tree();
		} break;
		case NOTIFICATION_EXIT_TREE: {
			set_process(false);
			do_exit_tree();
		} break;
		case NOTIFICATION_READY: {
			set_process(true);
		} break;
		case NOTIFICATION_PROCESS: {
			do_process(get_process_delta_time());
		} break;
		case NOTIFICATION_WM_CLOSE_REQUEST: {
			set_process(false);
			do_exit_tree();
		}
		default:
			break;
	}
}

void FMODDebugMonitor::do_enter_tree()
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	Performance* performance = Performance::get_singleton();

	if (performance == nullptr)
	{
		return;
	}

	studio_system = FMODStudioModule::get_singleton()->get_studio_system();

	if (studio_system == nullptr)
	{
		return;
	}

	core_system = FMODStudioModule::get_singleton()->get_core_system();

	if (core_system == nullptr)
	{
		return;
	}

	if (!performance->has_custom_monitor("FMOD/DSP CPU Usage (%)"))
	{
		performance->add_custom_monitor("FMOD/DSP CPU Usage (%)", callable_mp(this, &FMODDebugMonitor::get_cpu_dsp_usage),Vector<Variant>());
	}
	if (!performance->has_custom_monitor("FMOD/Studio CPU Update (%)"))
	{
		performance->add_custom_monitor("FMOD/Studio CPU Update (%)",
			callable_mp(this, &FMODDebugMonitor::get_cpu_studio_update),Vector<Variant>());
	}
	if (!performance->has_custom_monitor("FMOD/Memory Allocation (MB)"))
	{
		performance->add_custom_monitor("FMOD/Memory Allocation (MB)",
				callable_mp(this, &FMODDebugMonitor::get_current_memory_alloc),Vector<Variant>());
	}
	if (!performance->has_custom_monitor("FMOD/Max Memory Allocation (MB)"))
	{
		performance->add_custom_monitor("FMOD/Max Memory Allocation (MB)",
				callable_mp(this, &FMODDebugMonitor::get_max_memory_alloc),Vector<Variant>());
	}
	if (!performance->has_custom_monitor("FMOD/Channels"))
	{
		performance->add_custom_monitor("FMOD/Channels", callable_mp(this, &FMODDebugMonitor::get_channels),Vector<Variant>());
	}
	if (!performance->has_custom_monitor("FMOD/Real Channels"))
	{
		performance->add_custom_monitor("FMOD/Real Channels", callable_mp(this, &FMODDebugMonitor::get_real_channels),Vector<Variant>());
	}
}

void FMODDebugMonitor::do_exit_tree()
{
	leaving_tree=true;
	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	if (!core_system)
	{
		return;
	}
}

void FMODDebugMonitor::do_process(double delta)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	if(leaving_tree) {
		return;
	}
	if (last_debug_update + 250 < Time::get_singleton()->get_ticks_msec())
	{
		process_debug_info();

		last_debug_update = Time::get_singleton()->get_ticks_msec();
	}
}

void FMODDebugMonitor::process_debug_info()
{
	if (!core_system || !studio_system)
	{
		return;
	}

	FMOD_STUDIO_CPU_USAGE studioUsage{};
	FMOD_CPU_USAGE coreUsage{};
	ERROR_CHECK(studio_system->getCPUUsage(&studioUsage, &coreUsage));

	int currentAlloc{}, maxAlloc{};
	ERROR_CHECK(FMOD::Memory_GetStats(&currentAlloc, &maxAlloc));
	currentAlloc = currentAlloc >> 20;
	maxAlloc = maxAlloc >> 20;

	int channels{}, real_channels{};
	ERROR_CHECK(core_system->getChannelsPlaying(&channels, &real_channels));

	dsp_cpu_info = coreUsage.dsp;
	studio_cpu_info = studioUsage.update;
	current_alloc_info = currentAlloc;
	max_alloc_info = maxAlloc;
	channels_info = channels;
	real_channels_info = real_channels;
}

float FMODDebugMonitor::get_cpu_dsp_usage()
{
	return dsp_cpu_info;
}

float FMODDebugMonitor::get_cpu_studio_update()
{
	return studio_cpu_info;
}

int FMODDebugMonitor::get_current_memory_alloc()
{
	return current_alloc_info;
}

int FMODDebugMonitor::get_max_memory_alloc()
{
	return max_alloc_info;
}

int FMODDebugMonitor::get_channels()
{
	return channels_info;
}

int FMODDebugMonitor::get_real_channels()
{
	return real_channels_info;
}