#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <chrono>
#include <cmath>

// 실린더를 그리기 위한 GLU 객체를 정의합니다.
GLUquadricObj *quadratic;

// double로 표현되는 초 단위를 정의합니다.
using dseconds = std::chrono::duration<double>;

// 프로그램이 시작된 순간의 시간을 저장합니다. 애니메이션에 사용됩니다.
static std::chrono::time_point<std::chrono::system_clock> begin;

void DrawEngineBlock()
{
	// 엔진 블럭을 그립니다.
	glColor3d(0, 0, 0);

	// 상단 앞쪽 프레임
	glPushMatrix();
	{
		glTranslated(0, 0.9, 0.5);
		glRotated(45, 1, 0, 0);
		glScaled(1, 0.2, 0.4);
		glutWireCube(2);
	}
	glPopMatrix();

	// 상단 뒷쪽 프레임
	glPushMatrix();
	{
		glTranslated(0, 0.9, -0.5);
		glRotated(-45, 1, 0, 0);
		glScaled(1, 0.2, 0.4);
		glutWireCube(2);
	}
	glPopMatrix();

	// 상단 프레임
	glPushMatrix();
	{
		glTranslated(0, 1.25, 0);
		glScaled(1, 0.05, 0.28);
		glutWireCube(2);
	}
	glPopMatrix();

	// 상단 프레임 앞쪽 구조물
	glPushMatrix();
	{
		glTranslated(0, 1.325, 0.075);
		glScaled(0.8, 0.08, 0.03);
		glutWireCube(2);
	}
	glPopMatrix();

	// 상단 프레임 뒷쪽 구조물
	glPushMatrix();
	{
		glTranslated(0, 1.325, -0.075);
		glScaled(0.8, 0.08, 0.03);
		glutWireCube(2);
	}
	glPopMatrix();

	// 우측 프레임
	glPushMatrix();
	{
		glTranslated(1, 1.325 / 2, 0);
		glRotated(90, 0, 1, 0);
		glScaled(2, 2, 2);
		glBegin(GL_QUADS);
		glVertex3d(0.1, 0.2, 0);
		glVertex3d(0.2425, -0.2, -0.1);
		glVertex3d(-0.2425, -0.2, -0.1);
		glVertex3d(-0.1, 0.2, 0);
		glEnd();
	}
	glPopMatrix();

	// 좌측 프레임
	glPushMatrix();
	{
		glTranslated(-1, 1.325 / 2, 0);
		glRotated(-90, 0, 1, 0);
		glScaled(2, 2, 2);
		glBegin(GL_QUADS);
		glVertex3d(0.2425, 0.2, 0);
		glVertex3d(0.2425, -0.2, 0);
		glVertex3d(-0.2425, -0.2, 0);
		glVertex3d(-0.2425, 0.2, 0);
		glEnd();
	}
	glPopMatrix();
}

