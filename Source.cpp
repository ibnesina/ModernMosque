#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include "BezierCurve.h"
#include "BezierCurveArch.h"
#include "Hexa.h"
#include "sphere.h"

#include "water_fountain.h"

#include "stb_image.h"

#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


void SetupPointLight(PointLight& pointLight, Shader ourShader, int lightNum);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color);

//fuctions prototypes
void load_texture(unsigned int& texture, string image_name, GLenum format);//texture loading function

//draw function
void Field(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

void MainMosjidBase(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1, unsigned int texture2 , unsigned int texture3);
void Mosjid1stFloor(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, unsigned int VAO14, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Mosjid2ndFloor(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, unsigned int VAO14, unsigned int VAO220, unsigned int VAO38, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

void MidGate(unsigned int VAO1, unsigned int VAO1020, unsigned int VAO16, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void StairTower1(unsigned int VAO, BezierCurve Round_Piller, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//Component
void Fan_and_switch(unsigned int VAO, BezierCurve Fan_Bati, BezierCurve Fan_Blade, BezierCurve Fan_Tube, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Main_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Common_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Common_Arch_Vertical(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void small_dome(unsigned int VAO, BezierCurve circle, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift);
void mid_dome(unsigned int VAO, BezierCurve circle1, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Big_dome(unsigned int VAO, BezierCurve circle2, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift);
void jharbati(unsigned int VAO, BezierCurve Round_Piller, Shader ourShader, float x_shift, float y_shift, float z_shift);

void DoubleDoors(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1, unsigned int texture2);
void SideDoor1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void SideDoor2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
// void tape3(unsigned int VAO, BezierCurve Piller_round1, BezierCurve spike2, Shader ourShader, float x_shift, float y_shift, float z_shift);
void imam_Place(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void bookshef(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Glass_Door_1_1(unsigned int TransparentVAO,Shader transparentShader, float x_shift, float y_shift, float z_shift);
void Glass_Door_Frame_1_1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Glass_Door_1_2(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift);
void Glass_Door_Frame_1_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);

void Almari_1_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Almari_2_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);

void Glass_win_Frame_2_1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Glass_win_Frame_2_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Glass_win_Frame_2_3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Glass_win_Frame_2_4(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Glass_win_2_1(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift);
void Glass_win_2_2(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift);
void Glass_win_2_3(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift);
void Glass_win_2_4(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift);

//Genral Core-----------------------------
void HorizontalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift,  float len, float ht, float lbx, float lby, float lbz, unsigned int texture);
void VerticalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture);
void GenFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture);
void GenFloor2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture);
void Box(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void FlatBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void HoloBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void MidArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void RaillingUnit(unsigned int VAO, BezierCurve Round_piller, Shader ourShader, float x_shift, float y_shift, float z_shift);
//GenSheet--
//rot_x, rot_y, rot_z origin e thaka obosthay kaj kore
void GenSheet_Transparent(unsigned int VAO, Shader ourShader, float len, float width, float height, float local_x, float local_y, float local_z, float rot_x,float rot_y, float rot_z, float trans_x, float trans_y, float trans_z, float x_shift, float y_shift, float z_shift, glm::vec4 color, unsigned int texture);
void GenSheet(unsigned int VAO, Shader ourShader, float len, float width, float height, float local_x, float local_y, float local_z, float rot_x, float rot_y, float rot_z, float trans_x, float trans_y, float trans_z, float x_shift, float y_shift, float z_shift, glm::vec4 color, unsigned int texture);



//Collors
glm::vec4 red = glm::vec4(1.0, 0.0, 0.0, 1.0f);
glm::vec4 green = glm::vec4(0.0, 1.0, 0.0, 1.0f);
glm::vec4 blue = glm::vec4(0.0, 0.0, 1.0, 1.0f);
glm::vec4 black = glm::vec4(0.0, 0.0, 0.0, 1.0f);
glm::vec4 white = glm::vec4(1.0, 1.0, 1.0, 1.0f);
glm::vec4 off_white = glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f);
glm::vec4 sky_blue = glm::vec4(0.4549019607843137, 0.8196078431372549, 0.9450980392156862, 1.0f);
glm::vec4 light_sky_blue = glm::vec4(0.4549019607843137, 0.8196078431372549, 0.9450980392156862, 0.3f);//opacity 0.3
glm::vec4 gloden = glm::vec4(0.9098039215686274, 0.792156862745098, 0.2980392156862745, 1.0f);


// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

//FAN rotate
//1st floor
bool isRotate1 = false;
float fanspeed1 = 0.0f;
float rotateAxis_Y_Fan1 = 0.0;
bool Fan1_ready = true;

//2nd floor
bool isRotate2 = false;
float fanspeed2 = 0.0f;
float rotateAxis_Y_Fan2 = 0.0;
bool Fan2_ready = true;


//MAIN DOUBLE DOOR
bool isDoubleDoor = false;
float doorspeed = 1.0f;
float rotateAxis_Y_Door = 0.0;
bool DDoor_ready = true;

//MAIN DOUBLE DOOR
bool isTDoor = false;
float Tspeed = 1.0f;
float rotateAxis_Y_TDoor = 0.0;
bool TDoor_ready = true;

//TAP1
bool isTape1 = false;
float Tape_speed1 = 0.05;
float translate_Y_Tape1 = 0.0;

//sideDoor1
float side_trans_Z_1 = 0.0;

//sideDoor2
float side_trans_Z_2 = 0.0;

//water counter
int wcnt = 0;

//almari_1_1
float rotateAxis_Y_Almari_1_1 = 0.0;
//almari_1_2
float rotateAxis_Y_Almari_1_2 = 0.0;
//almari_2_1
float rotateAxis_Y_Almari_2_1 = 0.0;
//almari_2_2
float rotateAxis_Y_Almari_2_2 = 0.0;

//Door_1_1
float rotateAxis_Y_Door_1_1 = 0.0;
//Door_1_2
float rotateAxis_Y_Door_1_2 = 0.0;

//win_1_1
float rotateAxis_Y_win_2_1 = 0.0;
//win_2_2
float rotateAxis_Y_win_2_2 = 0.0;
//win_2_3
float rotateAxis_Y_win_2_3 = 0.0;
//win_2_4
float rotateAxis_Y_win_2_4 = 0.0;

//ligth
bool jhar_light = false;

// camera
Camera camera(glm::vec3(38.0f, 2.5f, -19.5f));//camera position
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 0.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f,lastTimeSky = 0.0f;

bool useTexture = false;  // Initially, textures are OFF
unsigned int objectTexture = 0;


// Light initialization
const int noOfPointLights = 36;

glm::vec3 lightPositions[] = {
        glm::vec3(-0.95f, 1.4f, -2.7f),         //Directional Light
        glm::vec3(22.5f, 3.7f, -14.00f),
        glm::vec3(52.5f, 3.7f, -14.00f),
        glm::vec3(10.2f, -331.35f, 1.48f),
        glm::vec3(6.2f, -144.35f, 7.98f),
        glm::vec3(12.0f, 7.75f, -61.00f), //spot light
        glm::vec3(12.0f, 3.9f, -14.00f),//oju//6
        glm::vec3(63.0f, 3.9f, -14.00f),//toilet//7
        glm::vec3(12.0f, 3.7f, -26.5f),
        glm::vec3(12.0f, 7.75f, -61.00f),//siri //9
        glm::vec3(63.0f, 3.7f, -26.50f),
        glm::vec3(63.0, 3.7f, -56.00f),//lift //11
        glm::vec3(23.0f, 3.7f, -39.50f),
        glm::vec3(37.5f, 4.6f, -39.50f),//mid gate //13
        glm::vec3(54.5f, 3.7f, -39.50f),
        glm::vec3(34.0f, -332.5f, -26.25f),//pond
        glm::vec3(41.0f, -332.5f, -26.25f),//pond
        glm::vec3(37.5f, 4.5f, -14.00f),//main gate
        glm::vec3(15.7f, 3.5f, -67.80f),//room back left corner
        glm::vec3(59.3f, 3.5f, -67.80f),//room back right corner
        glm::vec3(15.7f, 7.5f, -66.80f),//room back 2nd left corner //20
        glm::vec3(59.3f, 7.5f, -66.80f),//room back 2nd right corner
        glm::vec3(15.7f, 3.5f, -43.20f),//room back left corner
        glm::vec3(59.3f, 3.5f, -43.20f),//room back right corner
        glm::vec3(15.7f, 7.5f, -45.20f),//room back 2nd left corner
        glm::vec3(59.3f, 7.5f, -45.20f),//room back 2nd right corner
        glm::vec3(29.0, 8.88f, -56.00f),//top//26
        glm::vec3(46.0f, 8.88f, -56.00f),//top
        glm::vec3(37.5f+0.9f, 3.3f, -56.00f),//28
        glm::vec3(37.5f+1.8, 3.3f, -56.00f),
        glm::vec3(37.5f, 3.3f, -56.00f-0.9),
        glm::vec3(37.5f, 3.3f, -56.00f-1.8),
        glm::vec3(37.5f - 0.9f, 3.3f, -56.00f),
        glm::vec3(37.5f - 1.8, 3.3f, -56.00f),
        glm::vec3(37.5f, 3.3f, -56.00f + 0.9),
        glm::vec3(37.5f, 3.3f, -56.00f + 1.8),
        glm::vec3(0.0f, -222.5f, 0.0f),
        glm::vec3(60.5f, -223.5f, -4.00f)
};

glm::vec3 lightDirections[] = {
    glm::vec3(-2.0f, -0.2f, -1.3f)
};

DirectionalLight directionalLight(-lightPositions[0], glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 0.2f), 1);
SpotLight spotLight(lightPositions[5], lightDirections[0], 4.5f, 7.5f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0014f, 0.000007f, 1);
PointLight pointLight1(lightPositions[1], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 1);
PointLight pointLight2(lightPositions[2], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 2);
PointLight pointLight3(lightPositions[3], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 3);
PointLight pointLight4(lightPositions[4], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 4);
PointLight pointLight5(lightPositions[6], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 5);
PointLight pointLight6(lightPositions[7], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 6);
PointLight pointLight7(lightPositions[8], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1, 0.9333333333333333, 0.4588235294117647, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 7);
PointLight pointLight8(lightPositions[9], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1, 0.9333333333333333, 0.4588235294117647, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 8);
PointLight pointLight9(lightPositions[10], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1, 0.9333333333333333, 0.4588235294117647, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 9);
PointLight pointLight10(lightPositions[11], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1, 0.9333333333333333, 0.4588235294117647, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 10);
PointLight pointLight11(lightPositions[12], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1, 0.9333333333333333, 0.4588235294117647, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 11);
PointLight pointLight12(lightPositions[13], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 12);
PointLight pointLight13(lightPositions[14], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1, 0.9333333333333333, 0.4588235294117647, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 13);
PointLight pointLight14(lightPositions[15], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 14);
PointLight pointLight15(lightPositions[16], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 15);
PointLight pointLight16(lightPositions[17], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 16);
PointLight pointLight17(lightPositions[18], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 17);
PointLight pointLight18(lightPositions[19], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 18);
PointLight pointLight19(lightPositions[20], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 19);
PointLight pointLight20(lightPositions[21], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 20);
PointLight pointLight21(lightPositions[22], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 21);
PointLight pointLight22(lightPositions[23], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 22);
PointLight pointLight23(lightPositions[24], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 23);
PointLight pointLight24(lightPositions[25], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 24);
PointLight pointLight25(lightPositions[26], glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 25);
PointLight pointLight26(lightPositions[27], glm::vec4(0.984313725490196, 1, 0.08627450980392157, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 26);
PointLight pointLight27(lightPositions[28], glm::vec4(0.4f, 0.0f, 0.0f, 1.0f), glm::vec4(0.2, 0, 0.0, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 27);
PointLight pointLight28(lightPositions[29], glm::vec4(0.0f, 0.0f, 0.2f, 1.0f), glm::vec4(0.0, 0, 0.2, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 28);
PointLight pointLight29(lightPositions[30], glm::vec4(0.4f, 0.0f, 0.0f, 1.0f), glm::vec4(0.2, 0, 0.0, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 29);
PointLight pointLight30(lightPositions[31], glm::vec4(0.0f, 0.0f, 0.2f, 1.0f), glm::vec4(0.0, 0, 0.2, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 30);
PointLight pointLight31(lightPositions[32], glm::vec4(0.4f, 0.0f, 0.0f, 1.0f), glm::vec4(0.2, 0, 0.0, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 31);
PointLight pointLight32(lightPositions[33], glm::vec4(0.0f, 0.0f, 0.2f, 1.0f), glm::vec4(0.0, 0, 0.2, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 32);
PointLight pointLight33(lightPositions[34], glm::vec4(0.4f, 0.0f, 0.0f, 1.0f), glm::vec4(0.2, 0, 0.0, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 33);
PointLight pointLight34(lightPositions[35], glm::vec4(0.0f, 0.0f, 0.2f, 1.0f), glm::vec4(0.0, 0, 0.2, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 34);
PointLight pointLight35(lightPositions[36], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 35);
PointLight pointLight36(lightPositions[37], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 36);

////texture
//style1-- 1X1//used
float ext = 0.0f;
float TXmin = 0.0f;
float TXmax = 1.0f+ext;
float TYmin = 0.0f;
float TYmax = 1.0f+ext;

//style2--- 1X2//used
float ext2 = 1.0f;
float TXmin2 = 0.0f;
float TXmax2 = 1.0f + ext2;
float TYmin2 = 0.0f;
float TYmax2 = 1.0f + 0.0f;

//style3-- 1X3
float ext3 = 2.0f;
float TXmin3 = 0.0f;
float TXmax3 = 1.0f + ext3;
float TYmin3 = 0.0f;
float TYmax3 = 1.0f + 0.0f;

//style3-- 1X4
float ext14 = 3.0f;
float TXmin14 = 0.0f;
float TXmax14 = 1.0f + 3.0;
float TYmin14 = 0.0f;
float TYmax14 = 1.0f + 0.0f;
//style3-- 4X1
float ext41 = 3.0f;
float TXmin41 = 0.0f;
float TXmax41 = 1.0f + 0.0;
float TYmin41 = 0.0f;
float TYmax41 = 1.0f + 3.0f;
//style3-- 1X6//used
float ext6 = 6.0f;
float TXmin6 = 0.0f;
float TXmax6 = 1.0f + ext6;
float TYmin6 = 0.0f;
float TYmax6 = 1.0f + 0.0f;
//style3-- 10X1//used
float ext10 = 9.0f;
float TXmin10 = 0.0f;
float TXmax10 = 1.0f + 0.0;
float TYmin10 = 0.0f;
float TYmax10 = 1.0f + ext10;
//style4-- 7x20//used
float ext4 = 2.0f;
float TXmin4 = 0.0f;
float TXmax4 = 1.0f + 19.0;
float TYmin4 = 0.0f;
float TYmax4 = 1.0f + 6.0;

//style5-- 7x7used
float ext5 = 2.0f;
float TXmin5 = 0.0f;
float TXmax5 = 1.0f + 7.0;
float TYmin5 = 0.0f;
float TYmax5 = 1.0f + 7.0;

//style5-- 3x8used
float ext38 = 2.0f;
float TXmin38 = 0.0f;
float TXmax38 = 1.0f + 7.0;
float TYmin38 = 0.0f;
float TYmax38 = 1.0f + 2.0;

//style5-- 2x20used
float ext220 = 2.0f;
float TXmin220 = 0.0f;
float TXmax220 = 1.0f + 19.0;
float TYmin220 = 0.0f;
float TYmax220 = 1.0f + 1.0;

//style5-- 5x10used
float TXmin1020 = 0.0f;
float TXmax1020 = 1.0f + 9.0;
float TYmin1020 = 0.0f;
float TYmax1020 = 1.0f + 4.0;

//LIGHT SWITCH
bool lightingOn = true;
float ambientOn = 1.0;
float diffuseOn = 1.0;
float specularOn = 1.0;
bool dark = false;

float directionalLightOn = 1.0;
float pointLightOn[noOfPointLights] = { 0.0, 0.0, 0.0, 0.0,0.0 ,0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
float spotLightOn = 0.0;

//Texture variables
unsigned int texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10, texture11, texture12, texture13, frontwall1,frontwall2,sidewall1,sidewall2,blankwall;
unsigned int mehrab, mehrabside, t_door, t_floor, wodden, side_door, metal_dome, metal_tape, flu, leftDoor, rightDoor, glass, win_frame, win_right, win_left, main_glass,ac,acflap;
unsigned int al,al_books,al_door1,al_door2,low_com,water[10];


WaterFountain fountain(glm::vec3(37.5f, 0.5f, -27.0f), 2000);

void updateScene(float deltaTime) {
    fountain.update(deltaTime);
}

void renderScene(Shader &shader) {
    static bool initialized = false;
    if (!initialized) {
        fountain.setupSphere();  // Setup Sphere once when rendering starts
        initialized = true;
    }
    fountain.render(shader);
}

void drawBranch(Shader &shader, glm::mat4 model, int depth) {
    if (depth == 0) return;

    // Render branch
    glBindVertexArray(1); // Assuming VAO 1 is for branch
    shader.setMat4("model", model);
    glDrawArrays(GL_LINES, 0, 2);

    // Create transformations
    glm::mat4 leftBranch = model;
    leftBranch = glm::translate(leftBranch, glm::vec3(0.0f, 1.0f, 0.0f));
    leftBranch = glm::rotate(leftBranch, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    leftBranch = glm::scale(leftBranch, glm::vec3(0.7f, 0.7f, 1.0f));

    glm::mat4 rightBranch = model;
    rightBranch = glm::translate(rightBranch, glm::vec3(0.0f, 1.0f, 0.0f));
    rightBranch = glm::rotate(rightBranch, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rightBranch = glm::scale(rightBranch, glm::vec3(0.7f, 0.7f, 1.0f));

    // Recursive call
    drawBranch(shader, leftBranch, depth - 1);
    drawBranch(shader, rightBranch, depth - 1);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Modern Mosque", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader zprogram
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");//for other objects
    Shader lightCubeShader("lightVertexShader.vs", "lightFragmentShader.fs");//only for light cubes
    Shader TransparentShader("vertexShaderForBlending.vs", "fragmentShaderForBlending.fs");//for transparent object
    //Shader skyboxShader("skybox.vert", "skybox.frag");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    // Transparent VAO
    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
         0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  0.0f,  1.0f,  0.0f
    };

    // transparent VAO
    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


    //cube 1X1---------------------------------------------------------------------------------------------
    float cube_vertices[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmax,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmin,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmax,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmin,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmax,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube 1
    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    //ekhon total 8 ta value thakbe
    // 1st 3 ta vertex point, 2nd 3 ta normal vector, 3rd 2 ta texture cords
    // stride parameter 6 theke ekhon 8 hoye jabe
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 1X2-----------------------------------------------------------------------------

    float cube_vertices2[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax2, TYmin2,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin2, TYmin2,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin2, TYmax2,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax2, TYmax2,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax2, TYmin2,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax2, TYmax2,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin2, TYmin2,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin2, TYmax2,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin2, TYmin2,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax2, TYmin2,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax2, TYmax2,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin2, TYmax2,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax2, TYmin2,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax2, TYmax2,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin2, TYmax2,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin2, TYmin2,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax2, TYmin2,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax2, TYmax2,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin2, TYmax2,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin2, TYmin2,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin2, TYmin2,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax2, TYmin2,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax2, TYmax2,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin2, TYmax2
    };
    unsigned int cube_indices2[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO2, cubeVBO2, cubeEBO2;
    glGenVertexArrays(1, &cubeVAO2);
    glGenBuffers(1, &cubeVBO2);
    glGenBuffers(1, &cubeEBO2);

    glBindVertexArray(cubeVAO2);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices2), cube_vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices2), cube_indices2, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 1X3-----------------------------------------------------------------------------

    float cube_vertices3[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax3, TYmin3,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin3, TYmin3,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin3, TYmax3,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax3, TYmax3,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax3, TYmin3,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax3, TYmax3,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin3, TYmin3,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin3, TYmax3,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin3, TYmin3,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax3, TYmin3,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax3, TYmax3,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin3, TYmax3,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax3, TYmin3,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax3, TYmax3,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin3, TYmax3,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin3, TYmin3,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax3, TYmin3,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax3, TYmax3,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin3, TYmax3,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin3, TYmin3,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin3, TYmin3,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax3, TYmin3,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax3, TYmax3,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin3, TYmax3
    };
    unsigned int cube_indices3[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube3 
    unsigned int cubeVAO3, cubeVBO3, cubeEBO3;
    glGenVertexArrays(1, &cubeVAO3);
    glGenBuffers(1, &cubeVBO3);
    glGenBuffers(1, &cubeEBO3);

    glBindVertexArray(cubeVAO3);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices3), cube_indices3, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);

    //1x4
    float cube_vertices14[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax14, TYmin14,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin14, TYmin14,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin14, TYmax14,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax14, TYmax14,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax14, TYmin14,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax14, TYmax14,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin14, TYmin14,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin14, TYmax14,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin14, TYmin14,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax14, TYmin14,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax14, TYmax14,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin14, TYmax14,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax14, TYmin14,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax14, TYmax14,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin14, TYmax14,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin14, TYmin14,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax14, TYmin14,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax14, TYmax14,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin14, TYmax14,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin14, TYmin14,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin14, TYmin14,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax14, TYmin14,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax14, TYmax14,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin14, TYmax14
    };
    unsigned int cube_indices14[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube3 
    unsigned int cubeVAO14, cubeVBO14, cubeEBO14;
    glGenVertexArrays(1, &cubeVAO14);
    glGenBuffers(1, &cubeVBO14);
    glGenBuffers(1, &cubeEBO14);

    glBindVertexArray(cubeVAO14);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO14);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices14), cube_vertices14, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO14);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices14), cube_indices14, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);



    //cube 1X6-----------------------------------------------------------------------------
    float cube_vertices16[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax6, TYmin6,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin6, TYmin6,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin6, TYmax6,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax6, TYmax6,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax6, TYmin6,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax6, TYmax6,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin6, TYmin6,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin6, TYmax6,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin6, TYmin6,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax6, TYmin6,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax6, TYmax6,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin6, TYmax6,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax6, TYmin6,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax6, TYmax6,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin6, TYmax6,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin6, TYmin6,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax6, TYmin6,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax6, TYmax6,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin6, TYmax6,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin6, TYmin6,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin6, TYmin6,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax6, TYmin6,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax6, TYmax6,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin6, TYmax6
    };
    unsigned int cube_indices16[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO16, cubeVBO16, cubeEBO16;
    glGenVertexArrays(1, &cubeVAO16);
    glGenBuffers(1, &cubeVBO16);
    glGenBuffers(1, &cubeEBO16);

    glBindVertexArray(cubeVAO16);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO16);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices16), cube_vertices16, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO16);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices16), cube_indices16, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 1X6-----------------------------------------------------------------------------

    float cube_vertices101[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax10, TYmin10,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin10, TYmin10,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin10, TYmax10,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax10, TYmax10,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax10, TYmin10,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax10, TYmax10,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin10, TYmin10,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin10, TYmax10,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin10, TYmin10,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax10, TYmin10,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax10, TYmax10,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin10, TYmax10,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax10, TYmin10,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax10, TYmax10,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin10, TYmax10,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin10, TYmin10,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax10, TYmin10,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax10, TYmax10,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin10, TYmax10,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin10, TYmin10,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin10, TYmin10,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax10, TYmin10,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax10, TYmax10,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin10, TYmax10
    };
    unsigned int cube_indices101[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO101, cubeVBO101, cubeEBO101;
    glGenVertexArrays(1, &cubeVAO101);
    glGenBuffers(1, &cubeVBO101);
    glGenBuffers(1, &cubeEBO101);

    glBindVertexArray(cubeVAO101);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO101);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices101), cube_vertices101, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO101);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices101), cube_indices101, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 3X8-----------------------------------------------------------------------------

    float cube_vertices38[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax38, TYmin38,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin38, TYmin38,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin38, TYmax38,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax38, TYmax38,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax38, TYmin38,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax38, TYmax38,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin38, TYmin38,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin38, TYmax38,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin38, TYmin38,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax38, TYmin38,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax38, TYmax38,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin38, TYmax38,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax38, TYmin38,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax38, TYmax38,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin38, TYmax38,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin38, TYmin38,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax38, TYmin38,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax38, TYmax38,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin38, TYmax38,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin38, TYmin38,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin38, TYmin38,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax38, TYmin38,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax38, TYmax38,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin38, TYmax38
    };
    unsigned int cube_indices38[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO38, cubeVBO38, cubeEBO38;
    glGenVertexArrays(1, &cubeVAO38);
    glGenBuffers(1, &cubeVBO38);
    glGenBuffers(1, &cubeEBO38);

    glBindVertexArray(cubeVAO38);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO38);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices38), cube_vertices38, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO38);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices38), cube_indices38, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 2X20-----------------------------------------------------------------------------

    float cube_vertices220[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax220, TYmin220,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin220, TYmin220,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin220, TYmax220,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax220, TYmax220,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax220, TYmin220,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax220, TYmax220,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin220, TYmin220,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin220, TYmax220,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin220, TYmin220,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax220, TYmin220,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax220, TYmax220,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin220, TYmax220,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax220, TYmin220,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax220, TYmax220,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin220, TYmax220,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin220, TYmin220,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax220, TYmin220,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax220, TYmax220,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin220, TYmax220,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin220, TYmin220,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin220, TYmin220,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax220, TYmin220,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax220, TYmax220,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin220, TYmax220
    };
    unsigned int cube_indices220[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO220, cubeVBO220, cubeEBO220;
    glGenVertexArrays(1, &cubeVAO220);
    glGenBuffers(1, &cubeVBO220);
    glGenBuffers(1, &cubeEBO220);

    glBindVertexArray(cubeVAO220);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO220);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices220), cube_vertices220, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO220);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices220), cube_indices220, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);

    //cube 7X20-----------------------------------------------------------------------------

    float cube_vertices4[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax4, TYmin4,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin4, TYmin4,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin4, TYmax4,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax4, TYmax4,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax4, TYmin4,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax4, TYmax4,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin4, TYmin4,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin4, TYmax4,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin4, TYmin4,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax4, TYmin4,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax4, TYmax4,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin4, TYmax4,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax4, TYmin4,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax4, TYmax4,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin4, TYmax4,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin4, TYmin4,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax4, TYmin4,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax4, TYmax4,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin4, TYmax4,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin4, TYmin4,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin4, TYmin4,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax4, TYmin4,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax4, TYmax4,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin4, TYmax4
    };
    unsigned int cube_indices4[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cubex 7x20
    unsigned int cubeVAO4, cubeVBO4, cubeEBO4;
    glGenVertexArrays(1, &cubeVAO4);
    glGenBuffers(1, &cubeVBO4);
    glGenBuffers(1, &cubeEBO4);

    glBindVertexArray(cubeVAO4);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices4), cube_vertices4, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO4);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices4), cube_indices4, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 5X10-----------------------------------------------------------------------------

    float cube_vertices1020[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax1020, TYmin1020,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin1020, TYmin1020,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin1020, TYmax1020,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax1020, TYmax1020,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax1020, TYmin1020,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax1020, TYmax1020,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin1020, TYmin1020,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin1020, TYmax1020,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin1020, TYmin1020,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax1020, TYmin1020,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax1020, TYmax1020,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin1020, TYmax1020,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax1020, TYmin1020,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax1020, TYmax1020,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin1020, TYmax1020,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin1020, TYmin1020,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax1020, TYmin1020,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax1020, TYmax1020,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin1020, TYmax1020,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin1020, TYmin1020,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin1020, TYmin1020,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax1020, TYmin1020,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax1020, TYmax1020,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin1020, TYmax1020
    };
    unsigned int cube_indices1020[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cubex 5x10
    unsigned int cubeVAO1020, cubeVBO1020, cubeEBO1020;
    glGenVertexArrays(1, &cubeVAO1020);
    glGenBuffers(1, &cubeVBO1020);
    glGenBuffers(1, &cubeEBO1020);

    glBindVertexArray(cubeVAO1020);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO1020);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices1020), cube_vertices1020, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO1020);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices1020), cube_indices1020, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);



    //cube 7X7-----------------------------------------------------------------------------
    //0.5f
    //1.0f
    float cube_vertices5[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax5, TYmin5,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin5, TYmin5,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin5, TYmax5,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax5, TYmax5,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax5, TYmin5,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax5, TYmax5,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin5, TYmin5,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin5, TYmax5,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin5, TYmin5,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax5, TYmin5,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax5, TYmax5,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin5, TYmax5,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax5, TYmin5,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax5, TYmax5,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin5, TYmax5,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin5, TYmin5,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax5, TYmin5,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax5, TYmax5,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin5, TYmax5,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin5, TYmin5,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin5, TYmin5,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax5, TYmin5,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax5, TYmax5,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin5, TYmax5
    };
    unsigned int cube_indices5[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cubex 7x7
    unsigned int cubeVAO77, cubeVBO77, cubeEBO77;
    glGenVertexArrays(1, &cubeVAO77);
    glGenBuffers(1, &cubeVBO77);
    glGenBuffers(1, &cubeEBO77);

    glBindVertexArray(cubeVAO77);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO77);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices5), cube_vertices5, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO77);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices5), cube_indices5, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //HEXAGON------------------------------------------------------------------------------
    float hexa_vertices[] = {
        //    pos        //     normals      // texture cords
        -0.5f, 0.0f, -0.866f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,
        0.5f, 0.0f, -0.866f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,
        0.5f, 0.5f, -0.866f, 0.0f, 0.0f, -1.0f, TXmin, TYmax,
        -0.5f, 0.5f, -0.866f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,

        0.5f, 0.0f, -0.866f, 1.0f, 0.0f, -1.732f, TXmax, TYmin,
        0.5f, 0.5f, -0.866f, 1.0f, 0.0f, -1.732f, TXmax, TYmax,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.732f, TXmin, TYmin,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f, -1.732f, TXmin, TYmax,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.732f, TXmax, TYmin,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.732f, TXmax, TYmax,
        0.5f, 0.0f, 0.866f, 1.0f, 0.0f, 1.732f, TXmin, TYmin,
        0.5f, 0.5f, 0.866f, 1.0f, 0.0f, 1.732f, TXmin, TYmax,

        -0.5f, 0.0f, 0.866f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,
        0.5f, 0.0f, 0.866f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
        0.5f, 0.5f, 0.866f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
        -0.5f, 0.5f, 0.866f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

        -0.5f, 0.0f, 0.866f, -1.0f, 0.0f, 1.732f, TXmax, TYmin,
       -0.5f, 0.5f, 0.866f, -1.0f, 0.0f, 1.732f, TXmax, TYmax,
        -1.0f, 0.5f, 0.0f, -1.0f, 0.0f, 1.732f, TXmin, TYmax,
        -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.732f, TXmin, TYmin,

       -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.732f, TXmax, TYmin,
       -1.0f, 0.5f, 0.0f, -1.0f, 0.0f, -1.732f, TXmax, TYmax,
        -0.5f, 0.5f, -0.866f, -1.0f, 0.0f, -1.732f, TXmin, TYmax,
        -0.5f, 0.0f, -0.866f, -1.0f, 0.0f, -1.732f, TXmin, TYmin,

        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        0.5f, 0.5f, 0.866f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        -0.5f, 0.5f, 0.866f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        0.5f, 0.5f, -0.866f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        0.5f, 0.5f, 0.866f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        -0.5f, 0.5f, -0.866f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        0.5f, 0.5f, -0.866f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        0.5f, 0.0f, -0.866f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        -0.5f, 0.0f, -0.866f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,

        0.5f, 0.0f, 0.866f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        0.5f, 0.0f, -0.866f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,

        -0.5f, 0.0f, 0.866f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        0.5f, 0.0f, 0.866f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,
    };
    unsigned int hexa_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 11,
        11, 10, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
        
        24, 25, 26,
        26, 27, 24,

        28, 29, 30,
        30, 31, 28,

        32, 33, 34,
        34, 35, 32,

        36, 37, 38,
        38, 39, 36,

        40, 41, 42,
        42, 43, 40,

        44, 45, 46,
        46, 47, 44

    };

    //hexa
    unsigned int hexaVAO, hexaVBO, hexaEBO;
    glGenVertexArrays(1, &hexaVAO);
    glGenBuffers(1, &hexaVBO);
    glGenBuffers(1, &hexaEBO);
    glBindVertexArray(hexaVAO);
    glBindBuffer(GL_ARRAY_BUFFER, hexaVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hexa_vertices), hexa_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexaEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexa_indices), hexa_indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);




    //light's VAO
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    //Texture loading
    //Texture 0
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("transparent.png", &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture 0" << endl;
    }
    stbi_image_free(data);

    //water
    load_texture(water[0], "water1.jpg", GL_RGB);//used
    load_texture(water[1], "water2.jpg", GL_RGB);//used
    load_texture(water[2], "water3.jpg", GL_RGB);//used
    load_texture(water[3], "water4.jpg", GL_RGB);//used
    load_texture(water[4], "water5.jpg", GL_RGB);//used
    load_texture(water[5], "water6.jpg", GL_RGB);//used
    load_texture(water[6], "water7.jpg", GL_RGB);//used
    load_texture(water[7], "water8.jpg", GL_RGB);//used
    load_texture(water[8], "water9.jpg", GL_RGB);//used
    load_texture(water[9], "water10.jpg", GL_RGB);//used


    load_texture(glass, "glass1.png", GL_RGBA);//used
    load_texture(texture1, "ground_1k.jpg", GL_RGB);//used
    load_texture(texture2, "Piller_concrete_1.jpg", GL_RGB);//used
    load_texture(texture3, "golden.jpg", GL_RGB);//used


    load_texture(texture4, "Marble012_1K-JPG_Color.jpg", GL_RGB);//used
    load_texture(texture5, "balcony_tiles1.jpg", GL_RGB);//used
    load_texture(texture6, "Stripe_1.jpg", GL_RGB);//used
    load_texture(texture7, "Concrete007_1K-JPG_Color.jpg", GL_RGB);//used
    load_texture(texture8, "con07_1.jpg", GL_RGB);//used
    load_texture(texture9, "wall12.jpg", GL_RGB);
    load_texture(texture10, "ceilling_mid_870.jpg", GL_RGB);
    load_texture(texture11, "ceilling_mid_1000.jpg", GL_RGB);
    load_texture(texture12, "ceilling_mid_1282.jpg", GL_RGB);
    load_texture(texture13, "arch1.png", GL_RGBA);

    load_texture(frontwall1, "wallGG.jpg", GL_RGB);
    load_texture(frontwall2, "Blank_Wall_Pattern.jpg", GL_RGB);
    load_texture(sidewall1, "wallGG.jpg", GL_RGB);
    load_texture(sidewall2, "side_wall.jpg", GL_RGB);
    load_texture(blankwall, "square_wall.jpg", GL_RGB);
    load_texture(mehrab, "MehrabGG.jpg", GL_RGB);
    load_texture(mehrabside, "MehrabGGSide.jpg", GL_RGB);

    load_texture(t_door, "Tdoor.jpg", GL_RGB);
    load_texture(t_floor, "Toilet_floor.jpg", GL_RGB);
    load_texture(wodden, "wood.jpg", GL_RGB);
    load_texture(side_door, "Side_Door.jpg", GL_RGB);

    //load_texture(metal_dome, "metal.jpg", GL_RGB);
    load_texture(metal_tape, "Metal_2.jpg", GL_RGB);
    load_texture(flu, "flush.jpg", GL_RGB);

    load_texture(leftDoor, "leftdoor.jpg", GL_RGB);
    load_texture(rightDoor, "Right_door.jpg", GL_RGB);
    load_texture(ac, "ac.jpg", GL_RGB);
    load_texture(acflap, "ac_flap.jpg", GL_RGB);

    load_texture(win_frame, "win_frame_rev.png", GL_RGBA);
    load_texture(win_left, "win_win.png", GL_RGBA);
    load_texture(win_right, "win_win.png", GL_RGBA);
    load_texture(main_glass, "Main_Glasssss.png", GL_RGBA);

    load_texture(al, "al.jpg", GL_RGB);
    load_texture(al_books, "al_books.png", GL_RGBA);
    load_texture(al_door1, "al_door_2.jpg", GL_RGB);
    load_texture(al_door2, "al_door_1.jpg", GL_RGB);
    load_texture(low_com, "low_com.jpg", GL_RGB);


    //Curves
    //Fan_bati
    GLfloat cp_Fan_Bati[] = {
        0.0, 0.476, 0.0,
        -0.64, 0.455, 0.0,
        -0.727, 0.305, 0.0,
        -0.64, 0.113, 0.0,
        0.0, 0.0, 0.0
    };

    BezierCurve Fan_Bati = BezierCurve(cp_Fan_Bati, 15, texture3);
    //Fan_Blade
    GLfloat cp_Fan_Blade[] = {
        0.0, 1.945, 0.0,
        -0.071, 1.93, 0.0,
        -0.1395, 1.9245, 0.0,
        -0.1834, 1.889, 0.0,
        -0.1958, 1.842, 0.0,
        -0.415, 0.264, 0.0,
        -0.425, 0.128, 0.0,
        -0.383, 0.0543, 0.0,
        0.0, 0.0, 0.0
    };
    BezierCurve Fan_Blade = BezierCurve(cp_Fan_Blade, 27, texture13);

    //FAN_TUBE
    GLfloat cp_Fan_Tube[] = {
    -0.1395, 1.9245, 0.0,
    -0.1395, 0.0, 0.0
    };
    BezierCurve Fan_Tube = BezierCurve(cp_Fan_Tube, 6, texture3);

    //Common Arch***************************************************
    //main arch
        GLfloat cp_Main_Arch[] = {
            -0.001, 1.01, 0.0,
            -0.29, 0.755, 0.0,
            -0.725, 0.74,0.0,
            -0.89, 0.0, 0.0
            //-0.71, 0.07, 0.0,
            //-0.42, 0.0, 0.0
        };
        BezierCurveArch Main_Arch = BezierCurveArch(cp_Main_Arch, 4*3, texture4, 1.0);
     //sub arch
     GLfloat cp_Sub_Arch[] = {
        -0.0001, 0.71, 0,
        -0.4801, 0.64, 0,
        -0.7451, 0.35, 0,
        -0.7651, 0, 0
        };
        BezierCurveArch Sub_Arch = BezierCurveArch(cp_Sub_Arch, 4*3, texture13,1.0);
        //round piller
        GLfloat cp_Round_Piller[] = {
           -0.5,1.0,0.0,
           -0.5,0.0,0.0
        };
        BezierCurve Round_Piller = BezierCurve(cp_Round_Piller, 2*3, texture2);
        //round piller 22
        BezierCurve Round_Piller2 = BezierCurve(cp_Round_Piller, 2 * 3, metal_tape);
        //piller_nicher_border
        BezierCurve AC_Round_Piller = BezierCurve(cp_Round_Piller, 2 * 3, texture8);
        GLfloat cp_Piller_Border[] = {
            -0.03, 0.43, 0,
            -0.31, 0.44, 0,
            -0.675, 0.435, 0,
            -0.74, 0.375, 0,
            -0.78, 0.105, 0,
            -0.72, 0.03, 0,
            -0.57, 0.015, 0,
            -0.35, 0, 0,
            -0.12, 0, 0
        };
        BezierCurve Piller_Border = BezierCurve(cp_Piller_Border, 9*3, texture2);

        ///MINAR
                //round piller
        GLfloat cp_circle[] = {
            -0.0301, 1.645, 0,
            -0.7301, 1.595, 0,
            -1.0801, 1.35, 0,
            -1.2701, 1.05, 0,
            -1.3051, 0.715, 0,
            -1.2701, 0.365, 0,
            -1.1601, 0.165, 0,
            -0.9301, 0.085, 0,
            -0.6751, 0.04, 0,
            -0.4101, 0, 0,
            -0.1651, 0, 0,
            -0.0001, 0, 0
        };
        BezierCurve circle = BezierCurve(cp_circle, 12 * 3, texture0);
        //piller_nicher_border
        GLfloat cp_spike[] = {
            -0.0451, 1.745, 0,
            -0.4651, 0.13, 0,
            -0.3501, 0.01, 0,
            -0.0001, 0, 0
        };
        BezierCurve spike = BezierCurve(cp_spike, 4 * 3, texture3);
        BezierCurve spike2 = BezierCurve(cp_spike, 4 * 3, water[0]);

        //2nd circle
        GLfloat cp_circle1[] = {
            -0.0001, 1.645, 0,
            -0.1901, 1.35, 0,
            -0.6301, 1.26, 0,
            -1.0101, 1.17, 0,
            -1.3001, 0.855, 0,
            -1.2701, 0.25, 0,
            -0.8951, 0, 0,
        };
        BezierCurve circle1 = BezierCurve(cp_circle1, 7 * 3, texture0);//tex8

        //HEXA
        //round piller
        GLfloat cp_Round_Piller_Hexa[] = {
           -0.5,1.0,0.0,
           -0.5,0.0,0.0
        };
        Hexa Round_Piller_Hexa = Hexa(cp_Round_Piller_Hexa, 2 * 3, texture2);

    // render loop
    // -----------

        Sphere sphere = Sphere();

        //config transfer shader
         // For window shader config
        TransparentShader.use();
        TransparentShader.setInt("texture1", 0);



    // VAO and VBO setup
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    float branchVertices[] = {
        // Positions           // Texture Coords
        -0.05f,  0.0f, 0.0f,   0.0f, 0.0f,  // Bottom Left
        0.05f,  0.0f, 0.0f,   1.0f, 0.0f,  // Bottom Right
        0.05f,  1.0f, 0.0f,   1.0f, 1.0f,  // Top Right

        -0.05f,  0.0f, 0.0f,   0.0f, 0.0f,  // Bottom Left
        0.05f,  1.0f, 0.0f,   1.0f, 1.0f,  // Top Right
        -0.05f,  1.0f, 0.0f,   0.0f, 1.0f   // Top Left
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(branchVertices), branchVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // ********************************************************activate Our Main shader*****************************************************************
        ourShader.use();
        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        ourShader.setMat4("projection", projection);//vertex shader e
        ourShader.setMat4("view", view);//vertex shader e


        //**************lighting**************

     //Setting up Directional Light
        directionalLight.setUpLight(ourShader);
        if (!directionalLightOn)
            directionalLight.turnOff();
        if (!ambientOn)
            directionalLight.turnAmbientOff();
        if (!diffuseOn)
            directionalLight.turnDiffuseOff();
        if (!specularOn)
            directionalLight.turnSpecularOff();

        //Setting up Point Light
        SetupPointLight(pointLight1, ourShader, 1);
        SetupPointLight(pointLight2, ourShader, 2);
        SetupPointLight(pointLight3, ourShader, 3);
        SetupPointLight(pointLight4, ourShader, 4);
        SetupPointLight(pointLight5, ourShader, 5);
        SetupPointLight(pointLight6, ourShader, 6);
        SetupPointLight(pointLight7, ourShader, 7);
        SetupPointLight(pointLight8, ourShader, 8);
        SetupPointLight(pointLight9, ourShader, 9);
        SetupPointLight(pointLight10, ourShader, 10);
        SetupPointLight(pointLight11, ourShader, 11);
        SetupPointLight(pointLight12, ourShader, 12);
        SetupPointLight(pointLight13, ourShader, 13);
        SetupPointLight(pointLight14, ourShader, 14);
        SetupPointLight(pointLight15, ourShader, 15);
        SetupPointLight(pointLight16, ourShader, 16);
        SetupPointLight(pointLight17, ourShader, 17);
        SetupPointLight(pointLight18, ourShader, 18);
        SetupPointLight(pointLight19, ourShader, 19);
        SetupPointLight(pointLight20, ourShader, 20);
        SetupPointLight(pointLight21, ourShader, 21);
        SetupPointLight(pointLight22, ourShader, 22);
        SetupPointLight(pointLight23, ourShader, 23);
        SetupPointLight(pointLight24, ourShader, 24);
        SetupPointLight(pointLight25, ourShader, 25);
        SetupPointLight(pointLight26, ourShader, 26);
        SetupPointLight(pointLight27, ourShader, 27);
        SetupPointLight(pointLight28, ourShader, 28);
        SetupPointLight(pointLight29, ourShader, 29);
        SetupPointLight(pointLight30, ourShader, 30);
        SetupPointLight(pointLight31, ourShader, 31);
        SetupPointLight(pointLight32, ourShader, 32);
        SetupPointLight(pointLight33, ourShader, 33);
        SetupPointLight(pointLight34, ourShader, 34);
        SetupPointLight(pointLight35, ourShader, 35);
        SetupPointLight(pointLight36, ourShader, 36);

        //Setting up Spot Light
        spotLight.setUpLight(ourShader);
        if (!spotLightOn)
            spotLight.turnOff();
        if (!ambientOn)
            spotLight.turnAmbientOff();
        if (!diffuseOn)
            spotLight.turnDiffuseOff();
        if (!specularOn)
            spotLight.turnSpecularOff();

        //Camera and Others
        ourShader.setVec3("viewPos", camera.Position);//fragment  shader e
        ourShader.setBool("lightingOn", lightingOn);//fragment shader e

        //cout << camera.Position[0] << " " << camera.Position[1] << " " << camera.Position[2] << endl;
        //glBindVertexArray(cubeVAO);//by default cubeVAO


        //creating objects
        glActiveTexture(GL_TEXTURE0);

        //testing--------------------------------------------------curve
        float x_shift = 0;
        float y_shift = 0;
        float z_shift = 0;
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
        //universal translate
        uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
        model = uni_translate * translateMatrix * scaleMatrix;
        //circle1.drawBezierCurve(ourShader, model);
        //testing end--------------------------------------------------------------eurve


        //2nd floor Railling****************************************************
        //railling olta L
        x_shift = 32.9;
        y_shift = 4.8;
        z_shift = 60.6;
        for (int i = 0; i < 11; i++)
        {
            RaillingUnit(cubeVAO, Round_Piller, ourShader, x_shift, y_shift, z_shift-i*0.92);
        }
        for (int i = 1; i < 11; i++)
        {
            RaillingUnit(cubeVAO, Round_Piller, ourShader, x_shift + i * 0.92, y_shift, z_shift);
        }

        //Railing L
        x_shift = 42.1;
        y_shift = 4.8;
        z_shift = 51.4;
        for (int i = 0; i < 11; i++)
        {
            RaillingUnit(cubeVAO, Round_Piller, ourShader, x_shift, y_shift, z_shift + i * 0.92);
        }
        for (int i = 1; i < 11; i++)
        {
            RaillingUnit(cubeVAO, Round_Piller, ourShader, x_shift - i * 0.92, y_shift, z_shift);
        }
        float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
        float len = 0.0f, width = 0.0f, height = 0.0f;
        
        //front dondo++++++++++++++++++++
        x_shift = 32.86;
        y_shift = 4.8 + 0.42;
        z_shift = 51.4;
        len = 9.28f, width = 0.1f, height = 0.05f;
        local_x = 0.0, local_y = 0.0f, local_z = -0.05f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
        
        //back dondo++++++++++++++++++++
        x_shift = 32.86;
        y_shift = 4.8 + 0.42;
        z_shift = 60.6;
        len = 9.28f, width = 0.1f, height = 0.05f;
        local_x = 0.0, local_y = 0.0f, local_z = -0.05f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
        
        //left dondo++++++++++++++++++++
        x_shift = 42.1;
        y_shift = 4.8 + 0.42;
        z_shift = 51.36;
        len = 0.1f, width = 9.28f, height = 0.05f;
        local_x = -0.05, local_y = 0.0f, local_z = 0.0f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
        
        //right dondo++++++++++++++++++++
        x_shift = 32.9;
        y_shift = 4.8 + 0.42;
        z_shift = 51.36;
        len = 0.1f, width = 9.28f, height = 0.05f;
        local_x = -0.05, local_y = 0.0f, local_z = 0.0f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
        //2nd floor Railling END****************************************************
        
        
        x_shift = 20.0;
        y_shift = 4.8;
        z_shift = 66.3;
        Almari_2_2(cubeVAO, ourShader, x_shift, y_shift, z_shift);
        
        x_shift = 55.0;
        y_shift = 4.8;
        z_shift = 66.3;
        Almari_1_2(cubeVAO, ourShader, x_shift, y_shift, z_shift);

        
        ///

        glm::mat4 modell = glm::mat4(1.0f);
        modell = glm::translate(modell, glm::vec3(37.0f, 1.0f, -27.0f)); // Start from bottom

        drawBranch(ourShader, modell, 5); // Recursion depth

        glfwSwapBuffers(window);
        glfwPollEvents();


        //FAN1
        x_shift = 24;
        y_shift = 4.3;
        z_shift = 0;
        for (int i = 0; i < 2; i++)
        {
            Fan_and_switch(cubeVAO, Fan_Bati, Fan_Blade, Fan_Tube, ourShader, x_shift + 27.0 * i, y_shift, 59.0);
            Fan_and_switch(cubeVAO, Fan_Bati, Fan_Blade, Fan_Tube, ourShader, x_shift + 27.0 * i, y_shift, 49.0);
        }

        //FAN2
        x_shift = 24;
        y_shift = 8.25;
        z_shift = 0;
        for (int i = 0; i < 2; i++)
        {
            Fan_and_switch(cubeVAO, Fan_Bati, Fan_Blade, Fan_Tube, ourShader, x_shift + 27.0 * i, y_shift, 57.0);
            Fan_and_switch(cubeVAO, Fan_Bati, Fan_Blade, Fan_Tube, ourShader, x_shift + 27.0 * i, y_shift, 49.0);
        }
        
        //jharbati
        x_shift = 37.5;
        y_shift = 3.5;
        z_shift = 56;
        jharbati(cubeVAO, Round_Piller, ourShader, x_shift, y_shift, z_shift);

        

        //MAIN DOOR
        x_shift = 34.5;
        y_shift = 0.45;
        z_shift = 43;
        DoubleDoors(cubeVAO,ourShader, x_shift,  y_shift,  z_shift,  texture1, texture1);

        //side door1
        x_shift = 15.4;
        y_shift = 0.0;
        z_shift = 58;
        SideDoor1(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture1);

        //side door2
        x_shift = 59.3;
        y_shift = 0.0;
        z_shift = 58.0;
        SideDoor2(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture1);


        //Imam
        x_shift = 37.0;
        y_shift = 0.4;
        z_shift = 68.5;
        imam_Place(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture1);

        //book shef
        x_shift = 24.0;
        y_shift = 0.6;
        z_shift = 67.8;
        bookshef(cubeVAO, ourShader, x_shift, y_shift, z_shift, wodden);
        
        //book shef
        x_shift = 51.0;
        y_shift = 0.6;
        z_shift = 67.8;
        bookshef(cubeVAO, ourShader, x_shift, y_shift, z_shift, wodden);

        //Mid ARC
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        MidArchGen(cubeVAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);

        //Grass Field------------------------------************************
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        Field(cubeVAO77, ourShader, x_shift, y_shift, z_shift, texture1);

        //Main Mosjid+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //Mosjid base
        x_shift = 15.5;
        y_shift = 0.2;
        z_shift = 43;
        MainMosjidBase(cubeVAO4, cubeVAO, cubeVAO4 , ourShader, x_shift, y_shift, z_shift, texture4, texture4, texture5);

        //Mosjid 1st floor-----------------------------------------------------------------------------------------
        x_shift = 0;
        y_shift = 0.2;
        z_shift = 0;
        Mosjid1stFloor(cubeVAO, cubeVAO2, cubeVAO3, cubeVAO14, ourShader, x_shift, y_shift, z_shift, texture3);
        //Mosjid 2nd floor------------------------------------------------------------------------------------------
        x_shift = 0;
        y_shift = 0.2;
        z_shift = 0;
        Mosjid2ndFloor(cubeVAO, cubeVAO2, cubeVAO3, cubeVAO14, cubeVAO220, cubeVAO38,ourShader, x_shift, y_shift, z_shift, texture3);///till now

        //Mid main gate
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        MidGate(cubeVAO, cubeVAO1020, cubeVAO16, ourShader, x_shift, y_shift, z_shift, texture7);


        //Stair tower
        //Left tower
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        StairTower1(cubeVAO, Round_Piller, ourShader, x_shift, y_shift, z_shift, texture0 );
       
        //siri railing down
        x_shift = 13.0;
        y_shift = 0.2 + 0.7;
        z_shift = 61.8;
        len = -3.5f, width = 0.1f, height = 0.08f;
        local_x = 0.00, local_y = -0.04f, local_z = -0.05f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, -33.69f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
        
        //siri railing up
        x_shift = 10.0;
        y_shift = 2.4 + 0.7;
        z_shift = 61.2;
        len = 3.5f, width = 0.1f, height = 0.08f;
        local_x = 0.00, local_y = -0.04f, local_z = -0.05f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 33.69f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
        
        //siri 2nd floor railing
        x_shift = 13.0+0.15;
        y_shift = 4.7+0.5;
        z_shift = 59.5+2.1;
        len = 0.1f, width = 1.7f, height = 0.08f;
        local_x = -0.05, local_y = 0.0f, local_z = -0.05f;
        GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);

        
        //domes
        //mid
        x_shift = 22.0;
        y_shift = 3.0;
        z_shift = 39.5;
        for (int i = 0; i < 2; i++)
        {
            small_dome(cubeVAO, circle, spike, ourShader, x_shift + 6.0 * i, y_shift, z_shift);
            small_dome(cubeVAO, circle, spike, ourShader, x_shift + 29.5 + 6.0 * i, y_shift, z_shift);
        }
       
       for (int i = 0; i < 2; i++)
       {
           mid_dome(cubeVAO, circle1, spike, ourShader, 24.2 + 26.8*i, 8.2, 56);
       }
       x_shift = 37.5;
       y_shift = 8.2;
       z_shift = 56.0;
       Big_dome(cubeVAO, circle1, spike, ourShader, x_shift, y_shift,  z_shift);

       //door frame
       x_shift = 24.0;
       y_shift = 0.4;
       z_shift = 43.0;
       Glass_Door_Frame_1_1(cubeVAO, ourShader, x_shift, y_shift, z_shift);
       
       //door frame
       x_shift = 48.0;
       y_shift = 0.4;
       z_shift = 43.0;
       Glass_Door_Frame_1_2(cubeVAO, ourShader, x_shift, y_shift, z_shift);


       //win frame 2_1
       x_shift = 24.0;
       y_shift = 5.2;
       z_shift = 45.0;
       Glass_win_Frame_2_1(cubeVAO, ourShader, x_shift, y_shift, z_shift);
       //win frame 2_2
       x_shift = 48.0;
       y_shift = 5.2;
       z_shift = 45.0;
       Glass_win_Frame_2_2(cubeVAO, ourShader, x_shift, y_shift, z_shift);
       //win frame 2_3
       x_shift = 24.0;
       y_shift = 5.2;
       z_shift = 67.0;
       Glass_win_Frame_2_3(cubeVAO, ourShader, x_shift, y_shift, z_shift);
       //win frame 2_4
       x_shift = 48.0;
       y_shift = 5.2;
       z_shift = 67.0;
       Glass_win_Frame_2_4(cubeVAO, ourShader, x_shift, y_shift, z_shift);

       //Lighter dori
       for (int i = 28; i < 28 + 8; i++)
       {
           glm::vec3 gg = lightPositions[i];
           x_shift = gg[0];
           y_shift = gg[1];
           z_shift = -1.0*gg[2];
           len = 0.05f, width = 0.05f, height = 0.2f;
           local_x = -0.025, local_y = 0.0f, local_z = -0.025f;
           GenSheet(cubeVAO, ourShader, len, width, height, local_x, local_y, local_z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, x_shift, y_shift, z_shift, off_white, wodden);
       }
      

       

       //********* END of Object Making **********
       // ********************************************************End of Our Main shader*****************************************************************

       //*********************************************************Activate LightsShader******************************************************************
       lightCubeShader.use();
       glm::mat4 projection1 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
       glm::mat4 view1 = camera.GetViewMatrix();
       lightCubeShader.setMat4("projection", projection1);
       lightCubeShader.setMat4("view", view1);



       scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.13f, 0.1f, 0.13f));
       for (int i = 1; i <= noOfPointLights+1; i++)
       {
           glm::vec4 bodyColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
           //emissive
           glm::vec3 val = glm::vec3(0.5f);
           if (i < noOfPointLights and pointLightOn[i-1] == 0.0)
               bodyColor = glm::vec4(val, 1.0f);
           if (i == noOfPointLights+1 and spotLightOn == 0.0)
               bodyColor = glm::vec4(val, 1.0f);

           lightCubeShader.setVec4("bodyColor", bodyColor);
           glm::mat4 tempModel = glm::mat4(1.0f);
           tempModel = glm::translate(tempModel, lightPositions[i]);
           lightCubeShader.setMat4("model", tempModel * scaleMatrix);
           sphere.drawSphere(lightCubeShader);
       }

       //**************************************************************END Of LightShader*********************************************************************
       
       //*************************************************************Transparent Shader**********************************************************************
       TransparentShader.use();
       glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
       glm::mat4 view2 = camera.GetViewMatrix();
       TransparentShader.setMat4("projection", projection2);
       TransparentShader.setMat4("view", view2);

       glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

       //doors
       x_shift = 24.0;
       y_shift = 0.4;
       z_shift = 43.0;
       Glass_Door_1_1(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);
       
       x_shift = 48.0;
       y_shift = 0.4;
       z_shift = 43.0;
       Glass_Door_1_2(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);

       //win
       //2-1
       x_shift = 24.0;
       y_shift = 5.0;
       z_shift = 45.0;
       Glass_win_2_1(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);
       
       //2-2
       x_shift = 48.0;
       y_shift = 5.0;
       z_shift = 45.0;
       Glass_win_2_2(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);
       
       //2-3
       x_shift = 24.0;
       y_shift = 5.0;
       z_shift = 67.0;
       Glass_win_2_3(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);
       
       //2-4
       x_shift = 48.0;
       y_shift = 5.0;
       z_shift = 67.0;
       Glass_win_2_4(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);

       //Lift and stairs
       x_shift = 0.0;
       y_shift = 0.0;
       z_shift = 0.0;
    //    Stairs_Lift_Glass(transparentVAO, TransparentShader, x_shift, y_shift, z_shift);

       glDisable(GL_BLEND);

       //*************************************************************End of Transparent Shader**********************************************************************
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &lightCubeVAO);

    glDeleteVertexArrays(1, &transparentVAO);
    glDeleteBuffers(1, &transparentVBO);

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    glDeleteVertexArrays(1, &cubeVAO2);
    glDeleteBuffers(1, &cubeVBO2);
    glDeleteBuffers(1, &cubeEBO2);

    glDeleteVertexArrays(1, &cubeVAO3);
    glDeleteBuffers(1, &cubeVBO3);
    glDeleteBuffers(1, &cubeEBO3);


    glDeleteVertexArrays(1, &cubeVAO4);
    glDeleteBuffers(1, &cubeVBO4);
    glDeleteBuffers(1, &cubeEBO4);

    glDeleteVertexArrays(1, &cubeVAO77);
    glDeleteBuffers(1, &cubeVBO77);
    glDeleteBuffers(1, &cubeEBO77);

    glDeleteVertexArrays(1, &cubeVAO16);
    glDeleteBuffers(1, &cubeVBO16);
    glDeleteBuffers(1, &cubeEBO16);

    glDeleteVertexArrays(1, &cubeVAO14);
    glDeleteBuffers(1, &cubeVBO14);
    glDeleteBuffers(1, &cubeEBO14);


    glDeleteVertexArrays(1, &cubeVAO38);
    glDeleteBuffers(1, &cubeVBO38);
    glDeleteBuffers(1, &cubeEBO38);


    glDeleteVertexArrays(1, &cubeVAO220);
    glDeleteBuffers(1, &cubeVBO220);
    glDeleteBuffers(1, &cubeEBO220);

    glDeleteVertexArrays(1, &cubeVAO101);
    glDeleteBuffers(1, &cubeVBO101);
    glDeleteBuffers(1, &cubeEBO101);

    glDeleteVertexArrays(1, &cubeVAO1020);
    glDeleteBuffers(1, &cubeVBO1020);
    glDeleteBuffers(1, &cubeEBO1020);


    glDeleteVertexArrays(1, &hexaVAO);
    glDeleteBuffers(1, &hexaVBO);
    glDeleteBuffers(1, &hexaEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void SetupPointLight(PointLight& pointLight, Shader ourShader, int lightNum)
{
    pointLight.setUpLight(ourShader);
    if (!pointLightOn[pointLight.lightNumber - 1])
        pointLight.turnOff();
    if (!ambientOn)
        pointLight.turnAmbientOff();
    if (!diffuseOn)
        pointLight.turnDiffuseOff();
    if (!specularOn)
        pointLight.turnSpecularOff();
}

//Texture Loading function
void load_texture(unsigned int& texture, string image_name, GLenum format)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture " << image_name << endl;
    }
    stbi_image_free(data);
}

