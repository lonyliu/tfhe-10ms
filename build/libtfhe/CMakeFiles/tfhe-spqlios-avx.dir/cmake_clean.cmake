file(REMOVE_RECURSE
  "libtfhe-spqlios-avx.pdb"
  "libtfhe-spqlios-avx.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM CXX)
  include(CMakeFiles/tfhe-spqlios-avx.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
