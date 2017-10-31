file(REMOVE_RECURSE
  "libtfhe-spqlios-fma.pdb"
  "libtfhe-spqlios-fma.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM CXX)
  include(CMakeFiles/tfhe-spqlios-fma.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
