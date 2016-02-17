/*
 *	Copyright (c) 2016 Garrett Weaver
 *
 *	moon-earth-sun is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	moon-earth-sun is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "n-body.h"


/**
 *	Simulate takes a step in time of an n-body system and calculates new possitions and velocities for all objects in the system
 *	@param	pointList an array of points in the n-body system
 *  @param  elements size of the pointList array
 *  @param  numSteps the number of steps the simulation shall take before completing
 *  @param  timeStep the size of time step
 *  @param  record an array which all positions of all bodies are recorded into
 *  @param  stepsPerSample the number of steps the simulation takes before recording particle possitions into the record array
 *	@return	an NBodyError if anything went wrong
 */
NBodyError Simulate(PARTICLE * pointList, UnsignedType elements, UnsignedType numSteps, FloatingType timeStep, FloatingType ** record, unsigned int stepsPerSample) {
    UnsignedType step;
    UnsignedType i;
    PARTICLE * nextStep = NULL;
    NBodyError error = SUCCESS;
    nextStep = (PARTICLE *) malloc(elements * sizeof(PARTICLE));
    if(pointList == NULL) {
        return POINTLIST_NULL;
    }
    
    for(step = 0; step < numSteps; step++) {
        for(i = 0; (i < elements) && (error == SUCCESS); i++) {
            error = CalculateNewPositionAndVelocity(nextStep + i, pointList, elements, i, timeStep);
        }
        
        if((step % stepsPerSample) == 0){
            record[step/stepsPerSample][0] = step * timeStep;
            record[step/stepsPerSample][1] = pointList[1].position.x;
            record[step/stepsPerSample][2] = pointList[1].position.y;
            record[step/stepsPerSample][3] = pointList[0].position.x;
            record[step/stepsPerSample][4] = pointList[0].position.y;
        }
        for(i = 0; (i < elements) && (error == SUCCESS); i++) {
            pointList[i] = nextStep[i]; 
        }
    }
    
    free(nextStep); 
    nextStep = NULL; 
    
    return error; 
}

/**	FLAGS_USED.
 *	The FLAGS_USED struct contains booleans indicating if a flag used in the program is being used
 */
typedef struct _FLAGS_USED {
    unsigned char inputNull;
    unsigned char unknownOption;
    unsigned char conversionFailure;
    unsigned char outputFile;
    unsigned char simulationStepSize;
    unsigned char simlulationTime;
    unsigned char stepsPerSample;
} FLAGS_USED;

FLAGS_USED ProcessFlags(int argc, char **argv, char ** outputFile, FloatingType * stepSize, unsigned long long * numSeconds, unsigned int * stepsPerSample) {
    int c;
    FLAGS_USED flagsUsed;
    flagsUsed.inputNull = 0;
    flagsUsed.unknownOption = 0;
    flagsUsed.conversionFailure = 0;
    flagsUsed.outputFile = 0;
    flagsUsed.simulationStepSize = 0;
    flagsUsed.simlulationTime = 0;
    flagsUsed.stepsPerSample = 0;
    
    if((stepSize == NULL) || (numSeconds == NULL) || (stepsPerSample == NULL)){
        flagsUsed.inputNull = 1;
        return flagsUsed;
    }
    
    while ((c = getopt (argc, argv, "o:s:t:m:")) != -1){
        switch (c)
        {
            case 'o': // input file flag
                *outputFile = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(*outputFile, optarg);
                flagsUsed.outputFile = 1;
                break;
            case 's':
                *stepSize = (FloatingType) atof(optarg);
                if(*stepSize <= 0.0) {
                    flagsUsed.conversionFailure = 1;
                }
                flagsUsed.simulationStepSize = 1;
                break;
            case 't':
                *numSeconds = atoll(optarg);
                if(*numSeconds <= 0){
                    flagsUsed.conversionFailure = 1;
                }
                flagsUsed.simlulationTime = 1;
                break;
            case 'm':
                *stepsPerSample = atoi(optarg);
                if(*stepsPerSample <= 0){
                    flagsUsed.conversionFailure = 1;
                }
                flagsUsed.stepsPerSample = 1;
                break;
            case ':':
                fprintf(stderr, "Option -%c requires and operand\n", optopt);
                flagsUsed.unknownOption = 1;
                break;
            case '?':
                flagsUsed.unknownOption = 1;
                if ((optopt == 'o') || (optopt == 's') || (optopt == 't') || (optopt == 'm'))
                    fprintf (stderr, "Option -%o requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%o'.\n", optopt);
                else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n", optopt);
                return flagsUsed;
                break;
            default:
                abort();
                break;
                
        }
    }
    return flagsUsed;
}

