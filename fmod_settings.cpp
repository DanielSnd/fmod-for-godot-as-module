//
// Created by Daniel on 2024-01-17.
//

#include "fmod_settings.h"

#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "utils/fmod_utils.h"

FMODSettings* FMODSettings::singleton = nullptr;

void FMODSettings::_bind_methods()
{
}

FMODSettings::FMODSettings()
{
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;
}

FMODSettings::~FMODSettings()
{
	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
}

FMODSettings* FMODSettings::get_singleton()
{
	return singleton;
}

void FMODSettings::add_fmod_enabled_setting() {
	const String& fmod_enabled_settings_path = get_platform_setting_path(PlatformSettingsPath::FMOD_SETTINGS_ENABLED_PATH);
	if (!ProjectSettings::get_singleton()->has_setting(fmod_enabled_settings_path)) {
		ProjectSettings::get_singleton()->set_setting(fmod_enabled_settings_path,false);
	}
	ProjectSettings::get_singleton()->set_custom_property_info(PropertyInfo(Variant::Type::BOOL, fmod_enabled_settings_path, PROPERTY_HINT_NONE, "",PROPERTY_USAGE_DEFAULT));
	ProjectSettings::get_singleton()->set_initial_value(fmod_enabled_settings_path, false);
	ProjectSettings::get_singleton()->set_restart_if_changed(fmod_enabled_settings_path, true);
}

void FMODSettings::initialize()
{
	if (already_initialized) return;
	already_initialized = true;
	if (!is_fmod_enabled()) {
		//Add only the FMOD Enabled setting.
		add_setting(get_platform_setting_path(PlatformSettingsPath::FMOD_SETTINGS_ENABLED_PATH), false, Variant::Type::BOOL);
		ProjectSettings::get_singleton()->set_restart_if_changed(get_platform_setting_path(PlatformSettingsPath::FMOD_SETTINGS_ENABLED_PATH), true);
		if (Engine::get_singleton()->is_editor_hint() && OS::get_singleton()->has_feature("editor")) {
			Error error = ProjectSettings::get_singleton()->save();
		}
		return;
	}
	//print_line("[FMOD] Initializing Fmod Settings");
	add_fmod_settings();

	if (Engine::get_singleton()->is_editor_hint())
	{
		Error error = ProjectSettings::get_singleton()->save();
		if (error)
		{
			ERR_PRINT(vformat("Encountered error %s when saving FMOD Project Settings", error));
		}
		else
		{
			//print_line("[FMOD] Saved Project Settings");
		}
	}
}

void FMODSettings::add_fmod_settings()
{
	const String settings_path = get_platform_setting_path(PlatformSettingsPath::FMOD_SETTINGS_PATH);
	add_setting(settings_path + String("fmod_enabled"), false, Variant::Type::BOOL,PROPERTY_HINT_NONE,"",PROPERTY_USAGE_DEFAULT,true);
	add_setting(settings_path + String("banks_path"), "res://FMOD/banks/Desktop", Variant::Type::STRING, PROPERTY_HINT_DIR,"",PROPERTY_USAGE_DEFAULT,true);
	add_setting(settings_path + String("fmod_output_type"), 0, Variant::Type::INT, PROPERTY_HINT_ENUM,
			"AUTODETECT, UNKNOWN, NOSOUND, WAVWRITER, NOSOUND_NRT, WAVWRITER_NRT, WASAPI, ASIO, PULSEAUDIO, ALSA, "
			"COREAUDIO, AUDIOTRACK, OPENSL, AUDIOOUT, AUDIO3D, WEBAUDIO, NNAUDIO, WINSONIC, AAUDIO");
	add_setting(settings_path + String("fmod_debug_flags"), 0, Variant::Type::INT, PROPERTY_HINT_FLAGS,
			"Error,Warning,Log");
	add_setting(settings_path + String("fmod_debug_mode"), 1, Variant::Type::INT, PROPERTY_HINT_ENUM,
			"TTY,File,Godot Output");
	add_setting(settings_path + String("banks_to_load_at_startup"), TypedArray<String>(), Variant::Type::ARRAY, PROPERTY_HINT_ARRAY_TYPE,
			vformat("%s/%s:",Variant::Type::STRING, PROPERTY_HINT_FILE));
	add_setting(settings_path + String("banks_preload_samples"), false, Variant::Type::BOOL);
	add_setting(settings_path + String("banks_flags"), 0, Variant::Type::INT, PROPERTY_HINT_FLAGS,
			"Non Blocking,Decompress Samples,Unencrypted");
	add_setting(settings_path + String("sample_rate"), 48000, Variant::Type::INT);
	add_setting(settings_path + String("speaker_mode"), 3, Variant::Type::INT, PROPERTY_HINT_ENUM,
			"Default,Raw,Mono,Stereo,Quad,Surround,5.1,7.1,7.1.4");
	add_setting(settings_path + String("debug_performance"), false, Variant::Type::BOOL,PROPERTY_HINT_NONE,"",PROPERTY_USAGE_DEFAULT,true);
	add_setting(settings_path + String("dsp_buffer_length"), 512, Variant::Type::INT);
	add_setting(settings_path + String("dsp_buffer_count"), 4, Variant::Type::INT);
	add_setting(settings_path + String("real_channel_count"), 32, Variant::Type::INT);
	add_setting(settings_path + String("virtual_channel_count"), 128, Variant::Type::INT);
	add_setting(settings_path + String("enable_live_update"), true, Variant::Type::BOOL);
	add_setting(settings_path + String("live_update_port"), 9264, Variant::Type::INT);
	add_setting(settings_path + String("enable_memory_tracking"), false, Variant::Type::BOOL);
	add_setting(settings_path + String("encryption_key"), "", Variant::Type::STRING);
	add_setting(settings_path + String("distance_scale_2d"), 1.0f, Variant::Type::FLOAT);
	add_setting(settings_path + String("init_with_3d_righthanded"), true, Variant::Type::BOOL);
}

void FMODSettings::add_setting(const String& p_name, const Variant& p_default_value, Variant::Type p_type,
PropertyHint p_hint, const String& p_hint_string, int p_usage,bool restart_if_changed) {
	if (!ProjectSettings::get_singleton()->has_setting(p_name)) {
		ProjectSettings::get_singleton()->set_setting(p_name, p_default_value);
	}
	ProjectSettings::get_singleton()->set_custom_property_info(PropertyInfo(p_type, p_name, p_hint, p_hint_string,p_usage));
	ProjectSettings::get_singleton()->set_initial_value(p_name, p_default_value);
	ProjectSettings::get_singleton()->set_restart_if_changed(p_name, restart_if_changed);
}
