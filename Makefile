TARGET = watery
CFLAGS = `sdl-config --cflags` -D_PC_ -Wall -O3
LIBS = `sdl-config --static-libs` -lSDL_mixer -lSDL_ttf -lSDL_image -lSDL_gfx
OBJS = $(addprefix src/, main.o App.o Graphics.o Controls.o Audio.o Images.o Font.o Animations.o Sounds.o Music.o Level.o Hero.o)
CXX = g++

.SUFFIXES: .cc

.cc.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

clean:
	rm -rf $(OBJS) ./*~ $(TARGET)
