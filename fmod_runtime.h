//
// Created by Daniel on 2024-01-18.
//

#ifndef FMOD_RUNTIME_H
#define FMOD_RUNTIME_H
#include <vector>

#include "fmod_assets.h"
#include "api/studio_api.h"
#include "scene/main/node.h"
#include "fmod_types.h"
#include "fmod_assets.h"
#include "fmod_studio_module.h"
#include "scene/studio_event_emitter.h"
#include "scene/main/window.h"
#include "utils/debug_monitors.h"
#include "utils/runtime_utils.h"

class FMODStudioModule;

class FMODRuntime : public Node
{
	GDCLASS(FMODRuntime, Node)

    protected:
        static void _bind_methods();

	public:
		Ref<StudioApi::StudioSystem> studio_system;
		Ref<StudioApi::StudioSystem> get_studio_system(){return studio_system;}
		void set_studio_system(Ref<StudioApi::StudioSystem> val){studio_system = val;}

		bool already_setup_in_tree = false;
		Node* debug_scene;
		Node* get_debug_scene() {return debug_scene;}
		void set_debug_scene(Node* val) { debug_scene = val; }

		void _notification(int p_what);

		void do_enter_tree();

        String path_to_guid(const String &path);

        Ref<StudioApi::EventDescription> get_event_description(const Ref<EventAsset> &event_asset);

        Ref<StudioApi::EventDescription> get_event_description_path(const String &event_path);

        Ref<StudioApi::EventDescription> get_event_description_id(const String &guid);

        Ref<StudioApi::EventInstance> create_instance(const Ref<EventAsset> &event_asset);

        Ref<StudioApi::EventInstance> create_instance_path(const String &event_path);

        Ref<StudioApi::EventInstance> create_instance_id(const String &guid);

        void play_one_shot_attached(const Ref<EventAsset> &event_asset, Node *node);

        void play_one_shot_attached_path(const String &event_path, Node *node);

        void play_one_shot_attached_id(const String &guid, Node *node);

        void play_one_shot(const Ref<EventAsset> &event_asset, const Variant &position);

        void play_one_shot_path(const String &event_path, const Variant &position);

	void play_one_shot_volume(const Ref<EventAsset> &event_asset, float volume, const Variant &position);

	void play_one_shot_path_volume(const String &event_path, float volume, const Variant &position);

	void play_one_shot_id(const String &guid, const Variant &position);

	void play_one_shot_id_volume(const String &guid, float volume, const Variant &position);

	void attach_instance_to_node(const Ref<StudioApi::EventInstance> &instance, Node *node, Object *physicsbody);

        void detach_instance_from_node(const Ref<StudioApi::EventInstance> &instance);

        void do_ready();
		void do_exit_tree();
		void do_process();

        static FMODRuntime* singleton;
	    static FMODRuntime* get_singleton();
		bool has_initialized = false;
		bool debug_print_event_calls = false;
		bool get_debug_print_event_calls() const {return debug_print_event_calls;}
		void set_debug_print_event_calls(bool val) {debug_print_event_calls = val;}
		void setup_in_tree();
	    FMODRuntime();
	    ~FMODRuntime() override;
};

#endif //FMOD_RUNTIME_H
