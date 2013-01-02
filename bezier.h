#define WIDTH 640
#define HEIGHT 480

const float BLUE[] = {0,0,0.9};
const float GREEN[] = {0,0.9,0};
const float GRAY[] = {0.4,0.4,0.4};
const float ORCHID[] = {0.8549,0.4392,0.8392};
const float RED[] = {0.9,0,0};
const float WHITE[] = {0.9,0.9,0.9};

//screen coordinates
float bx[] = {100,200,400,500};
float bx2[] = {50,300,500,600};
float by[] = {100,200,400,200};
float by1[] = {100,400,300,200};
float by2[] = {100,200,300,200};
float by3[] = {100,400,200,200};


float* screen;

int abs(int x) {
	return x > 0 ? x : -x;
}

void draw(int x, int y,float *c) {
	//draw to screen
	int p = 3*(WIDTH*y+x);
	screen[p] = c[0];
	screen[p+1] = c[1];
	screen[p+2] = c[2];
}


void swap(int* x, int* y) {
	int z = *x;
	*x = *y;
	*y = z;
}

void line(int x0,int y0, int x1, int y1, float *c) {
	//Bresenham's algorithm
	//as given in 
	//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization 
	int flip = abs(y1 - y0) > abs(x1 - x0);
	if(flip) {
		swap(&x0,&y0);
		swap(&x1,&y1);
	}
	if(x0 > x1) {
		swap(&x0,&x1);
		swap(&y0,&y1);
	}
	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int er = dx/2;
	int sy = y0 < y1 ? 1 : -1;
	int y = y0;
	int x;
	for(x = x0; x1 > x; ++x) {
		if(flip)
			draw(y,x,c);
		else
			draw(x,y,c);
		er = er - dy;
		if(er < 0) {
			y = y + sy;
			er = er + dx;
		}
	}
}

void bz1(float px[], float py[], float *c) {
	//direct evaluation of the cubic Bezier curve
	float i;
	for(i = 0; 1>i; i += 0.001) {
		float j = 1-i;
		float i2 = i*i;
		float j2 = j*j;
		int x = j*j2*px[0] + 3*(i*j2*px[1] + i2*j*px[2]) + i*i2*px[3];
		int y = j*j2*py[0] + 3*(i*j2*py[1] + i2*j*py[2]) + i*i2*py[3];
		draw(x,y,c);
	}
}

float cstl(int r, int i, float u, float p[]) {
	//de Casteljau's algorithm - recursive implementation
	return r > 0 ? (1-u)*cstl(r-1,i,u,p) + u*cstl(r-1,i+1,u,p) : p[i];
}

void bz2(float px[], float py[], float *c) {
	//drawing Bezier curves using De Casteljau's algorithm
	float i;
	for(i = 0; 1>i; i += 0.001) {
		int x = cstl(3,0,i,px);
		int y = cstl(3,0,i,py);
		draw(x,y,c);
	}
}

void subdivide(float px[], float py[], float u, float leftx[], float lefty[], float rightx[], float righty[]) {
	//cubic subdivision algorithm using de Casteljau's algorithm
	//intermediates - as given in
	//www.cs.sunysb.edu/~qin/courses/geometry/4.pdf 

	leftx[0] = px[0];
	leftx[1] = cstl(1,0,u,px);
	leftx[2] = cstl(2,0,u,px);
	leftx[3] = cstl(3,0,u,px);

	lefty[0] = py[0];
	lefty[1] = cstl(1,0,u,py);
	lefty[2] = cstl(2,0,u,py);
	lefty[3] = cstl(3,0,u,py);

	rightx[0] = cstl(3,0,u,px);
	rightx[1] = cstl(2,1,u,px);
	rightx[2] = cstl(1,2,u,px);
	rightx[3] = px[3];

	righty[0] = cstl(3,0,u,py);
	righty[1] = cstl(2,1,u,py);
	righty[2] = cstl(1,2,u,py);
	righty[3] = py[3];
}
