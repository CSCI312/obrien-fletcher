#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perceptron.h"

struct shape {
    int num_examples;
    int num_features;
};

struct data {
    double **elements; // 2D array for the features (inputs)
    double *targets;   // 1D array for the targets
    struct shape dims; // Shape to store num_examples and num_features
};

struct model {
    double *weights;   // 1D array for the weights
    struct shape dims; // Dimensionality of the model
};

Data new_Data(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(1);
    }

    Data data = (Data)malloc(sizeof(struct data));

    // Read the file to determine the number of examples and features
    char line[1024];
    int num_examples = 0;
    int num_features = 0;
    while (fgets(line, sizeof(line), fp)) {
        num_examples++;
        char *token = strtok(line, " ");
        while (token) {
            num_features++;
            token = strtok(NULL, " ");
        }
    }

    // Reset the file pointer and allocate memory for the data
    fseek(fp, 0, SEEK_SET);

    data->elements = (double **)malloc(num_examples * sizeof(double *));
    data->targets = (double *)malloc(num_examples * sizeof(double));

    data->dims.num_examples = num_examples;
    data->dims.num_features = num_features - 1; // Last value is the target

    // Read the data into the data structure
    int idx = 0;
    while (fgets(line, sizeof(line), fp)) {
        data->elements[idx] = (double *)malloc(data->dims.num_features * sizeof(double));

        char *token = strtok(line, " ");
        for (int i = 0; i < data->dims.num_features; i++) {
            data->elements[idx][i] = atof(token);
            token = strtok(NULL, " ");
        }

        data->targets[idx] = atof(token);  // Last value is the target
        idx++;
    }

    fclose(fp);
    return data;
}

Model new_Model(const Data data)
{
    Model model = (Model)malloc(sizeof(struct model));
    model->dims = data->dims;  // Get dimensionality from data

    // Initialize weights with random values
    model->weights = (double *)malloc((data->dims.num_features + 1) * sizeof(double)); // +1 for w0
    for (int i = 0; i < data->dims.num_features + 1; i++) {
        model->weights[i] = (double)rand() / RAND_MAX;
    }

    return model;
}

static void sgd(Model model, Data data, int idx)
{
    double xcoord, ycoord, target;

    // Get coordinates and target for the idx-th example
    xcoord = data->elements[idx][0];
    ycoord = data->elements[idx][1];
    target = data->targets[idx];

    // Update weights using the gradient
    model->weights[2] += target * xcoord;
    model->weights[1] += target * ycoord;
    model->weights[0] += target * 1;  // bias term
}

static int predict(Model model, Data data, int idx)
{
    double xcoord = data->elements[idx][0];
    double ycoord = data->elements[idx][1];

    double hypothesis = model->weights[2] * xcoord + model->weights[1] * ycoord + model->weights[0];
    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data)
{
    bool misclassified = true;

    while (misclassified) {
        misclassified = false;
        for (int i = 0; i < data->dims.num_examples; i++) {
            int hypothesis = predict(model, data, i);
            double target = data->targets[i];
            if ((hypothesis > 0 && target > 0) || (hypothesis < 0 && target < 0)) {
                continue;
            }
            sgd(model, data, i);
            misclassified = true;
        }
    }
}

void run_scoring_engine(const Model model)
{
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);

    printf("Prediction = %d\n", predict(model, model, x, y));
}
