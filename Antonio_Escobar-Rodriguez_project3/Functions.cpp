#include <iostream>
#include <sstream>

#include "Functions.h"
using namespace std;
/*
"the result is stored into the "result" variable in each of the functions, after the calculations it will print out the result
in this format: 0x12D49
*/

// variable i is the destination of the Register or memory address, j & k are the operands, isReg is a bool flag to is if its
// an i or r-type operation

void ADD(uint32_t& i, uint32_t& j, uint32_t& k, bool& isReg, uint32_t* r){
    uint32_t val1 = r[j];
    uint32_t val2 = r[k];

    if(isReg){
        r[i] = val1 + val2;
    }
    else{
        r[i] = val1 + k;
        val2 = k;
    }
    uint32_t result = r[i];

    i = result;
    j = val1;
    k = val2;

    
    
}
void SUB(uint32_t& i, uint32_t& j, uint32_t& k, bool& isReg, uint32_t* r){
    uint32_t val1 = r[j];
    uint32_t val2 = r[k];


    if(isReg){
        r[i] = r[j] - r[k];
    }
    else{
        r[i] = r[j] - k;
        val2 = k;
    }
    uint32_t result = r[i];

    i = result;
    j = val1;
    k = val2;

}

void AND(uint32_t& i, uint32_t& j, uint32_t& k, bool& isReg, uint32_t* r){
    uint32_t val1 = r[j];
    uint32_t val2 = r[k];

    if(isReg){
        r[i] = r[j] & r[k];
    }
    else{
        r[i] = r[j] & k;
        val2 = k;
    }

    uint32_t result = r[i];

    i = result;
    j = val1;
    k = val2;
}
void ORR(uint32_t& i, uint32_t& j, uint32_t& k, bool& isReg, uint32_t* r){
    uint32_t val1 = r[j];
    uint32_t val2 = r[k];

    if(isReg){
        r[i] = r[j] | r[k];
    }
    else{
        r[i] = r[j] | k;
    }   

    uint32_t result = r[i];

    i = result;
    j = val1;
    k = val2; 
}
void EOR(uint32_t& i, uint32_t& j, uint32_t& k, bool& isReg, uint32_t* r){
    uint32_t val1 = r[j];
    uint32_t val2 = r[k];
   
    if(isReg){
        r[i] = r[j] ^ r[k];
    }
    else{
        r[i] = r[j] ^ k;
        val2 = k;
    }

    uint32_t result = r[i];

    i = result;
    j = val1;
    k = val2;
}


void LSL(uint32_t& i, uint32_t& j, uint32_t& k, uint32_t* r){

    r[i] = r[j] << k;

}
void LSR(uint32_t& i, uint32_t& j, uint32_t& k, uint32_t* r){


    r[i] = r[j] >> k;

}


void MVN(uint32_t& i, uint32_t& j, bool& isReg, uint32_t* r){
    if(isReg){
        r[i] = ~r[j];
    }
    else{
        r[i] = ~j;
    }
}

void CMP(uint32_t& i, uint32_t& j, uint32_t& k, bool& isReg, uint32_t* r){
    uint32_t result = 0;
    uint32_t val1 = r[j];
    uint32_t val2 = r[k];

    if(isReg){
        result = val1 - val2;
    }
    else{
        result = val1 - k;
        val2 = k;
    }

    i = result;
    j = val1;
    k = val2;
}
void MOV(uint32_t& i, uint32_t& j, bool& isReg, uint32_t* r){
    if(isReg){
        uint32_t val = r[j];
        r[i] = val;
    }
    else{
        r[i] = j;
    }
    

}
void LDR(uint32_t& i, uint32_t& k, uint32_t* r, uint32_t* m){
    uint32_t addr = r[k];
    int index = (addr - 0x100) / 4;
    if(index >= 0 && index < 5){
        r[i] = m[index];
    }

    else{
        cout << "Invalid memory address." << endl;
    }

}
void STR(uint32_t& i, uint32_t& k, uint32_t* r, uint32_t* m){
    uint32_t addr = r[k];
    int index = (addr - 0x100) / 4;
    if(index >= 0 && index < 5){
        m[index] = r[i];
    }
    else{
        cout << "Invalid memory address." << endl;
    }
}