void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); 
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.25f + 0.45f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.3f, 0.1f, 40.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Field(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift,  y_shift, -1.0f *z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(75.0f, 0.1f, -75.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0,1.0,1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void MainMosjidBase(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1 = texture0, unsigned int texture2 = texture0, unsigned int texture3 = texture0)
{
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++MAIN FLOOR
    float lbx = 0.0, lby = 0.0f, lbz = 0.0f;
    float len = 44.0;
    float width = 25.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture1);
    //imam box floor+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 20.3, lby = 0.0f, lbz = 25.0f;
    len = 3.4;
    width = 2.0;
    GenFloor(VAO2, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture2);

    //main floor box tex+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 0.5, lby = 0.01f, lbz = 0.5f;
    len = 43;
    width = 24;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture3);

}


void Mosjid1stFloor(unsigned int VAO1, unsigned int VAO2 , unsigned int VAO3, unsigned int VAO14, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //roof box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 15.5, lby = 2.7f + 0.2f, lbz = 43.0f;
    float len = 44.0, ht = 1.7f;
    float width = 25.0;
    HoloBox(VAO14, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);//1x3
    //roof mid left
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 51.0f;
    len = 16.8, width = 10.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof mid right
    //(ht + lby) - 0.2f,
    lbx = 42.5, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 51.0f;
    len = 16.8, width = 10.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof front
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 43.2f;//1x3
    len = 43.6, width = 7.8f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture11);//1x3
    //roof back
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 61.0f;
    len = 43.6, width = 6.8f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture10);//1x3


    //front left wall-----------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2f, lbz = 43.0f;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //front mid left wall
    lbx = 27.0, lby = 0.2f, lbz = 43.0f;
    len = 7.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1
    //front mid right wall
    lbx = 40.5, lby = 0.2f, lbz = 43.0f;
    len = 7.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1
    //front right wall
    lbx = 51.0, lby = 0.2f, lbz = 43.0f;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //back left wall--------------------
    lbx = 15.5, lby = 0.2f, lbz = 67.8f;
    len = 20.5, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture9);//1x3

    //back right wall
    lbx = 39.0, lby = 0.2f, lbz = 67.8f;
    len = 20.5, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture9);//1x3

    //right side front wall-----------------+++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2f, lbz = 43.0f;
    len = 11.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1
    //right side back wall
    lbx = 15.5, lby = 0.2f, lbz = 58.0f;
    len = 10.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //left side front wall-----------------
    lbx = 59.3, lby = 0.2f, lbz = 43.0f;
    len = 11.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //left side back wall
    lbx = 59.3, lby = 0.2f, lbz = 58.0f;
    len = 10.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //imam place=====================
    //left wall
    lbx = 35.8, lby = 0.2f, lbz = 67.8f;
    len = 2.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, mehrabside);//1x1
    //right wall
    lbx = 39.0, lby = 0.2f, lbz = 67.8f;
    len = 2.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, mehrabside);//1x1
    //back wall
    lbx = 35.8, lby = 0.2f, lbz = 69.8f;
    len = 3.4, ht = 2.7f;
    HorizontalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, mehrab);//1x1
    //top box
    lbx = 35.8, lby = 2.7f+0.2f, lbz = 67.8f;
    len = 3.4, ht = 1.0f;
    width = 2.2;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);//1x1
}

