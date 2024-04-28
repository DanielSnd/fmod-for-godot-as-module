#config.py

AVAILABLE_PLATFORMS = ["windows", "android", "macos", "linuxbsd","web"]

def can_build(env, platform):
    return platform in AVAILABLE_PLATFORMS

def configure(env):
    CORE_LIBRARY_NAME = "fmod"
    STUDIO_LIBRARY_NAME = "fmodstudio"

    lfix = ""
    debug = False
    if env["target"] == "template_debug" or env["target"] == "editor":
        lfix = "L"
        debug = True

    if env["platform"] == "windows":
        env.Append(CPPPATH=['#../modules/fmodgodot/lib/core/inc/', '#../modules/fmodgodot/lib/studio/inc/'])
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
        env.Append(CPPPATH=['#../modules/fmodgodot/lib/core/inc/', '#../modules/fmodgodot/lib/studio/inc/'])
        env.Append(LIBPATH=["#../modules/fmodgodot/lib/core/lib/", "#../modules/fmodgodot/lib/studio/lib/"])
        env.Append(LIBS=["fmod", "fmodstudio"])
        env.Append(CPPDEFINES=["FMOD_OSX"])
    elif env["platform"] == "android":
        libfmod = 'libfmod%s' % lfix
        libfmodstudio = 'libfmodstudio%s' % lfix
        fmod_info_table = {
            "armv7": "armeabi-v7a/",
            "arm64": "arm64-v8a/",
            "x86": "x86/",
            "x86_64": "x86_64/"
        }
        arch_dir = fmod_info_table[env["arch"]]
        env.Append(CPPPATH=['#../modules/fmodgodot/lib/core/android/inc/', '#../modules/fmodgodot/lib/studio/android/inc/'])
        env.Append(LIBPATH=['#../modules/fmodgodot/lib/core/android/lib/'+ arch_dir, '#../modules/fmodgodot/lib/studio/android/lib/' + arch_dir])
        env.Append(LIBS=[libfmod, libfmodstudio])
        env.Append(CPPDEFINES=["FMOD_ANDROID"])
    elif env["platform"] == "linuxbsd":
        env.Append(CPPPATH=['#../modules/fmodgodot/lib/core/inc/', '#../modules/fmodgodot/lib/studio/inc/'])
        env.Append(LIBPATH=["#../modules/fmodgodot/lib/core/lib/x86_64/"])
        env.Append(LIBPATH=["#../modules/fmodgodot/lib/studio/lib/x86_64/"])
        env.Append(LIBS=["libfmod","libfmodstudio"])
        env.Append(RPATH=["\$$ORIGIN:."])
        env.Append(CPPDEFINES=["FMOD_LINUX"])
    elif env["platform"] == "web":
        env.Append(CPPDEFINES=["FMOD_WEB"])
        env.Append(CPPPATH=['#../modules/fmodgodot/lib/core/inc/', '#../modules/fmodgodot/lib/studio/inc/'])
        env.AddJSLibraries(["#../modules/fmodgodot/lib/core/lib/upstream/js/fmod_reduced.js","#../modules/fmodgodot/lib/studio/lib/upstream/js/fmodstudio.js"])
        env.AddJSExterns(["#../modules/fmodgodot/lib/core/lib/upstream/js/fmod_reduced.js.mem","#../modules/fmodgodot/lib/studio/lib/upstream/js/fmodstudio.js.mem"])