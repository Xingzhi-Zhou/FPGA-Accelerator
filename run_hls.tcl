open_project -reset accelerator_prj

add_files layer.cpp

add_files -tb layer_tb.cpp

set_top test

open_solution -reset solution1

set_part {xc7k325t-ffg900-1}
create_clock -period 10 -name default

csim_design -clean
csynth_design
# cosim_design
# export_design -format ip_catalog

exit