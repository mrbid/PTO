/*
    James William Fletcher  (github.com/mrbid)
        December 2023       

    "If you chase perfection you just end up making something that is so abstract
        and tailored to yourself that no one else will understand it."
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define uint GLuint
#define sint GLint

#include "inc/gl.h"
#define GLFW_INCLUDE_NONE
#include "inc/glfw3.h"
#define fTime() (float)glfwGetTime()

#include <sys/types.h>
#include <dirent.h>

#define MAX_MODELS 64 // hard limit, be aware and increase if needed
#define GL_DEBUG
#include "inc/esAux7.h"
#include "inc/res.h"

#include "assets/sample.h"

//*************************************
// globals
//*************************************
const char appTitle[]="PLY Viewer";
GLFWwindow* window;
uint winw=1024, winh=768;
float t=0.f, dt=0.f, lt=0.f, fc=0.f, lfct=0.f, aspect;
double mx,my,lx,ly,ww,wh;
mat projection, model;
#define FAR_DISTANCE 66.f

//*************************************
// utility functions
//*************************************
void timestamp(char* ts)
{
    const time_t tt = time(0);
    strftime(ts, 16, "%H:%M:%S", localtime(&tt));
}
void updateModel()
{
    glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (float*)&model.m[0][0]);
}
// void loadModels(const char* dir_path)
// {
//     unsigned int total_samples = 0;
//     DIR* d = opendir(dir_path);
//     if(d != NULL)
//     {
//         struct dirent *dir;
//         while((dir = readdir(d)) != NULL)
//         {
//             if(dir->d_name[0] != '.')
//             {
//                 char fp[384];
//                 sprintf(fp, "target/%s", dir->d_name);
//                 FILE* f = fopen(fp, "rb");
//                 if(f != NULL)
//                 {
//                     fseek(f, 0L, SEEK_END);
//                     const size_t len = ftell(f);
//                     unsigned char data[len];
//                     fseek(f, 0, SEEK_SET);
//                     if(fread(&data, 1, len, f) < len)
//                     {
//                         printf("ERR: %s load.", dir->d_name);\
//                     }
//                     else
//                     {
//                         //
//                         total_samples++;
//                         printf("Loaded: %s\n", dir->d_name);
//                     }
//                     fclose(f);
//                 }
//             }
//         }
//         closedir(d);
//     }
//     char tmp[256];
//     sprintf(tmp, "%u", total_samples);
//     glfwSetWindowTitle(window, tmp);
// }

//*************************************
// update & render
//*************************************
void main_loop()
{
    // delta time
    fc++;
    glfwPollEvents();
    t = fTime();
    dt = t-lt;
    lt = t;

    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render ufo
    mIdent(&model);
    mRotY(&model, 90*DEG2RAD);
    mRotZ(&model, t * 2.f);
    mSetPos(&model, (vec){0.f, -1.f, -5.f});
    updateModel();
    esBindRender(0);

    // display render
    glfwSwapBuffers(window);
}

//*************************************
// input
//*************************************
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // control
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_Q) // previous page
        {
            //
        }
        else if(key == GLFW_KEY_W) // next page
        {
            //
        }
        else if(key == GLFW_KEY_F) // show average fps
        {
            if(t-lfct > 2.0)
            {
                char strts[16];
                timestamp(&strts[0]);
                printf("[%s] FPS: %g\n", strts, fc/(t-lfct));
                lfct = t;
                fc = 0;
            }
        }
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset < 0.0)
    {
        //
    }
    else
    {
        //
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            //
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            //
        }
    }
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
    winw = width, winh = height;
    glViewport(0, 0, winw, winh);
    aspect = (float)winw / (float)winh;
    ww = winw, wh = winh;
    mIdent(&projection);
    mPerspective(&projection, 60.0f, aspect, 0.01f, FAR_DISTANCE);
    glUniformMatrix4fv(projection_id, 1, GL_FALSE, (float*)&projection.m[0][0]);
}

//*************************************
// process entry point
//*************************************
int main(int argc, char** argv)
{
    // allow custom msaa level
    int msaa = 16;
    if(argc >= 2){msaa = atoi(argv[1]);}

    // help
    printf("----\n");
    printf("James William Fletcher (github.com/mrbid)\n");
    printf("%s - If you chase perfection you just end up making something that is so abstract and tailored to yourself that no one else will understand it.\n", appTitle);
    printf("----\n");
    printf("One command line argument, msaa 0-16\n");
    printf("e.g; ./plv 16\n");
    printf("----\n");
    printf("keys mappings\n");
    printf("----\n");
    printf("Icon by Forest Walter\n");
    printf("https://www.forrestwalter.com/\n");
    printf("----\n");
    printf("%s\n", glfwGetVersionString());
    printf("----\n");

    // init glfw
    if(!glfwInit()){printf("glfwInit() failed.\n"); exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, msaa);
    window = glfwCreateWindow(winw, winh, appTitle, NULL, NULL);
    if(!window)
    {
        printf("glfwCreateWindow() failed.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    const GLFWvidmode* desktop = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (desktop->width/2)-(winw/2), (desktop->height/2)-(winh/2)); // center window on desktop
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1); // 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync
    glfwSetWindowIcon(window, 1, &(GLFWimage){16, 16, (unsigned char*)icon_image});

//*************************************
// bind vertex and index buffers
//*************************************
    esLoadModel(sample);

//*************************************
// configure render options
//*************************************
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.f, 0.f, 0.f, 0.f);
    //glClearColor(0.3f, 0.745f, 0.8863f, 0.f);
    //glClearColor(0.59608f, 0.37647f, 0.65882f, 0.f);

    makeLambert();
    shadeLambert(&position_id, &projection_id, &modelview_id, &lightpos_id, &normal_id, &color_id, &ambient_id, &saturate_id, &opacity_id);
    glUniformMatrix4fv(projection_id, 1, GL_FALSE, (float*)&projection.m[0][0]);
    window_size_callback(window, winw, winh);
    glUniform1f(ambient_id, 0.648f);
    glUniform1f(saturate_id, 1.f);

    esDebug(1);

//*************************************
// execute update / render loop
//*************************************
    t = fTime();
    lfct = t;
    while(!glfwWindowShouldClose(window)){main_loop();}
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
