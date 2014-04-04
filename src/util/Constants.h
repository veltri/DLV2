/*
 *
 *  Copyright 2014 Mario Alviano, Carmine Dodaro, Francesco Ricca and
 *                 Pierfrancesco Veltri.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

/* 
 * File:   Constants.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 16.29
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

// Input builder constants
#define INPUT_TESTING_OBJECTS 0
#define INPUT_DLV_DB 1
#define INPUT_IN_MEMORY 2

// Output builder constants
#define OUTPUT_ASPCORE2 0
#define OUTPUT_SILENT 1

// DLV2 constants 
#define DLV2_STRING "DLV 2.0\n"

// Error messages
#define ERRORPARSING "\nError during parsing"
#define ERRORGENERIC "\nGeneric error"
#define ERRORPARSINGCODE 100
#define ERRORGENERICCODE 110

// New types
typedef unsigned int INPUT_HANDLING_POLICY;
typedef unsigned int OUTPUT_POLICY;

#endif	/* CONSTANTS_H */

