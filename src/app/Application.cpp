#include "Application.h"

#include <iostream>
#include <format>
#include <functional>

#include "glad/glad.h" // Do not remove
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Debug.h"
#include "TextureScene.h"
#include "ClearColorScene.h"
#include "CubeScene.h"
#include "CircleScene.h"
#include "SkyboxScene.h"

namespace GL {
	Application::Application(const int width, const int height, std::string &&title)
		: title(title),
		  width(width),
		  height(height),
		  window(nullptr),
		  scene(nullptr) {
		InitGLFW();
		CreateWindow();
		InitGLAD();
		ConfigureOpenGL();
		InitImGui();
	}

	void Application::InitGLFW() {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW.");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		glfwSetErrorCallback([](const int error, const char *description) {
			std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
		});
	}

	void Application::CreateWindow() {
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window.");
		}

		glfwSetWindowUserPointer(window, this);

		glfwSetWindowSizeCallback(window, [](GLFWwindow *window, const int width, const int height) {
			if (auto *_this = static_cast<Application *>(glfwGetWindowUserPointer(window))) {
				_this->HandleResize(width, height);
			}
		});

		glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
			if (auto *_this = static_cast<Application *>(glfwGetWindowUserPointer(window))) {
				_this->HandleKey(key, scancode, action, mods);
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
			if (auto *_this = static_cast<Application *>(glfwGetWindowUserPointer(window))) {
				double newX, newY;
				glfwGetCursorPos(window, &newX, &newY);
				_this->HandleMouse(_this->lastX - newX, _this->lastY - newY, button, action, mods);
				_this->lastX = newX;
				_this->lastY = newY;
			}
		});

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // V-Sync
	}

	void Application::InitGLAD() {
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			glfwTerminate();
			throw std::runtime_error("Failed to initialize GLAD.");
		}
	}

	void Application::ConfigureOpenGL() {
		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(Debug::PrintGlDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Application::InitImGui() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 450 core");
		ImGui::StyleColorsClassic();
	}

	void Application::ImGuiMenu() {
		static const std::unordered_map<std::string, std::function<Scene*()> > sceneRegistry = {
			{"Texture", [] { return new TextureScene(); }},
			{"ClearColor", [] { return new ClearColorScene(); }},
			{"Cube", [] { return new CubeScene(); }},
			{"Circle", [] { return new CircleScene(); }},
			{"Skybox", [] { return new SkyboxScene(); }}
		};

		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("Width: %i", width);
		ImGui::Text("Height: %i", height);
		ImGui::Text("AR: %.1f", (float) width / (float) height);

		if (scene) {
			if (ImGui::Button("<-")) {
				delete scene;
				scene = nullptr;
			}
		} else {
			for (const auto &[name, factory]: sceneRegistry) {
				if (ImGui::Button(name.c_str())) {
					scene = factory();
					title = name;
					glfwSetWindowTitle(window, title.c_str());
				}
			}
		}
	}

	void Application::HandleResize(const int newWidth, const int newHeight) {
		width = newWidth;
		height = newHeight;
		glViewport(0, 0, width, height);
	}

	void Application::HandleKey(int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}

	void Application::HandleMouse(double xOffset, double yOffset, int button, int action, int mods) {
	}

	void Application::mainLoop() {
		double currentFrame = glfwGetTime();
		double lastFrame = currentFrame;
		double deltaTime;

		while (!glfwWindowShouldClose(window)) {
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glClearColor(Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGuiMenu();


			if (scene) {
				scene->OnImGuiRender();
				scene->OnUpdate(window, deltaTime);
				scene->OnRender();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	Application::~Application() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete scene;

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
