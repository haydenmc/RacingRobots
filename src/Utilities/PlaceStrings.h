#pragma once

#include <string>

class PlaceStrings
{
public:
    static std::wstring GetPlaceString(uint8_t placeNumber)
    {
        std::wstring suffix = L"th";
        uint8_t lastNumber = placeNumber % 10;

        // Now for all the edge cases
        if (placeNumber != 11 && placeNumber != 12 && placeNumber != 13)
        {
            if (lastNumber == 1)
            {
                suffix = L"st";
            }
            else if (lastNumber == 2)
            {
                suffix = L"nd";
            }
            else if (lastNumber == 3)
            {
                suffix = L"rd";
            }
        }

        return std::to_wstring(placeNumber) + suffix;
    }
};