#ifndef STUDIO_EVENT_EMITTER_3D_GIZMO_PLUGIN
#define STUDIO_EVENT_EMITTER_3D_GIZMO_PLUGIN

// This is slighty modified version of Godot's AudioStreamPlayer3DGizmoPlugin
// in editor/plugins/node_3d_editor_gizmos.cpp and adapted to also display
// the minimum distance of an FMOD Event.
// License: godotengine.org/license

#include "../scene/studio_event_emitter.h"
#include "editor/plugins/node_3d_editor_gizmos.h"

class StudioEventEmitter3DGizmoPlugin : public EditorNode3DGizmoPlugin
{
	GDCLASS(StudioEventEmitter3DGizmoPlugin, EditorNode3DGizmoPlugin);

protected:
	static void _bind_methods();
	bool has_gizmo(Node3D* for_node_3d) override;

private:

public:
	StudioEventEmitter3DGizmoPlugin()
	{
		create_icon_material("studio_event_emitter_3d_icon", FMODStudioEditorModule::get_singleton()->get_icon(FMODStudioEditorModule::FMOD_ICONTYPE_FMODEMITTER));
		create_material("studio_event_emitter_3d_material_billboard", Color(0.4, 0.8, 1), true, false, true);
	}

	String get_gizmo_name() const override;
	int32_t get_priority() const override;
	void redraw(EditorNode3DGizmo *p_gizmo) override;
};

#endif