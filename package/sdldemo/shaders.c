const char* vertexShaderSource =
    "#version 300 es\n"
    "precision mediump float;\n"
    "layout (location = 0) in vec2 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "\n"
    "out vec2 TexCoord;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "    TexCoord = aTexCoord;\n"
    "}\n"
    "\n";

const char* fragmentShaderSource =
    "#version 300 es\n"
    "precision highp float;\n"
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "\n"
    "uniform sampler2D uTexture;\n"
    "\n"
    "void main() {\n"
    "    FragColor = texture(uTexture, TexCoord);\n"
    "}\n";

