//
// Created by Daniel on 2024-01-18.
//

#include "fmod_runtime.h"

#include "scene/scene_string_names.h"
#include "scene/studio_listener.h"
#include "scene/gui/control.h"

FMODRuntime* FMODRuntime::singleton = nullptr;
void FMODRuntime::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_debug_print_event_calls", "status"), &FMODRuntime::set_debug_print_event_calls);
    ClassDB::bind_method(D_METHOD("get_debug_print_event_calls"), &FMODRuntime::get_debug_print_event_calls);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "debug_print_event_calls"), "set_debug_print_event_calls", "get_debug_print_event_calls");

    ClassDB::bind_method(D_METHOD("set_has_initialized", "initialized"), &FMODRuntime::set_has_initialized);
    ClassDB::bind_method(D_METHOD("get_has_initialized"), &FMODRuntime::get_has_initialized);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_initialized"), "set_has_initialized", "get_has_initialized");
    
    ClassDB::bind_method(D_METHOD("set_current_snapshot", "event_asset"), &FMODRuntime::set_current_snapshot);
    ClassDB::bind_method(D_METHOD("get_current_snapshot"), &FMODRuntime::get_current_snapshot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "current_snapshot", PROPERTY_HINT_RESOURCE_TYPE, "EventAsset"), "set_current_snapshot", "get_current_snapshot");
    
    ClassDB::bind_method(D_METHOD("set_current_music", "event_asset"), &FMODRuntime::set_current_music);
    ClassDB::bind_method(D_METHOD("get_current_music"), &FMODRuntime::get_current_music);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "current_music", PROPERTY_HINT_RESOURCE_TYPE, "EventAsset"), "set_current_music", "get_current_music");

    ClassDB::bind_method(D_METHOD("set_guid_dictionary", "event_asset"), &FMODRuntime::set_guid_dictionary);
    ClassDB::bind_method(D_METHOD("get_guid_dictionary"), &FMODRuntime::get_guid_dictionary);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "guid_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "FMODGuidDictionary"), "set_guid_dictionary", "get_guid_dictionary");

    ClassDB::bind_method(D_METHOD("path_to_guid","fmod_path"), &FMODRuntime::path_to_guid);

    ClassDB::bind_method(D_METHOD("set_click_and_hover_assets","click_eventasset","hover_eventasset"), &FMODRuntime::set_click_and_hover_assets);
    ClassDB::bind_method(D_METHOD("setup_button_sfx_callback","button","callback"), &FMODRuntime::setup_button_sfx_callback);
    ClassDB::bind_method(D_METHOD("setup_button_sfx","button"), &FMODRuntime::setup_button_sfx);

    ClassDB::bind_method(D_METHOD("back_to_previous_music"), &FMODRuntime::back_to_previous_music);
    ClassDB::bind_method(D_METHOD("back_to_previous_snapshot"), &FMODRuntime::back_to_previous_snapshot);

    ClassDB::bind_method(D_METHOD("get_event_description","event_asset"), &FMODRuntime::get_event_description);
    ClassDB::bind_method(D_METHOD("get_event_description_path","event_path"), &FMODRuntime::get_event_description_path);
    ClassDB::bind_method(D_METHOD("get_event_description_id","event_guid"), &FMODRuntime::get_event_description_id);
    ClassDB::bind_method(D_METHOD("create_instance","event_asset"), &FMODRuntime::create_instance);
    ClassDB::bind_method(D_METHOD("create_instance_path","event_path"), &FMODRuntime::create_instance_path);
    ClassDB::bind_method(D_METHOD("create_instance_id","event_id"), &FMODRuntime::create_instance_id);

    ClassDB::bind_method(D_METHOD("play_one_shot_attached","event_asset","node"), &FMODRuntime::play_one_shot_attached);
    ClassDB::bind_method(D_METHOD("play_one_shot_attached_path","event_path","node"), &FMODRuntime::play_one_shot_attached_path);
    ClassDB::bind_method(D_METHOD("play_one_shot_attached_id","event_guid","node"), &FMODRuntime::play_one_shot_attached_id);
    ClassDB::bind_method(D_METHOD("play_one_shot","event_asset","position"), &FMODRuntime::play_one_shot,DEFVAL(Variant{}));
    ClassDB::bind_method(D_METHOD("play_one_shot_path","event_path","position"), &FMODRuntime::play_one_shot_path,DEFVAL(Variant{}));
    ClassDB::bind_method(D_METHOD("play_one_shot_id","event_guid","position"), &FMODRuntime::play_one_shot_id,DEFVAL(Variant{}));

    ClassDB::bind_method(D_METHOD("play_looped_attached","event_asset","node"), &FMODRuntime::play_looped_attached);
    ClassDB::bind_method(D_METHOD("play_looped_attached_id","event_guid","node"), &FMODRuntime::play_looped_attached_id);
    ClassDB::bind_method(D_METHOD("play_looped","event_asset","node","position"), &FMODRuntime::play_looped);
    ClassDB::bind_method(D_METHOD("play_looped_id","event_guid","node","position"), &FMODRuntime::play_looped_id);
    ClassDB::bind_method(D_METHOD("stop_looped_id","event_guid","node_instance_id"), &FMODRuntime::stop_looped_id);
    ClassDB::bind_method(D_METHOD("stop_looped","event_asset","node_instance_id"), &FMODRuntime::stop_looped);


    ClassDB::bind_method(D_METHOD("play_one_shot_volume","event_asset","volume","position"), &FMODRuntime::play_one_shot_volume,DEFVAL(Variant{}));
    ClassDB::bind_method(D_METHOD("play_one_shot_path_volume","event_path","volume","position"), &FMODRuntime::play_one_shot_path_volume,DEFVAL(Variant{}));
    ClassDB::bind_method(D_METHOD("play_one_shot_id_volume","event_guid","volume","position"), &FMODRuntime::play_one_shot_id_volume,DEFVAL(Variant{}));

    ClassDB::bind_method(D_METHOD("attach_instance_to_node","event_instance","node","physicsbody"), &FMODRuntime::attach_instance_to_node);
    ClassDB::bind_method(D_METHOD("detach_instance_from_node","event_instance"), &FMODRuntime::detach_instance_from_node);
    ClassDB::bind_method(D_METHOD("setup_in_tree"), &FMODRuntime::setup_in_tree);
    ClassDB::bind_method(D_METHOD("set_parameter_by_name", "name", "value", "ignore_seek_speed"),&FMODRuntime::set_parameter_by_name, DEFVAL(false));
    ADD_SIGNAL(MethodInfo("initialized"));
}

