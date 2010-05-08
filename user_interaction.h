int move_up = 0;	// shall we move the ride up yet?
float move_height = 0;	// the height of the ride >=15 is full height

int tilt = 0;		// shall we tilt?
float tilt_ang = 0;	// what angle are we currently at?

int end = 0;		// is it time to end and bring the ride back to start?

int view_rotation_v = 5;
int view_rotation_h = 5;

void keyboard(unsigned char key,int x,int y);
void keyboard_special(int key, int x, int y);
