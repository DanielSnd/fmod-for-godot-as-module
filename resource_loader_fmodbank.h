//
// Created by Daniel on 2024-02-20.
//

#ifndef RESOURCE_LOADER_FMODBANK_H
#define RESOURCE_LOADER_FMODBANK_H

#include "core/io/file_access.h"
#include "core/io/resource_loader.h"

class ResourceFormatLoaderFmodBank : public ResourceFormatLoader {

public:
    virtual Ref<Resource> load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads = false, float *r_progress = nullptr, CacheMode p_cache_mode = CACHE_MODE_REUSE);
    virtual void get_recognized_extensions(List<String> *p_extensions) const;
    virtual bool handles_type(const String &p_type) const;
    virtual String get_resource_type(const String &p_path) const;
};

#endif //RESOURCE_LOADER_FMODBANK_H
