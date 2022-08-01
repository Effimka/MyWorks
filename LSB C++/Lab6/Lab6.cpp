#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma warning(disable : 4996)
using namespace std;

typedef struct
{
    unsigned int    bfType;
    unsigned long   bfSize;
    unsigned int    bfReserved1;
    unsigned int    bfReserved2;
    unsigned long   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    unsigned int    biSize;
    int             biWidth;
    int             biHeight;
    unsigned short  biPlanes;
    unsigned short  biBitCount;
    unsigned int    biCompression;
    unsigned int    biSizeImage;
    int             biXPelsPerMeter;
    int             biYPelsPerMeter;
    unsigned int    biClrUsed;
    unsigned int    biClrImportant;
} BITMAPINFOHEADER;

typedef struct
{
    int   rgbBlue;
    int   rgbGreen;
    int   rgbRed;
    int   rgbReserved;
} RGBQUAD;

typedef union
{
    uint8_t my_byte;
    struct
    {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } my_bits;
} my_conv;



void ReadBMPFile(const string& FileName);
void EncryptBmp(const string& FileName, const string& OutputFileName, const string& Message);
void DecryptBmp(const string& FileName);
unsigned short read_u16(FILE* fp);
unsigned int   read_u32(FILE* fp);
int            read_s32(FILE* fp);
void set_u16(unsigned short value);
void set_u32(unsigned int value);
void set_s32(int value);
void print_bin(uint8_t value);
void ConvertStrChar(const string& str, char*& charArr);

FILE* pFile;
BITMAPFILEHEADER header;
BITMAPINFOHEADER bmiHeader;
RGBQUAD** rgb;

int main()
{
    /*FILE* pFile = fopen("1.bmp", "rb");

    // считываем заголовок файла
    //BITMAPFILEHEADER header;

    header.bfType = read_u16(pFile);
    header.bfSize = read_u32(pFile);
    header.bfReserved1 = read_u16(pFile);
    header.bfReserved2 = read_u16(pFile);
    header.bfOffBits = read_u32(pFile);

    // считываем заголовок изображения
    //BITMAPINFOHEADER bmiHeader;

    bmiHeader.biSize = read_u32(pFile);
    bmiHeader.biWidth = read_s32(pFile);
    bmiHeader.biHeight = read_s32(pFile);
    bmiHeader.biPlanes = read_u16(pFile);
    bmiHeader.biBitCount = read_u16(pFile);
    bmiHeader.biCompression = read_u32(pFile);
    bmiHeader.biSizeImage = read_u32(pFile);
    bmiHeader.biXPelsPerMeter = read_s32(pFile);
    bmiHeader.biYPelsPerMeter = read_s32(pFile);
    bmiHeader.biClrUsed = read_u32(pFile);
    bmiHeader.biClrImportant = read_u32(pFile);


    RGBQUAD** rgb = new RGBQUAD* [bmiHeader.biWidth];
    for (int i = 0; i < bmiHeader.biWidth; i++) {
        rgb[i] = new RGBQUAD[bmiHeader.biHeight];
    }

    for (int i = 0; i < bmiHeader.biWidth; i++) {
        for (int j = 0; j < bmiHeader.biHeight; j++) {
            rgb[i][j].rgbBlue = getc(pFile);
            rgb[i][j].rgbGreen = getc(pFile);
            rgb[i][j].rgbRed = getc(pFile);
        }

        // пропускаем последний байт в строке
        getc(pFile);
    }
    fclose(pFile);

    // выводим результат
    for (int i = 0; i < bmiHeader.biWidth; i++) {
        for (int j = 0; j < bmiHeader.biHeight; j++) {
            printf("%d %d %d\n", rgb[i][j].rgbRed, rgb[i][j].rgbGreen, rgb[i][j].rgbBlue);
        }
        printf("\n");
    }*/

    string Message;
    string FileName;
    string OutputFileName;
    int choose = 0;
    //ReadBMPFile("1.bmp");


    EncryptBmp("1.bmp", OutputFileName, "Hello Bro");
    cout << endl;
    DecryptBmp("2.bmp");
    
    //while (choose != 3)
    //{
    //    cout << "1.encrypt \n2.decrypt \n3.Exit\n";
    //    cin >> choose;
    //    if (choose == 1)
    //    {
    //        cin.ignore(256, '\n');
    //        cout << "Please write name your file - "; getline(std::cin, FileName);
    //        cout << "Please write name for output file - "; getline(std::cin, OutputFileName);
    //        cout << "Please write your message - "; getline(std::cin, Message);
    //        cout << FileName << "\t" << OutputFileName << "\t" << Message;
    //        //EncryptBmp(FileName, OutputFileName, Message);
    //        
    //    }
    //    else if (choose == 2)
    //    {
    //    }
    //}
    //ReadBMPFile(FileName);
    
    
    return 0;
}


