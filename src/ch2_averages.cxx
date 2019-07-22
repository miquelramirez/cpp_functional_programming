//
// Created by bowman on 19/07/19.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>
#include <cmath>
#include <algorithm>
#include <execution>
#include <numeric>

double average_score(const std::vector<int>& score_vec) {

    int sum = 0;

    for (int score: score_vec)
        sum += score;

    return sum / (double)score_vec.size();
}

double average_score2(const std::vector<int>& score_vec) {

    return std::accumulate(score_vec.cbegin(), score_vec.cend(), 0) / (double)score_vec.size();
}

double average_score3(const std::vector<int>& score_vec) {
    return std::reduce(
                std::execution::par,
                score_vec.cbegin(), score_vec.cend(),
                0
            ) / (double) score_vec.size();
}

int main(int argc, char** argv) {
    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 4 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(4, 6);
    int mean = uniform_dist(e1);
    std::cout << "Randomly-chosen mean: " << mean << '\n';

    // Generate a normal distribution around that mean
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 2);

    std::cout << "Generating scores..." << std::endl;
    std::vector<int> movie_scores;
    for (unsigned i = 0; i < 10000; i++)
        movie_scores.push_back(std::round(normal_dist(e2)));

    std::cout << "== AVERAGING VECTORS ==" << std::endl;

    std::cout << "Plain C++ loop" << std::endl;
    auto t0 = std::chrono::system_clock::now();
    auto avg = average_score(movie_scores);
    auto tf = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = tf - t0;
    std::time_t end_time = std::chrono::system_clock::to_time_t(tf);

    std::cout << "Finished computation at " << std::ctime(&end_time)
                << " elapsed time: " << elapsed.count() << "s\n";
    std::cout << "Average score: " << avg << std::endl;

    std::cout << "std::accumulate" << std::endl;
    t0 = std::chrono::system_clock::now();
    avg = average_score2(movie_scores);
    tf = std::chrono::system_clock::now();

    elapsed = tf - t0;
    end_time = std::chrono::system_clock::to_time_t(tf);

    std::cout << "Finished computation at " << std::ctime(&end_time)
              << " elapsed time: " << elapsed.count() << "s\n";
    std::cout << "Average score: " << avg << std::endl;

    std::cout << "std::reduce() with std::execution::par" << std::endl;
    t0 = std::chrono::system_clock::now();
    avg = average_score3(movie_scores);
    tf = std::chrono::system_clock::now();

    elapsed = tf - t0;
    end_time = std::chrono::system_clock::to_time_t(tf);

    std::cout << "Finished computation at " << std::ctime(&end_time)
              << " elapsed time: " << elapsed.count() << "s\n";
    std::cout << "Average score: " << avg << std::endl;

    return 0;
}
