#include "fmod_types.h"

namespace FmodTypes
{

void FMOD_STUDIO_PARAMETER_ID::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_data_1", "data1"), &FMOD_STUDIO_PARAMETER_ID::set_data1);
	ClassDB::bind_method(D_METHOD("get_data_1"), &FMOD_STUDIO_PARAMETER_ID::get_data1);
	ClassDB::bind_method(D_METHOD("set_data_2", "data2"), &FMOD_STUDIO_PARAMETER_ID::set_data2);
	ClassDB::bind_method(D_METHOD("get_data_2"), &FMOD_STUDIO_PARAMETER_ID::get_data2);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "data1"), "set_data_1", "get_data_1");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "data2"), "set_data_2", "get_data_2");
}

void FMOD_STUDIO_PARAMETER_ID::set_data1(const unsigned int& _data1)
{
	this->data1 = _data1;
}

unsigned int FMOD_STUDIO_PARAMETER_ID::get_data1() const
{
	return data1;
}

void FMOD_STUDIO_PARAMETER_ID::set_data2(const unsigned int& _data2)
{
	this->data2 = _data2;
}

unsigned int FMOD_STUDIO_PARAMETER_ID::get_data2() const
{
	return data2;
}

void FMOD_STUDIO_PARAMETER_ID::set_parameter_id(const ::FMOD_STUDIO_PARAMETER_ID& parameter_id)
{
	set_data1(parameter_id.data1);
	set_data2(parameter_id.data2);
}

void FMOD_STUDIO_PARAMETER_ID::get_parameter_id(::FMOD_STUDIO_PARAMETER_ID& out_id) const
{
	out_id.data1 = get_data1();
	out_id.data2 = get_data2();
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_id", "id"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::set_id);
	ClassDB::bind_method(D_METHOD("get_id"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_id);
	ClassDB::bind_method(D_METHOD("set_minimum", "minimum"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::set_minimum);
	ClassDB::bind_method(D_METHOD("get_minimum"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_minimum);
	ClassDB::bind_method(D_METHOD("set_maximum", "maximum"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::set_maximum);
	ClassDB::bind_method(D_METHOD("get_maximum"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_maximum);
	ClassDB::bind_method(D_METHOD("set_default_value", "default_value"),
			&FMOD_STUDIO_PARAMETER_DESCRIPTION::set_default_value);
	ClassDB::bind_method(D_METHOD("get_default_value"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_default_value);
	ClassDB::bind_method(D_METHOD("set_type", "type"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_type);
	ClassDB::bind_method(D_METHOD("set_flags", "flags"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::set_flags);
	ClassDB::bind_method(D_METHOD("get_flags"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_flags);
	ClassDB::bind_method(D_METHOD("set_guid", "guid"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::set_guid);
	ClassDB::bind_method(D_METHOD("get_guid"), &FMOD_STUDIO_PARAMETER_DESCRIPTION::get_guid);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "id", PROPERTY_HINT_RESOURCE_TYPE, "FMOD_STUDIO_PARAMETER_ID"), "set_id",
			"get_id");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "minimum"), "set_minimum", "get_minimum");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "maximum"), "set_maximum", "get_maximum");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "default_value"), "set_default_value", "get_default_value");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM,
						 "GAME_CONTROLLED,DISTANCE,EVENT_CONE_ANGLE,EVENT_ORIENTATION,DIRECTION,ELEVATION,"
						 "LISTENER_ORIENTATION,SPEED,SPEED_ABSOLUTE,DISTANCE_NORMALIZED,MAX"),
			"set_type", "get_type");
	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "flags", PROPERTY_HINT_FLAGS, "READONLY, AUTOMATIC, GLOBAL, DISCRETE, LABELED"),
			"set_flags", "get_flags");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "guid"), "set_guid", "get_guid");
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_id(const Ref<FMOD_STUDIO_PARAMETER_ID>& _id)
{
	this->id = _id;
}

