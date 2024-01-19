#include "studio_bank_loader.h"

void StudioBankLoader::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("handle_game_event", "game_event"), &StudioBankLoader::handle_game_event);
	ClassDB::bind_method(D_METHOD("load"), &StudioBankLoader::load);
	ClassDB::bind_method(D_METHOD("unload"), &StudioBankLoader::unload);
	ClassDB::bind_method(D_METHOD("set_load_on", "load_on"), &StudioBankLoader::set_load_on);
	ClassDB::bind_method(D_METHOD("get_load_on"), &StudioBankLoader::get_load_on);
	ClassDB::bind_method(D_METHOD("set_unload_on", "unload_on"), &StudioBankLoader::set_unload_on);
	ClassDB::bind_method(D_METHOD("get_unload_on"), &StudioBankLoader::get_unload_on);
	ClassDB::bind_method(D_METHOD("set_num_banks", "num_banks"), &StudioBankLoader::set_num_banks);
	ClassDB::bind_method(D_METHOD("get_num_banks"), &StudioBankLoader::get_num_banks);
	ClassDB::bind_method(D_METHOD("set_preload_sample_data", "preload_sample_data"),
			&StudioBankLoader::set_preload_sample_data);
	ClassDB::bind_method(D_METHOD("get_preload_sample_data"), &StudioBankLoader::get_preload_sample_data);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "load_on", PROPERTY_HINT_ENUM, "None,Enter Tree,Ready,Exit Tree"),
			"set_load_on", "get_load_on");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "unload_on", PROPERTY_HINT_ENUM, "None,Enter Tree,Ready,Exit Tree"),
			"set_unload_on", "get_unload_on");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "preload_sample_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT),
			"set_preload_sample_data", "get_preload_sample_data");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_banks", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT),
			"set_num_banks", "get_num_banks");
}

void StudioBankLoader::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			do_enter_tree();
		} break;
		case NOTIFICATION_EXIT_TREE: {
			do_exit_tree();
		} break;
		case NOTIFICATION_READY: {
			do_ready();
		} break;
		// case NOTIFICATION_PROCESS: {
		// 	//
		// } break;
		default:
			break;
	}
}

bool StudioBankLoader::_set(const StringName& p_name, const Variant& p_value)
{
	auto name = String(p_name);

	if (name.begins_with("bank_"))
	{
		if (num_banks == 0)
		{
			return false;
		}
	}

	if (p_value.get_type() == Variant::NIL)
	{
		if (name.begins_with("bank_"))
		{
			int64_t bank_index = name.get_slice("_", 1).to_int();

			set_bank_ref(bank_index, Variant());
			notify_property_list_changed();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (name.begins_with("bank_"))
		{
			int64_t bank_index = name.get_slice("_", 1).to_int();
			set_bank_ref(bank_index, p_value);
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool StudioBankLoader::_get(const StringName& p_name, Variant& r_ret) const
{
	String name = String(p_name);

	if (name.begins_with("bank_"))
	{
		if (num_banks == 0)
		{
			return false;
		}

		int64_t bank_index = name.get_slice("_", 1).to_int();

		r_ret = banks[bank_index];
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void StudioBankLoader::_get_property_list(List<PropertyInfo>* p_list) const
{
	if (num_banks == 0)
	{
		return;
	}

	for (int i = 0; i < num_banks; i++)
	{
		p_list->push_back(PropertyInfo(Variant::OBJECT, String("bank_" + String::num_int64(i)).utf8().get_data(),
				PROPERTY_HINT_RESOURCE_TYPE, "BankAsset",
				PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_SCRIPT_VARIABLE));
	}
}

void StudioBankLoader::set_bank_ref(int index, const Variant& value)
{
	if (index < 0 || index >= num_banks)
	{
		return;
	}

	if (value.get_type() == Variant::NIL)
	{
		banks[index] = Variant();
	}
	else
	{
		banks[index] = value;
	}
}

void StudioBankLoader::do_enter_tree()
{
	handle_game_event(GAMEEVENT_ENTER_TREE);
}

void StudioBankLoader::do_ready()
{
	handle_game_event(GAMEEVENT_READY);
}

void StudioBankLoader::do_exit_tree()
{
	handle_game_event(GAMEEVENT_EXIT_TREE);
}

void StudioBankLoader::handle_game_event(FmodGameEvent game_event)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	if (load_on == game_event)
	{
		load();
	}
	if (unload_on == game_event)
	{
		unload();
	}
}

void StudioBankLoader::load()
{
	FMODStudioModule* fmod_module = FMODStudioModule::get_singleton();

	if (fmod_module)
	{
		for (int64_t i = 0; i < banks.size(); i++)
		{
			Ref<BankAsset> bank_ref = banks[i];
			if (bank_ref.is_valid())
			{
				fmod_module->get_studio_system_ref()
						->load_bank_file(bank_ref->get_file_path(),
								FMOD_STUDIO_LOAD_BANK_NORMAL, preload_sample_data);
			}
		}
	}
}

void StudioBankLoader::unload()
{
	FMODStudioModule* fmod_module = FMODStudioModule::get_singleton();

	if (fmod_module)
	{
		for (int64_t i = 0; i < banks.size(); i++)
		{
			Ref<BankAsset> bank_ref = banks[i];
			Ref<StudioApi::Bank> bank =
					fmod_module->get_studio_system_ref()
							->get_bank(bank_ref->get_fmod_path());

			if (bank_ref.is_valid())
			{
				if (bank.is_valid())
				{
					bank->unload();
				}
			}
		}
	}
}

void StudioBankLoader::set_load_on(FmodGameEvent _load_on)
{
	this->load_on = _load_on;
}

FmodGameEvent StudioBankLoader::get_load_on() const
{
	return load_on;
}

void StudioBankLoader::set_unload_on(FmodGameEvent _unload_on)
{
	this->unload_on = _unload_on;
}

FmodGameEvent StudioBankLoader::get_unload_on() const
{
	return unload_on;
}

void StudioBankLoader::set_num_banks(int _num_banks)
{
	this->num_banks = _num_banks;

	banks.resize(num_banks);

	if (is_inside_tree())
	{
		Ref<SceneTreeTimer> timer = get_tree()->create_timer(0.001);
		timer->connect("timeout", Callable(this, "notify_property_list_changed"));
	}
}

int StudioBankLoader::get_num_banks() const
{
	return banks.size();
}

void StudioBankLoader::set_preload_sample_data(bool _preload_sample_data)
{
	this->preload_sample_data = _preload_sample_data;
}

bool StudioBankLoader::get_preload_sample_data() const
{
	return preload_sample_data;
}
