#include<stdio.h>
#include<GL/glut.h>

int left_bank[] = { 1,1,1 }, right_bank[] = { 0,0,0 }, boat[] = { 0,0,0 }; //{ wolf, sheep, boat }1`
int g = 0, s = 0, w = 0, b = 0, mo = 0; //displacement values
int left = 0, right = 1, move = 0; //boat values
int right_positions[] = { 730,970,1180 }, boat_positions[] = { 130,260,360 }; //position on back and boat
int man_face = 0; //expression
int i, j, k;

void draw_pixel(GLint cx, GLint cy)
{
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}

void plotpixels(GLint h, GLint k, GLint x, GLint y)
{
	draw_pixel(x + h, y + k);
	draw_pixel(-x + h, y + k);
	draw_pixel(x + h, -y + k);
	draw_pixel(-x + h, -y + k);
	draw_pixel(y + h, x + k);
	draw_pixel(-y + h, x + k);
	draw_pixel(y + h, -x + k);
	draw_pixel(-y + h, -x + k);
}

void draw_circle(GLint h, GLint k, GLint r)
{
	GLint d = 1 - r, x = 0, y = r;
	while (y > x)
	{
		plotpixels(h, k, x, y);
		if (d < 0) d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
	plotpixels(h, k, x, y);
}

void draw_sheep(GLint d)
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //left leg
	glVertex2i(130 + d, 220);
	glVertex2i(135 + d, 220);
	glVertex2i(135 + d, 200);
	glVertex2i(130 + d, 200);
	glEnd();
	glBegin(GL_POLYGON); //right leg
	glVertex2i(165 + d, 220);
	glVertex2i(170 + d, 220);
	glVertex2i(170 + d, 200);
	glVertex2i(165 + d, 200);
	glEnd();
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 1.0); //body
	for (i = 0; i <= 20; i += 5)
		draw_circle(150 + d, 290, i);
	for (i = 0; i <= 20; i += 5)
		draw_circle(150 + d, 230, i);
	for (j = 0; j < 80; j += 40)
		for (i = 0; i <= 20; i += 5)
			draw_circle(130 + d + j, 280, i);
	for (j = 0; j < 120; j += 60)
		for (i = 0; i <= 20; i += 5)
			draw_circle(120 + d + j, 260, i);
	for (j = 0; j < 80; j += 40)
		for (i = 0; i <= 20; i += 5)
			draw_circle(130 + d + j, 240, i);
	for (i = 0; i <= 20; i += 5)
		draw_circle(150 + d, 250, i);
	glColor3f(0.0, 0.0, 0.0);
	draw_circle(140 + d, 240, 1); //ears
	draw_circle(137 + d, 240, 1);
	draw_circle(135 + d, 239, 1);
	draw_circle(160 + d, 240, 1);
	draw_circle(163 + d, 240, 1);
	draw_circle(165 + d, 239, 1);
	for (i = 0; i <= 10; i += 5) //head
		draw_circle(150 + d, 230, i);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS); //eyes
	glVertex2i(145 + d, 230);
	glVertex2i(155 + d, 230);
	glEnd();
	glPointSize(3.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(145 + d, 229);
	glVertex2i(155 + d, 229);
	glEnd();
}

void draw_wolf(GLint d)
{
	glColor3f(0.17, 0.17, 0.17);
	glBegin(GL_QUADS); //face
	glVertex2i(333 + d, 280);
	glVertex2i(333 + d, 270);
	glVertex2i(293 + d, 255);
	glVertex2i(293 + d, 285);
	glEnd();
	glBegin(GL_TRIANGLES); //ears
	glVertex2i(293 + d, 285);
	glVertex2i(293 + d, 305);
	glVertex2i(305 + d, 275);
	glVertex2i(300 + d, 285);
	glVertex2i(300 + d, 305);
	glVertex2i(313 + d, 275);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2i(293 + d, 280); //neck
	glVertex2i(293 + d, 255);
	glVertex2i(280 + d, 238);
	glVertex2i(280 + d, 270);
	glVertex2i(280 + d, 270); //body
	glVertex2i(280 + d, 238);
	glVertex2i(220 + d, 238);
	glVertex2i(220 + d, 270);
	for (i = 0; i < 52; i += 13) //legs
	{
		if (i == 26) i += 9;
		glVertex2i(220 + d + i, 238); //thigh
		glVertex2i(233 + d + i, 238);
		glVertex2i(227 + d + i, 218);
		glVertex2i(220 + d + i, 218);

		glVertex2i(220 + d + i, 218); //calf
		glVertex2i(227 + d + i, 218);
		glVertex2i(233 + d + i, 205);
		glVertex2i(227 + d + i, 205);

		glVertex2i(227 + d + i, 205); //foot
		glVertex2i(237 + d + i, 205);
		glVertex2i(237 + d + i, 200);
		glVertex2i(227 + d + i, 200);
	}
	glEnd();
	glBegin(GL_QUADS); //tail
	glVertex2i(222 + d, 265);
	glVertex2i(215 + d, 285);
	glVertex2i(225 + d, 285);
	glVertex2i(235 + d, 265);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2i(215 + d, 285);
	glVertex2i(238 + d, 300);
	glVertex2i(242 + d, 300);
	glVertex2i(225 + d, 285);
	glEnd();
	glColor3f(0.51, 0.0, 0.0); //eye
	glBegin(GL_TRIANGLES);
	glVertex2i(303 + d, 279);
	glVertex2i(303 + d, 273);
	glVertex2i(315 + d, 276);
	glEnd();
}

