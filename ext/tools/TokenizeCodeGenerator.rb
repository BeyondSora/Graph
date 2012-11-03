File.open("DeltaInitMacro.h", 'w') { |f|
  f.puts "#ifndef DELTA_INIT_MACRO_H"
  f.puts "#define DELTA_INIT_MACRO_H"

  f.puts "// This file is auto-generated by TokenizeCodeGenerator"
  f.puts "//"
  f.puts "// Used for initializing delta"
  f.puts ""

  for i in 0..254
    f.puts "#define INIT_#{i}(S) next((S), #{i}), INIT_#{i+1}(S)"
  end
  f.puts "#define INIT_255(S) next((S), 255)"

  f.puts ""
  f.puts "#endif//DELTA_INIT_MACRO_H"
}