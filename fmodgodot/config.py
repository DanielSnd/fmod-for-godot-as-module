#config.py

AVAILABLE_PLATFORMS = ["windows", "macos", "linuxbsd"]

def can_build(env, platform):
    return platform in AVAILABLE_PLATFORMS

def configure(env):
    CORE_LIBRARY_NAME = "fmod"
    STUDIO_LIBRARY_NAME = "fmodstudio"
    if env["platform"] == "windows":
        if env["arch"]=="x86":
            env.Append(LIBPATH=["#../modules/fmodgodot/lib/core/lib/x86/"])
            env.Append(LIBPATH=["#../modules/fmodgodot/lib/studio/lib/x86/"])
            #env.Append(LINKFLAGS=[CORE_LIBRARY_NAME + ".dll", STUDIO_LIBRARY_NAME + ".dll"])
            #env.Append(LINKFLAGS=[CORE_LIBRARY_NAME + "_vc.lib", STUDIO_LIBRARY_NAME + "_vc.lib"])
            env.Append(LIBS=["fmod_vc", "fmodstudio_vc"])
        else: # 64 bit
            env.Append(LIBPATH=["#../modules/fmodgodot/lib/core/lib/x64/"])
            env.Append(LIBPATH=["#../modules/fmodgodot/lib/studio/lib/x64/"])
            env.Append(LINKFLAGS=["fmod_vc.lib", "fmodstudio_vc.lib"])
            env.Append(LIBS=["fmod_vc", "fmodstudio_vc"])
        env.Append(CPPDEFINES=["FMOD_WIN"])
    elif env["platform"] == "macos":
        env.Append(
            LIBPATH=["#../modules/fmodgodot/lib/core/lib/", "#../modules/fmodgodot/lib/studio/lib/"])
        env.Append(LIBS=[CORE_LIBRARY_NAME, STUDIO_LIBRARY_NAME])
        env.Append(CPPDEFINES=["FMOD_OSX"])
    elif env["platform"] == "linuxbsd":
        env.Append(
            LIBPATH=["lib/core/lib/x86_64/", "lib/studio/lib/x86_64/"])
        env.Append(LIBS=["lib" + CORE_LIBRARY_NAME, "lib" + STUDIO_LIBRARY_NAME])
        env.Append(RPATH=["\$$ORIGIN:."])
        env.Append(CPPDEFINES=["FMOD_LINUX"])