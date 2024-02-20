//
// Created by Daniel on 2024-02-20.
//

#ifndef RESOURCE_FMODBANK_H
#define RESOURCE_FMODBANK_H

#include "core/io/resource.h"
#include "core/config/engine.h"
#include "core/io/file_access.h"

class FMODBank : public Resource {
    GDCLASS(FMODBank, Resource);

protected:
    static void _bind_methods();

public:
	Error load(const String &path);

    Vector<uint8_t> buffer;
    int length;
    int get_length() {return length;}
    void set_length(int val) {}

    FMODBank();
    ~FMODBank();
};

#endif //RESOURCE_FMODBANK_H
