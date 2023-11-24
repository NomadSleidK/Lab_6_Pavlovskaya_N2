#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>

using namespace std;

class Factory
{
public:
    virtual void CreatuerElement() = 0;
    virtual void DeleteElement() = 0;
};

class T1: public Factory
{
private:
    string SymbString; //символьная строка
    string Name;
    bool offset;
    vector <string> sdvigArray;
    
public:
    
    void CreatuerElement()
    {
        cin >> Name >> SymbString;
        offset = false;
    }
    
    void DeleteElement()
    {
        
    }
    
    void Sdvig(int kol)
    {
        int lastPos = int(SymbString.size()) - 1;
        char boofer;
        
        for (int x = 0; x < kol; x++)
        {
            boofer = SymbString[0];
            
            for (int i = 0; i < lastPos; i++)
            {
                SymbString[i] = SymbString[i + 1];
            }
            
            SymbString[lastPos] = boofer;
        }
    }
    
    void SdvigCorrect()
    {
        int nomber = 0;
        
        cin >> nomber;
        offset = true;
        Sdvig(nomber);
        sdvigArray.insert(sdvigArray.begin(), "sdvig" + to_string(nomber));
    }
    
    void DispleyOffset()
    {
        int size = int(sdvigArray.size());
        for (int i = 0; i < size; i++)
        {
            cout << sdvigArray[i] << ' ';
        }
    }
    
    string GetSymbString()
    {
        return SymbString;
    }
    
    void DispleyValue()
    {
        cout << SymbString << endl;
    }
    
    void DispleyName()
    {
        if (offset == true)
        {
            DispleyOffset();
            cout << Name << ' ';
        }
        else
        {
            cout << Name << ' ';
        }
    }
};

class T2: public Factory
{
private:
    string HexString; //шестнадцатиричная строка
    string Name;
    int offset;
    
public:
    
    void CreatuerElement()
    {
        cin >> Name >> HexString;
        offset = 0;
    }
    
    void DeleteElement()
    {
        offset = 0;
    }
    
    string GetHexString()
    {
        return HexString;
    }
    
    string Sdvig(int kol)
    {
        int lastPos = int(HexString.size()) - 1;
        char boofer;
        string hexBoofer = HexString;
        
        for (int x = 0; x < kol; x++)
        {
            boofer = hexBoofer[0];
            
            for (int i = 0; i < lastPos; i++)
            {
                hexBoofer[i] = hexBoofer[i + 1];
            }
            
            hexBoofer[lastPos] = boofer;
        }
        return hexBoofer;
    }
    
    string SdvigCorrect()
    {
        string hexBoofer;
        
        cin >> offset;
        hexBoofer = Sdvig(offset);
        return hexBoofer;
    }
    
    void DispleyValue()
    {
        cout << HexString << endl;
    }
    
    void DispleyName()
    {
        if (offset != 0)
        {
            cout << "sdvig" << offset << ' ' << Name << ' ';
        }
        else
        {
            cout << Name << ' ';
        }
    }
};

int WhatSupper(char simbol)
{
    int result = 0;
    
    switch (simbol) {
        case 'a':
            result = 10;
            break;
        case 'b':
            result = 11;
            break;
        case 'c':
            result = 12;
            break;
        case 'd':
            result = 13;
            break;
        case 'e':
            result = 14;
            break;
        case 'f':
            result = 15;
            break;
    }
    
    return result;
}

long long ConvertationToInt(string HexString)
{
    long long result = 0;
    int arraySize = int(HexString.size());
    int stepen = arraySize - 1;
    vector <int> normalArray;
    
    for (int i = 0; i < arraySize; i++)
    {
        if (islower(HexString[i]))
        {
            normalArray.push_back(WhatSupper(HexString[i]));
        }
        else
        {
            normalArray.push_back(int(HexString[i] - '0'));
        }
    }
    
    for (int k = 0; k < arraySize; k++)
    {
        result += normalArray[k] * pow(16, stepen);
        stepen--;
    }
    return result;
}

string T1Sum(T1 ElemA, T1 ElemB, bool isSum)
{
    string result = ElemA.GetSymbString();
    
    if(isSum == true)
    {
        result += ElemB.GetSymbString();
    }
    return result;
}

void SumOperations(T1 ElemA, T1 ElemB)
{
    ElemA.DispleyName();
    ElemA.DispleyValue();

    ElemB.DispleyName();
    ElemB.DispleyValue();

    ElemA.DispleyName();
    cout << "+ ";
    ElemB.DispleyName();
    cout << T1Sum(ElemA, ElemB, true) << endl;
    
    ElemA.DispleyName();
    cout << "- ";
    ElemB.DispleyName();
    cout << T1Sum(ElemA, ElemB, false) << endl;
}

void HexSum(T2 ElemC, T2 ElemD, int code)
{
    long long a = 0;
    long long b = 0;
    string hexBoofer;
    
    switch (code) {
        case 0:
            a = ConvertationToInt(ElemC.GetHexString());
            b = ConvertationToInt(ElemD.GetHexString());
            break;
        case 1:
            hexBoofer = ElemC.SdvigCorrect();
            a = ConvertationToInt(hexBoofer);
            b = ConvertationToInt(ElemD.GetHexString());
            
            ElemC.DispleyName();
            cout << hexBoofer << endl;
            
            ElemD.DispleyName();
            ElemD.DispleyValue();

            break;
        case 2:
            hexBoofer = ElemD.SdvigCorrect();
            a = ConvertationToInt(ElemC.GetHexString());
            b = ConvertationToInt(hexBoofer);
            
            ElemC.DispleyName();
            ElemC.DispleyValue();
            
            ElemD.DispleyName();
            cout << hexBoofer << endl;
            break;
    }
    
    ElemC.DispleyName();
    cout << "+ ";
    ElemD.DispleyName();
    cout << hex << a + b << endl;
    ElemC.DeleteElement();
    ElemD.DeleteElement();
}

void Control(T1 ElemA, T1 ElemB, T2 ElemC, T2 ElemD)
{
    int comand = 0;
    string hexBoofer;
    
    do
    {
        cin >> comand;
        switch (comand) {
            case 1:
                ElemA.SdvigCorrect();
                SumOperations(ElemA, ElemB);
                break;
            case 2:
                ElemB.SdvigCorrect();
                SumOperations(ElemA, ElemB);
                break;
            case 3:
                HexSum(ElemC, ElemD, 1);
                break;
            case 4:
                HexSum(ElemC, ElemD, 2);
                break;
        }
    }
    while(comand != 0);
}

int main()
{
    T1 ElemA, ElemB;
    T2 ElemC, ElemD;
    
    ElemA.CreatuerElement();
    ElemB.CreatuerElement();
    ElemC.CreatuerElement();
    ElemD.CreatuerElement();
    
    SumOperations(ElemA, ElemB);
    
    ElemC.DispleyName();
    ElemC.DispleyValue();
    
    ElemD.DispleyName();
    ElemD.DispleyValue();
    
    HexSum(ElemC, ElemD, 0);
    
    Control(ElemA, ElemB, ElemC, ElemD);
    
    return 0;
}
