//
// Created by Daniel on 2024-01-17.
//

#ifndef FMOD_SETTINGS_H
#define FMOD_SETTINGS_H
#include "core/object/ref_counted.h"

class ProjectCache;

class FMODSettings : public RefCounted
{
    GDCLASS(FMODSettings, RefCounted);

protected:
    static FMODSettings* singleton;
    static void _bind_methods();

public:
    bool already_initialized = false;
    FMODSettings();
    ~FMODSettings() override;
    static FMODSettings* get_singleton();

    static void add_fmod_enabled_setting();

    void initialize();

private:
    void add_fmod_settings();
    void add_setting(const String& name, const Variant& default_value, Variant::Type type,
            PropertyHint hint = PROPERTY_HINT_NONE, const String& hint_string = "",
            int usage = PROPERTY_USAGE_DEFAULT, bool restart_if_changed = false);
};

#endif //FMOD_SETTINGS_H