Ref<FMOD_STUDIO_PARAMETER_ID> FMOD_STUDIO_PARAMETER_DESCRIPTION::get_id() const
{
	return id;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_minimum(float _minimum)
{
	this->minimum = _minimum;
}

float FMOD_STUDIO_PARAMETER_DESCRIPTION::get_minimum() const
{
	return minimum;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_maximum(float _maximum)
{
	this->maximum = _maximum;
}

float FMOD_STUDIO_PARAMETER_DESCRIPTION::get_maximum() const
{
	return maximum;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_default_value(float _defaultValue)
{
	this->defaultvalue = _defaultValue;
}

float FMOD_STUDIO_PARAMETER_DESCRIPTION::get_default_value() const
{
	return defaultvalue;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_type(int _type)
{
	this->type = (FMOD_STUDIO_PARAMETER_TYPE)_type;
}

int FMOD_STUDIO_PARAMETER_DESCRIPTION::get_type() const
{
	return (int)type;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_flags(int _flags)
{
	this->flags = _flags;
}

int FMOD_STUDIO_PARAMETER_DESCRIPTION::get_flags() const
{
	return flags;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_guid(const String& _guid)
{
	this->guid = _guid;
}

String FMOD_STUDIO_PARAMETER_DESCRIPTION::get_guid() const
{
	return guid;
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::set_parameter_description(
		const ::FMOD_STUDIO_PARAMETER_DESCRIPTION& _parameter_description)
{
	name = _parameter_description.name;
	id = create_ref<FmodTypes::FMOD_STUDIO_PARAMETER_ID>();
	id->set_parameter_id(_parameter_description.id);
	minimum = _parameter_description.minimum;
	maximum = _parameter_description.maximum;
	defaultvalue = _parameter_description.defaultvalue;
	type = _parameter_description.type;
	flags = _parameter_description.flags;
	guid = guid_to_string(_parameter_description.guid);
}

void FMOD_STUDIO_PARAMETER_DESCRIPTION::get_parameter_description(
		::FMOD_STUDIO_PARAMETER_DESCRIPTION& out_description) const
{
	out_description.name = name.utf8().get_data();
	id->get_parameter_id(out_description.id);
	out_description.minimum = minimum;
	out_description.maximum = maximum;
	out_description.defaultvalue = defaultvalue;
	out_description.type = type;
	out_description.flags = flags;
	FMOD::Studio::parseID(guid.utf8().get_data(), &out_description.guid);
}

void FMOD_STUDIO_USER_PROPERTY::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_name", "name"), &FMOD_STUDIO_USER_PROPERTY::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &FMOD_STUDIO_USER_PROPERTY::get_name);
	ClassDB::bind_method(D_METHOD("set_type", "type"), &FMOD_STUDIO_USER_PROPERTY::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &FMOD_STUDIO_USER_PROPERTY::get_type);
	ClassDB::bind_method(D_METHOD("set_intvalue", "intvalue"), &FMOD_STUDIO_USER_PROPERTY::set_intvalue);
	ClassDB::bind_method(D_METHOD("get_intvalue"), &FMOD_STUDIO_USER_PROPERTY::get_intvalue);
	ClassDB::bind_method(D_METHOD("set_boolvalue", "boolvalue"), &FMOD_STUDIO_USER_PROPERTY::set_boolvalue);
	ClassDB::bind_method(D_METHOD("get_boolvalue"), &FMOD_STUDIO_USER_PROPERTY::get_boolvalue);
	ClassDB::bind_method(D_METHOD("set_floatvalue", "floatvalue"), &FMOD_STUDIO_USER_PROPERTY::set_floatvalue);
	ClassDB::bind_method(D_METHOD("get_floatvalue"), &FMOD_STUDIO_USER_PROPERTY::get_floatvalue);
	ClassDB::bind_method(D_METHOD("set_stringvalue", "stringvalue"), &FMOD_STUDIO_USER_PROPERTY::set_stringvalue);
	ClassDB::bind_method(D_METHOD("get_stringvalue"), &FMOD_STUDIO_USER_PROPERTY::get_stringvalue);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM,
						 "INTEGER,BOOLEAN,FLOAT,STRING"),
			"set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "intvalue"), "set_intvalue", "get_intvalue");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "boolvalue"), "set_boolvalue", "get_boolvalue");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "floatvalue"), "set_floatvalue", "get_floatvalue");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "stringvalue"), "set_stringvalue", "get_stringvalue");
}

void FMOD_STUDIO_USER_PROPERTY::set_name(const String& _name)
{
	this->name = _name;
}

String FMOD_STUDIO_USER_PROPERTY::get_name() const
{
	return name;
}

void FMOD_STUDIO_USER_PROPERTY::set_type(int _type)
{
	this->type = (FMOD_STUDIO_USER_PROPERTY_TYPE)_type;
}

int FMOD_STUDIO_USER_PROPERTY::get_type() const
{
	return type;
}

void FMOD_STUDIO_USER_PROPERTY::set_intvalue(int _intvalue)
{
	this->intvalue = _intvalue;
}

int FMOD_STUDIO_USER_PROPERTY::get_intvalue() const
{
	return intvalue;
}

void FMOD_STUDIO_USER_PROPERTY::set_boolvalue(bool _boolvalue)
{
	this->boolvalue = _boolvalue;
}

bool FMOD_STUDIO_USER_PROPERTY::get_boolvalue() const
{
	return boolvalue;
}

void FMOD_STUDIO_USER_PROPERTY::set_floatvalue(float _floatvalue)
{
	this->floatvalue = _floatvalue;
}

float FMOD_STUDIO_USER_PROPERTY::get_floatvalue() const
{
	return floatvalue;
}

void FMOD_STUDIO_USER_PROPERTY::set_stringvalue(const String& _stringvalue)
{
	this->stringvalue = _stringvalue;
}

String FMOD_STUDIO_USER_PROPERTY::get_stringvalue() const
{
	return stringvalue;
}

void FMOD_STUDIO_USER_PROPERTY::set_user_property(const ::FMOD_STUDIO_USER_PROPERTY& user_property)
{
	name = user_property.name;
	type = user_property.type;
	intvalue = user_property.intvalue;
	boolvalue = user_property.boolvalue;
	floatvalue = user_property.floatvalue;
	if (type == FMOD_STUDIO_USER_PROPERTY_TYPE_STRING)
	{
		stringvalue = user_property.stringvalue;
	}
}

void FMOD_STUDIO_USER_PROPERTY::get_user_property(::FMOD_STUDIO_USER_PROPERTY& out_user_property) const
{
	out_user_property.name = name.utf8().get_data();
	out_user_property.type = type;
	out_user_property.intvalue = intvalue;
	out_user_property.boolvalue = boolvalue;
	out_user_property.floatvalue = floatvalue;
	out_user_property.stringvalue = stringvalue.utf8().get_data();
}

void FMOD_3D_ATTRIBUTES::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_forward", "forward"), &FMOD_3D_ATTRIBUTES::set_forward);
	ClassDB::bind_method(D_METHOD("get_forward"), &FMOD_3D_ATTRIBUTES::get_forward);
	ClassDB::bind_method(D_METHOD("set_up", "up"), &FMOD_3D_ATTRIBUTES::set_up);
	ClassDB::bind_method(D_METHOD("get_up"), &FMOD_3D_ATTRIBUTES::get_up);
	ClassDB::bind_method(D_METHOD("set_position", "position"), &FMOD_3D_ATTRIBUTES::set_position);
	ClassDB::bind_method(D_METHOD("get_position"), &FMOD_3D_ATTRIBUTES::get_position);
	ClassDB::bind_method(D_METHOD("set_velocity", "velocity"), &FMOD_3D_ATTRIBUTES::set_velocity);
	ClassDB::bind_method(D_METHOD("get_velocity"), &FMOD_3D_ATTRIBUTES::get_velocity);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "forward"), "set_forward", "get_forward");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "up"), "set_up", "get_up");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "velocity"), "set_velocity", "get_velocity");
}

