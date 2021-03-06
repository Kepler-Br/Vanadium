import math

version = "#version 330 core"
textureUniformName = "tex"
outColorName = "color"
screenResolutionUniform = "screenResolution"
uvInName = "UV"
tabulation = " " * 4
kernelWidth = 3


def gauss_kernel_formula(x: float, y: float):
    sigma = 1.0
    first_part = 1/(2*math.pi*pow(sigma, 2))
    second_part = math.exp(-(pow(x, 2) + pow(y, 2))/(2*pow(sigma, 2)))
    return first_part*second_part


def generate_gauss_kernel():
    output = f"{version}\n\n"
    output += f"layout(location = 0) out vec4 {outColorName};\n"
    output += f"uniform sampler2D {textureUniformName};\n"
    output += f"uniform vec2 {screenResolutionUniform};\n"
    output += f"in vec2 {uvInName};\n"
    output += "\n"

    output += "void main()\n{\n"
    output += tabulation + f"float deltaX = 1.0f/{screenResolutionUniform}.x;\n"
    output += tabulation + f"float deltaY = 1.0f/{screenResolutionUniform}.y;\n"

    center_x = int(kernelWidth/2)
    center_y = int(kernelWidth/2)
    for x in range(kernelWidth):
        for y in range(kernelWidth):
            value = gauss_kernel_formula(x - center_x, y - center_y)
            output += tabulation + f"{outColorName} += texture({textureUniformName}, {uvInName} + vec2(deltaX * {x - center_x}, deltaY * {y - center_y})) * {value}f;\n"
            pass
    output += tabulation + f"{outColorName} /= {kernelWidth*kernelWidth};\n"
    output += "}"
    return output


def generate_blur_kernel():
    output = f"{version}\n\n"
    output += f"layout(location = 0) out vec4 {outColorName};\n"
    output += f"uniform sampler2D {textureUniformName};\n"
    output += f"uniform vec2 {screenResolutionUniform};\n"
    output += f"in vec2 {uvInName};\n"
    output += "\n"

    output += "void main()\n{\n"
    output += tabulation + f"float deltaX = 1.0f/{screenResolutionUniform}.x;\n"
    output += tabulation + f"float deltaY = 1.0f/{screenResolutionUniform}.y;\n"

    center_x = int(kernelWidth/2)
    center_y = int(kernelWidth/2)
    for x in range(kernelWidth):
        for y in range(kernelWidth):
            output += tabulation + f"{outColorName} += texture({textureUniformName}, {uvInName} + vec2(deltaX * {x - center_x}, deltaY * {y - center_y}));\n"
            pass
    output += tabulation + f"{outColorName} /= {kernelWidth*kernelWidth};\n"
    output += "}"
    return output


def main():
    print(generate_gauss_kernel())


if __name__ == "__main__":
    main()