void Mosjid2ndFloor(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, unsigned int VAO14, unsigned int VAO220, unsigned int VAO38, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //roof box-------------------------------------------------------Not FLat
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 15.5, lby = 6.8f + 0.2f, lbz = 45.0f;
    float len = 44.0, ht = 1.8f;
    float width = 22.0;
    HoloBox(VAO14, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);//1x3
    //ROOF TOP************************************************
    //roof Front
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x3
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x1
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x1
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x3

    //ROOF BOTTOM************************************************
    //roof Front
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f -.01) - 0.4f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture11);//1x3
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f - .01) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.8f + 6.8f + 0.2f - .01) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f - .01) - 0.4f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture10);//1x3

    //FLOOR TOP************************************************
   //roof Front
   //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f+0.01) - 0.2f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO220, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//2x220
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f + 0.01) - 0.2f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO38, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//3x8
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.7f + 2.7f + 0.2f + 0.01) - 0.2f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO38, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//3x8
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f + 0.01) - 0.2f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO220, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//2x20

    //front left wall-----------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //front mid wall
    lbx = 27.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 21, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2
    //front right wall
    lbx = 51.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //back left wall--------------------
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //back MID wall--------------------
    lbx = 27.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 21.0, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x2

    //back right wall
    lbx = 51.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //right side front wall-----------------+++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 15.0, ht = 2.7f;
    VerticalWall(VAO3, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2

    //right side back wall
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 63.0;
    len = 4.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //left side front wall-----------------
    lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0f;
    len = 22.0, ht = 2.7f;
    VerticalWall(VAO3, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2

    // lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 55.0f;
    // len = 10.0, ht = 2.7f;
    // VerticalWall(VAO3, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2

    // //left side back wall
    // lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 63.0f;
    // len = 4.0, ht = 2.7f;
    // VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1


}

void MidGate(unsigned int VAO1, unsigned int VAO1020, unsigned int VAO16, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 31.5f, lby = 0.2f, lbz = 35.5f;
    float len = 2.0, ht = 5.0;
    float width = len;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 41.5f, lby = 0.2f, lbz = 35.5f;
    len = 2.0, ht = 5.0;
    width = len;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //Mid Gate main box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 32.0, lby = 2.7f + 0.2f, lbz = 36.0f;
    len = 11.0, ht = 1.9f;
    width = 7.0;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);
     

    //Left wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 37.5f;
    len = 18, ht = 1.0f;
    width = 4.0;
    Box(VAO1, VAO16, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);

    //right wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0, lby = 2.7f + 0.2f, lbz = 37.5f;
    len = 18, ht = 1.0f;
    width = 4.0;
    Box(VAO1, VAO16, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);
   
    //Chipa wallllllllllllllllllll---------------------------------------=-
    //front left chipa wall
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 41.5f;
    len = 18.0;
    width = 1.5;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //front right chipa wall
    lbx = 43.0, lby = 2.7f + 0.2f, lbz = 41.5f;
    len = 18.0;
    width = 1.5;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width,  lbx, lby, lbz, texture4);


    //left side chipa wall
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 43.0f;
    len = 1.5f;
    width = 15.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //right side chipa wall
    lbx = 59.5, lby = 2.7f + 0.2f, lbz = 43.0f;
    len = 1.5f;
    width = 15.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);


    //FLOORS ***********
     //Left wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.01f, lbz = 37.5f;
    len = 17.5;
    width = 4.0;
    GenFloor(VAO16,ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);

    //right wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.5, lby = 0.01, lbz = 37.5f;
    len = 17.5f;
    width = 4.0;
    GenFloor(VAO16, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);

    //MID FLOOR_+_+_+_+_+