void FMODRuntime::_notification(int p_what) {
    if (p_what == 0 && !Engine::get_singleton()->is_editor_hint()) {
        call_deferred("setup_in_tree");
    }
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
        case NOTIFICATION_PROCESS: {
            if(has_initialized) {
                do_process();
            }
        } break;
        case NOTIFICATION_WM_CLOSE_REQUEST: {
            do_exit_tree();
        } break;
        default:
            break;
    }
}

void FMODRuntime::do_enter_tree() {
    if (!is_fmod_enabled()) {
        return;
    }
    print_line("[FMOD] Fmod Runtime started");
    if(FMODStudioModule::get_singleton()->init()) {
        studio_system = FMODStudioModule::get_singleton()->get_studio_system_ref();

        has_initialized = true;
        const String guid_dictionary_path = "res://FMOD/fmod_guid_dictionary.tres";
        if (!ResourceLoader::exists(guid_dictionary_path)) {
            guid_dictionary.instantiate();
        } else {
            guid_dictionary = ResourceLoader::load(guid_dictionary_path, "FMODGuidDictionary");
        }
        const String settings_path = get_platform_setting_path(PlatformSettingsPath::FMOD_SETTINGS_PATH);
        const bool enable_debug_performance =
                static_cast<bool>(get_platform_project_setting(settings_path + String("debug_performance")));
        if (!OS::get_singleton()->has_feature("editor") && enable_debug_performance) {
            debug_scene = memnew(FMODDebugMonitor);
            call_deferred("add_child",debug_scene);
        }
        if (!current_music.is_empty()) {
            music_instance = create_instance_id(current_music);
            music_instance->start();
        }
        if (!current_snapshot.is_empty()) {
            snapshot_instance = create_instance_id(current_snapshot);
            snapshot_instance->start();
        }
        emit_signal("initialized");
    }
}

