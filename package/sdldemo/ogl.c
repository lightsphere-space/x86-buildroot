#include <SDL.h>
#include "SDL_image.h"
#include "stdio.h"
#include <SDL_opengles2.h>
#include "glad.h"

extern SDL_Window* tmp_displayWindow;
SDL_GLContext oglContext;
GLuint VAO, VBO, EBO, texture, shaderProgram;

void Test();
void InitGL();
void LoadTexture();

GLuint PrepareTexture(SDL_Surface* Surface);
GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource);
void SetupQuad(GLuint* VAO, GLuint* VBO, GLuint* EBO);
void Render(GLuint program, GLuint VAO, GLuint texture);

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

#define DEBUG // no printing
//#define DEBUG printf

void CheckError()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		DEBUG("OpenGL Error: 0x%x\n", error);
	}
}

void CloseGL()
{
	SDL_GL_DeleteContext(oglContext);
}

void InitGL()
{
	// Set OpenGL ES version (major 3, minor 0 for GLES 3.0)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	tmp_displayWindow = SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);

	// Create OpenGL context
	oglContext = SDL_GL_CreateContext(tmp_displayWindow);
	if (!oglContext)
	{
		SDL_DestroyWindow(tmp_displayWindow);
		SDL_Quit();
		return -1;
	}

	if (!gladLoadGLES2Loader(SDL_GL_GetProcAddress))
	{
		DEBUG("Failed to initialize GLAD.\n");
		return -1;
	}

	int majorVersion, minorVersion;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion);
	GLenum error = glGetError();
	// No error reported, major/minor version match - 3.0

	SDL_GL_SetSwapInterval(1);

	// Initialize OpenGL (set clear color, enable depth testing, etc.)
	glClearColor(0.0f, 0.3f, 0.8f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Enable alpha blending for transparent sprites

	SDL_GLContext currentContext = SDL_GL_GetCurrentContext();
	if (currentContext != oglContext) {
		DEBUG("ERROR: Context is not current as expected.\n");
	}

	char* renderer = glGetString(GL_RENDERER);
	char* glVersion = glGetString(GL_VERSION);

	if (glVersion)
		DEBUG("glVersion: %s\n", glVersion);
	else
		DEBUG("glGetString(GL_VERSION) returned NULL\n");

	if (renderer)
		DEBUG("Renderer: %s\n", renderer);
	else
		DEBUG("glGetString(GL_RENDERER) returned NULL\n");

	shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	GLuint textureLoc = glGetUniformLocation(shaderProgram, "uTexture");
	if (textureLoc == -1)
		DEBUG("Failed to find uniform 'uTexture'.\n");
	else
	{
		glUseProgram(shaderProgram);
		glUniform1i(textureLoc, 0); // Bind to texture unit 0
	}

	SetupQuad(&VAO, &VBO, &EBO);
}

void ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void SwapWindow()
{
	SDL_GL_SwapWindow(tmp_displayWindow);
}

void LoadTexture()
{
	// Called after InitGL()
	SDL_Surface* surface = IMG_Load("tex.png");

	if (!surface)
	{
		DEBUG("Error loading image: %s\n", SDL_GetError());
		return 0;
	}

	texture = PrepareTexture(surface);

	SDL_FreeSurface(surface);
}

GLuint PrepareTexture(SDL_Surface *Surface)
{
	GLenum format = (Surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

	// Generate OpenGL texture
	GLuint texture;
	glGenTextures(1, &texture);

	if (texture == 0)
	{
		DEBUG("Error generating texture.\n");
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	CheckError();

	// Load texture data into OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, Surface->w, Surface->h,
		0, format, GL_UNSIGNED_BYTE, Surface->pixels);
	CheckError();

	// Set texture parameters (filtering, wrapping)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	CheckError();

	return texture;
}

GLuint CompileShader(const char* source, GLenum type)
{
	if (type == GL_VERTEX_SHADER) DEBUG("Compiling vertex shader\n");
	else if (type == GL_FRAGMENT_SHADER) DEBUG("Compiling fragment shader\n");
	else DEBUG("Compiling ??? - %d\n", type);

	GLuint shader = glCreateShader(type);

	if (shader == 0)
	{
		GLenum error = glGetError();
		DEBUG("glCreateShader failed. OpenGL error: 0x%x\n", error);
		return 0;
	}

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	if (success == GL_FALSE)
	{
		char infoLog[512];
		GLenum err = glGetError();
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		GLint worked = glIsShader(shader);
		DEBUG(stderr, "Shader compilation failed: %s\n", infoLog);
	}

	return shader;
}

GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource)
{
	GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	GLint success;

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		DEBUG("Shader Program Linking Failed: %s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void Test()
{
	Render(shaderProgram, VAO, texture);
}

// Quad vertices (x, y, u, v)
const float quadVertices[] = {
	// Positions   // TexCoords
	-1.0f, -1.0f,  0.0f, 1.0f, // Bottom-left
	 1.0f, -1.0f,  1.0f, 1.0f, // Bottom-right
	-1.0f,  1.0f,  0.0f, 0.0f, // Top-left
	 1.0f,  1.0f,  1.0f, 0.0f  // Top-right
};

const unsigned int indices[] = {
	0, 1, 2, // First triangle
	1, 3, 2  // Second triangle
};

void SetupQuad(GLuint* VAO, GLuint* VBO, GLuint* EBO) {
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture coordinate attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Render(GLuint program, GLuint VAO, GLuint texture) {
	glUseProgram(program);

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "uTexture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}