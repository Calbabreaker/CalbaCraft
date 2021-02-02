function(set_project_options project_name)
    target_compile_features(${project_name} INTERFACE cxx_std_17)
endfunction()