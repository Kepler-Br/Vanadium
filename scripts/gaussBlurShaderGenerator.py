import math
import argparse


def gauss_kernel_formula(x: float, y: float):
    sigma = 7.0
    first_part = 1/(2*math.pi*pow(sigma, 2))
    second_part = math.exp(-(pow(x, 2) + pow(y, 2))/(2*pow(sigma, 2)))
    return first_part*second_part


def generate_gauss_kernel(width: int, height: int, ver: str, tabulation_count: int):
    tabulation = " " * tabulation_count

    output = f"{ver}\n\n"
    output += f"layout(location = 0) out vec4 outColor;\n"
    output += f"uniform sampler2D inputTexture;\n"
    output += f"uniform vec2 screenResolution;\n"
    output += f"in vec2 uv;\n"
    output += "\n"

    output += "void main()\n{\n"
    output += tabulation + f"outColor = vec4(0.0f);\n"
    output += tabulation + f"float deltaX = 1.0f/screenResolution.x;\n"
    output += tabulation + f"float deltaY = 1.0f/screenResolution.y;\n"

    center_x = int(width/2)
    center_y = int(height/2)
    for x in range(width):
        for y in range(height):
            value = gauss_kernel_formula(x - center_x, y - center_y)
            output += tabulation + f"outColor += texture(inputTexture, uv + vec2(deltaX * {x - center_x}, deltaY * {y - center_y})) * {value}f;\n"
            pass
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

    # print(args)
    kernel_text = generate_gauss_kernel(width, height, ver, tabulation)
    print(kernel_text)


if __name__ == "__main__":
    main()
