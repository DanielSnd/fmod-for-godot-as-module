//
// Created by Daniel on 2024-02-20.
//

#include "resource_fmodbank.h"


void FMODBank::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_length", "len"), &FMODBank::set_length);
    ClassDB::bind_method(D_METHOD("get_length"), &FMODBank::get_length);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "length"), "set_length", "get_length");
}

Error FMODBank::load(const String &path) {
    set_path(path);
    // Open bank file
    Error file_access_err;
    Ref<FileAccess> file = FileAccess::open(get_path(), FileAccess::READ, &file_access_err);

    if (file_access_err != Error::OK) {
        return file_access_err;
    }

    length = file->get_length();
    buffer = file->get_buffer(length);

    return Error::OK;
}

FMODBank::FMODBank() {
    length = -1;
}

FMODBank::~FMODBank() {
    if (length != -1) {
        length = -1;
        buffer.clear();
    }
}