Ref<FMODGuidDictionary> FMODRuntime::get_guid_dictionary() {
    return guid_dictionary;
}

void FMODRuntime::set_guid_dictionary(const Dictionary &p_guid_dictionary) {
    guid_dictionary = p_guid_dictionary;
}

void FMODRuntime::back_to_previous_music() {
    if (current_music != previous_music && !previous_music_resource_path.is_empty() && ResourceLoader::exists(previous_music_resource_path)) {
        Ref<EventAsset> res_previous_music =  ResourceLoader::load(previous_music_resource_path);
        if (res_previous_music.is_valid()) {
            set_current_music(res_previous_music);
        }
    }
}

void FMODRuntime::back_to_previous_snapshot() {
    if (current_snapshot != previous_snapshot && !previous_snapshot_resource_path.is_empty() && ResourceLoader::exists(previous_snapshot_resource_path)) {
        Ref<EventAsset> res_previous_snapshot =  ResourceLoader::load(previous_snapshot_resource_path);
        if (res_previous_snapshot.is_valid()) {
            set_current_snapshot(res_previous_snapshot);
        }
    }
}

String FMODRuntime::path_from_guid(const String &guid) const {
    if (guid_dictionary.is_valid()) {
        return guid_dictionary->guid_dictionary.get(guid,guid);
    }
    return guid;
}

void FMODRuntime::make_button_grab_focus(Control* button) { if(button != nullptr && button->get_focus_mode() != Control::FOCUS_NONE) button->grab_focus(); }

void FMODRuntime::set_current_music(const Ref<EventAsset> &desired_music) {
    if (!has_initialized) {
        if (desired_music.is_valid()) {
            current_music = desired_music->get_guid();
            current_music_resource_path = desired_music->get_path();
        }
        return;
    }
    if (desired_music.is_null() || !desired_music.is_valid()) {
        if (!current_music.is_empty()) {
            previous_music = current_music;
            previous_music_resource_path = current_music_resource_path;
        }
        current_music = "";
        current_music_resource_path = "";
    }
    else {
        if (desired_music->get_path() != current_music_resource_path) {
            if (!current_music.is_empty()) {
                previous_music = current_music;
                previous_music_resource_path = current_music_resource_path;
            }
            if (music_instance.is_valid()) {
                auto result = music_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
                result = music_instance->release();
                music_instance.unref();
            }
            current_music = desired_music->get_guid();
            current_music_resource_path = desired_music->get_path();
            music_instance = create_instance_id(desired_music->get_guid());
            if (music_instance.is_valid()) {
                auto result = music_instance->start();
            }
        }
    }
}

Ref<EventAsset> FMODRuntime::get_current_music() const {
    Ref<EventAsset> return_current_music;
    if (!current_music_resource_path.is_empty() && ResourceLoader::exists(current_music_resource_path)) {
        return_current_music =  ResourceLoader::load(current_music_resource_path);
    }
    return return_current_music;
}

bool FMODRuntime::set_parameter_by_name(const String &name, float value, bool ignore_seek_speed) {
    if (has_initialized) {
        return FMODStudioModule::get_singleton()->get_studio_system_ref()->set_parameter_by_name(name,value,ignore_seek_speed);
    }
    return false;
}

