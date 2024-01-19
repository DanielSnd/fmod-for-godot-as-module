#ifndef RUNTIME_UTILS_H
#define RUNTIME_UTILS_H

#include "../fmod_studio_module.h"
#include "../fmod_types.h"
#include "core/object/ref_counted.h"

class RuntimeUtils : public RefCounted
{
	GDCLASS(RuntimeUtils, RefCounted);

protected:
	static void _bind_methods();

public:
	static void to_3d_attributes_node(const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> &attributes, Object *node, Object *physicsbody);
	static void to_3d_attributes_transform_physicsbody(const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> &attributes,
	                                                   const Variant &transform, Object *physicsbody);
	static void to_3d_attributes(const Ref<FmodTypes::FMOD_3D_ATTRIBUTES> &attributes, const Variant &position);
};

VARIANT_ENUM_CAST(FmodGameEvent);

#endif // RUNTIME_UTILS_H