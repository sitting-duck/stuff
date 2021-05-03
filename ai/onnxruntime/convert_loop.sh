
# I like to store my files on a NAS server, copy them onto my local machine and then copy the finished converted models back to a NAS
# server when I am done because models can take up a lot of space.
#cp /Volumes/project/*.pb ./

# Here is an example of what a model conversion script for onnxruntime might look like:

# You may have many models saved as pb files that you have frozen from your Tensorflow code
# for example you may have a "fast" model and a "slow" model, 
# or perhaps one model for mobile and one for desktop and so on
pb_names=("m1" "m1_fast" "m2" "m2_fast" "m3")

# all neural net inputs have a "size", in the case of CNNs, the size of the input is the dimensions of a 2D array
# that represents a 2 dimensional image
pb_input_size=("256" "512")

version=1
for pb in "${!pb_names[@]}"; do
  for input_in in "${!pb_input_size[@]}"; do
    for i in "${!sizen[@]}"; do
    
      mkdir -p ${pb_input_size[$input_in]}
      # all neural nets have input and output names that you must specify on the command line
      python -m tf2onnx.convert --graphdef ${pb_names[$pb]}-${pb_input_size[$input_in]}.pb --output ${pb_input_size[$input_in]}/model_name.onnx --inputs "input_name:0,parameter_name:0,parameter_name:0" --outputs "${outputs[$i]}"
      
    done
  done
done         
