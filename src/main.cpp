#include <iostream>

#include "marian.h"

/**
 * Builds the example graph from the documentation.
 */
marian::Expr example_one(marian::Ptr<marian::ExpressionGraph> graph) {

  graph->clear();

  // Set up x as a parameter
  marian::Expr x = graph->param("x", {1, 1}, marian::inits::fromValue(2));
  debug(x, "x");  // Output the value of x during graph forward/backward

  // Add input node y
  auto y = graph->constant({1, 1}, marian::inits::fromValue(3));

  // Define expression
  auto mulOp = x * y;
  auto sinOp = sin(x);
  auto z = mulOp + sinOp;

  debug(z, "z"); // Output the value of z during graph forward/backward

  // Pass the 'actual' value
  auto actual = graph->constant({1, 1}, marian::inits::fromValue(6));

  // Define loss function
  auto loss = abs(actual - z);
  return loss;
}

int main() {

  // Create the graph and assign it to the CPU
  marian::Ptr <marian::ExpressionGraph>  graph = marian::New<marian::ExpressionGraph>();
  graph->setDevice({0, marian::DeviceType::cpu});
  graph->reserveWorkspaceMB(8);

  // Model filename
  std::string filename{"example-model.npz"};

  // Load parameters from model
  // if (marian::filesystem::exists(filename)) {
  //   graph->load(filename);
  //   std::cerr << "Parameters have been loaded from '" << filename << "'.\n";
  // }

  // Create the graph from the documentation example
  auto output = example_one(graph);

  // Perform a forward pass on the graph
  std::cerr << "---- Forward Pass ----\n";
  graph->forward();

  // Perform a backward pass on the graph
  std::cerr << "---- Backward Pass ----\n";
  graph->backward();

  // Setup a SGD optimizer.
  marian::Ptr<marian::Options> opts = marian::New<marian::Options>(
      "optimizer", "sgd",
      "learn-rate", 0.005);
  auto opt = marian::Optimizer(opts);

  // Update the graph
  std::cerr << "---- Optimizer Update ----\n";
  opt->update(graph, 0);

  // Output the updated value of x.
  std::cerr << "Debug: x\n" << graph->get("x")->val()->debug();

  // Save parameters to file
  graph->save(filename);
  std::cerr << "Parameters have been saved to '" << filename << "'.\n";

  return 0;
}
