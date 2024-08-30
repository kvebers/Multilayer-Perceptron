#include "../includes/Perception.hpp"

int main()
{
    // data preprocessing
    size_t seed = 2002;
    string input_file = "data.csv";
    string trainingFile = "training.csv";
    string testingFile = "testing.csv";
    vector<size_t> params;
    size_t prediction = 1;
    vector<pair<string, std::vector<float>>> trainingData;
    vector<pair<string, std::vector<float>>> testingData;
    for (size_t i = 2; i < 32; i++)
    {
        params.push_back(i);
    }
    params.reserve(30);

    // data spliting training / testing
    splitDataFiles(input_file, trainingFile, testingFile, seed);
    trainingData = splitDataInVectors(trainingFile, params, prediction);
    testingData = splitDataInVectors(testingFile, params, prediction);

    // create network
    Network network;
    InputLayer inputLayer(params.size(), "relu");
    HiddenLayer hiddenLayer(10, "softmax", "random");
    HiddenLayer hiddenLayer2(10, "softmax", "random");
    OutputLayer outputLayer(identityLabels(trainingData), "sigmoid", "random");
    network.addLayer(inputLayer);
    network.addLayer(hiddenLayer);
    network.addLayer(hiddenLayer2);
    network.addLayer(outputLayer);
    network.CheckValidNetwork();
    // training
    training(trainingData, testingData, network);   
    // testing
    // predict();
    return 0;
}