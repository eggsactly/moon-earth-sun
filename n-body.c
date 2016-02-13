/*	
 *	Copyright (c) 2014 - 2016 Garrett Weaver
 *
 *	n-body is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	n-body is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	printf("position.x: %f, position.y: %f, position.z: %f, speed.x: %f, speed.y %f, speed.z: %f, mass: %f\n", input->position.x, input->position.y, input->position.z, input->speed.x, input->speed.y, input->speed.z, input->mass); 
	return "";
}
