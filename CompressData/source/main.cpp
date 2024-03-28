#include <iostream>
#include <optional>
#include <vector>
#include <array>
#include <cstdint>
#include <sstream>

template<typename T>
struct Data
{
    T value;
    uint8_t count;
};

constexpr size_t sizeX{ 32 };
constexpr size_t sizeY{ 16 };

template<typename T>
/*
* Tutaj mia³em problem z std::array mianowicie nie mog³em omin¹æ tego, ¿e input z zadania jest trochê mniejszy
* ni¿ tablica przez co wykorzystywane by³y nieistniej¹ce dane.
*/
//using Array2D = std::array<std::array<T, sizeX>, sizeY>;
using Array2D = std::vector<std::vector<T>>;

template<typename T>
using CompressedData = std::optional<std::vector<Data<T>>>;

template<typename T>
CompressedData<T> compressData(const Array2D<T>& input)
{
    std::vector<Data<T>> compressedData;

    for (size_t i = 0; i < input.size(); i++)
    {
        Data<T>* currentValue = nullptr;
        for (size_t j = 0; j < input[i].size(); j++)
        {
            if (!currentValue || input[i][j] != currentValue->value)
            {
                compressedData.push_back({ input[i][j], 1 });
                currentValue = &(compressedData)[compressedData.size() - 1];
            }
            else
            {
                currentValue->count += 1;
            }
        }
    }

    if (sizeof(compressedData) < sizeof(input)) return std::nullopt;

    return compressedData;
}

int main()
{
    /*Array2D<int> input;
    input[0] = { 0, 0, 0, 1, 1, 2, 3 };
    input[1] = { 0, 0, 4, 4, 4, 2, 2 };
    input[2] = { 2, 2, 2, 2, 2, 1, 2 };*/

    Array2D<int> input = {
        { 0, 0, 0, 1, 1, 2, 3 },
        { 0, 0, 4, 4, 4, 2, 2 },
        { 2, 2, 2, 2, 2, 1, 2 } 
    };

    auto compressed = compressData(input);

    if (compressed.has_value())
    {
        auto vec = compressed.value();

        std::stringstream output{};
        output << "{";

        int inputX = 0;
        int inputY = 0;

        for (int i = 0; i < vec.size(); i++)
        {
            output << "{" << static_cast<int>(vec[i].value) << "," << static_cast<int>(vec[i].count) << "}";
            if (i < vec.size() - 1) output << ", ";

            inputX += vec[i].count;
            if (inputX >= input[inputY].size())
            {
                inputX = 0;
                inputY += 1;
                if (inputY < input.size()) output << "\n";
            }
        }

        output << "}";
        std::cout << output.str();
    }

    return 0;
}