void ReadBMPFile(const string& FileName)
{
    char* FileNameChar = nullptr;
    ConvertStrChar(FileName, FileNameChar);

    pFile = fopen(FileNameChar, "rb");
    header.bfType = read_u16(pFile);
    header.bfSize = read_u32(pFile);
    header.bfReserved1 = read_u16(pFile);
    header.bfReserved2 = read_u16(pFile);
    header.bfOffBits = read_u32(pFile);

    // считываем заголовок изображения
    //BITMAPINFOHEADER bmiHeader;

    bmiHeader.biSize = read_u32(pFile);
    bmiHeader.biWidth = read_s32(pFile);
    bmiHeader.biHeight = read_s32(pFile);
    bmiHeader.biPlanes = read_u16(pFile);
    bmiHeader.biBitCount = read_u16(pFile);
    bmiHeader.biCompression = read_u32(pFile);
    bmiHeader.biSizeImage = read_u32(pFile);
    bmiHeader.biXPelsPerMeter = read_s32(pFile);
    bmiHeader.biYPelsPerMeter = read_s32(pFile);
    bmiHeader.biClrUsed = read_u32(pFile);
    bmiHeader.biClrImportant = read_u32(pFile);


    rgb = new RGBQUAD * [bmiHeader.biWidth];
    for (int i = 0; i < bmiHeader.biWidth; i++) {
        rgb[i] = new RGBQUAD[bmiHeader.biHeight];
    }

    for (int i = 0; i < bmiHeader.biWidth; i++) {
        for (int j = 0; j < bmiHeader.biHeight; j++) {
            rgb[i][j].rgbBlue = getc(pFile);
            rgb[i][j].rgbGreen = getc(pFile);
            rgb[i][j].rgbRed = getc(pFile);
        }

        // пропускаем последний байт в строке
        getc(pFile);
    }
    fclose(pFile);

    cout << "Header: " << endl;

    cout << "Heder Type: " << header.bfType << endl;
    cout << "Heder bfSize: " << header.bfSize << endl;
    cout << "Heder bfReserved1: " << header.bfReserved1 << endl;
    cout << "Heder bfReserved2: " << header.bfReserved2 << endl;
    cout << "Heder bfOffBits: " << header.bfOffBits << endl;

    cout << "BNI Header: " << endl;
    cout << "BNI Header Size: " << bmiHeader.biSize << endl;
    cout << "BNI Header Width: " << bmiHeader.biWidth << endl;
    cout << "BNI Header Height: " << bmiHeader.biHeight << endl;
    cout << "BNI Header Planes: " << bmiHeader.biPlanes << endl;
    cout << "BNI Header BitCount: " << bmiHeader.biBitCount << endl;
    cout << "BNI Header Compression: " << bmiHeader.biCompression << endl;
    cout << "BNI Header SizeImage: " << bmiHeader.biSizeImage << endl;
    cout << "BNI Header X PelsPerMeter: " << bmiHeader.biXPelsPerMeter << endl;
    cout << "BNI Header Y PelsPerMeter: " << bmiHeader.biYPelsPerMeter << endl;
    cout << "BNI Header ClrUsed: " << bmiHeader.biClrUsed << endl;
    cout << "BNI Header ClrImportant: " << bmiHeader.biClrImportant << endl;

}

