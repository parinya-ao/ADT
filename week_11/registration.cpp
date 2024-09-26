#include <bits/stdc++.h>

using namespace std;

string extractLastDigits(const string input)
{
    string digits;
    bool foundDigit = false;

    for (int i = input.size() - 1; i >= 0; --i)
    {
        char ch = input[i];
        if (isdigit(ch))
        {
            digits = ch + digits; // เพิ่มตัวเลขที่พบที่ด้านหน้า
            foundDigit = true;    // พบตัวเลข
        }
        else if (foundDigit)
        {
            // ถ้าพบตัวเลขแล้วและเจอตัวอักษร ให้หยุดการเพิ่มตัวเลข
            break;
        }
    }

    return digits; // คืนค่าตัวเลขสุดท้าย
}

string extractBeforeLastDigits(const string input)
{
    string result;
    bool foundDigit = false;

    for (int i = input.size() - 1; i >= 0; --i)
    {
        char ch = input[i];
        if (isdigit(ch))
        {
            foundDigit = true; // พบตัวเลข
        }
        else if (foundDigit)
        {
            // ถ้าพบตัวเลขแล้วและเจอตัวอักษร ให้หยุดการเพิ่มตัวอักษร
            break;
        }
        else
        {
            result = ch + result; // เพิ่มตัวอักษรที่พบ
        }
    }

    // ถ้าพบตัวเลข ให้คืนค่าผลลัพธ์ที่กลับด้าน
    if (foundDigit)
    {
        reverse(result.begin(), result.end()); // กลับด้านผลลัพธ์
    }
    else
    {
        return input; // คืนค่าทั้งหมดถ้าไม่มีตัวเลข
    }

    return result; // คืนค่าชุดตัวอักษรที่อยู่ก่อนตัวเลขสุดท้าย
}

int main()
{
    string input;
    cout << "Enter a string: ";
    cin >> input;

    string lastDigits = extractLastDigits(input);
    string beforeLastDigits = extractBeforeLastDigits(input);

    cout << "Last digits: " << lastDigits << endl;
    cout << "Before last digits: " << beforeLastDigits << endl;

    return 0;
}
