#ifndef STUDIO_BANK_LOADER_H
#define STUDIO_BANK_LOADER_H

#include "../fmod_assets.h"
#include "../fmod_studio_module.h"
#include "../utils/runtime_utils.h"

class StudioBankLoader : public Node
{
	GDCLASS(StudioBankLoader, Node);

protected:
	static void _bind_methods();
	void _notification(int p_what);
	bool _set(const StringName& p_name, const Variant& p_value);
	bool _get(const StringName& p_name, Variant& r_ret) const;
	void _get_property_list(List<PropertyInfo>* p_list) const;

private:
	FmodGameEvent load_on = GAMEEVENT_NONE;
	FmodGameEvent unload_on = GAMEEVENT_NONE;
	int num_banks = 0;
	Array banks;
	bool preload_sample_data = false;

	void set_bank_ref(int index, const Variant& value);

public:
	void do_enter_tree();
	void do_ready();
	void do_exit_tree();

	void handle_game_event(FmodGameEvent game_event);

	void load();
	void unload();

	void set_load_on(FmodGameEvent load_on);
	FmodGameEvent get_load_on() const;

	void set_unload_on(FmodGameEvent unload_on);
	FmodGameEvent get_unload_on() const;

	void set_num_banks(int num_banks);
	int get_num_banks() const;

	void set_preload_sample_data(bool preload_sample_data);
	bool get_preload_sample_data() const;
};

#endif // STUDIO_BANK_LOADER_H