void EncryptBmp(const string& FileName, const string& OutputFileName, const string& Message)
{
    ReadBMPFile(FileName);
    char* Msg = nullptr;
    char* OutFile = nullptr;
    ConvertStrChar(Message, Msg);
    ConvertStrChar(OutputFileName, OutFile);
    int counter = 0;
    int pass = 0;

    my_conv CharByte;
    my_conv ColorByte;

    for (int i = 0; i < bmiHeader.biWidth && !(counter > Message.size()); i++)
    {
        for (int j = 0; j < bmiHeader.biHeight; j++)
        {
            
            if (pass == 2)
            {
                pass = 0;
                counter++;
            }
            
            if (counter > Message.size()) break;
            //cout << "Pass - " << pass << "\t Count - " << counter << endl;

            CharByte.my_byte = Msg[counter];
            
            if (pass == 1)
            {
                //Red Chanale 
                //cout << "Red befor: " << rgb[i][j].rgbRed << "\t";
                ColorByte.my_byte = rgb[i][j].rgbRed;
                ColorByte.my_bits.b0 = CharByte.my_bits.b3;
                ColorByte.my_bits.b1 = CharByte.my_bits.b2;
                rgb[i][j].rgbRed = ColorByte.my_byte;
                //cout << "Red after: " << rgb[i][j].rgbRed << endl;


                //Green Chanel
                //cout << "Green befor: " << rgb[i][j].rgbGreen << "\t";
                ColorByte.my_byte = rgb[i][j].rgbGreen;
                ColorByte.my_bits.b0 = CharByte.my_bits.b1;
                ColorByte.my_bits.b1 = CharByte.my_bits.b0;
                rgb[i][j].rgbGreen = ColorByte.my_byte;
                //cout << "Green after: " << rgb[i][j].rgbGreen << endl;

                pass++;
            }
            if (pass == 0)
            {
                //Red Chanale 
                //cout << "Red befor: " << rgb[i][j].rgbRed << "\t"; 
                ColorByte.my_byte = rgb[i][j].rgbRed;
                ColorByte.my_bits.b0 = CharByte.my_bits.b7;
                ColorByte.my_bits.b1 = CharByte.my_bits.b6;
                rgb[i][j].rgbRed = ColorByte.my_byte;
                //cout << "Red after: " << rgb[i][j].rgbRed << endl;

                //Green Chanel
                //cout << "Green befor: " << rgb[i][j].rgbGreen << "\t";
                ColorByte.my_byte = rgb[i][j].rgbGreen;
                ColorByte.my_bits.b0 = CharByte.my_bits.b5;
                ColorByte.my_bits.b1 = CharByte.my_bits.b4;
                rgb[i][j].rgbGreen = ColorByte.my_byte;
                //cout << "Green after: " << rgb[i][j].rgbGreen << endl;

                pass++;
            }
        }
    }

    // Create new file
    pFile = fopen("2.bmp", "wb");
    set_u16(header.bfType);
    set_u32(header.bfSize);
    set_u16(header.bfReserved1);
    set_u16(header.bfReserved2);
    set_u32(header.bfOffBits);
    set_u32(bmiHeader.biSize);
    set_s32(bmiHeader.biWidth);
    set_s32(bmiHeader.biHeight);
    set_u16(bmiHeader.biPlanes);
    set_u16(bmiHeader.biBitCount);
    set_u32(bmiHeader.biCompression);
    set_u32(bmiHeader.biSizeImage);
    set_s32(bmiHeader.biXPelsPerMeter);
    set_s32(bmiHeader.biYPelsPerMeter);
    set_u32(bmiHeader.biClrUsed);
    set_u32(bmiHeader.biClrImportant);

    for (int i = 0; i < bmiHeader.biWidth; i++) {
        for (int j = 0; j < bmiHeader.biHeight; j++) {
            putc(rgb[i][j].rgbBlue, pFile);
            putc(rgb[i][j].rgbGreen, pFile);
            putc(rgb[i][j].rgbRed, pFile);
        }
        // пропускаем последний байт в строке
      putc(0, pFile);
    }
    fclose(pFile);


}

