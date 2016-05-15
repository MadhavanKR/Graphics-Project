#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<string.h>
//comment
GLfloat transx=0.0;
GLfloat transy=0.0,angle=1;;
GLfloat flag=0,start=0;
float x_max;
int count=0;
int welcome=0;
int gameover=0;
float sx=1.0,sy=1.0;
char ch='0';
void print_text(char *s, GLint i,GLint j)
{
	int n=strlen(s);
	glRasterPos3f(i,j,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glScalef(0.1,0.1,0.1);
	for(i=0;i<n;i++)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)s[i]);
    glPopMatrix();
}

void draw()
{
	glColor3f(0.5,0.75,0.5);
	glBegin(GL_POLYGON);
	 glVertex3i(0,30,0); 
	 glVertex3i(40,30,0);
	 glVertex3i(40,70,0);
	 glVertex3i(0,70,0);
	glEnd();
}

void drawtop()
{
	glColor3f(0,0.1,0.1);
	glBegin(GL_POLYGON);
	 glVertex2i(0,499);
	 glVertex2i(499,499);
	 glVertex2i(499,300);
	 glVertex2i(0,300);
	glEnd();
}

void drawland()
{
	glColor3f(0,0.1,0.1);
	glBegin(GL_POLYGON);
	 glVertex2i(0,0);
	 glVertex2i(0,30);
	 glVertex2i(499,30);
	 glVertex2i(499,0);
	glEnd();
}

void obstacle(int x,int y,int l)
{
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
	 glVertex2i(x,y);
	 glVertex2i(x+50,y);
	 glVertex2i(x+50,y+60+l);
	 glVertex2i(x,y+60+l);
	glEnd();
}


void top_obstacle(int x,int y,int l)
{
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
	 glVertex2i(x,y);
	 glVertex2i(x+50,y);
	 glVertex2i(x+50,y-60-l);
	 glVertex2i(x,y-60-l);
	glEnd();
}

void level1()
{
	glColor3f(0.2,0.5,1);
	glPointSize(10);		
	glPushMatrix();
	glTranslatef(transx,transy,0);
	if(gameover)
	 glScalef(sx,sy,0);
	glTranslatef(20,50,0);
	glRotatef(-angle,0,0,1);
	glTranslatef(-20,-50,0);
	draw();
	glPopMatrix();
	drawland();
	drawtop();
	obstacle(60,30,0);
	obstacle(170,30,30);
	obstacle(260,30,15);
	obstacle(370,30,20);
	top_obstacle(90,300,40);
	top_obstacle(300,300,50);
}

void counter(int count1)
{
	char val=(char)count1;
	print_text("score",400,400);
	glRasterPos3f(470,400,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,ch);
}

void decide()
{
	int decision=1;
	int value;
	if(60<=transx && transx<=110)
	{
	 if(transy<=70)	
	 {
	  gameover=1;
	  ch='0';
	  count=0;	
     }
     else
     {
	  ch='1';
	  count=1;
	 }
    }
	if(170<=transx && transx<=220)
	{
		if(transy<=70)
	    {
		  gameover=1;
	      ch='2';
	      count=2;
	    }
	    else
	    {
		  ch='3';
		  count=3;
		}
	}
	if(260<=transx && transx<=310)
	{
		if(transy<=70)
		{
		 gameover=1;
		 ch='3';
		 count=3;
	    }
	    else
	    {
		  ch='4';
		  count=4;
	    }
    }
	if(370<=transx && transx<=420)
	{
	 if(transy<=70)
	  {
		gameover=1;
		ch='5';
		count=5;
	  }
	  else
	  {
	   ch='6';
	   count=6;
	  } 
    }
	if(90<=transx && transx<=140)
	{
	  if(transy>=149)	
	  {
		gameover=1;
	    count=1;
	    ch='1';
	  }
	  else
	  {
	   ch='2';
	   count=2;
	  }
   }
	if(300<=transx && transx<=350)
	{
	  if(transy>=139)
	  {
		gameover=1;
	    ch='4';
	    count=4;
	  }
	  else
	  {
		ch='5';
		count=5;
	  }
    }
}


void over(int count1)
{
	char *gameover="GAME OVER";
	char *win="YOU WIN";
	char *lose="YOU LOSE";
	char *score="SCORE : ";
	int n=strlen(gameover);
	int i;
	char val;
	//printf("count=%d\n",count1);
	val=count;
	glColor3f(0,1,0);
	print_text(gameover,50,400);
	decide();
	if(count<6)
	{
		print_text(lose,225,400);
		//print_text(score,300,300);
	}
	else
	{
		print_text(win,225,400);
		//print_text(score,300,300);
	}
    //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)val);
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.5,0,1);	
	glColor3f(0,0,0);
	level1();
	glColor3f(0,1,0);
	counter(count);
	if(gameover)
		over(count);
	glFlush(); 
}


void update(int value)
{
	if(gameover && sx<3.5)
	{
		sx+=0.01;
		sy+=0.01;
		glutPostRedisplay();
		glutTimerFunc(500,update,0);
	}
	if(start && !value && !gameover)	
	{
		transx+=1;
		if(transy<0)
		flag=0;
		else
		transy-=1;
		angle+=15;
		if(angle>=360)
		 angle-=360;
		if(transx>=500)
		{
		 transx+=0;
		 over(count);
		}
		decide();
	}
	if(transx>500)
	 glutTimerFunc(25,update,1);
	else
	 {
	  glutPostRedisplay();
	  glutTimerFunc(25,update,0);
	 }
}


int colors[4][4]={{.5,.5,1,1},{0.5,0.25,0.5,1},{0.5,1,1,1},{1,0.5,0.25,1}};
int i=0;
void keyboard(unsigned char ch,int x,int y)
{
	if(ch=='w')
	{
	 transy+=30;
	 flag=1;
	 welcome=(welcome+1)%5;
	 if(welcome==3)
	 {
		i=(i+1)%4;
		glClearColor(colors[i][0],colors[i][1],colors[i][2],colors[i][3]);
	 }
	}
	else if(ch=='x')
	 start=1;
	
	x_max=transx+50;
}

void menu(int id)
{
	switch(id)
	{
		case 1: start=1;
				break;
		case 2: start=0;
				break;
		default: break;
	}
}

void myinit()
{
	glClearColor(1,1,1,1);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluOrtho2D(0,499,0,499);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("project");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glDisable(GL_TEXTURE_2D);
	glutKeyboardFunc(keyboard);
	glutCreateMenu(menu);
	glutAddMenuEntry("start",1);
	glutAddMenuEntry("stop",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(25,update,0);
	myinit();
	
	//printf("count=%d\n",count);
	glutMainLoop();
}


