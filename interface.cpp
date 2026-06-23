#include "interface.hpp"

void parse_position (std::istringstream &ss) {
    std::string token;
    ss >> token;

    if (token == "startpos") {
        set_position("a/a/a/a/a/a/a/a/a/a w 0");
        ss >> token;
    }

    else if (token == "bn") {
        std::string pos;

        while (ss >> token && token != "moves") {
            pos += token + " ";
        }
        pos.pop_back();
        
        set_position(pos);
    }

    if (token == "moves") {
        while (ss >> token) {
            make_move(std::stoi(token));
        }
    }
}

void o5i () {
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "o5i") {
            std::cout << "id name omega-five\n";
            std::cout << "id author nicoalesi\n";
            std::cout << "o5iok\n";
        }
        
        else if (cmd == "isready") {
            std::cout << "readyok\n";
        }
        
        else if (cmd == "newgame") {
            reset();
        }

        else if (cmd == "position") {
            parse_position(ss);
        }

        else if (cmd == "go") {
            int depth = 6;
            std::string param;

            if (ss >> param) {
                depth = std::stoi(param);
                depth = depth > MAX_DEPTH ? MAX_DEPTH : depth;
            }

            std::cout << "bestmove " << search_best_move(depth) << "\n";
        }

        else if (cmd == "evaluate") {
            int depth = 6;
            std::string param;

            if (ss >> param) {
                depth = std::stoi(param);
                depth = depth > MAX_DEPTH ? MAX_DEPTH : depth;
            }

            std::cout << "value " << negamax(depth, -INT32_MAX, INT32_MAX) << "\n";
        }

        else if (cmd == "quit") {
            break;
        }

        std::cout << std::flush;
    }
}
