// TinyEngine.cpp: 定义应用程序的入口点。
//
//main.cpp
#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "shader.h"
#include "VertexData.h"

GLFWwindow* window;
int width = 960;
int height = 640;
float ratio;

int InitOpenGL();


int main(void)
{
    if (InitOpenGL())
        return -1;

    Shader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

    int mvp_location = glGetUniformLocation(ourShader.ID, "u_mvp");
    int vpos_location = glGetAttribLocation(ourShader.ID, "aPos");
    int vcol_location = glGetAttribLocation(ourShader.ID, "aColor");

    /* 进入游戏引擎主循环 */
    while (!glfwWindowShouldClose(window))
    {

        glm::mat4 model, view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        if (height == 0) height = 1;
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans * scale * rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;


        //指定GPU程序(就是指定顶点着色器、片段着色器)
        ourShader.use();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);//开启背面剔除

        //启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联
        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions);

        //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors);

        //上传mvp矩阵
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
        //上传顶点数据并进行绘制
        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* 处理鼠标 键盘事件 */
        glfwPollEvents();
    }
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int InitOpenGL()
{
    glfwSetErrorCallback(error_callback);

    /* 初始化glfw */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* 创建一个Window 和 OpenGL上下文 */
    window = glfwCreateWindow(960, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //创建失败就退出
        glfwTerminate();
        return -1;
    }

    /* 激活上面创建的OpenGL上下文 */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSwapInterval(1);
    return 0;
}