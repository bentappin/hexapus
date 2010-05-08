
INCPATH = -I /usr/X11R6/include/
LIBS = -lglut -lGLU -lGL -lXi -lXmu -lX11 -lm -lpthread
LIBPATH = -L/usr/lib -L/usr/X11R6/lib/

%:%.c
	gcc $(INCPATH) $(LIBPATH) $^ $(LIBS) -o $@

%:%.cpp
	g++ $(INCPATH) $(LIBPATH) $^ $(LIBS) -o $@

%:%.cc
	g++ $(INCPATH) $(LIBPATH) $^ $(LIBS) -o $@

