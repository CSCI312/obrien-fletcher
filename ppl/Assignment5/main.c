#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <data_file>\n", argv[0]);
        exit(1);
    }

    char *fname = argv[1];

    // Building
    Data data = new_Data(fname);
    Model model = new_Model(data);

    // Training
    fit_model(model, data);

    // Scoring
    run_scoring_engine(model);

    // Clean up
    for (int i = 0; i < data->dims.num_examples; i++) {
        free(data->elements[i]);
    }
    free(data->elements);
    free(data->targets);
    free(data);
    free(model->weights);
    free(model);

    return 0;
}

