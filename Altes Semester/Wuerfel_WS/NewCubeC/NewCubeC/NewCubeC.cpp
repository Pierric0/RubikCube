#define GLEW_STATIC
#include <GL\glew.h>

#include <iostream>
#include <GLFW/glfw3.h>
#include "Gameinterface.h"
#include "TestGlm.h"

#include "TestTriangle.h"

GameInterface* gUsedInterface;

GameInterface gDummyInterface;

TestGlm gTestGlm;

TestTriangle tTri;

GLFWwindow* InitializeSystem() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Rubiks Cube", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    gUsedInterface->Initialize(window);

    return window;


}
void RunCoreLoop(GLFWwindow* window) {
    
    double lastTime = glfwGetTime();
    double timeDifference = 0.0;
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        gUsedInterface->Update(timeDifference);

        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        const float aspectRatio = screenWidth*1.0 / static_cast<float>(screenHeight);


        glViewport(0, 0, screenWidth, screenHeight);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gUsedInterface->Render(aspectRatio);

        glfwSwapBuffers(window);

        // wenn nur schwarz kann es sein das ich nichts zeichne oder der hintergrund die gleiche farbe hat. Auch kann sein das ich einfach woanders zeichne.

        const double currentTime = glfwGetTime();
        timeDifference = currentTime - lastTime;
        lastTime = currentTime;
    }
}

void ShutdownSystem() {
    gUsedInterface->ClearResources();
    glfwTerminate();
}

int main()
{
    //gUsedInterface = &gDummyInterface;
    //gUsedInterface = &gTestGlm;
    gUsedInterface = &tTri;

    GLFWwindow* window = InitializeSystem();
    RunCoreLoop(window);
    ShutdownSystem();

    // glfwInit();
    
    
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
