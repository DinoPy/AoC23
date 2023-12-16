#!/bin/bash

path="./"

fswatch -r "$path" |
while read -r fullpath
do
  # Your action here
  filename=$(basename "$fullpath")
    filename_no_extension="${filename%.*}"

  if [[ -f "$fullpath" && "$filename" != *~  ]]; then
    echo "File $filename has been modified."

      if [[ "$filename" == *.py ]]; then
    python3 ${filename} sample.txt
      fi

      if [[ "$filename" == *.cpp ]]; then
          make target name=${filename_no_extension}
      fi
  fi

done
