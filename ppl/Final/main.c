#include "perceptron.h"

int main(int argc, char **argv) {
    /* argv[1] = train.dat, argv[2] = test.dat */
    Data train = new_Data(argv[1]);
    Model m     = new_Model(train);
    fit_model(m, train);
    delete_Data(train);

    Data test  = new_Data(argv[2]);
    evaluate_model(m, test);
    delete_Data(test);

    delete_Model(m);
    return 0;
}

