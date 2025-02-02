#include "Application.h"

#include <iostream>
#include <format>
#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "Debug.h"
#include "TextureScene.h"
#include "ClearColorScene.h"
#include "CubeScene.h"
#include "CircleScene.h"
#include "SkyboxScene.h"

namespace GL {
	Application::Application(const int width, const int height, const std::string &title)
		: title(title),
		  width(width),
		  height(height),
		  aspectRatio(static_cast<float>(width) / static_cast<float>(height)),
		  window(nullptr), camera(), scene(nullptr) {
		InitGLFW();
		CreateWindow();
		InitGLAD();
		ConfigureOpenGL();
		InitImGui();
		InitCamera();
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

	void Application::InitCamera() {
		camera.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
		camera.SetOrientation(glm::vec3(0.0f, 0.0f, 1.0f));
		camera.SetUp(glm::vec3(0.0f, 1.0f, 0.0f));
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
					InitCamera();
				}
			}
		}
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

			camera.Compute(45.f, aspectRatio, 0.1f, 100.0f);

			if (scene) {
				scene->OnImGuiRender();
				scene->OnUpdate(deltaTime);
				scene->OnRender(camera);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			HandleEvents();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void Application::HandleEvents() {
		// Key events
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		if (scene && scene->isUsingCamera) {
			CameraEvents();
		}

		// Resize event
		int newWidth, newHeight;
		glfwGetWindowSize(window, &newWidth, &newHeight);
		if (newWidth != width || newHeight != height) {
			glViewport(0, 0, newWidth, newHeight);

			width = newWidth;
			height = newHeight;
			aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		}
	}

	void Application::CameraEvents() {
		// Handles key inputs
		glm::vec3 &position = camera.GetPosition();
		glm::vec3 &orientation = camera.GetOrientation();
		const glm::vec3 &up = camera.GetUp();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += speed * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position += speed * -glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position += speed * -orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			position += speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			position += speed * -up;
		}

		// Adjust speed
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			speed = 0.4f;
		} else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			speed = 0.1f;
		}

		// Check if ImGui is interacting
		if (ImGui::GetIO().WantCaptureMouse) {
			// Do not process camera inputs if ImGui is active
			return;
		}

		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick) {
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor
			float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

			// Calculate upcoming vertical change in the orientation
			glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX),
			                                       glm::normalize(glm::cross(orientation, up)));

			// Ensure the vertical orientation stays within legal bounds
			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				orientation = newOrientation;
			}

			// Rotate the orientation left and right
			orientation = glm::rotate(orientation, glm::radians(-rotY), up);

			// Center the cursor on the screen
			glfwSetCursorPos(window, (width / 2), (height / 2));
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			// Reset first click state
			firstClick = true;
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
