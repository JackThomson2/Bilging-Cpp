#include <iostream>
#include <chrono>
#include "Generator.hpp"
#include "Searcher.hpp"

int main() {
    auto test_board = MakeTestBoard();

    auto start = std::chrono::steady_clock::now();
    auto result = GetBestMoveList(test_board, 5);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    std::cout << "Best move was: " << result.score << " it took " << std::chrono::duration <double, std::milli> (diff).count() << std::endl;
    return 0;
}
