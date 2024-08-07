#!/bin/bash

# Navigate to the build directory
cd build

# Run CMake
cmake ..

# Build the project
make

# Run the executable
./FinancialNewsSentimentAnalyzer

# Navigate back to the project root
cd ..

echo "Project rebuilt and executed!"