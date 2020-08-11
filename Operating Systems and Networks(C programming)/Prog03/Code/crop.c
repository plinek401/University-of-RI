#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include "imageIO/imageIO_TGA.h"

#define LOG_PATH	"cropLog.txt"

//Function Declarations
int checkFileExist(char* path);
char* generateOutputPath(char* input, char* output);
char* outputCropName(char* rootName, char* output);

//Struct
typedef	struct ImageInfoStruct {
    unsigned char* raster;
    unsigned int numCols;
    unsigned int numRows;
    unsigned int bytesPerPixel;
    unsigned int bytesPerRow;
} ImageStruct;

//This function helps build the pieces that will become the output name
char* generateOutputPath(char* input, char* output){
    int indexDot = 0;
    int indexSlash = 0;
    int index = 0;
    //Loops and finds where the last slash is and the last period is. The characters between those 2 indexes is the rootName. ex ../Images/clown.tga returns "clown"
    while(input[index] != '\0'){
        if(input[index] == '/'){
            indexSlash = index;
        }
        if(input[index] == '.'){
            indexDot = index;
        }
            index++;
    }

    int i;
    int rootNameLen = indexDot-indexSlash;

    char* rootName = (char*)malloc(sizeof(char)*rootNameLen+1);

    for(i = 1; i < rootNameLen; ++i){
        rootName[i-1] = input[indexSlash + i];
    }
    rootName[i-1] = '\0';

    //Check if outputPath directory slash exists. if it does, removes it. so "../Output/" becomes "../Output". This gets added back later, but for consistency sake.
    int outputLen = strlen(output);
    if(output[outputLen-1] == '/'){
        output[outputLen-1] = '\0';
    }

    char* outputName = outputCropName(rootName, output);
    free(rootName);
    rootName = NULL;
    return outputName;
}

//TThis function creates the output name after generateOutputName creates the pieces.
char* outputCropName(char* rootName, char* output){
    int rootNameLen = strlen(rootName);
    char* temp = (char*)malloc(sizeof(char)*rootNameLen+20);

    char strIndex[3];
    int index = 0;
    //Loops until a file whos name doesnt exist name is generated. Then returns that output name.
    while(1){
        strcpy(temp, output);
        temp[strlen(temp)] = '\0';
        strcat(temp, "/");
        temp[strlen(temp)] = '\0';
        if(index > 0){
            sprintf(strIndex, "%d", index);
        }
        strcat(temp, rootName);
        temp[strlen(temp)] = '\0';
        strcat(temp, "[cropped");
        temp[strlen(temp)] = '\0';
        if(index > 0){
            strcat(temp, " ");
            temp[strlen(temp)] = '\0';
            strcat(temp, strIndex);
            temp[strlen(temp)] = '\0';
        }
        strcat(temp, "].tga");
        temp[strlen(temp)] = '\0';
        if(checkFileExist(temp) == 1){
            break;
        }
        index++;
    }
    return temp;
}
//Function to check existence of a file by looking in the path.
int checkFileExist(char* path){
    if(access(path, F_OK) != -1){
        //Exists
        return 0;
    }
    else{
        //Doesn't Exist
        return 1;
    }
}

int main(int argc, char** argv){
    //LOG maintaining variables
    FILE * fp;
    if(checkFileExist(LOG_PATH) == 1){
        fp = fopen (LOG_PATH,"w");
    }
    else{
        fp = fopen (LOG_PATH,"a");
    }

    ImageType imgType;
    ImageStruct inputImage;

    fprintf (fp, "Reading in Rasters..\n");
    inputImage.raster = readTGA(argv[1], &inputImage.numRows, &inputImage.numCols, &imgType);
    //Argc checks
    if(argc > 7){
        printf("Too Many Arguments. Should be (path to file, path of output, x, y, width, height).\n");
        exit(1);
    }
    if(argc < 7){
    printf("Not Enough Arguments. Should be (path to file, path to output, x, y, width, height).\n");
    exit(1);
    }
    //Converts arguments into integers.
    fprintf (fp, "Converting arguments.. Potential error if integers not entered.\n");
    int x = strtoul(argv[3], &argv[3], 10);
    int y = strtoul(argv[4], &argv[4], 10);
    int width = strtoul(argv[5], &argv[5], 10);
    int height = strtoul(argv[6], &argv[6], 10);

    //Error checks----------------------------------------------------------------------------
    fprintf (fp, "Checking Errors...\n");
    if(checkFileExist(argv[1]) == 1){
        printf("Invalid input path.\n");
        exit(1);
    }
    if(checkFileExist(argv[2]) == 1){
        printf("Invalid output path.\n");
        exit(1);
    }
    if(width < 1 || height < 1){
        printf("Error: width and height need to be greater than 1.\n");
        exit(1);
    }
    if(x < 0 || y < 0){
        printf("Error: x and y need to be greater than 0.\n");
        exit(1);
    }
    if((x + width > inputImage.numCols) || (y + height > inputImage.numRows)){
        printf("Error: Dimensions out of range.\n");
        exit(1);
    }
    if(inputImage.raster != NULL){
        switch (imgType){
            case RGBA32_RASTER:
            case FLOAT_RASTER:
                inputImage.bytesPerPixel = 4;
                break;

            case GRAY_RASTER:
                inputImage.bytesPerPixel = 1;
            break;
        }

        inputImage.bytesPerRow = inputImage.bytesPerPixel * inputImage.numCols;
    }
    else{
        printf("Reading of image file failed.\n");
        exit(-1);
    }
    //--------------------------------------------------------------------------------------------------
    fprintf (fp, "Generating Output Raster...\n");
    unsigned char* outputRaster = malloc(sizeof(unsigned char)*width*height*4);


    //CREATE OUTPUT FILE PATH
    fprintf (fp, "Generating output path..\n");
    char* outPath = generateOutputPath(argv[1], argv[2]);

    fprintf (fp, "Constructing Struct.\n");
    ImageStruct outputImage = {outputRaster, width, height, 4, width*4};

    fprintf (fp, "Cropping image..\n");
    //Nested for loop which gets rgba values both both the input image raster, and the output image raster, and assigns the input raster to output raster.
    for(unsigned int i  = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            unsigned char* input_rgba = (unsigned char*)inputImage.raster + 4*((i+y)*inputImage.numCols + (j+x));
            unsigned char* output_rgba = (unsigned char*)outputImage.raster + 4*(i*outputImage.numCols + j);
            output_rgba[0] = input_rgba[0];
            output_rgba[1] = input_rgba[1];
            output_rgba[2] = input_rgba[2];
            output_rgba[3] = input_rgba[3];
        }
    }
    fprintf (fp, "Writing TGA file...\n");
    if (writeTGA(outPath, outputRaster, outputImage.numRows, outputImage.numCols)){
        printf("Writing out of the image failed.\n");
    }
    free(outPath);
    fprintf (fp, "--------------DONE EXECUTION:---------------\n");
    printf("DONE!");
    fclose(fp);
    return 0;
}

