#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Person.h"
#include "Shader.h"
#include "Hospital.h"

void Init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
float vertices[2005 * 360];
float lastFrame = 0.0f;
GLFWwindow* window;