void draw_grass(GLint i)
{
	glColor3f(0.59, 0.37, 0.15);
	glBegin(GL_POLYGON); //box-front
	glVertex2i(5 + i, 195);
	glVertex2i(5 + i, 225);
	glVertex2i(70 + i, 225);
	glVertex2i(70 + i, 195);
	glEnd();
	glBegin(GL_POLYGON); //box-side
	glVertex2i(70 + i, 225);
	glVertex2i(70 + i, 195);
	glVertex2i(80 + i, 205);
	glVertex2i(80 + i, 235);
	glEnd();
	glColor3f(0.16, 0.70, 0.13);
	glBegin(GL_POLYGON); //grass
	glVertex2i(5 + i, 225);
	glVertex2i(70 + i, 225);
	glVertex2i(80 + i, 235);
	glVertex2i(15 + i, 235);
	glEnd();
	glColor3f(0.19, 0.49, 0.1); //grass
	for (j = 0; j < 10; j += 5)
		for (k = 0; k < 50; k += 10)
		{
			glBegin(GL_LINES);
			glVertex2i(17 + k + i, 231 - j);
			glVertex2i(22 + k + i, 233 - j);
			glVertex2i(22 + k + i, 233 - j);
			glVertex2i(27 + k + i, 231 - j);
			glEnd();
		}
	//glColor3f(0.21, 0.10, 0.0);
	glColor3f(0.16, 0.70, 0.13);
	glBegin(GL_LINES); //box lines
	glVertex2i(5 + i, 215);
	glVertex2i(70 + i, 215);
	glVertex2i(5 + i, 203);
	glVertex2i(70 + i, 203);
	glVertex2i(70 + i, 215);
	glVertex2i(80 + i, 225);
	glVertex2i(70 + i, 203);
	glVertex2i(80 + i, 213);
	glEnd();
	glColor3f(0.16, 0.70, 0.13);
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 63; k += 21)
	{
		glVertex2i(15 + i + k, 235);
		glVertex2i(20 + i + k, 265);
		glVertex2i(25 + i + k, 235);
	}
	glEnd();
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 60; k += 20)
	{
		glVertex2i(26 + i + k, 235);
		glVertex2i(31 + i + k, 250);
		glVertex2i(36 + i + k, 235);
	}
	glEnd();
}

void draw_boat(GLint i)
{
	glColor3f(0.65, 0.16, 0.16);
	glBegin(GL_POLYGON);
	glVertex2i(323 + i, 200);
	glVertex2i(623 + i, 200);
	glVertex2i(583 + i, 150);
	glVertex2i(363 + i, 150);
	glEnd();
	glColor3f(0.22, 0.15, 0.07);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2i(339 + i, 180);
	glVertex2i(607 + i, 180);
	glVertex2i(355 + i, 160);
	glVertex2i(591 + i, 160);
	glEnd();
	glLineWidth(1.0);
}

