"""Functions used to generate source files during build time

All such functions are invoked in a subprocess on Windows to prevent build flakiness.

"""
import argparse
import os
from io import StringIO


# See also `editor/icons/editor_icons_builders.py`.
def make_fmod_icons_action(target, source):
    dst = target[0]
    svg_icons = source
    print("target:", target)
    print("source:", source)
    icons_string = StringIO()

    for f in svg_icons:
        fname = str(f)

        icons_string.write('\t"')

        with open(fname, "rb") as svgf:
            b = svgf.read(1)
            while len(b) == 1:
                icons_string.write("\\" + str(hex(ord(b)))[1:])
                b = svgf.read(1)

        icons_string.write('"')
        if fname != svg_icons[-1]:
            icons_string.write(",")
        icons_string.write("\n")

    s = StringIO()
    s.write("/* THIS FILE IS GENERATED DO NOT EDIT */\n\n")
    s.write('#include "modules/modules_enabled.gen.h"\n\n')
    s.write("#ifndef _FMOD_ICONS_H\n")
    s.write("#define _FMOD_ICONS_H\n")
    s.write("static const int fmod_icons_count = {};\n\n".format(len(svg_icons)))
    s.write("#ifdef MODULE_SVG_ENABLED\n")
    s.write("static const char *fmod_icons_sources[] = {\n")
    s.write(icons_string.getvalue())
    s.write("};\n")
    s.write("#endif // MODULE_SVG_ENABLED\n\n")
    s.write("static const char *fmod_icons_names[] = {\n")

    index = 0
    for f in svg_icons:
        fname = str(f)

        # Trim the `.svg` extension from the string.
        icon_name = os.path.basename(fname)[:-4]

        s.write('\t"{0}"'.format(icon_name))

        if fname != svg_icons[-1]:
            s.write(",")
        s.write("\n")

        index += 1

    s.write("};\n")

    s.write("#endif\n")

    with open(dst, "w") as f:
        f.write(s.getvalue())

    s.close()
    icons_string.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate source files during build time.")
    parser.add_argument("output_file", help="Output file path (e.g., #fmod_icons.gen.h)")
    parser.add_argument("icons_directory", help="Directory containing SVG icons")

    args = parser.parse_args()

    icons_directory = args.icons_directory
    output_file = args.output_file

    # Call your function with the parsed arguments
    make_fmod_icons_action([output_file], [os.path.join(icons_directory, f) for f in os.listdir(icons_directory)])