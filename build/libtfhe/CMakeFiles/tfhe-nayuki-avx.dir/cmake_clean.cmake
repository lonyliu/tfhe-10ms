file(REMOVE_RECURSE
  "libtfhe-nayuki-avx.pdb"
  "libtfhe-nayuki-avx.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C CXX)
  include(CMakeFiles/tfhe-nayuki-avx.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
