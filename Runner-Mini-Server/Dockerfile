# Use an official Ubuntu image
FROM ubuntu:latest

# Install required dependencies
RUN apt-get update && apt-get install -y cmake g++ make

# Set working directory inside the container
WORKDIR /app

# Copy the source code into the container
COPY . /app

# Remove old CMake cache, create a new build directory, and compile the project
RUN rm -rf build && mkdir build && cd build && cmake -G "Unix Makefiles" .. && cmake --build .

# Set the default command to run the compiled program
CMD ["./build/miniserver"]
