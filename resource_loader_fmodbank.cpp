//
// Created by Daniel on 2024-02-20.
//

#include "resource_loader_fmodbank.h"

#include "resource_fmodbank.h"


Ref<Resource> ResourceFormatLoaderFmodBank::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, CacheMode p_cache_mode) {
	Ref<FMODBank> bank = memnew(FMODBank);
	Error err = bank->load(p_path);
	if (r_error != nullptr) {
		*r_error = err;
	}

	return bank;
}

void ResourceFormatLoaderFmodBank::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("bank");
}

bool ResourceFormatLoaderFmodBank::handles_type(const String &p_type) const {
	return (p_type == "FMODBank");
}

String ResourceFormatLoaderFmodBank::get_resource_type(const String &p_path) const {
	if (p_path.get_extension().to_lower() == "bank") {
		return "FMODBank";
	}
	return "";
}