void FMOD_3D_ATTRIBUTES::set_position(const Vector3& _position)
{
	this->position = _position;
}

Vector3 FMOD_3D_ATTRIBUTES::get_position() const
{
	return position;
}

void FMOD_3D_ATTRIBUTES::set_velocity(const Vector3& _velocity)
{
	this->velocity = _velocity;
}

Vector3 FMOD_3D_ATTRIBUTES::get_velocity() const
{
	return velocity;
}

void FMOD_3D_ATTRIBUTES::set_forward(const Vector3& _forward)
{
	this->forward = _forward;
}

Vector3 FMOD_3D_ATTRIBUTES::get_forward() const
{
	return forward;
}

void FMOD_3D_ATTRIBUTES::set_up(const Vector3& _up)
{
	this->up = _up;
}

Vector3 FMOD_3D_ATTRIBUTES::get_up() const
{
	return up;
}

void FMOD_3D_ATTRIBUTES::set_3d_attributes( ::FMOD_3D_ATTRIBUTES& attributes)
{
	fmod_vector_to_vector3(attributes.position, position);
	fmod_vector_to_vector3(attributes.velocity, velocity);
	fmod_vector_to_vector3(attributes.forward, forward);
	fmod_vector_to_vector3(attributes.up, up);
}

void FMOD_3D_ATTRIBUTES::get_3d_attributes(::FMOD_3D_ATTRIBUTES& out_attributes) const
{
	vector3_to_fmod_vector(position, out_attributes.position);
	vector3_to_fmod_vector(velocity, out_attributes.velocity);
	vector3_to_fmod_vector(forward, out_attributes.forward);
	vector3_to_fmod_vector(up, out_attributes.up);
}

