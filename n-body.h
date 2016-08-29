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
 *	along with moon-earth-sun.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef N_BODY_H
#define N_BODY_H

typedef double FloatingType; 
typedef unsigned long UnsignedType;

static const unsigned int x = 0;
static const unsigned int y = 1;
static const unsigned int z = 2;

static const FloatingType G = 6.673e-11;

/**	THREE_VECTOR_FLOAT. 
 *	The THREE_VECTOR_FLOAT struct is a container for three congruent variables in floating point.  
 */
typedef struct _THREE_VECTOR_FLOAT {
	FloatingType x;
	FloatingType y;
	FloatingType z; 
} THREE_VECTOR_FLOAT; 

/**	THREE_VECTOR_UINT. 
 *	The THREE_VECTOR_UINT struct is a container for three congruent variables in unsigned integers.  
 */
typedef struct _THREE_VECTOR_UINT {
	UnsignedType x;
	UnsignedType y;
	UnsignedType z; 
} THREE_VECTOR_UINT; 

/**	POLY_MESH. 
 *	The POLY_MESH structure is used to describe a three dimensional shape made up of points and faces. 
 *	The POLY_MESH structure contains a list of points (in 3-space) and a list of faces (made up of exactly 3 points). 
 */
typedef struct _POLY_MESH {
	unsigned int pointCount; 	/*Number of points forming the shape (number of elements of the point array) */
	unsigned int faceCount; 	/*Number of faces forming the shame (number of elements of the face array) */
	THREE_VECTOR_FLOAT * point;	/*Pointer to a list of points forming the shape. (0,0,0) is considered the center of the object. Distance is measured in meters*/
	THREE_VECTOR_UINT * face;	/*Pointer to a list of faces making up the shape, each index shall contain a vector of points, each point shall be identified by its index in the point list of this struct*/
} POLY_MESH;

/**	PARTICLE.
 *	The PARTICLE structure defines the properties of a point particle, every physical object is based on a particle.
 */
typedef struct _PARTICLE {
	THREE_VECTOR_FLOAT position;	/*Position of point in 3-space in meters */
	THREE_VECTOR_FLOAT speed; 	/*Speed of point in 3-space in meters/Second */
	FloatingType mass; 		/*Mass of point in kilograms */
} PARTICLE;

/**	BODY.
 *	The BODY struct is based on the POINT structure and adds attributes for dimension, such as a shape and angular position and velocity. 
 */
typedef struct _BODY {
	THREE_VECTOR_FLOAT axis; 		/*The angular offset from (0, 0, 0) */
	THREE_VECTOR_FLOAT angularVelocity;	/*The angular velocity of the object */
	THREE_VECTOR_FLOAT momentOfInertia;	/*The moment of inertia of the object */
	POLY_MESH shape; 			/*The poly-mesh describing the object */ 
	PARTICLE pointAttributes; 			/*The position, velocity and mass of the object */
} BODY; 

typedef enum NBodyError {
	SUCCESS, 
	OUTPUT_NULL,
	POINTLIST_NULL,
	POI_NOT_IN_RANGE,
	TIME_STEP_NOT_VALID
} NBodyError;


/** 
 *	errorParser takes an error code and outputs a human readable string of the error.
 *	@param	errorCode an error code returned from a function.
 *	@return	a human readable version of the error code. 
 */
const char * ErrorParser(NBodyError errorCode);

/**
 *	calculateNewPositionAndVelocity calculates the change in position and velocity on a point particle based on all the other particles in the system.
 *	@param	output A pointer to the point particle that the function will update to the new velocity and position of the point of interest
 *	@param	pointList A pointer to the list of particles in the n-body system.
 *	@param	elements The number of elements in pointList.
 *	@param	pointOfInterest The index of the particle in pointList that the new position and velocity will be calculated for.
 *	@param	timeStep The time amount of time, in seconds, overwhich the calculation will occur .
 *	@return An error code indicating how the function operated.
 */
NBodyError CalculateNewPositionAndVelocity(PARTICLE * output, PARTICLE * pointList,  UnsignedType elements, UnsignedType pointOfInterest, FloatingType timeStep);

/**
 *	calculateNewPositionAndVelocity calculates the change in position and velocity on a point particle based on all the other particles in the system.
 *	@param	input The particle you want to look at.
 *	@return A character array putting the point into a human readable form.
 */
const char * PointToString(PARTICLE * input);

#endif //N_BODY_H

