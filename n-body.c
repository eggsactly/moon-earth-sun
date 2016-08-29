/*	
 *	Copyright (c) 2014 - 2016 W.A. Garrett Weaver
 *
 *	This file is part of moon-earth-sun.
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
 *	along moon-earth-sun.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "n-body.h"

NBodyError CalculateNewPositionAndVelocity(PARTICLE * output, PARTICLE * pointList, UnsignedType elements, UnsignedType pointOfInterest, FloatingType timeStep) {
	
	THREE_VECTOR_FLOAT distanceComponent;
	FloatingType distance, acceleration;
	UnsignedType i;

	//Error checking
	if(output == NULL) {
		return OUTPUT_NULL;
	}
	if(pointList == NULL) {
		return POINTLIST_NULL;
	}
	if(pointOfInterest >= elements) {
		return POI_NOT_IN_RANGE;
	}
	if(timeStep <= 0.0f) {
		return TIME_STEP_NOT_VALID;
	}
	*output = pointList[pointOfInterest]; 

	for(i = 0; i < elements; i++) {
		distanceComponent.x = pointList[i].position.x - pointList[pointOfInterest].position.x;
		distanceComponent.y = pointList[i].position.y - pointList[pointOfInterest].position.y;
		distanceComponent.z = pointList[i].position.z - pointList[pointOfInterest].position.z;

		distance = sqrt(pow(distanceComponent.x, 2) + pow(distanceComponent.y, 2) + pow(distanceComponent.z, 2));
		
		acceleration = (distance != 0.0f) ? (G * pointList[i].mass) / (pow(distanceComponent.x, 2) + pow(distanceComponent.y, 2) + pow(distanceComponent.z, 2)) : 0;
		output->speed.x += (distance != 0.0f) ? ((acceleration) * timeStep) * (distanceComponent.x / distance) : 0;
		output->speed.y += (distance != 0.0f) ? ((acceleration) * timeStep) * (distanceComponent.y / distance) : 0;
		output->speed.z += (distance != 0.0f) ? ((acceleration) * timeStep) * (distanceComponent.z / distance) : 0;
	}

	output->position.x += output->speed.x * timeStep;
	output->position.y += output->speed.y * timeStep;
	output->position.z += output->speed.z * timeStep;

	return SUCCESS; 
}

const char * ErrorParser(NBodyError errorCode) {
	switch (errorCode) {
		case SUCCESS:
			return "no errors";
			break;
		case OUTPUT_NULL:
			return "destination pointer is null";
			break;
		case POINTLIST_NULL:
			return "particle array is null";
			break;
		case POI_NOT_IN_RANGE:
			return "point of interest is not in range";
			break;
		case TIME_STEP_NOT_VALID:
			return "time step is less than or equal to zero";
			break;
		default:
			return "unknown error";
			break; 
	}
}

const char * PointToString(PARTICLE * input) {
    const size_t retStrLen = 1024;
    char * outputVal = (char *) malloc(sizeof(char) * retStrLen);
	snprintf(outputVal, retStrLen, "position.x: %f, position.y: %f, position.z: %f, speed.x: %f, speed.y %f, speed.z: %f, mass: %f\n", input->position.x, input->position.y, input->position.z, input->speed.x, input->speed.y, input->speed.z, input->mass);
	return outputVal;
}