FMOD_3D_ATTRIBUTES::FMOD_3D_ATTRIBUTES() {
	position = {0.0,0.0,0.0};
	velocity = position;
	forward = {0.0,0.0,-1.0};
	up = {0.0,1.0,0.0};
}

void FMOD_STUDIO_BUFFER_INFO::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_currentusage", "currentusage"), &FMOD_STUDIO_BUFFER_INFO::set_currentusage);
	ClassDB::bind_method(D_METHOD("get_currentusage"), &FMOD_STUDIO_BUFFER_INFO::get_currentusage);
	ClassDB::bind_method(D_METHOD("set_peakusage", "peakusage"), &FMOD_STUDIO_BUFFER_INFO::set_peakusage);
	ClassDB::bind_method(D_METHOD("get_peakusage"), &FMOD_STUDIO_BUFFER_INFO::get_peakusage);
	ClassDB::bind_method(D_METHOD("set_capacity", "capacity"), &FMOD_STUDIO_BUFFER_INFO::set_capacity);
	ClassDB::bind_method(D_METHOD("get_capacity"), &FMOD_STUDIO_BUFFER_INFO::get_capacity);
	ClassDB::bind_method(D_METHOD("set_stallcount", "stallcount"), &FMOD_STUDIO_BUFFER_INFO::set_stallcount);
	ClassDB::bind_method(D_METHOD("get_stallcount"), &FMOD_STUDIO_BUFFER_INFO::get_stallcount);
	ClassDB::bind_method(D_METHOD("set_stalltime", "stalltime"), &FMOD_STUDIO_BUFFER_INFO::set_stalltime);
	ClassDB::bind_method(D_METHOD("get_stalltime"), &FMOD_STUDIO_BUFFER_INFO::get_stalltime);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "currentusage"), "set_currentusage", "get_currentusage");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "peakusage"), "set_peakusage", "get_peakusage");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "capacity"), "set_capacity", "get_capacity");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stallcount"), "set_stallcount", "get_stallcount");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "stalltime"), "set_stalltime", "get_stalltime");
}