//box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 31.5, lby = 0.02, lbz = 35.5f;
    len = 12.0f;
    width = 7.5;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //MAIN OUTSIDE TILES FLLOR
    lbx = 14.25, lby = 0.005, lbz = 16.25f;
    len = 46.5;
    width = 21;
    // GenFloor(VAO1020, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture8);
    
    static bool initialized = false;
    if (!initialized) {
        fountain.setupSphere();
        initialized = true;
    }

    updateScene(deltaTime);
    renderScene(ourShader);

 /*   POND 
    HOLO BOX*/
    lbx = 34.5, lby = 0.0, lbz = 23.75;
    len = 6.0;
    width = 6.0;
    ht = 0.8;
    HoloBox(VAO16, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture8);
    //Water
    lbx = 34.7, lby = 0.4, lbz = 23.95;
    len = 6.0-0.4;
    width = 6.0 - 0.4;;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, water[wcnt/10]);
    wcnt++;
    wcnt = wcnt % 100;
}

void StairTower1(unsigned int VAO, BezierCurve Round_Piller, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 8.5f, lby = 0.2f, lbz = 58.0f;
    float len = 1.5, ht = 8.2;
    float width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, blankwall);

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5f, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, blankwall);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 58.0f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, blankwall);

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, blankwall);

    //main box tower-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 6.8f + 0.2f, lbz = 58.0f;
    len = 7.0, ht = 1.0f;
    width = 7.0;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);

    //2ND FLOOR STAIR FLOOR
    lbx = 13.0, lby = 4.6-0.2, lbz = 59.5;
    len = 2.5;
    width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);
    for (int i = 0; i < 5; i++)
    {
        RaillingUnit(VAO, Round_Piller, ourShader, lbx + x_shift + .15 , lby + y_shift + 0.2, lbz + z_shift + 2.1 + i* 0.4 );
    }

    //bottom stairs
    lbx = 12.7, lby = 0.2, lbz = 61.7;
    len = 0.3;
    width = 1.8;
    for (int i = 0; i < 10; i++)
    {
        GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx - i*0.3, lby+i*0.2, lbz, texture4);
        RaillingUnit(VAO, Round_Piller, ourShader, lbx+x_shift +0.15 - i * 0.3, lby+y_shift+0.2 + i * 0.2, lbz+z_shift+0.1);
    }
    //half talar floor
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 2.2, lbz = 59.5;
    len = 1.5;
    width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //top stairs
    lbx = 10.0, lby = 2.4, lbz = 59.5;
    len = 0.3;
    width = 1.8;
    for (int i = 0; i < 10; i++)
    {
        GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx + i * 0.3, lby + i * 0.2, lbz, texture4);
        RaillingUnit(VAO, Round_Piller, ourShader, lbx + x_shift + 0.15 + i * 0.3, lby + y_shift + 0.2 + i * 0.2, lbz + z_shift + 1.8 - 0.1);
    }

    //front mid box
    lbx = 10.0, lby = 2.2, lbz = 58.0f;
    len = 4.0, ht = 1.7f;
    width = 1.5;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);

    //left mid box
    lbx = 8.5, lby = 0.2, lbz = 59.5f;
    len = 1.5, ht = 2.0f;
    width = 4.0;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);

    //back mid box
    lbx = 10.0, lby = 0.2, lbz = 63.5f;
    len = 4.0, ht = 3.7f;
    width = 1.5;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);
}

void MidArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;

    //LEFT FRONT BALCONY
    //left box single arch
    float zz = 4.0 - 0.2;
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);
    lbx = -1.5, lby = 0.0, lbz = 25.5;

    //common arch
    for (int i = 0; i < 5; i++)
    {
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, lbx + i * 2.6, lby, lbz);
        //Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift + i * 2.6, y_shift, z_shift + zz);
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);

    //RIGHT FRONT BALCONY
    //left box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    /*Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);*/
    lbx = -1.5, lby = 0.0, lbz = 25.5;
    //common arch
    float right_displace = 29.5;
    for (int i = 0; i < 5; i++)
    {
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, lbx + right_displace + i * 2.6, lby, lbz);
        //Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift + right_displace + i * 2.6, y_shift, z_shift + zz);
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);


}


void Almari_1_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_Almari_1_2 += 0.5;
        
        // Ensure the value does not exceed 100.0
        if (rotateAxis_Y_Almari_1_2 > 100.0) {
            rotateAxis_Y_Almari_1_2 = 100.0;
        }
    } 
    else {
        rotateAxis_Y_Almari_1_2 -= 0.5;
        
        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_Almari_1_2 < 0.0) {
            rotateAxis_Y_Almari_1_2 = 0.0;
        }
    }

    cout << " almari " << rotateAxis_Y_Almari_1_2 << endl;
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left Door*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_Almari_1_2, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 1.0f, width = 0.05f, height = 2.0f;
    local_x = 0.0, local_y = 0.2f, local_z = 0.0f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, al_door1);
    //*************************************END of left Door***************************


    //**************************************Right Door*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_Almari_1_2, rot_z = 0.0f;
    trans_x = -2.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 1.0f, width = 0.05f, height = 2.0f;
    local_x = 1.0, local_y = 0.2f, local_z = 0.0f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, al_door2);
    //**************************************End of Right Door*********************************

     //**************************************Mid BOX*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 2.2f, width = 0.4f, height = 2.3f;
    local_x = -0.1, local_y = 0.0f, local_z = 0.04f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, al);
    //**************************************End of Right Door*********************************

    //**************************************Mid inside BOX*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 2.0f, width = 0.4f, height = 2.0f;
    local_x = 0.0, local_y = 0.2f, local_z = 0.035f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, al_books);
    //**************************************End of Right Door*********************************



}

