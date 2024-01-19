# FMOD for Godot 4.2+ (Converted from GDEXtension to Custom Module)

[![Build](https://github.com/alessandrofama/fmod-for-godot/workflows/Build/badge.svg)](https://github.com/alessandrofama/fmod-for-godot/actions/workflows/build_all.yml) [![Discord](https://img.shields.io/discord/1083520667451920394?label=Discord)](https://discord.gg/XQbvRdQcNn)

Welcome! This repository provides an integration of [FMOD Studio's audio middleware](https://www.fmod.com/) into the [Godot game engine](https://godotengine.org). At the moment, **FMOD version 2.02.17** and **Godot 4.2+ stable** are supported.

<img src="https://alessandrofama.com/wp-content/uploads/sites/3/fmod-for-godot-1920.png" width="720">

## As a module

This fork takes the great work done by Alessandro Fama with his GDExtension and converts it into a Custom Module that you can compile into the engine itself.

One thing to note at this point is that I have only adjusted the **config.py** file for Windows 64-bits, so if you're building for a different platform please go into config.py and adjust it for your platform.

Another thing to note is that when I'm developing my custom modules I have it in a folder called modules outside of the godot folder and I compile it with the scons setting: `custom_modules=../modules` so you either have to do the same or change the path to the fmod libraries on **config.py**, example of how it is right now:

```python
            env.Append(LIBPATH=["#../modules/fmodgodot/lib/core/lib/x64/"])
            env.Append(LIBPATH=["#../modules/fmodgodot/lib/studio/lib/x64/"])
```
One last thing, if you're following Alessandro's [getting started](https://alessandrofama.com/tutorials/fmod/godot/getting-started) guide, the main difference is that there's a "fmod_enabled" setting in the FMOD settings window. After toggling that setting to true and restarting godot the module will be fully enabled and the other settings will appear.

About the fmod libraries, it's important to point out that the FMOD libraries in this project and FMOD itself is not free and has different license schemes depending on the type and budget of your project.

You can find out more about FMOD licensing [here](https://www.fmod.com/licensing). Please make sure to obtain a license for your commercial game.

## Features

* Use the FMOD Studio API on different platforms (Windows, ~macOS, Linux, iOS and Android~) with a Custom Module that seamlessly integrates with Godot and GDScript.
* Modify and build the library for any target platform with ease using SCons, a flexible and cross-platform software construction tool.
* Streamlined audio authoring workflow with FMOD Studio Live Update, which lets you sync your audio project with your game in the editor or in a build. Experiment and iterate faster without reloading or recompiling your game.
* Custom blocking I/O implementation that uses Godot's `FileAccess` API. This ensures compatibility across different platforms.
* Custom FMOD nodes, such as StudioEventEmitter3D, StudioEventEmitter2D, StudioBankLoader, StudioListener3D, StudioListener2D, StudioParameterTrigger and StudioGlobalParameterTrigger. Create an immersive audio experience for players with little code.
* Event **Timeline Marker** and **Timeline Beat** callback support to easily synchronize your game with your audio's logic. You can use these callbacks to trigger animations or gameplay events based on the timing of your audio events.
* Generate unique identifiers (GUIDs) for GDScript to maintain organization and consistency in your project. GUIDs will help you reference FMOD assets without hard-coding paths or names. 
* Search and preview Events in the Godot editor with the **FMOD Project Browser**. This handy tool lets you browse through all the Events in your project and play them back directly in the editor.
* Customize **FMOD settings** for each platform in the Godot Project Settings. You can adjust settings such as **sample rate**, **speaker mode**, **real and virtual channels**, **DSP buffer size** and more to optimize performance and quality for each platform.
* Studio API wrapper unit tests ensuring a reliable and stable integration.
* Custom performance monitors to track the performance of FMOD in the editor.

## Getting started

If you are a game developer that would like to integrate FMOD into your Godot project, ~go to the [releases](https://github.com/alessandrofama/fmod-for-godot/releases) page to download the addon~ compile this module into the engine and read the [getting started](https://alessandrofama.com/tutorials/fmod/godot/getting-started) guide.

If you would like to modify the code of the FMOD addon or build it yourself, visit the short [Building](https://alessandrofama.com/tutorials/fmod/godot/building) tutorial for build instructions.

## Tutorials

Extensive tutorials for the integration, including custom nodes usage and code examples can be found on the [tutorials](https://alessandrofama.com/tutorials/fmod/godot/) section of my website. 

## Known issues

Known issues are being logged into the [issues page](https://github.com/alessandrofama/fmod-for-godot/issues) of this repo. Please check this page first, then log a new issue if you haven't found it listed.

## Contributing

Any contribution is welcome. Please send pull-requests with fixes or useful additions!

## License

The integration files, code and scripts in this repository are released under the [MIT license](https://github.com/alessandrofama/fmod-for-godot/blob/master/LICENSE).

While this project is licensed under MIT, FMOD itself is not free and has different license schemes depending on the type and budget of your project.

You can find out more about FMOD licensing [here](https://www.fmod.com/licensing). Please make sure to obtain a license for your commercial game.
