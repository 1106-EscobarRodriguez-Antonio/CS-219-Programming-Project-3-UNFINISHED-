// Name: Antonio Escobar Rodriguez

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Functions.h"
using namespace std;

int main(){
    vector<string> filelines; // declare a allocated vector array
    uint32_t num1 = 0; // num1 and num2 store valid numbers in 32-bit hexadecimal numbers
    uint32_t num2 = 0;
    uint32_t num3 = 0;

    string condition;

    bool affectFlags = false;
    bool iscondition = false;
    bool isReg = false;

    bool n_Flag = false;
    bool z_Flag = false;
    bool c_Flag = false;
    bool v_Flag = false;


    uint32_t memory[5] = {0x0, 0x0, 0x0, 0x0, 0x0};
    uint32_t registers[12] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

    

    ifstream fin("PP3_input.txt"); //opens an input stream to the input file

    if(!fin.eof()){ // stores each line into the vector array until it gets to the end of the file
        string line; // a variable that stores each line
        /*
        this while loop grabs each line and put into the vector array using .push_back
    
        */

        while(getline(fin, line)) {
            filelines.push_back(line);
        }

    }
    /*
    after reaching the end of the input file, the input stream closes
    */
    fin.close(); // closes the input stream
    /*
    in the for loop it cycles through each line to extract the operation into the "operation" string variable,
    and get the numbers into the "number" string variable and ultimately store them into the "numbers" vector array/
    */
    for(int i = 0; i < filelines.size(); i++) {
        stringstream ss(filelines[i]);
        string junk;
        string operation; // this is where the operation is stored
        string baseOp;
        string number; // this is where the numbers are going to be stored
        vector<string> numbers; // a vector array where all the operands are going to be stored
        ss >> operation; //grabs the operation and store it in the variable

        ss.ignore();

        while (getline(ss, number, ',')) { // grabs each number and store it into the "numbers" vector array until the end of the line
            if(ss.peek() == ' '){
                ss.ignore();
            }
            numbers.push_back(number);
        }

        /*
        the results will be calculated depending on what operation is used and will print out the results in this format:

        operation num1 num2
        */

        cout << filelines[i] << endl;

            
            
        if(validOperation(baseOp, operation, numbers, num1, num2, num3, isReg, iscondition, affectFlags, condition)){ // checks to see if the operation and numbers are valid
            bool isADD = false;
            bool isSUB = false;
            // if they are, then 1 or 2 operands will be inserted to one of the function and print the result
            if(getnums(baseOp, numbers, num1, num2, num3, isReg, iscondition, registers)){
                if(validCondition(condition, n_Flag, z_Flag, c_Flag, v_Flag, iscondition)){
                    // cout << "affectFlags is " << affectFlags << endl;
                    // cout << "flags are " << n_Flag << z_Flag << c_Flag << v_Flag << endl;
                    if(baseOp == "ADD"){
                        //cout << "num3 is " << num3 << endl;
                        ADD(num1, num2, num3, isReg, registers);
                        isADD = true;
                    }
                    else if(baseOp == "SUB"){
                        SUB(num1, num2, num3, isReg, registers);
                        isSUB = true;
                    }
                    else if(baseOp == "AND"){
                        AND(num1, num2, num3, isReg, registers);
                    }
                    else if(baseOp == "ORR"){
                        ORR(num1, num2, num3, isReg, registers);
                    }
                    else if(baseOp == "EOR"){
                        EOR(num1, num2, num3, isReg, registers);
                    }
                    else if(baseOp == "CMP"){
                        CMP(num1, num2, num3, isReg, registers);
                        affectFlags = true;
                        isSUB = true;
                    }
                    else if(baseOp == "MOV"){
                        MOV(num1, num2, isReg, registers);
                    }
                    else if(baseOp == "LDR"){
                        LDR(num1, num2, registers, memory);
                    }
                    else if(baseOp == "STR"){
                        STR(num1, num2, registers, memory);
                    }
                    else if(baseOp == "LSL"){
                        LSL(num1, num2, num3, registers);
                    }
                    else if(baseOp == "LSR"){
                        LSR(num1, num2, num3, registers);
                    }
                    else if(baseOp == "MVN"){
                        MVN(num1, num2, isReg, registers);
                    }


                    else{ // if the operation is invalid it will print out this message to let the user know
                    cout << "Unsupported Operation" << endl;
                    }
                    
                
                }
                if(affectFlags){
                        updateflags(n_Flag, z_Flag, c_Flag, v_Flag, isADD, isSUB, num2, num3, num1);
                }
                display(registers, memory, n_Flag, z_Flag, c_Flag, v_Flag);  
                num1 = 0;
                num2 = 0;
                num3 = 0;
                affectFlags = false; 
            }
        }
    }
};



