import java.util.List;
import java.util.ArrayList;

class Weight {
  double value;
  Weight(double value) { this.value = value; }
}

class Model {
  List<Weight> weights = new ArrayList<Weight>();
  Double dimensionality = 0;

  Model(Data data) {
    dimensionality = data.number_of_features + 1;
    for (int i = 0; i < dimensionality; i++) {
      weights.add(new Weight(Math.random()));
    }
  }

  void sgd(Example example) {
    for (int i = 0; i < weights.size(); i++) {
      weights.get(i).value += example.target * example.input.get(i);
    }
  }

  void fit(Data data) {
    for (int i = 0; i < data.examples.size(); i++) {
      sgd(data.examples.get(i));
    }
  }

  int predict(Example example) {
    double hypothesis = 0.0;
    for (int i = 0; i < weights.size(); i++) {
      hypothesis += weights.get(i).value * example.input.get(i);
    }
    return (hypothesis < 0) ? -1 : 1;
  }

  void evaluate(Data data) {
  }

  void runScoringEngine() {
  }
}
