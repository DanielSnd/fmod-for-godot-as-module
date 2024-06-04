#ifndef STUDIO_EVENT_EMITTER_H
#define STUDIO_EVENT_EMITTER_H

#include "../utils/runtime_utils.h"
#include "../fmod_assets.h"
#include "../fmod_studio_editor_module.h"

class RuntimeUtils;

template <typename T>
struct StudioEventEmitterImpl
{
	T* node;
	FmodGameEvent play_event = GAMEEVENT_NONE;
	FmodGameEvent stop_event = GAMEEVENT_NONE;
	Ref<StudioApi::EventDescription> event_description;
	Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = create_ref<FmodTypes::FMOD_3D_ATTRIBUTES>();
	Ref<EventAsset> event;
	bool has_triggered{};
	bool is_active{};
	bool preload_samples{};
	bool allow_fadeout = true;
	bool trigger_once{};
	Object* rigidbody = nullptr;
	Dictionary overridden_parameters;
	Ref<StudioApi::EventInstance> event_instance;

	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name, Variant& r_ret) const;
	void _get_property_list(List<PropertyInfo>* p_list) const;
	bool _property_can_revert(const StringName& p_name) const;
	bool _property_get_revert(const StringName& p_name, Variant& r_property) const;

	void play_instance();
	void stop_instance();
	bool is_playing();

	void register_active_emitter(T* emitter);
	void deregister_active_emitter(T* emitter);
	void update_playing_status(bool force = false);

	void _enter_tree();
	void _ready();
	void _exit_tree();
	void _process(double p_delta);

	void handle_game_event(FmodGameEvent game_event);

	void play();
	void stop();
	void lookup();
	float get_max_distance();
};

class StudioEventEmitter2D : public Node2D
{
	GDCLASS(StudioEventEmitter2D, Node2D);

protected:
	static void _bind_methods();
	void _notification(int p_what);
	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name, Variant& r_ret) const;
	void _get_property_list(List<PropertyInfo>* p_list) const;
	bool _property_can_revert(const StringName& p_name) const;
	bool _property_get_revert(const StringName& p_name, Variant& r_property) const;

public:
	StudioEventEmitterImpl<StudioEventEmitter2D> implementation;

	bool has_done_enter_tree = false;
	void do_enter_tree();
	void do_ready();
	void do_exit_tree();
	void do_process(double p_delta);

	void handle_game_event(FmodGameEvent game_event);

	void play();
	void stop();
	void lookup();
	float get_max_distance();

	void set_play_event(FmodGameEvent play_event);
	FmodGameEvent get_play_event() const;

	void set_stop_event(FmodGameEvent stop_event);
	FmodGameEvent get_stop_event() const;

	void set_event(const Ref<EventAsset>& event);
	Ref<EventAsset> get_event() const;

	void set_preload_samples(bool preload_samples);
	bool get_preload_samples() const;

	void set_allow_fadeout(bool allow_fadeout);
	bool get_allow_fadeout() const;

	void set_trigger_once(bool trigger_once);
	bool get_trigger_once() const;

	void set_rigidbody(Object* rigidbody);
	Object* get_rigidbody() const;

	void set_overridden_parameters(const Dictionary& overridden_parameters);
	Dictionary get_overridden_parameters() const;
};

class StudioEventEmitter3D : public Node3D
{
	GDCLASS(StudioEventEmitter3D, Node3D);

protected:
	static void _bind_methods();
	void _notification(int p_what);
	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name, Variant& r_ret) const;
	void _get_property_list(List<PropertyInfo>* p_list) const;
	bool _property_can_revert(const StringName& p_name) const;
	bool _property_get_revert(const StringName& p_name, Variant& r_property) const;

public:
	StudioEventEmitterImpl<StudioEventEmitter3D> implementation;

	static void update_active_emitters();

	virtual void do_enter_tree();
	virtual void do_ready();
	virtual void do_exit_tree();
	virtual void do_process(double p_delta);

	void handle_game_event(FmodGameEvent game_event);
	bool has_done_enter_tree = false;
	void play();
	void stop();
	void lookup();
	float get_max_distance();

	void set_play_event(FmodGameEvent play_event);
	FmodGameEvent get_play_event() const;

	void set_stop_event(FmodGameEvent stop_event);
	FmodGameEvent get_stop_event() const;

	void set_event(const Ref<EventAsset>& event);
	Ref<EventAsset> get_event() const;

	void set_preload_samples(bool preload_samples);
	bool get_preload_samples() const;

	void set_allow_fadeout(bool allow_fadeout);
	bool get_allow_fadeout() const;

	void set_trigger_once(bool trigger_once);
	bool get_trigger_once() const;

	void set_rigidbody(Object* rigidbody);
	Object* get_rigidbody() const;

	void set_overridden_parameters(const Dictionary& overridden_parameters);
	Dictionary get_overridden_parameters() const;
};

#endif // STUDIO_EVENT_EMITTER_H