void draw_manoar(GLint i)
{
	//man
	glColor3f(1.0, 0.60, 0.63);
	draw_circle(558 + i, 280, 2); //ears
	draw_circle(602 + i, 280, 2);
	glColor3f(1.0, 0.70, 0.51);
	glPointSize(5.0);
	for (j = 0; j < 25; j += 5)
		draw_circle(580 + i, 280, 20 - j); //head
	glBegin(GL_QUADS); //neck
	glVertex2i(576 + i, 260);
	glVertex2i(576 + i, 250);
	glVertex2i(584 + i, 250);
	glVertex2i(584 + i, 260);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //hair
	glVertex2i(558 + i, 290);
	glVertex2i(565 + i, 305);
	glVertex2i(595 + i, 305);
	glVertex2i(602 + i, 290);
	glEnd();
	glBegin(GL_LINES); //eyebrows
	glVertex2i(565 + i, 285);
	glVertex2i(575 + i, 285);
	glVertex2i(585 + i, 285);
	glVertex2i(595 + i, 285);
	glEnd();
	glBegin(GL_POINTS); //eyes
	glVertex2i(570 + i, 280);
	glVertex2i(590 + i, 280);
	glEnd();
	glBegin(GL_LINES); //nose
	glVertex2i(581 + i, 278);
	glVertex2i(581 + i, 270);
	glEnd();
	if (man_face) k = 4;
	else k = 0;
	glBegin(GL_TRIANGLES); //mouth
	glVertex2i(572 + i, 267 - k);
	glVertex2i(590 + i, 267 - k);
	glVertex2i(581 + i, 263 + k);
	glEnd();
	glColor3f(0.8, 0.0, 0.0);
	glBegin(GL_QUADS); //shirt
	glVertex2i(560 + i, 250);
	glVertex2i(560 + i, 210);
	glVertex2i(600 + i, 210);
	glVertex2i(600 + i, 250);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS); //pant
	glVertex2i(560 + i, 210);
	glVertex2i(560 + i, 200);
	glVertex2i(600 + i, 200);
	glVertex2i(600 + i, 210);
	glEnd();
	glColor3f(0.51, 0.0, 0.0);
	glBegin(GL_QUADS); //sleeves
	glVertex2i(560 + i, 250);
	glVertex2i(555 + i, 240);
	glVertex2i(555 + i, 225);
	glVertex2i(560 + i, 235);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2i(600 + i, 250);
	glVertex2i(590 + i, 240);
	glVertex2i(590 + i, 225);
	glVertex2i(600 + i, 235);
	glEnd();
	glColor3f(1.0, 0.70, 0.51);
	glBegin(GL_QUADS); //hands
	glVertex2i(555 + i, 240);
	glVertex2i(545 + i, 220);
	glVertex2i(545 + i, 210);
	glVertex2i(555 + i, 225);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2i(590 + i, 240);
	glVertex2i(570 + i, 220);
	glVertex2i(570 + i, 210);
	glVertex2i(590 + i, 225);
	glEnd();

	//oar
	glColor3f(0.16, 0.11, 0.05);
	glLineWidth(7.0);
	glBegin(GL_LINES);
	glVertex2i(545 + i, 240);
	glVertex2i(623 + i, 150);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2i(622 + i, 150);
	glVertex2i(620 + i, 160);
	glVertex2i(615 + i, 150);
	glVertex2i(624 + i, 150);
	glVertex2i(614 + i, 160);
	glVertex2i(640 + i, 150);
	glEnd();
	glLineWidth(1.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	// water
	glColor3f(0.0, 0.58, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(360, 0);
	glVertex2i(323, 150);
	glVertex2i(947, 150);
	glVertex2i(910, 0);
	glEnd();

	//water lines
	glColor3f(0.0, 0.0, 0.8);
	glBegin(GL_LINES);
	for (i = 0; i < 15; i++)
		for (j = 0; j < 3; j++)
		{
			int x1 = 335 + (100 * i) - (50 * i);
			int x2 = 355 + (100 * i) - (50 * i);
			int y = 120 - (45 * j);
			glVertex2i(x1, y);
			glVertex2i(x2, y);
		}
	glEnd();

	//left land
	glColor3f(0.74, 0.49, 0.25);
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(0, 200);
	glVertex2i(323, 200);
	glVertex2i(360, 0);
	glEnd();

	//right land
	glColor3f(0.74, 0.49, 0.25);
	glBegin(GL_POLYGON);
	glVertex2i(910, 0);
	glVertex2i(947, 200);
	glVertex2i(1270, 200);
	glVertex2i(1270, 0);
	glEnd();

	//sun
	glColor3f(1.0, 0.84, 0.0);
	glPointSize(5.0);
	for (i = 0; i < 45; i += 5)
		draw_circle(635, 580, 40 - i);

	//clouds
	glColor3f(1.0, 1.0, 1.0);
	for (j = 0; j < 1200; j += 300)
	{
		if (j == 600) j += 120;
		for (i = 0; i < 25; i += 5)
			draw_circle(85 + j, 570, 20 - i);
		for (i = 0; i < 25; i += 5)
			draw_circle(115 + j, 585, 20 - i);
		for (i = 0; i < 25; i += 5)
			draw_circle(145 + j, 585, 20 - i);
		for (i = 0; i < 25; i += 5)
			draw_circle(175 + j, 570, 20 - i);
		for (i = 0; i < 25; i += 5)
			draw_circle(145 + j, 555, 20 - i);
		for (i = 0; i < 25; i += 5)
			draw_circle(115 + j, 555, 20 - i);
	}

	draw_boat(b);
	draw_manoar(mo);
	draw_wolf(w);
	draw_sheep(s);
	draw_grass(g);

	glFlush();
}

int add(int i)
{
	if (right)
	{
		if (left_bank[i] || boat[i])
		{
			boat[i] = 1; left_bank[i] = 0;
			return boat_positions[i];
		}
		return right_positions[i];
	}
	else
	{
		if (right_bank[i] || boat[i])
		{
			boat[i] = 1; right_bank[i] = 0;
			return boat_positions[i] + 300;
		}
		return 0;
	}
}

int remove(int i) //updating banks array based on boat
{
	boat[i] = 0;
	if (right)
	{
		left_bank[i] = 1;
		return 0;
	}
	else
	{
		right_bank[i] = 1;
		return right_positions[i];
	}
}

void print(GLint x, GLint y, char* str) //print text
{
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	int len = strlen(str);
	for (i = 0; i < strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	glFlush();
}


int check() //checking for winning condition
{
		for (i = 0; i < 3; i++)
			if (!right_bank[i])
				return 0;
	return 1;
}

void menu(int option)
{
	if (!move) //checking if boat is near bank or not
		switch (option)
		{
		case 1: //grass2boat
			if (boat[1]) s = remove(1); //only one passenger on boat
			if (boat[0]) w = remove(0);
			g = add(2);
			break;
		case 2:	//sheep2boat
			if (boat[2]) g = remove(2);
			if (boat[0]) w = remove(0);
			s = add(1);
			break;
		case 3: //wolf2boat
			if (boat[2]) g = remove(2);
			if (boat[1]) s = remove(1);
			w = add(0);
			break;
		default:
			if (boat[0]) w = remove(0);
			else if (boat[1]) s = remove(1);
			else if (boat[2]) g = remove(2);
			break;
		}
	display();
	if (check())
		print(600, 400, "You win!");
}

int check_eat()
{
	if (right)
	{
		if (left_bank[0] && left_bank[1])
		{
			man_face = 1;
			display();
			print(530, 400, "Wolf eats sheep! Try again");
			return 0;
		}
		else if (left_bank[1] && left_bank[2])
		{
			man_face = 1;
			display();
			print(530, 400, "Sheep eats grass! Try again");
			return 0;
		}
	}
	else
	{
		if (right_bank[0] && right_bank[1])
		{
			man_face = 1;
			display();
			print(530, 400, "Wolf eats sheep! Try again");
			return 0;
		}
		else if (right_bank[1] && right_bank[2])
		{
			man_face = 1;
			display();
			print(530, 400, "Sheep eats grass! Try again");
			return 0;
		}
	}
	return 1;
}

void update(int val)
{
	move = 1;
	b += val;
	mo += val;
	if (boat[0]) w += val;
	else if (boat[1]) s += val;
	else if (boat[2]) g += val;
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if (right) //move only if direction is towards right
			if (check_eat())
			{
				if (b == 300)
				{
					left = 1; right = 0; move = 0;
					break;
				}
				update(10);
				glutPostRedisplay();
			}
		break;
	case GLUT_KEY_LEFT:
		if (left) //move only if direction is towards left
			if (check_eat())
			{
				if (b == 10)
				{
					update(-10);
					glutPostRedisplay();
					left = 0;  right = 1; move = 0;
					break;
				}
				update(-10);
				glutPostRedisplay();
			}
		break;
	}
	man_face = 0;
}

void myInit() {
	glClearColor(0.54, 0.71, 0.94, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1270.0, 0.0, 650.0);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1270, 650);
	glutCreateWindow("Grass-Sheep-Wolf Puzzle");
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("Grass", 1);
	glutAddMenuEntry("Sheep", 2);
	glutAddMenuEntry("Wolf", 3);
	glutAddMenuEntry("None", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(keys);
	myInit();
	glutMainLoop();
}
