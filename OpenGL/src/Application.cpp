#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "Camera.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Model.h"

#include "FrameBuffer.h"
#include "RenderBuffer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void SetShaderUniforms(const Shader& shader,const glm::vec3* pointLightPositions);

extern const unsigned int SCR_WIDTH = 800;
extern const unsigned int SCR_HEIGHT = 600;

bool firstMouse = true;
float yaw =-90.0f;
float pitch = 0.0f;
float lastX =400.0f;
float lastY =300.0f;
float fov = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

glm::vec3 lightPos(1.2f,1.0f,2.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
  
    {
       float vertices[] = {
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };

       float planeVertices[] = {
            5.0f, -0.51f,  5.0f, 0.0f, 1.0f, 0.0f,  2.0f, 0.0f,
           -5.0f, -0.51f,  5.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
           -5.0f, -0.51f, -5.0f, 0.0f, 1.0f, 0.0f,  0.0f, 2.0f,

            5.0f, -0.51f,  5.0f, 0.0f, 1.0f, 0.0f,  2.0f, 0.0f,
           -5.0f, -0.51f, -5.0f, 0.0f, 1.0f, 0.0f,  0.0f, 2.0f,
            5.0f, -0.51f, -5.0f, 0.0f, 1.0f, 0.0f,  2.0f, 2.0f
       };
     
       float quadVertices[] = {
           -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
           -1.0f,  0.5f, 0.0f, 0.0f, 0.0f,
           -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

           -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
           -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
           -0.5f, 1.0f, 0.0f, 1.0f, 1.0f
       };

       float skyboxVertices[] = {
           -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
       };

       glm::vec3 cubePositions[] = {
          glm::vec3(-1.0f,2.0f,-1.0f),
          glm::vec3(2.0f,0.0f,0.0f),
       };

       glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f,0.2f,2.0f),
            glm::vec3(2.3f,-3.3f,-4.0f),
            glm::vec3(-4.0f,2.0f,-12.0f),
            glm::vec3(0.0f,0.0f,-3.0f),
       };

        VertexBuffer vb(vertices, sizeof(vertices));
        VertexBuffer vb1(planeVertices, sizeof(planeVertices));
        VertexBuffer vbQuad(quadVertices, sizeof(quadVertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        VertexBufferLayout layoutPlane;
        layoutPlane.Push<float>(3);
        layoutPlane.Push<float>(3);
        layoutPlane.Push<float>(2);

        VertexBufferLayout layoutQuad;
        layoutQuad.Push<float>(3);
        layoutQuad.Push<float>(2);

        VertexArray va;
        va.AddBuffer(vb,layout);

        VertexArray lightVa;
        lightVa.AddBuffer(vb,layout);

        VertexArray planeVa;
        planeVa.AddBuffer(vb1, layoutPlane);

        VertexArray quadVa;
        quadVa.AddBuffer(vbQuad, layoutQuad);

        Shader shader("res/shaders/VertexShader.glsl","res/shaders/FragmentShader.glsl");
        shader.Bind();

        Shader modelShader("res/shaders/ModelVertex.glsl","res/shaders/ModelFragment.glsl");
        modelShader.Bind();

        Shader planeShader("res/shaders/PlaneVertex.glsl","res/shaders/PlaneFragment.glsl");
        planeShader.Bind();

        Shader lineShader("res/shaders/LineVertex.glsl","res/shaders/LineFragment.glsl");
        lineShader.Bind();

        Shader frame("res/shaders/CubeVertex.glsl", "res/shaders/CubeFragment.glsl");
        frame.Bind();

        Shader quadShader("res/shaders/QuadVertex.glsl", "res/shaders/QuadFragment.glsl");
        quadShader.Bind();

        Shader depthShader("res/shaders/DepthVertex.glsl", "res/shaders/DepthFragment.glsl");
        depthShader.Bind();

        Shader shadowShader("res/shaders/ShadowVertex.glsl", "res/shaders/ShadowFragment.glsl");
        shadowShader.Bind();

        //Model nanosuit("res/models/donut/Donut.obj");

        VertexBuffer skyboxIB(skyboxVertices,sizeof(skyboxVertices));
        VertexBufferLayout layoutSkybox;
        layoutSkybox.Push<float>(3);
        VertexArray skyboxVa;
        skyboxVa.AddBuffer(skyboxIB, layoutSkybox);

        Shader skyboxShader("res/shaders/SkyboxVertex.glsl", "res/shaders/SkyboxFragment.glsl");

        std::vector<std::string> skyboxPath = {
            "res/textures/cubemaps/skybox/right.jpg",
            "res/textures/cubemaps/skybox/left.jpg",
            "res/textures/cubemaps/skybox/top.jpg",
            "res/textures/cubemaps/skybox/bottom.jpg",
            "res/textures/cubemaps/skybox/front.jpg",
            "res/textures/cubemaps/skybox/back.jpg"
        };
        Texture skyboxTex(skyboxPath);


        Texture diffuseMap("res/textures/container2.png");
        Texture specularMap("res/textures/container2_specular.png");
        Texture planeMap("res/textures/grass.jpg");
        Texture donut("res/textures/donut.png");

        Renderer render;     

        frame.Bind();
        frame.SetUniformInt("texture1", 0);
        quadShader.Bind();
        quadShader.SetUniformInt("tex", 0);
       
        shadowShader.Bind();
        shadowShader.SetUniformInt("diffuseMap", 0);
        shadowShader.SetUniformInt("shadowMap", 1);
        shadowShader.SetUniformInt("specularMap", 2);

        FrameBuffer depthFBO;
        Texture depthMap(1024,1024);
        depthFBO.Status();

        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window);

            render.Clear();

            //SetShaderUniforms(shader,pointLightPositions);
            
            glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()),(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.View();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 mvp = projection*view*model;
            
            glm::mat4 lightProjection=glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
            glm::mat4 lightView = glm::lookAt(glm::vec3(-1.5f,4.0f,-1.5f),glm::vec3(0.0f),glm::vec3(0.0f,1.0f,0.0f));
            glm::mat4 lightSpaceMatrix = lightProjection * lightView;

            depthShader.Bind();
            depthShader.SetUniform4x4("lightSpaceMatrix", lightSpaceMatrix);

            glViewport(0, 0, 1024, 1024);
            depthFBO.Bind();
            glClear(GL_DEPTH_BUFFER_BIT);
            diffuseMap.Bind();

            model = glm::mat4(1.0f);
            depthShader.SetUniform4x4("model", model);
            render.Draw(planeVa, depthShader, 6);

            for (unsigned int i = 0; i < 2; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                depthShader.SetUniform4x4("model", model);
                render.Draw(va, depthShader, 36);
            }

            depthFBO.UnBind();
                   
            glViewport(0, 0,SCR_WIDTH,SCR_HEIGHT);
            render.Clear();

            shadowShader.Bind();
            shadowShader.SetUniform4x4("projection", projection);
            shadowShader.SetUniform4x4("view", view);
            shadowShader.SetUniformVec3("lightPos", glm::vec3(-2.0f, 4.0f, -1.0f));
            shadowShader.SetUniformVec3("viewPos", camera.GetPosition());
            shadowShader.SetUniform4x4("lightSpaceMatrix", lightSpaceMatrix);

            diffuseMap.Bind(0);
            depthMap.Bind(1);

            model = glm::mat4(1.0f);
            shadowShader.SetUniform4x4("model", model);
            planeMap.Bind(0);
            planeMap.Bind(2);
            render.Draw(planeVa,shadowShader, 6);
              
            for (unsigned int i = 0; i < 2; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                shadowShader.SetUniform4x4("model", model);
                diffuseMap.Bind(0);
                specularMap.Bind(2);
                render.Draw(va,shadowShader, 36);
            }

            glDepthFunc(GL_LEQUAL);
            view = glm::mat4(glm::mat3(camera.View()));
            mvp = projection * view;
            skyboxShader.Bind();
            skyboxShader.SetUniform4x4("mvp", mvp);
            skyboxTex.BindCubeMap();
            render.Draw(skyboxVa, skyboxShader, 36);
            glDepthFunc(GL_LESS);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.KeyboardInput(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.KeyboardInput(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.KeyboardInput(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.KeyboardInput(RIGHT, deltaTime);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY-ypos;
    lastX = xpos;
    lastY = ypos;
    
    camera.MouseProcess(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ScrollProcess(yoffset);
}

void SetShaderUniforms(const Shader& shader,const glm::vec3* pointLightPositions)
{
    shader.Bind();

    shader.SetUniformInt("material.diffuse", 0);
    shader.SetUniformInt("material.specular", 1);
    shader.SetUniformFloat("material.shininess", 64.0f);
    shader.SetUniformVec3("view", camera.GetPosition());

    // directional light
    shader.SetUniformVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shader.SetUniformVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shader.SetUniformVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    shader.SetUniformVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    shader.SetUniformVec3("pointLights[0].position", pointLightPositions[0]);
    shader.SetUniformVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shader.SetUniformVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    shader.SetUniformVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    shader.SetUniformFloat("pointLights[0].constant", 1.0f);
    shader.SetUniformFloat("pointLights[0].linear", 0.09);
    shader.SetUniformFloat("pointLights[0].quadratic", 0.032);
    // point light 2
    shader.SetUniformVec3("pointLights[1].position", pointLightPositions[1]);
    shader.SetUniformVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    shader.SetUniformVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    shader.SetUniformVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    shader.SetUniformFloat("pointLights[1].constant", 1.0f);
    shader.SetUniformFloat("pointLights[1].linear", 0.09);
    shader.SetUniformFloat("pointLights[1].quadratic", 0.032);
    // point light 3
    shader.SetUniformVec3("pointLights[2].position", pointLightPositions[2]);
    shader.SetUniformVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    shader.SetUniformVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    shader.SetUniformVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    shader.SetUniformFloat("pointLights[2].constant", 1.0f);
    shader.SetUniformFloat("pointLights[2].linear", 0.09);
    shader.SetUniformFloat("pointLights[2].quadratic", 0.032);
    // point light 4
    shader.SetUniformVec3("pointLights[3].position", pointLightPositions[3]);
    shader.SetUniformVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    shader.SetUniformVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    shader.SetUniformVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    shader.SetUniformFloat("pointLights[3].constant", 1.0f);
    shader.SetUniformFloat("pointLights[3].linear", 0.09);
    shader.SetUniformFloat("pointLights[3].quadratic", 0.032);
    // spotLight
    shader.SetUniformVec3("spotLight.position", camera.GetPosition());
    shader.SetUniformVec3("spotLight.direction", camera.GetFront());
    shader.SetUniformVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shader.SetUniformVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shader.SetUniformVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shader.SetUniformFloat("spotLight.constant", 1.0f);
    shader.SetUniformFloat("spotLight.linear", 0.09);
    shader.SetUniformFloat("spotLight.quadratic", 0.032);
    shader.SetUniformFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.SetUniformFloat("spotLight.outOff", glm::cos(glm::radians(15.0f)));
}

//model = glm::translate(model, glm::vec3(0.0f, -0.555f, 3.0f));   //0.0f, -1.74f, 1.0f - nanosuit
//model = glm::scale(model, glm::vec3(5.0f));   //0.2 - nanosuit    //5.0f-donut