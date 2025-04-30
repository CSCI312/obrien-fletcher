#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "perceptron.h"

struct shape {
    int num_examples;
    int num_features;
};

struct data {
    double **elements;
    double *targets;
    struct shape dims;
};

struct model {
    double *weights;
    struct shape dims;
};

Data new_Data(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", fname);
        exit(1);
    }

    Data data = (Data)malloc(sizeof(struct data));

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

    fseek(fp, 0, SEEK_SET);

    data->elements = (double **)malloc(num_examples * sizeof(double *));
    data->targets = (double *)malloc(num_examples * sizeof(double));

    data->dims.num_examples = num_examples;
    data->dims.num_features = num_features - 1;

    int idx = 0;
    while (fgets(line, sizeof(line), fp)) {
        data->elements[idx] = (double *)malloc(data->dims.num_features * sizeof(double));

        char *token = strtok(line, " ");
        for (int i = 0; i < data->dims.num_features; i++) {
            data->elements[idx][i] = atof(token);
            token = strtok(NULL, " ");
        }

        data->targets[idx] = atof(token);
        idx++;
    }

    fclose(fp);
    return data;
}

Model new_Model(const Data data)
{
    Model model = (Model)malloc(sizeof(struct model));
    model->dims = data->dims;
    model->weights = (double *)malloc((data->dims.num_features + 1) * sizeof(double));

    for (int i = 0; i < data->dims.num_features + 1; i++) {
        model->weights[i] = (double)rand() / RAND_MAX;
    }

    return model;
}

static void sgd(Model model, Data data, int idx)
{
    double xcoord = data->elements[idx][0];
    double ycoord = data->elements[idx][1];
    double target = data->targets[idx];

    model->weights[2] += target * xcoord;
    model->weights[1] += target * ycoord;
    model->weights[0] += target * 1;
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
    int max_iterations = 1000;
    int iterations = 0;

    while (misclassified && iterations < max_iterations) {
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
        iterations++;
    }
}

void run_scoring_engine(const Model model, const Data data)
{
    double x, y;

    printf("Enter x: \n");
    scanf("%lf", &x);

    printf("Enter y: \n");
    scanf("%lf", &y);

    printf("Prediction = %d\n", predict(model, data, 0));
}

int get_num_examples(Data data)
{
    return data->dims.num_examples;
}

int get_num_features(Data data)
{
    return data->dims.num_features;
}

void free_Model(Model model)
{
    if (model) {
        free(model->weights);
        free(model);
    }
}

void free_Data(Data data)
{
    for (int i = 0; i < data->dims.num_examples; i++) {
        free(data->elements[i]);
    }
    free(data->elements);
    free(data->targets);
    free(data);
}

