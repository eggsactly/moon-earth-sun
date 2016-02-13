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

unsigned ProcessFlags(int argc, char **argv, char ** inputFile) {
    int index, c;
    while ((c = getopt (argc, argv, "o:")) != -1){
        switch (c)
        {
            case 'o': // input file flag
                *inputFile = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(*inputFile, optarg);
                break;
            case '?':
                if (optopt == 'o')
                    fprintf (stderr, "Option -%o requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%o'.\n", optopt);
                else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort ();
        }
        
        for (index = optind; index < argc; index++)
            printf ("Non-option argument %s\n", argv[index]);
        return 0;
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    const unsigned long long numSeconds = 31536000;
    unsigned long long i;
    NBodyError error = SUCCESS;
    unsigned int stepsPerSample = 3600;
    char * inputFile = NULL;
    
    PARTICLE solarSystem[3];
    PARTICLE earth, moon, sun;
    FILE *fp;
    
    //Set up the array to record locations of the earth and the moon
    FloatingType ** recordArray;
    recordArray = (FloatingType **) malloc(sizeof(FloatingType *) * numSeconds);
    for(i = 0; i < numSeconds/stepsPerSample; i++) {
        recordArray[i] = (FloatingType *) malloc(sizeof(FloatingType) * 5);
    }
    
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
    
    // Process the input flags before running the simulation
    ProcessFlags(argc, argv, &inputFile);
    
    error = Simulate(solarSystem, sizeof(solarSystem) / sizeof(PARTICLE), numSeconds, 1.0, recordArray, stepsPerSample);
    if(error != SUCCESS) {
        printf("ERROR: %s.\n", ErrorParser(error));
    }
    
    fp = fopen(inputFile, "w+");
    
    fprintf(fp, "# Time\tMoon-x\tMoon-y\tEarth-x\tEarth-y\n");
    
    for(i = 0; i < numSeconds/stepsPerSample; i++) {
        fprintf(fp, "%f\t%f\t%f\t%f\t%f\n", recordArray[i][0], recordArray[i][1], recordArray[i][2], recordArray[i][3], recordArray[i][4]);
    }
    
    fclose(fp);
    
    for(i = 0; i < numSeconds/stepsPerSample; i++) {
        free(recordArray[i]); 
    }
    free(recordArray);
    free(inputFile);
    
    return 0; 
}
