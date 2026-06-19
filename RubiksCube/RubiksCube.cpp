
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GameInterface.h"
#include "TestGlm.h"
#include "TestTriangle.h"

// Collection of test classes.
GameInterface gDummyTest;
TestGlm gTestGlm;
TestTriangle gTestTriangle;

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

    gUsedInterface->Initialize();

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
        glClearColor(1.0f,1.0f, 0.0f, 1.0f); // Hier Farbe ändern falls du nichts siehst
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
    gUsedInterface = &gTestTriangle;

    GLFWwindow* window = InitializeSystem();
    RunCoreloop(window);
    ShutdownSystem();
}





















// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