void FMOD_STUDIO_BUFFER_INFO::set_currentusage(int _currentusage)
{
	this->currentusage = _currentusage;
}

int FMOD_STUDIO_BUFFER_INFO::get_currentusage() const
{
	return currentusage;
}

void FMOD_STUDIO_BUFFER_INFO::set_peakusage(int _peakusage)
{
	this->peakusage = _peakusage;
}

int FMOD_STUDIO_BUFFER_INFO::get_peakusage() const
{
	return peakusage;
}

void FMOD_STUDIO_BUFFER_INFO::set_capacity(int _capacity)
{
	this->capacity = _capacity;
}

int FMOD_STUDIO_BUFFER_INFO::get_capacity() const
{
	return capacity;
}

void FMOD_STUDIO_BUFFER_INFO::set_stallcount(int _stallcount)
{
	this->stallcount = _stallcount;
}

int FMOD_STUDIO_BUFFER_INFO::get_stallcount() const
{
	return stallcount;
}

void FMOD_STUDIO_BUFFER_INFO::set_stalltime(float _stalltime)
{
	this->stalltime = _stalltime;
}

float FMOD_STUDIO_BUFFER_INFO::get_stalltime() const
{
	return stalltime;
}

void FMOD_STUDIO_BUFFER_INFO::set_buffer_info(const ::FMOD_STUDIO_BUFFER_INFO& buffer_info)
{
	currentusage = buffer_info.currentusage;
	peakusage = buffer_info.peakusage;
	capacity = buffer_info.capacity;
	stallcount = buffer_info.stallcount;
	stalltime = buffer_info.stalltime;
}

void FMOD_STUDIO_BUFFER_INFO::get_buffer_info(::FMOD_STUDIO_BUFFER_INFO& out_buffer_info) const
{
	out_buffer_info.currentusage = currentusage;
	out_buffer_info.peakusage = peakusage;
	out_buffer_info.capacity = capacity;
	out_buffer_info.stallcount = stallcount;
	out_buffer_info.stalltime = stalltime;
}

void FMOD_STUDIO_BUFFER_USAGE::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_studio_command_queue", "studio_command_queue"),
			&FMOD_STUDIO_BUFFER_USAGE::set_studio_command_queue);
	ClassDB::bind_method(D_METHOD("get_studio_command_queue"), &FMOD_STUDIO_BUFFER_USAGE::get_studio_command_queue);
	ClassDB::bind_method(D_METHOD("set_studio_handle", "studio_handle"), &FMOD_STUDIO_BUFFER_USAGE::set_studio_handle);
	ClassDB::bind_method(D_METHOD("get_studio_handle"), &FMOD_STUDIO_BUFFER_USAGE::get_studio_handle);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "studio_command_queue"), "set_studio_command_queue",
			"get_studio_command_queue");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "studio_handle"), "set_studio_handle", "get_studio_handle");
}

void FMOD_STUDIO_BUFFER_USAGE::set_studio_command_queue(const Ref<FMOD_STUDIO_BUFFER_INFO>& _studiocommandqueue)
{
	this->studiocommandqueue = _studiocommandqueue;
}

Ref<FMOD_STUDIO_BUFFER_INFO> FMOD_STUDIO_BUFFER_USAGE::get_studio_command_queue() const
{
	return studiocommandqueue;
}

void FMOD_STUDIO_BUFFER_USAGE::set_studio_handle(const Ref<FMOD_STUDIO_BUFFER_INFO>& _studiohandle)
{
	this->studiohandle = _studiohandle;
}

Ref<FMOD_STUDIO_BUFFER_INFO> FMOD_STUDIO_BUFFER_USAGE::get_studio_handle() const
{
	return studiohandle;
}

