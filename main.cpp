#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "utils.h"
#include "zipper.h"

enum Command { COMPRESS = 1, DECOMPRESS = 2, EXIT = 3 };

void performOperation(HuffmanCompression& hc, const std::string& operation) {
    std::string inputFilename = getFilename("Enter input file path: ");
    std::string outputFilename =
        extractOriginalFilename(inputFilename) + "_" + operation + "ed.txt";
    std::cout << operation << "ing file...\n";
    try {
        if (operation == "compress") {
            hc.compress(inputFilename, outputFilename);
        } else if (operation == "decompress") {
            hc.decompress(inputFilename, outputFilename);
        }
        std::cout << "File " << operation << "ed successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Unable to open file " << inputFilename << ".\n";
        return;
    }
}

Command getValidCommand() {
    int command;
    while (true) {
        system("clear");
        std::cout << "Choose action:\n1. Compress \n2. Decompress \n3. Exit \nChoice:";
        std::cin >> command;
        if (command == Command::COMPRESS || command == Command::DECOMPRESS ||
            command == Command::EXIT) {
            break;
        } else {
            std::cerr << "Invalid command.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return (Command)command;
}

int main() {
    HuffmanCompression hc;
    std::string inputFilename;
    std::string outputFilename;

    while (true) {
        Command command = getValidCommand();
        switch (command) {
            case Command::COMPRESS:
                performOperation(hc, "compress");
                break;
            case Command::DECOMPRESS:
                performOperation(hc, "decompress");
                break;
            case Command::EXIT:
                std::cout << "Exiting...\n";
                break;
        }
        if (command == Command::EXIT) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}
