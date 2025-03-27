/*Zachary Firth
Data Structures & Algorithm Analysis COP3530
7/5/22
Program: ModularExponentiation
Purpose: To use the equation a * k mod n to find the answer depending on the user's input values and 
converting k into binary for this equation
*/

#include <iostream>
using namespace std;

//Function definitions

//Function to double the size of the array in case there is not enough space
void DoubleSize(int*& K, int count, int& size)
{
    size *= 2;
    int* t = new int[size];
    for (int i = 0; i < count; i++)
    {
        t[i] = K[i];
    }
    delete[] K;
    K = t;
}

//Function to make the value k into binary (K)
void BinaryK(int * & K, int & count, int & size, int k)
{
    int tmp = k;
    while (tmp > 0)
    {
        if (count == size) //To make sure that the array has enough space
        {
            DoubleSize(K, count, size);
        }
        K[count] = tmp % 2;  //Converts k into binary represented by an aray called K
        tmp = (tmp - K[count]) / 2;
        count++;
    }
    
}

//Modular Exponentiation function using a, k in binary, and n
int ModularExpo(int a, int * & K, int n, int count_K)  
{
    int b;
    int A;
    if (n == 1)
    {
        return 0;
    }
    b = 1;
    if (K == 0)
    {
        return b;
    }
    A = a;
    if (K[0] == 1)
    {
        b = a;
    }
    for (int i = 1; i < count_K; i++)
    {
        A = (A * A) % n;
        if (K[i] == 1)
        {
            b = (A * b) % n;
        }
    }
    return b;
}

int main()
{
    int a, k, n, answer;
    int count_K = 0;
    int size_K = 1;
    int* K = new int[size_K];
    cout << "Enter a value of 'a': ";  //base
    cin >> a;
    cout << "Enter a value of 'k': ";  //exponent
    cin >> k;
    cout << "Enter a value of 'n': ";  //modulo
    cin >> n;
    BinaryK(K, count_K, size_K, k);
    answer = ModularExpo(a, K, n, count_K);
    cout << "The answer is " << answer << endl;

    return 0;
}