int main(int argc, char **argv)
{
    unsigned long long i;
    NBodyError error = SUCCESS;
    FLAGS_USED flagsUsed;
    const char defaultOutputFileName[] = "output.dat";
    
    const FloatingType defaultStepSize = 1.0;
    const unsigned long long defaultNumSeconds = 31536000;
    const unsigned int defaultStepsPerSample = 3600;
    
    char * outputFile = NULL;
    FloatingType stepSize = 1.0;
    unsigned long long numSeconds = 1;
    unsigned int stepsPerSample = 1;
    
    PARTICLE solarSystem[3];
    PARTICLE earth, moon, sun;
    FILE *fp;
    
    // Process the input flags before running the simulation
    flagsUsed = ProcessFlags(argc, argv, &outputFile, &stepSize, &numSeconds, &stepsPerSample);
    
    // Specify default values for all flags not specified
    // Unknown option used
    if(flagsUsed.unknownOption) {
        return 0;
    }
    // If one of the non-pointer variables passed in were null
    if(flagsUsed.inputNull) {
        printf("Input to option parser NULL.\n");
        return 0;
    }
    if(flagsUsed.conversionFailure) {
        printf("Failed trying to convert an input value.\n");
        return 0;
    }
    if(flagsUsed.unknownOption) {
        printf("Invalid input.\n");
        return 0;
    }
    // -o flag
    if(!flagsUsed.outputFile) {
        outputFile = (char *) malloc((strlen(defaultOutputFileName) + 1) * sizeof(char));
        strcpy(outputFile, defaultOutputFileName);
    }
    // -s flag
    if(!flagsUsed.simulationStepSize) {
        stepSize = defaultStepSize;
    }
    // -t flag
    if(!flagsUsed.simlulationTime){
        numSeconds = defaultNumSeconds;
    }
    // -m flag
    if(!flagsUsed.stepsPerSample){
        stepsPerSample = defaultStepsPerSample;
    }
    
    //Set up the array to record locations of the earth and the moon
    FloatingType ** recordArray;
    recordArray = (FloatingType **) malloc(sizeof(FloatingType *) * numSeconds);
    for(i = 0; i < numSeconds/stepsPerSample; i++) {
        recordArray[i] = (FloatingType *) malloc(sizeof(FloatingType) * 5);
    }
    
    // Set intial velocity and positions of the earth, sun and moon
    earth.position.x = 0;
    earth.position.y = 1.5210e11;
    earth.position.z = 0;
    earth.speed.x = -2.929e4;
    earth.speed.y = 0;
    earth.speed.z = 0;
    earth.mass = 5.972e24;
    
    moon.position.x = 4.054e8;
    moon.position.y = 1.5210e11;
    moon.position.z = 0;
    moon.speed.x = -2.929e4;
    moon.speed.y = -964.0f;
    moon.speed.z = 0;
    moon.mass = 7.34767309e22;
    
    sun.position.x = 0;
    sun.position.y = 0;
    sun.position.z = 0;
    sun.speed.x = 0;
    sun.speed.y = 0;
    sun.speed.z = 0;
    sun.mass = 1.988500e30;
    
    solarSystem[0] = earth;
    solarSystem[1] = moon;
    solarSystem[2] = sun;
    
    // Run the simulation, putting results into RAM
    error = Simulate(solarSystem, sizeof(solarSystem) / sizeof(PARTICLE), numSeconds, stepSize, recordArray, stepsPerSample);
    if(error != SUCCESS) {
        printf("ERROR: %s.\n", ErrorParser(error));
    }
    
    // Open the output file for writing
    fp = fopen(outputFile, "w+");
    
    // Write the solar system results from RAM to Disk
    fprintf(fp, "# Time\tMoon-x\tMoon-y\tEarth-x\tEarth-y\n");
    for(i = 0; i < numSeconds/stepsPerSample; i++) {
        fprintf(fp, "%f\t%f\t%f\t%f\t%f\n", recordArray[i][0], recordArray[i][1], recordArray[i][2], recordArray[i][3], recordArray[i][4]);
    }
    // Close the file
    fclose(fp);
    
    // Deallocated contents of RAM
    for(i = 0; i < numSeconds/stepsPerSample; i++) {
        free(recordArray[i]); 
    }
    free(recordArray);
    free(outputFile);
    
    return 0; 
}
