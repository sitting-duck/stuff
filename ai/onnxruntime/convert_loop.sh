1 #cp /Volumes/project/*.pb ./
  2 
  3 pb_names=("m1" "m1_fast" "m2" "m2_fast" "m3")
  4 pb_input_size=("256" "512")
  5 
  6 version=1
  7 width=64
  8 height=64
  9 sizen=(1x 2x 4x 8x)
 10 outputs=("net8x/output1X:0" "net8x/output2X:0" "net8x/output4X:0" "net8x/output1X:0,net8x/output2X:0,net8x/output4X:0")
 11 
 12 for pb in "${!pb_names[@]}"; do
 13     for input_in in "${!pb_input_size[@]}"; do
 14         for i in "${!sizen[@]}"; do
 15             mkdir -p ${pb_input_size[$input_in]}
 16             python -m tf2onnx.convert --graphdef ${pb_names[$pb]}-${pb_input_size[$input_in]}.pb --output ${pb_input_size[$input_in]}/gpx-v${version}-fp32-${height}x${width}-${sizen[$i]}.onnx --inputs "netInput:0,t_param:0,t_para    m1:0" --outputs "${outputs[$i]}"
 17         done
 18     done
 19 done
~          
