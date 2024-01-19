#ifndef STUDIO_PARAMETER_TRIGGER_H
#define STUDIO_PARAMETER_TRIGGER_H

#include "../fmod_studio_module.h"
#include "studio_event_emitter.h"
#include "scene/main/node.h"
#include "../fmod_studio_editor_module.h"

class EventAsset;

class StudioParameterTrigger : public Node
{
	GDCLASS(StudioParameterTrigger, Node);

protected:
	static void _bind_methods();
	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name, Variant& r_ret) const;
	void _get_property_list(List<PropertyInfo>* p_list) const;
	bool _property_can_revert(const StringName& p_name) const;
	bool _property_get_revert(const StringName& p_name, Variant& r_property) const;
	void _notification(int p_what);

private:
	NodePath studio_event_emitter;
	Ref<EventAsset> event;
	bool event_changed = false;
	mutable Dictionary overridden_parameters;
	void reset();

public:
	FmodGameEvent trigger_on = GAMEEVENT_NONE;
	virtual void do_enter_tree();
	virtual void do_ready();
	virtual void do_exit_tree();

	void handle_game_event(FmodGameEvent game_event);
	void trigger();

	void set_studio_event_emitter(const Variant& path);
	NodePath get_studio_event_emitter() const;

	void set_trigger_on(FmodGameEvent trigger_on);
	FmodGameEvent get_trigger_on() const;

	void set_event(const Ref<EventAsset>& event_asset);
	Ref<EventAsset> get_event();

	void on_event_changed(Object* value);
};

#endif // STUDIO_PARAMETER_TRIGGER_H