#version 330 core
out vec4 FragColor;

uniform int state;

void main()
{
	if (state == 0) {
		FragColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);
	}
	else if (state == 1) {
		FragColor = vec4(1.0f, 0.7f, 0.3f, 1.0f);
	}
	else if (state == 2) {
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (state == 3) {
		FragColor = vec4(0.75f, 0.1f, 0.1f, 1.0f);
	}
	else if (state == 4) {
		FragColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);
	}
	else {
		FragColor = vec4(0.2f, 0.8f, 0.2f, 1.0f);
	}
}