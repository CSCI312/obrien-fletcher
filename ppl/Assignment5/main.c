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
    run_scoring_engine(model, data);

    free_Data(data);     
    free_Model(model);    

    return 0;
}