void Almari_2_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_Almari_2_2 += 0.5;

        // Ensure the value does not exceed 100.0
        if (rotateAxis_Y_Almari_2_2 > 100.0) {
            rotateAxis_Y_Almari_2_2 = 100.0;
        }
    } 
    else {
        rotateAxis_Y_Almari_2_2 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_Almari_2_2 < 0.0) {
            rotateAxis_Y_Almari_2_2 = 0.0;
        }
    }

    cout << " almari " << rotateAxis_Y_Almari_2_2 << endl;
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left Door*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_Almari_2_2, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 1.0f, width = 0.05f, height = 2.0f;
    local_x = 0.0, local_y = 0.2f, local_z = 0.0f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, al_door1);
    //*************************************END of left Door***************************


    //**************************************Right Door*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_Almari_2_2, rot_z = 0.0f;
    trans_x = -2.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 1.0f, width = 0.05f, height = 2.0f;
    local_x = 1.0, local_y = 0.2f, local_z = 0.0f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, al_door2);
    //**************************************End of Right Door*********************************

     //**************************************Mid BOX*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 2.2f, width = 0.4f, height = 2.3f;
    local_x = -0.1, local_y = 0.0f, local_z = 0.04f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, al);
    //**************************************End of Right Door*********************************

    //**************************************Mid inside BOX*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 2.0f, width = 0.4f, height = 2.0f;
    local_x = 0.0, local_y = 0.2f, local_z = 0.035f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, al_books);
    //**************************************End of Right Door*********************************



}

void Glass_Door_Frame_1_1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_Door_1_1 += 0.5;

        // Ensure the value does not exceed 75.0
        if (rotateAxis_Y_Door_1_1 > 75.0) {
            rotateAxis_Y_Door_1_1 = 75.0;
        }
    } 
    else {
        rotateAxis_Y_Door_1_1 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_Door_1_1 < 0.0) {
            rotateAxis_Y_Door_1_1 = 0.0;
        }
    }

    cout << rotateAxis_Y_Door_1_1 << endl;
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left Door Frame*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_Door_1_1, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //right frame+++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //bottom frame+++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //top frame+++++++++++++++++++++++++
    len = 1.5f, width = 0.1f, height = 0.1f;
    local_x = 0.0, local_y = 2.7f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //*************************************END of left Door Frame***************************


    //**************************************Right Door frame*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_Door_1_1, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //right frame++++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 1.5 + 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //bottom frame++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //top frame+++++++++++++++++++++++++++
    len = 1.5f, width = 0.1f, height = 0.1f;
    local_x = 1.5, local_y = 2.7f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //*************************************END of Right Door Frame***************************
    
}

void Glass_Door_1_1(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift)
{
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;

    //*********************************************************left glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_Door_1_1, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left glasS--------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.7f;
    local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, glass);
    //*********************************************************END of Left Glass*****************************************************
    
     //*********************************************************Right glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f- rotateAxis_Y_Door_1_1, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //right glass--------------------------------------------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.7f;
    local_x = 1.5f, local_y = 0.0f, local_z = 0.f;
    
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift- trans_x, y_shift- trans_y, z_shift- trans_z, off_white, glass);
}

void Glass_Door_Frame_1_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_Door_1_2 += 0.5;

        // Ensure the value does not exceed 75.0
        if (rotateAxis_Y_Door_1_2 > 75.0) {
            rotateAxis_Y_Door_1_2 = 75.0;
        }
    } 
    else {
        rotateAxis_Y_Door_1_2 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_Door_1_2 < 0.0) {
            rotateAxis_Y_Door_1_2 = 0.0;
        }
    }

    cout << rotateAxis_Y_Door_1_2 << endl;
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left Door Frame*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_Door_1_2, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //right frame+++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //bottom frame+++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //top frame+++++++++++++++++++++++++
    len = 1.5f, width = 0.1f, height = 0.1f;
    local_x = 0.0, local_y = 2.7f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //*************************************END of left Door Frame***************************


    //**************************************Right Door frame*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_Door_1_2, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //right frame++++++++++++
    len = 0.05f, width = 0.05f, height = 2.7f;
    local_x = 1.5 + 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //bottom frame++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //top frame+++++++++++++++++++++++++++
    len = 1.5f, width = 0.1f, height = 0.1f;
    local_x = 1.5, local_y = 2.7f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //*************************************END of Right Door Frame***************************
}

void Glass_Door_1_2(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift)
{
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;

    //*********************************************************left glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_Door_1_2, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left glasS--------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.7f;
    local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, glass);
    //*********************************************************END of Left Glass*****************************************************

     //*********************************************************Right glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_Door_1_2, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //right glass--------------------------------------------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.7f;
    local_x = 1.5f, local_y = 0.0f, local_z = 0.f;

    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, glass);
}

