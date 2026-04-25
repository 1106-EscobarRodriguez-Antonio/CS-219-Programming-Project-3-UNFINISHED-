#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//operation functions
void ADD(uint32_t&, uint32_t&, uint32_t&, bool&, uint32_t*); // adds two numbers together
void SUB(uint32_t&, uint32_t&, uint32_t&, bool&, uint32_t*); // subtract two numbers together
void AND(uint32_t&, uint32_t&, uint32_t&, bool&, uint32_t*); // compares the bits of 2 numbers, returns 1 if both bits are 1
void ORR(uint32_t&, uint32_t&, uint32_t&, bool&, uint32_t*); // comapares the bits of 2 numbers, returns 1 if one of the bits are 1
void EOR(uint32_t&, uint32_t&, uint32_t&, bool&, uint32_t*); // compares the bits of 2 numbers, returns 1 if both bits are not the same

void LSL(uint32_t&, uint32_t&, uint32_t&, uint32_t*); // logical shift left, shifts each bit left by one bit positon, shift 0 into the LSB
void LSR(uint32_t&, uint32_t&, uint32_t&, uint32_t*); // logical shift right, shifts each bit right by one bit positon, shift 0 into the MSB

void MVN(uint32_t&, uint32_t&, bool&, uint32_t*);

void CMP(uint32_t&, uint32_t&, uint32_t&, bool&, uint32_t*); // compares two numbers and update z flag
void MOV(uint32_t&, uint32_t&, bool&, uint32_t*); // moves value to the destination register
void LDR(uint32_t&, uint32_t&, uint32_t*, uint32_t*); // load a value from memory to a register
void STR(uint32_t&, uint32_t&, uint32_t*, uint32_t*); // Store a value from register to memory


/*
the "validOperation" function check to see if the operation and numbers are valid, if they are then the getnums function 
receives the numbers and put in num1 and num2
*/
bool validOperation(string&, string&, const vector<string>&, uint32_t&, uint32_t&, uint32_t&, bool&, bool&, bool&, string&);
bool getnums(const string&, const vector<string>&, uint32_t&, uint32_t&, uint32_t&, bool&, bool&, uint32_t*);
bool validCondition(const string&, bool&, bool&, bool&, bool&, bool&);
void updateflags(bool&, bool&, bool&, bool&, bool&, bool&, uint32_t, uint32_t, uint32_t);

void display(uint32_t*, uint32_t*, bool&, bool&, bool&, bool&);

#endif