bool validOperation(string& baseOp, string& operation, const vector<string>& numbers, uint32_t& num1, uint32_t& num2, uint32_t& num3, bool& isReg, bool& iscondition, bool& affectFlags, string& condition) {
    baseOp = operation;
    condition.clear();
    iscondition = false;
    affectFlags = false;
    cout << "operation is " << operation << endl;
    if (operation.size() > 3) {
            string suffix = operation.substr(3);
            if (suffix == "S") {
                baseOp = operation.substr(0, 3);
                affectFlags = true;
            } else if (suffix.size() == 2) {
                if (suffix == "EQ" || suffix == "NE" || suffix == "GT" ||
                    suffix == "LT" || suffix == "GE" || suffix == "LE") {
                    baseOp = operation.substr(0, 3);
                    condition = suffix;
                    iscondition = true;
                }
            } else if (suffix.size() == 3 && suffix.back() == 'S') {
                string cond = suffix.substr(0, 2);
                if (cond == "EQ" || cond == "NE" || cond == "GT" ||
                    cond == "LT" || cond == "GE" || cond == "LE") {
                    baseOp = operation.substr(0, 3);
                    condition = cond;
                    iscondition = true;
                    affectFlags = true;
                }
            }
        }
    

    //returns true if the "operation" string variable is a valid operation, other wise return false
    if(baseOp == "ADD" || baseOp == "SUB" || baseOp == "AND" || baseOp == "ORR"
         || baseOp == "EOR" || baseOp == "LDR" || baseOp == "STR" || baseOp == "MOV" || baseOp == "CMP"
        || baseOp == "MVN" || baseOp == "LSL" || baseOp == "LSR"){
            return true;
    
    }
    else{
        return false;
    }
}
bool getnums(const string& baseOp, const vector<string>& numbers, uint32_t& num1, uint32_t& num2, uint32_t& num3, bool& isReg, bool& iscondition, uint32_t* r){
    stringstream ss;
    isReg = true;
    int num;
    
    if(baseOp == "MOV" || baseOp == "CMP" || baseOp == "LDR" || baseOp == "STR" || baseOp == "MVN") {
        // cout << "number size is " << numbers.size() << endl;  
        if(numbers.size() == 2){
                ss << numbers[0];
                // cout << "____Here 1____" << endl;
                // cout << "peek shows: " << ss.peek() << endl;
                if(ss.get() == 'R'){
                    // cout << "____Here 2____" << endl;
                    
                    ss >> hex >> num1;
                   
                    ss.clear();
                    // cout << "num 1 is " << hex << num1 << endl; 
                    ss << numbers[1];
                     // cout << "numbers[1] is " << "$" << numbers[1] << "$" << endl;
                    if(ss.peek() == '['){
                        ss.ignore();
                    }
                    if(ss.peek() == '#'){
                        ss.ignore();
                        isReg = false;
                    }
                    else if(ss.peek() == 'R'){
                        ss.ignore();
                    }
                    
                    ss >> hex >> num2;
                    
                    if(ss.peek() == ']'){
                        ss.ignore();
                    }
                      
                    if(baseOp == "LDR" || baseOp == "STR"){
                        cout << "r[num2] is " << r[num2] << endl;
                        if(r[num2] > 0x110 || r[num2] < 0x100){
                            cout << "Invalid Instruction. Memory out-of-range." << endl;
                            return false;
                        }
                    }
                }   
            }
            else{
                cout << "incorrect number of operands" << endl;
                return false;
            }
        }
    else if(baseOp == "ADD" || baseOp == "SUB" || baseOp == "AND" || baseOp == "ORR"
         || baseOp == "EOR" || baseOp == "LSL" || baseOp == "LSR"){
            if(numbers.size() == 3){
                ss << numbers[0];
                if(ss.get() == 'R'){
                    ss >> hex >> num1;
                    ss.clear();

                    ss << numbers[1];
                    if(ss.get() == 'R'){
                        ss >> hex >> num2;
                        ss.clear();

                        ss << numbers[2];
                        if(ss.get() == 'R'){
                            ss >> hex >> num3;
                            ss.clear();
                            isReg = true;
                        }
                        else if(ss.peek() == '#'){
                        ss.ignore();
                        isReg = false;
                        }
                        
                            ss >> hex >> num3;
                    }
                    else{
                        cout << "Invalid Instruction." << endl;
                        return false;
                    }
                }
                
            }
            else{
                cout << "incorrect number of operands" << endl;
                return false;
            }
         }


        else{
            cout << "incorrect number of operands" << endl;
            return false;
        }
        return true;
    }

void display(uint32_t* r, uint32_t* m, bool& n, bool& z, bool& c, bool& v){
                cout << endl;
                cout << "Register array" << endl;
                int i;
                for(i = 0; i < 12; i++){
                    cout << "R" << dec << i; 
                    cout << hex << uppercase << " = 0x" << r[i]  << " ";
                }
                cout << endl;
                cout << "NZCV: " << n << z << c << v << endl;
                cout << "Memory array" << endl;
                for(int i = 0; i < 5; i++){
                    cout <<"0x"<<m[i];
                    if(i != 4){
                    cout << ", ";
                    }
                }
                cout << endl;
                cout << endl;
}

bool validCondition(const string& condition, bool& n, bool& z, bool& c, bool& v, bool& iscondition){
    if(iscondition){
        if(condition == "GT"){
            return z == 0 && n == v;
        }
        else if(condition == "GE"){
            return n == v;
        }
        else if(condition == "LT"){
            return n != v;
        }
        else if(condition == "LE"){
            return z == 1 && n != v;
        }
        else if(condition == "EQ"){
            return z == 1;
        }
        else if(condition == "NE"){
            return z == 0;
        }

        else{
            cout << "invalid condition." << endl; 
            return false;
        }
    }
    else{
        return true;
    }
}

void updateflags(bool& n, bool& z, bool& c, bool& v, bool& isADD, bool& isSUB, uint32_t op1, uint32_t op2, uint32_t result){
    uint32_t mask;

    mask = 1 << 31;

    if((result & mask) == 1){
        n = true;
    }
    else{
        n = false;
    }
    
    if(result == 0){
        z = true;
    }
    else{
        z = false;
    }

    if(isADD){
        if(result < op1){
            c = true;
        }
        else{
            c = false;
        }

        uint32_t op1Res = op1 & mask;
        uint32_t op2Res = op2 & mask;

        if(op1Res == 1 && op2Res == 1 && (result & mask) == 0){
            v = true;
        }
        else if(op1Res == 0 && op2Res == 0 && (result & mask) == 1){
            v = true;
        }
        else{
            v = false;
        }
            
    }
    else if(isSUB){
        if(op2 > op1){
            c = true;
        }
        else{
            c = false;
        }
    }




}