void FMODRuntime::set_current_snapshot(const Ref<EventAsset> &desired_snapshot) {
    if (!has_initialized) {
        if (desired_snapshot.is_valid()) {
            current_snapshot = desired_snapshot->get_guid();
            current_snapshot_resource_path = desired_snapshot->get_path();
        }
        return;
    }
    if (desired_snapshot.is_null() || !desired_snapshot.is_valid()) {
        if (!current_snapshot.is_empty()) {
            previous_snapshot = current_snapshot;
            previous_snapshot_resource_path = current_snapshot_resource_path;
        }
        current_snapshot = "";
        current_snapshot_resource_path = "";
    }
    else {
        if (desired_snapshot->get_path() != current_snapshot_resource_path) {
            if (!current_snapshot.is_empty()) {
                previous_snapshot = current_snapshot;
                previous_snapshot_resource_path = current_snapshot_resource_path;
            }
            if (snapshot_instance.is_valid()) {
                auto result = snapshot_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
                result = snapshot_instance->release();
                snapshot_instance.unref();
            }
            current_snapshot = desired_snapshot->get_guid();
            current_snapshot_resource_path = desired_snapshot->get_path();
            snapshot_instance = create_instance_id(desired_snapshot->get_guid());
            if (snapshot_instance.is_valid()) {
                auto result = snapshot_instance->start();
            }
        }
    }
}

Ref<EventAsset> FMODRuntime::get_current_snapshot() const {
    Ref<EventAsset> return_current_snapshot;
    if (!current_snapshot_resource_path.is_empty() && ResourceLoader::exists(current_snapshot_resource_path)) {
        return_current_snapshot =  ResourceLoader::load(current_snapshot_resource_path);
    }
    return return_current_snapshot;
}

void FMODRuntime::set_click_and_hover_assets(const Ref<EventAsset> &_click, const Ref<EventAsset> &_hover) {
    has_sfx_click = _click.is_valid();
    has_sfx_hover = _hover.is_valid();
    if(has_sfx_click)
        sfx_click_asset = _click->get_guid();
    if(has_sfx_hover)
        sfx_hover_asset = _hover->get_guid();
}

void FMODRuntime::play_click_sfx() {
    if(!has_sfx_click) return;
    auto last_ticks_msec = OS::get_singleton()->get_ticks_msec();
    if (last_time_played_click + 50 < last_ticks_msec) {
        last_time_played_click = last_ticks_msec;
        play_one_shot_id(sfx_click_asset,Variant{});
    }
}

void FMODRuntime::play_hover_sfx() {
    if(!has_sfx_hover) return;
    auto last_ticks_msec = OS::get_singleton()->get_ticks_msec();
    if (last_time_played_hover + 50 < last_ticks_msec) {
        last_time_played_hover = last_ticks_msec;
        play_one_shot_id(sfx_hover_asset,Variant{});
    }
}

void FMODRuntime::setup_button_sfx_callback(Control* _button, const Callable &p_callable) {
    if(_button == nullptr) return;
    _button->connect(SceneStringNames::get_singleton()->mouse_entered, callable_mp(this, &FMODRuntime::make_button_grab_focus).bind(_button));
    _button->connect(SceneStringNames::get_singleton()->focus_entered, callable_mp(this, &FMODRuntime::play_hover_sfx));
    if (_button->has_signal("pressed")) {
        _button->connect("pressed",callable_mp(this,&FMODRuntime::play_click_sfx));
        _button->connect("pressed",p_callable);
    }
}

void FMODRuntime::setup_button_sfx(Control* _button) {
    if(_button == nullptr) return;
    _button->connect(SceneStringNames::get_singleton()->mouse_entered, callable_mp(this, &FMODRuntime::make_button_grab_focus).bind(_button));
    _button->connect(SceneStringNames::get_singleton()->focus_entered, callable_mp(this, &FMODRuntime::play_hover_sfx));
    if (_button->has_signal("pressed")) {
        _button->connect("pressed",callable_mp(this,&FMODRuntime::play_click_sfx));
    }
}