void FMOD_STUDIO_BUFFER_USAGE::set_buffer_usage(const ::FMOD_STUDIO_BUFFER_USAGE& buffer_usage)
{
	studiocommandqueue.instantiate();
	studiocommandqueue->set_buffer_info(buffer_usage.studiocommandqueue);
	studiohandle.instantiate();
	studiohandle->set_buffer_info(buffer_usage.studiohandle);
}

void FMOD_STUDIO_BUFFER_USAGE::get_buffer_usage(::FMOD_STUDIO_BUFFER_USAGE& out_buffer_usage) const
{
	studiocommandqueue->get_buffer_info(out_buffer_usage.studiocommandqueue);
	studiohandle->get_buffer_info(out_buffer_usage.studiohandle);
}

void FMOD_STUDIO_CPU_USAGE::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_update", "update"), &FMOD_STUDIO_CPU_USAGE::set_update);
	ClassDB::bind_method(D_METHOD("get_update"), &FMOD_STUDIO_CPU_USAGE::get_update);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "update"), "set_update", "get_update");
}

void FMOD_STUDIO_CPU_USAGE::set_update(float _update)
{
	this->update = _update;
}

float FMOD_STUDIO_CPU_USAGE::get_update() const
{
	return update;
}

void FMOD_STUDIO_CPU_USAGE::set_cpu_usage(const ::FMOD_STUDIO_CPU_USAGE& _cpu_usage)
{
	this->update = _cpu_usage.update;
}

void FMOD_STUDIO_CPU_USAGE::get_cpu_usage(::FMOD_STUDIO_CPU_USAGE& out_cpu_usage) const
{
	out_cpu_usage.update = this->update;
}

void FMOD_CPU_USAGE::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_dsp", "dsp"), &FMOD_CPU_USAGE::set_dsp);
	ClassDB::bind_method(D_METHOD("get_dsp"), &FMOD_CPU_USAGE::get_dsp);
	ClassDB::bind_method(D_METHOD("set_geometry", "geometry"), &FMOD_CPU_USAGE::set_geometry);
	ClassDB::bind_method(D_METHOD("get_geometry"), &FMOD_CPU_USAGE::get_geometry);
	ClassDB::bind_method(D_METHOD("set_update", "update"), &FMOD_CPU_USAGE::set_update);
	ClassDB::bind_method(D_METHOD("get_update"), &FMOD_CPU_USAGE::get_update);
	ClassDB::bind_method(D_METHOD("set_convolution_1", "convolution_1"), &FMOD_CPU_USAGE::set_convolution_1);
	ClassDB::bind_method(D_METHOD("get_convolution_1"), &FMOD_CPU_USAGE::get_convolution_1);
	ClassDB::bind_method(D_METHOD("set_convolution_2", "convolution_2"), &FMOD_CPU_USAGE::set_convolution_2);
	ClassDB::bind_method(D_METHOD("get_convolution_2"), &FMOD_CPU_USAGE::get_convolution_2);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dsp"), "set_dsp", "get_dsp");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "geometry"), "set_geometry", "get_geometry");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "update"), "set_update", "get_update");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "convolution_1"), "set_convolution_1", "get_convolution_1");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "convolution_2"), "set_convolution_2", "get_convolution_2");
}

void FMOD_CPU_USAGE::set_dsp(float _dsp)
{
	this->dsp = _dsp;
}

float FMOD_CPU_USAGE::get_dsp() const
{
	return dsp;
}

void FMOD_CPU_USAGE::set_stream(float _stream)
{
	this->stream = _stream;
}

float FMOD_CPU_USAGE::get_stream() const
{
	return stream;
}

void FMOD_CPU_USAGE::set_geometry(float _geometry)
{
	this->geometry = _geometry;
}

float FMOD_CPU_USAGE::get_geometry() const
{
	return geometry;
}

void FMOD_CPU_USAGE::set_update(float _update)
{
	this->update = _update;
}

