#include "crypt.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

string GetFileName(const string& fullFileName);
string GetFileSuffix(const string& fullFileName);

int main()
{
    do
    {
        printf("What do you want me to do, encryption or decryption? input e or d:\n");
        char input;
        cin >> input ;
        switch(input)
        {
        case 'd':
            printf("input path of file which you want to decryt:\n");
            break;
        case 'e':
            printf("input path of file which you want to encryt:\n");
            break;
        default :
            printf("not surported input!\n");
            continue;
        }
        string inputFilePath;
        cin >> inputFilePath;
        string outputFilePath;
        try
        {
            system_clock::time_point start;
            Crypt  tool;
            printf("input file HASH CODE = %s\n", tool.GenerateSHA256(inputFilePath).c_str());
            if(input == 'e')
            {
                printf("I will output encrypted file in the same directory as the origin file and name it by adding a suffix \" -encrypted \"\n");
                printf("Encryting... ... ... ");
                start = system_clock::now();
                outputFilePath = GetFileName(inputFilePath) + "-encrypted." + GetFileSuffix(inputFilePath);
                tool.Encrypt(inputFilePath, outputFilePath);
                printf("\n");
            }
            else if(input == 'd')
            {
                printf("I will output decrypted file in the same directory as the encrypted file and name it by adding a suffix \" -decrypted \"\n");
                outputFilePath = GetFileName(inputFilePath) + "-decrypted." + GetFileSuffix(inputFilePath);
                printf("Decryting... ... ... ");
                start = system_clock::now();
                tool.Decrypt(inputFilePath, outputFilePath);
                printf("\n");
            }
            auto end   = system_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout <<  "Succeed! "<< duration.count()<< "ms cost" << endl;
            printf("output HASH CODE = %s\n", tool.GenerateSHA256(outputFilePath).c_str());
        }
        catch(const char* e)
        {
            printf("sorry programme go wrong !\n");
            printf("%s\n", e);
            continue;
        }
    }while(true);
    return 1;
}

string GetFileName(const string& fullFileName)
{
    size_t posOfDell = fullFileName.find_last_of(".");
    if(posOfDell == string::npos)
    {
        throw "illegal file name!";
    }
    string reslut;
    reslut = fullFileName.substr(0, posOfDell);
    return move(reslut);
}

string GetFileSuffix(const string& fullFileName)
{
    size_t posOfDell = fullFileName.find_last_of(".");
    if(posOfDell == string::npos)
    {
        throw "illegal file name!";
    }
    string reslut;
    reslut = fullFileName.substr(posOfDell + 1);
    return move(reslut);
}
