#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<stdio.h>


float blockSpeed=0.2; // block dx value
int cheats = 0;

char name[25];

float block_x=50.0,block_y=0;//block init position

float heroMotion=0.0;//dave moving dy value
int xinc=5,yinc=35;

int i=0,score=1;float scoreFlag=1; // for increment score score_int score_flag

char scs[20],slevel[20];
//to store score_string using itoa() and level as well
int prev=1,level=1,levelFlag=1,welcomeFlag=1; //level_flag & welcome_flag init w/ 1

void init(void){
	srand(time(0));
	block_y=(rand()%45)+10;//b/w 10 to 44
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glLoadIdentity ();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void drawDave(void){

	//hat
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2i(24,60);
	glVertex2i(26,60);
	glVertex2i(26,59);
	glVertex2i(24,59);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2i(24,59);
	glVertex2i(28,59);
	glVertex2i(28,58);
	glVertex2i(24,58);
	glEnd();
	//face
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.8,0.8);
	glVertex2i(24,58);
	glVertex2i(26,58);
	glVertex2i(26,55);
	glVertex2i(24,55);
	glEnd();
	// eye
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.1,1.0);
	glVertex2f(25.5,57.8);
	glVertex2f(25.8,57.8);
	glVertex2f(25.8,57.3);
	glVertex2f(25.5,57.3);
	glEnd();
	//body
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(21,58);
	glVertex2f(23.5,58);
	glVertex2f(23.5,55);
	glVertex2f(21,55);
	glEnd();
	//arm-sleeve
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(22.25,54.5);
	glVertex2f(24,54.5);
	glVertex2f(24,53.5);
	glVertex2f(22.25,53.5);
	glEnd();
	//arm-sleevless
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.8,0.8);
	glVertex2f(24,54.5);
	glVertex2f(27,54.5);
	glVertex2f(27,53.5);
	glVertex2f(24,53.5);
	glEnd();
	//legs-pant
	glBegin(GL_POLYGON);
	glColor3f(0.2,0.4,1.0);
	glVertex2f(17,58);
	glVertex2f(20.5,58);
	glVertex2f(20.5,56.75);
	glVertex2f(17,56.75);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.2,0.4,1.0);
	glVertex2f(17,56.25);
	glVertex2f(20.5,56.25);
	glVertex2f(20.5,55);
	glVertex2f(17,55);
	glEnd();
	//feet
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.8,0.8);
	glVertex2f(17,58);
	glVertex2f(16,58);
	glVertex2f(16,56.75);
	glVertex2f(17,56.75);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.8,0.8);
	glVertex2f(16,56.25);
	glVertex2f(17,56.25);
	glVertex2f(17,55);
	glVertex2f(16,55);
	glEnd();

}

