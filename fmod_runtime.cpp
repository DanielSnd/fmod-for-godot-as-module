//
// Created by Daniel on 2024-01-18.
//

#include "fmod_runtime.h"

void FMODRuntime::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_studio_system", "studio_system"), &FMODRuntime::set_studio_system);
    ClassDB::bind_method(D_METHOD("get_studio_system"), &FMODRuntime::get_studio_system);
    ClassDB::bind_method(D_METHOD("setup_in_tree"), &FMODRuntime::setup_in_tree);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "studio_system"), "set_studio_system", "get_studio_system");

    ClassDB::bind_method(D_METHOD("set_debug_scene", "debug_scene"), &FMODRuntime::set_debug_scene);
    ClassDB::bind_method(D_METHOD("get_debug_scene"), &FMODRuntime::get_debug_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "debug_scene", PROPERTY_HINT_NODE_TYPE,"Node"), "set_debug_scene", "get_debug_scene");

    ClassDB::bind_method(D_METHOD("set_debug_print_event_calls", "status"), &FMODRuntime::set_debug_print_event_calls);
    ClassDB::bind_method(D_METHOD("get_debug_print_event_calls"), &FMODRuntime::get_debug_print_event_calls);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "debug_print_event_calls"), "set_debug_print_event_calls", "get_debug_print_event_calls");

    ClassDB::bind_method(D_METHOD("path_to_guid","fmod_path"), &FMODRuntime::path_to_guid);

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
    ClassDB::bind_method(D_METHOD("attach_instance_to_node","event_instance","node","physicsbody"), &FMODRuntime::attach_instance_to_node);
    ClassDB::bind_method(D_METHOD("detach_instance_from_node","event_instance"), &FMODRuntime::detach_instance_from_node);
}

void FMODRuntime::_notification(int p_what) {
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

        const String settings_path = get_platform_setting_path(PlatformSettingsPath::FMOD_SETTINGS_PATH);
        const bool enable_debug_performance =
                static_cast<bool>(get_platform_project_setting(settings_path + String("debug_performance")));
        if (OS::get_singleton()->has_feature("editor") && enable_debug_performance) {
            debug_scene = memnew(FMODDebugMonitor);
            call_deferred("add_child",debug_scene);
        }
    }
}

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
        print_line("[FMOD] Event called ",guid);
    }
    instance->start();
    instance->release();
}

void FMODRuntime::play_one_shot(const Ref<EventAsset> &event_asset, const Variant &position = Variant()) {
    play_one_shot_id(event_asset->get_guid(), position);
}

void FMODRuntime::play_one_shot_path(const String &event_path, const Variant &position = Variant()) {
    play_one_shot_id(path_to_guid(event_path), position);
}

void FMODRuntime::play_one_shot_id(const String &guid, const Variant &position = Variant()) {
    Ref<StudioApi::EventInstance> instance = create_instance_id(guid);
    const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> attributes = memnew(FmodTypes::FMOD_3D_ATTRIBUTES);
    Variant::Type type = position.get_type();
    if (type == Variant::Type::OBJECT) {
        RuntimeUtils::to_3d_attributes_node(attributes, Object::cast_to<Node>(position), nullptr);
    } else if (type == Variant::Type::VECTOR2 || type == Variant::Type::VECTOR3 || type == Variant::Type::TRANSFORM2D || type == Variant::Type::TRANSFORM3D) {
        RuntimeUtils::to_3d_attributes(attributes, position);
    } else {
        RuntimeUtils::to_3d_attributes(attributes, Vector3(0, 0, 0));
    }
    if (debug_print_event_calls) {
        print_line("[FMOD] Event called ",guid);
    }
    instance->set_3d_attributes(attributes);
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


FMODRuntime* FMODRuntime::singleton = nullptr;

void FMODRuntime::setup_in_tree() {
    if(!already_setup_in_tree) {
        SceneTree::get_singleton()->get_root()->add_child(this);
        already_setup_in_tree=true;
    }
}

FMODRuntime::FMODRuntime() {
    singleton = this;
}

FMODRuntime::~FMODRuntime() {
}

FMODRuntime * FMODRuntime::get_singleton() {
    return singleton;
}
