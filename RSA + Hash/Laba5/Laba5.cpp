#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

bool isPrime(long int prime);
long int calculateE(long int t);
long int greatestCommonDivisor(long int e, long int t);
long int calculateD(long int e, long int t);
long int encrypt(long int i, long int e, long int n);
long int decrypt(long int i, long int d, long int n);
uint64_t joaat(const std::string& str);
std::string hex(uint64_t hash);
long binpow(uint64_t a, uint64_t n, uint64_t m); //a^n mod m
uint64_t subscribe(const std::string& str, uint64_t d, uint64_t n);
bool decode(std::fstream& IFile, uint64_t signature, uint64_t d, uint64_t e, uint64_t n);

int main()
{
    std::fstream IFile;
    uint64_t sub;
    long int p, q, n, t, e, d;

    long int encryptedText[100];
    memset(encryptedText, 0, sizeof(encryptedText));

    long int decryptedText[100];
    memset(decryptedText, 0, sizeof(decryptedText));

    bool flag;
    std::string msg;

    do
    {
        std::cout << "Enter a Prime number  p :" << std::endl;
        std::cin >> p;
        flag = isPrime(p);

        if (flag == false)
        {
            std::cout << "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n" << std::endl;
        }
    } while (flag == false);


    do
    {
        std::cout << "Enter a Prime number  q :" << std::endl;
        std::cin >> q;
        flag = isPrime(q);

        if (flag == false)
        {
            std::cout << "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n" << std::endl;
        }
    } while (flag == false);

    n = p * q;
    std::cout << "\nResult of computing n = p*q = " << n << std::endl;

    t = (p - 1) * (q - 1);
    std::cout << "Result of computing Euler's totient function:\t t = " << t << std::endl;

    e = calculateE(t);
    d = calculateD(e, t);

    
    std::cout << "\nRSA public key is (n = " << n << ", e = " << e << ")" << std::endl;
    std::cout << "RSA private key is (n = " << n << ", d = " << d << ")" << std::endl;

    IFile.open("1.txt", std::ios::in);
    if (IFile.is_open())
    {
        std::getline(IFile, msg);
        std::cout << "\nThe message is: " << msg << std::endl;
    }
    else
    {
        std::cout << "\nFailed open file\n";
        IFile.close();
    }
    IFile.close();

    std::cout << "\nEncrypt\n";
    std::cout << "\nHex: " << hex(joaat(msg));
    sub = subscribe(msg, d, n);
    std::cout << "\nSubscribe: " << sub << "\n";

    std::cout << "\nDecrypt\n";
    uint64_t mySub;
    std::cout << "\nInput subscribe: "; std::cin >> mySub; 
    std::cout << std::endl;
    bool dec = decode(IFile, mySub, d, e, n);
    if (dec)
        std::cout << "Hex equals decode: true\n";
    else
        std::cout << "Hex not equals decode: false\n";

    /*
    // encryption
    for (long int i = 0; i < msg.length(); i++)
    {
        encryptedText[i] = encrypt(msg[i], e, n);
    }

    std::cout << "\nTHE ENCRYPTED MESSAGE IS:" << std::endl;

    for (long int i = 0; i < msg.length(); i++)
    {
        printf("%c", (char)encryptedText[i]);
    }


    //decryption
    for (long int i = 0; i < msg.length(); i++)
    {
        decryptedText[i] = decrypt(encryptedText[i], d, n);
    }

    std::cout << "\n\nTHE DECRYPTED MESSAGE IS:" << std::endl;

    for (long int i = 0; i < msg.length(); i++)
    {
        printf("%c", (char)decryptedText[i]);
    }
    */

    std::cout << std::endl << std::endl;
    return 0;
}

bool isPrime(long int prime)
{
    long int i, j;

    j = (long int)sqrt((long double)prime);

    for (i = 2; i <= j; i++)
    {
        if (prime % i == 0)
        {
            return false;
        }
    }

    return true;
}

long int calculateE(long int t)
{
    long int e;

    for (e = 2; e < t; e++)
    {
        if (greatestCommonDivisor(e, t) == 1)
        {
            return e;
        }
    }

    return -1;
}

long int greatestCommonDivisor(long int e, long int t)
{
    while (e > 0)
    {
        long int myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long int calculateD(long int e, long int t)
{
    long int d;
    long int k = 1;

    while (1)
    {
        k = k + t;

        if (k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}


long int encrypt(long int i, long int e, long int n)
{
    long int current, result;

    current = i - 97;
    result = 1;

    for (long int j = 0; j < e; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result;
}

long int decrypt(long int i, long int d, long int n)
{
    long int current, result;

    current = i;
    result = 1;

    for (long int j = 0; j < d; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result + 97;
}

uint64_t joaat(const std::string& str)
{
    uint64_t hash = 0;
    for (const char c : str)
    {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

std::string hex(uint64_t hash)
{
    std::stringstream ss = {};
    ss << "0x" << std::uppercase << std::hex << hash;
    return ss.str();
}

long binpow(uint64_t a, uint64_t n, uint64_t m)
{
    if (n == 0)
        return 1 % m;
    if (n % 2 == 1)
        return (binpow(a, n - 1, m) * a) % m;
    else {
        return binpow((a * a) % m, n / 2, m);
    }
}
uint64_t subscribe(const std::string& str, uint64_t d, uint64_t n)
{
    uint32_t temp = joaat(str);
    return binpow(temp, d, n);
}

bool decode(std::fstream& File, uint64_t signature, uint64_t d, uint64_t e, uint64_t n)
{
    std::string temp;
    File.open("1.txt", std::ios::in);
    if (File.is_open())
    {
        std::getline(File, temp);
    }
    else
    {
        std::cout << "\nFailed open file\n";
        File.close();
    }
    File.close();

    uint64_t hexTmp = joaat(temp);
    uint64_t S = binpow(signature, e, n);
    uint64_t CorrectS = subscribe(temp, d, n);
    std::cout << "\nHex: " << hex(hexTmp);
    std::cout << "\nSignature: " << S << "\n";
    if (S == CorrectS)
        return true;
    else
        return false;
}