void renderBitmapString(float x,float y,float z,void *font,char*string){
	char *c;
	glRasterPos3f(x, y,z);
	for(c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	if (level>prev){
        // printf("%d%d",sci,prev);
        // printf("change Shape");
        int lower = 5, upper = 30;
        int newY = (rand() % (upper - lower + 1)) + lower;
        yinc=newY;
        prev=level;
    }

	//GameOver Checking
	if(
	// (i==63||i==-430) //top and bottom checking
	// ||
	( ((int)block_x==12||(int)block_x==11||(int)block_x==8||(int)block_x==2))&& //dave collision checking
		(int)block_y<53+(int)heroMotion && (int)block_y+yinc>53+(int)heroMotion
		&& (cheats==0)
	)
		
	{

		glColor3f(0.0,0.0,0.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(1.0,0.0,0.0);
		renderBitmapString(20,70,0,GLUT_BITMAP_HELVETICA_18,"GAME OVER!!!  BETTER LUCK NEXT TIME");
		glColor3f(1.0,1.0,1.0);
		renderBitmapString(25,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"Your");
		renderBitmapString(28,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"score:");
		renderBitmapString(70,58,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glutSwapBuffers();
		glFlush();
		printf("\nGAME OVER\n\n");
		printf("%s You scored  %s" ,name,scs);
		sleep(5);
		exit(0);
	}

	else if(welcomeFlag==1){//Welcome Screen
		welcomeFlag=0;

		// glColor3f(1.0,0.1,1.0);
		// glRectf(0.0,0.0,100.0,10.0);//ceil
		// glRectf(0.0,100.0,100.0,90.0);//floor

		glColor3f(1.0,1.0,0.0);
		renderBitmapString(35,65,0,GLUT_BITMAP_8_BY_13,"Moodabidri Karnataka");
		renderBitmapString(15,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"Mangalore Institute of Technology and Engineering");

		glColor3f(1.0,1.0,1.0);
		renderBitmapString(35,85,0,GLUT_BITMAP_HELVETICA_18,"Flying Dave");
		renderBitmapString(20,80,0,GLUT_BITMAP_HELVETICA_12,"A mini project for Computer Graphics & Visualization Laboratory");

		

		glColor3f(1.0,0.0,0.0);
		renderBitmapString(35,45,0,GLUT_BITMAP_TIMES_ROMAN_24,"Welcome");
		renderBitmapString(48,45,0,GLUT_BITMAP_TIMES_ROMAN_24,name);
		renderBitmapString(35,30,0,GLUT_BITMAP_TIMES_ROMAN_24,"Click To Start");

		glColor3f(0.0,0.0,0.0);
		// drawDave();

		glutSwapBuffers();
		glFlush();

	}

	else
	{
		//on every increase by 20 in score in each level
		if(score%20==0&&levelFlag==1)
		{
			levelFlag=0; //make level_flag=0
			level++;//increase level by 1
			blockSpeed+=0.1;//increase block_dx_speed by 0.01
		}

		//within every level make level_flag=1
		else if(score%20!=0&&levelFlag!=1){
			levelFlag=1;
		}

		glPushMatrix();

		glColor3f(1.0,1.0,1.0);   //score
		renderBitmapString(1,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Score:");
		//glColor3f(0.7,0.7,0.7);

		sprintf(slevel,"%d",level);   //level
		renderBitmapString(80,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Level:");
		renderBitmapString(93,3,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);

		scoreFlag+=0.025;//score flag increase slowly
		score=(int)scoreFlag;//int(scoreFlag) will be the displayed score	
		sprintf(scs,"%d",score);
		//from int to char convertion to display score

		renderBitmapString(20,3,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glTranslatef(0.0,heroMotion,0.0);

		drawDave();
		//display character

		//if object move towards left & get out of projection volume
		if(block_x<-10)
		{

			block_x=50;            //total width is 50
			block_y=(rand()%25)+20;
			//10 for selling+10 for giving enough space
			// block bottom limit 0+20 & top limit 24+20=44

		}

		else
			block_x-=blockSpeed;
		//within the projection volume dec its x value by block_speed

        glTranslatef(block_x, -heroMotion, 0.0);
        int lower = 1, upper = 3;
        int num = (rand() % (upper - lower + 1)) + lower;

//        printf("%d",num);
        if(num==1){
            glColor3f(1.0,0.0,0.0);
        }
        else if(num==2){
            glColor3f(0.0,1.0,0.0);
        }else{
            glColor3f(0.0,0.0,1.0);
        }
        glRectf(block_x,block_y,block_x+5,block_y+yinc);//block 1

        glPopMatrix();
        glutSwapBuffers();
        glFlush();

	}
}


void moveDaveUp(void)
{
	heroMotion+=0.5;
	i++;
	glutPostRedisplay();
}

void moveDaveDown(void)
{
	heroMotion-=0.5;
	i--;
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){

	switch (button){

		case GLUT_LEFT_BUTTON: 	if (state == GLUT_DOWN)
									glutIdleFunc(moveDaveUp);
								else if (state == GLUT_UP)
									glutIdleFunc(moveDaveDown);
								break;
		default: break;
	}

}


void keys(unsigned char key,int x,int y){
	if(key=='q') glutIdleFunc(moveDaveUp);
	if(key=='p') glutIdleFunc(moveDaveDown);

}

int main(int argc, char** argv){
	printf("ENTER PLAYER NAME: ");
	scanf("%s",name);
	printf("_Hit 1 to enable cheats_");
	scanf("%d",&cheats);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (200,200);
	glutCreateWindow ("Flying Dave - The Game");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutMainLoop();
	return 0;

}