void DecryptBmp(const string& FileName)
{
    ReadBMPFile(FileName);
    char Msg[1000];


    int counter = 0;
    int pass = 0;

    my_conv CharByte;
    my_conv ColorByte;
    ColorByte.my_byte;

    for (int i = 0; i < bmiHeader.biWidth && Msg[counter] != '\0'; i++)
    {
        for (int j = 0; j < bmiHeader.biHeight; j++)
        {

            
            if (pass == 2)
            {
                pass = 0;
                Msg[counter] = CharByte.my_byte;
                if (Msg[counter] == '\0') break;
                counter++;
            }
            //cout << "Pass - " << pass << "\t Count - " << counter << endl;
            //if (Msg[counter - 1] == '\0') break;

            if (pass == 1)
            {
                //Red Chanale 
                //cout << "Red befor: " << rgb[i][j].rgbRed << "\t";
                ColorByte.my_byte = rgb[i][j].rgbRed;
                CharByte.my_bits.b3 = ColorByte.my_bits.b0;
                CharByte.my_bits.b2 = ColorByte.my_bits.b1;
                //rgb[i][j].rgbRed = ColorByte.my_byte;
                //cout << "Red after: " << rgb[i][j].rgbRed << endl;


                //Green Chanel
                //cout << "Green befor: " << rgb[i][j].rgbGreen << "\t";
                ColorByte.my_byte = rgb[i][j].rgbGreen;
                CharByte.my_bits.b1 = ColorByte.my_bits.b0;
                CharByte.my_bits.b0 = ColorByte.my_bits.b1;
                //rgb[i][j].rgbGreen = ColorByte.my_byte;
                //cout << "Green after: " << rgb[i][j].rgbGreen << endl;

                pass++;
            }
            if (pass == 0)
            {
                CharByte.my_byte = rgb[i][j].rgbRed;
                //Red Chanale 
                //cout << "Red befor: " << rgb[i][j].rgbRed << "\t";
                ColorByte.my_byte = rgb[i][j].rgbRed;
                CharByte.my_bits.b7 = ColorByte.my_bits.b0;
                CharByte.my_bits.b6 = ColorByte.my_bits.b1;
                //rgb[i][j].rgbRed = ColorByte.my_byte;
                //cout << "Red after: " << rgb[i][j].rgbRed << endl;

                //Green Chanel
                //cout << "Green befor: " << rgb[i][j].rgbGreen << "\t";
                ColorByte.my_byte = rgb[i][j].rgbGreen;
                CharByte.my_bits.b5 = ColorByte.my_bits.b0;
                CharByte.my_bits.b4 = ColorByte.my_bits.b1;
                //rgb[i][j].rgbGreen = ColorByte.my_byte;
                //cout << "Green after: " << rgb[i][j].rgbGreen << endl;

                pass++;
            }
        }
    }

    for (int i = 0; Msg[i] != '\0'; i++)
        cout << Msg[i];
}

unsigned short read_u16(FILE* fp)
{
    unsigned char b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);
    
    return ((b1 << 8) | b0);
}