// 	func setup_click_and_hover_sfx_c(button:Control,callable : Callable,is_return:bool = false):
// 	button.mouse_entered.connect(make_button_grab_focus.bind(button))
// 	button.focus_entered.connect(play_hover_sfx)
// 	if button.has_signal("pressed"):
// 		button.pressed.connect(play_click_sfx)
// 		button.pressed.connect(callable)
//
// func setup_click_and_hover_sfx(button:Control,is_return:bool = false):
// 	button.mouse_entered.connect(make_button_grab_focus.bind(button))
// 	button.focus_entered.connect(play_hover_sfx)
// 	if button.has_signal("pressed"):
// 		button.pressed.connect(play_click_sfx)

String FMODRuntime::path_to_guid(const String &path) {
    return studio_system->lookup_id(path);
}

Ref<StudioApi::EventDescription> FMODRuntime::get_event_description(const Ref<EventAsset> &event_asset) {
    return studio_system->get_event_by_id(event_asset->get_guid());
}

Ref<StudioApi::EventDescription> FMODRuntime::get_event_description_path(const String &event_path) {
    return get_event_description_id(path_to_guid(event_path));
}

Ref<StudioApi::EventDescription> FMODRuntime::get_event_description_id(const String &guid) {
    return studio_system->get_event_by_id(guid);
}

Ref<StudioApi::EventInstance> FMODRuntime::create_instance(const Ref<EventAsset>  &event_asset) {
    return get_event_description_id(event_asset->get_guid())->create_instance();
}

Ref<StudioApi::EventInstance> FMODRuntime::create_instance_path(const String &event_path) {
    return get_event_description_path(event_path)->create_instance();;
}

Ref<StudioApi::EventInstance> FMODRuntime::create_instance_id(const String &guid) {
    return get_event_description_id(guid)->create_instance();
}

void FMODRuntime::play_one_shot_attached(const Ref<EventAsset> &event_asset, Node *node) {
    play_one_shot_attached_id(event_asset->get_guid(), node);
}

void FMODRuntime::play_looped_attached(const Ref<EventAsset> &event_asset, Node *node) {
    play_looped_attached_id(event_asset->get_guid(), node);
}

void FMODRuntime::play_one_shot_attached_path(const String &event_path, Node *node) {
    play_one_shot_attached_id(path_to_guid(event_path), node);
}

void FMODRuntime::play_one_shot_attached_id(const String &guid, Node *node) {
    Ref<StudioApi::EventInstance> instance = create_instance_id(guid);
    if (node->is_class("Node2D") || node->is_class("Node3D")) {
        attach_instance_to_node(instance, node,nullptr);
    } else {
        WARN_PRINT("[FMOD] Trying to attach an instance to an invalid node. The node should inherit Node3D or Node2D.");
    }
    if (debug_print_event_calls) {
        print_line("[FMOD] Event called ",path_from_guid(guid));
    }
    instance->start();
    instance->release();
}

void FMODRuntime::play_looped_attached_id(const String &guid, Node *node) {
    Ref<StudioApi::EventInstance> instance = create_instance_id(guid);
    if (node->is_class("Node2D") || node->is_class("Node3D")) {
        attach_instance_to_node(instance, node,nullptr);
    } else {
        WARN_PRINT("[FMOD] Trying to attach an instance to an invalid node. The node should inherit Node3D or Node2D.");
    }
    if (debug_print_event_calls) {
        print_line("[FMOD] Event called looped ",path_from_guid(guid));
    }
    instance->created_guid = guid;
    instance->start();
    // If the outer_key doesn't exist in the outer HashMap, it would default construct an inner Vector
    Vector<Ref<StudioApi::EventInstance>>& inner_map = looped_instances[node->get_instance_id()];
    inner_map.push_back(instance);
    auto destroy_callable = callable_mp(this,&FMODRuntime::stop_looped_id).bind(guid,node->get_instance_id());
    if (!node->is_connected("tree_exiting", destroy_callable))
        node->connect("tree_exiting", destroy_callable);
}

void FMODRuntime::stop_looped_id(const String &guid, ObjectID node_obj_id) {
    if (node_obj_id.is_valid()) {
        Vector<Ref<StudioApi::EventInstance>>& inner_map = looped_instances[node_obj_id];
        for (int i = 0; i < inner_map.size(); ++i) {
            auto ref_instance = inner_map[i];
            if (ref_instance.is_valid() && ref_instance->created_guid == guid) {
                ref_instance->release();
                inner_map.remove_at(i);
            }
        }
    }
}

