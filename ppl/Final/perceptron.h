#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct data   *Data;
typedef struct model  *Model;

Data   new_Data(const char *fname);
Model  new_Model(const Data data);
void   fit_model(Model model, Data data);
void   run_scoring_engine(const Model model, const Data data);
int    get_num_examples(Data data);
int    get_num_features(Data data);
void   delete_Data(Data data);
void   delete_Model(Model model);

#endif

