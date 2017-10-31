file(REMOVE_RECURSE
  "libtfhe-fftw.pdb"
  "libtfhe-fftw.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/tfhe-fftw.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