void FMODRuntime::stop_looped(const Ref<EventAsset> &event_asset, Node *node) {
    stop_looped_id(event_asset->get_guid(), node->get_instance_id());
}

void FMODRuntime::play_looped(const Ref<EventAsset> &event_asset, Node *node, const Variant &position = Variant()) {
    play_looped_id(event_asset->get_guid(), node, position);
}

void FMODRuntime::play_one_shot(const Ref<EventAsset> &event_asset, const Variant &position = Variant()) {
    play_one_shot_id(event_asset->get_guid(), position);
}

void FMODRuntime::play_one_shot_path(const String &event_path, const Variant &position = Variant()) {
    play_one_shot_id(path_to_guid(event_path), position);
}

void FMODRuntime::play_one_shot_volume(const Ref<EventAsset> &event_asset, const float volume, const Variant &position = Variant()) {
    play_one_shot_id_volume(event_asset->get_guid(),volume, position);
}

void FMODRuntime::play_one_shot_path_volume(const String &event_path, const float volume, const Variant &position = Variant()) {
    play_one_shot_id_volume(path_to_guid(event_path),volume, position);
}

void FMODRuntime::play_one_shot_id(const String &guid, const Variant &position = Variant()) {
    Ref<StudioApi::EventInstance> instance = create_instance_id(guid);
    if (!instance.is_valid()) {
        return;
    }
    const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = memnew(FmodTypes::FMOD_3D_ATTRIBUTES);
    Variant::Type type = position.get_type();
    bool is_3d = instance->is_3d();
    if (is_3d && type == Variant::Type::OBJECT) {
        RuntimeUtils::to_3d_attributes_node(attributes, Object::cast_to<Node>(position), nullptr);
        float max_distance = instance->get_min_max_distance_v2().y * instance->get_min_max_distance_v2().y;
        bool should_play_instance = ListenerImpl::distance_to_nearest_listener(attributes->get_position()) <= max_distance * max_distance;
        if (!should_play_instance) {
            if (debug_print_event_calls) {
                print_line("[FMOD] Event wasn't called because of distance ",path_from_guid(guid));
            }
            return;
        }
    } else if (is_3d && (type == Variant::Type::VECTOR2 || type == Variant::Type::VECTOR3 || type == Variant::Type::TRANSFORM2D || type == Variant::Type::TRANSFORM3D)) {
        RuntimeUtils::to_3d_attributes(attributes, position);
        float max_distance = instance->get_min_max_distance_v2().y * instance->get_min_max_distance_v2().y;
        bool should_play_instance = ListenerImpl::distance_to_nearest_listener(attributes->get_position()) <= max_distance * max_distance;
        if (!should_play_instance) {
            if (debug_print_event_calls) {
                print_line("[FMOD] Event wasn't called because of distance ",path_from_guid(guid));
            }
            return;
        }
    } else {
        RuntimeUtils::to_3d_attributes(attributes, Vector3(0, 0, 0));
    }
    if (debug_print_event_calls) {
        print_line("[FMOD] Event called ",path_from_guid(guid));
    }
    instance->set_3d_attributes(attributes);
    instance->start();
    instance->release();
}