unsigned int read_u32(FILE* fp)
{
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);
    
    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int read_s32(FILE* fp)
{
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

void set_u16(unsigned short value)
{
    my_conv PutValue;
    uint8_t temp[32] = { 0 };

    for (int j = sizeof(value) * 8 - 1; j >= 0; --j)
    {
        if ((int)((value >> j) & 1))
            temp[j] = 1;
        else
            temp[j] = 0;

    } 

    PutValue.my_bits.b7 = temp[7];
    PutValue.my_bits.b6 = temp[6];
    PutValue.my_bits.b5 = temp[5];
    PutValue.my_bits.b4 = temp[4];
    PutValue.my_bits.b3 = temp[3];
    PutValue.my_bits.b2 = temp[2];
    PutValue.my_bits.b1 = temp[1];
    PutValue.my_bits.b0 = temp[0];

    putc(PutValue.my_byte, pFile);

    PutValue.my_bits.b7 = temp[15];
    PutValue.my_bits.b6 = temp[14];
    PutValue.my_bits.b5 = temp[13];
    PutValue.my_bits.b4 = temp[12];
    PutValue.my_bits.b3 = temp[11];
    PutValue.my_bits.b2 = temp[10];
    PutValue.my_bits.b1 = temp[9];
    PutValue.my_bits.b0 = temp[8];

    putc(PutValue.my_byte, pFile);   
}

void set_u32(unsigned int value)
{
    my_conv PutValue;
    uint8_t temp[32] = { 0 };

    for (int j = sizeof(value) * 8 - 1; j >= 0; --j)
    {
        if ((int)((value >> j) & 1))
            temp[j] = 1;
        else
            temp[j] = 0;

    }

    PutValue.my_bits.b7 = temp[7];
    PutValue.my_bits.b6 = temp[6];
    PutValue.my_bits.b5 = temp[5];
    PutValue.my_bits.b4 = temp[4];
    PutValue.my_bits.b3 = temp[3];
    PutValue.my_bits.b2 = temp[2];
    PutValue.my_bits.b1 = temp[1];
    PutValue.my_bits.b0 = temp[0];
    
    putc(PutValue.my_byte, pFile);
    
    PutValue.my_bits.b7 = temp[15];
    PutValue.my_bits.b6 = temp[14];
    PutValue.my_bits.b5 = temp[13];
    PutValue.my_bits.b4 = temp[12];
    PutValue.my_bits.b3 = temp[11];
    PutValue.my_bits.b2 = temp[10];
    PutValue.my_bits.b1 = temp[9];
    PutValue.my_bits.b0 = temp[8];

    putc(PutValue.my_byte, pFile);

    PutValue.my_bits.b7 = temp[23];
    PutValue.my_bits.b6 = temp[22];
    PutValue.my_bits.b5 = temp[21];
    PutValue.my_bits.b4 = temp[20];
    PutValue.my_bits.b3 = temp[19];
    PutValue.my_bits.b2 = temp[18];
    PutValue.my_bits.b1 = temp[17];
    PutValue.my_bits.b0 = temp[16];

    putc(PutValue.my_byte, pFile);


    PutValue.my_bits.b7 = temp[31];
    PutValue.my_bits.b6 = temp[30];
    PutValue.my_bits.b5 = temp[29];
    PutValue.my_bits.b4 = temp[28];
    PutValue.my_bits.b3 = temp[27];
    PutValue.my_bits.b2 = temp[26];
    PutValue.my_bits.b1 = temp[25];
    PutValue.my_bits.b0 = temp[24];

    putc(PutValue.my_byte, pFile);
}

void set_s32(int value)
{
    my_conv PutValue;
    uint8_t temp[32] = { 0 };

    for (int j = sizeof(value) * 8 - 1; j >= 0; --j)
    {
        if ((int)((value >> j) & 1))
            temp[j] = 1;
        else
            temp[j] = 0;

    }

    PutValue.my_bits.b7 = temp[7];
    PutValue.my_bits.b6 = temp[6];
    PutValue.my_bits.b5 = temp[5];
    PutValue.my_bits.b4 = temp[4];
    PutValue.my_bits.b3 = temp[3];
    PutValue.my_bits.b2 = temp[2];
    PutValue.my_bits.b1 = temp[1];
    PutValue.my_bits.b0 = temp[0];

    putc(PutValue.my_byte, pFile);


    PutValue.my_bits.b7 = temp[15];
    PutValue.my_bits.b6 = temp[14];
    PutValue.my_bits.b5 = temp[13];
    PutValue.my_bits.b4 = temp[12];
    PutValue.my_bits.b3 = temp[11];
    PutValue.my_bits.b2 = temp[10];
    PutValue.my_bits.b1 = temp[9];
    PutValue.my_bits.b0 = temp[8];

    putc(PutValue.my_byte, pFile);
    

    PutValue.my_bits.b7 = temp[23];
    PutValue.my_bits.b6 = temp[22];
    PutValue.my_bits.b5 = temp[21];
    PutValue.my_bits.b4 = temp[20];
    PutValue.my_bits.b3 = temp[19];
    PutValue.my_bits.b2 = temp[18];
    PutValue.my_bits.b1 = temp[17];
    PutValue.my_bits.b0 = temp[16];

    putc(PutValue.my_byte, pFile);
    

    PutValue.my_bits.b7 = temp[31];
    PutValue.my_bits.b6 = temp[30];
    PutValue.my_bits.b5 = temp[29];
    PutValue.my_bits.b4 = temp[28];
    PutValue.my_bits.b3 = temp[27];
    PutValue.my_bits.b2 = temp[26];
    PutValue.my_bits.b1 = temp[25];
    PutValue.my_bits.b0 = temp[24];

    putc(PutValue.my_byte, pFile);
    
}


void print_bin(uint8_t value)
{
    for (int i = 7; i >= 0; --i)
    {
        if (value & (1 << i))
            cout << "1";
        else
            cout << "0";
    }
    cout << endl;
}

void ConvertStrChar(const string& str, char*& charArr)
{
    charArr = new char[str.size() + 1];
    for (size_t i = 0; i < str.size(); ++i)
    {
        charArr[i] = str[i];
    }
    charArr[str.size()] = '\0';
}