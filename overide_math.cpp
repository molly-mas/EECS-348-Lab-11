//Name: Molly Masalskis
//KUID: 3171860
//Date: 11/11/25
//Assignment: EECS 348 Lab11
//Purpose: Matrix opperations with opperator overflow and exprementing with classes in C++
#include <iostream>
#include <fstream> 
#include <string>
#include <stdio.h>
#include <limits>
#include <sstream>

class MathMatrix{
    private:
        int n;
        double** data;
    
    public:
    MathMatrix(int size){
        n = size;
        data = new double*[n];
        for(int i = 0; i<n; i++){
            data[i] = new double[n];
        }
    }

    ~MathMatrix(){
        clear();
    }

    void clear(){
        if(data){
            for(int i = 0; i < n; i++){
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
            n = 0;
        }
    }
    void resize(int newnum){
        clear();
        n = newnum;
        data = new double*[n];
        for(int i = 0; i <n; i++){
            data[i] = new double[n];
        }

    }

    void add_spot(int index1 = 0, int index2 =0, int value = 100){
        data[index1][index2] = value;
    }

    void print_matrix(){
        std::cout << "Matrix: \n";
        for(int i = 0; i< n; i++){
            for(int j = 0; j<n; j++){
                std::cout << data[i][j] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    MathMatrix operator+(const MathMatrix& other) const{
        MathMatrix result(n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j<n; j++){
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    MathMatrix operator*(const MathMatrix& other) const{
        MathMatrix result(n);
        int val = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j<n; j++){
                for(int k = 0; k <n; k++){
                    val = data[i][k] * other.data[k][j];
                    val += val;
                }
                result.data[i][j] = val;
                val = 0;
            }
        }

        return result;
    }

    int grab_val(int index1, int index2){
        return data[index1][index2];
    }

    int get_size(){
        return n;
    }

    // make a deep copy
MathMatrix(const MathMatrix& other) {
    n = other.n;
    data = new double*[n];
    for (int i = 0; i < n; ++i) {
        data[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            data[i][j] = other.data[i][j]; 
        }
    }
}


MathMatrix& operator=(const MathMatrix& other) {
    if (this == &other) return *this;

    for (int i = 0; i < n; ++i) {
        delete[] data[i];
    }
    delete[] data;
    n = other.n;
    data = new double*[n];
    for (int i = 0; i < n; ++i) {
        data[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

    

};

void fill_matrixs(std::string filename, MathMatrix& m1, MathMatrix& m2){
    std::ifstream theFile (filename);
    int size;
    if (!theFile){
        throw new std::runtime_error("this file cant be found");
    }

    theFile >> size;
    m1.resize(size);
    m2.resize(size);

    for(int i = 0; i < size; i++){
        for(int j =0; j <size; j++){
            int val;
            theFile >> val; 
            m1.add_spot(i, j, val);
        }
    }

    for(int i = 0; i < size; i++){
        for(int j =0; j <size; j++){
            int val;
            theFile >> val; 
            m2.add_spot(i, j, val);
        }
    }
    theFile.close();
}

void swap_row(MathMatrix a, int index1 = 0, int index2 = 1){
    int size = a.get_size();
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
        std::cerr << "Invalid Index\n";
        throw std::exception();
    }
    for (int i = 0; i < size; ++i){
        double temp = a.grab_val(index1, i);
        a.add_spot(index1, i, a.grab_val(index2, i));
        a.add_spot(index2, i, temp);
    }
    std::cout << "Swapped Rows: \n";
    a.print_matrix();
}

void add_diag(MathMatrix a){
    int val = 0;
    int size = a.get_size();
    for(int i = 0; i <size; i++){
        val += a.grab_val(i,i);
    }
    std::cout<< "Diagonal Sum of Matrix: " << val;
}


void swap_col(MathMatrix a, int index1 =0, int index2=1){
    int size = a.get_size();
    if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0){
        std::cout << "Invalid Index\n";
        throw std::exception();
    }
    int temp;
    for(int i = 0; i<size; i++){
        temp = a.grab_val(i, index1);
        a.add_spot(i, index1, a.grab_val(i, index2));
        a.add_spot(i,index2, temp);
    }
    std::cout << "Swapped Columns: \n";
    a.print_matrix();

}

int readOptionalInt(const std::string& prompt, int defaultVal) {
    std::string line;
    std::cout << prompt;
    std::getline(std::cin, line);

    if (line.empty()) return defaultVal;

    std::stringstream ss(line);
    int value;
    ss >> value;
    if (ss.fail()) {
        std::cout << "Invalid input, using default " << defaultVal << "\n";
        return defaultVal;
    }

    return value;
}

//make main dont for get to free after adding

int main(){
    std::string filename;
    std::cout<< "Please enter the file name: ";
    std::cin >> filename;
    std::cout << "\n";
    MathMatrix m1(1);
    MathMatrix m2(1);
    fill_matrixs(filename, m1, m2);
    std::cout << "Matrix 1: \n";
    m1.print_matrix();
    std::cout << "Matrix 2: \n";
    m2.print_matrix();
    MathMatrix added = m1 + m2;
    std::cout << "Added Matrixes: \n";
    added.print_matrix();
    added.~MathMatrix();
    std::cout << "Multiplied Matrixes: \n";
    MathMatrix mult = m1 * m2;
    mult.print_matrix();
    mult.~MathMatrix();
    std::cout << "matrix1: \n";
    add_diag(m1);
    std::cout << "\n";
    std::cout << "matrix2: \n";
    add_diag(m2);
    std::cout << "\n";
    int index1 = 0, index2 = 1, num = 100;
    std::cout << "matrix1: \n";
    std::string dummy;
    std::getline(std::cin, dummy);
    index1 = readOptionalInt("Please enter the first row index(press enter to use the default): ", 0);
    index2 = readOptionalInt("Please enter the second row index(press enter to use the default): ", 1);
    swap_row(m1, index1, index2);
    index1 = 0;
    index2 = 1;
    std::cout << "matrix2: \n";
    index1 = readOptionalInt("Please enter the first row index(press enter to use the default): ", 0);
    index2 = readOptionalInt("Please enter the second row index(press enter to use the default): ", 1);
    swap_row(m2, index1, index2);
    index1 = 0;
    index2 = 1;
    std::cout << "matrix1: \n";
    index1 = readOptionalInt("Please enter the first col index(press enter to use the default): ", 0);
    index2 = readOptionalInt("Please enter the second col index(press enter to use the default): ", 1);
    swap_col(m1, index1, index2);
    index1 = 0;
    index2 = 1;
    std::cout << "matrix2: \n";
    index1 = readOptionalInt("Please enter the first col index(press enter to use the default): ", 0);
    index2 = readOptionalInt("Please enter the second col index(press enter to use the default): ", 1);
    swap_col(m2, index1, index2);
    index1 = 0;
    index2 = 0;
    num = 100;
    std::cout << "matrix1 update: \n";
    index1 = readOptionalInt("Please enter the first index to update(press enter to use the default): ", 0);
    index2 = readOptionalInt("Please enter the second index to update(press enter to use the default): ", 0);
    num = readOptionalInt("Please enter the value you would like to update(press enter to use the default): ", 100);
    m1.add_spot(index1, index2, num);
    std::cout << "Updated Matrix: \n";
    m1.print_matrix();
    index1 = 0;
    index2 = 0;
    num = 100;
    std::cout << "matrix2 update: \n";
    index1 = readOptionalInt("Please enter the first index to update(press enter to use the default): ", 0);
    index2 = readOptionalInt("Please enter the second index to update(press enter to use the default): ", 0);
    num = readOptionalInt("Please enter the value you would like to update(press enter to use the default): ", 100);
    m2.add_spot(index1, index2, num);
    std::cout << "Updated Matrix: \n";
    m2.print_matrix();
    m1.~MathMatrix();
    m2.~MathMatrix();
    return 0;
}