void FMODRuntime::play_looped_id(const String &guid, Node *node, const Variant &position = Variant()) {
    Ref<StudioApi::EventInstance> instance = create_instance_id(guid);
    if (!instance.is_valid()) {
        return;
    }
    const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = memnew(FmodTypes::FMOD_3D_ATTRIBUTES);
    Variant::Type type = position.get_type();
    bool is_3d = instance->is_3d();
    if (is_3d && type == Variant::Type::OBJECT) {
        RuntimeUtils::to_3d_attributes_node(attributes, Object::cast_to<Node>(position), nullptr);
        float max_distance = instance->get_min_max_distance_v2().y * instance->get_min_max_distance_v2().y;
        bool should_play_instance = ListenerImpl::distance_to_nearest_listener(attributes->get_position()) <= max_distance * max_distance;
        if (!should_play_instance) {
            if (debug_print_event_calls) {
                print_line("[FMOD] Event wasn't called because of distance ",path_from_guid(guid));
            }
            return;
        }
    } else if (is_3d && (type == Variant::Type::VECTOR2 || type == Variant::Type::VECTOR3 || type == Variant::Type::TRANSFORM2D || type == Variant::Type::TRANSFORM3D)) {
        RuntimeUtils::to_3d_attributes(attributes, position);
        float max_distance = instance->get_min_max_distance_v2().y * instance->get_min_max_distance_v2().y;
        bool should_play_instance = ListenerImpl::distance_to_nearest_listener(attributes->get_position()) <= max_distance * max_distance;
        if (!should_play_instance) {
            if (debug_print_event_calls) {
                print_line("[FMOD] Event wasn't called because of distance ",path_from_guid(guid));
            }
            return;
        }
    } else {
        RuntimeUtils::to_3d_attributes(attributes, Vector3(0, 0, 0));
    }
    if (debug_print_event_calls) {

        print_line("[FMOD] Event called ",path_from_guid(guid));
    }
    instance->set_3d_attributes(attributes);
    instance->start();
    Vector<Ref<StudioApi::EventInstance>>& inner_map = looped_instances[node->get_instance_id()];
    inner_map.push_back(instance);
    auto destroy_callable = callable_mp(this,&FMODRuntime::stop_looped_id).bind(guid,node->get_instance_id());
    if (!node->is_connected("tree_exiting", destroy_callable))
        node->connect("tree_exiting", destroy_callable);
}


void FMODRuntime::play_one_shot_id_volume(const String &guid, const float volume, const Variant &position = Variant()) {
    Ref<StudioApi::EventInstance> instance = create_instance_id(guid);
    if (!instance.is_valid()) {
        return;
    }
    const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = memnew(FmodTypes::FMOD_3D_ATTRIBUTES);
    Variant::Type type = position.get_type();
    bool is_3d = instance->is_3d();
    if (is_3d && type == Variant::Type::OBJECT) {
        RuntimeUtils::to_3d_attributes_node(attributes, Object::cast_to<Node>(position), nullptr);
        float max_distance = instance->get_min_max_distance_v2().y * instance->get_min_max_distance_v2().y;
        bool should_play_instance = ListenerImpl::distance_to_nearest_listener(attributes->get_position()) <= max_distance * max_distance;
        if (!should_play_instance) {
            if (debug_print_event_calls) {
                print_line("[FMOD] Event wasn't called because of distance ",path_from_guid(guid));
            }
            return;
        }
    } else if (is_3d && (type == Variant::Type::VECTOR2 || type == Variant::Type::VECTOR3 || type == Variant::Type::TRANSFORM2D || type == Variant::Type::TRANSFORM3D)) {
        RuntimeUtils::to_3d_attributes(attributes, position);
        float max_distance = instance->get_min_max_distance_v2().y * instance->get_min_max_distance_v2().y;
        bool should_play_instance = ListenerImpl::distance_to_nearest_listener(attributes->get_position()) <= max_distance * max_distance;
        if (!should_play_instance) {
            if (debug_print_event_calls) {
                print_line("[FMOD] Event wasn't called because of distance ",path_from_guid(guid));
            }
            return;
        }
    } else {
        RuntimeUtils::to_3d_attributes(attributes, Vector3(0, 0, 0));
    }
    if (debug_print_event_calls) {
        print_line("[FMOD] Event called ",path_from_guid(guid));
    }
    instance->set_3d_attributes(attributes);
    instance->set_volume(volume);
    instance->start();
    instance->release();
}