void DrawPistons()
{
	// 피스톤을 그립니다.
	glColor3d(0, 0, 0);

	// 앞쪽 피스톤 구멍
	glPushMatrix();
	{
		// 위치와 각도를 설정합니다.
		glTranslated(0, 0.9, 0.5);
		glRotated(-45, 1, 0, 0);

		glTranslated(0, 0, -0.2);

		// #1
		glTranslated(-0.675, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);

		// #2
		glTranslated(0.45, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);

		// #3
		glTranslated(0.45, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);

		// #4
		glTranslated(0.45, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);
	}
	glPopMatrix();

	// 뒷쪽 피스톤 구멍
	glPushMatrix();
	{
		// 위치와 각도를 설정합니다.
		glTranslated(0, 0.9, -0.5);
		glRotated(-135, 1, 0, 0);

		glTranslated(0, 0, -0.2);

		// #1
		glTranslated(-0.675, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);

		// #2
		glTranslated(0.45, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);

		// #3
		glTranslated(0.45, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);

		// #4
		glTranslated(0.45, 0, 0);
		gluCylinder(quadratic, 0.21, 0.21, 0.4, 24, 3);
	}
	glPopMatrix();

	// 프로그램이 시작한 이후 몇 초가 흘렀는지 계산합니다.
	double seconds = std::chrono::duration_cast<dseconds>(std::chrono::system_clock::now() - begin).count();

	// 회전각을 계산합니다. 초당 720도.
	double angle = std::fmod(seconds * 720, 360);
	// 회전각의 라디안을 계산합니다.
	double angle_rad = angle * 3.14159265358979 / 180;
	// 주기의 offset를 구합니다.
	double offset = 2 * 3.14159265358979 / 8;

	// 앞쪽 피스톤
	glPushMatrix();
	{
		// 위치와 각도를 설정합니다.
		glTranslated(0, 0.9, 0.5);
		glRotated(-45, 1, 0, 0);

		// #1
		glTranslated(-0.675, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 0) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();

		// #2
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 1) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();

		// #3
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 7) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();

		// #4
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 4) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// 뒷쪽 피스톤
	glPushMatrix();
	{
		// 위치와 각도를 설정합니다.
		glTranslated(0, 0.9, -0.5);
		glRotated(-135, 1, 0, 0);

		// #1
		glTranslated(-0.675, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 5) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();

		// #2
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 6) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();

		// #3
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 2) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();

		// #4
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			glTranslated(0, 0, (std::cos(angle_rad - offset * 3) + 1) / 2 * -0.35);
			gluCylinder(quadratic, 0.20, 0.20, 0.2, 48, 3);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// 앞쪽 커넥팅 로드
	glPushMatrix();
	{
		// 위치와 각도를 설정합니다.
		glTranslated(0, 0.4, 0);
		glRotated(-45, 1, 0, 0);

		// #1
		glTranslated(-0.65, 0, 0.3 + 0.175);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 0) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 0) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 0) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();

		// #2
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 1) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 1) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 1) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();

		// #3
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 7) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 7) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 7) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();

		// #4
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 4) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 4) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 4) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// 뒷쪽 커넥팅 로드
	glPushMatrix();
	{
		// 위치와 각도를 설정합니다.
		glTranslated(0, 0.4, 0);
		glRotated(-135, 1, 0, 0);

		// #1
		glTranslated(-0.65, 0, 0.3 + 0.175);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 5) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 5) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 5) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();

		// #2
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 6) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 6) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 6) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();

		// #3
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 2) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 2) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 2) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();

		// #4
		glTranslated(0.45, 0, 0);
		glPushMatrix();
		{
			// 회전각에 따른 sin과 cos 값을 계산합니다.
			double sin	 = std::sin(angle_rad - offset * 3) / 2 * 0.35;
			double cos	 = std::cos(angle_rad - offset * 3) / 2 * 0.35;
			double cos01 = (std::cos(angle_rad - offset * 3) + 1) / 2 * -0.35;

			// 크랭크와 맞닿게 원 운동을 합니다.
			glTranslated(0, sin, cos01);

			// 각도를 계산해 끝 점을 기준으로 회전합니다.
			glTranslated(0, 0, -0.3);
			glRotated(std::atan2(sin, 0.6 + 0.175 - cos) * 180 / 3.14159265358979, 1, 0, 0);
			glTranslated(0, 0, 0.3);

			// 크기를 조절하고 큐브를 그립니다.
			glScaled(0.05, 0.05, 0.6);
			glutWireCube(1);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void DrawCrank()
{
	// 크랭크 축을 그립니다.
	glPushMatrix();
	{
		// 프로그램이 시작한 이후 몇 초가 흘렀는지 계산합니다.
		double seconds = std::chrono::duration_cast<dseconds>(std::chrono::system_clock::now() - begin).count();
		// 회전각을 계산합니다. 초당 720도.
		double angle = std::fmod(seconds * 720, 360);

		// 축
		glPushMatrix();
		{
			glTranslated(-1.1, 0.4, 0);
			glRotated(90, 0, 1, 0);
			glRotated(angle, 0, 0, 1);
			gluCylinder(quadratic, 0.08, 0.08, 2.2, 8, 4);
		}
		glPopMatrix();

		glPushMatrix();
		{
			// 저널 베어링

			// #1
			glTranslated(-0.725, 0.4, 0);
			glPushMatrix();
			{
				glRotated(90, 0, 1, 0);
				glRotated(angle, 0, 0, 1);
				gluCylinder(quadratic, 0.175, 0.175, 0.1, 12, 3);
			}
			glPopMatrix();

			// #2
			glTranslated(0.45, 0, 0);
			glPushMatrix();
			{
				glRotated(90, 0, 1, 0);
				glRotated(angle, 0, 0, 1);
				gluCylinder(quadratic, 0.175, 0.175, 0.1, 12, 3);
			}
			glPopMatrix();

			// #3
			glTranslated(0.45, 0, 0);
			glPushMatrix();
			{
				glRotated(90, 0, 1, 0);
				glRotated(angle, 0, 0, 1);
				gluCylinder(quadratic, 0.175, 0.175, 0.1, 12, 3);
			}
			glPopMatrix();

			// #4
			glTranslated(0.45, 0, 0);
			glPushMatrix();
			{
				glRotated(90, 0, 1, 0);
				glRotated(angle, 0, 0, 1);
				gluCylinder(quadratic, 0.175, 0.175, 0.1, 12, 3);
			}
			glPopMatrix();
		}
		glPopMatrix();

		// 플라이 휠
		glPushMatrix();
		{
			glTranslated(-1.135, 0.4, 0);
			glRotated(90, 0, 1, 0);
			glRotated(angle, 0, 0, 1);
			gluCylinder(quadratic, 0.4, 0.4, 0.11, 48, 4);
			gluCylinder(quadratic, 0.375, 0.375, 0.11, 48, 4);
		}
		glPopMatrix();

		// 출력 기어
		glPushMatrix();
		{
			glTranslated(1, 0.4, 0);
			glRotated(90, 0, 1, 0);
			glRotated(angle, 0, 0, 1);
			gluCylinder(quadratic, 0.3, 0.3, 0.05, 24, 2);
			gluCylinder(quadratic, 0.275, 0.275, 0.05, 24, 2);
			gluCylinder(quadratic, 0.25, 0.25, 0.05, 24, 2);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void MyDisplay()
{
	// 장면이 매번 다시 그려지므로 MyReshape이 아닌 MyDisplay 함수에서 modelview 행렬을 재설정합니다.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);

	// 프로그램이 시작한 이후 몇 초가 흘렀는지 계산합니다.
	double seconds = std::chrono::duration_cast<dseconds>(std::chrono::system_clock::now() - begin).count();
	// 회전각을 계산합니다. 초당 30도.
	double angle = std::fmod(seconds * 30.0, 360.0);

	// y축을 기준으로 엔진 전체를 회전시킵니다.
	glRotated(angle, 0, 1, 0);

	// 엔진을 그립니다.
	glClear(GL_COLOR_BUFFER_BIT);
	{
		DrawEngineBlock();
		DrawPistons();
		DrawCrank();
	}
	// 더블 버퍼링용 버퍼 스왑
	glutSwapBuffers();
}

void MyReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (GLdouble)w / (GLdouble)h, 1.0, 50.0);
	glutPostRedisplay();
}

void MyIdle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	// GLU Quadric 객체 생성
	quadratic = gluNewQuadric();

	// 시작 시간 저장
	begin = std::chrono::system_clock::now();

	glutInit(&argc, argv);
	// 더블 버퍼링 활성화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(MyIdle);
	glutMainLoop();

	gluDeleteQuadric(quadratic);

	return 0;
}
