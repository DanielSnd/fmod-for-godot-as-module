#ifndef FMOD_PLUGIN
#define FMOD_PLUGIN

#include "fmod_studio_editor_module.h"
#include "inspector_browser.h"
#include "project_browser.h"
#include "studio_event_emitter_3d_gizmo_plugin.h"
#include "editor/editor_interface.h"
#include "modules/modules_enabled.gen.h"
#include "fmod_icons.gen.h"

class FMODEditorPlugin : public EditorPlugin
{
	GDCLASS(FMODEditorPlugin, EditorPlugin);

protected:
	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("on_project_browser_button_pressed"), &FMODEditorPlugin::on_project_browser_button_pressed);
	}
	void _notification(int p_what) {
		switch (p_what) {
			case NOTIFICATION_ENTER_TREE: {
				//do_enter_tree();
			} break;
			case NOTIFICATION_READY: {
				do_enter_tree();
			} break;
			case NOTIFICATION_EXIT_TREE: {
				do_exit_tree();
			} break;
		}
	}

private:
	Ref<StudioEventEmitter3DGizmoPlugin> gizmo_plugin;
	Ref<FMODEditorInspectorPlugin> inspector_plugin;
	FMODProjectBrowserWindow* project_preview_browser;
	FMODProjectBrowserPreviewButton* project_preview_button;

public:
	void do_enter_tree()
	{
		FMODStudioEditorModule* fmod_editor = FMODStudioEditorModule::get_singleton();
		if (FMODSettings::get_singleton() != nullptr && !FMODSettings::get_singleton()->already_initialized) {
			FMODSettings::get_singleton()->initialize();
		}
		// Create Icons
		if (fmod_editor)
		{
			Dictionary icons;
			for (int i = 0; i < fmod_icons_count; i++) {
				icons[fmod_icons_names[i]] = i;
			}

			fmod_editor->create_icon(icons["fmod_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_PROJECT);
			fmod_editor->create_icon(icons["folder_closed"], FMODStudioEditorModule::FMOD_ICONTYPE_FOLDER_CLOSED);
			fmod_editor->create_icon(icons["folder_opened"], FMODStudioEditorModule::FMOD_ICONTYPE_FOLDER_OPENED);
			fmod_editor->create_icon(icons["event_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_EVENT);
			fmod_editor->create_icon(icons["bank_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_BANK);
			fmod_editor->create_icon(icons["snapshot_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_SNAPSHOT);
			fmod_editor->create_icon(icons["bus_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_BUS);
			fmod_editor->create_icon(icons["vca_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_VCA);
			fmod_editor->create_icon(icons["c_parameter_icon"], FMODStudioEditorModule::FMOD_ICONTYPE_C_PARAMETER);
			fmod_editor->create_icon(icons["fmod_emitter"], FMODStudioEditorModule::FMOD_ICONTYPE_FMODEMITTER);
		}

		// Init Project Browser
		project_preview_browser = memnew(FMODProjectBrowserWindow);
		float editor_scale = get_editor_interface()->get_editor_scale();
		project_preview_browser->set_editor_scale(editor_scale);
		project_preview_browser->initialize();

		// Add the Project Browser Button to the Container Toolbar
		project_preview_button = memnew(FMODProjectBrowserPreviewButton);
		project_preview_button->initialize();
		add_control_to_container(EditorPlugin::CONTAINER_TOOLBAR, project_preview_button);

		if (project_preview_button->get_child_count() == 0)
		{
			project_preview_button->call_deferred("add_child", project_preview_browser);
			project_preview_browser->set_visible(false);
		}

		// Set the Project Browser visible when pressed
		project_preview_button->connect("pressed", callable_mp(this, &FMODEditorPlugin::on_project_browser_button_pressed));

		gizmo_plugin.instantiate();
		add_node_3d_gizmo_plugin(gizmo_plugin);

		inspector_plugin.instantiate();
		inspector_plugin->set_editor_scale(editor_scale);
		add_inspector_plugin(inspector_plugin);
	}

	void do_exit_tree()
	{
		remove_control_from_container(EditorPlugin::CONTAINER_TOOLBAR, project_preview_button);
		project_preview_button->queue_free();
		remove_node_3d_gizmo_plugin(gizmo_plugin);
		remove_inspector_plugin(inspector_plugin);
		project_preview_browser->queue_free();
	}

	void on_project_browser_button_pressed()
	{
		if (!is_fmod_enabled()) {
			ERR_PRINT("[FMOD] Enable FMOD on the settings menu and restart godot.");
			return;
		}
		//print_line("project browser button pressed ",project_preview_browser == nullptr);
		if (!project_preview_browser->is_visible() && project_preview_browser->is_inside_tree())
		{
			project_preview_browser->popup_centered();
		}
		else
		{
			project_preview_browser->set_visible(false);
		}
	}
};

#endif