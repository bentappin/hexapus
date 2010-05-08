int move_up = 0;	// shall we move the ride up yet?
float move_height = 0;	// the height of the ride >=15 is full height

int tilt = 0;		// shall we tilt?
float tilt_ang = 0;	// what angle are we currently at?

int end = 0;		// is it time to end and bring the ride back to start?

int rotate_angle_v = 5;	// how much to increment by when rotating
int rotate_angle_h = 5;	// how much to increment by when rotating

int easter = 0;

void keyboard(unsigned char key,int x,int y);
void keyboardSpecial(int key, int x, int y);
