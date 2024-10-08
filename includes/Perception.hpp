#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <random>


using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cerr;
using std::size_t;
using std::getline;
using std::vector;
using std::pair;
using std::map;
using std::max;
using std::unique_ptr;
using std::move;
using std::make_unique;
using std::clamp;
using std::shuffle;
using std::mt19937;
using std::random_device;

using WeightInitFunctionPointer = float(*)(size_t, size_t); 
using ActivationFunctionPointer = vector<float>(*)(vector<float>);
using DerivativeActivationFunctionPointer = vector<float>(*)(vector<float>);

vector<float> relu(vector<float> x);
vector<float> softmax(vector<float> x);
vector<float> sigmoid(vector<float> x);
vector<float> myOwnTanh(vector<float> x);
vector<float> derivativeRelu(vector<float> x);
vector<float> derivativeSoftmax(vector<float> x);
vector<float> derivativeSigmoid(vector<float> x);
vector<float> derivativeMyOwnTanh(vector<float> x);

float zeros(size_t i, size_t j);
float ones(size_t i, size_t j);
float random(size_t i, size_t j);
float he(size_t i, size_t j);
float heNormal(size_t i, size_t j);


class Layer
{
    public:
        ~Layer();
        Layer& operator=(const Layer& layer) = default;
        Layer(const Layer& layer) = default;
        Layer(string layerName, size_t size, string activationFunction, string weightInitialization);
        void InitializeWeights(size_t neuronCount, string functionName, size_t previousLayerSize);
        vector<float> neurons;
        vector<float> bias;
        vector<vector<float>> weights;
        vector<vector<float>> gradientWeights;
        vector<float> gradientNeuronBias;
        string layerName;
        size_t size;
        string weightInitialization;
        string activationFunction;
        WeightInitFunctionPointer returnFunctionToInit(std::string &functionName, std::map<std::string, WeightInitFunctionPointer> &functionMap);
        ActivationFunctionPointer returnFunctionToExecute(string &functionName, map<string, ActivationFunctionPointer> &functionMap);
};

class Network
{
    public:
        Network();
        ~Network();
        void addLayer(string layerName, size_t size, string activationFunction, string weightInitialization);
        void CheckValidNetwork();
        vector<unique_ptr<Layer>> layers;
        vector<string> labels;
        vector<float> predict(pair<string, std::vector<float>> &input);
        void initializeNeuralNetworkWeights();
        void importNetwork(const string &file, vector<pair<string, std::vector<float>>> &trainingData, vector<size_t> &params);
        void exportNetwork(const string &file);
        void importWeights(const string &file);
        void initializeLabels(vector<pair<string, std::vector<float>>> &data);
        string extractPrediction(vector<float> &output);
        float calculateBinaryCrossEntropy(vector<float> &output, string label);
        void backpropagation(vector<float> &output, vector<float> &target);
        vector<float> createTargetVector(string &label);
        void applyGradients(float &learningRate);
};

void splitDataFiles(const string &inputFile, const string &trainingFile, const string &testingFile, const size_t &seed);
vector<pair<string, std::vector<float>>> splitDataInVectors(const string &file, std::vector<size_t> &params, const size_t &prediction);
void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network, size_t epochs, float learningRate);
size_t identityLabels(vector<pair<string, std::vector<float>>> &data);

#endif