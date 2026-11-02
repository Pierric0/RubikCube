
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GameInterface.h"
#include "TestGlm.h"
#include "TestTriangle.h"
#include "TestCubie.h"
#include "TestCompoundCube.h"
#include "TestKey.h"
#include "TestMaus.h"
#include "TestTexture.h"
#include "TestSound.h"

// Collection of test classes.
GameInterface gDummyTest;
TestGlm gTestGlm;
TestTriangle gTestTriangle;
TestCubie gTestCubie;
TestCompoundCube gTestCompoundCube;
TestKey gTestKey;
TestMaus gTestMaus;
TestTexture gTestTexture;
TestSound gTestSound;

GameInterface* gUsedInterface;


GLFWwindow* InitializeSystem()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Pierric Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    gUsedInterface->Initialize(window);

    return window;
}

void RunCoreloop(GLFWwindow* window)
{
    double lastTime = glfwGetTime();
    double timeDifference = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // Für Maus und Keyboard Input glaube

        gUsedInterface->Update(timeDifference);

        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        float aspectRatio = (float)screenWidth / (float)screenHeight;
        glViewport(0, 0, screenWidth, screenHeight);
        glEnable(GL_DEPTH_TEST);    // tiefentest I guess
        glDepthFunc(GL_LEQUAL);
        glClearColor(0.0f,1.0f, 1.0f, 1.0f); // Hier Farbe ändern falls du nichts siehst
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gUsedInterface->Render(aspectRatio);
        glfwSwapBuffers(window); // damit sieht man auch tatsächlich das was gerendered wird

        double currentTime = glfwGetTime();
        timeDifference = currentTime - lastTime;
        lastTime = currentTime;
    }
}

void ShutdownSystem()
{
    gUsedInterface->ClearResources();
    glfwTerminate();
}

int main()
{
    //gUsedInterface = &gDummyTest;
    //gUsedInterface = &gTestGlm;
    //gUsedInterface = &gTestTriangle;
    //gUsedInterface = &gTestCubie;
    //gUsedInterface = &gTestCompoundCube;
    //gUsedInterface = &gTestKey;
    //gUsedInterface = &gTestMaus;
    //gUsedInterface = &gTestTexture;
    gUsedInterface = &gTestSound;

    GLFWwindow* window = InitializeSystem();
    RunCoreloop(window);
    ShutdownSystem();
}