float FMOD_CPU_USAGE::get_update() const
{
	return update;
}

void FMOD_CPU_USAGE::set_convolution_1(float _convolution1)
{
	this->convolution1 = _convolution1;
}

float FMOD_CPU_USAGE::get_convolution_1() const
{
	return convolution1;
}

void FMOD_CPU_USAGE::set_convolution_2(float _convolution2)
{
	this->convolution2 = _convolution2;
}

float FMOD_CPU_USAGE::get_convolution_2() const
{
	return convolution2;
}

void FMOD_CPU_USAGE::set_cpu_usage(const ::FMOD_CPU_USAGE& cpu_usage)
{
	dsp = cpu_usage.dsp;
	stream = cpu_usage.stream;
	geometry = cpu_usage.geometry;
	update = cpu_usage.update;
	convolution1 = cpu_usage.convolution1;
	convolution2 = cpu_usage.convolution2;
}

void FMOD_CPU_USAGE::get_cpu_usage(::FMOD_CPU_USAGE& out_cpu_usage) const
{
	out_cpu_usage.dsp = dsp;
	out_cpu_usage.stream = stream;
	out_cpu_usage.geometry = geometry;
	out_cpu_usage.update = update;
	out_cpu_usage.convolution1 = convolution1;
	out_cpu_usage.convolution2 = convolution2;
}

void FMOD_STUDIO_MEMORY_USAGE::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_exclusive", "exclusive"), &FMOD_STUDIO_MEMORY_USAGE::set_exclusive);
	ClassDB::bind_method(D_METHOD("get_exclusive"), &FMOD_STUDIO_MEMORY_USAGE::get_exclusive);
	ClassDB::bind_method(D_METHOD("set_inclusive", "inclusive"), &FMOD_STUDIO_MEMORY_USAGE::set_inclusive);
	ClassDB::bind_method(D_METHOD("get_inclusive"), &FMOD_STUDIO_MEMORY_USAGE::get_inclusive);
	ClassDB::bind_method(D_METHOD("set_sampledata", "sample_data"), &FMOD_STUDIO_MEMORY_USAGE::set_sampledata);
	ClassDB::bind_method(D_METHOD("get_sampledata"), &FMOD_STUDIO_MEMORY_USAGE::get_sampledata);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "exclusive"), "set_exclusive", "get_exclusive");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "inclusive"), "set_inclusive", "get_inclusive");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sample_data"), "set_sampledata", "get_sampledata");
}

void FMOD_STUDIO_MEMORY_USAGE::set_exclusive(int _exclusive)
{
	this->exclusive = _exclusive;
}

int FMOD_STUDIO_MEMORY_USAGE::get_exclusive() const
{
	return exclusive;
}

void FMOD_STUDIO_MEMORY_USAGE::set_inclusive(int _inclusive)
{
	this->inclusive = _inclusive;
}

int FMOD_STUDIO_MEMORY_USAGE::get_inclusive() const
{
	return inclusive;
}

void FMOD_STUDIO_MEMORY_USAGE::set_sampledata(int _sampledata)
{
	this->sampledata = _sampledata;
}

int FMOD_STUDIO_MEMORY_USAGE::get_sampledata() const
{
	return sampledata;
}

void FMOD_STUDIO_MEMORY_USAGE::set_memory_usage(const ::FMOD_STUDIO_MEMORY_USAGE& memory_usage)
{
	exclusive = memory_usage.exclusive;
	inclusive = memory_usage.inclusive;
	sampledata = memory_usage.sampledata;
}

void FMOD_STUDIO_MEMORY_USAGE::get_memory_usage(::FMOD_STUDIO_MEMORY_USAGE& out_memory_usage) const
{
	out_memory_usage.exclusive = exclusive;
	out_memory_usage.inclusive = inclusive;
	out_memory_usage.sampledata = sampledata;
}

} // namespace FmodTypes