void FMODRuntime::attach_instance_to_node(const Ref<StudioApi::EventInstance> &instance, Node *node, Object *physicsbody = nullptr) {
    auto attached_instances = FMODStudioModule::get_singleton()->attached_instances;
    AttachedInstance attached_instance {instance,node,physicsbody};
    for (auto & _attached_instance : attached_instances) {
        if (_attached_instance.instance == instance) {
            attached_instance = _attached_instance;
        }
    }
    if (attached_instance.instance == nullptr) {
        attached_instance = AttachedInstance();
        attached_instances.push_back(attached_instance);
    }
    Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = memnew(FmodTypes::FMOD_3D_ATTRIBUTES);
    RuntimeUtils::to_3d_attributes_node(attributes, node, physicsbody);
    instance->set_3d_attributes(attributes);
    attached_instance.node = node;
    attached_instance.instance = instance;
    attached_instance.physicsbody = physicsbody;
}

void FMODRuntime::detach_instance_from_node(const Ref<StudioApi::EventInstance> &instance) {
    auto attached_instances = FMODStudioModule::get_singleton()->attached_instances;
    for (auto & _attached_instance : attached_instances) {
        if (_attached_instance.instance == instance) {
            _attached_instance = attached_instances.back();
            attached_instances.pop_back();
            break;
        }
    }
}

void FMODRuntime::do_ready() {
    set_process(true);
}

void FMODRuntime::do_exit_tree() {
    if (get_child_count() > 0 && debug_scene != nullptr) {
        debug_scene->set_process(false);
        debug_scene->queue_free();
        debug_scene = nullptr;
        FMODStudioModule::get_singleton()->shutdown();
        if (singleton != nullptr && singleton == this) {
            singleton = nullptr;
        }
    }
}

void FMODRuntime::do_process() {
    if (!has_initialized) return;
    if (!studio_system->is_valid()) return;

    StudioEventEmitter3D::update_active_emitters();
    int i = 0;
    auto attached_instances = FMODStudioModule::get_singleton()->attached_instances;

    while (i < attached_instances.size() && i >= 0) {
        FMOD_STUDIO_PLAYBACK_STATE playback_state = FMOD_STUDIO_PLAYBACK_STOPPED;
        if (attached_instances[i].instance->is_valid()) {
            playback_state = attached_instances[i].instance->get_playback_state();
        }
        if (playback_state == FMOD_STUDIO_PLAYBACK_STOPPED || attached_instances[i].node == nullptr) {
            attached_instances[i] = attached_instances.back();
            attached_instances.pop_back();
            --i;
            continue;
        }
        Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = memnew(FmodTypes::FMOD_3D_ATTRIBUTES);
        if (attached_instances[i].node->is_inside_tree()) {
            RuntimeUtils::to_3d_attributes_node(attributes, attached_instances[i].node, attached_instances[i].physicsbody);
            attached_instances[i].instance->set_3d_attributes(attributes);
        } else {
            WARN_PRINT("[FMOD] Trying to set FMOD_3D_ATTRIBUTES for an attached instance, but the instance is not inside the scene tree anymore. Detach the instance before removing the node from the tree.");
        }
        ++i;
    }
    studio_system->update();
}

void FMODRuntime::setup_in_tree() {
    if(!already_setup_in_tree && SceneTree::get_singleton() != nullptr) {
        if (!is_fmod_enabled()) {
            return;
        }
        SceneTree::get_singleton()->get_root()->call_deferred("add_child",this);
        already_setup_in_tree=true;
    }
}

FMODRuntime::FMODRuntime() {
    singleton = this;
    last_time_played_hover = 0;
    last_time_played_click = 0;
    debug_scene = nullptr;
}

FMODRuntime::~FMODRuntime() {
    if (has_initialized) {
        if (snapshot_instance.is_valid()) {
            snapshot_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
            snapshot_instance->release();
            snapshot_instance.unref();
        }

        if (music_instance.is_valid()) {
            music_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
            music_instance->release();
            music_instance.unref();
        }
    }
    if(singleton != nullptr && singleton == this) {
        singleton = nullptr;
    }
}

FMODRuntime * FMODRuntime::get_singleton() {
    return singleton;
}
