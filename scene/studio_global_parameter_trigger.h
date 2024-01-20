#ifndef STUDIO_GLOBAL_PARAMETER_TRIGGER_H
#define STUDIO_GLOBAL_PARAMETER_TRIGGER_H

#include "../fmod_assets.h"
#include "../fmod_studio_module.h"
#include "../utils/runtime_utils.h"

class StudioGlobalParameterTrigger : public Node
{
	GDCLASS(StudioGlobalParameterTrigger, Node);

protected:
	static void _bind_methods();

	void _notification(int p_what);

	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name, Variant& r_ret) const;
	void _get_property_list(List<PropertyInfo>* p_list) const;
	bool _property_can_revert(const StringName& p_name) const;
	bool _property_get_revert(const StringName& p_name, Variant& r_property) const;

private:
	FmodGameEvent trigger_on = GAMEEVENT_NONE;
	Dictionary overridden_parameter;
	Ref<ParameterAsset> parameter;
	float parameter_value = 0.0f;

public:
	void do_enter_tree();
	void do_ready();
	void do_exit_tree();

	void handle_game_event(FmodGameEvent game_event);
	void trigger();

	void set_trigger_on(FmodGameEvent trigger_on);
	FmodGameEvent get_trigger_on() const;

	void set_parameter(const Ref<ParameterAsset>& parameter);
	Ref<ParameterAsset> get_parameter() const;

	Dictionary get_overridden_parameter() const;
};

#endif // STUDIO_GLOBAL_PARAMETER_TRIGGER_H