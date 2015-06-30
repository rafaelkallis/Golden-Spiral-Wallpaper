//
//  main.c
//  GoldenSpiralCalculator
//
//  Created by Rafael Kallis on 09/04/15.
//  Copyright (c) 2015 Rafael Kallis. All rights reserved.
//
//  This App helps in the calculation of posters for a Golden Spiral looking Wallpaper. If you would like to try out I suggest using the Following Inputs: 2 (Landscape), 2 (Height), 75 (Height Value), 2 (Gap Space Value between Pictures)

#define FI 1.61803398875
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef __MINGW32__
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
void drawSquare(double x,double y,double size){
    /*
     _______
     |       |    + is middle of Square with x and y coordinates from function arguments
     |   +   |
     |       |
     -------
     
     */
    //main structure
    glVertex2d(x-size/2,y+size/2);
    glVertex2d(x-size/2,y-size/2);
    
    glVertex2d(x-size/2,y-size/2);
    glVertex2d(x+size/2,y-size/2);
    
    glVertex2d(x+size/2,y-size/2);
    glVertex2d(x+size/2,y+size/2);
    
    glVertex2d(x+size/2,y+size/2);
    glVertex2d(x-size/2,y+size/2);
    //Filling Lines
    glVertex2d(x-size/2,y);
    glVertex2d(x,y+size/2);
    
    glVertex2d(x-size/2,y-size/2);
    glVertex2d(x+size/2,y+size/2);
    
    glVertex2d(x,y-size/2);
    glVertex2d(x+size/2,y);
}
/*
 Phases: AntiClockWise Spin.
 [2]<[1]
 \/   ^
 [3]>[4]
 */
void GoldenSpiral(double size,int phase,double x,double y,double scale,double space){
    if (size-space>1) {
        drawSquare(x, y, (size-space)*scale);
        printf("%0.1lfcm x %0.1lfcm\n",size-space,size-space);
        switch (phase) {
            case 1:
                GoldenSpiral(size/FI, 2, x-size*scale/2-size*scale/(FI*2), y+size*scale/2-size*scale/(FI*2),scale,space);
                break;
            case 2:
                GoldenSpiral(size/FI, 3, x-size*scale/2+size*scale/(FI*2), y-size*scale/2-size*scale/(FI*2),scale,space);
                break;
            case 3:
                GoldenSpiral(size/FI, 4, x+size*scale/2+size*scale/(FI*2), y-size*scale/2+size*scale/(FI*2),scale,space);
                break;
            case 4:
                GoldenSpiral(size/FI, 1, x+size*scale/2-size*scale/(FI*2), y+size*scale/2+size*scale/(FI*2),scale,space);
                break;
        }
    }
}
void printSize(double width,double height){
    printf("\nEstimated Width: %0.1lfcm Estimated Height: %0.1lfcm\nCanvas Sizes:\n",width,height);
}
void start(){
    double space,size;
    int option1,option2;
    printf("Select Image type:\n1 Portait\n2 Landscape\n");
    scanf("%d",&option1);
    printf("\nPlease measure desired width or height (in cm) and select what you have measured:\n1 Width\n2 Height\n");
    scanf("%d",&option2);
    if ((option2!=1 && option2!=2) || (option1!=1 && option1!=2)) {
        printf("Exception: Illegal Inputs. Terminating App\n");
        return;
    }else if(option2==1) printf("\nEnter Width (in cm): \n"); else printf("\nEnter Height (in cm): \n");
    scanf("%lf",&size); //Size takes value of known length (either Width or Height)
    printf("\nPlease enter desired gap space length (in cm) between pictures:\n");
    scanf("%lf",&space);
    size+=space;
    // size  phase  X      Y      scale        space
    if     (option1==1 && option2==1){ printSize(size-space,(size-space)*FI); GoldenSpiral(size,    2,  0,     0.382, 2/(size*FI), space); }//Portait + Width Known
    else if(option1==1 && option2==2){ printSize((size-space)/FI,size-space); GoldenSpiral(size/FI, 2,  0,     0.382, 2/size,      space); }//Portait + Height Known
    else if(option1==2 && option2==1){ printSize(size-space,(size-space)/FI); GoldenSpiral(size/FI, 1,  0.382, 0,     2/size,      space); }//Landscape + Width Known
    else if(option1==2 && option2==2){ printSize((size-space)*FI,size-space); GoldenSpiral(size,    1,  0.382, 0,     2/(size*FI), space); }//Landscape + Height Known
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    start();
    glEnd();
    glFlush();
}
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutCreateWindow("Preview");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
