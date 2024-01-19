#include "register_types.h"

#include "fmod_runtime.h"
#include "fmod_settings.h"
#include "fmod_studio_editor_module.h"
#include "fmod_studio_module.h"
#include "editor/editor_plugin.h"
#include "editor/fmod_plugin.h"
#include "editor/inspector_browser.h"
#include "editor/project_browser.h"
#include "editor/studio_event_emitter_3d_gizmo_plugin.h"
#include "scene/studio_bank_loader.h"
#include "scene/studio_event_emitter.h"
#include "scene/studio_global_parameter_trigger.h"
#include "scene/studio_listener.h"
#include "scene/studio_parameter_trigger.h"
#include "utils/debug_monitors.h"
#include "utils/runtime_utils.h"

static FMODStudioModule* fmod_module;
static FMODStudioEditorModule* fmod_editor_module;
static FMODSettings* fmod_settings;

void initialize_fmodgodot_module(ModuleInitializationLevel p_level)
{
#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
		if (fmod_settings == nullptr) {
			ClassDB::register_class<FMODSettings>();
			fmod_settings = memnew(FMODSettings);
		}

		ClassDB::register_class<FmodTCPClient>();
		ClassDB::register_class<FMODStudioEditorModule>();
		fmod_editor_module = memnew(FMODStudioEditorModule);
		Engine::get_singleton()->add_singleton(Engine::Singleton("FMODStudioEditorModule", FMODStudioEditorModule::get_singleton()));

		// Gizmo Plugins
		ClassDB::register_class<StudioEventEmitter3DGizmoPlugin>();

		// Editor Utilities
		ClassDB::register_class<ProjectCache>();

		ClassDB::register_class<FMODProjectBrowserPreviewButton>();
		ClassDB::register_class<FMODEditorInspector>();
		ClassDB::register_class<FMODEditorInspectorTree>();
		ClassDB::register_class<FMODEditorInspectorProperty>();
		ClassDB::register_class<FMODEditorInspectorPlugin>();

		ClassDB::register_class<FMODEditorDiscreteParameter>();
		ClassDB::register_class<FMODEditorLabeledParameter>();
		ClassDB::register_class<FMODEditorContinuousParameter>();

		ClassDB::register_class<FMODProjectBrowserTree>();
		ClassDB::register_class<FMODProjectBrowserWindow>();

		ClassDB::register_class<FMODEditorPlugin>();
		if (is_fmod_enabled()) {
			EditorPlugins::add_by_type<FMODEditorPlugin>();
		} else {
			FMODSettings::add_fmod_enabled_setting();
		}
	}
#endif

	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		if (fmod_settings == nullptr) {
			ClassDB::register_class<FMODSettings>();
			fmod_settings = memnew(FMODSettings);
		}
		// FMOD modules
		ClassDB::register_class<FMODRuntime>();
		ClassDB::register_class<FMODStudioModule>();
		fmod_module = memnew(FMODStudioModule);
		Engine::get_singleton()->add_singleton(Engine::Singleton("FMODStudioModule", FMODStudioModule::get_singleton()));

		if (fmod_module->fmod_runtime == nullptr) {
			fmod_module->fmod_runtime = memnew(FMODRuntime);
			Engine::get_singleton()->add_singleton(Engine::Singleton("FMODRuntime", FMODRuntime::get_singleton()));
		}
		// Studio API
		ClassDB::register_class<StudioApi::StudioSystem>();
		ClassDB::register_class<StudioApi::EventDescription>();
		ClassDB::register_class<StudioApi::EventInstance>();
		ClassDB::register_class<StudioApi::Bus>();
		ClassDB::register_class<StudioApi::Bank>();
		ClassDB::register_class<StudioApi::VCA>();
		ClassDB::register_class<StudioApi::CommandReplay>();

		// FMOD specific types
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_PARAMETER_ID>();
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_PARAMETER_DESCRIPTION>();
		ClassDB::register_class<FmodTypes::FMOD_3D_ATTRIBUTES>();
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_BUFFER_INFO>();
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_BUFFER_USAGE>();
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_CPU_USAGE>();
		ClassDB::register_class<FmodTypes::FMOD_CPU_USAGE>();
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_MEMORY_USAGE>();
		ClassDB::register_class<FmodTypes::FMOD_STUDIO_USER_PROPERTY>();

		// FMOD Resources
		ClassDB::register_class<FMODAsset>();
		ClassDB::register_class<BankAsset>();
		ClassDB::register_class<EventAsset>();
		ClassDB::register_class<BusAsset>();
		ClassDB::register_class<VCAAsset>();
		ClassDB::register_class<ParameterAsset>();

		// Runtime Utils
		ClassDB::register_class<RuntimeUtils>();

		// Custom nodes
		ClassDB::register_class<StudioEventEmitter3D>();
		ClassDB::register_class<StudioEventEmitter2D>();
		ClassDB::register_class<StudioParameterTrigger>();
		ClassDB::register_class<StudioGlobalParameterTrigger>();
		ClassDB::register_class<StudioBankLoader>();
		ClassDB::register_class<StudioListener3D>();
		ClassDB::register_class<StudioListener2D>();

		// Custom performance monitors
		ClassDB::register_class<FMODDebugMonitor>();
	}
}

void uninitialize_fmodgodot_module(ModuleInitializationLevel p_level)
{
#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		Engine::get_singleton()->remove_singleton("FMODStudioEditorModule");
		memdelete(fmod_editor_module);
		fmod_editor_module = nullptr;
	}
#endif

	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		Engine::get_singleton()->remove_singleton("FMODStudioModule");
		Engine::get_singleton()->remove_singleton("FMODRuntime");
		if(fmod_module->fmod_runtime != nullptr) {
			memdelete(fmod_module->fmod_runtime);
			fmod_module->fmod_runtime = nullptr;
		}
		memdelete(fmod_module);
		fmod_module = nullptr;
		if (fmod_settings != nullptr) {
			memdelete(fmod_settings);
			fmod_settings = nullptr;
		}
	}
}