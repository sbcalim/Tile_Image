# Tile_Image
Tile and give output of specified size for each piece

Compile:
g++ tile.cpp -o tile `Magick++-config --cppflags --cxxflags --ldflags --libs` `pkg-config opencv --libs --cflags`

Run:
./tile <filename>
