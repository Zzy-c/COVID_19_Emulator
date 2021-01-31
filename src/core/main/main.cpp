#include "main.h"

using namespace std;

int main()
{
	Init();
	Shader shader("vertexShader.vs", "fragmentShader.fs");
	for (int i = 0; i < total; i++) {
		person[i] = new Person(vector(Random::Range(-400, 400) / (SCR_WIDTH / 2.0), Random::Range(-400, 400) / (SCR_HEIGHT / 2.0)), Person::NORMAL);
		for (int j = 0; j < 360; j += 2) {
			vertices[i * 360 + j] = person[i]->pos.x + (cos(Maths::DegreesToRadians(j)) * radius);
			vertices[i * 360 + j + 1] = person[i]->pos.y + (sin(Maths::DegreesToRadians(j)) * radius);
		}
	}
	person[0]->state = Person::INCUBATION;

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		float curFrame = glfwGetTime();
		deltaTime = curFrame - lastFrame;
		lastFrame = curFrame;
		processInput(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Use();
		glBindVertexArray(VAO);
		for (int i = 0; i < total; i++) {
			for (int j = 0; j < total; j++) {
				if (i != j && person[i]->state != Person::DEATH && person[j]->state != Person::DEATH) {
					if (vector::Distance(person[i]->pos, person[j]->pos) < 2 * radius && person[i]->lastCollider != j) {
						person[i]->lastCollider = j;
						person[j]->lastCollider = i;
						person[i]->direction = glm::vec3(Random::Range(-10, 10) / 1000.0, Random::Range(-10, 10) / 1000.0, 0.0f);
						person[j]->direction = glm::vec3(Random::Range(-10, 10) / 1000.0, Random::Range(-10, 10) / 1000.0, 0.0f);
						if (person[i]->IsInfected() && !person[j]->IsInfected()) {
							if ((person[j]->state != Person::RECOVERY && Random::Percent(infectionRate)) || Random::Percent(relapseRate))
								person[j]->state = Person::INCUBATION;
						}
						else if (!person[i]->IsInfected() && person[j]->IsInfected()) {
							if ((person[i]->state != Person::RECOVERY && Random::Percent(infectionRate)) || Random::Percent(relapseRate))
								person[i]->state = Person::INCUBATION;
						}
					}
				}
			}
			if (person[i]->pos.x < -(1 - radius) || person[i]->pos.x > 1 - radius) {
				person[i]->lastCollider = -1;
				person[i]->direction.x = -person[i]->direction.x;
			}
			if (person[i]->pos.y < -(1 - radius) || person[i]->pos.y > 1 - radius) {
				person[i]->lastCollider = -1;
				person[i]->direction.y = -person[i]->direction.y;
			}
			if (person[i]->state == Person::CONFIRMED || person[i]->state == Person::SERIOUS) {
				if (!Hospital::Full() && !Hospital::isInHospital[i]) {
					Hospital::isInHospital[i] = true;
					Hospital::size++;
				}
			}
			if (person[i]->state == Person::INCUBATION) {
				person[i]->BeConfirmed();
			}
			else if (person[i]->state == Person::CONFIRMED) {
				person[i]->BeSerious();
			}
			else if (person[i]->state == Person::SERIOUS) {
				person[i]->Die();
			}
			if (person[i]->state == Person::DEATH && Hospital::isInHospital[i]) {
				Hospital::isInHospital[i] = false;
				Hospital::size--;
			}
			if (person[i]->state != Person::DEATH && Hospital::isInHospital[i]) {
				person[i]->trans = glm::translate(person[i]->trans, person[i]->direction * (mobility * deltaTime / 5));
				person[i]->pos.x += person[i]->direction.x * (mobility * deltaTime / 5);
				person[i]->pos.y += person[i]->direction.y * (mobility * deltaTime / 5);
			}
			else if (person[i]->state != Person::DEATH) {
				person[i]->trans = glm::translate(person[i]->trans, person[i]->direction * (mobility * deltaTime));
				person[i]->pos.x += person[i]->direction.x * (mobility * deltaTime);
				person[i]->pos.y += person[i]->direction.y * (mobility * deltaTime);
			}
			unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(person[i]->trans));
			unsigned int stateLoc = glGetUniformLocation(shader.ID, "state");
			glUniform1i(stateLoc, (GLint)person[i]->state);
			glDrawArrays(GL_TRIANGLE_FAN, 180 * i, 180);
		}
		Hospital::Run();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
void Init() {
	srand(time(0));
#if 0 配置参数
	cout << "输入 总人数 (推荐 1 ~ 1000 )：";
	cin >> total;
	cout << "输入 医院床位：";
	cin >> Hospital::capacity;
	cout << "输入 人口流动性(推荐 1 ~ 50)：";
	cin >> mobility;
	cout << "输入 圆点半径(推荐 0.01 ~ 0.05)：";
	cin >> radius;
	cout << "输入 感染率(%)：";
	cin >> infectionRate;
	cout << "输入 复得率(%)：";
	cin >> relapseRate;
	cout << "配置完毕" << endl;
	system("pause");
#endif
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "COVID_19_Emulator", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(0);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(0);
	}
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}