void Glass_win_Frame_2_1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_win_2_1 += 0.5;

        // Ensure the value does not exceed 75.0
        if (rotateAxis_Y_win_2_1 > 75.0) {
            rotateAxis_Y_win_2_1 = 75.0;
        }
    } 
    else {
        rotateAxis_Y_win_2_1 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_win_2_1 < 0.0) {
            rotateAxis_Y_win_2_1 = 0.0;
        }
    }

    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left win Frame*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_1, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //right frame+++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //bottom frame+++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //top frame+++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //*************************************END of left win Frame***************************

    //**************************************win bottom wall*********************************
    //**************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //---------------------------------------
    len = 3.0f, width = 0.05f, height = 0.5f;
    local_x = 0.0, local_y = -0.5, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);

    //**************************************Right win frame*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_1, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //right frame++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 + 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //bottom frame++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //top frame+++++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //*************************************END of Right win Frame***************************

}
void Glass_win_Frame_2_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_win_2_2 += 0.5;

        // Ensure the value does not exceed 75.0
        if (rotateAxis_Y_win_2_2 > 75.0) {
            rotateAxis_Y_win_2_2 = 75.0;
        }
    } 
    else {
        rotateAxis_Y_win_2_2 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_win_2_2 < 0.0) {
            rotateAxis_Y_win_2_2 = 0.0;
        }
    }

    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left win Frame*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_2, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //right frame+++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //bottom frame+++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //top frame+++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //*************************************END of left win Frame***************************

    //**************************************win bottom wall*********************************
    //**************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //---------------------------------------
    len = 3.0f, width = 0.05f, height = 0.5f;
    local_x = 0.0, local_y = -0.5, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);

    //**************************************Right win frame*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_2, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //right frame++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 + 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //bottom frame++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //top frame+++++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //*************************************END of Right win Frame***************************
}
void Glass_win_Frame_2_3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_win_2_3 += 0.5;

        // Ensure the value does not exceed 75.0
        if (rotateAxis_Y_win_2_3 > 75.0) {
            rotateAxis_Y_win_2_3 = 75.0;
        }
    } 
    else {
        rotateAxis_Y_win_2_3 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_win_2_3 < 0.0) {
            rotateAxis_Y_win_2_3 = 0.0;
        }
    }

    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left win Frame*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_3, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //right frame+++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //bottom frame+++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //top frame+++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //*************************************END of left win Frame***************************

    //**************************************win bottom wall*********************************
    //**************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //---------------------------------------
    len = 3.0f, width = 0.05f, height = 0.5f;
    local_x = 0.0, local_y = -0.5, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);

    //**************************************Right win frame*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_3, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //right frame++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 + 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //bottom frame++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //top frame+++++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //*************************************END of Right win Frame***************************
}
void Glass_win_Frame_2_4(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (abs(camera.Position.z) > abs(z_shift - 5) && abs(camera.Position.z) < abs(z_shift + 5)) {
        rotateAxis_Y_win_2_4 += 0.5;

        // Ensure the value does not exceed 75.0
        if (rotateAxis_Y_win_2_4 > 75.0) {
            rotateAxis_Y_win_2_4 = 75.0;
        }
    } 
    else {
        rotateAxis_Y_win_2_4 -= 0.5;

        // Ensure the value does not go below 0.0
        if (rotateAxis_Y_win_2_4 < 0.0) {
            rotateAxis_Y_win_2_4 = 0.0;
        }
    }

    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************left win Frame*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_4, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //right frame+++++++++++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //bottom frame+++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //top frame+++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 0.0, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);
    //*************************************END of left win Frame***************************

    //**************************************win bottom wall*********************************
    //**************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //---------------------------------------
    len = 3.0f, width = 0.05f, height = 0.5f;
    local_x = 0.0, local_y = -0.5, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture0);

    //**************************************Right win frame*********************************
    //***************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_4, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left frame+++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //right frame++++++++++++
    len = 0.05f, width = 0.05f, height = 2.0f;
    local_x = 1.5 + 1.5 - 0.05f, local_y = 0.0, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //bottom frame++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 0.0f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //top frame+++++++++++++++++++++++++++
    len = 1.5f, width = 0.05f, height = 0.1f;
    local_x = 1.5, local_y = 2.0f - 0.1f, local_z = -0.025f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, texture0);
    //*************************************END of Right win Frame***************************
}
void Glass_win_2_1(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift)
{
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;

    //*********************************************************left glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_1, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left glasS--------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 0.0f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, glass);
    //*********************************************************END of Left Glass*****************************************************

     //*********************************************************Right glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_1, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //right glass--------------------------------------------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 1.5f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, glass);

}
void Glass_win_2_2(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift)
{
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;

    //*********************************************************left glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_2, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left glasS--------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 0.0f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, glass);
    //*********************************************************END of Left Glass*****************************************************

     //*********************************************************Right glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_2, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //right glass--------------------------------------------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 1.5f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, glass);
}
void Glass_win_2_3(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift)
{
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;

    //*********************************************************left glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_3, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left glasS--------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 0.0f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, glass);
    //*********************************************************END of Left Glass*****************************************************

     //*********************************************************Right glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_3, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //right glass--------------------------------------------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 1.5f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, glass);
}
void Glass_win_2_4(unsigned int TransparentVAO, Shader transparentShader, float x_shift, float y_shift, float z_shift)
{
    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;

    //*********************************************************left glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f + rotateAxis_Y_win_2_4, rot_z = 0.0f;
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;
    //left glasS--------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 0.0f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, glass);
    //*********************************************************END of Left Glass*****************************************************

     //*********************************************************Right glass***********************************************************
    //*****************************************************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f - rotateAxis_Y_win_2_4, rot_z = 0.0f;
    trans_x = -3.0f, trans_y = 0.0f, trans_z = 0.0f;
    //right glass--------------------------------------------------------------------------------
    len = 1.5f, width = 0.05f, height = 2.0f;
    local_x = 1.5f, local_y = 0.2f, local_z = 0.0f;
    GenSheet_Transparent(TransparentVAO, transparentShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift - trans_x, y_shift - trans_y, z_shift - trans_z, off_white, glass);
}

//General
void RaillingUnit(unsigned int VAO, BezierCurve Round_piller, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    //variable declaration
    float local_x = 0.0f, local_y = 0.0f, local_z = 0.f;//local jevabe shape howar kotha
    float len = 0.0f, width = 0.0f, height = 0.0f;
    float  rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
    float trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//dynamic sliding e kaj korbe OR object k origin e anar kaj korbe


    //******************bottom cube*************************************************************
    //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f , rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.08f, width = 0.08f, height = 0.02f;
    local_x = -0.04, local_y = 0.0f, local_z = -0.04f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture7);


    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    len = 0.0;
    float ht = 0.0f;
    width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.0, lbz = 0.0;




    //piller round+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.05, ht = 0.4f;
    width = 0.05;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_piller.drawBezierCurve(ourShader, model);


    //******************top cube*************************************************************
  //**********************************************************************************************
    rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;//era common for all sub component
    trans_x = 0.0f, trans_y = 0.0f, trans_z = 0.0f;//era common for all sub component
    //left frame++++++++++++++++++++
    len = 0.08f, width = 0.08f, height = 0.02f;
    local_x = -0.04, local_y = 0.4f, local_z = -0.04f;
    GenSheet(VAO, ourShader, len, width, height, local_x, local_y, local_z, rot_x, rot_y, rot_z, trans_x, trans_y, trans_z, x_shift, y_shift, z_shift, off_white, texture7);



   

}

void GenSheet_Transparent(unsigned int VAO, Shader ourShader, float len, float width, float height, float local_x, float local_y, float local_z, float rot_x, float rot_y, float rot_z, float trans_x, float trans_y, float trans_z, float x_shift, float y_shift, float z_shift, glm::vec4 color, unsigned int texture)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 local_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f *(z_shift)));
    float x_sft = local_x, y_sft = local_y, z_sft = local_z;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    local_translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(trans_x, trans_y, -1.0f * trans_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, height, -1.0 * width));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = uni_translate * rotateZMatrix * rotateYMatrix * rotateXMatrix * translateMatrix * local_translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
  
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GenSheet(unsigned int VAO, Shader ourShader, float len, float width, float height, float local_x, float local_y, float local_z, float rot_x, float rot_y, float rot_z, float trans_x, float trans_y, float trans_z, float x_shift, float y_shift, float z_shift, glm::vec4 color, unsigned int texture)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 local_translateMatrix,translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    float x_sft = local_x, y_sft = local_y, z_sft = local_z;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    local_translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(trans_x, trans_y, -1.0f * trans_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, height, -1.0*width));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = uni_translate * rotateZMatrix * rotateYMatrix * rotateXMatrix * translateMatrix * local_translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void HorizontalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    float x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void VerticalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    float x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f*len));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void GenFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //Floor
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, 0.2f, -1.0*width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

void GenFloor2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //Floor
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, 0.1f, -1.0 * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

void Box(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top box
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + 0.1f, y_sft = (ht + lby) - 0.4f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (width - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO1);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

}

void FlatBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
        x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top box
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + 0.1f, y_sft = (ht + lby) - 0.2f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (width - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.9, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.9, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

void HoloBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //NO TOP BOX
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

//components===============
void Fan_and_switch(unsigned int VAO, BezierCurve Fan_Bati, BezierCurve Fan_Blade, BezierCurve Fan_Tube, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (isRotate1)
    {
        if (fanspeed1 < 12.0)
        {
            fanspeed1 += 0.2;
            rotateAxis_Y_Fan1 += fanspeed1;
            rotateAxis_Y_Fan1 = fmod(rotateAxis_Y_Fan1, 360);
            Fan1_ready = true;
        }
        else
        {
            rotateAxis_Y_Fan1 += fanspeed1;
            rotateAxis_Y_Fan1 = fmod(rotateAxis_Y_Fan1, 360);
        }
    }
    else
    {
        if (fanspeed1 > 0.0)
        {
            fanspeed1 -= 0.1;
            rotateAxis_Y_Fan1 += fanspeed1;
            rotateAxis_Y_Fan1 = fmod(rotateAxis_Y_Fan1, 360);
        }
        else
        {
            Fan1_ready = true;
        }
    }
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix,translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0 , rsz = 0.0;

    //FAN BATI+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy , -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rotateAxis_Y_Fan1), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Fan_Bati.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //FAN BLADE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    len = 0.7, ht = 0.7f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.25, rsy = 0.0667, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    for (int i = 0; i < 3; i++)
    {
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i * 120.0f + rotateAxis_Y_Fan1), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
        model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * rotateXMatrix * rotateZMatrix * scaleMatrix;
        Fan_Blade.drawBezierCurve(ourShader, model);
    }
    //CURVE---------END----------------------------CURVE

    //FAN BLADE Tube CONNECTOR+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    len = 0.0667, ht = 0.15f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0667, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    for (int i = 0; i < 3; i++)
    {
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i * 120.0f + rotateAxis_Y_Fan1), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
        model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * rotateZMatrix * scaleMatrix;
        Fan_Tube.drawBezierCurve(ourShader, model);
    }
    //CURVE---------END-------------------CURVE

    //FAN RODE Tube CONNECTOR++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    len = 0.1, ht = 0.15f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0667, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    model = uni_translate * translateMatrix *  RS_translateMatrix * scaleMatrix;
    Fan_Tube.drawBezierCurve(ourShader, model);
    
    //CURVE---------END-------------------CURVE

}

void Main_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 17.5, lby = 0.4, lbz = 12.0;

    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Border.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //Round piller+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.25, ht = 2.7f;
    width = 0.25;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);
    //CURVE---------END----------------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    //Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 1.0, ht = 0.5725;
    width = 0.75;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Sub_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++SIDE****************
    //------CURVE---START
    float xx = 2.6, zz = 0.2;
    lbx = 17.5 + xx, lby = 0.4, lbz = 12.0 + zz;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    //Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5 + xx, lby = 0.4, lbz = 12.0 + zz;
    len = 1.0, ht = 0.5725;
    width = 0.75;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Sub_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE
}


void Common_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 17.5, lby = 0.4, lbz = 12.0;

    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Border.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //Round piller+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.25, ht = 2.7f;
    width = 0.25;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);
    //CURVE---------END----------------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    //lbx = 17.5, lby = 0.4, lbz =  12.0;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.0, rsy = 0.594+0.69, rsz = 0.55;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++SIDE****************
    //------CURVE---START
    float xx = 2.6, zz = 0.2;
    lbx = 17.5+xx, lby = 0.4, lbz = 12.0+zz;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    //lbx = 17.5 + xx, lby = 0.4, lbz = 12.0 + zz;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE
}

void Common_Arch_Vertical(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;

    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 10.0, lby = 0.4, lbz = 21.5;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0+0.1, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Border.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //Round piller+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 10.0, lby = 0.4, lbz = 21.5;
    len = 0.25, ht = 2.7f;
    width = 0.25;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0+0.1, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);
    //CURVE---------END----------------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 10.0, lby = 0.4, lbz = 21.5;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.2, rsy = 1.69, rsz = -1.2;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    //lbx = 10.0, lby = 0.4, lbz = 21.5;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.2, rsy = 0.594 + 0.69, rsz = -0.65;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++SIDE****************
    //------CURVE---START
    //lbx = 0.0, lby = 0.0, lbz = 0.0;
    float xx = 0.0, zz = 1.4;
    lbx = 10.0 + xx, lby = 0.4, lbz = 21.5 + zz;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    ////lbx = 0.0, lby = 0.0, lbz = 0.0;
    //lbx = 10.0 + xx, lby = 0.4, lbz = 21.5 + zz;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE
}

void jharbati(unsigned int VAO, BezierCurve Round_Piller, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.0, lbz = 0.0;

    //round chakti
    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 3.6, ht = 0.1f;
    width = 3.6;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);

    //dondo1
    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.1, ht = 1.8f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, 0.05+y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateXMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);

    //dondo2
    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.1, ht = 1.8f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, 0.05 + y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateXMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);


    //dondo3
    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.1, ht = 1.8f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, 0.05 + y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateZMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);

    //dondo4
    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.1, ht = 1.8f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, 0.05 + y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateZMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);

    //stand
    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.03, ht = 9.6f;
    width = 0.03;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft,  y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateZMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);

}

void small_dome(unsigned int VAO, BezierCurve circle, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;


    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.7, ht = 0.8f;
    width = 0.7;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle.drawBezierCurve(ourShader, model);




    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.3f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve
}
void mid_dome(unsigned int VAO, BezierCurve circle1, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;

    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 3.0, ht = 3.0f;
    width = 3.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle1.drawBezierCurve(ourShader, model);

    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.8f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 4.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve
}
void Big_dome(unsigned int VAO, BezierCurve circle2, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;

    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 7.0, ht = 7.0f;
    width = 7.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle2.drawBezierCurve(ourShader, model);

    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.8f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 11.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve
}




