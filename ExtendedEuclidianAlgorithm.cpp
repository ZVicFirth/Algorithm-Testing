/*Zachary Firth
Data Structures & Algorithm Analysis COP3530
7/5/22
Program: ExtendedEuclidianAlgorithm
Purpose: To find the GCD of two integers and find the values of s and t that 
make the EEA work
*/

#include <iostream>
using namespace std;

int main()
{
    
        int a, b, q, s, t, old_s, old_t, temp, temp1, temp2, temp3;
        cout << "Enter your first integer value (a): ";
        cin >> a;
        cout << "Enter your second interger value (b): ";
        cin >> b;
        if (b > a) //In the case the 2nd integer is larger, switch them
        {
            temp = a;
            a = b;
            b = temp;
        }
        s = 0;
        t = 1;
        old_s = 1;
        old_t = 0;
        while (b != 0)  //Loop to set up the EEA equations to find the GCD, s, and t
        {
            q = a / b;
            temp1 = a % b;
            a = b;
            b = temp1;

            temp2 = s;
            s = old_s - (q * s);
            old_s = temp2;

            temp3 = t;
            t = old_t - (q * t);
            old_t = temp3;
        }
        cout << "GCD: " << a << endl;
        cout << "s=" << old_s << endl;
        cout << "t=" << old_t << endl;

     return 0;
   
}


