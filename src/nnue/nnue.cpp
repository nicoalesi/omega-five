#include "nnue/nnue.hpp"

NNUE model;
int32_t acc_stack[STACK_DEPTH][2][HIDDEN_L1_SIZE];

const std::string WEIGHTS_FILE = "./weights.nnue";

void load_model () {
    std::ifstream file(WEIGHTS_FILE, std::ios::binary);

    if (!file) {
        std::exit(1);
    }

    file.read(reinterpret_cast<char*>(model.hl1_weights), sizeof(model.hl1_weights));
    file.read(reinterpret_cast<char*>(model.hl1_biases), sizeof(model.hl1_biases));

    file.read(reinterpret_cast<char*>(model.hl2_weights), sizeof(model.hl2_weights));
    file.read(reinterpret_cast<char*>(model.hl2_biases), sizeof(model.hl2_biases));

    file.read(reinterpret_cast<char*>(model.ol_weights), sizeof(model.ol_weights));
    file.read(reinterpret_cast<char*>(&model.ol_bias), sizeof(model.ol_bias));

    if (!file) {
        std::exit(1);
    }
}

void init_nnue () {
    load_model();
    std::memcpy(acc_stack[0][white], model.hl1_biases, sizeof(acc_stack[0][white]));
    std::memcpy(acc_stack[0][black], model.hl1_biases, sizeof(acc_stack[0][black]));
}
