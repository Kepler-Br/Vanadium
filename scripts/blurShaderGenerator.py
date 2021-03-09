import math
import argparse

def generate_blur_kernel(width: int, height: int, ver: str, tabulation_count: int):
    tabulation = " " * tabulation_count

    output = f"{ver}\n\n"
    output += f"layout(location = 0) out vec4 outColor;\n"
    output += f"uniform sampler2D inputTexture;\n"
    output += f"uniform vec2 screenResolution;\n"
    output += f"in vec2 uv;\n"
    output += "\n"

    output += "void main()\n{\n"
    output += tabulation + f"float deltaX = 1.0f/screenResolution.x;\n"
    output += tabulation + f"float deltaY = 1.0f/screenResolution.y;\n"

    center_x = int(width/2)
    center_y = int(height/2)
    for x in range(width):
        for y in range(height):
            output += tabulation + f"outColor += texture(inputTexture, uv + vec2(deltaX * {x - center_x}, deltaY * {y - center_y}));\n"
    output += tabulation + f"outColor /= {width*height};\n"
    output += "}"
    return output

def main():
    # Create the parser
    my_parser = argparse.ArgumentParser(description='Create Gauss blur kernel for GLSL.')

    my_parser.add_argument("--width",
                           type=int,
                           help="kernel width",
                           default=3)
    my_parser.add_argument("--height",
                           type=int,
                           help="kernel height",
                           default=3)
    my_parser.add_argument("--version",
                           type=str,
                           help="glsl version header",
                           default="#version 330 core")
    my_parser.add_argument("--tabulation",
                           type=int,
                           help="tabulation",
                           default=4)

    args = my_parser.parse_args()

    width = args.width
    height = args.height
    ver = args.version
    tabulation = args.tabulation

    kernel_text = generate_blur_kernel(width, height, ver, tabulation)
    print(kernel_text)


if __name__ == "__main__":
    main()