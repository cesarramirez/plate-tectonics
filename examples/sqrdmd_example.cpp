#include <stdio.h>
#include "sqrdmd.hpp"
#include <cstdlib>
#include <cstring>
#include <il.h>
#include <ilu.h>

ILuint GenerateSingleImage(void) 
{
    ILuint ImageName; // The image name to return.
    ilGenImages(1, &ImageName); // Grab a new image name.
    return ImageName; // Go wild with the return value.
} 

void CheckForErrors()
{
    ILenum Error;
    while ((Error = ilGetError()) != IL_NO_ERROR) { 
        printf("%d/n", Error); 
        exit(1);
    } 
}

void drawMap(const float* heightmap)
{
    ILubyte* bytes = ilGetData(); 
    ILuint width,height;
    width  = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);

    for (int y = 0; y < height; y++)
    {
       for (int x = 0; x < width; x++)
       {
          float h = heightmap[(y*width + x)];
          if (h <= 0.0f) {
            bytes[(y*width + x)] = 0;
          } else if (h >= 1.0f) {
            bytes[(y*width + x)] = 255;
          } else {
            bytes[(y*width + x)] = (ILubyte)(h * 255.0);
          }          
       }
    }
}

void save_image(float* heightmap, int width, int height, const char* filename)
{
    ILuint imageName = GenerateSingleImage();    
    CheckForErrors();
    ilBindImage(imageName);    
    CheckForErrors();
    iluScale(width, height, 32);
    CheckForErrors();

    drawMap(heightmap);   

    ilEnable(IL_FILE_OVERWRITE);
    CheckForErrors();
    ilSaveImage(filename); 
    CheckForErrors();
}

void generate(long seed, float* heightmap, int side)
{
    memset(heightmap, 0, sizeof(float) * side * side);
    sqrdmd(seed, heightmap, side, 0.7f);
    normalize(heightmap, side * side);
}

int main(int argc, char* argv[])
{
    int seed = 10;
    printf("Generating a square-diamond noise map with seed %d\n", seed);

    float heightmap_square[513 * 513];
    generate(seed, heightmap_square, 513);

    ilInit();
    iluInit();

    save_image(heightmap_square, 513, 513, "sqrdmd_square.png");
}