//Doors
void DoubleDoors(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1 = texture0, unsigned int texture2 = texture0)
{
    if (isDoubleDoor)
    {
        if (rotateAxis_Y_Door < 75.0)
        {
            rotateAxis_Y_Door += doorspeed;
            
        }
        else
        {
            DDoor_ready = true;
        }
    }
    else
    {
        if (rotateAxis_Y_Door > 0.0)
        {
            rotateAxis_Y_Door -= doorspeed;

        }
        else
        {
            DDoor_ready = true;
        }
    }

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //LEFT DOOR
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift , y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, rightDoor);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 2.6f, -0.15f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rotateAxis_Y_Door), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix *  scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    ///RIGHT DOOR
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift + 6.0, y_shift, -1.0 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, rightDoor); //bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-3.0f, 2.6f, -0.15f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f - rotateAxis_Y_Door), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void SideDoor1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    if (camera.Position.x > x_shift - 5 && camera.Position.x < x_shift + 5) {
        side_trans_Z_1 += 0.1;

        // Ensure the value does not exceed 4.0
        if (side_trans_Z_1 > 4.0) {
            side_trans_Z_1 = 4.0;
        }
    } 
    else {
        side_trans_Z_1 -= 0.1;

        // Ensure the value does not go below 0.0
        if (side_trans_Z_1 < 0.0) {
            side_trans_Z_1 = 0.0;
        }
    }


    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //LEFT DOOR
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, t_door);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.42f, 0.05f- side_trans_Z_1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 2.6f, 4.0f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f ), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void SideDoor2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    if (camera.Position.x > x_shift - 5 && camera.Position.x < x_shift + 5) {
        side_trans_Z_2 += 0.1;

        // Ensure the value does not exceed 4.0
        if (side_trans_Z_2 > 4.0) {
            side_trans_Z_2 = 4.0;
        }
    } 
    else {
        side_trans_Z_2 -= 0.1;

        // Ensure the value does not go below 0.0
        if (side_trans_Z_2 < 0.0) {
            side_trans_Z_2 = 0.0;
        }
    }

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //LEFT DOOR
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, t_door);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.42f, 0.05f - side_trans_Z_2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 2.6f, 4.0f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void imam_Place(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //LEFT DOOR
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture6);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5*0.7f, 1.5 * 0.125f, 1.5 * 0.8f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //LEFT DOOR
   //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f+.125, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5 * 0.7f, 1.5 * 0.125f, 1.5 * 0.6f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //LEFT DOOR
//universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f + .25, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5 * 0.7f, 1.5 * 0.5f, 1.5 * 0.2f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //LEFT DOOR
//universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture6);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f + .25, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5 * 0.7f, 1.5 * 0.7f, 1.5 * 0.2f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void bookshef(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //tol
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.00f ));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.01f, 0.7f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //tol
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.3f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.01f, 0.7f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //tol
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.6f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.01f, 0.7f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.6f,0.1f ));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //side
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.6f, 0.7f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //mid
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.3f, 0.7f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right side
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, wodden);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.0f, 0.00f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.6f, 0.7f));


    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}





// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {                 //Forward
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {                 //Backward
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {                 //Left
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {                 //Right
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Down
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
    {
        eyeY -= 2.5 * deltaTime;
        camera.ProcessKeyboard(UP, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)                   //Yaw ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 3.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)                   //Yaw ve-
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, -3.0f, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)                   //Pitch ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(3.0f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)                   //Pitch ve-
    {
        camera.Proccess_Pitch_Yaw_Roll(-3.0f, 0.0f, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //Roll ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 0.0f, 4.0f);

    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)                   //Roll ve-
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 0.0f, -4.0f);

    }

    if (glfwGetKey(window, GLFW_KEY_I ) == GLFW_PRESS)                   //Rotate camera around a look at point
    {                                                                   //Right
        camera.RotateAroundLookAt(2.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_O ) == GLFW_PRESS)                   //Rotate camera around a look at point
    {                                                                   //Left
        camera.RotateAroundLookAt(-2.0f);
    }

    //************Dynamic object************
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)                   //Rotate Fan
    {
        
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)                   //Point Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)                   //Directional Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)                   //Spot Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)                   //Directional Light Off
    {

    }
    
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)                   //Spot Light Off
    {
        isTape1 ^= true;
        cout << isTape1 << endl;
    }
    

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)                   //Fan1 rotate
    {
        if (Fan1_ready)
        {
            Fan1_ready = false;
            isRotate1 ^= true;
            cout << isRotate1 << endl;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)                   //Fan2 rotate
    {
        if (Fan2_ready)
        {
            Fan2_ready = false;
            isRotate2 ^= true;
            cout << isRotate2 << endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)                   //Specular Off
    {
        if (DDoor_ready)
        {
            DDoor_ready = false;
            isDoubleDoor ^= true;
            cout << isDoubleDoor << endl;
        }
    }
    
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)                   //jhar bati On/Off
    {
        jhar_light ^= true;
        usleep(500000);
        // std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        if (jhar_light)
        {
            for (int i = 27; i <= 34; i++)
            {
                pointLightOn[i] = 1.0;
            }
            pointLight27.turnOn();
            pointLight28.turnOn();
            pointLight29.turnOn();
            pointLight30.turnOn();
            pointLight31.turnOn();
            pointLight32.turnOn();
            pointLight33.turnOn();
            pointLight34.turnOn();
        }
        else
        {
            for (int i = 27; i <= 34; i++)
            {
                pointLightOn[i] = 0.0;
            }
            pointLight27.turnOff();
            pointLight28.turnOff();
            pointLight29.turnOff();
            pointLight30.turnOff();
            pointLight31.turnOff();
            pointLight32.turnOff();
            pointLight33.turnOff();
            pointLight34.turnOff();
        }
    }

    //***************Lighting***************
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)                   //Lighting On-Off
    {
        lightingOn ^= true;
        cout << lightingOn << endl;
        usleep(100000);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)                   //Ambient On
    {
        if (ambientOn == 0.0)
        {
            ambientOn = 1.0;
            pointLight1.turnAmbientOn();
            pointLight2.turnAmbientOn();
            pointLight3.turnAmbientOn();
            pointLight4.turnAmbientOn();
            spotLight.turnAmbientOn();
            directionalLight.turnAmbientOn();
        }
        else
        {
            ambientOn = 0.0;
            pointLight1.turnAmbientOff();
            pointLight2.turnAmbientOff();
            pointLight3.turnAmbientOff();
            pointLight4.turnAmbientOff();
            spotLight.turnAmbientOff();
            directionalLight.turnAmbientOff();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)                   //Ambient Off
    {
        if (diffuseOn == 0.0)
        {
            diffuseOn = 1.0;
            pointLight1.turnDiffuseOn();
            pointLight2.turnDiffuseOn();
            pointLight3.turnDiffuseOn();
            pointLight4.turnDiffuseOn();
            spotLight.turnDiffuseOn();
            directionalLight.turnDiffuseOn();
        }
        else
        {
            diffuseOn = 0.0;
            pointLight1.turnDiffuseOff();
            pointLight2.turnDiffuseOff();
            pointLight3.turnDiffuseOff();
            pointLight4.turnDiffuseOff();
            spotLight.turnDiffuseOff();
            directionalLight.turnDiffuseOff();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)                   //Diffuse On
    {
        if (specularOn == 0.0)
        {
            specularOn = 1.0;
            pointLight1.turnSpecularOn();
            pointLight2.turnSpecularOn();
            pointLight3.turnSpecularOn();
            pointLight4.turnSpecularOn();
            spotLight.turnSpecularOn();
            directionalLight.turnSpecularOn();
        }
        else
        {
            specularOn = 0.0;
            pointLight1.turnSpecularOff();
            pointLight2.turnSpecularOff();
            pointLight3.turnSpecularOff();
            pointLight4.turnSpecularOff();
            spotLight.turnSpecularOff();
            directionalLight.turnSpecularOff();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)                   //Point Light On
    {
        if (pointLightOn[0] == 0.0)
        {
            
            for (int i = 0; i < noOfPointLights; i++)
            {
                if (i < 27 || i > 34)
                {
                    pointLightOn[i] = 1.0;
                }
                
                
            }
            pointLight1.turnOn();
            pointLight2.turnOn();
            pointLight3.turnOn();
            pointLight4.turnOn();
            pointLight5.turnOn();
            pointLight6.turnOn();
            pointLight7.turnOn();
            pointLight8.turnOn();
            pointLight9.turnOn();
            pointLight10.turnOn();
            pointLight11.turnOn();
            pointLight12.turnOn();
            pointLight13.turnOn();
            pointLight14.turnOn();
            pointLight15.turnOn();
            pointLight16.turnOn();
            pointLight17.turnOn();
            pointLight18.turnOn();
            pointLight19.turnOn();
            pointLight20.turnOn();
            pointLight21.turnOn();
            pointLight22.turnOn();
            pointLight23.turnOn();
            pointLight24.turnOn();
            pointLight25.turnOn();
            pointLight26.turnOn();
            pointLight35.turnOn();
            pointLight36.turnOn();
        }
        else
        {
            for (int i = 0; i < noOfPointLights; i++)
            {
                if (i < 27 || i > 34)
                {
                    pointLightOn[i] = 0.0;
                }
            }
            pointLight1.turnOff();


            pointLight2.turnOff();


            pointLight3.turnOff();


            pointLight4.turnOff();

            pointLight5.turnOff();
            pointLight6.turnOff();
            pointLight7.turnOff();
            pointLight8.turnOff();
            pointLight9.turnOff();
            pointLight10.turnOff();
            pointLight11.turnOff();
            pointLight12.turnOff();
            pointLight13.turnOff();
            pointLight14.turnOff();
            pointLight15.turnOff();
            pointLight16.turnOff();
            pointLight17.turnOff();
            pointLight18.turnOff();
            pointLight19.turnOff();
            pointLight20.turnOff();
            pointLight21.turnOff();
            pointLight22.turnOff();
            pointLight23.turnOff();
            pointLight24.turnOff();
            pointLight25.turnOff();
            pointLight26.turnOff();
            pointLight35.turnOff();
            pointLight36.turnOff();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)                   //Directional Light On/off
    {
        if (directionalLightOn == 0.0)
        {
            directionalLightOn = 1.0;
            directionalLight.turnOn();
        }
        else
        {
            directionalLightOn = 0.0;
            directionalLight.turnOff();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)                   //Spot Light On/off
    {
        if (spotLightOn == 0.0)
        {
            spotLightOn = 1.0;
            spotLight.turnOn();
        }
        else
        {
            spotLightOn = 0.0;
            spotLight.turnOff();
        }
        
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)                   //Dark On-Off
    {
        dark ^= true;
        if (dark)
        {
            for (int i = 0; i < noOfPointLights; i++)
            {
                pointLightOn[i] = 1.0;
            }
            pointLight1.turnOn();
            pointLight2.turnOn();
            pointLight3.turnOn();
            pointLight4.turnOn();
            pointLight5.turnOn();
            pointLight6.turnOn();
            pointLight7.turnOn();
            pointLight8.turnOn();
            pointLight9.turnOn();
            pointLight10.turnOn();
            pointLight11.turnOn();
            pointLight12.turnOn();
            pointLight13.turnOn();
            pointLight14.turnOn();
            pointLight15.turnOn();
            pointLight16.turnOn();
            pointLight17.turnOn();
            pointLight18.turnOn();
            pointLight19.turnOn();
            pointLight20.turnOn();
            pointLight21.turnOn();
            pointLight22.turnOn();
            pointLight23.turnOn();
            pointLight24.turnOn();
            pointLight25.turnOn();
            pointLight26.turnOn();
            pointLight27.turnOn();
            pointLight28.turnOn();
            pointLight29.turnOn();
            pointLight30.turnOn();
            pointLight31.turnOn();
            pointLight32.turnOn();
            pointLight33.turnOn();
            pointLight34.turnOn();
            pointLight35.turnOn();
            pointLight36.turnOn();
            directionalLightOn = 0.0;
            directionalLight.turnOff();
        }
        else
        {
            for (int i = 0; i < noOfPointLights; i++)
            {
                pointLightOn[i] = 0.0;
            }
            pointLight1.turnOff();


            pointLight2.turnOff();


            pointLight3.turnOff();


            pointLight4.turnOff();

            pointLight5.turnOff();
            pointLight6.turnOff();
            pointLight7.turnOff();
            pointLight8.turnOff();
            pointLight9.turnOff();
            pointLight10.turnOff();
            pointLight11.turnOff();
            pointLight12.turnOff();
            pointLight13.turnOff();
            pointLight14.turnOff();
            pointLight15.turnOff();
            pointLight16.turnOff();
            pointLight17.turnOff();
            pointLight18.turnOff();
            pointLight19.turnOff();
            pointLight20.turnOff();
            pointLight21.turnOff();
            pointLight22.turnOff();
            pointLight23.turnOff();
            pointLight24.turnOff();
            pointLight25.turnOff();
            pointLight26.turnOff();
            pointLight27.turnOff();
            pointLight28.turnOff();
            pointLight29.turnOff();
            pointLight30.turnOff();
            pointLight31.turnOff();
            pointLight32.turnOff();
            pointLight33.turnOff();
            pointLight34.turnOff();
            pointLight35.turnOff();
            pointLight36.turnOff();
            directionalLightOn = 1.0;
            directionalLight.turnOn();
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

